/*
    Lynx McCormick
    CSCI311 Systems Programming
    Homework 5
*/

#include <iostream>
#include <crypt.h> // encryption
#include <thread>
#include <string.h>
#include <cassert>
// #include <mutex>
#include <vector>

using namespace std;

const bool DEBUG_MODE = true;
const string encryptedPassword = "DBtH8T8yNcN0U";
const char CHARACTER_SET[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
const int MAX_CHARACTERS = 6;

class SearchSpaceT {
    public:
        SearchSpaceT(int start, int end);
        string BruteForcePassword();
    private:
        int startCharIndex;
        int endCharIndex;
};

int GetCmdLineArgs(int argc, char * argv[]);
string IntArrayToString(int indexArray[]);

int main(int argc, char * argv[]) {
    vector<thread> threads;
    int n = GetCmdLineArgs(argc, argv);
    int searchSize = 26 / n;
    int searchBegin = 0;
    int searchEnd = searchSize;
    SearchSpaceT searchSpace(searchBegin, searchEnd);

    // make threads
    for (int i = 0; i < n; i++) {
        thread t(&SearchSpaceT::BruteForcePassword, searchSpace); 
        threads.push_back(move(t));

        // make new search space
        searchBegin = searchEnd + 1;
        if (searchBegin + searchSize < 26) {
            searchEnd = searchBegin + searchSize;
        } else {
            searchEnd = 25;
        }
        searchSpace = SearchSpaceT(searchBegin, searchEnd);
    }

    for (int i = 0; i < n; i++) {
       threads[i].join();
    }

    return 0;
}

int GetCmdLineArgs(int argc, char * argv[]) {
    if (argc == 3 and !strcmp(argv[1], "-N")) {
        assert("Invalid command line argument given" && atoi(argv[2]) >= 1);
        return atoi(argv[2]);
    }
    cout << "Use command line argument -N <integer> to specify number of processes to create" << endl;
    exit(1);
}

string IntArrayToString(int indexArray[]) {
    string builtString;

    for (int i = 0; i < MAX_CHARACTERS; i++) {
        builtString = builtString + CHARACTER_SET[indexArray[i]];
    }

    return builtString;
}

SearchSpaceT::SearchSpaceT(int start, int end) {
    startCharIndex = start;
    endCharIndex = end;

    return;
}

string SearchSpaceT::BruteForcePassword() {
    int charIndexArray[MAX_CHARACTERS] = {startCharIndex, 0, 0, 0, 0, 0};
    string stringFromArray;
    string encryptedString;
    string salt = "DB";
    // int start = startCharIndex;
    crypt_data data;
    int i = MAX_CHARACTERS - 1;
    bool incremented;

    data.initialized = 0;

    while (charIndexArray[0] <= endCharIndex) {
        stringFromArray = IntArrayToString(charIndexArray);
        crypt_r(stringFromArray.c_str(), salt.c_str(), &data);
        encryptedString = data.output;

        if (encryptedString == encryptedPassword) {
            return stringFromArray;
        }
        
        // increment search
        if (charIndexArray[MAX_CHARACTERS - 1] == 25) {
            while (i >= 0 and !incremented) {
                if (charIndexArray[i] != 25) {
                    charIndexArray[i] += 1;
                    incremented = true;
                }
                i--;
            }
            // max search value reached
            if (!incremented) {
                charIndexArray[0] = endCharIndex + 1;
            }
        } else {
            charIndexArray[MAX_CHARACTERS - 1] += 1;
        }
    }

    return "";
}