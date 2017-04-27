//
//  Functions.h
//  CSCI 2421 Final Project
//
//  Created by Bradley Ruck on 4/15/16.
//  Last updated 3/31/17.
//  Copyright © 2016 Bradley Ruck. All rights reserved.
//

#ifndef Functions_h
#define Functions_h

#include <iostream>
#include <fstream>
#include <istream>
#include <vector>
#include <cctype>
#include <algorithm>
#include <string>
#include <cstdlib>

using namespace std;

void displayMenu() {
// Display the main menu for user selection

    cout << "\n				MENU\n";
    cout << "______________________________________\n";
    cout << "1)  Display Address Book\n";
    cout << "2)  Add a new Contact\n";
    cout << "3)  Update a Contact\n";
    cout << "4)  Delete a Contact\n";
    cout << "5)  Search Address Book for ID Number\n";
    cout << "6)  Search Address Book for Contact\n";
    cout << "7)  Read a list of Contacts from file\n";
    cout << "8)  Write the Address Book to file and exit\n";
    cout << "9)  Exit without saving\n\n";
    cout << "Please enter your menu selection, 1 - 9: ";
}

void addContact(AVLTree& addressbook) {
// Adds a contact to the existing address book

    Contact data;
    char choice1, choice2, choice3;
    int IDtag;
    string affFirst, affLast, affMobNo, affEmail;
    
    cout << "Please enter the contact's first name: ";
    cin.clear();
    cin.ignore();
    getline(cin, data.First);
    cout << "Please enter the contact's middle name: ";
    getline(cin, data.Middle);
    cout << "Please enter the contact's last name: ";
    getline(cin, data.Last);
    cout << "Please enter the contact's company name: ";
    getline(cin, data.Company);
    cout << "Please enter the contact's home phone: ";
    getline(cin, data.HomePhone);
    cout << "Please enter the contact's office phone: ";
    getline(cin, data.OfficePhone);
    cout << "Please enter the contact's email: ";
    getline(cin, data.Email);
    cout << "Please enter the contact's mobile phone: ";
    getline(cin, data.MobileNo);
    cout << "Please enter the contact's street address: ";
    getline(cin, data.StreetAddress);
    cout << "Please enter the contact's city: ";
    getline(cin, data.City);
    cout << "Please enter the contact's state: ";
    getline(cin, data.State);
    cout << "Please enter the contact's zip code: ";
    getline(cin, data.ZipCode);
    cout << "Please enter the contact's country: ";
    getline(cin, data.Country);
    
    cout << "Do you have any affiliates to add to the contact's record?" << endl << "Enter Y or N: ";
    cin >> choice1;
    if (choice1 == 'Y' || choice1 == 'y') {
        do{
            affFirst.erase(); affLast.erase(); affMobNo.erase(); affEmail.erase();
        cout << "Please enter the affiliates first name: ";
        cin >> affFirst;
        cout << "Please enter the affiliates last name: ";
        cin >> affLast;
        cout << "Would you like to add a mobile number and email for this affiliate?" << endl << "Enter Y or N: ";
        cin >> choice2;
        if (choice2 == 'Y' || choice2 == 'y') {
            cout << "Please enter the affiliates mobile number: ";
            cin >> affMobNo;
            cout << "Please enter the affiliates email: ";
            cin >> affEmail;
        }
        Affiliate newAffiliate(affFirst, affLast, affMobNo, affEmail);
        data.AffiliateList.push_back(newAffiliate);
        cout << "Would you like to add another affiliate to add to the contact's record?" << endl << "Enter Y or N: ";
        cin >> choice3;
        }
        while (choice3 == 'Y' || choice3 == 'y');
        }
    else
        cout << "You have chosen not to add any affiliates" << endl;
    
    IDtag = (rand()% 890000001) + 100000000;
    data.ID = IDtag;
    
    addressbook.insert(data);
}

void editContact(AVLTree& addressbook) {
// Allows any contact in address book to be edited for any of its fields

    int ch1, ch2, ch3, ID;
    char choice1, choice2, choice3, choice4;
    char choice5, choice6, choice7, choice8;
    string name, affFirst, affLast, affMobNo, affEmail;
    vector<Contact> Results;
    Contact data;
    
    if(addressbook.size() == 0) {
        cout << "\n**The address book is empty.**\n\n";
        return;
    }
    cout << "Do you know the name of a contact you would like to edit?" << endl << "Enter Y for yes or N for no :";
    cin >> choice1;
    // Search all fields in contact names to find a particular name
    if (choice1 == 'Y' || choice1 == 'y') {
        cout << endl << "Please enter the name of the contact: ";
        cin.clear();
        cin.ignore();
        getline(cin, name);
        // Change name to all lower case for robustness of search
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        // Call the search function for the name entered
        addressbook.search(name, Results);
        if (Results.size() != 0) {
            // Print out all of the unique contacts for the name entered
            cout << "\n'" << name << "' has existing match(es) with the following " << Results.size()
                 << " Contact(s): \n";
            for (int j = 0; j < Results.size(); j++) {
                cout << endl << (j + 1) << ")  ";
                cout << addressbook.printNode(Results[j]) << endl;
            }
            cout << endl;
        }
        else {
            cout << "The name you entered does not exist in the address book." << endl << endl;
            displayMenu();
        }
    }
    else {
        // Offer up the entire address book if no specific name is known
        cout << "\nThe following is the current list of contacts in the address book: " << endl;
        addressbook.printTree();
    }

    // Have user choose from a list of possible contacts that have name match
    if ((choice1 == 'Y' || choice1 == 'y') && (Results.size() > 1)) {
        cout << "\nIf you see the contact you wish to edit, please enter the corresponding number 1) thru "
             << Results.size() << "): ";
        // Check entry for non integer entry, if found, clear flag and empty buffer
        while (!(cin >> ch3)) {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "\nThat was not a valid choice!\n";
            cout << "\nIf you see the contact you wish to edit, please enter the corresponding number 1) thru "
                 << Results.size() << "): ";
        }
        // After entry checked for type, check that entry falls within acceptable range
        if (ch3 < 1 || ch3 > (Results.size())) {
            do {
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                cout << "\nPlease limit your selection from 1) thru " << Results.size() << "): ";
                cin >> ch3;
            } while (ch3 < 1 || ch3 > (Results.size()));
            // Entry has now been cleaned-up, can use it to process
            ID = Results[ch3 - 1].ID;
        }
        else
            // Entry was good to start with, can use it to process
            ID = Results[ch3 - 1].ID;
    }
        // If only one contact found, by default, it is the selection
    else if (Results.size() == 1) {
        ID = Results[0].ID;
    }
    else {
        cout << "\nIf you know the contact you wish to edit, please enter the corresponding ID number: ";
        cin >> ID;
    }
    if (!addressbook.searchID(ID, data))
        cout << "\n**The address book is empty.**\n";
    else {
        if (data.ID == ID) {
            cout << "We have a match! " << data.ID << " is an existing contact ID number." << endl;
            cout << endl << "Here is the data for the contact you have selected: \n";
            addressbook.printNode(data);

            cout << "\nIs this the contact you wish to edit? Enter Y for yes or N for no: ";
            // Check for non-integer selection.
            cin >> choice2;
            if (choice2 == 'Y' || choice2 == 'y') {
                Contact newdata(data);              // Use copy constructor to create duplicate
                do {
                    cout << "\nThe following is a list of fields that can be edited: " << endl << endl;
                    cout << "1)  First Name\n";
                    cout << "2)  Middle Name\n";
                    cout << "3)  Last Name\n";
                    cout << "4)  Company Name\n";
                    cout << "5)  Home Phone\n";
                    cout << "6)  Office Phone\n";
                    cout << "7)  Email\n";
                    cout << "8)  Mobile Number\n";
                    cout << "9)  Street Address\n";
                    cout << "10) City\n";
                    cout << "11) State\n";
                    cout << "12) Zip Code\n";
                    cout << "13) Country\n";
                    cout << "14) Affiliates\n";

                    cout << "\nPlease make a selection in the range of 1 through 14: ";
                    cin >> ch1;
                    cout << endl;

                    //modify data in new node
                    switch (ch1) {
                        case 1:
                            cout << "The current first name: " << data.First << endl;
                            cout << "Please enter the new first name: ";
                            cin.ignore();
                            getline(cin, newdata.First);
                            break;
                        case 2:
                            cout << "The current middle name: " << data.Middle << endl;
                            cout << "Please enter the new middle name: ";
                            cin.ignore();
                            getline(cin, newdata.Middle);
                            break;
                        case 3:
                            cout << "The current last name: " << data.Last << endl;
                            cout << "Please enter the new last name: ";
                            cin.ignore();
                            getline(cin, newdata.Last);
                            break;
                        case 4:
                            cout << "The current company name: " << data.Company << endl;
                            cout << "Please enter the new company name: ";
                            cin.ignore();
                            getline(cin, newdata.Company);
                            break;
                        case 5:
                            cout << "The current home phone: " << data.HomePhone << endl;
                            cout << "Please enter the new home phone: ";
                            cin.ignore();
                            getline(cin, newdata.HomePhone);
                            break;
                        case 6:
                            cout << "The current office phone: " << data.OfficePhone << endl;
                            cout << "Please enter the new office phone: ";
                            cin.ignore();
                            getline(cin, newdata.OfficePhone);
                            break;
                        case 7:
                            cout << "The current email: " << data.Email << endl;
                            cout << "Please enter the new email: ";
                            cin.ignore();
                            getline(cin, newdata.Email);
                            break;
                        case 8:
                            cout << "The current mobile number: " << data.MobileNo << endl;
                            cout << "Please enter the new mobile number: ";
                            cin.ignore();
                            getline(cin, newdata.MobileNo);
                            break;
                        case 9:
                            cout << "The current street address: " << data.StreetAddress << endl;
                            cout << "Please enter the new street address: ";
                            cin.ignore();
                            getline(cin, newdata.StreetAddress);
                            break;
                        case 10:
                            cout << "The current city: " << data.City << endl;
                            cout << "Please enter the new city: ";
                            cin.ignore();
                            getline(cin, newdata.City);
                            break;
                        case 11:
                            cout << "The current state: " << data.State << endl;
                            cout << "Please enter the new state: ";
                            cin.ignore();
                            getline(cin, newdata.State);
                            break;
                        case 12:
                            cout << "The current zip code: " << data.ZipCode << endl;
                            cout << "Please enter the new zip code: ";
                            cin.ignore();
                            getline(cin, newdata.ZipCode);
                            break;
                        case 13:
                            cout << "The current country: " << data.Country << endl;
                            cout << "Please enter the new country: ";
                            cin.ignore();
                            getline(cin, newdata.Country);
                            break;
                        case 14:
                            if (data.AffiliateList.size() == 0) {
                                cout << "\nThere are currently no affiliates associated with this contact.\n";
                                cout << "\nWould you like to add affiliates to the contact's record?" << endl
                                     << "Enter 'Y' to add an affiliate: ";
                                cin >> choice7;
                                if (choice7 == 'Y' || choice7 == 'y') {
                                    do {
                                        cout << "You have chosen to add an affiliate. " << endl;
                                        affFirst.erase();
                                        affLast.erase();
                                        affMobNo.erase();
                                        affEmail.erase();
                                        cout << "Please enter the affiliates first name: ";
                                        cin >> affFirst;
                                        cout << "Please enter the affiliates last name: ";
                                        cin >> affLast;
                                        cout << "Would you like to add a mobile number and email for this affiliate?"
                                             << endl << "Enter Y or N: ";
                                        cin >> choice8;
                                        if (choice8 == 'Y' || choice8 == 'y') {
                                            cout << "Please enter the affiliates mobile number: ";
                                            cin >> affMobNo;
                                            cout << "Please enter the affiliates email: ";
                                            cin >> affEmail;
                                        }
                                        Affiliate newAffiliate(affFirst, affLast, affMobNo, affEmail);
                                        newdata.AffiliateList.push_back(newAffiliate);
                                        cout << "Would you like to add another affiliate to add to the contact's record?"
                                                << endl << "Enter Y or N: ";
                                        cin >> choice7;
                                    } while (choice7 == 'Y' || choice7 == 'y');
                                }
                                else {
                                    cout << "\nYou have chosen not to add any contacts.\n";
                                }
                            }
                            else {
                                cout << "\nThese are the current Affiliates associated with this contact: \n" << endl;
                                for (int i = 0; i < data.AffiliateList.size(); i++) {
                                    std::cout << i + 1 << ")  " << data.AffiliateList[i].getFirst() << " "
                                              << data.AffiliateList[i].getLast();
                                    if (data.AffiliateList[i].getMobileNo() != "") {
                                        std::cout << ", " << data.AffiliateList[i].getMobileNo();
                                    }
                                    if (data.AffiliateList[i].getEmail() != "") {
                                        std::cout << ", " << data.AffiliateList[i].getEmail() << ";" << endl;
                                    } else {
                                        std::cout << ";" << endl;
                                    }
                                }
                                cout << "\nWould you like to edit or add affiliates to the contact's record?" << endl
                                     << "Enter 'A' to add an affiliate or 'E' to edit an existing affiliate: ";
                                cin >> choice4;
                                if (choice4 == 'A' || choice4 == 'a') {
                                    do {
                                        cout << "\nYou have chosen to add an affiliate. " << endl;
                                        affFirst.erase();
                                        affLast.erase();
                                        affMobNo.erase();
                                        affEmail.erase();
                                        cout << "\nPlease enter the affiliates first name: ";
                                        cin >> affFirst;
                                        cout << "Please enter the affiliates last name: ";
                                        cin >> affLast;
                                        cout << "\nWould you like to add a mobile number and email for this affiliate?"
                                             << endl << "Enter Y or N: ";
                                        cin >> choice5;
                                        if (choice5 == 'Y' || choice5 == 'y') {
                                            cout << "\nPlease enter the affiliates mobile number: ";
                                            cin >> affMobNo;
                                            cout << "Please enter the affiliates email: ";
                                            cin >> affEmail;
                                        }
                                        Affiliate newAffiliate(affFirst, affLast, affMobNo, affEmail);
                                        newdata.AffiliateList.push_back(newAffiliate);
                                        cout
                                                << "Would you like to add another affiliate to add to the contact's record?"
                                                << endl << "Enter Y or N: ";
                                        cin >> choice6;
                                    } while (choice6 == 'Y' || choice6 == 'y');
                                } else if (choice4 == 'E' || choice4 == 'e') {
                                    do {
                                        cout << "\nYou have chosen to edit an affiliate. " << endl
                                             << "\nIf you see the affiliate you wish to edit, please enter the corresponding number 1) thru "
                                             << data.AffiliateList.size() << "): ";

                                        while (!(cin >> ch2)) {
                                            cin.clear();
                                            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                                            cout << "\nThat was not a valid choice!\n";
                                            cout << "\nIf you see the affiliate you wish to edit, please enter the corresponding number 1) thru "
                                                 << data.AffiliateList.size() << "): ";
                                        }

                                        if (ch2 < 1 || ch2 > (data.AffiliateList.size())) {
                                            do {
                                                cin.clear();
                                                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                                                cout << "\nPlease limit your selection from 1) thru "
                                                     << data.AffiliateList.size() << "): ";
                                                cin >> ch2;
                                            } while (ch2 < 1 || ch2 > (data.AffiliateList.size()));
                                        }

                                        affFirst.erase();
                                        affLast.erase();
                                        affMobNo.erase();
                                        affEmail.erase();

                                        cout << "\nThe current affiliate first name: "
                                             << data.AffiliateList[ch2 - 1].getFirst() << endl;
                                        cout << "Please enter the new affiliate first name: ";
                                        cin >> affFirst;
                                        newdata.AffiliateList[ch2 - 1].setFirst(affFirst);
                                        cout << "\nThe current affiliate last name: "
                                             << data.AffiliateList[ch2 - 1].getLast()
                                             << endl;
                                        cout << "Please enter the new affiliate last name: ";
                                        cin >> affLast;
                                        newdata.AffiliateList[ch2 - 1].setLast(affLast);
                                        cout << "\nWould you like to edit the mobile number or email for this affiliate?"
                                             << endl
                                             << "Enter Y or N: ";
                                        cin >> choice5;
                                        if (choice5 == 'Y' || choice5 == 'y') {
                                            cout << "\nThe current affiliate mobile number: "
                                                 << data.AffiliateList[ch2 - 1].getMobileNo() << endl;
                                            cout << "Please enter the new affiliate mobile number: ";
                                            cin >> affMobNo;
                                            newdata.AffiliateList[ch2 - 1].setMobileNo(affMobNo);
                                            cout << "\nThe current affiliate email: "
                                                 << data.AffiliateList[ch2 - 1].getEmail() << endl;
                                            cout << "Please enter the new affiliate email: ";
                                            cin >> affEmail;
                                            newdata.AffiliateList[ch2 - 1].setEmail(affEmail);
                                        }

                                        cout << "\nHere is the newly modified affiliate list for this contact: \n\n";
                                        for (int i = 0; i < newdata.AffiliateList.size(); i++) {
                                            std::cout << i + 1 << ")  " << newdata.AffiliateList[i].getFirst() << " "
                                                      << newdata.AffiliateList[i].getLast();
                                            if (newdata.AffiliateList[i].getMobileNo() != "") {
                                                std::cout << ", " << newdata.AffiliateList[i].getMobileNo();
                                            }
                                            if (newdata.AffiliateList[i].getEmail() != "") {
                                                std::cout << ", " << newdata.AffiliateList[i].getEmail() << ";" << endl;
                                            } else {
                                                std::cout << ";" << endl;
                                            }
                                        }
                                        cout << "\nWould you like to edit another affiliate on the contact's record?"
                                             << endl << "Enter Y or N: ";
                                        cin >> choice6;
                                    } while (choice6 == 'Y' || choice6 == 'y');
                                } else
                                    cout << "You have chosen not to edit or add any affiliates" << endl;
                            }
                            break;
                        default:
                            cout << "\nThat was not a valid selection.\n";
                            cin.clear();                                    // Clears the buffer for mis-typed entry
                            break;
                    }
                    cout << endl << "Would you like to edit another field for this contact?" << endl
                         << "Enter Y or N: ";
                    cin >> choice2;
                } while (choice2 == 'Y' || choice2 == 'y');
                addressbook.remove(data);
                addressbook.insert(newdata);

                cout << "\n\nThis is the contact with the updated information: \n";
                addressbook.printNode(newdata);
            }
            else {
                cout << "\nPlease make another selection.\n";
            }
        }
        else
            cout << "There is no number '" << ID << "' associated with any contact" << endl;
    }
}

void deleteContact(AVLTree& addressbook) {
// Deletes a designated contact from the address book

    char ans;
    int ID;
    Contact Result;

    if (addressbook.size() == 0) {
        cout << "\n**The address book is empty.**\n\n";
        return;
    } else {
        cout << "The following is the current list of contacts in the address book: " << endl;
        addressbook.printTree();
        cout << endl << "Please select the contact you wish to delete and enter the ID number: ";

        // Check for non-integer selection.
        if (!(cin >> ID)) {
            cin.clear();
            cin.ignore(10, '\n');
            cout << "That was not a valid ID number, please enter numbers only." << endl;
        }
        // Check for integer choice out-of-range or bad number.
        else if (ID < 99999999 || ID > 1000000000) {
            cout << "There is no ID number " << ID << endl << endl;
        }
        // Proceed with deletion of valid contact ID
        else {
            // Perform search using ID
            addressbook.searchID(ID, Result);
            cout << "\nYou have chosen to delete the following contact: \n\n";
            addressbook.printNode(Result);
            // Confirm deletion request, execute if confirmed, else do nothing
            cout << "\n\nAre you sure you want to delete this contact?: ";
            cin >> ans;
            if (ans == 'Y' || ans == 'y') {
                addressbook.remove(Result);
                cout << "\nID number " << ID << " has been deleted from the address book" << endl;
            } else
                cout << "\nNo contact was deleted.\n";
        }
    }
}

void searchContactID(AVLTree& addressbook) {
// Search address book based on contact ID number

    int ID;
    Contact Result;

    cout << endl << "Please enter an ID number that you would like to search for: ";

    // Test for incorrect entry of ID number
    while (!(cin >> ID)) {
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cout << "\nThat was not a valid choice!\n";
        // Offer up the entire address book if the number is entered wrong
        cout << "\nThe following is the current list of contacts in the address book: " << endl;
        addressbook.printTree();
        cout << "\nIf you see the affiliate you wish to edit, please enter the corresponding ID number: ";
    }
    if (ID < 99999999 || ID > 1000000000) {
        do {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "\nThat was not a valid choice!\n";
            // Offer up the entire address book if the number is entered wrong
            cout << "\nThe following is the current list of contacts in the address book: " << endl;
            addressbook.printTree();
            cout << "\nIf you see the affiliate you wish to edit, please enter the corresponding ID number: ";
            cin >> ID;

        } while (ID < 99999999 || ID > 1000000000);
    }
    cout << endl;

    if (!addressbook.searchID(ID, Result))
        cout << "\n**The address book is empty.**\n";
    else {
        if (Result.ID == ID) {
            cout << "We have a match! " << Result.ID << " is an existing contact ID number." << endl;
            cout << endl << "Here is the data for the contact you have selected: \n";
            addressbook.printNode(Result);
        } else
            cout << "There is no ID number '" << ID << "' associated with any contact" << endl;
    }
}

void searchContact(AVLTree& addressbook) {
// Search address book for any name or number field in the contact

    string Str, str;
    vector<Contact> Results;

    cout << endl << "Please enter a name or number that you would like to search for: ";
    cin.clear();
    cin.ignore();
    getline(cin, Str);
    str = Str;

    // Convert the search name to lower case for user entry robustness
    transform(str.begin(), str.end(), str.begin(), ::tolower);

    if (!addressbook.search(str, Results))
        cout << "\n**The address book is empty.**\n";

    else {
        if (Results.size() > 0) {
            cout << "\n'" << Str << "' has existing matches with the following " << Results.size() << " Contacts: \n";
            for (int i = 0; i < Results.size(); i++) {
                cout << addressbook.printNode(Results[i]) << endl;
            }
            cout << endl;
        } else
            cout << "\nThere is no such word or number associated with any contact" << endl;
    }
}

void readContactList(AVLTree& addressbook) {
// Reads in the initial contact list from a file

    int ch1, IDtag, i, j, k, l;
    string inFileName, firstName, s;
    ifstream inputFile;

    // Offer input options and request selection
    cout << "\n1) Read data from a user specified file.";
    cout << "\n2) Read data from a system defined data file.";

    cout << "\n\nPlease enter a 1 or 2 indicating your selection: ";

    // Check incoming selection for valid character type
    while (!(cin >> ch1)) {
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cout << "\nThat was not a valid choice!\n";
        cout << "\nIf you see the affiliate you wish to edit, please enter the corresponding number 1) or 2): ";
    }

    // Check that selection is either a 1 or 2
    if (ch1 < 1 || ch1 > 2) {
        do {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "\nPlease limit your selection from 1) or 2) ";
            cin >> ch1;
        } while (ch1 < 1 || ch1 > 2);
    }

    // Execute the file read to a user specified input data file
    if (ch1 == 1) {
        cout << endl << "Please enter the file name and path for the input data: ";
        cin.ignore();
        getline(cin, inFileName);
        inputFile.open(inFileName);
        if(!inputFile)
            cout << "\nError opening file, please recheck file name and path." << endl;
    }
    // Execute the file read from a system defined input data file
    else {
        inputFile.open("contacts.txt");
        if(!inputFile)
            cout << "\nError opening file, please recheck file name and path." << endl;
    }

    // Read in the contact data
    getline(inputFile, firstName);
    while (inputFile) {
        Contact data;
        data.First = firstName;
        getline(inputFile, data.Middle);
        getline(inputFile, data.Last);
        getline(inputFile, data.Company);
        getline(inputFile, data.HomePhone);
        getline(inputFile, data.OfficePhone);
        getline(inputFile, data.Email);
        getline(inputFile, data.MobileNo);
        getline(inputFile, data.StreetAddress);
        getline(inputFile, data.City);
        getline(inputFile, data.State);
        getline(inputFile, data.ZipCode);
        getline(inputFile, data.Country);

       // Read in affiliate information for the contact - if there is any
        while (inputFile) {
            string affFirst, affLast, affMobNo, affEmail, ss("");
            if (inputFile.peek() != '|') {              // check to see if end of address book entry
                getline(inputFile, affFirst, ' ');      // read in the affiliate first name, stop at first blank space
                s.clear();
                ss.clear();
                getline(inputFile, s);                  // read in the rest of the line including last name, mobile, email
                for (i = 0; i < s.length(); i++) {      // step through line to eliminate commas and semicolons
                    if (s[i] == ' ' || s[i] == ';') {   // remove blanks and semicolons from string
                        continue;
                    } else if (s[i] == ',') {           // substitute blanks for commas in string
                        ss += ' ';
                    } else {
                        ss += s[i];                     // add character to string if not a comma, blank or semicolon
                    }
                }

                j = 0;
                affLast = "";
                while (ss[j] && (ss[j] != ' ')) {       // add char to affiliate last-name string until blank read
                    affLast += ss[j];
                    j++;
                }

                k = 0;
                affMobNo = "";
                k = j + 1;
                while (ss[k] && (ss[k] != ' ')) {       // add char to affiliate mobile string until bank read
                    affMobNo += ss[k];
                    k++;
                }

                l = 0;
                affEmail = "";
                l = k + 1;
                while (ss[l] && (ss[l] != '\n')) {      // add char to affiliate email string until new line character
                    affEmail += ss[l];
                    l++;
                }

                Affiliate newAffiliate(affFirst, affLast, affMobNo, affEmail);  // create new affiliate
                data.AffiliateList.push_back(newAffiliate);                     // add new affiliate to  contact vector
            }
            else {
                inputFile.get();                        // if end of entry, read and eat the '|' character
                break;                                  // exit the read affiliate while loop
            }
        }
        inputFile.get();                                // read and eat the new line character

        IDtag = (rand()% 890000001) + 100000000;        // create a random number of 9 digits in length for the id
        data.ID = IDtag;                                // set the contact id number
        addressbook.insert(data);                       // add contact to address book

        inputFile.peek();
        if (inputFile.peek() == '|')                    // look for end of contact delimiter '|' and eat the character
            getline(inputFile, s);
        getline(inputFile, firstName);                  // read next contact first-name if it exists, otherwise loop exits
    }
    inputFile.close();
}

void writeContactList(AVLTree& addressbook) {
// Writes modified address book to a designated file

    int ch1;
    string outFileName;
    ofstream outputFile;

    // Offer output options and request selection
    cout << "\n1) Write data to new data file.";
    cout << "\n2) Write data to original system defined data file.";

    cout << "\n\nPlease enter a 1 or 2 indicating your selection: ";

    // Check incoming selection for valid character type
    while (!(cin >> ch1)) {
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cout << "\nThat was not a valid choice!\n";
        cout << "\nIf you see the affiliate you wish to edit, please enter the corresponding number 1) or 2): ";
    }

    // Check that selection is either a 1 or 2
    if (ch1 < 1 || ch1 > 2) {
        do {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "\nPlease limit your selection from 1) or 2) ";
            cin >> ch1;
        } while (ch1 < 1 || ch1 > 2);
    }

    // Execute the file write to a user specified output data file
    if (ch1 == 1) {
        cout << "\nPlease enter a file name and path for the output data: ";
        cin.ignore();
        getline(cin, outFileName);
        outputFile.open(outFileName);
        cout << endl;
        if(!outputFile)
            cout << "Error opening file." << endl;
    }
    // Execute the file write to the original system defined input data file
    else {
        outputFile.open("contacts.txt");
        cout << endl;
        if(!outputFile)
            cout << "Error opening file." << endl;
    }

    // Write the address book to the output file
    addressbook.writeTree(outputFile);
    outputFile.close();
    exit(0);
}

void processSelection(AVLTree& addressbook) {
// Displays the main menu and prompts user for selection

    char choice;

    do {
        // Display the menu and request a valid selection.
        displayMenu();

        // Enter user's menu selection
        cin >> choice;

        // Process the user's valid menu selection.
        switch(choice) {
            case '1': cout << endl << "The Address Book is as follows: " << endl;
                addressbook.printTree();
                break;
            case '2': cout << endl << "You have chosen to add a contact " << endl << endl;
                addContact(addressbook);
                break;
            case '3': cout << endl << "You have chosen to update/edit a contact " << endl << endl;
                editContact(addressbook);
                break;
            case '4': cout << endl << "You have chosen to delete a contact " << endl << endl;
                deleteContact(addressbook);
                break;
            case '5': cout << endl << "You have chosen to search by ID Number " << endl << endl;
                searchContactID(addressbook);
                break;
            case '6': cout << endl << "You have chosen to search by Contact " << endl << endl;
                searchContact(addressbook);
                break;
            case '7': cout << endl << "You have chosen to read in a list of contacts from a file " << endl << endl;
                readContactList(addressbook);
                break;
            case '8': cout << endl << "You have chosen to write the address book to a file and exit the program "
                           << endl << endl;
                writeContactList(addressbook);
                break;
            case '9': cout << endl << "You have chosen to exit without saving your data, Goodbye! " << endl << endl;
                exit(0);
            default: cout << endl << choice << " is not a valid menu choice!" << endl
                          << "Please make a selection in the range of 1 through 8: " << endl;
        }
    }
    while (choice != 9);
}

#endif /* Functions_h */
