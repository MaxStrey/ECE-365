#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

unordered_map<string, string> memory;

string checkMerge(const string &a, const string &b, const string &c) {
    
    if (a.empty() && b.empty() && c.empty()) {
        return "";
    }
    
    if ((a.empty() && b.empty() && !c.empty()) || 
        (a.empty() && !b.empty() && c.empty()) || 
        (!a.empty() && b.empty() && c.empty())) {
        return "*** NOT A MERGE ***";
    }

    string key = a + "|" + b + "|" + c;
    if (memory.find(key) != memory.end()) {
        return memory[key];
    }

    string merge = "*** NOT A MERGE ***";
    if (!a.empty() && a[0] == c[0]) {
        merge = checkMerge(a.substr(1), b, c.substr(1));
        if (merge != "*** NOT A MERGE ***") {
            merge = (char)toupper(c[0]) + merge;
        }
    }
    
    if (merge == "*** NOT A MERGE ***" && !b.empty() && b[0] == c[0]) {
        merge = checkMerge(a, b.substr(1), c.substr(1));
        if (merge != "*** NOT A MERGE ***") {
            merge = c[0] + merge;
        }
    }

    memory[key] = merge;
    return merge;
}

int main() {
    string infile, outfile, a, b, c;
    cout << "Enter name of input file: ";
    cin >> infile;
    ifstream input(infile);
    cout << "Enter name of output file: ";
    cin >> outfile;
    ofstream output(outfile);

    while (getline(input, a) && getline(input, b) && getline(input, c)) {
        output << checkMerge(a, b, c) << endl;
        memory.clear();  // Clear memory after each check to prevent incorrect memoization between different test cases
    }

    input.close();
    output.close();
    return 0;
}
