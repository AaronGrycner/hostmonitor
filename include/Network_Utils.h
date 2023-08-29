//
// Created by aaron on 8/18/23.
//

#ifndef YOSHIMIWRT_NETWORK_UTILS_H
#define YOSHIMIWRT_NETWORK_UTILS_H

#include <vector>
#include <ifaddrs.h>
#include <regex>
#include <fstream>

namespace Network_Utils {

    static std::string find_ip(const std::string &input){
        std::string ip;
        std::regex ip_regex{R"((\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}))"};
        std::smatch match;

        if (std::regex_search(input, match, ip_regex)) {
            ip = match[0];
        }
        return ip;
    }

    static std::string find_mac(const std::string &input){
        std::string mac;
        std::regex mac_regex{R"(([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2}))"};
        std::smatch match;

        if (std::regex_search(input, match, mac_regex)) {
            mac = match[0];
        }
        return mac;
    }

    static void oui_lookup(Host &host) {
        std::ifstream file;
        file.open(MANUFACTURER_FILE);

        if (!file) {
            throw;
        }

        std::string line;

        // skip first 5 lines
        for (int i{}; i < 5; ++i) {
            std::getline(file, line);
        }

        while (file.good()) {
            std::getline(file, line, ' ');

            line.insert(2, ":");
            line.insert(5, ":");

            if (host.get_mac().to_string().contains(line)) {
                std::getline(file, line, '\n');
                size_t pos = line.find_first_not_of("\t ");
                file.close();
                host.set_manufacturer(line.substr(pos, line.find(' ', pos+1)));
            }

            // clear rest of line and peek next line
            getline(file, line);
            file.peek();
        }
        file.close();
    }

    static void name_lookup(Host &host) {
        FILE *fp;
        char buf[512];
        std::string name, cmd{"nslookup " + host.get_ip().to_string()};

        fp = popen(cmd.c_str(), "r");

        if (fp == nullptr) {
            return;
        }

        while (fgets(buf, sizeof(buf), fp) != nullptr) {
            std::string line{buf};

            if (line.find("name =") != std::string::npos) {
                name = line.substr(line.find("name =") + 6); // get name
                name.erase(std::remove(name.begin(), name.end(), '\n'), name.end()); // remove \r and \n
                name.erase(std::remove(name.begin(), name.end(), '\r'), name.end()); // remove \r and \n
                name.erase(name.find(".lan"), 4); // erase .lan from end of name
                host.set_hostname(name);
                break;
            }
        }
        pclose(fp);
    }
}

#endif //YOSHIMIWRT_NETWORK_UTILS_H
