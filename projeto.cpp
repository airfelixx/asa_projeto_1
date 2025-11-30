#include <iostream>
#include <list>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

// Mapeia char por índice
// P=0, N=1, A=2, B=3, T=4
int typeId(char c){
    if (c == 'P') return 0;
    if (c == 'N') return 1;
    if (c == 'A') return 2;
    if (c == 'B') return 3;
    return 4;
}


//unordered_map<string, int> affinityMap;

struct aminoacid{
    int _pot;
    int _type;
};


int main(){
    
    int Af[5][5]= {
    //   P N A B T
        {1,3,1,3,1}, // P
        {5,1,0,1,1}, // N
        {0,1,0,4,1}, // A
        {1,3,2,3,1}, // B
        {1,1,1,1,1}  // T
    };
    
   /* affinityMap.insert({"PP", 1});
    affinityMap.insert({"PN", 3});
    affinityMap.insert({"PA", 1});
    affinityMap.insert({"PB", 3});
    affinityMap.insert({"NP", 5});
    affinityMap.insert({"NN", 1});
    affinityMap.insert({"NA", 0});
    affinityMap.insert({"NB", 1});
    affinityMap.insert({"AP", 0});
    affinityMap.insert({"AN", 1});
    affinityMap.insert({"AA", 0});
    affinityMap.insert({"AB", 4});
    affinityMap.insert({"BP", 1});
    affinityMap.insert({"BN", 3});
    affinityMap.insert({"BA", 2});
    affinityMap.insert({"BB", 3});*/

    int n;
    cin >> n;

    vector<int> pots;
    pots.reserve(n);
    for(int i = 0; i < n; ++i){
        int p;
        cin >> p;
        pots.push_back(p);
    }
    string types;
    cin >> types;   

    vector<aminoacid> protein;
    protein.reserve(n+2);
    protein.push_back({1,typeId('T')});

    for(int i=0; i<n; ++i){
        aminoacid a;
        a._pot = pots[i];
        a._type = typeId(types[i]);
        protein.push_back(a);
    }
    protein.push_back({1,typeId('T')});

    return 0;
}
