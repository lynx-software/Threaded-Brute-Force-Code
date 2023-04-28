#pragma once

#include <sys/times.h>

class ClockT {
    public:
        void StartClock();
        long int EndClock();
    private:
        clock_t startTime;
        clock_t endTime;
        tms startcpu;
        tms endcpu;
};