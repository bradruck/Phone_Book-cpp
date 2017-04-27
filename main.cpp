//
//  main.cpp
//  CSCI 2421 Final Project
//
//  Created by Bradley Ruck on 4/15/16.
//  Copyright © 2016 Bradley Ruck. All rights reserved.
//

#include <iostream>
#include <time.h>
#include "AVLTree.h"
#include "AVLNode.h"
#include "Functions.h"

void processSelection(AVLTree& addressbook);

int main() {
    AVLTree addressbook;
    
    srand( static_cast<unsigned int>(time(0)));
    
    processSelection(addressbook);
    
    return 0;
}