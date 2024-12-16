/*  ProjectThreeVillanueva.cpp
*   CS-210 
*   Project Three
*   Aiden Villanueva
*   Dec. 12, 2024
*/

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

// Function to read the input file and populate a map with item frequencies
void readFileToMap(string& filename, map<string, int>& itemFrequency) {
    // Load the file into an ifstream
    ifstream inputFile(filename);

    // Ensure input file opened correctly, get a new file name if not
    while (inputFile.fail()) {
        inputFile.clear();
        cerr << "Error: Unable to open file " << filename << endl;
        cout << "Please enter a new file name and extension (example.txt)" << endl;
        cin >> filename;
        ifstream inputFile(filename);
    }

    // Extract the file into the itemFrequency map
    string item;
    while (inputFile >> item) {
        itemFrequency[item]++;
    }

    inputFile.close();
}

// Function to write item frequencies to a backup file
void writeBackupFile(string& filename, const map<string, int>& itemFrequency) {
    // Create and open the backup file filename
    ofstream outputFile(filename);

    // Ensure file opened correctly and handle collecting a new file name if not
    while (!outputFile.is_open()) {
        outputFile.clear();
        cerr << "Error: Unable to open backup file " << filename << endl;
        cout << "Please enter a new file name and extension (example.dat)" << endl;
        cin >> filename;
        ofstream outputFile(filename);
    }

    // Print each pair in the map itemFrequency into a line in the file
    for (const auto& pair : itemFrequency) {
        outputFile << pair.first << " " << pair.second << endl;
    }

    outputFile.close();
}

// Function to display the frequency of a specific item
void displayItemFrequency(const map<string, int>& itemFrequency) {
    // Member variable for user's input for item name search
    string item;
    cout << "Enter the item name: ";
    cin >> item;

    // Search for item in itemFrequency and assign the first resulting map location pointer or itemFrequency.end() for no results
    auto itm = itemFrequency.find(item);
    // if itm exists in file, i.e itm is not the end() iterator
    if (itm != itemFrequency.end()) {
        // Print the name along with the occurance count(itm->second)
        cout << "\n" << item << " appears " << itm->second << " times." << endl;
    }
    else {
        cout << "\n" << item << " does not appear in the list." << endl;
    }
}

// Function to display all items and their frequencies
void displayAllFrequencies(const map<string, int>& itemFrequency) {
    // Print the header
    cout << "\n" << setw(15) << left << "Item" << "Frequency" << endl;
    cout << "---------------------------" << endl;
    // Print each map pair 
    for (const auto& pair : itemFrequency) {
        cout << setw(15) << left << pair.first << pair.second << endl;
    }
}

// Function to display a histogram of item frequencies
void displayHistogram(const map<string, int>& itemFrequency) {
    // Header
    cout << "\nHistogram of Items" << endl;
    cout << "------------------" << endl;
    // Print each pair, with the frequency int represented as repeated '*' for simple histogram
    for (const auto& pair : itemFrequency) {
        cout << setw(15) << left << pair.first << string(pair.second, '*') << endl;
    }
}

// Function to print main menu
void printMainMenu() {
    cout << "\nCorner Grocer - Item Tracking Program\n";
    cout << "1. Search for an item's frequency\n";
    cout << "2. Display all item frequencies\n";
    cout << "3. Display histogram of item frequencies\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

// Function to check user input for valid int range
bool validateUserInt(const int& choice) {
    // check for input type not equals int or choice less than 1 or greater than 4 (out of range)
    if (typeid(choice).name() != "int" || 0 <= choice <= 5) {
        cout << "Invalid input. Please enter a valid choice number.\n";
        return false;
    }
    else return true;
}

// Function to get user input and check validity
void getValidInput(int& choice) {
    cin >> choice;
    while (cin.fail()) {
        validateUserInt(choice);
        cin.clear();
        cin.ignore(1000, '\n');
        printMainMenu();
        cin >> choice;
    }
}


// Main entry point of the program
int main() {
// Initial Setup
    // Pre-setting the input and backup file names, this could become a prompt or file search as well
    string inputFilename = "CS210_Project_Three_Input_File.txt";
    string backupFilename = "frequency.dat";

    // central map for storing an item name to a quantity count
    map<string, int> itemFrequency;

    // Read input file and populate the frequency map
    readFileToMap(inputFilename, itemFrequency);

    // Backup the frequency data to a file
    writeBackupFile(backupFilename, itemFrequency);

    // int to store user input
    int choice;

    // do-while used for compact starting menu text operation
    do {
        printMainMenu();
        getValidInput(choice);

        // Switch for menu selections
        switch (choice) {
        case 1:
            displayItemFrequency(itemFrequency);
            break;
        case 2:
            displayAllFrequencies(itemFrequency);
            break;
        case 3:
            displayHistogram(itemFrequency);
            break;
        case 4:
            cout << "Exiting program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid input. Please enter a valid choice number.\n" << endl;
        }
    } while (choice != 4); // Choice '4' is the exit code

    return 0;
}