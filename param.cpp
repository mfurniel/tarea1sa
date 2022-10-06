#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main(int argv, char *argc[]) {
    map<string, string> param;
    param["-i"] = "100-300-001.txt";
    param["-t"] = "90";
    param["-th"] = "0.80";
    param["-det"] = "1";

    for (int i = 1; i < argv - 1; i += 2) {
        string aux = argc[i];
        param[aux] = argc[i + 1];
    }

    for (auto i = param.begin(); i != param.end(); i++) {
        cout << i->first << " " << i->second << endl;
    }

    cout << argv << endl;
}