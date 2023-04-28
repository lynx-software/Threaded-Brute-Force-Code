#include "SearchSpaceT.h"

#include <cassert>
#include <iostream>
#include <crypt.h> // encryption

SearchSpaceT::SearchSpaceT(int start, int end) {
    if (DEBUG_MODE) {
        std::cout << "start = " << start << "\tend = " << end << std::endl;
    }
    assert(start <= end);
    assert(start >= 0);
    startCharIndex = start;
    endCharIndex = end;
    result = "";

    return;
}

void SearchSpaceT::BruteForcePassword() {
    std::string stringFromArray;
    std::string encryptedString;
    const std::string SALT = "DB";
    crypt_data data;
    int charIndexArray[MAX_CHARACTERS];

    charIndexArray[0] = startCharIndex;
    for (int i = 1; i < MAX_CHARACTERS; i++) {
        charIndexArray[i] = 0;
    }

    data.initialized = 0;

    while (charIndexArray[0] <= endCharIndex and result == "") {
        stringFromArray = IntArrayToString(charIndexArray);
        crypt_r(stringFromArray.c_str(), SALT.c_str(), &data);
        encryptedString = data.output;
        // if (DEBUG_MODE) {
        //     std::cout << "stringFromArray = " << stringFromArray << "\tencryptedString = " << encryptedString << std::endl;
        // }

        if (encryptedString == encryptedPassword) {
            if (DEBUG_MODE) {
                std::cout << "RESULT FOUND: " << stringFromArray << std::endl;
            }
            result = stringFromArray;
            charIndexArray[0] = endCharIndex + 1;
        } else {
            IncrementArray(charIndexArray);
        }
    }
}

void SearchSpaceT::IncrementArray(int (&array)[MAX_CHARACTERS]) {
    bool incremented = false;
    int i = MAX_CHARACTERS - 1;
    const int MAXVALUE = CHARS_IN_SET - 1;

    while (i >= 0 and !incremented) {
        if (array[i] != MAXVALUE) {
            array[i] += 1;
            incremented = true;
            for (int j = MAX_CHARACTERS - 1; j > i; j--) {
                if (array[j] == MAXVALUE) {
                    array[j] = 0;
                }
            }
        }
        i--;
    }

    if (!incremented) {
        array[0] = endCharIndex + 1;
    }

    return;
}

const std::string SearchSpaceT::GetResult() {
    return result;
}

std::string IntArrayToString(int indexArray[]) {
    std::string builtString;

    for (int i = 0; i < MAX_CHARACTERS; i++) {
        builtString = builtString + CHARACTER_SET[indexArray[i]];
    }

    return builtString;
}