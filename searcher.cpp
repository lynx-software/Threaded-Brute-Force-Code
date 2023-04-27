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
#include <fstream>
// #include <sys/times.h>

using namespace std;

const bool DEBUG_MODE = true;
// const string encryptedPassword = "DBtH8T8yNcN0U";
const string encryptedPassword = "DBDLjTPhWLYM2";
const int CHARS_IN_SET = 26;
const char CHARACTER_SET[CHARS_IN_SET] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
// const int MAX_CHARACTERS = 6;
const int MAX_CHARACTERS = 5;

string result = "";
// mutex result_mutex;

class SearchSpaceT {
    public:
        SearchSpaceT(int start, int end);
        void BruteForcePassword();
        void IncrementArray(int (&array)[MAX_CHARACTERS]);
    private:
        int startCharIndex;
        int endCharIndex;
};

// class ClockT {
//     public:
//         ClockT();
//         ~ClockT();
//     private:
// };

int GetCmdLineArgs(int argc, char * argv[]);
string IntArrayToString(int indexArray[]);
void WriteResultToFile();

int main(int argc, char * argv[]) {
    vector<thread> threads;
    int n = GetCmdLineArgs(argc, argv);
    int searchSize = CHARS_IN_SET / n;
    int searchBegin = 0;
    int searchEnd = searchSize;
    SearchSpaceT searchSpace(searchBegin, searchEnd);

    // make threads
    for (int i = 0; i < n; i++) {
        thread t(&SearchSpaceT::BruteForcePassword, searchSpace); 
        threads.push_back(move(t));

        // make new search space
        searchBegin = searchEnd + 1;
        if (searchBegin + searchSize < CHARS_IN_SET) {
            searchEnd = searchBegin + searchSize;
        } else {
            searchEnd = CHARS_IN_SET - 1;
        }
        searchSpace = SearchSpaceT(searchBegin, searchEnd);
    }

    for (int i = 0; i < n; i++) {
       threads[i].join();
    }

    WriteResultToFile();

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

void WriteResultToFile() {
    assert(result != "");

    ofstream outFile("output.txt");

    if (DEBUG_MODE) {
        cout << "--- RESULT: " << result << " ---" << endl;
    }
    outFile << result << '\n';

    outFile.close();
    return;
}