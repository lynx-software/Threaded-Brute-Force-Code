#pragma once

#include "Globals.h"
#include <string>

class SearchSpaceT {
    public:
        SearchSpaceT(int start, int end);
        void BruteForcePassword();
        void IncrementArray(int (&array)[MAX_CHARACTERS]);
    private:
        int startCharIndex;
        int endCharIndex;
};

std::string IntArrayToString(int indexArray[]);