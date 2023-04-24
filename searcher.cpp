/*
    Lynx McCormick
    CSCI311 Systems Programming
    Homework 5
*/

#include <iostream>
#include <crypt.h> // encryption
// #include <thread>

using namespace std;

const bool DEBUG_MODE = true;
const string encryptedPassword = "DBtH8T8yNcN0U";
const char CHARACTER_SET[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
const int MAX_CHARACTERS = 6;

struct SearchSpaceT {
    int startCharIndex;
    int endCharIndex;
};

int GetCmdLineArgs(int argc, char * argv[]);
string IntArrayToString(int indexArray[]);
string BruteForcePassword(SearchSpaceT search);

int main(int argc, char * argv[]) {
    int n = GetCmdLineArgs(argc, argv);

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

string BruteForcePassword(SearchSpaceT search) {
    int charIndexArray[MAX_CHARACTERS] = {search.startCharIndex, 0, 0, 0, 0, 0};
    string stringFromArray;
    string encryptedString;
    string salt = "DB";
    crypt_data data;

    while (charIndexArray[0] <= search.endCharIndex) {
        stringFromArray = IntArrayToString(charIndexArray);
        encryptedString = crypt_r(stringFromArray.c_str(), salt.c_str(), data);
        if (encryptedString == encryptedPassword) {
            return stringFromArray;
        }
    }
    return "";
}