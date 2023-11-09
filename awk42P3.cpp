/*
* awk42P3.cpp
*
* COSC 1020 Fall 2023
* Project #3 Code
*
* Due on: 5 November 2023
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
#include <vector>

using namespace std;

// global variables
const double sSetup = 111.00;
const double iSetup = 0.00;
const double eSetup = 12.00;
const double nSetup = 0.00;
const double sPerChar = 0.00;
const double iPerChar = 0.27;
const double ePerChar = 0.14;
const double mediumPerUnit = 3.15;
const double largePerUnit = 4.15;
const double extraLargePerUnit = 5.15;
const double sPerUnit = 1.59;
const double iPerUnit = 2.35;
const double ePerUnit = 7.99;
const double nPerUnit = 0.00;
const double nonWhitePrice = 0.22;
const double discount144 = 0.045;
const double discount1440 = 0.095;
const int maxNumberOfShirts = 14400;
const string validColor[] = {"White", "Green", "Blue", "Yellow", "Red", "Black"};
const int validColorLength = 6; // length of validColor[], c++ is weird with array lengths

char displayMenu();
bool uploadFile (string fileName, vector<string>& region, vector<int>& yyyy, vector<int>& mm, vector<int>& dd, vector<char>& printMethod, vector<string>& message, vector<int>& m, vector<int>& l, vector<int>& xl, vector<string>& shirtColor, vector<string>& inkColor, vector<string>& contact);
double calculateShirtTotal(const int m, const int l, const int xl, const string shirtColor);
double calculatePrintTotal(const char printMethod, const string message, const int m, const int l, const int xl, const string shirtColor, const string inkColor);
double calculateCost(char printMethod, string message, int m, int l, int xl, string shirtColor, string inkColor);
void allDetails (const vector<string>& region, const vector<int>& yyyy, const vector<int>& mm, const vector<int>& dd, const vector<char>& printMethod, const vector<string>& message, const vector<int>& m, const vector<int>& l, const vector<int>& xl, const vector<string>& shirtColor, const vector<string>& inkColor, const vector<string>& contact);
void summaryByMethod(const vector<string>& region, const vector<int>& yyyy, const vector<int>& mm, const vector<int>& dd, const vector<char>& printMethod, const vector<string>& message, const vector<int>& m, const vector<int>& l, const vector<int>& xl, const vector<string>& shirtColor, const vector<string>& inkColor, const vector<string>& contact);
void clearAll (vector<string>& region, vector<int>& yyyy, vector<int>& mm, vector<int>& dd, vector<char>& printMethod, vector<string>& message, vector<int>& m, vector<int>& l, vector<int>& xl, vector<string>& shirtColor, vector<string>& inkColor, vector<string>& contact);

int main() {
    vector<string> region;
    vector<int> yyyy, mm , dd;
    vector<char> printMethod;
    vector<string> message;
    vector<int> m, l, xl;
    vector<string> shirtColor, inkColor, contact;
    char menu;
    string fileName;

    cout << "Welcome to Sally's Awesome Shirts, Inc. (SASI) custom ordering program." << endl;

    do {
        menu = displayMenu();
        //menu functions
        switch (menu) {
            case 'u':
            case 'U':
                cout << endl << "Please enter the name and full path to the input data file: ";
                cin >> fileName;
                uploadFile(fileName, region, yyyy, mm, dd, printMethod, message, m, l, xl, shirtColor, inkColor, contact);
                break;
            case 'a':
            case 'A':
                allDetails(region, yyyy, mm, dd, printMethod, message, m, l, xl, shirtColor, inkColor, contact);
                break;
            case 'm':
            case 'M':
                summaryByMethod(region, yyyy, mm, dd, printMethod, message, m, l, xl, shirtColor, inkColor, contact);
                break;
            case 'c':
            case 'C':
                clearAll(region, yyyy, mm, dd, printMethod, message, m, l, xl, shirtColor, inkColor, contact);
                break;
        }
    } while (menu != 'q' && menu != 'Q');
    cout << endl << "Thank you for ordering from Sally's Awesome Shirts, Inc. (SASI) custom ordering program." << endl;
    return 0;
}

char displayMenu() {
    char choice;
    cout << endl << "Please select from the following user options:" << endl;
    cout << "\t" << " - (U) Upload a regional sales data file" << endl;
    cout << "\t" << " - (A) display All loaded data details" << endl;
    cout << "\t" << " - (M) display a summary by print Method" << endl;
    cout << "\t" << " - (C) Clear all data" << endl;
    cout << "\t" << " - (Q) Quit" << endl;
    cin >> choice;
    cin.ignore(10000, '\n');
    return choice;
}

bool uploadFile (string fileName, vector<string>& region, vector<int>& yyyy, vector<int>& mm, vector<int>& dd, vector<char>& printMethod, vector<string>& message, vector<int>& m, vector<int>& l, vector<int>& xl, vector<string>& shirtColor, vector<string>& inkColor, vector<string>& contact) {
    // INTERMEDIATE VALUES
    ifstream inputFile;
    char shirtType;
    string inputMessage;
    int medium, large, extraLarge;
    string color;
    string ink;
    string s;
    string date;
    int year;
    int month;
    int day;
    int numDate;
    string errorMessage;
    bool validColorBool = false;
    bool validOrder;
    bool nonWhitespaceMessage;
    string inputLine;
    string custNameAndEmail;
    double orderTotal;
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
    string fileRegion;
    bool oneValid = false;
    

    inputFile.open(fileName);
    
    // Open check
    if (inputFile.fail()) {
        cout << "File failed to open." << endl;
        return false;
    }
    else {
         // set region
        if (fileName.find("North", 0) != string::npos) {
            fileRegion = "North";
        }
        else if (fileName.find("South", 0) != string::npos) {
            fileRegion = "South";
        }
        else if (fileName.find("East", 0) != string::npos) {
            fileRegion = "East";
        }
        else if (fileName.find("West", 0) != string::npos) {
            fileRegion = "West";
        }
        else {
            fileRegion = "Other";
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
            inputMessage = inputLine.substr(index, inputLine.find('"', index) - index);
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

            cout << endl << setw(10) << date << " " << setw(2) << left << shirtType << setw(23) << left << "\"" + inputMessage.substr(0,5) +  "..." << setw(3) << left << "\"" << setw(5) << right << inputMessage.length() << setw(6) << right << medium << setw(6) << right << large << setw(6) << right << extraLarge << setw(10) << right << color << setw(10) << right << ink;
            
            //clear intermediate values
            validColorBool = false;
            nonWhitespaceMessage = false;

            //date validation
            month = stoi(date.substr(5,2));
            if (month < 4) {
                validOrder = false;
                cout << endl << "\t" << "ERROR !!! " << "date " << date << " is an expired/invalid order";
            }

            //shirtType
            switch (shirtType) {
                case 's':
                case 'S':
                case 'i':
                case 'I':
                case 'e':
                case 'E':
                case 'n':
                case 'N':
                    break;
                default:
                    validOrder = false;
                    cout << endl << "\t" << "ERROR !!! " << "invalid print method";
                    break;
            }

            // inputMessage length costs
            if ((shirtType == 'n' || shirtType == 'N') && inputMessage.length() != 0) {
                validOrder = false;
                cout << endl << "\t" << "ERROR !!! " << "print method of None, must also have empty string for message";
            }
            if (!(shirtType == 'n' || shirtType == 'N') && inputMessage.length() == 0) {
                validOrder = false;
                cout << endl << "\t" << "ERROR !!! " << "non-None print method, must not have empty string for message";
            }
            if (inputMessage.length() > 48) {
                validOrder = false;
                cout << endl << "\t" << "ERROR !!! " << "The message is longer than the allowed length of 49.  [ " << inputMessage.length() << " ]";
            }
            if (!(shirtType == 'n' || shirtType == 'N') && inputMessage.length() != 0) {
                for (int i = 0; i < inputMessage.length(); i++) {
                    if (inputMessage[i] != ' ') {
                        nonWhitespaceMessage = true;
                        break;
                    }
                }
                if (!nonWhitespaceMessage) {
                    validOrder = false;
                    cout << endl << "\t" << "ERROR !!! " << "non-None print method, must not have empty string for message";
                }
            }
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
            else if (!(shirtType == 'n' || shirtType == 'N') && (ink == "None")) {
                validOrder = false;
                cout << endl << "\t" << "ERROR !!! " << "non-None print method, must have non-None ink color";
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

            // Large
            if (large < 0) {
                validOrder = false;
                cout << endl << "\t" << "ERROR !!! " << "large shirt count must be greater than 0";
            }
            else if (large > maxNumberOfShirts) {
                validOrder = false;
                cout << endl << "\t" << "ERROR !!! " << large << " large shirts exceeds the maximum count for any size of " << maxNumberOfShirts;
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

            if ((medium + large + extraLarge) == 0) {
                validOrder = false;
                cout << endl << "\t" << "ERROR !!! " << "invalid order of 0 shirts";
            }
            if (validOrder) {
                orderTotal = calculateCost(shirtType, inputMessage, medium, large, extraLarge, color, ink);
                cout << setw(4) << right << "$" << setw(16) << fixed << setprecision(5) << right << orderTotal;
                switch (shirtType) {
                    case 's':
                    case 'S':
                        sShirtTotal += calculateShirtTotal(medium, large, extraLarge, color);
                        sPrintTotal += calculatePrintTotal(shirtType, inputMessage, medium, large, extraLarge, color, ink);
                        sFinalCost += orderTotal;
                        break;
                    case 'i':
                    case 'I':
                        iShirtTotal += calculateShirtTotal(medium, large, extraLarge, color);
                        iPrintTotal += calculatePrintTotal(shirtType, inputMessage, medium, large, extraLarge, color, ink);
                        iFinalCost += orderTotal;
                        break;
                    case 'e':
                    case 'E':
                        eShirtTotal += calculateShirtTotal(medium, large, extraLarge, color);
                        ePrintTotal += calculatePrintTotal(shirtType, inputMessage, medium, large, extraLarge, color, ink);
                        eFinalCost += orderTotal;
                        break;
                    case 'n':
                    case 'N':
                        nShirtTotal += calculateShirtTotal(medium, large, extraLarge, color);
                        nPrintTotal += calculatePrintTotal(shirtType, inputMessage, medium, large, extraLarge, color, ink);
                        nFinalCost += orderTotal;
                        break;
                }    
                // append valid records to vectors
                year = stoi(date.substr(0,4));
                day = stoi(date.substr(8,2));
                region.push_back(fileRegion);
                yyyy.push_back(year);
                mm.push_back(month);
                dd.push_back(day);
                printMethod.push_back(shirtType);
                message.push_back(inputMessage);
                m.push_back(medium);
                l.push_back(large);
                xl.push_back(extraLarge);
                shirtColor.push_back(color);
                inkColor.push_back(ink);
                contact.push_back(custNameAndEmail);
                oneValid = true;
                goodRecords++;
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

        inputFile.close();
        return oneValid;
    }
}
double calculateShirtTotal(const int m, const int l, const int xl, const string shirtColor) {
    double totalShirtCost = 0;
    int totalShirtCount = m + l + xl;

    totalShirtCost += ((m * mediumPerUnit) + (l * largePerUnit) + (xl * extraLargePerUnit)); //shirt cost per size
    if (shirtColor != "White") {
        totalShirtCost += (totalShirtCount * nonWhitePrice);
    }
    return totalShirtCost;
}
double calculatePrintTotal(const char printMethod, const string message, const int m, const int l, const int xl, const string shirtColor, const string inkColor) {
    double totalPrintCost;
    int totalShirtCount = m + l + xl;
    double setupPrice;
    double perUnitPrice;

    //printMethod and per character price
    switch (printMethod) {
    case 's':
    case 'S':
        setupPrice = sSetup;
        perUnitPrice = sPerUnit;
        break;
    case 'i':
    case 'I':
        setupPrice = iSetup;
        perUnitPrice = iPerUnit + iPerChar * message.length();
        break;
    case 'e':
    case 'E':
        setupPrice = eSetup;
        perUnitPrice = ePerUnit + ePerChar * message.length();
        break;
    default: //cases 'n' and 'N
        setupPrice = nSetup;
        perUnitPrice = nPerUnit;
        break;
    }
    totalPrintCost = setupPrice + perUnitPrice * totalShirtCount;

    return totalPrintCost;
}
double calculateCost(const char printMethod, const string message, const int m, const int l, const int xl, const string shirtColor, const string inkColor) {
    int totalShirtCount = m + l + xl;
    double subtotal;
    double discount = 0;
    double discountAmount;
    double orderTotal;

    //calculate discount
    if (totalShirtCount >= 1440) {
        discount = discount1440;
    }
    else if (totalShirtCount >= 144) {
        discount = discount144;
    }

    // calculate totals
    subtotal = calculateShirtTotal(m, l, xl, shirtColor) + calculatePrintTotal(printMethod, message, m, l, xl, shirtColor, inkColor);
    discountAmount = subtotal * discount;
    orderTotal = subtotal - discountAmount;
    
    return orderTotal;
}

void allDetails(const vector<string>& region, const vector<int>& yyyy, const vector<int>& mm, const vector<int>& dd, const vector<char>& printMethod, const vector<string>& message, const vector<int>& m, const vector<int>& l, const vector<int>& xl, const vector<string>& shirtColor, const vector<string>& inkColor, const vector<string>& contact) {
    if (region.empty()) {
        cout << endl << "There are no stored records." << endl;
        return;
    }
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << setw(8) << left << "region" << setw(10) << right << "order" << " " << setw(2) << left << "p" << setw(25) << left << "5 chars" << setw(5) << right << "msg" << setw(18) << right << "SIZES     " << setw(20) << right << "COLORS    " << setw(20) << "final" << endl;
    cout << setw(8) << " " << setw(10) << right << "date" << " " << setw(2) << left << "m" << setw(25) << left << "of msg" << setw(5) << right << "len" << setw(6) << right << "M" << setw(6) << right << "L" << setw(6) << right << "XL" << setw(10) << right << "shirt" << setw(10) << right << "ink" << setw(20) << "cost" << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
        
    for(int i = 0; i < region.size(); i++) {
        double finalCost = calculateCost(printMethod[i], message[i], m[i], l[i], xl[i], shirtColor[i], inkColor[i]);
        cout << setw(8) << left << region[i] << yyyy[i] << "/" << setw(2) << setfill('0') << right << mm[i] << "/" << setw(2) << dd[i] << " " << setw(2) << setfill(' ') << left << printMethod[i] << setw(23) << left << "\"" + message[i].substr(0,5) +  "..." << setw(3) << left << "\"" << setw(5) << right << message[i].length() << setw(6) << right << m[i] << setw(6) << right << l[i] << setw(6) << right << xl[i] << setw(10) << right << shirtColor[i] << setw(10) << right << inkColor[i] << setw(4) << right << "$" << setw(16) << fixed << setprecision(5) << right << finalCost << endl;;
    }
    return;
}
void summaryByMethod(const vector<string>& region, const vector<int>& yyyy, const vector<int>& mm, const vector<int>& dd, const vector<char>& printMethod, const vector<string>& message, const vector<int>& m, const vector<int>& l, const vector<int>& xl, const vector<string>& shirtColor, const vector<string>& inkColor, const vector<string>& contact) {
    if (region.empty()) {
        cout << endl << "There are no stored records." << endl;
        return;
    }

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

    for(int i = 0; i < region.size(); i++) {
        switch (printMethod[i]) {
            case 's':
            case 'S':
                sShirtTotal += calculateShirtTotal(m[i], l[i], xl[i], shirtColor[i]);
                sPrintTotal += calculatePrintTotal(printMethod[i], message[i], m[i], l[i], xl[i], shirtColor[i], inkColor[i]);
                sFinalCost += calculateCost(printMethod[i], message[i], m[i], l[i], xl[i], shirtColor[i], inkColor[i]);
                break;
            case 'i':
            case 'I':
                iShirtTotal += calculateShirtTotal(m[i], l[i], xl[i], shirtColor[i]);
                iPrintTotal += calculatePrintTotal(printMethod[i], message[i], m[i], l[i], xl[i], shirtColor[i], inkColor[i]);
                iFinalCost += calculateCost(printMethod[i], message[i], m[i], l[i], xl[i], shirtColor[i], inkColor[i]);
                break;
            case 'e':
            case 'E':
                eShirtTotal += calculateShirtTotal(m[i], l[i], xl[i], shirtColor[i]);
                ePrintTotal += calculatePrintTotal(printMethod[i], message[i], m[i], l[i], xl[i], shirtColor[i], inkColor[i]);
                eFinalCost += calculateCost(printMethod[i], message[i], m[i], l[i], xl[i], shirtColor[i], inkColor[i]);
                break;
            default: //cases 'n' and 'N
                nShirtTotal += calculateShirtTotal(m[i], l[i], xl[i], shirtColor[i]);
                nPrintTotal += calculatePrintTotal(printMethod[i], message[i], m[i], l[i], xl[i], shirtColor[i], inkColor[i]);
                nFinalCost += calculateCost(printMethod[i], message[i], m[i], l[i], xl[i], shirtColor[i], inkColor[i]);
                break;
            }
    }

    // final table
    cout << endl << setw(20) << right << "print method" << setw(20) << right << "blank shirt" << setw(20) << right << "printing" << setw(20) << right << "final cost" << endl;
    cout << setw(20) << right << "silk screen" << setw(20) << right << fixed << setprecision(5) << sShirtTotal << setw(20) << right << fixed << setprecision(5) << sPrintTotal << setw(20) << right << fixed << setprecision(5) << sFinalCost << endl;
    cout << setw(20) << right << "iron-on" << setw(20) << right << fixed << setprecision(5) << iShirtTotal << setw(20) << right << fixed << setprecision(5) << iPrintTotal << setw(20) << right << fixed << setprecision(5) << iFinalCost << endl;
    cout << setw(20) << right << "embroider" << setw(20) << right << fixed << setprecision(5) << eShirtTotal << setw(20) << right << fixed << setprecision(5) << ePrintTotal << setw(20) << right << fixed << setprecision(5) << eFinalCost << endl;
    cout << setw(20) << right << "none" << setw(20) << right << fixed << setprecision(5) << nShirtTotal << setw(20) << right << fixed << setprecision(5) << nPrintTotal << setw(20) << right << fixed << setprecision(5) << nFinalCost << endl;
    return;
}
void clearAll (vector<string>& region, vector<int>& yyyy, vector<int>& mm, vector<int>& dd, vector<char>& printMethod, vector<string>& message, vector<int>& m, vector<int>& l, vector<int>& xl, vector<string>& shirtColor, vector<string>& inkColor, vector<string>& contact) {
    region.clear();
    yyyy.clear();
    mm.clear();
    dd.clear();
    printMethod.clear();
    message.clear();
    m.clear();
    l.clear();
    xl.clear();
    shirtColor.clear();
    inkColor.clear();
    contact.clear();
    return;
}