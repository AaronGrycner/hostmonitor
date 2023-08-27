//
// Created by aaron on 7/24/23.
//

#ifndef YOSHIMI_LOGGER_H
#define YOSHIMI_LOGGER_H

#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>
#include <filesystem>

#include "Definitions.h"

static bool OUTPUT_ENABLED{true};

class Logger {
private:
    static time_t get_time() {
        auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        return now;
    }

    static std::string make_log_message(const std::string &msg) {
        std::stringstream st;

        st << get_time() << ": " << msg;

        return st.str();
    };

public:
    static void toggle_output() {
        OUTPUT_ENABLED = !OUTPUT_ENABLED;
    }

    static bool create_log_dir() {
        if (!std::filesystem::exists(LOG_DIR)) {
            std::string cmd{"mkdir " + LOG_DIR};
            return system(cmd.c_str());
        }
        else {
            return true;
        }
    }

    static bool create_log_file() {
        if (!std::filesystem::exists(LOG_DIR + "/" + LOG_NAME)) {
            std::ofstream log{LOG_DIR + "/" + LOG_NAME};
            log << make_log_message("Log file created.") << std::endl;
            log.close();
        }

        if (std::filesystem::exists(LOG_DIR + "/" + LOG_NAME)) {
            return true;
        }
        else {
            return false;
        }
    }

    static bool log_error(const std::string &err) {
        std::ofstream log{LOG_NAME, std::ios::app};

        if (err.empty()) {
            return true;
        }

        if (log) {
            log << make_log_message("ERROR: " + err) << std::endl;
            std::cout << "ERROR: " << err << std::endl;
            log.close();
            return true;
        }

        else {
            log.close();
            return false;
        }
    }

    static bool log_msg(const std::string &msg) {
        std::ofstream log{LOG_NAME, std::ios::app};

        if (msg.empty()) {
            return true;
        }

        if (log) {
            log << make_log_message(msg) << std::endl;

            if (OUTPUT_ENABLED) {
                std::cout << msg << std::endl;
            }
            log.close();
            return true;
        }

        else {
            log.close();
            return false;
        }
    }
};

#endif //YOSHIMI_LOGGER_H
