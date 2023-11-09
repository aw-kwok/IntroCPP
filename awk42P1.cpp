/*
* awk42P1.cpp
*
* COSC 1020 Fall 2023
* Project #1 Code
*
* Due on: 8 October 2023
* Author: awk42
*
* In accordance with class policies and Georgetown’s Honor Code,
* I certify that, with the exception of the class resources and those
* items noted below, I have neither given nor received any assistance
* on this project.
*
* Note that you may use without citation any help from our TAs,
* professors, or any code taken from the course textbook.
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() {
    // USER INPUTS
    char shirtType;
    string message;
    int medium, large, extraLarge;
    string color;
    string ink;

    // KNOWN VALUES
    double sSetup = 111.00;
    double iSetup = 0.00;
    double eSetup = 12.00;
    double sPerChar = 0.00;
    double iPerChar = 0.27;
    double ePerChar = 0.14;
    double mediumPerUnit = 3.15;
    double largePerUnit = 4.15;
    double extraLargePerUnit = 5.15;
    double sPerUnit = 1.59;
    double iPerUnit = 2.35;
    double ePerUnit = 7.99;
    double nonWhitePrice = 0.22;
    double discount144 = 0.045;
    double discount1440 = 0.095;
    int maxNumberOfShirts = 14400;
    string validColor[] = {"White", "white", "Green", "green", "Blue", "blue", "Yellow", "yellow", "Red", "red", "Black", "black"};
    int validColorLength = 12; // length of validColor[], c++ is weird with array lengths
    bool validColorBool = false;

    // INTERMEDIATE VALUES
    string printType;
    double setupPrice;
    double perCharPrice = 0;
    double perUnitPrice = 0;
    double totalPrintCost = 0;
    double totalShirtCost = 0;
    int totalShirtCount = 0;
    double subtotal;
    double discount = 0;
    double orderTotal;
    double discountAmount;

    cout << "Welcome to Sally's Awesome Shirts, Inc. (SASI)." << endl;

    // Printing type
    cout << "Please enter the type of printing you would like:" << endl;
    cout << "- Enter 'S' or 's' for silk-screen printing" << endl;
    cout << "- Enter 'I' or 'i' for iron-on printing" << endl;
    cout << "- Enter 'E' or 'e' for embroidered printing" << endl;
    cout << "Your selection: ";
    cin >> shirtType;
    cin.ignore(10000, '\n');

    // Based on printing type, set printType, setupPrice, and perUnitPrice
    switch (shirtType) {
        case 's':
        case 'S':
            printType = "silk-screen printing";
            setupPrice = sSetup;
            perUnitPrice = sPerUnit;
            break;
        case 'i':
        case 'I':
            printType = "iron-on printing";
            setupPrice = iSetup;
            perUnitPrice = iPerUnit;
            break;
        case 'e':
        case 'E':
            printType = "embroidered printing";
            setupPrice = eSetup;
            perUnitPrice = ePerUnit;
            break;
        default:
            cout << "You have selected an invalid type of printing." << endl;
            return -1;
    }
    cout << "You have selected " + printType + "." << endl << endl;
    totalPrintCost += setupPrice;

    // Message length costs
    cout << "Please enter the message you wish to print." << endl;
    cout << "- Messages may be empty, but must not be longer than 48 characters" << endl;
    cout << "Your message: ";
    getline(cin, message);
    if (message.length() > 48) {
        cout << "Your message is longer than 48 characters!" << endl;
        return -1;
    }
    cout << "Your message is \"" + message + "\"" << endl << endl;

    // Calculate per character price based on shirtType and multiply by message length (perCharPrice initialized to 0)
    switch (shirtType) {
        case 'i':
        case 'I':
            perCharPrice = iPerChar * message.length();
            break;
        case 'e':
        case 'E':
            perCharPrice = ePerChar * message.length();
            break;
    }
    perUnitPrice += perCharPrice;

    // T-shirt sizes
    cout << "Please enter the number of shirts you wish to print" << endl;
    cout << "- Enter three numbers separated by spaces" << endl;
    cout << "- These are the numbers of Medium, Large, and XL shirts to print" << endl;
    cout << "Number of shirts: ";
    cin >> medium;
    if (medium < 0 || medium > maxNumberOfShirts) {
        cout << "Your input for medium shirts is invalid!" << endl;
        return -1;
    }
    totalShirtCost += (medium * mediumPerUnit);
    cin >> large;
    if (large < 0 || large > maxNumberOfShirts) {
        cout << "Your input for large shirts is invalid!" << endl;
        return -1;
    }
    totalShirtCost += (large * largePerUnit);
    cin >> extraLarge;
    cin.ignore(10000, '\n');
    if (extraLarge < 0 || extraLarge > 14400) {
        cout << "Your input for XL shirts is invalid!" << endl;
        return -1;
    }
    totalShirtCost += (extraLarge * extraLargePerUnit);
    totalShirtCount = medium + large + extraLarge;
    if (totalShirtCount == 0) {
        cout << "You've entered an order for 0 shirts!" << endl;
        return -1;
    }
    if (totalShirtCount >= 1440) {
        discount = discount1440;
    }
    else if (totalShirtCount >= 144) {
        discount = discount144;
    }
    totalPrintCost += perUnitPrice * totalShirtCount;
    cout << endl;

    // Shirt color
    cout << "Please enter the shirt color you would like to print on" << endl;
    cout << " - Valid choices are \"white,\" \"green,\" \"blue,\" \"yellow,\" \"red,\" or \"black.\"" << endl;
    cout << "Shirt color: ";
    cin >> color; // data validation, only want one word so don't use getline()
    cin.ignore(10000, '\n');
    for (int i = 0; i < validColorLength; i++) {
        if (color == validColor[i]) {
            validColorBool = true;
            break;
        }
    }
    if (!validColorBool) {
        cout << "That is not a valid color!" << endl;
        return -1;
    }
    if (!(color == "white" || color == "White")) {
        totalShirtCost += (totalShirtCount * nonWhitePrice);
    }

    // Ink color
    cout << "Please enter the ink color you would like to print with" << endl;
    cout << "- Valid choices are \"white\" or \"black\"" << endl;
    cout << "- The ink color must be different from the shirt color you chose" << endl;
    cout << "Ink color: ";
    cin >> ink; // data validation, only want one word so don't use getline()
    cin.ignore(10000, '\n');
    if (!(ink == "Black" || ink == "black" || ink == "White" || ink == "white")) {
        cout << "Ink color invalid!" << endl;
        return -1;
    }
    else if ((color == "Black" || color == "black") && (ink == "Black" || ink == "black")) {
        cout << "Shirt color is the same as ink color!" << endl;
        return -1;
    }
    else if ((color == "White" || color == "white") && (ink == "White" || ink == "white")) {
        cout << "Shirt color is the same as ink color!" << endl;
        return -1;
    }
    cout << endl;
    subtotal = totalShirtCost + totalPrintCost;
    discountAmount = subtotal * discount;
    orderTotal = subtotal - discountAmount;

    cout << "Your order details:" << endl;
    cout << left << setw(23) << "- Printing Style: " << printType << endl;
    cout << left << setw(23) << "- Message: " << message << endl;
    cout << left << setw(23) << "- Number of M shirts: " << medium << endl;
    cout << left << setw(23) << "- Number of L shirts" << large << endl;
    cout << left << setw(23) << "- Number of XL shirts" << extraLarge << endl;
    cout << left << setw(23) << "- Shirt color: " << color << endl;
    cout << left << setw(23) << "- Ink color:  " << ink << endl << endl;

    cout << "Itemized order costs:" << endl;
    cout << left << setw(23) << "- Cost of printing: " << setw(5) << "$" << setw(12) << right << fixed << setprecision(5) << totalPrintCost << endl;
    cout << left << setw(23) << "- Cost of shirts: " << setw(5) << "$" << setw(12) << right << fixed << setprecision(5) << totalShirtCost << endl;
    cout << left << setw(23) << "Order Subtotal: " << setw(5) << "$" << setw(12) << right << fixed << setprecision(5) << subtotal << endl;
    cout << left << setw(23) << "Discount: " << setw(5) << "$" << setw(12) << right << fixed << setprecision(5) << discountAmount<< endl;
    cout << left << setw(23) << "Order Total: " << setw(5) << "$" << setw(12) << right << fixed << setprecision(5) << orderTotal << endl << endl;

    cout << "Thank you for ordering from Sally's Awesome Shirts, Inc (SASI) !" << endl;
    cout << "Goodbye!" << endl;
    return 0;
}