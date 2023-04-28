/*
    Lynx McCormick
    CSCI311 Systems Programming
    Homework 5
*/

#include <iostream>
#include <thread>
#include <cassert>
// #include <mutex>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cstring> // strcmp

#include "Globals.h"
#include "ClockT.h"
#include "SearchSpaceT.h"

using namespace std;

// mutex result_mutex;

int GetCmdLineArgs(int argc, char * argv[]);
void WriteResultToFile(std::string result, long int time);

int main(int argc, char * argv[]) {
    vector<thread> threads;
    vector<SearchSpaceT> searchSpaces;
    ClockT clock;
    int n = GetCmdLineArgs(argc, argv);
    int searchSize = CHARS_IN_SET / n;
    int searchBegin = 0;
    int searchEnd = searchSize;
    // SearchSpaceT searchSpace(0,0);
    std::string storeResult = "";

    clock.StartClock();
    // make threads
    for (int i = 0; i < n; i++) {
        searchSpaces.push_back(SearchSpaceT(searchBegin, searchEnd));
        thread t(&SearchSpaceT::BruteForcePassword, searchSpaces[i]); 
        threads.push_back(move(t));

        // make new search space
        searchBegin = searchEnd + 1;
        if (searchBegin + searchSize < CHARS_IN_SET) {
            searchEnd = searchBegin + searchSize;
        } else {
            searchEnd = CHARS_IN_SET - 1;
        }
    }

    for (int i = 0; i < n; i++) {
        threads[i].join();
    }

    for (int i = 0; i < n; i++) {
        if (DEBUG_MODE) {
            cout << "result " << i << " = " << searchSpaces[i].GetResult() << '\t';
        }
        if (searchSpaces[i].GetResult() != "") {
            storeResult = searchSpaces[i].GetResult();
        }
    }

    WriteResultToFile(storeResult, clock.EndClock());

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

void WriteResultToFile(std::string result, long int time) {
    assert(result != "");

    ofstream outFile("output.txt");
    float minutes = static_cast<float>(time) / 60;

    if (DEBUG_MODE) {
        cout << "--- RESULT: " << result << " ---" << endl;
    }
    outFile << result << '\n'
            << "Time taken in seconds: " << time << '\n'
            << "Time taken in minutes: " << setprecision(2) << minutes << endl;

    outFile.close();
    return;
}