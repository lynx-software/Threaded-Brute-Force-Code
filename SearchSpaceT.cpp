
#include "SearchSpaceT.h"
#include <string>
#include <iostream>
#include <crypt.h> // encryption

using namespace std;

SearchSpaceT::SearchSpaceT(int start, int end) {
    startCharIndex = start;
    endCharIndex = end;

    return;
}

void SearchSpaceT::BruteForcePassword() {
    string stringFromArray;
    string encryptedString;
    const string SALT = "DB";
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
        if (DEBUG_MODE) {
            cout << "stringFromArray = " << stringFromArray << "\tencryptedString = " << encryptedString << endl;
        }

        if (encryptedString == encryptedPassword) {
            // result_mutex.lock();
            result = stringFromArray;
            // result_mutex.unlock();
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

string IntArrayToString(int indexArray[]) {
    string builtString;

    for (int i = 0; i < MAX_CHARACTERS; i++) {
        builtString = builtString + CHARACTER_SET[indexArray[i]];
    }

    return builtString;
}