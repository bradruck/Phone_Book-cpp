//
//  AVLNode.h
//  CSCI 2421 Final Project
//
//  Created by Bradley Ruck on 4/15/16.
//  Copyright © 2016 Bradley Ruck. All rights reserved.
//

#ifndef AVLNode_H
#define AVLNode_H

#include <iostream>
#include <string>
#include <vector>
#include "AffiliateClass.h"

using namespace std;

// Node Internal Data
struct Contact{
    int ID;
    string First;
    string Middle;
    string Last;
    string Company;
    string HomePhone;
    string OfficePhone;
    string Email;
    string MobileNo;
    string StreetAddress;
    string City;
    string State;
    string ZipCode;
    string Country;
    vector<Affiliate> AffiliateList;
};

class AVLNode {
public:
    AVLNode();
    AVLNode(Contact data, AVLNode* parent);
    AVLNode(Contact data, AVLNode* left, AVLNode* right);
    AVLNode(Contact data, AVLNode* left, AVLNode* right, int balance);
    AVLNode(const Contact node);
    ~AVLNode();

    void setBalance(int bal);
    void setLeft(AVLNode* left);
    void setRight(AVLNode* right);
    
    int getBalance() const;
    const AVLNode* const getLeft() const;
    const AVLNode* const getRight() const;
    int const getID() const;
    string const getFirst() const;
    string const getMiddle() const;
    string const getLast() const;
    string const getCompany() const;
    string const getHomePhone() const;
    string const getOfficePhone() const;
    string const getEmail() const;
    string const getMobileNo() const;
    string const getStreetAddress() const;
    string const getCity() const;
    string const getState() const;
    string const getZipCode() const;
    string const getCountry() const;
    
    bool operator < (const AVLNode& AVLNode) const;


    //friend std::ostream& operator << (std::ostream& out, const AVLNode& AVLNode);
    
    /* Tree structure pointers */
    AVLNode* left;
    AVLNode* right;
    AVLNode* parent;
    
    /* AVL Balance Factor */
    int balance;
    
     /* Node Internal Data */
    Contact data, newdata;
};


#endif
