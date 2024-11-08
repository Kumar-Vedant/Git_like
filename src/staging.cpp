#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "../include/repository.hpp"

namespace fs = std::filesystem;

using namespace std;
//creating an index file to store the file paths and their hash values
void createIndex() {
    // Create .gitlike/index if it doesn't exist
    fs::path indexPath = ".gitlike/index";
    if (!fs::exists(indexPath)) {
        ofstream indexFile(indexPath);
        if (!indexFile) {
            cerr << "Failed to create index file" << endl;
        }
        indexFile.close();
    }

}

void stageFile(string filePath) {
    // Hash the file's contents
    string fileHash = hashObject(filePath);  // Assume hashObject hashes the file content

    // Open the index file to store the file path and its hash
    fs::path indexPath = ".gitlike/index";
    ofstream indexFile(indexPath, ios::app);  // Open in append mode

    if (indexFile.is_open()) {
        indexFile << filePath << " " << fileHash << endl;
        indexFile.close();
        cout << "File " << filePath << " staged successfully." << endl;
    } else {
        cerr << "Failed to update index." << endl;
    }
}

void showStagedFiles() {
    fs::path indexPath = ".gitlike/index";
    ifstream indexFile(indexPath);

    if (indexFile.is_open()) {
        string line;
        while (getline(indexFile, line)) {
            cout << line << endl;
        }
        indexFile.close();
    } else {
        cerr << "Index file not found." << endl;
    }
}

void clearStagingArea() {
    fs::path indexPath = ".gitlike/index";
    ofstream indexFile(indexPath, ios::trunc);  // Truncate the index file
    indexFile.close();
    cout << "Staging area cleared." << endl;
}

//wrote the main function to create a repository and stage files
int main() {
    initializeRepo(".repo");
    createIndex();
    stageFile("file1.txt");
    stageFile("file2.txt");
    showStagedFiles();
    clearStagingArea();
    showStagedFiles();
    return 0;
}
