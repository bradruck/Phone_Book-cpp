//
//  AVLNode.cpp
//  CSCI 2421 Final Project
//
//  Created by Bradley Ruck on 4/15/16.
//  Copyright © 2016 Bradley Ruck. All rights reserved.
//

#include "AVLNode.h"

using namespace std;

AVLNode::AVLNode() {
    this->data.ID = 0;
    this->data.First = "No First";
    this->data.Middle = "No Middle";
    this->data.Last = "No Last";
    this->data.Company = "No Company";
    this->data.HomePhone = "No Home Phone";
    this->data.OfficePhone = "No Office Phone";
    this->data.Email = "No Email";
    this->data.MobileNo = "No Mobile Number";
    this->data.StreetAddress = "No Street Address";
    this->data.City = "No City";
    this->data.State = "No State";
    this->data.ZipCode = "No Zip Code";
    this->data.Country = "No Country";
    this->data.AffiliateList;
    this->balance = 0;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}

AVLNode::AVLNode(Contact data, AVLNode* parent) {
    this->data = data;
    this->balance = 0;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = parent;
}

AVLNode::AVLNode(Contact data, AVLNode* left, AVLNode* right) {
    this->data = data;
    this->balance = 0;
    this->left = left;
    this->right = right;
    this->parent = nullptr;
}

AVLNode::AVLNode(Contact data, AVLNode* left, AVLNode* right, int balance) {
    this->data = data;
    this->balance = balance;
    this->left = left;
    this->right = right;
    this->parent = nullptr;
}

AVLNode::AVLNode(const Contact data) {
    this->data.ID = data.ID;
    this->data.First = data.First;
    this->data.Middle = data.Middle;
    this->data.Last = data.Last;
    this->data.Company = data.Company;
    this->data.HomePhone = data.HomePhone;
    this->data.OfficePhone = data.OfficePhone;
    this->data.Email = data.Email;
    this->data.MobileNo = data.MobileNo;
    this->data.StreetAddress = data.StreetAddress;
    this->data.City = data.City;
    this->data.State = data.State;
    this->data.ZipCode = data.ZipCode;
    this->data.Country = data.Country;
    this->balance = 0;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}

AVLNode::~AVLNode() {
    delete this->left;
    delete this->right;
}

void AVLNode::setBalance(int bal) {
    this->balance = bal;
}

void AVLNode::setLeft(AVLNode* left) {
    this->left = left;
}

void AVLNode::setRight(AVLNode* right) {
    this->right = right;
}

int AVLNode::getBalance() const {
    return this->balance;
}

const AVLNode* const AVLNode::getLeft() const {
    return this->left;
}

const AVLNode* const AVLNode::getRight() const {
    return this->right;
}

int const AVLNode::getID() const {
    return this->data.ID;
}

string const AVLNode::getFirst() const {
    return this->data.First;
}

string const AVLNode::getMiddle() const {
    return this->data.Middle;
}

string const AVLNode::getLast() const {
    return this->data.Last;
}

string const AVLNode::getCompany() const {
    return this->data.Company;
}

string const AVLNode::getHomePhone() const {
    return this->data.HomePhone;
}

string const AVLNode::getOfficePhone() const {
    return this->data.OfficePhone;
}

string const AVLNode::getEmail() const {
    return this->data.Email;
}

string const AVLNode::getMobileNo() const {
    return this->data.MobileNo;
}

string const AVLNode::getStreetAddress() const {
    return this->data.StreetAddress;
}

string const AVLNode::getCity() const {
    return this->data.City;
}

string const AVLNode::getState() const {
    return this->data.State;
}

string const AVLNode::getZipCode() const {
    return this->data.ZipCode;
}

string const AVLNode::getCountry() const {
    return this->data.Country;
}

bool AVLNode::operator < (const AVLNode& AVLNode) const {
    if ( this->data.ID < AVLNode.data.ID ) return true;
    return false;
}

/*friend std::ostream& operator << (std::ostream& out, const AVLNode& AVLNode) {
 (out << &AVLNode.data.ID << endl << &AVLNode.data.First << endl << &AVLNode.data.Middle << endl << &AVLNode.data.Last << endl << &AVLNode.data.Company << endl << &AVLNode.data.HomePhone << endl << &AVLNode.data.OfficePhone << endl << &AVLNode.data.MobileNo << endl << &AVLNode.data.StreetAddress << endl << &AVLNode.data.City << endl << &AVLNode.data.State << endl << &AVLNode.data.ZipCode << endl << &AVLNode.data.Country << endl << endl);
 return out;
}*/


