#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void compressRLE(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename, ios::binary);
    ofstream outputFile(outputFilename, ios::binary);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Error opening file(s)." << endl;
        return;
    }

    char currentChar, previousChar;
    int count = 0;

    while (inputFile.get(currentChar)) {
        if (currentChar == previousChar) {
            count++;
        } else {
            if (count > 0) {
                outputFile << previousChar << count;
            }
            previousChar = currentChar;
            count = 1;
        }
    }

    if (count > 0) {
        outputFile << previousChar << count;
    }

    inputFile.close();
    outputFile.close();
}

void decompressRLE(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename, ios::binary);
    ofstream outputFile(outputFilename, ios::binary);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Error opening file(s)." << endl;
        return;
    }

    char currentChar;
    stringstream countStream;

    while (inputFile.get(currentChar)) {
        if (isdigit(currentChar)) {
            countStream << currentChar;
        } else {
            int count;
            countStream >> count;
            countStream.str("");
            countStream.clear();

            for (int i = 0; i < count; ++i) {
                outputFile << currentChar;
            }
        }
    }

    inputFile.close();
    outputFile.close();
}

int main() {
    int choice;
    string inputFilename, outputFilename;

    cout << "File Compression Tool" << endl;
    cout << "1. Compress File" << endl;
    cout << "2. Decompress File" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
        case 1:
            cout << "Enter input file name: ";
            getline(cin, inputFilename);
            cout << "Enter output file name: ";
            getline(cin, outputFilename);
            compressRLE(inputFilename, outputFilename);
            cout << "File compressed successfully!" << endl;
            break;
        case 2:
            cout << "Enter input file name: ";
            getline(cin, inputFilename);
            cout << "Enter output file name: ";
            getline(cin, outputFilename);
            decompressRLE(inputFilename, outputFilename);
            cout << "File decompressed successfully!" << endl;
            break;
        case 3:
            cout << "Exiting..." << endl;
            return 0;
        default:
            cout << "Invalid choice!" << endl;
    }

    return 0;
}
