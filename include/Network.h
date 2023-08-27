//
// Created by aaron on 8/21/23.
//

#ifndef YOSHIMIWRT_NETWORK_H
#define YOSHIMIWRT_NETWORK_H

#include <tins/address_range.h>
#include <tins/network_interface.h>
#include <tins/ip_address.h>

#include "Definitions.h"

// class containing network information

using namespace Tins;

class Network {
private:
    NetworkInterface interface{NetworkInterface::default_interface()};
    AddressRange<Tins::IPv4Address> range{interface.ipv4_address(), interface.ipv4_mask(), true};

public:
    Network()=default;

    [[nodiscard]] NetworkInterface get_interface() const {
        return interface;
    }

    bool in_range(IPv4Address ip) {
        return range.contains(ip);
    }
};

#endif //YOSHIMIWRT_NETWORK_H
