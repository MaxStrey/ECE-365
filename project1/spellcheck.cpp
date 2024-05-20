#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include "hash.h"  
#include <sstream>


using namespace std;

// Function to convert a string to lowercase (bit crude I know but it was the simplist)
void toLowerCase(string &str) {
    for (char &c : str) {
        c = tolower(c);
    }
}

// Function to parse words from a line of text
vector<string> parseWords(const string &line) {
    vector<string> words;
    string word;
    for (char c : line) {
        if (isalpha(c) || c == '-' || c == '\'') {  // Check if character is valid
            word.push_back(tolower(c));  // Convert to lowercase as per assignment specs
        } else if (!word.empty()) {
            words.push_back(word);
            word.clear();
        }
    }
    if (!word.empty()) {  // Push the last word if any
        words.push_back(word);
    }
    return words;
}

int main() {
    string dictionaryFile, documentFile, outputFile;
    cout << "Enter name of dictionary: ";
    cin >> dictionaryFile;

    hashTable hashTable;  

    clock_t start, end;  // declare start and end clock_t variables

    // Measure time taken to load dictionary
    start = clock();  // record start time
    ifstream dict(dictionaryFile);
    string word;
    while (getline(dict, word)) {
        toLowerCase(word);
        hashTable.insert(word);  
    }
    dict.close();
    end = clock();  // record end time
    double dictionaryLoadTime = double(end - start) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to load dictionary: " << dictionaryLoadTime << endl;

    cout << "Enter name of input file: ";
    cin >> documentFile;
    cout << "Enter name of output file: ";
    cin >> outputFile;

    ifstream doc(documentFile);
    if (!doc.is_open()) {
        cerr << "Could not open the document file." << endl;
        return -1;
    }
    ofstream out(outputFile);
    if (!out.is_open()) {
        cerr << "Could not open the output file." << endl;
        return -1;
    }

    // Measure time taken to check document
    start = clock();  // record start time
    string line;
    int lineNumber = 0;
    while (getline(doc, line)) {
        lineNumber++;
        vector<string> words = parseWords(line);
        for (const string &word : words) {
            if (word.length() > 20) {
                out << "Long word at line " << lineNumber << ", starts: " << word.substr(0, 20) << endl;
            } else if (any_of(word.begin(), word.end(), ::isdigit)) {
                // Skip words with digits
            } else if (!hashTable.contains(word)) {
                out << "Unknown word at line " << lineNumber << ": " << word << endl;
            }
        }
    }
    end = clock();  // record end time
    double documentCheckTime = double(end - start) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to check document: " << documentCheckTime << endl;

    doc.close();
    out.close();

    return 0;
}
