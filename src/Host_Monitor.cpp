//
// Created by aaron on 8/17/23.
//

#include "../include/Host_Monitor.h"

Host_Monitor::Host_Monitor() {
    Logger::log_msg("Host_Monitor starting...");
}

[[maybe_unused]] void Host_Monitor::update_hosts() {
    std::vector<Host> new_hosts;
    Logger::log_msg("Updating host list...");
    FILE *fp;
    char buf[512];
    std::string cmd{"arp -a"};

    // run command and pipe output
    fp = popen(cmd.c_str(), "r");

    // check for error
    if (fp == nullptr) {
        Logger::log_msg("Error opening pipe. Code: " + std::to_string(pclose(fp)));
    }

    // read output
    while (fgets(buf, sizeof(buf), fp) != nullptr) {
        std::string line{buf};
        HWAddress mac;
        IPv4Address ip;

        // find mac and ip
        mac = Network_Utils::find_mac(line);
        ip = Network_Utils::find_ip(line);

        Host temp(mac, ip);

        // check if current host is in cache, if so, add it to new_hosts
        auto cache_check = std::find(host_cache.begin(), host_cache.end(), temp);
        if (cache_check != host_cache.end()) {
            new_hosts.push_back(*cache_check);
            continue;
        }

        // if not, add to cache and host list
        else {

            // get host info using Network Utils
            Network_Utils::oui_lookup(temp);
            Network_Utils::name_lookup(temp);

            // add host to cache and new_hosts
            new_hosts.push_back(temp);
            if (!write_host_to_cache(temp)) {
                throw cache_file_error();
            }
        }
    }

    // update shared host vector
    Logger::log_msg(std::to_string(new_hosts.size()) + " hosts found.");
    hosts = new_hosts;

    // close pipe
    pclose(fp);
}

bool Host_Monitor::write_host_to_cache(const Host &h) {
    cache_file_in.open(HOST_CACHE_DIR + HOST_CACHE_FILE, std::ios::app);
    std::string temp;

    if (!cache_file_in) {
        return false;
    }

    while (cache_file_in.good()) {
        std::getline(cache_file_in, temp);
        if (temp.find(h.get_mac().to_string()) != std::string::npos) {
            cache_file_in.close();
            return true;
        }
        cache_file_in.peek();
    }

    cache_file_in.close();
    cache_file_out.open(HOST_CACHE_DIR + HOST_CACHE_FILE, std::ios::app);

    if (!cache_file_out) {
        return false;
    }

    cache_file_out << h.get_mac().to_string() << "-"
    << h.get_ip().to_string() << "-"
    << h.get_hostname() << "-"
    << h.get_manufacturer()
    << std::endl;

    cache_file_out.close();
    return true;
}

bool Host_Monitor::read_cache_file() {
    cache_file_in.open(HOST_CACHE_DIR + HOST_CACHE_FILE, std::ios::app);

    if (!cache_file_in) {
        return false;
    }

    std::string line;
    while (std::getline(cache_file_in, line)) {
        std::string mac, ip, hostname, manufacturer;

        mac = line.substr(0, line.find('-'));
        line.erase(0, line.find('-') + 1);

        ip = line.substr(0, line.find('-'));
        line.erase(0, line.find('-') + 1);

        hostname = line.substr(0, line.find('-'));
        line.erase(0, line.find('-') + 1);

        manufacturer = line.substr(0, line.find('-'));
        line.erase(0, line.find('-') + 1);

        Host temp(HWAddress(mac), IPv4Address(ip), hostname, manufacturer);
        host_cache.push_back(temp);
    }

    cache_file_in.close();
    return true;
}
