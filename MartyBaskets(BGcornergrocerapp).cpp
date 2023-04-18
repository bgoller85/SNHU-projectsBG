#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
using namespace std;

class Grocer {
public:
    int grocerMenu();
    int openFile();
    int choice = 0;

private:
    string item;
    int freq = 0;
    map<string, int> itemFreq;
};
int Grocer::grocerMenu() {
    do {
        cout << "----Corner Grocer Application----" << endl;
        cout << "1. Search for an item" << endl;
        cout << "2. Print item frequencies" << endl;
        cout << "3. Print item frequencies in histogram" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string searchItem;
            cout << "Enter item name: ";
            cin >> searchItem;

            if (itemFreq.count(searchItem) > 0) {
                cout << searchItem << " " << itemFreq[searchItem] << endl;
            }
            else {
                cout << "Item not found!" << endl;
            }
            break;
        }
        case 2: {
            for (auto&& item : itemFreq) {
                cout << item.first << " - " << item.second << endl;
            }
            break;
        }
        case 3: {
            for (auto&& item : itemFreq) {
                cout << item.first << " ";
                for (int i = 1; i <= item.second; i++) {
                    cout << "*";
                }
                cout << endl;
            }
            break;
        }
        case 4: {
            cout << "Exiting program..." << endl;
            break;
        }
        default: {
            cout << "Invalid choice! Try again." << endl;
        }
        }
    }
        while (choice != 4);
    ofstream outFS; // Output file stream

   // Open file
    outFS.open("frequency.dat");

    if (!outFS.is_open()) {
        cout << "Could not open file frequency.dat." << endl;
        return 1;
    }
    // Write to file
    for (auto&& item : itemFreq) {
        outFS << item.first << " - " << item.second << endl;
    }
    // Done with file, so close
    outFS.close();
}
int Grocer::openFile() {
    ifstream inputFile("CS210_Project_Three_Input_File.txt");
    if (!inputFile) {
        cout << "Error opening input file!" << endl;
        return 1;
    }

    string line, word;
    while (getline(inputFile, line)) {
        // process each line
        istringstream iss(line);
        while (iss >> word) {
            // process each word
            itemFreq[word]++;
        }
    }
}

int main() {
    //created object of Grocer as g
    Grocer g;

    g.openFile();
    g.grocerMenu();
    
    return 0;
}
