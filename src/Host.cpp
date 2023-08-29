//
// Created by aaron on 8/17/23.
//

#include "../include/Host.h"

#include <utility>

Host::Host(HWAddress mac, IPv4Address ip) :
mac_address(std::move(mac)),
ip_address(std::move(ip))
{
}

Host::Host(HWAddress mac, IPv4Address ip, std::string hostname, std::string manufacturer) :
mac_address(std::move(mac)),
ip_address(std::move(ip)),
hostname(std::move(hostname)),
manufacturer(std::move(manufacturer))
{
}

std::string Host::to_string() const {
    if (manufacturer.empty() && hostname.empty()) {
        return "Unknown device (" + mac_address.to_string() + ")";
    }
    else if (manufacturer.empty()) {
        return "Device '" + hostname + "' (" + mac_address.to_string() + ")";
    }
    else if (hostname.empty()) {
        return manufacturer + " device (" + mac_address.to_string() + ")";
    }
    return manufacturer + " device '" + hostname + "' (" + mac_address.to_string() + ")";
}

bool Host::operator==(const Host &rhs) const {
    if (mac_address == rhs.mac_address) {
        return true;
    }
    return false;
}

bool Host::operator!=(const Host &rhs) const {
    if (mac_address != rhs.mac_address) {
        return true;
    }
    return false;
}