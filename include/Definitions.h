//
// Created by aaron on 8/18/23.
//

#ifndef YOSHIMIWRT_DEFINITIONS_H
#define YOSHIMIWRT_DEFINITIONS_H

#include <boost/interprocess/detail/segment_manager_helper.hpp>

// Logger definitions
static std::string LOG_NAME{ "yoshimi.log"},
    LOG_DIR{"/var/log"};

// File definitions
static std::string MANUFACTURER_FILE{"/usr/share/nmap/nmap-mac-prefixes"},
            HOST_CACHE_FILE{"host_cache"},
            HOST_CACHE_DIR{"/etc/HostMonitor"};

// Memory definitions
static const char  *SHARED_MUTEX_NAME{"host_mutex"},
            *SHARED_MEMORY_NAME{"host_shared_memory"},
            *SHARED_VECTOR_NAME{"host_shared_vector"};

// Network definitions
const std::string DEFAULT_INTERFACE{"wlan0"};


#endif //YOSHIMIWRT_DEFINITIONS_H
