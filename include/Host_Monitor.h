//
// Created by aaron on 8/17/23.
//

#ifndef YOSHIMIWRT_HOST_MONITOR_H
#define YOSHIMIWRT_HOST_MONITOR_H

#include <vector>
#include <iostream>
#include <algorithm>

#include "Exceptions.h"
#include "Network.h"
#include "Shared_Host_Vector.h"
#include "Network_Utils.h"
#include "Logger.h"
#include "Definitions.h"
#include "Host.h"

class Host_Monitor {
private:
    std::ofstream cache_file_out;
    std::ifstream cache_file_in;
    Shared_Host_Vector hosts;
    Network network;
    std::vector<Host> host_cache;

    bool read_cache_file();
    bool write_host_to_cache(const Host &h);

public:
    Host_Monitor();

    void update_hosts();
    [[nodiscard]] std::vector<std::string> get_hosts() const { return hosts.to_vector(); }

};

#endif //YOSHIMIWRT_HOST_MONITOR_H
