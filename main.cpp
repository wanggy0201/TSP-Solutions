
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string>
#include <fstream>
#include <vector>

#include "modea.h"
#include "modeb.h"
#include "modec.h"
using namespace std;

int main(int argc, char** argv)
{
    std::ios_base::sync_with_stdio(false);

//    ifstream input;
//    input.open("sample-c.txt");
    
    
    vector<pair<int,int>> coordinates;
    int c;
    int idx=0;
    int numcages;
    string mode;
    static struct option longopts[] =
    {
        {"help", no_argument, nullptr, 'h'},
        {"mode", required_argument, nullptr, 'm'},
        {nullptr, 0, nullptr, 0}
    };
    while((c=getopt_long(argc, argv, "hm:", longopts, &idx))!= -1)
    {
        switch (c)
        {
            case 'h':
                cout<<"There is no help here"<<endl;
                exit(0);
                break;
                
            case 'm':
                mode.assign(optarg);
                break;
                
           
        }
    }
    
    int tfirst;
    int tsecond;
    cin>>numcages;
    //input>>numcages;
    for(int i=0; i<numcages; i++)
    {
        cin>>tfirst>>tsecond;
        //input>>tfirst>>tsecond;
        coordinates.push_back(pair<int,int>{tfirst,tsecond});
    }
    
    
    
    if (mode=="MST")
        modea(coordinates);
    else if (mode=="FASTTSP")
        modeb(coordinates);
    else if (mode=="OPTTSP")
        modec(coordinates);
    
    
    
    
    return 0;
}
