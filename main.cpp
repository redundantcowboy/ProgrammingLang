/*
 * main.cpp
 *
 *  Created on: Oct 18, 2024
 *      Author: leannawalker1_snhu
 */
#include <iostream>   // For input and output
#include <fstream>    // For file handling (reading/writing files)
#include <map>        // To store items and their frequencies in a key-value pair
#include <string>     // For handling string types
#include <algorithm>  // For transforming strings (like converting to lowercase)
#include <cctype>     // For checking and converting characters to lowercase

// This class tracks the items and how many times they were bought
class ItemTracker {
private:
    // A map to store item names and their purchase frequencies
    std::map<std::string, int> itemFrequency;

public:
    // This function loads the item data from a file and stores them in lowercase
    void LoadItemData(const std::string& filename) {
        std::ifstream inputFile(filename);  // Open the file for reading
        std::string item;  // Variable to hold each item we read from the file

        // This loop reads every item from the file and adds it to the map
        while (inputFile >> item) {
            std::string lowerItem = ToLowerCase(item);  // Convert the item to lowercase
            itemFrequency[lowerItem]++;  // Increase the count for the lowercase item
        }

        inputFile.close();  // Close the file after we're done reading it
    }

    // This function converts any string to lowercase
    std::string ToLowerCase(const std::string& str) {
        std::string lowerStr = str;  // Make a copy of the input string
        std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        return lowerStr;  // Return the lowercase version of the string
    }

    // Function to find and display the frequency of a specific item
    void FindItemFrequency() {
        std::string itemName;
        std::cout << "Enter item name: ";  // Ask the user for the item name
        std::cin >> itemName;

        // Convert the input item name to lowercase
        std::string lowerItemName = ToLowerCase(itemName);

        // Check if the item exists in our map
        if (itemFrequency.find(lowerItemName) != itemFrequency.end()) {
            // If the item is found, display its frequency (how many times it was bought)
            std::cout << "Item: " << itemName << " | Frequency: " << itemFrequency[lowerItemName] << std::endl;
        } else {
            // If the item wasn't found in the map, let the user know
            std::cout << "Item not found!" << std::endl;
        }
    }

    // Function to print all items and their frequencies
    void PrintAllItems() {
        // Loop through every item in the map and print its name and count
        for (const auto& pair : itemFrequency) {
            std::cout << pair.first << " " << pair.second << std::endl;  // Print item and its frequency
        }
    }

    // Function to print a histogram of items
    void PrintHistogram() {
        // Loop through each item in the map
        for (const auto& pair : itemFrequency) {
            std::cout << pair.first << " ";  // Print the name of the item

            // Print a star (*) for each time the item was bought
            for (int i = 0; i < pair.second; ++i) {
                std::cout << "*";
            }
            std::cout << std::endl;  // Move to the next line after printing stars for an item
        }
    }

    // This function creates a backup file that saves the frequency of all items
    void CreateBackupFile(const std::string& filename) {
        std::ofstream backupFile(filename);  // Open a new file to write the backup data

        // Loop through every item in the map and write it to the file
        for (const auto& pair : itemFrequency) {
            backupFile << pair.first << " " << pair.second << std::endl;  // Write the item name and count
        }

        // Close the backup file after writing everything
        backupFile.close();
    }
};

// Function to validate user input for the menu
int GetValidatedChoice() {
    int choice;
    while (true) {  // Keep asking until the user enters a valid option
        std::cout << "Enter your choice (1-4): ";  // Ask the user for their choice
        std::cin >> choice;  // Read the input

        // Check if the input is valid: must be an integer between 1 and 4
        if (std::cin.fail() || choice < 1 || choice > 4) {
            std::cin.clear();  // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore invalid input
            std::cout << "Invalid input, please try again.\n";  // Let the user know the input was invalid
        } else {
            return choice;  // Return the valid choice
        }
    }
}

int main() {
    // Create an instance of the ItemTracker class, which will handle item-related operations
    ItemTracker tracker;

    // Load the item data from a file (this file contains the list of items bought throughout the day)
    tracker.LoadItemData("CS210_Project_Three_Input_File.txt");

    // Create a backup of the item frequencies in case we need to reference it later
    tracker.CreateBackupFile("frequency.dat");

    int choice;  // This will store the user's menu choice

    // Keep showing the menu until the user chooses to exit (choice 4)
    do {
        // Display the menu options
        std::cout << "\n1. Find item frequency\n2. Print all items\n3. Print histogram\n4. Exit\n";

        // Get a valid menu choice from the user
        choice = GetValidatedChoice();

        // Perform different actions based on the user's choice
        switch (choice) {
            case 1:
                tracker.FindItemFrequency();  // Find and display the frequency of a specific item
                break;
            case 2:
                tracker.PrintAllItems();  // Print all items and their frequencies
                break;
            case 3:
                tracker.PrintHistogram();  // Print a histogram of item frequencies
                break;
            case 4:
                std::cout << "Exiting...\n";  // Exit the program
                break;
        }
    } while (choice != 4);  // Keep running until the user chooses to exit (choice 4)

    return 0;  // End the program
}



