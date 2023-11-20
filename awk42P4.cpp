/*
* awk42P4.cpp
*
* COSC 1020 Fall 2023
* Project #4 Code
*
* Due on: 19 November 2023
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

class ShirtOrder
{
    friend ostream& operator<<( ostream& os, const ShirtOrder& rhsObj ) {
        os << setw(8) << left << rhsObj.region << rhsObj.orderYear << "/" << setw(2) << setfill('0') << right << rhsObj.orderMonth << "/" << setw(2) << rhsObj.orderDay << " " << setw(2) << setfill(' ') << left << rhsObj.printMethod << setw(23) << left << "\"" + rhsObj.message.substr(0,5) +  "..." << setw(3) << left << "\"" << setw(5) << right << rhsObj.message.length() << setw(6) << right << rhsObj.mediums << setw(6) << right << rhsObj.larges << setw(6) << right << rhsObj.xls << setw(10) << right << rhsObj.shirtColor << setw(10) << right << rhsObj.inkColor << endl;// << setw(4) << right << "$" << setw(16) << fixed << setprecision(5) << right << rhsObj.getTotalCost() << endl;
        return os;
    };
    friend istream& operator>>( istream& in, ShirtOrder& rhsObj ) {
            string inputLine;
            if (getline(in, inputLine)) {
                int index = 0;
                string date = inputLine.substr(0, 10);
                int year = stoi(date.substr(0,4));
                int month = stoi(date.substr(5,2));
                int day = stoi(date.substr(8,2));
                index = inputLine.find_first_not_of(' ', inputLine.find(' ', index));
                char shirtType = inputLine[index];
                index = inputLine.find('"', index);
                index++;
                string inputMessage = inputLine.substr(index, inputLine.find('"', index) - index);
                index = inputLine.find_first_not_of(' ', inputLine.find(' ', inputLine.find('"', index)));
                int medium = stoi(inputLine.substr(index, inputLine.find(' ', index) - index));
                index = inputLine.find_first_not_of(' ', inputLine.find(' ', index));
                int large = stoi(inputLine.substr(index, inputLine.find(' ', index) - index));
                index = inputLine.find_first_not_of(' ', inputLine.find(' ', index));
                int extraLarge = stoi(inputLine.substr(index, inputLine.find(' ', index) - index));
                index = inputLine.find_first_not_of(' ', inputLine.find(' ', index));
                string color = inputLine.substr(index, inputLine.find(' ', index) - index);
                index = inputLine.find_first_not_of(' ', inputLine.find(' ', index));
                string ink = inputLine.substr(index, inputLine.find(' ', index) - index);
                index = inputLine.find_first_not_of(' ', inputLine.find(' ', index));
                string custNameAndEmail = inputLine.substr(index);

                cout << endl << setw(10) << date << " " << setw(2) << left << shirtType << setw(23) << left << "\"" + inputMessage.substr(0,5) +  "..." << setw(3) << left << "\"" << setw(5) << right << inputMessage.length() << setw(6) << right << medium << setw(6) << right << large << setw(6) << right << extraLarge << setw(10) << right << color << setw(10) << right << ink;
                
                ShirtOrder order("Other", year, month, day, shirtType, inputMessage, medium, large, extraLarge, color, ink, custNameAndEmail);
                rhsObj = order;
                return in;
            }
            else {
                return getline(in, inputLine);
            }
    };
    
private:
    // the data members below are required (you may change identifiers)
    // there is no need for additional data members and none are allowed
    string region;
    int orderYear, orderMonth, orderDay;
    char printMethod; // 's', 'i', 'e', or 'n'
    string message;
    int mediums; // number of medium shirts ordered
    int larges; // number of large shirts ordered
    int xls; // number of XL shirts ordered
    string shirtColor;
    string inkColor;
    string nameAndEmail;

    double discountedPrice(double price, int totalShirtCount) const {
        if (totalShirtCount >= 1440) {
            price *= (1 - discount1440);
        }
        else if (totalShirtCount >= 144) {
            price *= (1 - discount144);
        }
        return price;
    }

public:
    ShirtOrder() : orderYear(2023), orderMonth(4), orderDay(1), mediums(0), larges(0), xls(0), region(""), message(""), shirtColor(""), inkColor(""), nameAndEmail(""), printMethod('n') {
    };
    ShirtOrder( string region, int orderYear, int orderMonth, int orderDay,
               char printMethod, string message, 
               int mediums, int larges, int xls,
               string shirtColor,  string inkColor, 
               string nameAndEmail ) : region(region), orderYear(orderYear), orderMonth(orderMonth), orderDay(orderDay), printMethod(printMethod), message(message), mediums(mediums), larges(larges), xls(xls), shirtColor(shirtColor), inkColor(inkColor), nameAndEmail(nameAndEmail) {
               };
    
    ShirtOrder( const ShirtOrder &otherOrder ) {
        region = otherOrder.region;
        orderYear = otherOrder.orderYear;
        orderMonth = otherOrder.orderMonth;
        orderDay = otherOrder.orderDay;
        printMethod = otherOrder.printMethod;
        message = otherOrder.message;
        mediums = otherOrder.mediums;
        larges = otherOrder.larges;
        xls = otherOrder.xls;
        shirtColor = otherOrder.shirtColor;
        inkColor = otherOrder.inkColor;
        nameAndEmail = otherOrder.nameAndEmail;
    };
    
    ShirtOrder& operator=( const ShirtOrder &otherOrder ) {
        region = otherOrder.region;
        orderYear = otherOrder.orderYear;
        orderMonth = otherOrder.orderMonth;
        orderDay = otherOrder.orderDay;
        printMethod = otherOrder.printMethod;
        message = otherOrder.message;
        mediums = otherOrder.mediums;
        larges = otherOrder.larges;
        xls = otherOrder.xls;
        shirtColor = otherOrder.shirtColor;
        inkColor = otherOrder.inkColor;
        nameAndEmail = otherOrder.nameAndEmail;
        return *this;
    };
    
    void setOrderDate(int yyyy, int mm, int dd) {
        orderYear = yyyy;
        orderMonth = mm;
        orderDay = dd;
    
    };
    // ADD DISCOUNT
    double getBlankCost() const {
        double totalShirtCost = 0;
        int totalShirtCount = mediums + larges + xls;
        totalShirtCost += ((mediums * mediumPerUnit) + (larges * largePerUnit) + (xls * extraLargePerUnit)); //shirt cost per size
        if (shirtColor != "White") {
            totalShirtCost += (totalShirtCount * nonWhitePrice);
        }
        return discountedPrice(totalShirtCost, totalShirtCount);
    };
    double getPrintingCost() const {
        double totalPrintCost;
        int totalShirtCount = mediums + larges + xls;
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

        return discountedPrice(totalPrintCost, totalShirtCount);
    };
    double getTotalCost() const {
        return getBlankCost() + getPrintingCost();
    };
    string getMethodName() const {
        switch(printMethod) {
            case 's':
            case 'S':
                return "Silk-screen";
            case 'i':
            case 'I':
                return "Iron-on";
            case 'e':
            case 'E':
                return "Embroidery";
        }
        return "None";
    };
    
    // basic accessor methods provided with in-line implementation
    // NOTE: must edit identifiers if you changed them above
    string getRegion() const { return  region; }
    int getOrderYear() const { return  orderYear; }
    int getOrderMonth() const { return  orderMonth; }
    int getOrderDay() const { return  orderDay; }
    char getPrintMethod() const { return  printMethod; }
    string getMessage() const { return  message; }
    int getMessageLength() const { return message.length(); }
    int getMediums() const { return  mediums; }
    int getLarges() const { return  larges; }
    int getXls() const { return  xls; }
    string getShirtColor() const { return  shirtColor; }
    string getInkColor() const { return  inkColor; }
    string getNameAndEmail() const { return  nameAndEmail; }
    
    // basic mutator methods provided with in-line implementation
    // NOTE: must edit identifiers if you changed them above
    void setRegion( string value ) { region = value; }
    void setOrderYear( int value ) { orderYear = value; }
    void setOrderMonth( int value ) { orderMonth = value; }
    void setOrderDay( int value ) { orderDay = value; }
    void setPrintMethod( char value ) { printMethod = value; }
    void setMessage( string value ) { message = value; }
    void setMediums( int value ) { mediums = value; }
    void setLarges( int value ) { larges = value; }
    void setXls( int value ) { xls = value; }
    void setShirtColor( string value ) { shirtColor = value; }
    void setInkColor( string value ) { inkColor = value; }
    void setNameAndEmail( string value ) { nameAndEmail = value; }
    
    // NOTE: all of these validation methods are OPTIONAL
    //       the function stubs should all return true
    //       move the applicable code from Project 3 into
    //       these methods if you decide to write the
    //       implementation code
    // bool isValidRegion() const {};
    bool isValidMonth() const {
        if (orderMonth < 4) {
            return false;
        }
        return true;
    };
    bool isValidMethod() const {
        switch (printMethod) {
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
                    cout << endl << "\t" << "ERROR !!! " << "invalid print method";
                    return false;
                    break;
            }
        return true;
    };
    bool isValidMessage() const {
        bool validOrder = true;
        bool nonWhitespaceMessage = false;
        if ((printMethod == 'n' || printMethod == 'N') && message.length() != 0) {
            validOrder = false;
            cout << endl << "\t" << "ERROR !!! " << "print method of None, must also have empty string for message";
        }
        if (!(printMethod == 'n' || printMethod== 'N') && message.length() == 0) {
            validOrder = false;
            cout << endl << "\t" << "ERROR !!! " << "non-None print method, must not have empty string for message";
        }
        if (message.length() > 48) {
            validOrder = false;
            cout << endl << "\t" << "ERROR !!! " << "The message is longer than the allowed length of 49.  [ " << message.length() << " ]";
        }
        if (!(printMethod== 'n' || printMethod == 'N') && message.length() != 0) {
            for (int i = 0; i < message.length(); i++) {
                if (message[i] != ' ') {
                    nonWhitespaceMessage = true;
                    break;
                }
            }
            if (!nonWhitespaceMessage) {
                validOrder = false;
                cout << endl << "\t" << "ERROR !!! " << "non-None print method, must not have empty string for message";
            }
        }
        return validOrder;
    };
    bool isValidMessageLength() const;
    bool isValidMCount() const {
        if (mediums < 0) {
                cout << endl << "\t" << "ERROR !!! " << "medium shirt count must be greater than 0";
                return false;
        }
        else if (mediums > maxNumberOfShirts) {
            cout << endl << "\t" << "ERROR !!! " << mediums << " medium shirts exceeds the maximum count for any size of " << maxNumberOfShirts;
            return false;
        }
        return true;
    };
    bool isValidLCount() const {
        // Large
        if (larges < 0) {
            cout << endl << "\t" << "ERROR !!! " << "large shirt count must be greater than 0";
            return false;
        }
        else if (larges > maxNumberOfShirts) {
            cout << endl << "\t" << "ERROR !!! " << larges << " large shirts exceeds the maximum count for any size of " << maxNumberOfShirts;
            return false;
        }
        return true;
    };
    bool isValidXLCount() const {
        if (xls < 0) {
            cout << endl << "\t" << "ERROR !!! " << "extra large shirt count must be greater than 0";
            return false;
        }
        else if (xls > maxNumberOfShirts) {
            cout << endl << "\t" << "ERROR !!! " << xls << " extra large shirts exceeds the maximum count for any size of " << maxNumberOfShirts;
            return false;
        }
        return true;
    };
    bool isValidShirtCount() const {
        if (mediums + larges + xls == 0) {
            cout << endl << "\t" << "ERROR !!! " << "invalid order of 0 shirts";
            return false;
        }
        return true;
    }
    bool isValidShirtColor() const {
//        cout << endl << setw(8) << left << region << orderYear << "/" << setw(2) << setfill('0') << right << orderMonth << "/" << setw(2) << orderDay << " " << setw(2) << setfill(' ') << left << printMethod << setw(23) << left << "\"" + message.substr(0,5) +  "..." << setw(3) << left << "\"" << setw(5) << right << message.length() << setw(6) << right << mediums << setw(6) << right << larges << setw(6) << right << xls << setw(10) << right << shirtColor << setw(10) << right << inkColor << setw(4) << right << "$" << setw(16) << fixed << setprecision(5) << right << getTotalCost() << endl;
        bool validColorBool = false;
        for (int i = 0; i < validColorLength; i++) {
            if (shirtColor == validColor[i]) {
                validColorBool = true;
                break;
            }
        }
        if (!validColorBool) {
            cout << endl << "\t" << "ERROR !!! " << "invalid shirt color";
            return false;
        }
        return true;
    };
    bool isValidInkColor() const {
            if (!(inkColor == "Black" || inkColor == "White" || inkColor == "None")) {
                cout << endl << "\t" << "ERROR !!! " << "invalid ink color";
                return false;
            }
            return true;
    };
    bool isValidColorCombination() const {
        if ((shirtColor == "Black" && inkColor == "Black") || (shirtColor == "White" && inkColor == "White")) {
            cout << endl << "\t" << "ERROR !!! " << inkColor << " print on a " << shirtColor << " shirt is not a valid color combination";
            return false;
        }
        else if ((printMethod == 'n' || printMethod == 'N') && (inkColor != "None")) {
            cout << endl << "\t" << "ERROR !!! " << "print method of None, must also have ink color None";
            return false;
        }
        else if (!(printMethod == 'n' || printMethod == 'N') && (inkColor == "None")) {
            cout << endl << "\t" << "ERROR !!! " << "non-None print method, must have non-None ink color";
            return false;
        }
        return true;
    };	
    bool isValidShirtOrder() const {
        bool validOrder = true;
        if (!isValidMonth()) validOrder = false;
        if (!isValidMethod()) validOrder = false;
        if (!isValidMessage()) validOrder = false;
        if (!isValidMCount()) validOrder = false;
        if (!isValidLCount()) validOrder = false;
        if (!isValidXLCount()) validOrder = false;
        if (!isValidShirtCount()) validOrder = false;
        if (!isValidShirtColor()) validOrder = false;
        if (!isValidInkColor()) validOrder = false;
        if (!isValidColorCombination()) validOrder = false;
        return validOrder;
    };
    
}; // END declaration of class ShirtOrder

char displayMenu();
bool uploadFile (string fileName, vector<ShirtOrder>& shirtOrders);
void allDetails (const vector<ShirtOrder>& shirtOrders);
void summaryByMethod(const vector<ShirtOrder>& shirtOrders);
void summaryByRegion(const vector<ShirtOrder>& shirtOrders);
void clearAll (vector<ShirtOrder>& shirtOrders);

int main() {
    vector<ShirtOrder> shirtOrders;
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
                uploadFile(fileName, shirtOrders);
                break;
            case 'a':
            case 'A':
                allDetails(shirtOrders);
                break;
            case 'm':
            case 'M':
                summaryByMethod(shirtOrders);
                break;
            case 'r':
            case 'R':
                summaryByRegion(shirtOrders);
                break;
            case 'c':
            case 'C':
                clearAll(shirtOrders);
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
    cout << "\t" << " - (R) display a summary by Region" << endl;
    cout << "\t" << " - (C) Clear all data" << endl;
    cout << "\t" << " - (Q) Quit" << endl;
    cin >> choice;
    cin.ignore(10000, '\n');
    return choice;
}

bool uploadFile (string fileName, vector<ShirtOrder>& shirtOrders) {
    // INTERMEDIATE VALUES
    ifstream inputFile;
    string inputLine;
    double orderTotal;
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
        
        ShirtOrder order;
        while (inputFile >> order) {
            order.setRegion(fileRegion);
            if (order.isValidShirtOrder()) {
                orderTotal = order.getTotalCost();
                shirtOrders.push_back(order);
                cout << setw(4) << right << "$" << setw(16) << fixed << setprecision(5) << right << orderTotal;
                // switch (order.getPrintMethod()) {
                //     case 's':
                //     case 'S':
                //         sShirtTotal += order.getBlankCost();
                //         sPrintTotal += order.getPrintingCost();
                //         sFinalCost += orderTotal;
                //         break;
                //     case 'i':
                //     case 'I':
                //         iShirtTotal += order.getBlankCost();
                //         iPrintTotal += order.getPrintingCost();
                //         iFinalCost += orderTotal;
                //         break;
                //     case 'e':
                //     case 'E':
                //         eShirtTotal += order.getBlankCost();
                //         ePrintTotal += order.getPrintingCost();
                //         eFinalCost += orderTotal;
                //         break;
                //     case 'n':
                //     case 'N':
                //         nShirtTotal += order.getBlankCost();
                //         nPrintTotal += order.getPrintingCost();
                //         nFinalCost += orderTotal;
                //         break;
                // }   
                oneValid = true;
                goodRecords++;
            }
            else {
                cout << endl << "\t" << "To fix this line, please contact .. " << order.getNameAndEmail();
                badRecords++;
            }
        }
        cout << endl << endl << "good records = " << goodRecords << ", bad records = " << badRecords << endl << endl;

        // final table
        // cout << setw(20) << right << "print method" << setw(20) << right << "blank shirt" << setw(20) << right << "printing" << setw(20) << right << "final cost" << endl;
        // cout << setw(20) << right << "silk screen" << setw(20) << right << fixed << setprecision(5) << sShirtTotal << setw(20) << right << fixed << setprecision(5) << sPrintTotal << setw(20) << right << fixed << setprecision(5) << sFinalCost << endl;
        // cout << setw(20) << right << "iron-on" << setw(20) << right << fixed << setprecision(5) << iShirtTotal << setw(20) << right << fixed << setprecision(5) << iPrintTotal << setw(20) << right << fixed << setprecision(5) << iFinalCost << endl;
        // cout << setw(20) << right << "embroider" << setw(20) << right << fixed << setprecision(5) << eShirtTotal << setw(20) << right << fixed << setprecision(5) << ePrintTotal << setw(20) << right << fixed << setprecision(5) << eFinalCost << endl;
        // cout << setw(20) << right << "none" << setw(20) << right << fixed << setprecision(5) << nShirtTotal << setw(20) << right << fixed << setprecision(5) << nPrintTotal << setw(20) << right << fixed << setprecision(5) << nFinalCost << endl;

        inputFile.close();
        return oneValid;
    }
}

void allDetails(const vector<ShirtOrder>& shirtOrders) {
    if (shirtOrders.empty()) {
        cout << endl << "There are no stored records." << endl;
        return;
    }
    cout << "----------------------------------------------------------------------------------------------------" << endl;
    cout << setw(8) << left << "region" << setw(10) << right << "order" << " " << setw(2) << left << "p" << setw(25) << left << "5 chars" << setw(5) << right << "msg" << setw(18) << right << "SIZES     " << setw(20) << right << "COLORS    " << setw(20) << "final" << endl;
    cout << setw(8) << " " << setw(10) << right << "date" << " " << setw(2) << left << "m" << setw(25) << left << "of msg" << setw(5) << right << "len" << setw(6) << right << "M" << setw(6) << right << "L" << setw(6) << right << "XL" << setw(10) << right << "shirt" << setw(10) << right << "ink" << setw(20) << "cost" << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;
        
    for(int i = 0; i < shirtOrders.size(); i++) {
        cout << shirtOrders[i];
    }
    return;
}
void summaryByMethod(const vector<ShirtOrder>& shirtOrders) {
    if (shirtOrders.empty()) {
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

    for(int i = 0; i < shirtOrders.size(); i++) {
        switch (shirtOrders[i].getPrintMethod()) {
            case 's':
            case 'S':
                sShirtTotal += shirtOrders[i].getBlankCost();
                sPrintTotal += shirtOrders[i].getPrintingCost();
                sFinalCost += shirtOrders[i].getTotalCost();
                break;
            case 'i':
            case 'I':
                iShirtTotal += shirtOrders[i].getBlankCost();
                iPrintTotal += shirtOrders[i].getPrintingCost();
                iFinalCost += shirtOrders[i].getTotalCost();
                break;
            case 'e':
            case 'E':
                eShirtTotal += shirtOrders[i].getBlankCost();
                ePrintTotal += shirtOrders[i].getPrintingCost();
                eFinalCost += shirtOrders[i].getTotalCost();
                break;
            default: //cases 'n' and 'N
                nShirtTotal += shirtOrders[i].getBlankCost();
                nPrintTotal += shirtOrders[i].getPrintingCost();
                nFinalCost += shirtOrders[i].getTotalCost();
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
void summaryByRegion(const vector<ShirtOrder>& shirtOrders) {
    if (shirtOrders.empty()) {
        cout << endl << "There are no stored records." << endl;
        return;
    }

    double northShirtTotal = 0;
    double southShirtTotal = 0;
    double eastShirtTotal = 0;
    double westShirtTotal = 0;
    double otherShirtTotal = 0;
    double northPrintTotal = 0;
    double southPrintTotal = 0;
    double eastPrintTotal = 0;
    double westPrintTotal = 0;
    double otherPrintTotal = 0;
    double northFinalCost = 0;
    double southFinalCost = 0;
    double eastFinalCost = 0;
    double westFinalCost = 0;
    double otherFinalCost = 0;

    for(int i = 0; i < shirtOrders.size(); i++) {
        string region = shirtOrders[i].getRegion();
        if (region == "North") {
            northShirtTotal += shirtOrders[i].getBlankCost();
            northPrintTotal += shirtOrders[i].getPrintingCost();
            northFinalCost += shirtOrders[i].getTotalCost();
        }
        else if (region == "South") {
            southShirtTotal += shirtOrders[i].getBlankCost();
            southPrintTotal += shirtOrders[i].getPrintingCost();
            southFinalCost += shirtOrders[i].getTotalCost();
        }
        else if (region == "East") {
            eastShirtTotal += shirtOrders[i].getBlankCost();
            eastPrintTotal += shirtOrders[i].getPrintingCost();
            eastFinalCost += shirtOrders[i].getTotalCost();
        }
        else if (region == "West") {
            westShirtTotal += shirtOrders[i].getBlankCost();
            westPrintTotal += shirtOrders[i].getPrintingCost();
            westFinalCost += shirtOrders[i].getTotalCost();
        }
        else {
            otherShirtTotal += shirtOrders[i].getBlankCost();
            otherPrintTotal += shirtOrders[i].getPrintingCost();
            otherFinalCost += shirtOrders[i].getTotalCost();
        }
    }

    // final table
    cout << endl << setw(20) << right << "region" << setw(20) << right << "blank shirt" << setw(20) << right << "printing" << setw(20) << right << "final cost" << endl;
    cout << setw(20) << right << "North" << setw(20) << right << fixed << setprecision(5) << northShirtTotal << setw(20) << right << fixed << setprecision(5) << northPrintTotal << setw(20) << right << fixed << setprecision(5) << northFinalCost << endl;
    cout << setw(20) << right << "South" << setw(20) << right << fixed << setprecision(5) << southShirtTotal << setw(20) << right << fixed << setprecision(5) << southPrintTotal << setw(20) << right << fixed << setprecision(5) << southFinalCost << endl;
    cout << setw(20) << right << "East" << setw(20) << right << fixed << setprecision(5) << eastShirtTotal << setw(20) << right << fixed << setprecision(5) << eastPrintTotal << setw(20) << right << fixed << setprecision(5) << eastFinalCost << endl;
    cout << setw(20) << right << "West" << setw(20) << right << fixed << setprecision(5) << westShirtTotal << setw(20) << right << fixed << setprecision(5) << westPrintTotal << setw(20) << right << fixed << setprecision(5) << westFinalCost << endl;
    cout << setw(20) << right << "Other" << setw(20) << right << fixed << setprecision(5) << otherShirtTotal << setw(20) << right << fixed << setprecision(5) << otherPrintTotal << setw(20) << right << fixed << setprecision(5) << otherFinalCost << endl;
    return;
}
void clearAll (vector<ShirtOrder>& shirtOrders) {
    shirtOrders.clear();
    return;
}