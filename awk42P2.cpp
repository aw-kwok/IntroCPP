/*
* awk42P2.cpp
*
* COSC 1020 Fall 2023
* Project #1 Code
*
* Due on: 20 October 2023
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
#include <fstream>

using namespace std;

int main() {
    // USER INPUTS
    string filePath;

    // KNOWN VALUES
    double sSetup = 111.00;
    double iSetup = 0.00;
    double eSetup = 12.00;
    double nSetup = 0.00;
    double sPerChar = 0.00;
    double iPerChar = 0.27;
    double ePerChar = 0.14;
    double mediumPerUnit = 3.15;
    double largePerUnit = 4.15;
    double extraLargePerUnit = 5.15;
    double sPerUnit = 1.59;
    double iPerUnit = 2.35;
    double ePerUnit = 7.99;
    double nPerUnit = 0.00;
    double nonWhitePrice = 0.22;
    double discount144 = 0.045;
    double discount1440 = 0.095;
    int maxNumberOfShirts = 14400;
    string validColor[] = {"White", "Green", "Blue", "Yellow", "Red", "Black"};
    int validColorLength = 6; // length of validColor[], c++ is weird with array lengths
    bool validColorBool = false;

    // INTERMEDIATE VALUES
    ifstream inputFile;
    char shirtType;
    string message;
    int medium, large, extraLarge;
    string color;
    string ink;
    double setupPrice = 0; // Initialize to 0 so compile-time error not thrown
    double perCharPrice = 0;
    double perUnitPrice = 0;
    double totalPrintCost = 0;
    double totalShirtCost = 0;
    int totalShirtCount = 0;
    double subtotal;
    double discount = 0;
    double orderTotal;
    double discountAmount;
    string s;
    string date;
    int numDate;
    string errorMessage;
    bool validOrder;
    string inputLine;
    string custNameAndEmail;
    int index = 0;
    int goodRecords = 0;
    int badRecords = 0;
    double sShirtTotal = 0;
    double iShirtTotal = 0;
    double eShirtTotal = 0;
    double nShirtTotal = 0;
    double sPrintTotal = 0;
    double iPrintTotal = 0;
    double ePrintTotal = 0;
    double nPrintTotal = 0;
    double sFinalCost = 0;
    double iFinalCost = 0;
    double eFinalCost = 0;
    double nFinalCost = 0;

    cout << "Welcome to Sally's Awesome Shirts, Inc. (SASI) custom ordering program." << endl;
    cout << "Please enter the name and full path to the input data file: ";
    cin >> filePath;

    inputFile.open(filePath);
    
    // Open check
    if (inputFile.fail()) {
        cout << "File failed to open." << endl;
        return -1;
    }
    // Ignore first line
    getline(inputFile, inputLine);

    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << setw(10) << "order" << " " <<setw(2) << left << "p" << setw(25) << left << "5 chars" << setw(5) << right << "msg" << setw(18) << right << "SIZES     " << setw(20) << right << "COLORS    " << setw(20) << "final" << endl;
    cout << setw(10) << "date" << " " << setw(2) << left << "m" << setw(25) << left << "of msg" << setw(5) << right << "len" << setw(6) << right << "M" << setw(6) << right << "L" << setw(6) << right << "XL" << setw(10) << right << "shirt" << setw(10) << right << "ink" << setw(20) << "cost" << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    
    while (getline(inputFile, inputLine)) {
        validOrder = true;
        index = 0;
        date = inputLine.substr(0, 10);
        index = inputLine.find_first_not_of(' ', inputLine.find(' ', index));
        shirtType = inputLine[index];
        index = inputLine.find('"', index);
        index++;
        message = inputLine.substr(index, inputLine.find('"', index) - index);
        index = inputLine.find_first_not_of(' ', inputLine.find(' ', inputLine.find('"', index)));
        medium = stoi(inputLine.substr(index, inputLine.find(' ', index) - index));
        index = inputLine.find_first_not_of(' ', inputLine.find(' ', index));
        large = stoi(inputLine.substr(index, inputLine.find(' ', index) - index));
        index = inputLine.find_first_not_of(' ', inputLine.find(' ', index));
        extraLarge = stoi(inputLine.substr(index, inputLine.find(' ', index) - index));
        index = inputLine.find_first_not_of(' ', inputLine.find(' ', index));
        color = inputLine.substr(index, inputLine.find(' ', index) - index);
        index = inputLine.find_first_not_of(' ', inputLine.find(' ', index));
        ink = inputLine.substr(index, inputLine.find(' ', index) - index);
        index = inputLine.find_first_not_of(' ', inputLine.find(' ', index));
        custNameAndEmail = inputLine.substr(index);

        cout << endl << setw(10) << date << " " << setw(2) << left << shirtType << setw(23) << left << "\"" + message.substr(0,5) +  "..." << setw(3) << left << "\"" << setw(5) << right << message.length() << setw(6) << right << medium << setw(6) << right << large << setw(6) << right << extraLarge << setw(10) << right << color << setw(10) << right << ink;
        
        //clear intermediate values
        totalShirtCost = 0;
        totalPrintCost = 0;
        totalShirtCount = 0;
        perCharPrice = 0;
        discount = 0;
        validColorBool = false;

        //date validation
        numDate = stoi(date.substr(5,2));
        if (numDate < 4) {
            validOrder = false;
            cout << endl << "\t" << "ERROR !!! " << "date " << date << " is an expired/invalid order";
        }

        //shirtType
        switch (shirtType) {
        case 's':
        case 'S':
            setupPrice = sSetup;
            perUnitPrice = sPerUnit;
            break;
        case 'i':
        case 'I':
            setupPrice = iSetup;
            perUnitPrice = iPerUnit;
            break;
        case 'e':
        case 'E':
            setupPrice = eSetup;
            perUnitPrice = ePerUnit;
            break;
        case 'n':
        case 'N':
            setupPrice = nSetup;
            perUnitPrice = nPerUnit;
            break;
        default:
            validOrder = false;
            cout << endl << "\t" << "ERROR !!! " << "invalid print method";
            break;
        }
        totalPrintCost += setupPrice; //calculate anyways, regardless of error, if error will be thrown out anyways

        // Message length costs
        if ((shirtType == 'n' || shirtType == 'N') && message.length() != 0) {
            validOrder = false;
            cout << endl << "\t" << "ERROR !!! " << "print method of None, must also have empty string for message";
        }
        if (!(shirtType == 'n' || shirtType == 'N') && message.length() == 0) {
            validOrder = false;
            cout << endl << "\t" << "ERROR !!! " << "non-None print method, must not have empty string for message";
        }
        if (message.length() > 48) {
            validOrder = false;
            cout << endl << "\t" << "ERROR !!! " << "The message is longer than the allowed length of 49.  [ " << message.length() << " ]";
        }
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

        // Shirt color
        for (int i = 0; i < validColorLength; i++) {
            if (color == validColor[i]) {
                validColorBool = true;
                break;
            }
        }
        if (!validColorBool) {
            validOrder = false;
            cout << endl << "\t" << "ERROR !!! " << "invalid shirt color";
        }

        // Ink color
        if (!(ink == "Black" || ink == "White" || ink == "None")) {
            validOrder = false;
            cout << endl << "\t" << "ERROR !!! " << "invalid ink color";
        }
        else if ((color == "Black" && ink == "Black") || (color == "White" && ink == "White")) {
            validOrder = false;
            cout << endl << "\t" << "ERROR !!! " << ink << " print on a " << color << " shirt is not a valid color combination";
        }
        else if ((shirtType == 'n' || shirtType == 'N') && (ink != "None")) {
            validOrder = false;
            cout << endl << "\t" << "ERROR !!! " << "print method of None, must also have ink color None";
        }
                // T-shirt sizes
        // Medium
        if (medium < 0) {
            validOrder = false;
            cout << endl << "\t" << "ERROR !!! " << "medium shirt count must be greater than 0";
        }
        else if (medium > maxNumberOfShirts) {
            validOrder = false;
            cout << endl << "\t" << "ERROR !!! " << medium << " medium shirts exceeds the maximum count for any size of " << maxNumberOfShirts;
        }
        else {
            totalShirtCost += (medium * mediumPerUnit);
        }
        // Large
        if (large < 0) {
            validOrder = false;
            cout << endl << "\t" << "ERROR !!! " << "large shirt count must be greater than 0";
        }
        else if (large > maxNumberOfShirts) {
            validOrder = false;
            cout << endl << "\t" << "ERROR !!! " << large << " large shirts exceeds the maximum count for any size of " << maxNumberOfShirts;
        }
        else {
            totalShirtCost += (large * largePerUnit);
        }
        // Extra Large
        if (extraLarge < 0) {
            validOrder = false;
            cout << endl << "\t" << "ERROR !!! " << "extra large shirt count must be greater than 0";
        }
        else if (extraLarge > maxNumberOfShirts) {
            validOrder = false;
            cout << endl << "\t" << "ERROR !!! " << extraLarge << " extra large shirts exceeds the maximum count for any size of " << maxNumberOfShirts;
        }
        else {
            totalShirtCost += (extraLarge * extraLargePerUnit);
        }
        totalShirtCount = medium + large + extraLarge;
        if (totalShirtCount == 0) {
            validOrder = false;
            cout << endl << "\t" << "ERROR !!! " << "invalid order of 0 shirts";
        }
        if (color != "White") {
            totalShirtCost += (totalShirtCount * nonWhitePrice);
        }
        if (totalShirtCount >= 1440) {
            discount = discount1440;
        }
        else if (totalShirtCount >= 144) {
            discount = discount144;
        }
        totalPrintCost += perUnitPrice * totalShirtCount;
        if (validOrder) {
            subtotal = totalShirtCost + totalPrintCost;
            discountAmount = subtotal * discount;
            orderTotal = subtotal - discountAmount;
            cout << setw(4) << right << "$" << setw(16) << fixed << setprecision(5) << right << orderTotal;
            goodRecords++;
            switch (shirtType) {
                case 's':
                case 'S':
                    sShirtTotal += totalShirtCost;
                    sPrintTotal += totalPrintCost;
                    sFinalCost += orderTotal;
                    break;
                case 'i':
                case 'I':
                    iShirtTotal += totalShirtCost;
                    iPrintTotal += totalPrintCost;
                    iFinalCost += orderTotal;
                    break;
                case 'e':
                case 'E':
                    eShirtTotal += totalShirtCost;
                    ePrintTotal += totalPrintCost;
                    eFinalCost += orderTotal;
                    break;
                case 'n':
                case 'N':
                    nShirtTotal += totalShirtCost;
                    nPrintTotal += totalPrintCost;
                    nFinalCost += orderTotal;
                    break;
            }    
        }
        else {
            cout << endl << "\t" << "To fix this line, please contact .. " << custNameAndEmail;
            badRecords++;
        }
    }
    cout << endl << endl << "good records = " << goodRecords << ", bad records = " << badRecords << endl << endl;

    // final table
    cout << setw(20) << right << "print method" << setw(20) << right << "blank shirt" << setw(20) << right << "printing" << setw(20) << right << "final cost" << endl;
    cout << setw(20) << right << "silk screen" << setw(20) << right << fixed << setprecision(5) << sShirtTotal << setw(20) << right << fixed << setprecision(5) << sPrintTotal << setw(20) << right << fixed << setprecision(5) << sFinalCost << endl;
    cout << setw(20) << right << "iron-on" << setw(20) << right << fixed << setprecision(5) << iShirtTotal << setw(20) << right << fixed << setprecision(5) << iPrintTotal << setw(20) << right << fixed << setprecision(5) << iFinalCost << endl;
    cout << setw(20) << right << "embroider" << setw(20) << right << fixed << setprecision(5) << eShirtTotal << setw(20) << right << fixed << setprecision(5) << ePrintTotal << setw(20) << right << fixed << setprecision(5) << eFinalCost << endl;
    cout << setw(20) << right << "none" << setw(20) << right << fixed << setprecision(5) << nShirtTotal << setw(20) << right << fixed << setprecision(5) << nPrintTotal << setw(20) << right << fixed << setprecision(5) << nFinalCost << endl;

    cout << endl << "Thank you for ordering from Sally's Awesome Shirts, Inc. (SASI) custom ordering program." << endl;

    inputFile.close();
    return 0;
}
