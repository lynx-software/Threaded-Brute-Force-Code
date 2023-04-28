#include "ClockT.h"

#include <unistd.h>

void ClockT::StartClock() {
    startTime = times(&startcpu);

    return;
}

long int ClockT::EndClock() {
    endTime = times(&endcpu);

    // return time in seconds
    return (endTime - startTime) / sysconf(_SC_CLK_TCK);
}