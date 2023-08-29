//
// Created by aaron on 8/28/23.
//

#ifndef YOSHIMIWRT_NETWORK_INTERFACE_H
#define YOSHIMIWRT_NETWORK_INTERFACE_H

#include <string>

#include "Definitions.h"

class network_interface {
private:
    std::string name{DEFAULT_INTERFACE};

public:
    network_interface()=default;

    [[nodiscard]] std::string get_name() const { return name; }
};


#endif //YOSHIMIWRT_NETWORK_INTERFACE_H
