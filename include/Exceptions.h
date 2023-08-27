//
// Created by aaron on 8/21/23.
//

#ifndef YOSHIMIWRT_EXCEPTIONS_H
#define YOSHIMIWRT_EXCEPTIONS_H

#include "Logger.h"

class exception;

struct cache_file_error : public std::exception {
    cache_file_error() {
        Logger::log_msg("Error opening host cache file");
    }
};

struct create_log_dir_error : public std::exception {
    create_log_dir_error() {
        Logger::log_msg("Error creating log directory, logging is disabled");
    }
};

struct create_log_file_error : public std::exception {
    create_log_file_error() {
        Logger::log_msg("Error creating log file, logging is disabled");
    }
};

struct read_log_file_error : public std::exception {
    read_log_file_error() {
        Logger::log_msg("Error reading log file");
    }
};

struct write_log_file_error : public std::exception {
    write_log_file_error() {
        Logger::log_msg("Error writing to log file");
    }
};

#endif //YOSHIMIWRT_EXCEPTIONS_H
