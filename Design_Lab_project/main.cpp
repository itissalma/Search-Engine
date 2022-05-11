#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <vector>
#include <list>
#include <sstream>
#include <string>
#define V vector
#include <map>
#include <unordered_map>
#include <queue>
#include "searching.h"
#include "pagerank.h"
using namespace std;
struct dexy{
    string stringy;
    int indexy;
};


// handling pagerank:done , impressions:done , CTR:done , score:done, sorting websites by score:done, output to files after updating (impressions and CTR):done. THEN FINISH THE USER INTERFACE:done.  :3

int main() {
    
    ifstream webgraph("/Users/salmaaly/Desktop/AUC-xcode/Design_Lab_project/webgraphfile.csv");
    ifstream impressions("/Users/salmaaly/Desktop/AUC-xcode/Design_Lab_project/numofimpressions.csv");
    ifstream CTRfile ("/Users/salmaaly/Desktop/AUC-xcode/Design_Lab_project/CTR.csv");
    
    if(webgraph.fail()) cout<<"not opening"<<endl;
    if(impressions.fail()) cout<<"oh no "<<endl;
    int vertices=webnums;
    //Graph webGraph(vertices);
    
    bool adjmatrix[webnums][webnums]={0};
    node nodes[webnums];
    vector<string> row;
        string line, website, temp;
    map<string, int>websitenamey;
    int count1=1, count=0;
    int lines=0, indy=0, webgraphh=0, index=0;
    string line1, link1, line3, link2;
    int i=0, m=0;
    int flippy=0;
    
    while (getline(webgraph, line1)){
            stringstream ss (line1);
            getline(ss, link1, ',');
        if(flippy<webnums){
            nodes[i].num=count;
            nodes[i].websitename=link1;
        websitenamey[link1]=count;
                count++;
            i++;
            flippy++;}
    }
    string tempwebname, tempimpressions, tempCTR;
    while(impressions.good()){
        getline(impressions, tempwebname, ',');
        getline(impressions, tempimpressions, ',');
        nodes[m].impressions=stoi(tempimpressions);
        //cout<<"the impressions are "<<nodes[m].impressions<<endl;
        m++;
    }
    m=0;
    while(CTRfile.good()){
        getline(CTRfile, tempwebname, ',');
        getline(CTRfile, tempCTR, ',');
        nodes[m].clicks=stoi(tempCTR);
        m++;
    }
    
    webgraph.close();
    webgraph.open("/Users/salmaaly/Desktop/AUC-xcode/Design_Lab_project/webgraphfile.csv");
    if(webgraph.fail())
        cout<<"not opening 2"<<endl;
    int k=0, counting=0;
    int indexy1, indexy2;
    string stringy1, stringy2;
    vector <string>weby;
    unordered_map<string,vector<string>>adjList;
    unordered_map<string,int>inEdges, hash;
    unordered_map<int,string>reverse;
    while (getline(webgraph, line)) {
               row.clear();
               stringstream s(line);
            
               while (getline(s, website, ',')) {
                   weby.push_back(website);
                   //webgraphh++;
               }
        
        if(weby.size()==3){
            indexy1=websitenamey[weby[0]];
            indexy2=websitenamey[weby[1]];
            adjmatrix[indexy1][indexy2]=1;
            adjmatrix[indexy2][indexy1]=1;
            nodes[indexy1].numofedges++;
            nodes[indexy2].numofedges++;
            nodes[indexy1].webgraphs[nodes[indexy1].numofedges]=weby[1];
            nodes[indexy2].webgraphs[nodes[indexy2].numofedges]=weby[0];
            
            adjList[weby[0]].push_back(weby[1]);
            inEdges[weby[1]]++;
            if(!hash[weby[1]]) {
                hash[weby[1]]=hash.size();
                reverse[hash[weby[1]]] = weby[1];
            }
            adjList[weby[1]].push_back(weby[0]);
            inEdges[weby[0]]++;
            if(!hash[weby[0]]) {
                hash[weby[0]]=hash.size();
                reverse[hash[weby[0]]] = weby[0];
            }
        }
        weby.clear();
               count1++;
               lines++;k++;
               
           }

    vector <string>wordss;
    string line2, word;
    int j;
    lines=0;
    
    ifstream keywords("/Users/salmaaly/Desktop/AUC-xcode/Design_Lab_project/keywordfile.csv");
    if(keywords.fail()) cout<<"not opening keyword"<<endl;
    while (getline(keywords, line2)) {
        row.clear();
        stringstream s(line2);
        j=1;
        while (getline(s, word, ',')) {
            //nodes[lines].keywords[j]=word;
            nodes[lines].keywords[word]=j;
                   j++;
        }
               count1++;
        lines++;k++; j++;
               }

    int choice, end1, end2;
    string search;
    vector<string> words;
    vector<double>finalpageRanks;
    finalpageRanks=pageRank(adjList, inEdges, hash, reverse);
    //pageRank(adjmatrix, nodes);
    
    map<int, string>pageScore;
    double score, pageRank;
    double frac1;
    for(int i=0; i<webnums; i++){
        nodes[i].pageRank=finalpageRanks[hash[nodes[i].websitename]];
        nodes[i].CTR=(float)nodes[i].clicks/nodes[i].impressions;
        frac1=(0.1*nodes[i].impressions)/(1+(0.1*nodes[i].impressions));
        nodes[i].score=0.4*nodes[i].pageRank+((1-frac1)*nodes[i].CTR)*0.6;
    }
    
    string word1, word2;
    int casee;
    cout<<"Welcome!\nWhat would you like to do?\n1. New Search\n2. Exit\n\nType in your choice: ";
    cin>>choice;
    cout<<endl;
    int websitechoice;
    int continuechoice;
    //string secondstring;
    vector<node> returnedWPs;
    bool shouldcontinue=true;
    switch (choice) {
        case 1:
        {
            do{do{
                words.clear();
                returnedWPs.clear();
                cout<<"What would you like to search for?\n";
                 //sometimes ignores the first character of the next keyword when the one before is wrong.
                cin.ignore();
                getline(cin, search);
            if(search.find("AND") != string::npos){
                ANDfunction(search, words, casee);
                returnedWPs=getwebpages(nodes, webnums, words, casee, shouldcontinue);
            }
            if(search.find("OR") != string::npos){
                ORfunction(search, words, casee);
                returnedWPs=getwebpages(nodes, webnums, words, casee,shouldcontinue);
            }
            if(search.find("AND") == string::npos&&search.find("OR") == string::npos){
                returnedWPs.clear();
                if(isalpha(search[0])){
                    ORfunction(search, words, casee);
                    returnedWPs=getwebpages(nodes, webnums, words, casee, shouldcontinue);
                }
                else{
                    ORfunction(search, words, casee);
                    returnedWPs=getwebpages(nodes, webnums, words, casee, shouldcontinue);
                }

            }}while(!shouldcontinue);
                
                priority_queue<node> Q;
               
            vector<node>::iterator itty;
            map<int, string>chosenpages;
            int tempclicks, tempimps;
            do{
            cout<<"Your available webpages are "<<endl;
                int w=0, indexy3, indexy4;
            for(itty=returnedWPs.begin(); itty!=returnedWPs.end(); itty++){
                indexy3=(*itty).num;
                nodes[indexy3].impressions++;
                frac1=(0.1*nodes[indexy3].impressions)/(1+(0.1*nodes[indexy3].impressions));
                nodes[indexy3].score=0.4*nodes[indexy3].pageRank+((1-frac1)*nodes[indexy3].CTR)*0.6;
                Q.push((*itty));
                //chosenpages[nodes[indexy3].score]=(*itty).websitename;
            }
                while (!Q.empty()) {
                cout<<w<<" - "<<Q.top().websitename<<endl;
                    returnedWPs[w]=Q.top();
                    Q.pop();
                w++;
                }
                do{
            cout<<"Which one would you like to choose?"<<endl;
            cin>>websitechoice;
                    if(websitechoice>w-1)
                        cout<<"Webpage number is not available "<<endl;
                }while(websitechoice>w-1);
            indexy4=returnedWPs[websitechoice].num;
            nodes[indexy4].clicks++;
            tempclicks=nodes[indexy4].clicks;
            tempimps=nodes[indexy4].impressions;
            nodes[indexy4].CTR=(float)tempclicks/tempimps;
            cout<<"You are now viewing "<<returnedWPs[websitechoice].websitename<<endl<<"Would you like to"<<endl<<"1- Go back to search results\n2- Do a new search\n3- Exit\n";
                cin>>continuechoice;
                
                ofstream impressions("/Users/salmaaly/Desktop/AUC-xcode/Design_Lab_project/numofimpressions.csv");
                ofstream CTRfile("/Users/salmaaly/Desktop/AUC-xcode/Design_Lab_project/CTR.csv");
                for(int i=0; i<webnums; i++){
                    impressions<<nodes[i].websitename<<","<<nodes[i].impressions<<","<<endl;
                    CTRfile<<nodes[i].websitename<<","<<nodes[i].clicks<<","<<endl;
                }
                impressions.close();
                CTRfile.close();
            }while(continuechoice!=3&&continuechoice==1);
                words.clear();
                returnedWPs.clear();
            }while(continuechoice!=3&&continuechoice==2);
           
            break;
        }
            
        default:
            break;
    }
    keywords.close();
    webgraph.close();
    return 0;
}
