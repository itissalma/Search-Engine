
#ifndef searching_h
#define searching_h
#include <string>
#include <vector>
#include "pagerank.h"
using namespace std;
void ORfunction(string searchword, vector<string> &words, int &casee){
    string word1, word2;
    int size1, size2;
    bool continuee=false, space=false;
    for(int i=0; i<searchword.size(); i++){
        if(i+1<searchword.size()&&searchword[i]=='O'&&searchword[i+1]=='R'){
            size1=i-2;
            size2=i+3;
            continuee=true;
        }
    }
    if(continuee==true){
    for(int j=0; j<=size1; j++){
        word1+=searchword[j];
    }
    words.push_back(word1);
    int k=0;
    for(int j=size2; j<searchword.size(); j++){
    word2+=searchword[j];
        k++;
    }
        words.push_back(word2);
        casee=2;
    }
    else{
        if(isalpha(searchword[0])){
            for(int i=0; i<searchword.size();i++){
                if(searchword[i]==' '){
                    size1=i-1;
                    size2=i+1;
                    space=true;
                }
            }
            if(space==true){
            for(int j=0; j<=size1; j++){
                word1+=searchword[j];
            }
            words.push_back(word1);
            int k=0;
            for(int j=size2; j<searchword.size(); j++){
            word2+=searchword[j];
                k++;
            }
                words.push_back(word2);
                casee=2;}
            else{
                words.push_back(searchword);
                casee=3;
            }
        }
        else{
        searchword.erase(searchword.begin());
        searchword.pop_back();
        words.push_back(searchword);
            casee=3;}
    }
}

void ANDfunction(string searchword, vector<string> &words, int &casee){
    string word1, word2;
    int size1, size2;
    bool continuee=false;
    for(int i=0; i<searchword.size(); i++){
        if(i+2<searchword.size()&&searchword[i]=='A'&&searchword[i+1]=='N'&&searchword[i+2]=='D'){
            size1=i-2;
            size2=i+4;
            continuee=true;
        }
    }
    if(continuee==true){
    for(int j=0; j<=size1; j++){
        word1+=searchword[j];
    }
    words.push_back(word1);
    int k=0;
    for(int j=size2; j<searchword.size(); j++){
    word2+=searchword[j];
        k++;
    }

        words.push_back(word2);}
    casee=1;
}
vector<node> getwebpages(node nodes[], int size, vector<string>wordies, int casee, bool &shouldcontinue){
    bool first=false, second=false;
    bool onlyone=false;
    int index1=0, index2=0;
    vector<node>vectorAND, vectorOR, emptyone;
    vector<int>indices1, indices2, indices, indicesboth;

    if(casee==1){
            for(int i=0;i<size; i++){
                if(nodes[i].keywords[wordies[0]]!=0&&nodes[i].keywords[wordies[1]]!=0){
                    indices.push_back(i);
                    onlyone=true;}
            }
            if(onlyone){
            vector<int>::iterator itr;
                for(itr=indices.begin(); itr!=indices.end(); itr++){
                    vectorAND.push_back(nodes[*itr]);
                }
            
                return vectorAND;}
            else {cout<<"sorry, not found :("<<endl; shouldcontinue=false;}
    }
    else if(casee==2){
        for(int i=0;i<size; i++){
            if(nodes[i].keywords[wordies[0]]!=0&&nodes[i].keywords[wordies[1]]!=0){
                indicesboth.push_back(i);
                first=true; second=true;
            }else{
            if(nodes[i].keywords[wordies[0]]!=0){
                indices1.push_back(i);
                first=true;
            }
            if(nodes[i].keywords[wordies[1]]!=0){
                indices2.push_back(i);
                second=true;}
            }}
        vector<int>::iterator itr1;
        vector<int>::iterator itr2;
        
        if(first&&second){
            for(itr1=indicesboth.begin(); itr1!=indicesboth.end(); itr1++)
                vectorOR.push_back(nodes[*itr1]);
            
            for(itr1=indices1.begin(); itr1!=indices1.end(); itr1++)
                vectorOR.push_back(nodes[*itr1]);
            
            for(itr2=indices2.begin(); itr2!=indices2.end(); itr2++)
            vectorOR.push_back(nodes[*itr2]);
            
            shouldcontinue=true;
            return vectorOR;
        }
        else if(first){
            for(itr1=indices1.begin(); itr1!=indices1.end(); itr1++)
            vectorOR.push_back(nodes[*itr1]);
            shouldcontinue=true;
            return vectorOR;
        } else if(second){
            for(itr2=indices2.begin(); itr2!=indices2.end(); itr2++)
            vectorOR.push_back(nodes[*itr2]);
            shouldcontinue=true;
            return vectorOR;
        }else {cout<<"there aren't any available websites"<<endl; shouldcontinue=false;}
    }else if(casee==3){
        for(int i=0;i<size; i++){
            if(nodes[i].keywords[wordies[0]]!=0){
                indices.push_back(i);
                onlyone=true;}
        }
        if(onlyone){
        vector<int>::iterator itr;
        for(itr=indices.begin(); itr!=indices.end(); itr++)
        vectorAND.push_back(nodes[*itr]);
            shouldcontinue=true;
            return vectorAND;}
        else {cout<<"sorry, not found :(("<<endl; shouldcontinue=false;}
    }
    return emptyone;
}
bool operator >(node x,node y)
{
    return x.score>y.score;
}
bool operator <(node x,node y)
{
    return x.score<y.score;
}
bool operator ==(node x,node y)
{
    return x.score==y.score;
}

#endif /* searching_h */
