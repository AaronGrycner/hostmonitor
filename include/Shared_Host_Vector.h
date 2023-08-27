//
// Created by aaron on 8/20/23.
//

#ifndef YOSHIMIWRT_SHARED_HOST_VECTOR_H
#define YOSHIMIWRT_SHARED_HOST_VECTOR_H

#include "Definitions.h"
#include "Host.h"

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

using namespace boost::interprocess;

typedef allocator<std::string, managed_shared_memory::segment_manager>  mAllocator;
typedef vector<std::string, mAllocator> mVector;

class Shared_Host_Vector {
private:
    managed_shared_memory segment; // open or create the segment with given name and size
    interprocess_mutex *mutex;
    mVector *hosts;

public:
    Shared_Host_Vector() : segment{create_only, SHARED_MEMORY_NAME, 65536} {

        mAllocator alloc(segment.get_segment_manager()); // initialize allocator with segment manager

        hosts = segment.construct<mVector>(SHARED_VECTOR_NAME)(alloc); // construct vector in shared memory
        mutex = segment.construct<interprocess_mutex>(SHARED_MUTEX_NAME)(); // construct mutex in shared memory
    }

    ~Shared_Host_Vector() {
        shared_memory_object::remove(SHARED_MEMORY_NAME);
    }

    Shared_Host_Vector& operator = (const std::vector<Host> &other) {
        mutex->lock();

        hosts->clear();
        for (const auto &h : other) {
            hosts->push_back(h.to_string());
        }
        mutex->unlock();

        return *this;
    }

    [[nodiscard]] std::vector<std::string> to_vector() const {
        std::vector<std::string> temp;
        mutex->lock();
        for (const auto &h : *hosts) {
            temp.push_back(h);
        }
        mutex->unlock();
        return temp;
    }

};


#endif //YOSHIMIWRT_SHARED_HOST_VECTOR_H
