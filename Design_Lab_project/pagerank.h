
#ifndef pagerank_h
#define pagerank_h
#pragma once
#include <string>
#include<map>
#include <unordered_map>
using namespace std;
const int webnums=33;

struct node{
    string websitename;
    int num;
    int numofedges=1;
    map<int , string> webgraphs;
    map<string, int>keywords;
    vector<node>webbies;
    int impressions=1;
    int clicks=1;
    float CTR=1;
    float pageRank;
    float score;
};

vector<double> pageRank(unordered_map<string,vector<string>>&adjlist,
                        unordered_map<string,int>&edgesin,unordered_map<string,int>& hashing,
                        unordered_map<int,string>&reversing){
    vector<vector<double>> rank(webnums, vector<double>(webnums,0));
    for(int i=0; i<webnums; i++){rank[0][i]=1./double(webnums);}
    double answer=0;
    for(int i=1; i<webnums; i++){
        for(int j=0; j<webnums; j++){
            answer=0;
            for(auto&u:adjlist[reversing[j]]){
                answer+=rank[i-1][j] / double(edgesin[reversing[j]]);
            }
            rank[i][j]=answer;
        }
    }
    return rank[webnums-1];
}

#endif /* pagerank_h */
