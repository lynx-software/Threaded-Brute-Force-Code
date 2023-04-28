/*
    Lynx McCormick
    CSCI311 Systems Programming
    Homework 5
*/

#include <iostream>
#include <thread>
#include <string.h>
#include <cassert>
// #include <mutex>
#include <vector>
#include <fstream>
#include <iomanip>
// #include <sys/times.h>

#include "SearchSpaceT.h"
#include "ClockT.h"

using namespace std;

int GetCmdLineArgs(int argc, char * argv[]);
void WriteResultToFile(long int time);

int main(int argc, char * argv[]) {
    vector<thread> threads;
    int n = GetCmdLineArgs(argc, argv);
    int searchSize = CHARS_IN_SET / n;
    int searchBegin = 0;
    int searchEnd = searchSize;
    SearchSpaceT searchSpace(searchBegin, searchEnd);
    ClockT clock;
    clock.StartClock();

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

    WriteResultToFile(clock.EndClock());

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

void WriteResultToFile(long int time) {
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