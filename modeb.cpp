//
//  modeb.cpp
//  281Project4
//
//  Created by Guangyu Wang on 11/29/16.
//  Copyright © 2016 Guangyu Wang. All rights reserved.
//

#include "modeb.h"
#include <math.h>
#include <sstream>
using namespace std;

void modeb(vector<pair<int,int>>& coordinates)
{
    vector<bool> checked(coordinates.size(),false);
    //vector<double> distances(coordinates.size(),0);
    vector<size_t> tsp(coordinates.size(),0);
    
    tsp[0]=0;
    checked[0]=true;
    size_t it=0;
	size_t next=0;
    int count=1;
    double mindistance;
    double totaldistance=0;
    double d;
    while(count!=(int)coordinates.size())
    {
        mindistance=numeric_limits<double>::infinity();
        for(size_t i=0;i<coordinates.size();i++)
        {
            if(!checked[i])
            {
                d=distance(coordinates[it], coordinates[i]);
                if (d<mindistance)
                {
                    mindistance=d;
                    next=i;
                }
            }
        }
        tsp[count]=next;
        checked[next]=true;
	it=next;
        //distances[count-1]=mindistance;
        //totaldistance+=mindistance;
        
        count++;
    }
    //distances[coordinates.size()]= distance(coordinates[tsp[0]], coordinates[tsp[coordinates.size()]]);
    //double minchange=0;
    double change =0;
    int mini=1;
    int minj=(int)tsp.size()-1;
    size_t temp;
    while(minj-mini>0)
    {
        temp=tsp[minj];
        tsp[minj]=tsp[mini];
        tsp[mini]=temp;
        minj--;
        mini++;
        
    }
    //    vector<size_t> swap;
    //int countt=0;
    //    do
    //    {
    //minchange=0;
    //    swap=tsp;
    //    for(size_t i=0 ; i<tsp.size();i++)
    //        tsp[i]=swap[tsp.size()-i-1];
    
 
        for(int i=0; i<(int)tsp.size()-3;i++)
        {
         
            //minchange = 0;
            for(int j=i+2; j<(int)tsp.size()-1;j++)
            {
                change = distance(coordinates[tsp[i]], coordinates[tsp[j]]) + distance(coordinates[tsp[i+1]], coordinates[tsp[j+1]])
                - distance(coordinates[tsp[i]], coordinates[tsp[i+1]])-distance(coordinates[tsp[j]], coordinates[tsp[j+1]]);
                
                if(change<0)
                {
                    //minchange=change;
                    mini = i+1;
                    minj = j;
		while(minj-mini>0)
            	{
                temp=tsp[minj];
                tsp[minj]=tsp[mini];
                tsp[mini]=temp;
                minj--;
                mini++;
                
            	}
		
                }
            }
            
            
        }

    
    //swap mini, minj
    totaldistance=0;
    for(size_t i=0;i<tsp.size()-1;i++)
    {
        totaldistance+=distanceb(coordinates[tsp[i]],coordinates[tsp[i+1]]);
    }
    totaldistance+=distance(coordinates[tsp[0]], coordinates[tsp[tsp.size()-1]]);
    //        swap=tsp;
    //        for(size_t t=0;t<minj-mini;t++)
    //        {
    //            tsp[minj-t]=swap[t];
    //        }
    //        cout<<countt++<<endl;
    //}while (minchange<0);
    
    ostringstream out;
    out<<setprecision(2);
    out<<fixed;
    out<<totaldistance<<'\n';
    for(size_t i=0; i<tsp.size();i++)
        out<<tsp[i]<<" ";
    out<<'\n';
    cout<<out.str();
    return;
}


double distanceb(pair<int,int>& a, pair<int,int>& b)
{
    double x = a.first -b.first;
    double y = a.second-b.second;
    return sqrt(x*x+y*y);
    //    return sqrt(((double)a.first -(double)b.first)*((double)a.first -(double)b.first)+(((double)a.second-(double)b.second)*(((double)a.second-(double)b.second))));
}
