#include "include/Header.h"

int main() {

    init_files();

    Host_Monitor monitor;
    Test test;

    while (true) {
        try {
        monitor.update_hosts();
        std::cout << test.read_hosts();
        }
        catch (const std::exception &e) {
            Logger::log_msg(e.what());
            break;
        }
        sleep(15);
    }

    return 0;
}
