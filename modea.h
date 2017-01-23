//
//  Header.h
//  281Project4
//
//  Created by Guangyu Wang on 11/28/16.
//  Copyright © 2016 Guangyu Wang. All rights reserved.
//

#ifndef Header_h
#define Header_h
#include <iomanip>
using namespace std;

void modea(vector<pair<int,int>>& coordinates);
double distance(pair<int,int>& a, pair<int,int>& b);
bool iswild(pair<int,int>& a);
bool isborder(pair<int,int>& a);
#endif /* Header_h */
