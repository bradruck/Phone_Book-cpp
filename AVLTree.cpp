//
//  AVLTree.cpp
//  CSCI 2421 Final Project
//
//  Created by Bradley Ruck on 4/15/16.
//  Copyright © 2016 Bradley Ruck. All rights reserved.
//

#include "AVLTree.h"

#include <sstream>
#include <algorithm>

/*
 * The implementation of this class is completely self-contained with the exception
 * of the provided node class.
 */
AVLTree::AVLTree() {
    this->root = nullptr;
}

AVLTree::AVLTree(const AVLTree& tree) {
    this->copyTree(tree);
}

AVLTree::~AVLTree() {
    delete this->root;
}

bool AVLTree::copyTree(const AVLTree& tree) {
    if ( tree.root == nullptr ) return false;
    this->clearTree();
    this->root = this->copySubtree(tree.root);
    return true;
}

bool AVLTree::insert(Contact newData) {
    //------------------------------------------------------------------------------
    // If the tree is empy, insert a new node; otherwise insert the new data and
    // ensure the tree is rebalanced recursively.
    //------------------------------------------------------------------------------
    if ( this->root == nullptr ) {
        this->root = new AVLNode(newData, nullptr);
    }
    else {
        AVLNode* node = this->root;
        AVLNode* parent = nullptr;
        bool insertComplete = false;
        
        //------------------------------------------------------------------------------
        // Determine the correct position to insert the new data. If the new value is
        // already stored, return false since there can only be one unique key.
        //------------------------------------------------------------------------------
        while ( !insertComplete ) {
            if ( node->data.ID == newData.ID ) return false;
            
            parent = node;
            bool leftOp = node->data.ID > newData.ID;
            node = leftOp ? node->left : node->right;
            
            //------------------------------------------------------------------------------
            // If the correct position is determined, add the new node appropriately. This
            // may incur an imbalance in the tree that must then be resolved using one or
            // more node rotations. The node rotations are performed until the balance
            // factor of each node is within the acceptable [-1, 1] bound.
            //------------------------------------------------------------------------------
            if ( node == nullptr ) {
                if ( leftOp ) parent->left = new AVLNode(newData, parent);
                else parent->right = new AVLNode(newData, parent);
                
                this->rebalance(parent);
                insertComplete = true;
            }
        }
    }
    
    return true;
}

bool AVLTree::printBalance() {
    if ( this->root == nullptr ) return false;
    this->printBalance(this->root);
    return true;
}

bool AVLTree::printTree() const {
    if (this->root == nullptr) return false;
    this->printTree(this->root);
    return true;
}

bool AVLTree::writeTree(ostream& outfile) const {
    if (this->root == nullptr) return false;
    this->writeTree(this->root, outfile);
    return true;
}

bool AVLTree::printNode(Contact data) const{
    
    if (this->root == nullptr)
        return false;

    this->printNode(this->root, data);
    return true;
}

unsigned int AVLTree::height() const {
    return this->height(this->root);
}

unsigned int AVLTree::size() const {
    unsigned int count = 0;
    this->size(this->root, count);
    return count;
}

bool AVLTree::remove(Contact existingData) {
    if (this->root == nullptr) return false;
    
    AVLNode* node = this->root;
    AVLNode* parent = this->root;
    AVLNode* deleteAVLNode = nullptr;
    AVLNode* child = this->root;
    
    //------------------------------------------------------------------------------
    // Determine the node that must be removed from the tree. This is simply a
    // traversal (based on the binary search tree) for the node that should be
    // removed. If the node is not found, then it cannot be removed.
    //------------------------------------------------------------------------------
    while ( child != nullptr ) {
        parent = node;
        node = child;
        child = existingData.ID >= node->data.ID ? node->right : node->left;
        
        if ( existingData.ID == node->data.ID ) deleteAVLNode = node;
    }
    
    //------------------------------------------------------------------------------
    // The node with the provided data was found in the tree. The node must then
    // be manually removed through pointer reassignment.
    //------------------------------------------------------------------------------
    if ( deleteAVLNode != nullptr ) {
        //------------------------------------------------------------------------------
        // Copy operation of the data. This is a slighly more expensive operation
        // (depending on the store data and the overloaded = operator), but simplifes
        // the process of removing the existing node.
        //------------------------------------------------------------------------------
        deleteAVLNode->data = node->data ;
        
        child = node->left != nullptr ? node->left : node->right;
        
        //------------------------------------------------------------------------------
        // The reassignment of the tree incurs the rebalance operation. This will
        // recursively rebalance the tree due to the change in the height based on the
        // removal of the target node. Also perform the parent pointer check to
        // reassign the parent child pointer correctly.
        //------------------------------------------------------------------------------
        if ( this->root->data.ID == existingData.ID) {
            this->root = child;
        }
        else {
            if ( parent->left == node ) parent->left = child;
            else parent->right = child;
            
            this->rebalance(parent);
        }
    }
    else return false;
    
    return true;
}

bool AVLTree::searchID(int ID, Contact &Result) const {
    if (this->root == NULL)
        return false;
    else
        this->searchID(this->root, ID, Result);
        return true;
}

bool AVLTree::search(string str, vector<Contact> &Results) const {
    if (this->root == NULL)
        return false;
    else
        this->search(this->root, str, Results);
        return true;
}

bool AVLTree::clearTree() {
    if ( this->root == NULL ) return false;
    delete this->root;
    return true;
}

std::string AVLTree::preorder() const {
    std::stringstream stream;
    this->preorder(stream, this->root);
    return stream.str();
}

std::string AVLTree::inorder() const {
    std::stringstream stream;
    this->inorder(stream, this->root);
    return stream.str();
}

std::string AVLTree::postorder() const {
    std::stringstream stream;
    this->postorder(stream, this->root);
    return stream.str();
}

std::string AVLTree::toString() const {
    return this->inorder();
}

AVLTree& AVLTree::operator = (const AVLTree& tree) {
    if ( this == &tree ) return *this;
    this->clearTree();
    this->copyTree(tree);
    return *this;
}

std::ostream& operator << (std::ostream& out, const AVLTree& tree) {
    out << tree.toString() << std::endl;
    return out;
}


unsigned int AVLTree::height(AVLNode* node) {
    if ( node == nullptr ) return 0;
    return 1 + std::max(height(node->left), height(node->right));
}

/*
 * Primary re-balance function of the AVL tree implementation. This function
 * extensively uses the standard AVL rotation functions to recursively
 * balance the tree until the balance factor of each node resides within
 * the acceptable bounds of [-1, 1].
 */
void AVLTree::rebalance(AVLNode* node) {
    this->setBalance(node);
    
    //------------------------------------------------------------------------------
    // This sub-tree is left heavy, which means that nodes have to be rotated to
    // the right to balance the load of the lower trees.
    //------------------------------------------------------------------------------
    if ( node->balance == LEFT_HEAVY ) {
        if ( height(node->left->left ) >= height(node->left->right) )
            node = rotateRight(node);
        else node = rotateLeftRight(node);
    }
    //------------------------------------------------------------------------------
    // This sub-tree is right heavy, which means that nodes have to be rotated to
    // the left to balance the load of the lower trees (opposite case from above).
    //------------------------------------------------------------------------------
    else if ( node->balance == RIGHT_HEAVY ) {
        if ( height(node->right->right) >= height(node->right->left) )
            node = rotateLeft(node);
        else node = rotateRightLeft(node);
    }
    
    //------------------------------------------------------------------------------
    // Balance propigation. If an insertion/deletion operation causes a signifiant
    // imbalance within the tree, the changes must be propigated to ensure that
    // the load is evenly distributed and the tree is balanced.
    //------------------------------------------------------------------------------
    if ( node->parent != nullptr ) this->rebalance(node->parent);
    else root = node;
}

/*
 * Set the balance of the current node which represents a sub-tree.
 * The height of both the left and right sub-trees of this node will
 * be recursively determined, then their difference will represent
 * how unbalanced they are.
 */
bool AVLTree::setBalance(AVLNode* node) {
    if ( node == nullptr ) return false;
    node->balance = height(node->right) - height(node->left);
    return true;
}

void AVLTree::printBalance(AVLNode* node) {
    if ( node == nullptr ) return;
    
    this->printBalance(node->left);
    std::cout << node->balance << " ";
    this->printBalance(node->right);
}

void AVLTree::printNode(AVLNode* node, Contact data) const {
    //cout << boolalpha;
    if (node == nullptr) return;

    std::cout << endl << "ID#: " << data.ID << endl << "First name: " << data.First << endl << "Middle name: "
              << data.Middle << endl << "Last name: " << data.Last << endl << "Company name: " << data.Company << endl
              << "Home phone: " << data.HomePhone << endl << "Office phone: " << data.OfficePhone << endl << "Email: "
              << data.Email << endl << "Mobile number: " << data.MobileNo << endl << "Street address: "
              << data.StreetAddress << endl << "City: " << data.City << endl << "State: " << data.State << endl
              << "Zip code: " << data.ZipCode << endl << "Country: " << data.Country << endl;
    std::cout << "Affiliates: " << endl;
    for (int i = 0; i < data.AffiliateList.size(); i++) {
        std::cout << "  " << data.AffiliateList[i].getFirst() << " " << data.AffiliateList[i].getLast();
        if (data.AffiliateList[i].getMobileNo() != "") {
            std::cout << ", " << data.AffiliateList[i].getMobileNo();
        }
        if (data.AffiliateList[i].getEmail() != "") {
            std::cout << ", " << data.AffiliateList[i].getEmail() << ";" << endl;
        } else {
            std::cout << ";" << endl;
        }
    }
}

void AVLTree::printTree(AVLNode* node) const{
    if (node == nullptr) return;
    
    this->printTree(node->left);
    std::cout << endl << "ID#: " << node->data.ID << endl << "First name: " << node->data.First << endl << "Middle name: "
              << node->data.Middle << endl << "Last name: " << node->data.Last << endl << "Company name: "
              << node->data.Company << endl << "Home phone: " << node->data.HomePhone << endl << "Office phone: "
              << node->data.OfficePhone << endl << "Email: " << node->data.Email << endl << "Mobile number: "
              << node->data.MobileNo << endl <<  "Street address: " << node->data.StreetAddress << endl << "City: "
              << node->data.City << endl << "State: " << node->data.State << endl << "Zip code: " << node->data.ZipCode
              << endl << "Country: " << node->data.Country<< endl;
    std::cout << "Affiliates: " << endl;
    for (int i=0; i < node->data.AffiliateList.size(); i++) {
        std::cout << "  " << node->data.AffiliateList[i].getFirst() << " " << node->data.AffiliateList[i].getLast();
        if (node->data.AffiliateList[i].getMobileNo() != "") {
            std::cout << ", " << node->data.AffiliateList[i].getMobileNo();
        }
        if (node->data.AffiliateList[i].getEmail() != "") {
            std::cout << ", " << node->data.AffiliateList[i].getEmail() << ";" << endl;
        }
        else {
            std::cout << ";" << endl;
        }
    }
    this->printTree(node->right);
}

void AVLTree::writeTree(AVLNode* node, ostream& outfile) const{
    if ( node == nullptr ) return;
    
    this->writeTree(node->left, outfile);
    outfile << node->data.First << endl << node->data.Middle << endl << node->data.Last << endl << node->data.Company
            << endl << node->data.HomePhone << endl << node->data.OfficePhone << endl << node->data.Email << endl
            << node->data.MobileNo << endl << node->data.StreetAddress << endl << node->data.City << endl
            << node->data.State << endl << node->data.ZipCode << endl << node->data.Country << endl;
    for (int i=0; i < node->data.AffiliateList.size(); i++) {
        outfile << node->data.AffiliateList[i].getFirst() << " " << node->data.AffiliateList[i].getLast();
        if (node->data.AffiliateList[i].getMobileNo() != "") {
            outfile << ", " << node->data.AffiliateList[i].getMobileNo();
        }
        if (node->data.AffiliateList[i].getEmail() != "") {
            outfile << ", " << node->data.AffiliateList[i].getEmail() << ";" << endl;
        }
        else {
            outfile << ";" << endl;
        }
    }
    outfile << "|" << endl;
    this->writeTree(node->right, outfile);
}

void AVLTree::searchID(AVLNode* node, int ID, Contact &Result) const {

    if (node == nullptr) return;

    if (ID == node->data.ID) {
        Result = node->data;
    }
    else if (ID < node->data.ID) {
        if (&left == NULL)
            return;
        else
            return this->searchID(node->left, ID, Result);
    }
    else if (ID > node->data.ID) {
        if (&right == NULL)
            return;
        else
            return this->searchID(node->right, ID, Result);
    }
    return;
}

void AVLTree::search(AVLNode* node ,string str, vector<Contact> &Results) const {

    string First, Middle, Last, Company, HomePhone, OfficePhone, Email, MobileNo, StreetAddress,
            City, State, ZipCode, Country, affFir, affLast, affMobileNo, affEmail;
    vector<Contact>::iterator itr;

    if (node == nullptr) return;

    this->search(node->left, str, Results);

    // Convert all of the contact search targets to lower case
    First = node->data.First;
    transform(First.begin(), First.end(), First.begin(), ::tolower);
    Middle = node->data.Middle;
    transform(Middle.begin(), Middle.end(), Middle.begin(), ::tolower);
    Last = node->data.Last;
    transform(Last.begin(), Last.end(), Last.begin(), ::tolower);
    Company = node->data.Company;
    transform(Company.begin(), Company.end(), Company.begin(), ::tolower);
    HomePhone = node->data.HomePhone;
    transform(HomePhone.begin(), HomePhone.end(), HomePhone.begin(), ::tolower);
    OfficePhone = node->data.OfficePhone;
    transform(OfficePhone.begin(), OfficePhone.end(), OfficePhone.begin(), ::tolower);
    Email = node->data.Email;
    transform(Email.begin(), Email.end(), Email.begin(), ::tolower);
    MobileNo = node->data.MobileNo;
    transform(MobileNo.begin(), MobileNo.end(), MobileNo.begin(), ::tolower);
    StreetAddress = node->data.StreetAddress;
    transform(StreetAddress.begin(), StreetAddress.end(), StreetAddress.begin(), ::tolower);
    City = node->data.City;
    transform(City.begin(), City.end(), City.begin(), ::tolower);
    State = node->data.State;
    transform(State.begin(), State.end(), State.begin(), ::tolower);
    ZipCode = node->data.ZipCode;
    transform(ZipCode.begin(), ZipCode.end(), ZipCode.begin(), ::tolower);
    Country = node->data.Country;
    transform(Country.begin(), Country.end(), Country.begin(), ::tolower);

    // Compare search-string to each separate field in the contact
    // Then search Results vector using lambda to prevent addition of duplicate contacts
    if (str == First) {
        itr = find_if(Results.begin(), Results.end(),
                      [&node](const Contact &data) -> int { return data.ID == node->data.ID; });
        if (itr != Results.end())
            return;
        else
            Results.push_back(node->data);
    }
    else if (str == Middle) {
        itr = find_if(Results.begin(), Results.end(),
                      [&node](const Contact &data) -> int { return data.ID == node->data.ID; });
        if (itr != Results.end())
            return;
        else
            Results.push_back(node->data);
    }
    else if (str == Last) {
        itr = find_if(Results.begin(), Results.end(),
                      [&node](const Contact &data) -> int { return data.ID == node->data.ID; });
        if (itr != Results.end())
            return;
        else
            Results.push_back(node->data);
    }
    else if (str == Company) {
        itr = find_if(Results.begin(), Results.end(),
                      [&node](const Contact &data) -> int { return data.ID == node->data.ID; });
        if (itr != Results.end())
            return;
        else
            Results.push_back(node->data);
    }
    else if (str == HomePhone) {
        itr = find_if(Results.begin(), Results.end(),
                      [&node](const Contact &data) -> int { return data.ID == node->data.ID; });
        if (itr != Results.end())
            return;
        else
            Results.push_back(node->data);
    }
    else if (str == OfficePhone) {
        itr = find_if(Results.begin(), Results.end(),
                      [&node](const Contact &data) -> int { return data.ID == node->data.ID; });
        if (itr != Results.end())
            return;
        else
            Results.push_back(node->data);
    }
    else if (str == Email) {
        itr = find_if(Results.begin(), Results.end(),
                      [&node](const Contact &data) -> int { return data.ID == node->data.ID; });
        if (itr != Results.end())
            return;
        else
            Results.push_back(node->data);
    }
    else if (str == MobileNo) {
        itr = find_if(Results.begin(), Results.end(),
                      [&node](const Contact &data) -> int { return data.ID == node->data.ID; });
        if (itr != Results.end())
            return;
        else
            Results.push_back(node->data);
    }
    else if (str == StreetAddress) {
        itr = find_if(Results.begin(), Results.end(),
                      [&node](const Contact &data) -> int { return data.ID == node->data.ID; });
        if (itr != Results.end())
            return;
        else
            Results.push_back(node->data);
    }
    else if (str == City) {
        itr = find_if(Results.begin(), Results.end(),
                      [&node](const Contact &data) -> int { return data.ID == node->data.ID; });
        if (itr != Results.end())
            return;
        else
            Results.push_back(node->data);
    }
    else if (str == State) {
        itr = find_if(Results.begin(), Results.end(),
                      [&node](const Contact &data) -> int { return data.ID == node->data.ID; });
        if (itr != Results.end())
            return;
        else
            Results.push_back(node->data);
    }
    else if (str == ZipCode) {
        itr = find_if(Results.begin(), Results.end(),
                      [&node](const Contact &data) -> int { return data.ID == node->data.ID; });
        if (itr != Results.end())
            return;
        else
            Results.push_back(node->data);
    }
    else if (str == Country) {
        itr = find_if(Results.begin(), Results.end(),
                      [&node](const Contact &data) -> int { return data.ID == node->data.ID; });
        if (itr != Results.end())
            return;
        else
            Results.push_back(node->data);
    }

    // Cycle through the affiliate list looking for search matches
    for (int i = 0; i < node->data.AffiliateList.size(); i++) {

        // Convert all of the affiliate search targets to lower case
        affFir = node->data.AffiliateList[i].getFirst();
        transform(affFir.begin(), affFir.end(), affFir.begin(), ::tolower);
        affLast = node->data.AffiliateList[i].getLast();
        transform(affLast.begin(), affLast.end(), affLast.begin(), ::tolower);
        affMobileNo = node->data.AffiliateList[i].getMobileNo();
        transform(affMobileNo.begin(), affMobileNo.end(), affMobileNo.begin(), ::tolower);
        affEmail = node->data.AffiliateList[i].getEmail();
        transform(affEmail.begin(), affEmail.end(), affEmail.begin(), ::tolower);

        // Compare search-string to each separate field in the contact's affiliates list
        // Then search Results vector using lambda to prevent addition of duplicate contacts
        if (str == affFir) {
            itr = find_if(Results.begin(), Results.end(),
                          [&node](const Contact &data) -> int { return data.ID == node->data.ID; });
            if (itr != Results.end())
                return;
            else
                Results.push_back(node->data);
        }
        else if (str == affLast) {
            itr = find_if(Results.begin(), Results.end(),
                          [&node](const Contact &data) -> int { return data.ID == node->data.ID; });
            if (itr != Results.end())
                return;
            else
                Results.push_back(node->data);
        }
        else if (str == affMobileNo) {
            itr = find_if(Results.begin(), Results.end(),
                          [&node](const Contact &data) -> int { return data.ID == node->data.ID; });
            if (itr != Results.end())
                return;
            else
                Results.push_back(node->data);
        }
        else if (str == affEmail) {
            itr = find_if(Results.begin(), Results.end(),
                          [&node](const Contact &data) -> int { return data.ID == node->data.ID; });
                if (itr != Results.end())
                    return;
                else
                    Results.push_back(node->data);
        }
    }
    this->search(node->right, str, Results);
    return;
}

unsigned int AVLTree::height(AVLNode* node) const {
    if ( node == nullptr ) return 0;
    else {
        unsigned int leftHeight = this->height(node->left);
        unsigned int rightHeight = this->height(node->right);
        
        if ( leftHeight > rightHeight ) return leftHeight + 1;
        else return rightHeight + 1;
    }
}

void AVLTree::size(AVLNode* node, unsigned int& count) const {
    if ( node == nullptr ) return;
    
    this->size(node->left, count);
    count++;
    this->size(node->right, count);
}

void AVLTree::preorder(std::stringstream& out, AVLNode* node) const {
    if ( node == nullptr ) return;
    
    out << node->data.ID << " ";
    this->preorder(out, node->left);
    this->preorder(out, node->right);
}

void AVLTree::inorder(std::stringstream& out, AVLNode* node) const {
    if ( node == nullptr ) return;
    
    this->inorder(out, node->left);
    out << node->data.ID << " ";
    this->inorder(out, node->right);
}

void AVLTree::postorder(std::stringstream& out, AVLNode* node) const {
    if ( node == nullptr ) return;
    
    this->postorder(out, node->left);
    this->postorder(out, node->right);
    out << node->data.ID << " ";
}

/*
 * Manual reassignment of the internal pointers for the standard left
 * rotation. This function also updates the balance of the rotated
 * sub-trees and updates the parent pointer correctly.
 */
AVLNode* AVLTree::rotateLeft(AVLNode* node) {
    if ( node == nullptr ) return nullptr;
    
    //------------------------------------------------------------------------------
    // In the common notation, node is labeld 'a', its right is 'b' and that
    // childs right is 'c'
    //------------------------------------------------------------------------------
    AVLNode* b = node->right;
    b->parent = node->parent;
    node->right = b->left;
    
    //------------------------------------------------------------------------------
    // Set the nodes right parent to be the current node.
    //------------------------------------------------------------------------------
    if ( node->right != nullptr ) node->right->parent = node;
    
    //------------------------------------------------------------------------------
    // Manual pointer reassignment.
    //------------------------------------------------------------------------------
    b->left = node;
    node->parent = b;
    
    //------------------------------------------------------------------------------
    // Determine the correct parent for the new root. This has to be done as a
    // check of both children from the uknown parent (because we do not know if
    // the current base rotation node is the left or right child of the tree above)
    //------------------------------------------------------------------------------
    if ( b->parent != nullptr ) {
        if ( b->parent->right == node ) b->parent->right = b;
        else b->parent->left = b;
    }
    
    //------------------------------------------------------------------------------
    // Update the balance values based on the height of the sub-trees for the
    // newly rotated nodes.
    //------------------------------------------------------------------------------
    this->setBalance(node);
    this->setBalance(b);
    
    //------------------------------------------------------------------------------
    // Return the new root of the rotated sub-tree.
    //------------------------------------------------------------------------------
    return b;
}

/*
 * Manual reassignment of the internal pointers for the standard right
 * rotation. This function also updates the balance of the rotated
 * sub-trees and updates the parent pointer correctly.
 */
AVLNode* AVLTree::rotateRight(AVLNode* node) {
    if ( node == nullptr ) return nullptr;
    
    //------------------------------------------------------------------------------
    // In the common notation, node is labeld 'a', its left is 'b' and that
    // childs left is 'c'
    //------------------------------------------------------------------------------
    AVLNode* b = node->left;
    b->parent = node->parent;
    node->left = b->right;
    
    //------------------------------------------------------------------------------
    // Set the nodes left parent to be the current node.
    //------------------------------------------------------------------------------
    if ( node->left != nullptr ) node->left->parent = node;
    
    //------------------------------------------------------------------------------
    // Manual pointer reassignment.
    //------------------------------------------------------------------------------
    b->right = node;
    node->parent = b;
    
    //------------------------------------------------------------------------------
    // Determine the correct parent for the new root. This has to be done as a
    // check of both children from the uknown parent (because we do not know if
    // the current base rotation node is the left or right child of the tree above)
    //------------------------------------------------------------------------------
    if ( b->parent != nullptr ) {
        if ( b->parent->right == node ) b->parent->right = b;
        else b->parent->left = b;
    }
    
    //------------------------------------------------------------------------------
    // Update the balance values based on the height of the sub-trees for the
    // newly rotated nodes.
    //------------------------------------------------------------------------------
    this->setBalance(node);
    this->setBalance(b);
    
    //------------------------------------------------------------------------------
    // Return the new root of the rotated sub-tree.
    //------------------------------------------------------------------------------
    return b;
}

/*
 * Perform a compound rotation based on the existing rotation
 * functions. The returned node is the parent of the newly
 * rotated sub-tree. Rotate left then right.
 */
AVLNode* AVLTree::rotateLeftRight(AVLNode* node) {
    node->left = this->rotateLeft(node->left);
    return this->rotateRight(node);
}

/*
 * Perform a compound rotation based on the existing rotation
 * functions. The returned node is the parent of the newly
 * rotated sub-tree. Rotate right then left.
 */
AVLNode* AVLTree::rotateRightLeft(AVLNode* node) {
    node->right = this->rotateRight(node->right);
    return this->rotateLeft(node);
}

AVLNode* AVLTree::copySubtree(AVLNode* node) {
    if ( node == nullptr ) return nullptr;
    
    AVLNode* left = nullptr;
    AVLNode* right = nullptr;
    AVLNode* parent = nullptr;
    
    //------------------------------------------------------------------------------
    // Recursively copy the left sub-tree.
    //------------------------------------------------------------------------------
    if ( node->left == nullptr ) left = nullptr;
    else left = this->copySubtree(node->left);
    
    //------------------------------------------------------------------------------
    // Recursively copy the right sub-tree.
    //------------------------------------------------------------------------------
    if ( node->right == nullptr ) right = nullptr;
    else right = this->copySubtree(node->right);
    
    //------------------------------------------------------------------------------
    // Create a new parent based on the new left and right constructed sub-trees.
    //------------------------------------------------------------------------------
    parent = new AVLNode(node->data, left, right, node->balance);
    return parent;
}
