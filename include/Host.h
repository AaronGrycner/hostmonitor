//
// Created by aaron on 8/17/23.
//

#ifndef YOSHIMIWRT_HOST_H
#define YOSHIMIWRT_HOST_H

#include <string>
#include <utility>

#include "HWAddress.h"
#include "IPv4Address.h"

class Host {
private:
     HWAddress mac_address{};
     IPv4Address ip_address{};

     std::string hostname{},
        manufacturer{};
public:
    Host(HWAddress mac, IPv4Address ip);
    Host(HWAddress mac, IPv4Address ip, std::string hostname, std::string manufacturer);

    // getters
    [[nodiscard]] HWAddress get_mac() const { return mac_address;}
    [[nodiscard]] IPv4Address get_ip() const { return ip_address;}
    [[nodiscard]] std::string get_hostname() const { return hostname;}
    [[nodiscard]] std::string get_manufacturer() const { return manufacturer;}
    [[nodiscard]] std::string to_string() const;

    // setters
    void set_mac(const HWAddress &mac) { mac_address = mac;}
    void set_ip(const IPv4Address &ip) { ip_address = ip;}
    void set_hostname(const std::string &name) { hostname = name;}
    void set_manufacturer(const std::string &man) { manufacturer = man; }

    // operators
    bool operator==(const Host &rhs) const;
    bool operator!=(const Host &rhs) const;

};

#endif //YOSHIMIWRT_HOST_H
