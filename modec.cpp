//
//  modec.cpp
//  281Project4
//
//  Created by Guangyu Wang on 12/3/16.
//  Copyright © 2016 Guangyu Wang. All rights reserved.
//

#include "modec.h"

using namespace  std;

class things
{
public:
    vector<vector<double>> distancem;
    vector<size_t> finalpath;
    vector<size_t> path;
    deque<size_t> unused;
    double pathdistance;
    double upperbound;
    int count;
    things(vector<pair<int,int>>& coordinates)
    {
        count=0;
        distancem.resize(coordinates.size());
        for(size_t i=0;i<coordinates.size();i++)
            distancem[i].resize(coordinates.size());
        
        for(size_t i=0;i<coordinates.size();i++)
        {
            for(size_t j=0;j<coordinates.size();j++)
            {
                distancem[i][j]=distance(coordinates[i],coordinates[j]);
                distancem[j][i]=distancem[i][j];
            }
        }
        finalpath.resize(coordinates.size());
        path.push_back(0);
        for(unsigned i=1; i<coordinates.size();i++)
            unused.push_back(i);
        pathdistance=0;
        
        
        
        
        
        
        //find upperbound
        vector<bool> checked(coordinates.size(),false);
        vector<size_t> tsp(coordinates.size(),0);
        tsp[0]=0;
        checked[0]=true;
        size_t it=0;
        unsigned count=1;
        size_t next=0;
        double mindistance;
        double totaldistance=0;
        while(count!=coordinates.size())
        {
            mindistance=numeric_limits<double>::infinity();
            for(size_t i=0;i<coordinates.size();i++)
            {
                if(!checked[i])
                {
                    if (distancem[i][it]<mindistance)
                    {
                        mindistance=distancem[i][it];
                        next=i;
                    }
                }
            }
            tsp[count]=next;
            checked[next]=true;
            count++;
            it=next;
        }
        
        double change =0;
        
        vector<size_t> swap;
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
        
        for(unsigned i=0; i<tsp.size()-3;i++)
        {
            for(unsigned j=i+2; j<tsp.size()-1;j++)
            {
                change = distancem[tsp[i]][tsp[j]]+distancem[tsp[i+1]][tsp[j+1]]-distancem[tsp[i]][tsp[i+1]]-distancem[tsp[j+1]][tsp[j]];
                //                change = distance(coordinates[tsp[i]], coordinates[tsp[j]]) + distance(coordinates[tsp[i+1]], coordinates[tsp[j+1]])
                //                - distance(coordinates[tsp[i]], coordinates[tsp[i+1]]) -distance(coordinates[tsp[j]], coordinates[tsp[j+1]]);
                if(change<0)
                {
                    reverse(tsp.begin()+i+1,tsp.begin()+j+1);
                    //                    swap=tsp;
                    //
                    //                    for(int t=0;t<j-i;t++)
                    //                    {
                    //                        tsp[j-t]=swap[i+t+1];
                    //                    }
                    //
                }
            }
        }
        finalpath=tsp;
        totaldistance=0;
        for(size_t i=0;i<tsp.size()-1;i++)
        {
            totaldistance+=distancem[tsp[i]][tsp[i+1]];
        }
        totaldistance+=distancem[tsp[0]][tsp[tsp.size()-1]];
        upperbound=totaldistance;
    }
    
};

bool promising(things& work)
{
    //calculate path diatance
    //    work.pathdistance=0;
    //    for(unsigned i=1; i<work.path.size();i++)
    //    {
    //        work.pathdistance+=work.distancem[work.path[i]][work.path[i-1]];
    //    }
    
    
    
    
    
    
    //find mst
    vector<bool> checked(work.unused.size(),false);
    vector<double> distances(work.unused.size(),numeric_limits<double>::infinity());
    distances[0]=0;
    int it1;
    //int last =0;
    unsigned count =0;
    double mstdis=0;
    double minhead=numeric_limits<double>::infinity();
    double minend=numeric_limits<double>::infinity();
    for (unsigned i=0; i<work.unused.size();i++)
    {
        if(work.distancem[work.path.front()][work.unused[i]]<minhead)
            minhead=work.distancem[work.path.front()][work.unused[i]];
        if(work.distancem[work.path.back()][work.unused[i]]<minend)
            minend=work.distancem[work.path.back()][work.unused[i]];
    }
    while(count!=work.unused.size())
    {
        it1 = -1;
        for (unsigned i=0; i<work.unused.size();i++)
        {
            if(checked[i]==false && it1 == -1)
                it1=(int)i;
            if (checked[i]==false &&distances[i]<distances[it1])
                it1=(int)i;
        }
        checked[it1]=true;
        mstdis+=distances[it1];
        count++;
        for (unsigned i=0; i<work.unused.size();i++)
        {
            if(checked[i]==false)
            {
                if(work.distancem[work.unused[i]][work.unused[it1]]<distances[i])
                    distances[i]=work.distancem[work.unused[i]][work.unused[it1]];
            }
        }
    }
    //    cout<<"Comparing"<<work.pathdistance+mstdis+minhead+minend<<" and "<<work.upperbound<<endl;
    //    cout<<"pathdistance"<<work.pathdistance<<" "<<mstdis<<" "<<minhead<<" "<<minend<<endl;
    if(work.pathdistance+mstdis+minhead+minend<work.upperbound)
        //if(work.pathdistance+mstdis<work.upperbound)
        return true;
    else return false;
}

void genperms(things& work)
{
    //    work.count++;
    //    if(work.count>30000)
    //        exit(2);
    //    cout<<work.pathdistance<<"  "<<work.unused.size()<<endl;
    if (work.unused.empty())
    {
        //        work.pathdistance=0;
        //        for(unsigned i=1; i<work.path.size();i++)
        //        {
        //            work.pathdistance+=work.distancem[work.path[i]][work.path[i-1]];
        //        }
        //        work.pathdistance+=work.distancem[work.path[0]][work.path[work.path.size()-1]];
        if(work.upperbound>work.pathdistance)
        {
            work.finalpath=work.path;
            work.upperbound=work.pathdistance;
            work.upperbound+=work.distancem[work.finalpath.front()][work.finalpath.back()];

        }
        return;
    }
    if (!promising(work))
        return;
    for(size_t k=0;k!=work.unused.size();k++)
    {
        work.path.push_back(work.unused.front());
        work.pathdistance+=work.distancem[work.path[work.path.size()-1]][work.path[work.path.size()-2]];
        work.unused.pop_front();
        
        // cout<<work.pathdistance<<"  "<<work.unused.size()<<" k="<<k<<endl;
        
        
        genperms(work);
        work.unused.push_back(work.path.back());
        work.pathdistance-=work.distancem[work.path[work.path.size()-1]][work.path[work.path.size()-2]];
        work.path.pop_back();
    }
    
}


void modec(vector<pair<int,int>>& coordinates)
{
    //create distance matrix
    things work(coordinates);
    
    genperms(work);
    cout<<setprecision(2);
    cout<<fixed;
    //work.upperbound+=work.distancem[work.finalpath.front()][work.finalpath.back()];
    cout<<work.upperbound<<endl;
    cout<<work.finalpath[0];
    for(unsigned i=1;i<coordinates.size();i++)
        cout<<" "<<work.finalpath[i];
    cout<<endl;
    
    
    
}
