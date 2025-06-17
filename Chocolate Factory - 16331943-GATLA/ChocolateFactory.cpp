//Name = Meher Sasmmith Kaligatla
//Program = Chocolate Factory



/*
 * Chocolate Factory Inventory Management System
 *
 * This program helps manage a warehouse chocolate inventory with three types:
 * - Large (5 lb bars)
 * - Medium (3 lb bars)
 * - Small (1 lb bars)
 */

#include <iostream>
#include <iomanip>  // For formatting output
#include <string>   // For string handling
#include <cctype>   // For toupper()

using namespace std;

// Constants for pricing and tax
const double LARGE_PRICE = 41.25;   // Price per large bar
const double MEDIUM_PRICE = 25.80;  // Price per medium bar
const double SMALL_PRICE = 13.50;   // Price per small bar
const double TAX_RATE = 0.072;      // 7.2% sales tax

// Function prototypes
char printMenu();
void printInventory(int l, int m, int s);
void fillOrder(int& l, int& m, int& s, int& o);
void orderInventory(int& l, int& m, int& s);
float shippingCost(int o);
void printReceipt(int l, int m, int s, int order, int o);

int main() {
    // Initialize inventory counts
    int largeCt = 1500;   // Starting large bars
    int medCt = 1200;     // Starting medium bars
    int smallCt = 7000;   // Starting small bars
    int orderNum = 1;     // Starting order number

    // Main program loop
    char choice = printMenu();
    while (choice != 'E') {
        switch (choice) {
        case 'F':  // Fill order
            fillOrder(largeCt, medCt, smallCt, orderNum);
            break;
        case 'P':  // Print inventory
            printInventory(largeCt, medCt, smallCt);
            break;
        case 'O':  // Order more inventory
            orderInventory(largeCt, medCt, smallCt);
            break;
        default:   // Invalid choice
            cout << "WARNING: " << choice << " is an invalid choice. Command ignored\n\n\n";
            break;
        }
        choice = printMenu();  // Showing menu again (loop)
    }

    // Exit message
    cout << "Thank you for using my program!";
    return 0;
}

// Displays the main menu and gets user choice
char printMenu() {
    char choice;
    cout << "\nChocolate Inventory System\n";
    cout << "F: Fill Order\n";
    cout << "P: Print Inventory\n";
    cout << "O: Order Inventory\n";
    cout << "E: Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    choice = toupper(choice);  // Convert to uppercase

    // Validate input
    while (choice != 'F' && choice != 'P' && choice != 'O' && choice != 'E') {
        cout << "Invalid choice. Please try again\n";
        cout << "Enter your choice: ";
        cin >> choice;
        choice = toupper(choice);
    }
    return choice;
}

// Prints current inventory levels
void printInventory(int l, int m, int s) {
    cout << "\nCurrent Inventory:\n";
    cout << "Large Bars (5 lb): " << l << endl;
    cout << "Medium Bars (3 lb): " << m << endl;
    cout << "Small Bars (1 lb): " << s << endl;
    cout << "Total pounds available: "
        << (l * 5 + m * 3 + s) << "\n\n";
}

// Processes a customer order
void fillOrder(int& l, int& m, int& s, int& o) {
    int pounds;
    cout << "\nEnter pounds needed: ";
    cin >> pounds;

    // Calculate how many bars of each type to use
    int largeUsed = pounds / 5;       // Max large bars we can use
    if (largeUsed > l) largeUsed = l; // Don't exceed inventory
    int remaining = pounds - largeUsed * 5;

    int mediumUsed = remaining / 3;   // Then medium bars
    if (mediumUsed > m) mediumUsed = m;
    remaining = remaining - mediumUsed * 3;

    int smallUsed = remaining;        // Finally small bars

    // Check if we can fulfill the order
    if (smallUsed > s) {
        int shortBy = (largeUsed * 5 + mediumUsed * 3 + smallUsed) - pounds;
        cout << "WARNING: Can't fulfill order. Short by "
            << shortBy << " pounds.\n\n";
    }
    else {
        // Update inventory
        l -= largeUsed;
        m -= mediumUsed;
        s -= smallUsed;

        // Generate receipt
        printReceipt(largeUsed, mediumUsed, smallUsed, pounds, o);
        o++;  // Increment order number
    }
}

// Prints a detailed receipt
void printReceipt(int l, int m, int s, int order, int o) {
    // Set up decimal formatting
    cout << fixed << setprecision(2);

    // Calculate costs
    double largeCost = l * LARGE_PRICE;
    double mediumCost = m * MEDIUM_PRICE;
    double smallCost = s * SMALL_PRICE;
    double subtotal = largeCost + mediumCost + smallCost;
    double tax = subtotal * TAX_RATE;
    double shipping = shippingCost(order);
    double total = subtotal + tax + shipping;

    // Print receipt header
    cout << "\nChocolate Order #" << o << endl;
    cout << "--------------------------------\n";

    // Print bar details
    cout << left << setw(12) << "Bar Type" << setw(8) << "Count"
        << setw(10) << "Pounds" << "Cost\n";
    cout << setw(12) << "Large" << setw(8) << l
        << setw(10) << l * 5 << "$" << largeCost << endl;
    cout << setw(12) << "Medium" << setw(8) << m
        << setw(10) << m * 3 << "$" << mediumCost << endl;
    cout << setw(12) << "Small" << setw(8) << s
        << setw(10) << s << "$" << smallCost << endl;

    // Print totals
    cout << "--------------------------------\n";
    cout << setw(22) << "Subtotal:" << "$" << subtotal << endl;
    cout << setw(22) << "Tax (7.2%):" << "$" << tax << endl;
    cout << setw(22) << "Shipping:" << "$" << shipping << endl;
    cout << setw(22) << "Total:" << "$" << total << "\n\n";
}

// Calculates shipping cost based on weight
float shippingCost(int pounds) {
    if (pounds <= 10) return 8.25;
    else if (pounds <= 20) return 12.75;
    else if (pounds <= 50) return 15.25;
    else return 19.75;
}

// Handles adding more inventory
void orderInventory(int& l, int& m, int& s) {
    char type;
    int amount;

    cout << "\nEnter bar type (L/M/S): ";
    cin >> type;
    type = toupper(type);

    cout << "Enter quantity to add: ";
    cin >> amount;

    switch (type) {
    case 'L':
        l += amount;
        cout << "Added " << amount << " large bars. New total: " << l << "\n";
        break;
    case 'M':
        m += amount;
        cout << "Added " << amount << " medium bars. New total: " << m << "\n";
        break;
    case 'S':
        s += amount;
        cout << "Added " << amount << " small bars. New total: " << s << "\n";
        break;
    default:
        cout << "Invalid bar type. No changes made.\n";
    }
}