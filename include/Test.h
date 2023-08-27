//
// Created by aaron on 8/21/23.
//

#ifndef YOSHIMIWRT_TEST_H
#define YOSHIMIWRT_TEST_H

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/containers/vector.hpp>

#include "Definitions.h"

using namespace boost::interprocess;

typedef allocator<std::string, managed_shared_memory::segment_manager>  mAllocator;
typedef vector<std::string, mAllocator> mVector;

class Test {
private:
    managed_shared_memory segment{open_only, SHARED_MEMORY_NAME};
    mAllocator alloc{segment.get_segment_manager()};
    interprocess_mutex *mutex;
    mVector *hosts;

public:
    Test(){
        mutex = segment.find<interprocess_mutex>(SHARED_MUTEX_NAME).first;
        hosts = segment.find<mVector>(SHARED_VECTOR_NAME).first;

        if (!mutex || !hosts) {
            throw;
        }
    }

    ~Test() {
        shared_memory_object::remove(SHARED_MEMORY_NAME);
    }

    std::string read_hosts() {
        std::string temp;
        mutex->lock();
        for (const auto &h : *hosts) {
            temp += h + "\n";
        }
        mutex->unlock();
        return temp;
    }
};


#endif //YOSHIMIWRT_TEST_H
