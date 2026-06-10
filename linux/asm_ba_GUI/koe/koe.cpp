#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include "koe.h"
using namespace std;

vector<pair<int, int>> iv;
std::unordered_map<int, tietue> taulukko;
std::unordered_map<int, tietue> taulukko2;
vector<pair<int, int>> iv2;
vector<pair<int, int>>::iterator it2;
vector<pair<int, int>>::iterator it3;

int* tulos3=new int[4];
int muuttujatlkm = 2;
int pot=0, e=0, b=0;

int main(int argc, char* argv[]){
    tulos3[0] = 1;
    tulos3[1] = 1;
    tulos3[2] = 0;
    tulos3[3] = 0;
    int r_id [2]= {1,2};
    int bin_rivi_1 [2][2] = {{1,0},
                             {1,1}};
    
    pot = pow(2, muuttujatlkm);
    cout << "tulostaPOS:" << endl;
    
    for (int a = pot - 1; a >= 0; a--) {		
		if (tulos3[a] == 1) {
			tietue t;
			vector<int> v;
            v.push_back(b);
            string koe = to_string(bin_rivi_1[e][0]);
            cout << "bin_rivi_1:" << bin_rivi_1[e][0] << endl;
            
            string koe2 = to_string(bin_rivi_1[e][1]);
            cout << "bin_rivi_1:" << bin_rivi_1[e][1] << endl;

            cout << "koe:" << koe << "\nkoe2:" << koe2 << endl;
            
			t.bin += koe + koe2;
			t.r_indeksi = r_id[e];
			t.tunnus = v;
			cout << "\t.r_indeksi:" <<  t.r_indeksi;
			cout << ", t.bin:" << t.bin;
            cout << ", tunnus:" << v[0] << endl;
			taulukko.insert(pair<int, tietue>(e, t));
			iv.emplace_back(t.r_indeksi, e);
			e++;
		}
		else if (tulos3[a] == 0) {
            cout << "0";
		}	
        b++;	
	}
    
    cout << "rakennataulukko2:" << endl;

    stable_sort(iv.begin(), iv.end());
    int a=0, ii=0;
    for (auto it2 = iv.begin(); it2 != iv.end(); ++it2) {
        tietue t2;
        cout << "it2 first (ryhma_id):" << it2->first << endl;
        cout << "it2 second (jarjestysnro):" << it2->second << endl;
        t2.r_indeksi = taulukko.at(it2->second).r_indeksi;
        t2.tunnus = taulukko.at(it2->second).tunnus;
        t2.bin = taulukko.at(it2->second).bin;
        cout << "t2.bin:" << t2.bin << endl;
        taulukko2.insert(pair<int, tietue>(ii, t2));
        iv2.emplace_back(it2->second, a);
        a++;
        ii++;
    }
   // exit(0);
    cout << "muuttujienparitus1:" << endl;

    for (auto it2 = iv2.begin(); it2 != iv2.end(); ++it2) {
		// Talletetaan ryhma_id f:aan.
		//cout << "it2->second:" << it2->second << endl;
		//int f =it2->second;
        int f = taulukko2.at(it2->second).r_indeksi;
        cout << "f:" << f << endl;

		for (auto it3 = iv2.begin(); it3 != iv2.end(); ++it3) {
            int g = taulukko2.at(it3->second).r_indeksi;
            cout << "g:" << g << endl;

            if (f + 1 == g) {
                //cout << "tunnus koko:" <<  taulukko2.at(it2->second).tunnus.size() << endl;
                cout << "taulukko2 it2:" << taulukko2.at(it2->second).tunnus.at(0) << endl;
				cout << "taulukko2 it3:" << taulukko2.at(it3->second).tunnus.at(0) << endl;
                // cout << "t2.bin:" << taulukko2.at(it3->second).bin << endl;
                    
                for (int laskuri23 = 0; laskuri23 < muuttujatlkm; laskuri23++) {
				    cout << taulukko2.at(it2->second).bin[laskuri23] << ",";
					cout << taulukko2.at(it3->second).bin[laskuri23] << endl;
                }
                //cout << "it2->first:" << it2->first << endl;
			    //cout << "it3->first:" << it3->first << endl;
            }
        }
    }        
}
