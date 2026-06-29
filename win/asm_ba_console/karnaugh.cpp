#include <iostream>
#include ".\karnaugh.h"

int arvotNelja[4] = { 0,2,1,3 };
int arvotKasi[8] = { 0,2,6,4,1,3,7,5 };
int arvotKuustoista[16] = { 0,4,12,8,1,5,13,9,3,7,15,11,2,6,14,10 };
int tyhjienlkm = 0;
// Taulukko5 on Karnaughin kartta
std::unordered_map<int, int> taulukko51;
// Iterator12 on Karnaughin kartta
std::unordered_map<int, int>::iterator it12;

void alustaTaulukko(int lkm, int mlkm) {
	int tyhja = -1;

	for (int a = 0; a < lkm; a++) {
		taulukko51.insert(pair<int, int>(a, tyhja));
	}
}

void tulostaTaulukko(int lkm, int mlkm) {
	if (lkm == 4) {
		for (int b = 0; b < lkm; b++) {
			it12 = taulukko51.find(arvotNelja[b]);
			//cout << it12->second;
			//if (b == 1) cout << endl;
		}
	}
	else if (lkm == 8) {
		for (int b = 0; b < lkm; b++) {
			it12 = taulukko51.find(arvotKasi[b]);
			//cout << it12->second;
			//if (b == 3) cout << endl;
		}
	}
	else if (lkm == 16) {
		for (int b = 0; b < lkm; b++) {
			it12 = taulukko51.find(arvotKuustoista[b]);
			//cout << it12->second;
			//if (b == 7) cout << endl;
		}
	}
	//cout << endl;
}
void nollaaTyhjienlkm(){
	tyhjienlkm = 0;
}

void asetaTaulukko(int pluku, int arvo) {
//	cout << "asetaTaulukko:" << pluku << ", arvo:" << arvo << endl;
	//taulukko5.insert(pair<int, int>(pluku, arvo));
	taulukko51[pluku] = arvo;
	//std::unordered_map<int, int>::const_iterator got = taulukko5.find(pluku);

	auto it = taulukko51.find(pluku);
	// Tulosta taulukko5:en sisältö!

	for (auto it12 = taulukko51.begin(); it12 != taulukko51.end(); ++it12) {
	//	cout << it12->first << ",";
	//	cout << it12->second << ",";
	//	cout << endl;
	}

	//cout << "Iterator points to " << it->first
	//	<< " = " << it->second << endl;

	//cout << "it12:" << it12->second;
	tyhjienlkm++;
}


