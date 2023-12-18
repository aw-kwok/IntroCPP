/*
 *  main.cpp                                 
 *                                                
 *  COSC 1020 Fall 2023                          
 *  Project #5                                    
 *                                                
 *  Due on: DEC 4, 2023                  
 *  Author: Andrew Kwok   awk42                           
 * 
 *
 *  In accordance with the class policies and Georgetown's
 *  Honor Code, I certify that, with the exception of the 
 *  class resources and those items noted below, I have neither
 *  given nor received any assistance on this project. 
 *
 *  References not otherwise commented within the program source code.
 *  Note that you should not mention any help from the TAs, the professor, 
 *  or any code taken from the class textbooks.
 */



// You will probably need some additional includes here
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int defaultYear = 2023;
const int defaultMonth = 1;
const int defaultDay = 1;
const string defaultEmail = "none@none.com";

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 class ShirtCustomer declaration                        **
 **                                                                        **
 **                 This code is provided to students                      **
 **                 in COSC 1020 Fall 2023 to use in                       **
 **                 part or in total for class projects.                   **
 **                 Students may use this code as their                    **
 **                 own, without any attribution.                          **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/


class ShirtCustomer
{
    friend ostream& operator<<( ostream& os, const ShirtCustomer& rhsObj ) {
        os << rhsObj.orderYear << "/" << setw(2) << setfill('0') << right << rhsObj.orderMonth << "/" << setw(2) << rhsObj.orderDay << " " << rhsObj.email;
        return os;
    };
    friend istream& operator>>( istream& in, ShirtCustomer& rhsObj ) {
        return in;
    };
    
private:
    // The data members below are required (you may change identifiers)
    // There is no need for additional data members and none are allowed

	// Date of the last order from this customer
    // Default 2023/1/1 (use these values in the default constructor, make them global constants)
    int orderYear, orderMonth, orderDay;  
	
	// Customer's email address
	// Default none@none.com (use that string for default constructor, make them global constants)
    string email;
	
	// Pointer to next ShirtCustomer object in the linked list 
	// Default NULL (use that address for the default constructor)
	ShirtCustomer* next;

    
public:
    ShirtCustomer() {
        orderYear = defaultYear;
        orderMonth = defaultMonth;
        orderDay = defaultDay;
        email = defaultEmail;
        next = nullptr;
    };
    ShirtCustomer( int orderYear, int orderMonth, int orderDay, string email ) : orderYear(orderYear), orderMonth(orderMonth), orderDay(orderDay), email(email), next(nullptr) {
    };    
    ShirtCustomer( const ShirtCustomer &otherCustomer ) {
        orderYear = otherCustomer.orderYear;
        orderMonth = otherCustomer.orderMonth;
        orderDay = otherCustomer.orderDay;
        email = otherCustomer.email;
        next = nullptr;
    };
    
    ShirtCustomer& operator=( const ShirtCustomer &otherCustomer ) {
        orderYear = otherCustomer.orderYear;
        orderMonth = otherCustomer.orderMonth;
        orderDay = otherCustomer.orderDay;
        email = otherCustomer.email;
        next = nullptr;
        return *this;
    };
    
    
    // Basic accessor methods provided with in-line implementation
    // NOTE: must edit identifiers if you changed them above
    int getOrderYear() const { return  orderYear; }
    int getOrderMonth() const { return  orderMonth; }
    int getOrderDay() const { return  orderDay; }
    string getEmail() const { return  email; }
	ShirtCustomer* getNext() const { return next; }
    
    // Basic mutator methods provided with in-line implementation
    // NOTE: must edit identifiers if you changed them above
    void setOrderYear( int value ) { orderYear = value; }
    void setOrderMonth( int value ) { orderMonth = value; }
    void setOrderDay( int value ) { orderDay = value; }
    void setEmail( string value ) { email = value; }
	void setNext( ShirtCustomer* value ) { next = value; }
    
}; // END declaration of class ShirtCustomer






/****************************************************************************
 *                  Stand-alone Function Prototypes                         *
 ****************************************************************************/

// Both upload functions are responsible for opening the data file, testing that 
// the file opened successfully, then reading the contents and building a linked list 
// of ShirtCustomer objects.
//
// It is expected that the pointer passed is a pointer to an empty linked list
// meaning a pointer storing NULL.  If the pointer is not to an empty linked list 
// then the function should not open the data file or load any data.  Return false.
//
// The listSize should be zero.  If the listSize is not zero then the function should
// not open the data file or load any data.  Return false.
//
// If the list is empty, the pointer is NULL, and the listSize is zero, 
// then open the data file.  If the file fails to open, then do not try 
// to load any data.  Return false.
//
// If the file does not contain any data, then the listSize will not change.  If the 
// listSize does not increase, then loading the data failed.  Return false.
//
// If the linked list is originally empty (pointer is NULL and listSize is zero); and the 
// file is successfully loaded (the listSize increases), then return true.

// HINT: Append to end of the list.
bool uploadFileInOrder(string fileName, ShirtCustomer*& customerPointer, long& listSize) {
    if (customerPointer != nullptr || listSize != 0) {
        return false;
    }
    
    ifstream inputFile;
    string inputLine;
    int origListSize = listSize;
    int inputYear;
    int inputMonth;
    int inputDay;
    string inputEmail;

    inputFile.open(fileName);
    if (inputFile.fail()) {
        return false;
    }
    
    // Ignore first line
    getline(inputFile, inputLine);
    
    ShirtCustomer* current = nullptr;

    while (getline(inputFile, inputLine)) {
        int index = 0;
        inputYear = stoi(inputLine.substr(0, 4));
        index = inputLine.find('/', index);
        index++;
        inputMonth = stoi(inputLine.substr(index, 2));
        index = inputLine.find('/', index);
        index++;
        inputDay = stoi(inputLine.substr(index, 2));
        index = inputLine.find(' ', index);
        index++;
        inputEmail = inputLine.substr(index);
        ShirtCustomer* cust = new ShirtCustomer(inputYear, inputMonth, inputDay, inputEmail);
        // if new customer is first customer created, set head to cust
        if (current == nullptr) {
            customerPointer = cust;
        }
        else {
            current->setNext(cust);
        }
        listSize++;
        current = cust;
    }
    
    if (listSize == origListSize) {
        return false;
    }
    return true;
};

// HINT: Insert to front of the list.
bool uploadFileInReverse(string fileName, ShirtCustomer*& customerPointer, long& listSize) {
    if (customerPointer != nullptr || listSize != 0) {
        return false;
    }
    
    ifstream inputFile;
    string inputLine;
    int origListSize = listSize;
    int inputYear;
    int inputMonth;
    int inputDay;
    string inputEmail;

    inputFile.open(fileName);
    if (inputFile.fail()) {
        return false;
    }
    
    // Ignore first line
    getline(inputFile, inputLine);

    while (getline(inputFile, inputLine)) {
        int index = 0;
        inputYear = stoi(inputLine.substr(0, 4));
        index = inputLine.find('/', index);
        index++;
        inputMonth = stoi(inputLine.substr(index, 2));
        index = inputLine.find('/', index);
        index++;
        inputDay = stoi(inputLine.substr(index, 2));
        index = inputLine.find(' ', index);
        index++;
        inputEmail = inputLine.substr(index);
        ShirtCustomer* cust = new ShirtCustomer(inputYear, inputMonth, inputDay, inputEmail);
        cust->setNext(customerPointer);
        customerPointer = cust;
        listSize++;
    }

    if (listSize == origListSize) {
        return false;
    }
    return true;
};


// Delete all objects on the list and deallocate all dynamically allocted memory.
void deleteList(ShirtCustomer*& customerPointer, long& listSize) {
    while (customerPointer != nullptr) {
        ShirtCustomer* temp = customerPointer;
        customerPointer = customerPointer->getNext();
        delete temp;  
    }
    listSize = 0;
};  

// Output the objects on the list, starting at head.
// Do not consider which function loaded the data.  Just start at the head pointer 
// and print objects in the order they are stored on the list. 
void displayList(ShirtCustomer* customerPointer) {
    cout << setw(12) << setfill(' ') << left << "date" << "email" << endl;
    ShirtCustomer* current = customerPointer;
    while (current != nullptr) {
        cout << *current << endl;
        current = current->getNext();
    }
};  



/****************************************************************************
 *                                                                          *
 *                                 main                                     *
 *                                                                          *
 ****************************************************************************/
int main(int argc, char* argv[])
{

    // Put variables here. 
	// You will at least need one for the file name, a pointer for 
    // the address of the first object on the linked list, and
    // a long variable to store the number of objects on the 
    // linked lists.  Maybe a few others as well.
    string fileName;
    ShirtCustomer* head = nullptr;
    long size = 0;


    // Prompt for the user to enter the full path and name of the input data file

    cout << "Please enter the full path and name of the input data file: ";
    cin >> fileName;
	
	
	// Call the function to delete the objects on the linked list.
	// (technically not required here, but just to keep the sequence of events consistent)
	// Call the function to load the linked list in same order as the input data file.
	// Call the function to display the contents of the linked list.
	
    cout << "IN-ORDER" << endl;
    deleteList(head, size);
    uploadFileInOrder(fileName, head, size);
    displayList(head);

 	// Call the function to delete the objects on the linked list.
	// (now this is required since data were previously loaded onto the list)
	// Call the function to load the linked list in reverse order of the input data file.
	// Call the function to display the contents of the linked list.

    cout << endl;

    cout << "REVERSE ORDER" << endl;
    deleteList(head, size);
    uploadFileInReverse(fileName, head, size);
    displayList(head);
    
	// Make a final call to delete the linked list.
	deleteList(head, size);
    return 0;

} // END main function