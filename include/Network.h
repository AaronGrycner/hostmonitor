//
// Created by aaron on 8/21/23.
//

#ifndef YOSHIMIWRT_NETWORK_H
#define YOSHIMIWRT_NETWORK_H

#include <boost/asio.hpp>

#include "network_interface.h"

// class containing network information

using namespace boost::asio::ip;

class Network {
private:
    network_interface interface;
    address_v4_range range;

public:
    Network()=default;

    [[nodiscard]] network_interface get_interface() const { return interface; }

    bool in_range(const address_v4 &ip) { return range.find(ip) == range.end(); }
};

#endif //YOSHIMIWRT_NETWORK_H
