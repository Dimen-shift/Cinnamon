/*
    https://github.com/gekomad/ThreadPool
    Copyright (C) Giuseppe Cannella

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


// A shared Spinlock implementation

#pragma once

#include <atomic>

using namespace std;

#ifdef _WIN32
#include <intrin.h>
#pragma intrinsic(_InterlockedExchange)
#define LOCK_TEST_AND_SET(_lock) _InterlockedExchange(&_lock, 1)
#define LOCK_RELEASE(_lock) _InterlockedExchange(&_lock, 0)
#else
#define LOCK_TEST_AND_SET(_lock) __sync_lock_test_and_set(&_lock, 1)
#define LOCK_RELEASE(_lock) __sync_lock_release(&_lock)
#endif

class Spinlock {
private:
    volatile long _write = 0;
    volatile atomic_int _read;

    void _lock(){
        while (true) {
            if (!LOCK_TEST_AND_SET(_write))
                return;
            while (_write);
        }
    }

public:
    Spinlock() : _read(false) { }

    inline void lock(){
        bool w = false;
        while (true) {
            if (!w && !LOCK_TEST_AND_SET(_write)) {
                w = true;
            }
            if (w && !_read) {
                return;
            }
            while ((!w && _write) || _read);
        }
    }

    inline void unlock(){
        LOCK_RELEASE(_write);
    }

    inline void sharedLock(){
        _lock();
        _read++;
        unlock();
    }

    inline void sharedUnlock(){
        _read--;
    }
};
