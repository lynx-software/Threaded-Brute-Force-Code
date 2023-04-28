#pragma once

#include <string>
#include "Globals.h"

class SearchSpaceT {
    public:
        SearchSpaceT(int start, int end);
        void BruteForcePassword();
        const std::string GetResult();
    private:
        void IncrementArray(int (&array)[MAX_CHARACTERS]);

        static std::string result;
        int startCharIndex;
        int endCharIndex;
};

std::string IntArrayToString(int indexArray[]);