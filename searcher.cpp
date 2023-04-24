/*
    Lynx McCormick
    CSCI311 Systems Programming
    Homework 5
*/

#include <iostream>
#include <thread>

using namespace std;

const bool DEBUG_MODE = true;
const char CHARACTER_SET[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
const int MAX_CHARACTERS = 6;

struct SearchSpaceT {
    int startCharIndex;
    int endCharIndex;
};

int GetCmdLineArgs(int argc, char * argv[]);
string BruteForcePassword(SearchSpaceT search);

int main(int argc, char * argv[]) {
    int n = GetCmdLineArgs(argc, argv);

    return 0;
}

int GetCmdLineArgs(int argc, char * argv[]) {
    if (argc == 3 and !strcmp(argv[1], "-N")) {
        assert(atoi(argv[2]) >= 1);
        return atoi(argv[2]);
    }
    cout << "Use command line argument -N <integer> to specify number of processes to create" << endl;
    exit(1);
}

string BruteForcePassword(SearchSpaceT search) {

}