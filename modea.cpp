//
//  modea.cpp
//  281Project4
//
//  Created by Guangyu Wang on 11/28/16.
//  Copyright © 2016 Guangyu Wang. All rights reserved.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <limits>
#include "modea.h"
#include <sstream>
using namespace std;

void modea(vector<pair<int,int>>& coordinates)
{
    vector<bool> checked(coordinates.size(),false);
    vector<double> distances(coordinates.size(), numeric_limits<double>::infinity());
    distances[0]=0;
    vector<int> parent(coordinates.size(),-1);
    
    vector<bool> wild(coordinates.size(),false);
    vector<bool> border(coordinates.size(),false);
    bool hasborder = false;
    bool haswild = false;
    bool hasout = false;
    for (size_t i=0; i< wild.size(); i++)
    {
        if (iswild(coordinates[i]))
        {
            wild[i]=true;
            haswild=true;
        }
        else if (isborder(coordinates[i]))
        {
                 border[i]=true;
            hasborder=true;
        }
        else hasout=true;
    }
    if(hasborder==false && haswild==true&&hasout==true)
    {
        cerr<<"Cannot Construct MST"<<endl;
        exit(1);
    }
    
    int it1;
    //int last=0;
    double d;
    int count =0;
    double totaldistance=0;
    bool found = false;
    while(!found)
    {
        found = true;
        it1=-1;
        //find vertex with least distance
        for(size_t i =0; i<coordinates.size();i++)
        {
            if (checked[i]==false && it1==-1)
                it1=(int)i;
            if (checked[i]==false && distances[i]<distances[it1])
                it1=(int)i;
        }
        
        checked[it1]=true;
        totaldistance+=distances[it1];
        //parent[it1]=last;
        //last=it1;
        count++;
        if (wild[it1])
        {
            for(size_t i = 0; i<coordinates.size(); i++)
            {
                if (checked[i]==false)
                {
                    found = false;
                if (wild[i] || border[i])
                {
                    d = distance(coordinates[i], coordinates[it1]);
                    if (d<distances[i])
                    {
                        distances[i]=d;
                        parent[i]=it1;
                    }
                }
                }
            }
        }
        else if (border[it1])
        {
            for(size_t i = 0; i<coordinates.size(); i++)
            {
                if (checked[i]==false)
                {
                    found = false;
                    d = distance(coordinates[i], coordinates[it1]);
                    if (d<distances[i])
                    {
                        distances[i]=d;
                        parent[i]=it1;
                    }
                }
            }
        }
        else
        {
            for(size_t i = 0; i<coordinates.size(); i++)
            {
                if (checked[i]==false)
                {
                    found = false;
                if (!wild[i])
                {
                    d = distance(coordinates[i], coordinates[it1]);
                    if (d<distances[i])
                    {
                        distances[i]=d;
                        parent[i]=it1;
                    }
                }
                }
            }
        }
    } ostringstream out;
    out<<setprecision(2);
    out<<fixed;
    out<<totaldistance<<'\n';
    for(int i=1; i<(int)coordinates.size(); i++)
    {
        if(parent[i]>i)
            out<<i<<" "<<parent[i]<<'\n';
        else
            out<<parent[i]<<" "<<i<<'\n';
    }
	cout<<out.str();
    
    return;
}

double distance(pair<int,int>& a, pair<int,int>& b)
{
double x = a.first -b.first;
    double y = a.second-b.second;
    return sqrt(x*x+y*y);
    //    return sqrt(((double)a.first -(double)b.first)*((double)a.first -(double)b.first)+(((double)a.second-(double)b.second)*(((double)a.second-(double)b.second))));
}

bool iswild(pair<int,int>& a)
{
    if (a.first<0 && a.second<0)
        return true;
    else return false;
}

bool isborder(pair<int,int>& a)
{
    if (a.first==0 && a.second<=0)
        return true;
    else if (a.first<=0 && a.second==0)
        return true;
    else return false;
}

