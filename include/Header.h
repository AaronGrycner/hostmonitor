//
// Created by aaron on 8/17/23.
//

#ifndef YOSHIMIWRT_HEADER_H
#define YOSHIMIWRT_HEADER_H

#include <filesystem>

#include "Exceptions.h"
#include "Test.h"
#include "Logger.h"
#include "Definitions.h"
#include "Host_Monitor.h"

void init_files() {
    shared_memory_object::remove(SHARED_MEMORY_NAME);

    // create log directory if it doesn't exist
    if (!std::filesystem::exists(LOG_DIR + "/" + LOG_NAME)) {
        if(!Logger::create_log_file()) {
            throw create_log_file_error();
        }
    }

    // create log file if it doesn't exist
    if (!std::filesystem::exists(LOG_DIR + "/" + LOG_NAME)) {
        std::ofstream log_file_out(LOG_DIR + "/" + LOG_NAME);
        if (!log_file_out) {
            throw create_log_dir_error();
        }
    }

    // create host cache directory if it doesn't exist
    if (!std::filesystem::exists(HOST_CACHE_DIR)){
        std::filesystem::create_directory(HOST_CACHE_DIR);
    }

    // create host cache file if it doesn't exist
    if (!std::filesystem::exists(HOST_CACHE_DIR + "/" + HOST_CACHE_FILE)) {
        std::ofstream cache_file_out(HOST_CACHE_DIR + "/" + HOST_CACHE_FILE);
    }
}

#endif //YOSHIMIWRT_HEADER_H
