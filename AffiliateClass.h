//
//  AffiliateClass.h
//  CSCI 2421 Final Project
//
//  Created by Bradley Ruck on 4/15/16.
//  Copyright © 2016 Bradley Ruck. All rights reserved.
//

#ifndef AffiliateClass_h
#define AffiliateClass_h

#include<string>

using namespace std;

class Affiliate
{
public:
    Affiliate() { Initialize(); }
    Affiliate(string AffFir, string AffLas, string AffMNo, string AffEma) { New(AffFir, AffLas, AffMNo, AffEma); }
    ~Affiliate() { }
    
    //Mutator/Accessor Methods
    void setFirst(string AffFir) { (AffiliateFirst = AffFir); }
    string getFirst() { return AffiliateFirst; }
    void setLast(string AffLas) { (AffiliateLast = AffLas); }
    string getLast() { return AffiliateLast; }
    void setMobileNo(string AffMNo) { (AffiliateMobileNo = AffMNo); }
    string getMobileNo() { return AffiliateMobileNo; }
    void setEmail(string AffEma) { (AffiliateEmail = AffEma); }
    string getEmail() { return AffiliateEmail; }
    
    //Initialize values when constructor called
    void Initialize() {
        AffiliateFirst = " ";
        AffiliateLast = " ";
        AffiliateMobileNo = " ";
        AffiliateEmail = " ";
    }
    
    void New(string AffFir, string AffLas, string AffMNo, string AffEma) {
        AffiliateFirst = AffFir;
        AffiliateLast = AffLas;
        AffiliateMobileNo = AffMNo;
        AffiliateEmail = AffEma;
    }
    
private:
    
    string AffiliateFirst;
    string AffiliateLast;
    string AffiliateMobileNo;
    string AffiliateEmail;
    
};

#endif /* AffiliateClass_h */
