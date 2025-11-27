#include <iostream>
#include <list>
#include <unordered_map>
#include <string>

using namespace std;

unordered_map<string, int> affinityMap;

struct aminoacid{
    char _type;
    int _pot;
    int getAffinity(aminoacid other){
        string key = {_type, other._type};
        return affinityMap[key];
    }
};


int main(){
    affinityMap.insert({"PP", 1});
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
    affinityMap.insert({"BB", 3});

    list<aminoacid> protein;
    int n;
    cin >> n;
    for(size_t i=0; i<n; i++){
        int pot;
        aminoacid a;
        cin >> pot;
        a._pot = pot;
        protein.push_back(a);
        cin.ignore();
    }

    for (auto& a : protein){
        char buf;
        cin >> buf;
        a._type = buf;          
    }
    return 0;
}
