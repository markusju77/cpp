#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <math.h>
#include <bits/stdc++.h> 
#include "infix_to_postfix.h"
#include "quine_mccluskell.h"
#include "karnaugh.h"
#include "asm_ba.h"

using namespace std;
vector<pair<int, int>> iv;
vector<pair<int, int>> iv2;
vector<pair<int, int >> tunnusparit;
vector<pair<int, int>> tunnus_id_muunnos;
vector<pair<int, int>> taulukko2_parit;
vector<pair<int, tietue>> vektori_matriisi;
std::unordered_map<int, tietue> taulukko;
std::unordered_map<int, tietue> taulukko2;
std::unordered_map<int, tietue> taulukko3;
std::unordered_map<int, tietue> taulukko4;
std::unordered_map<int, tietue> taulukko5;
std::unordered_map<int, tietue> taulukko6;
// Taulukot ovat loppumatriisia varten, jossa on kaikki arvot (jos taulukko ei ole tyhj�)
std::unordered_map<int, std::unordered_map<int, tietue>> taulukot;
//std::unordered_map<int, tietue> taulukko;
std::unordered_map<int, tietue>::iterator it;
vector<pair<int, int>>::iterator it2;
vector<pair<int, int>>::iterator it3;
vector<pair<int, int>>::iterator it4;
vector<pair<int, int>>::iterator it5;
std::unordered_map<int, tietue>::iterator it6;
std::unordered_map<int, tietue>::iterator it7;
std::unordered_map<int, tietue>::iterator it8;
std::unordered_map<int, tietue>::iterator it9;
std::unordered_map<int, tietue>::iterator it10;
std::unordered_map<int, tietue>::iterator it11;
vector<pair<int, int>>::iterator it12;
std::unordered_map<int, tietue>::iterator it13;
std::unordered_map<int, tietue>::iterator it14;
std::unordered_map<int, tietue>::iterator it15;
std::unordered_map<int, unordered_map<int, tietue>>::iterator it16;
std::unordered_map<int, unordered_map<int, tietue>>::iterator it17;
std::unordered_map<int, tietue>::iterator it18;
std::unordered_map<int, tietue>::iterator it19;
std::unordered_map<int, tietue>::iterator it20;
	

int ii;
int laskuri2 = 0;
int laskuri3 = 0;
int laskuri4 = 0;
int laskuri5 = 0;
int laskuri6 = 0;
int laskuri7 = 0;
int laskuri8 = 0;
int* laskuri9;
int laskuri11 = 0;
int laskuri12 = 0;
int laskuri18 = 0;
int laskuri19 = 0;
int laskuri24 = 0;
int laskuri25 = 0;
int laskuri26 = 0;
int laskuri27 = 0;
int laskuri28 = 0;
int laskuri29 = 0;
int laskuri31 = 0;
int laskuri32 = 0;
int laskuri33 = 0;
int laskuri35 = 0;
int laskuri36 = 0;
int laskuri38 = 0;
int laskuri39 = 0;
int laskuri40=0;
int laskuri41=0;
int AM_laskuri = 0;
int* matriisin_otsikko;
int* matriisin_tulos;
bool* matriisin_apurivi;
// Rivien lukum��r�: laskuri33
int** matriisi;
int* laskuri30;
int* joukko4;
int* joukko2;
bool* apumuuttuja;
int osuma2 = 0;
bool tulos5 = false;

char ca = 65;
char cb = 66;
char cc = 67;
char cd = 68;
char cnot = 39;
char merkit[4] = { 'A','B','C','D' };

/*
* Tayta int taulukko indeksin mukaiseen jarjestykseen !
* Katso delete funktiota !!
*/

bool lopputulos_SOP(int* tulos3, int pot, int muuttujatlkm) {
	int* tulos4;
	int indeksi = 0;
	int e = 0;
	int b = 0;

	for (int a = pot - 1; a >= 0; a--) {		
		if (tulos3[a] == 1) {
			tietue t;
			vector<int> v;
			tulos4 = muunnaBinaari(muuttujatlkm, b, false);
			cout << endl;			
			indeksi += tulostaKanooninen(tulos4, muuttujatlkm);
			cout << "\tbin: ";
			tulostaBin(tulos4, muuttujatlkm);
			cout << "\tindeksi:" << indeksi << "\ttunnus:" << b << " ";			
			v.push_back(b);
			t.bin = convert_int_to_string(tulos4, muuttujatlkm);
			t.r_indeksi = laskeYkkoset(t.bin, muuttujatlkm);
			t.tunnus = v;			
			cout << "\tlaskeYkkoset:" << t.r_indeksi;
			taulukko.insert(pair<int, tietue>(e, t));
			iv.emplace_back(t.r_indeksi, e);			
			e++;
		}
		else if (tulos3[a] == 0) {
			laskuri40++;
		}
		indeksi = 0;
		b++;
	}
	b = 0;
	return true;
}

/*
* Tayta int taulukko indeksin mukaiseen jarjestykseen !
*/

bool tulostaPOS(int* tulos3, int pot, int muuttujatlkm) {
	int indeksi2 = 0;
	int* tulos6, * tulos7;
	int e = 0;
	int b = 0;
	int ykkoset = 0;
	iv.clear();
	taulukko.clear();
	cout << "muuttujatlkm:" << muuttujatlkm << endl;
	cout << "\nTulosta POS:" << endl;
	for (int a = pot - 1; a >= 0; a--) {		
		if (tulos3[a] == 0) {
			tietue t;
			vector<int> v;
			int pl2 = static_cast<int>(pow(2, muuttujatlkm) - 1);
			tulos6 = muunnaBinaari(muuttujatlkm, pl2 - b, false);
			tulos7 = muunnaBinaari(muuttujatlkm, b, false);
			int turha = tulostaKanooninen(tulos6, muuttujatlkm);
			if (turha == 0 && muuttujatlkm == 4) cout << " bin:";
			else cout << "\tbin: ";
			tulostaBin(tulos7, muuttujatlkm);
			indeksi2 = laskeIndeksi(tulos7, muuttujatlkm);
			//ykkoset= laskeYkkoset(convert_int_to_string(tulos7, muuttujatlkm), muuttujatlkm);
			cout << "\tindeksi2:" << indeksi2;
			cout << "\ttunnus:" << b;
			
			v.push_back(b);
			t.bin = convert_int_to_string(tulos7, muuttujatlkm);
			t.r_indeksi = laskeYkkoset(t.bin, muuttujatlkm);
			t.tunnus = v;
			cout << "\tlaskeYkkoset:" <<  t.r_indeksi;
			cout << ", t.bin:" << t.bin << endl;
			taulukko.insert(pair<int, tietue>(e, t));
			iv.emplace_back(t.r_indeksi, e);
			e++;
		}
		else if (tulos3[a] == 1) {
			laskuri41++;
		}
		indeksi2 = 0;
		b++;
	}
	return true;
}

/*
* Tayta taulukko2 seka iv2:n kaksinumeroinen taulukko
* Tassa funktiossa on virhe!!
*/

void rakennaTaulukko2() {
	stable_sort(iv.rbegin(), iv.rend());
	iv2.clear();
	ii = 0;
	taulukko2.clear();
	//cout << "taulukko.size():" << taulukko.size() << endl;
	cout << "Taulukko2: " << endl;	
	for (auto it2 = iv.rbegin(); it2 != iv.rend(); ++it2) {
		cout << "it2->first:" << it2->first;
		cout << ", it2->second:" << it2->second << ", ";
		tietue t2;
		vector<int> v2;		
		v2.push_back(taulukko.at(it2->second).tunnus.at(0));
		cout << "t2.bin:" << taulukko.at(it2->second).bin;
		t2.bin = taulukko.at(it2->second).bin;
		t2.r_indeksi = taulukko.at(it2->second).r_indeksi;
		t2.tunnus = v2;
		taulukko2.insert(pair<int, tietue>(ii, t2));
		cout << "bin:" << taulukko2.at(ii).bin << ",";
		cout << "r_indeksi:" << taulukko2.at(ii).r_indeksi << ",";
		cout << "tunnus:" << taulukko2.at(ii).tunnus.at(0) << endl;
		iv2.emplace_back(t2.r_indeksi, ii);
		ii++;
	}	
}

void muuttujienAlustus() {
	matriisin_otsikko = new int[ii];
	matriisin_tulos = new int[ii];
	joukko2 = new int[ii * ii];
	apumuuttuja = new bool[ii * ii];
	laskuri32 = 0;

	cout << "ii:" << ii << endl;
	//exit(0);
	
	for (auto it14 = taulukko.begin(); it14 != taulukko.end(); ++it14) {
		//cout << "taulukko[laskuri32]" << taulukko[laskuri32].tunnus.at(0) << endl;
		matriisin_otsikko[laskuri32] = taulukko[laskuri32].tunnus.at(0);
		matriisin_tulos[laskuri32] = 0;
		cout << "matriisin_otsikko:" << matriisin_otsikko[laskuri32] << endl;
		cout << ", laskuri32:" << laskuri32 << endl;
		laskuri32++;
	}
	
	for (int laskuri20 = 0; laskuri20 < ii * ii; laskuri20++) {
		joukko2[laskuri20] = -1;
		cout << "joukko2:" << joukko2[laskuri20] << endl;
	}

	for (int laskuri21 = 0; laskuri21 < ii * ii; laskuri21++) {
		apumuuttuja[laskuri21] = false;
		cout << "apumuuttuja:" << apumuuttuja[laskuri21] << endl;
	}
	cout << endl;
	//exit(0);
}

void muuttujienParitus1(int muuttujatlkm) {
	tunnusparit.clear();
	tunnus_id_muunnos.clear();
	AM_laskuri = 0;
	cout << "taulukko2.size():" << taulukko2.size() << endl;
	cout << "iv2.size():" << iv2.size() << endl;
	cout << "tunnusparit.size():" << tunnusparit.size() << endl;
	cout << "tunnus_id_muunnos.size():" << tunnus_id_muunnos.size() << endl;
	cout << "AM_laskuri:" << AM_laskuri << endl;

	// Tee nyt sellainen silmukka joka parittaa termin tunnuksien avulla siten etta indeksi on yhden suurempi kuin tunnus !!!
	for (auto it2 = iv2.begin(); it2 != iv2.end(); ++it2) {
		// Talletetaan ryhma_id f:aan.
		int f = taulukko2.at(it2->second).r_indeksi;
		for (auto it3 = iv2.begin(); it3 != iv2.end(); ++it3) {

			// Talletetaan toinen ryhma_id g:een
			int g = taulukko2.at(it3->second).r_indeksi;
				// Verrataan f ja g -ryhmia ja pitaisi laskea viela OIKEIN tama!
				// Vertaa taulukko2:n bin it2->second.bin(x) == it3->second.bin(x) ja laske yhtasuurien lukumaara!
			if (f + 1 == g) {
				cout << "taulukko2 it2:" << taulukko2.at(it2->second).tunnus.at(0) << endl;
				cout << "taulukko2 it3:" << taulukko2.at(it3->second).tunnus.at(0) << endl;

				for (int laskuri23 = 0; laskuri23 < muuttujatlkm; laskuri23++) {
					cout << taulukko2.at(it2->second).bin[laskuri23] << ",";
					cout << taulukko2.at(it3->second).bin[laskuri23] << endl;

					if (taulukko2.at(it2->second).bin[laskuri23] == '1' && taulukko2.at(it3->second).bin[laskuri23] == '1' && taulukko2.at(it2->second).bin[laskuri23] == taulukko2.at(it3->second).bin[laskuri23]) {
						// L A S K E  O S U M I E N  M A A R A
						osuma2++;
						//cout << ",\nOsuma:" << osuma2;
					}
				}
				if (osuma2 == taulukko2.at(it2->second).r_indeksi) {
					tulos5 = true;
					//cout << "tulos5==true" << endl;
				}
				if (tulos5) {
					//if (f + 1 == g && taulukko2.at(it2->second).tunnus.at(0) < taulukko2.at(it3->second).tunnus.at(0)) {
					// Tallennetaan termin tunnus parit tunnusparit vektoriin				
					tunnusparit.emplace_back(taulukko2.at(it2->second).tunnus.at(0), taulukko2.at(it3->second).tunnus.at(0));
					tunnus_id_muunnos.emplace_back(it2->second, it3->second);
					//cout << "AM_laskuri:" << endl;
					joukko2[AM_laskuri] = it2->second;
					//cout << AM_laskuri << "," << endl;
					AM_laskuri++;
					//cout << AM_laskuri << "," << endl;
					joukko2[AM_laskuri] = it3->second;
					//cout << AM_laskuri << "," << endl;
					AM_laskuri++;					
				// Muuttujan joukko2:n alustus!! Koeta ihmeessa
					laskuri19++;
				}
			}
			tulos5 = false;
			osuma2 = 0;
		}		
	}
	//exit(0);
}

void muuttujienParitus2(int muuttujatlkm) {
	laskuri2 = 0;
	laskuri4 = 0;
	laskuri3 = 0;
	taulukko3.clear();

	for (auto it4 = tunnusparit.begin(); it4 != tunnusparit.end(); ++it4) {
		cout << "(" << it4->first << "," << it4->second << ")" << endl;
		// Tassa lasketaan binaarit (suurempi ensin 001 - 000)
		// Tassa otetaan tunnusparien kaikki parit, jotka myohemmin poistetaan!
		laskuri2++;
		cout << endl;
	}
	
	cout << "Katso allaolevat parit:" << endl;
	// Tulostetaan kaikki tunnusparien binaariset arvot, niiden indeksien perusteella

	for (auto it5 = tunnus_id_muunnos.begin(); it5 != tunnus_id_muunnos.end(); ++it5) {		
		cout << taulukko2.at(it5->first).tunnus.at(0) << ",";
		cout << taulukko2.at(it5->second).tunnus.at(0);
		cout << endl;
		tietue t3;
		vector<int> v3;
		v3.push_back(taulukko2.at(it5->first).tunnus.at(0));
		//taulukko2[laskuri18];
		v3.push_back(taulukko2.at(it5->second).tunnus.at(0));
		//taulukko2[laskuri18];
		
		for (int h = 0; h < muuttujatlkm; h++) {
			char i = taulukko2.at(it5->first).bin.at(h);
			char j = taulukko2.at(it5->second).bin.at(h);
			bool kk = false;
			bool ll = false;
			cout << i << " XOR " << j << endl;
			
			kk = laskeXOR(i, j);

			if (kk == true) {
				cout << "-";
				t3.bin.append("-");
			}
			cout << "=";
			cout << kk;

			ll = laskeAND(i, j);

			if (ll == true && kk == false) {
				t3.bin.append("1");
				laskuri4++;
			}
			else if (ll == false && kk == false) {
				t3.bin.append("0");
			}
			
			/* Ja nyt lasku rediksi !
			cout << ", ";*/
			cout << endl;
		}

		t3.r_indeksi = laskuri4;
		t3.tunnus = v3;
		cout << t3.bin;
		cout << endl;
		taulukko3.insert(pair<int, tietue>(laskuri3, t3));
		laskuri3++;
		laskuri4 = 0;
	}
}

void vertaaTaulukkoja1(int muuttujatlkm) {
	bool osuma = false;
	int* laskuri15 = new int[laskuri3];
	int* joukko3 = new int[laskuri3];
	taulukko4.clear();
	taulukko2_parit.clear();
	//taulukko5.clear();
	int m1 = 0;
	int m2 = 0;
	laskuri6 = 0;
	cout << "laskuri3:" << laskuri3 << endl;

	// Ja nyt katso taulukko3:n tulokset
	for (auto it6 = taulukko3.begin(); it6 != taulukko3.end(); ++it6) {
		int eka = it6->second.tunnus.at(0);
		int toka = it6->second.tunnus.at(1);
		int kolmas = 0;
		int neljas = 0;
		cout << "Muuttuja 1" << endl;
		cout << eka << ",";
		cout << toka << endl;
		cout << it6->second.bin << endl;
		int f2 = it6->second.r_indeksi;

		for (auto it7 = taulukko3.begin(); it7 != taulukko3.end(); ++it7) {
			int g2 = it7->second.r_indeksi;
			string s1;
			if (f2 + 1 == g2 && eka < toka) {
				bool kk = false;
				cout << "Muuttuja 2" << endl;
				int eka1 = it7->second.tunnus.at(0);
				int toka1 = it7->second.tunnus.at(1);
				kolmas = eka1;
				neljas = toka1;				
				cout << kolmas << ",";
				cout << neljas << endl;
				cout << it7->second.bin << endl;
				// JATKA TASTA !! JA VERTAA NYT INDEKSILISTAA TOISEEN
				for (int h2 = 0; h2 < muuttujatlkm; h2++) {
					char k = it6->second.bin.at(h2);
					char l = it7->second.bin.at(h2);
					
					// Katso nyt t4.bin listaa kaksoisarvojen valossa !
					if (k == '-' && l == '-') {
						// XOR:in tulos k ja l tallennetaan tietue t4:aan
						osuma = true;
						cout << "-";
						s1.append("-");
					}
					if (k != '-' && l != '-') {
						bool ll = false;
						ll = laskeAND(k, l);
						kk = laskeXOR(k, l);
						if (ll == true && kk == false) {
							cout << "1";
							s1.append("1");
							laskuri5++;
						}
						else if (ll == false && kk == false) {
							cout << "0";
							s1.append("0");
						}
						else if (kk == true) {
							cout << "-";
							s1.append("-");
						}
					}
					else if (!osuma) {
						if (k == '-') {
							s1.push_back(l);
						}
						else {
							s1.push_back(k);
						}
					}
				}
				// Korjaa tama osio vertaamalla
				if (osuma) {
					tietue t4;
					vector<int> v4;
					t4.bin = s1;
					cout << endl;
					cout << t4.bin << endl;
					cout << "tunnus:\n" << it6->second.tunnus.at(0) << ", " << endl;
					cout << it6->second.tunnus.at(1) << "," << endl;
					cout << kolmas << "," << endl;
					cout << neljas << "," << endl;
					v4.push_back(it6->second.tunnus.at(0));
					v4.push_back(it6->second.tunnus.at(1));
					v4.push_back(kolmas);
					v4.push_back(neljas);
					t4.r_indeksi = laskuri5;
					t4.tunnus = v4;
					cout << "laskuri6:" << laskuri6 << endl;
					taulukko4.insert(pair<int, tietue>(laskuri6, t4));
					taulukko2_parit.emplace_back(m1, m2);
					joukko3[laskuri6] = laskuri6;
					laskuri6++;
					osuma = false;
				}
				cout << endl;
			}
			m2++;
		}
		laskuri4 = 0;
		m1++;
		m2 = 0;
	}
}

void vertaaTaulukkoja2(int muuttujatlkm) {	
	laskuri12 = 1;
	laskuri9 = new int[laskuri6];
	laskuri7 = 0;
	laskuri8 = 0;
	laskuri11 = 0;
	// Ja nyt katsotaan TAAS taulukko4:n tulokset ja poistetaan KAKSOISARVOT
	cout << "Vertaapa:" << endl;
	cout << taulukko4.size() << endl;

	for (auto it8 = taulukko4.begin(); it8 != taulukko4.end(); it8++) {
		int eka = it8->second.tunnus.at(0);
		int toka = it8->second.tunnus.at(1);
		int kolmas = it8->second.tunnus.at(2);
		int neljas = it8->second.tunnus.at(3);
		cout << "Muuttuja 1" << endl;
		cout << it8->first << endl;
		cout << eka << ",";
		cout << toka << ",";
		cout << kolmas << ",";
		cout << neljas << endl;
		cout << it8->second.bin << endl;		

		for (auto it9 = it8; it9 != taulukko4.end(); it9++) {
			int eka1 = it9->second.tunnus.at(0);
			int toka1 = it9->second.tunnus.at(1);
			int kolmas1 = it9->second.tunnus.at(2);
			int neljas1 = it9->second.tunnus.at(3);
			laskuri11 = vertaaTaulukko4(eka, toka, kolmas, neljas, eka1, toka1, kolmas1, neljas1);

			if (laskuri11 == 4 && it8 != it9) {
				cout << "Muuttuja 2" << endl;
				cout << it9->first << endl;
				cout << eka1 << ",";
				cout << toka1 << ",";
				cout << kolmas1 << ",";
				cout << neljas1 << endl;
				cout << "laskuri11:" << laskuri11 << endl;

				// Ja nyt katso taulukko4:n tulokset
				for (int h3 = 0; h3 < muuttujatlkm; h3++) {
					char k = it8->second.bin.at(h3);
					char l = it9->second.bin.at(h3);
					cout << k << ",";
					//cout << l << endl;
					if (k == l) {
						laskuri8++;
					}
				}
				cout << endl;
				//cout << "laskuri8:" << laskuri8 << endl;
				if (laskuri8 == muuttujatlkm) {
					cout << "Osuma" << endl;
					laskuri9[laskuri7] = it9->first;
					laskuri7++;
				}
			}
			laskuri8 = 0;
			laskuri11 = 0;
		}
		//laskuri7 = 0; laskuri8 ja laskuri11 siirretty tasta!
	//}
	}
	cout << "ohi" << endl;
}

void poistaKaksoisarvot_ja_tulosta(int muuttujatlkm) {
	cout << "poistaKaksoisarvot funktio" << endl;
	laskuri25 = 0;
	cout << "laskuri25" << endl;
	//if(taulukko5.size()==1){
		taulukko5.clear();
	//}
	cout << "taulukko5.clear ohi" << endl;
	cout << "Poistetaan kaksoisarvot:" << endl;
	cout << "laskuri7 (eli kaksoisarvojen lukumaara):" << laskuri7 << endl;
	if (laskuri7 == 0) {
		cout << "Taulukossa 4 ei ole kaksoisarvoja." << endl;
	}

	// Poistetaan kaksoisarvot
	for (int laskuri10 = 0; laskuri10 < laskuri7; laskuri10++) {
		//cout << laskuri9[laskuri10] << endl;
		taulukko4.erase(laskuri9[laskuri10]);
	}

	// Tulosta taulukko4
	cout << "Tulosta taulukko4:" << endl;
	for (auto it10 = taulukko4.begin(); it10 != taulukko4.end(); ++it10) {
		cout << it10->first << endl;
		cout << it10->second.tunnus.at(0) << ",";
		cout << it10->second.tunnus.at(1) << ",";
		cout << it10->second.tunnus.at(2) << ",";
		cout << it10->second.tunnus.at(3) << ",";

		taulukko5.insert(pair<int, tietue>(laskuri25, it10->second));
		cout << endl;
		// Taulukon4 binaariset muuttujat
		for (int h4 = 0; h4 < muuttujatlkm; h4++) {
			cout << it10->second.bin.at(h4);
		}
		laskuri25++;
		cout << endl;
	}
	cout << endl;
}

void uusioKaytto(int muuttujatlkm) {
	bool osuma = false;
	taulukko6.clear();
	laskuri28=0;
	cout << "Taulukko4:n uusiokaytto!:" << endl;
	joukko4 = new int[laskuri25];
	laskuri30 = new int[laskuri25];

	for (auto it10 = taulukko5.begin(); it10 != taulukko5.end(); it10++) {
		int eka2 = it10->second.tunnus.at(0);
		int toka2 = it10->second.tunnus.at(1);
		int kolmas2 = it10->second.tunnus.at(2);
		int neljas2 = it10->second.tunnus.at(3);

		cout << "Muuttuja 1" << endl;
		cout << it10->first << endl;	

		for (auto it11 = it10; it11 != taulukko5.end(); it11++) {
			int eka3 = it11->second.tunnus.at(0);
			int toka3 = it11->second.tunnus.at(1);
			int kolmas3 = it11->second.tunnus.at(2);
			int neljas3 = it11->second.tunnus.at(3);
			string s2;
			// Huomaa! Funktio ei ole yhtenevainen edellisen kanssa, koska
			// se eroaa 0,1,2,3 ja 4,5,6,7 ovat pari.
			if (it10 != it11) {
				bool kk = false;
				laskuri26 = 0;
				cout << "Muuttuja 2" << endl;
				cout << it11->first << endl;				
					// Vertaa nyt taulukko5:n arvoja !
					// Ja nyt katso taulukko4:n tulokset
				for (int h5 = 0; h5 < muuttujatlkm; h5++) {
					char k = it10->second.bin.at(h5);
					char l = it11->second.bin.at(h5);
					//	cout << "(" << k << ",";
					//	cout << l << ")" << endl;
					if (k == '-' && l == '-') {
						//	cout << "Osuma" << endl;
							// XOR:in tulos k ja l tallennetaan tietue t4:��n
						laskuri26++;						
						s2.append("-");
					}
					if (k != '-' && l != '-') {
						bool ll = false;
						ll = laskeAND(k, l);
						kk = laskeXOR(k, l);
						
						if (ll == true && kk == false) {
							
							s2.append("1");
							laskuri27++;
							laskuri26++;
						}
						else if (ll == false && kk == false) {
							//	cout << "0";
							laskuri26++;
							s2.append("0");
						}
						else if (kk == true) {
							//	cout << "kk == true" << endl;
							s2.append("-");
							laskuri26++;
						}
					}

				}
				if (laskuri26 == 3) {
					tietue t5;
					vector<int> v5;
					t5.bin = s2;
					v5.push_back(it10->second.tunnus.at(0));
					v5.push_back(it10->second.tunnus.at(1));
					v5.push_back(it10->second.tunnus.at(2));
					v5.push_back(it10->second.tunnus.at(3));
					v5.push_back(it11->second.tunnus.at(0));
					v5.push_back(it11->second.tunnus.at(1));
					v5.push_back(it11->second.tunnus.at(2));
					v5.push_back(it11->second.tunnus.at(3));
					
					t5.r_indeksi = laskuri27;
					t5.tunnus = v5;					
					cout << "laskuri28:" << laskuri28 << endl;
					taulukko6.insert(pair<int, tietue>(laskuri28, t5));
					//taulukko2_parit.emplace_back(m1, m2);

					joukko4[laskuri28] = it10->first;
					cout << "joukko4[laskuri28]:" << endl;
					cout << joukko4[laskuri28] << endl;
					//cout << "laskuri28:" << laskuri28 << endl;
					laskuri28++;
					joukko4[laskuri28] = it11->first;
					laskuri28++;
					osuma = false;
					laskuri26 = 0;
				}
				cout << endl;
			}
			//cout << "s2:" << s2 << endl;
		}
	}
	cout << endl;
	cout << "laskuri28:" << laskuri28 << endl;
	cout << "taulukko4:n koko:" << taulukko4.size() << endl;
}

void poistaKaksoisarvot2(int muuttujatlkm) {	
	// Poistetaan taulukko4:en kaksoisarvot osa kaksi: Nyt yritetaan
	// poistaa taulukko5:n arvoja
	taulukot.clear();
	laskuri33 = 0;
	laskuri35 = 0;

	for (int laskuri34 = 0; laskuri34 < laskuri28; laskuri34++) {
		cout << joukko4[laskuri34] << endl;
		taulukko5.erase(laskuri34);
	}

	cout << "Poistetaan kaksoisarvot taulukko6:" << endl;
	cout << "laskuri28 (eli kaksoisarvojen lukumaara):" << laskuri28 << endl;
	if (laskuri7 == 0) {
		cout << "Taulukossa 4 ei ole kaksoisarvoja." << endl;
	}
	for (auto it12 = taulukko6.begin(); it12 != taulukko6.end(); it12++) {
		cout << "it12:" << it12->first << endl;
		for (auto it13 = it12; it13 != taulukko6.end(); it13++) {
			if (it12 != it13) {
				cout << "it13:" << it13->first << endl;
				cout << "laskuri31:" << laskuri31 << endl;
				for (int h6 = 0; h6 < muuttujatlkm; h6++) {
					char m = it12->second.bin.at(h6);
					char n = it13->second.bin.at(h6);
					if (m == '-' && n == '-') {
						laskuri29++;
					}
				}
				if (laskuri29 == 3) {
					laskuri30[laskuri31] = it13->first;

					cout << "it13->first:" << it13->first << endl;
					laskuri31++;
					laskuri29 = 0;
				}
			}
		}
		cout << endl;
	}
	for (int laskuri32 = 0; laskuri32 < laskuri31; laskuri32++) {
		taulukko6.erase(laskuri30[laskuri32]);
	}

	cout << "Tulosta taulukko6:" << endl;
	if (taulukko6.empty()) {
		cout << "Taulukossa 6 ei ole alkioita." << endl;
	}
	else {
		//td::unordered_map<int, unordered_map<int, tietue>>
		taulukot[laskuri35]= taulukko6;
		//taulukot.insert(pair<int, unordered_map<int, tietue>>(laskuri35, taulukko6));
		laskuri33 += taulukko6.size();
		cout << "taulukko6:n koko:" << taulukko6.size() << endl;
		laskuri35++;
	}
}

void tulostaTaulukot5ja6(int muuttujatlkm) {

	for (auto it14 = taulukko6.begin(); it14 != taulukko6.end(); ++it14) {
		cout << it14->second.tunnus.at(0) << ",";
		cout << it14->second.tunnus.at(1) << ",";
		cout << it14->second.tunnus.at(2) << ",";
		cout << it14->second.tunnus.at(3) << ",";
		cout << it14->second.tunnus.at(4) << ",";
		cout << it14->second.tunnus.at(5) << ",";
		cout << it14->second.tunnus.at(6) << ",";
		cout << it14->second.tunnus.at(7) << ",";
		cout << endl;
		for (int h7 = 0; h7 < muuttujatlkm; h7++) {
			char m = it14->second.bin.at(h7);
			cout << m;
		}
	}
	// Nyt yritetaan kayttaa taulukko5:ta matriisin luomiseen
	cout << "Tulosta taulukko5:" << endl;
	if (taulukko5.empty()) {
		cout << "Taulukossa 5 ei ole alkioita." << endl;
	}
	else {
		for (auto it19 = taulukko5.begin(); it19 != taulukko5.end(); ++it19) {
			cout << it19->second.tunnus.at(0) << ",";
			cout << it19->second.tunnus.at(1) << ",";
			cout << it19->second.tunnus.at(2) << ",";
			cout << it19->second.tunnus.at(3) << ",";
			cout << endl;
		}
		taulukot[laskuri35]=taulukko5;
		//taulukot.insert(pair<int, unordered_map<int, tietue>>(laskuri35, taulukko5));
		laskuri33 += taulukko5.size();
		cout << "taulukko5:n koko:" << taulukko5.size() << endl;
		laskuri35++;
	}
}

// alusta_aseta_ja_tulosta alustaa karnaughin matriisin seka asettaa ja tulostaa sen!
void alusta_aseta_ja_tulosta_matriisi(int muuttujatlkm) {

	alustaTaulukko(pow(2, muuttujatlkm), muuttujatlkm);
	// Jatka taulukon tayttaa asetaTaulukko, Karnaugh
	for (auto it10 = taulukko4.begin(); it10 != taulukko4.end(); ++it10) {
		/*cout << it10->first << endl;
		cout << it10->second.tunnus.at(0) << ",";
		cout << it10->second.tunnus.at(1) << ",";
		cout << it10->second.tunnus.at(2) << ",";
		cout << it10->second.tunnus.at(3) << ",";
		cout << endl;*/
		for (int laskuri37 = 0; laskuri37 < 4; laskuri37++) {
			asetaTaulukko(it10->second.tunnus.at(laskuri37), 1);
			laskuri38++;
		}
		//cout << endl;
	}
	tulostaTaulukko(pow(2, muuttujatlkm), muuttujatlkm);
}

void poistaParilliset_ja_tulosta() {
	cout << "Poistetaan taulukko3:n parilliset" << endl;
	cout << "taulukko2_parit koko:" << taulukko2_parit.size() << endl;
	cout << "laskuri35:" << laskuri35 << endl;

	//cout << "laskuri3:" << laskuri3 << endl;
	if (taulukko2_parit.empty()) {
		cout << "Taulukossa 3 ei ole parillisia." << endl;
	}
	// Nyt koetetaan purkaa taulukko taulukko2_parit ja poistetaan parit taulukko2:sta !!
	// Eli lisaa tahan koodi joka poistaa it12->first ja it12->second -parit !!

	for (auto it12 = taulukko2_parit.begin(); it12 != taulukko2_parit.end(); ++it12) {
		cout << it12->first << ",";
		cout << it12->second << endl;
		taulukko3.erase(it12->first);
		taulukko3.erase(it12->second);
	}

	cout << "Tulostetaan taulukko3:" << endl;
	//cout << "Muuttujat lkm:" << muuttujatlkm << endl;
	if (taulukko3.empty()) {
		cout << "Taulukossa3 ei ole alkioita." << endl;
	}
	else {
		cout << "taulukko3:n koko:" << taulukko3.size() << endl;
		for (auto it20 = taulukko3.begin(); it20 != taulukko3.end(); ++it20) {
			cout << it20->first << ":";
			cout << it20->second.tunnus.at(0) << ",";
			cout << it20->second.tunnus.at(1) << ",";
			cout << endl;
		}
		taulukot[laskuri35]=taulukko3;
		//taulukot.insert(pair<int, unordered_map<int, tietue>>(laskuri35, taulukko3));
		laskuri33 += taulukko3.size();
		laskuri35++;
	}
}

void asetaTaulukko_ja_tulostaTaulukko(int muuttujatlkm) {

	for (auto it11 = taulukko3.begin(); it11 != taulukko3.end(); ++it11) {
		asetaTaulukko(it11->second.tunnus.at(0), 1);
		asetaTaulukko(it11->second.tunnus.at(1), 1);
		// Taulukon3 binaariset muuttujat
		for (int h5 = 0; h5 < muuttujatlkm; h5++) {
			//	cout << it11->second.bin.at(h5);
				//cout << h5 << endl;
		}
		//cout << endl;
	}
	cout << endl;
	tulostaTaulukko(pow(2, muuttujatlkm), muuttujatlkm);
}

void poistaParilliset_ja_tulostaTaulukko2() {
	cout << "Poistetaan taulukko2:n parilliset" << endl;
	cout << "taulukot koko:" << taulukot.size() << endl;
	cout << "laskuri35:" << laskuri35 << endl;

	if (laskuri19 * 2 == 0) {
		cout << "Taulukossa 2 ei ole parillisia." << endl;
	}
	//cout << laskuri6 << endl;
	for (int laskuri14 = 0; laskuri14 < laskuri19 * 2; laskuri14++) {
		taulukko2.erase(joukko2[laskuri14]);		
	}
	// Jatka taulukko3.emptysta !!
	cout << "Tulostetaan taulukko2 (eli parittomat):" << endl;
	if (taulukko2.empty()) {
		cout << "Taulukossa 2 ei ole alkioita." << endl;
	}
	else {
		taulukot[laskuri35]=taulukko2;
		//taulukot.insert(pair<int, unordered_map<int, tietue>>(laskuri35, taulukko2));
		// Nyt lisaa matriisin laskemiseen tarvittava luku
		laskuri33 += taulukko2.size();
		laskuri35++;
	}
}

void asetaTaulukko_ja_tulosta2(int muuttujatlkm) {

	for (auto it12 = taulukko2.begin(); it12 != taulukko2.end(); ++it12) {
		//cout << it12->first << endl;		
		cout << it12->second.tunnus.at(0) << endl;
		asetaTaulukko(it12->second.tunnus.at(0), 1);
		//cout << it12->second.tunnus.at(1) << endl;
		//cout << endl;
		// Taulukon3 binaariset muuttujat
		for (int h6 = 0; h6 < muuttujatlkm; h6++) {
			cout << it12->second.bin.at(h6);
		}
		cout << endl;
	}
	if(!taulukko2.empty()) tulostaTaulukko(pow(2, muuttujatlkm), muuttujatlkm);
}

void matriisinTaytto_ja_lasku(int muuttujatlkm) {
	// Tutustu SOP ja POS -tulostukseen
	// Jatka viela taulukko5 tulostusta
	// TEE LOPPUMATRIISI KAIKISTA TAULUKON ALKIOISTA !!!
	// Taulukko6, taulukko5, taulukko4, taulukko3, taulukko2, taulukko1 kaikki mukaan!
	matriisin_apurivi = new bool[ii];
//	matriisi = new int* [laskuri33];
	int sarake_laskuri = 0;
	laskuri39 = 0;
	int laskuri42=0;
	cout << "laskuri33:" << laskuri33 << endl;
	// Sarakkeiden lukumaara: ii tai laskuri19
	matriisi = new int*[laskuri33];
	for (int i = 0; i < laskuri33; i++){
		matriisi[i] = new int [ii];
	}

	//matriisi[laskuri33][ii];

	// Matriisin Taytto
	for (int i = 0; i < laskuri33; i++)
	{
		for(int kk=0; kk<ii;kk++){
			matriisi[i][kk]=0;
		}
	}
	cout << "pow:" << pow(2, muuttujatlkm) - 1 << endl;
	cout << "laskuri33:" << laskuri33 << endl;
	cout << "ii:" << ii << endl;
	cout << "taulukot size:" << taulukot.size() << endl;

	//for (auto it16 = taulukot.begin(); it16 != taulukot.end(); it16++)
	for(auto it16 : taulukot)
	{
		// Lisaa tahan oikeat luvut ks. toinen lehtio...
		//std::unordered_map<int, tietue>::iterator it15;
		//std::unordered_map<int, unordered_map<int, tietue>>::iterator it16;
		cout << "\nKierros:" << it16.first << endl;
		//cout << "\nKierros:" << taulukot[laskuri42].tunnus.at(0);
		if (!it16.second.empty()) {
			//for (auto it15 : it16.second){
			for (auto it15 = it16.second.begin(); it15 != it16.second.end(); it15++) {
				
				cout << "it16.first:" << it16.first << endl;
				cout << "it15->first:" << it15->first << endl;
				cout << "it15->second.tunnus.size:" << it15->second.tunnus.size() << endl;

				for (int j = 0; j < it15->second.tunnus.size(); j++) {
					//cout << "isdigit(it15->second.tunnus.at(j):" << isdigit(it15->second.tunnus.at(j)) << endl;
					// Etsi tahan jokin funktio joka tarkistaa etta it15 on luku valilla 0 .. 9
					for (int k = 0; k < ii; k++) {
						//cout << "matriisin_otsikko[" << k << "] == " << matriisin_otsikko[k] << endl;
						//cout << "it15->second.tunnus.at(" << j << "):" << it15->second.tunnus.at(j) << endl;
						//cout << "k:" << k << endl;
						
						if (matriisin_otsikko[k] == it15->second.tunnus.at(j)) {
							//cout << "matriisin_otsikko[" << k << "] == " << matriisin_otsikko[k] << endl;
							//cout << "it15->second.tunnus.at(" << j << "):" << it15->second.tunnus.at(j) << endl;							
							
							if (it16.first > 0) {
								matriisi[it16.first][k] = 1;
								cout << "(it16.first:" << it16.first << "), ";
								cout << "(k:" << k << ")" << endl;
							} else {
								matriisi[it15->first][k] = 1;
								cout << "(it15->first:" << it15->first << "), ";
								cout << "(k:" << k << ")" << endl;
							}
							//cout << "(matriisi:)" << matriisi[it15->first][k] << ")" << endl;
						}
					}
					
					/*
					if (it15->second.tunnus.at(j) <= pow(2, muuttujatlkm) - 1 && it15->second.tunnus.at(j) >= 0) {
						
						matriisi[it15->first][it15->second.tunnus.at(j)] = 1;
						//cout << "i:" << i << "," << endl;
						//cout << "it15:" << it15->second.tunnus.at(j) << ",";
						
						//cout << ", " << " matriisi:" << matriisi[it15->first][it15->second.tunnus.at(j)] << " ";
						cout << endl;
					}*/
				}
			}
		}
		laskuri42++;
	}
	cout << endl;
	//}
	cout << "laskuri33:" << laskuri33 << endl;
	cout << "ii:" << ii << endl;
	// Laske matriisi, nyt yritetaan kaantaa suuntaa !
	cout << "matriisin otsikot:" << endl;
	//for (int k = 0; k < laskuri33; k++) {
	for (int l = 0; l < ii; l++) {
		cout << "(" << matriisin_otsikko[l] << "),";
		for (int k = 0; k < laskuri33; k++) {
		//for(int k = 0; k < taulukot.size(); k++){
			//cout << "(l:" << l << "),";
			//cout << "(k:" << k << ")," << endl;
		
			if (matriisi[k][l] == 1) {
				//cout << "matriisi:" << matriisi[k][l] << " ";
				cout << endl;
				matriisin_tulos[l] += 1;
				//cout << "matriisin tulos:" << matriisin_tulos[l] << endl;
				//if(laskuri33==1)
			}
		}
	}
	cout << endl;
	cout << "ii:" << ii << endl;
	cout << "matriisin tulos:" << endl;
	for (int o = 0; o < ii; o++) {
		cout << matriisin_tulos[o] << ",";
		
		if (matriisin_tulos[o] == 1 && laskuri33 > 1) {
			matriisin_apurivi[o] = false;
		}
		else if (matriisin_tulos[o] > 1) {
			matriisin_apurivi[o] = true;
		}
		else if (laskuri33 == 1 && o == 0) {
			matriisin_apurivi[o] = false;
		}
		else if (laskuri33 == 1 && o >= 1) {
			matriisin_apurivi[o] = true;
		}
		if (matriisin_tulos[o] == 1) {
			laskuri39++;
		}
		//cout << matriisin_apurivi[o] << ",";
	}
	//exit(0);
}

void siirraTaulukot_ja_laskeMatriisin_tulos() {
	vektori_matriisi.clear();
	vektori_matriisi.resize(laskuri33);
	int koelaskuri = 0;
	int koelaskuri2 = laskuri33-1;
	cout << "koelaskuri2:" << koelaskuri2 << endl;
	
	for (auto it17 = taulukot.begin(); it17 != taulukot.end(); ++it17) {
		if (!it17->second.empty()) {
			for (auto it18 = it17->second.begin(); it18 != it17->second.end(); ++it18) {
				//cout << "it18->first:" << it18->first << endl;
				//vektori_matriisi.emplace_back(it18->first, it18->second);
				cout <<"koelaskuri:" << koelaskuri << endl;
				//vektori_matriisi.emplace_back(koelaskuri, it18->second);
				vektori_matriisi[koelaskuri2]=pair<int, tietue>(koelaskuri, it18->second);
				for (int k = 0; k < it18->second.tunnus.size(); k++) {
					//cout << "isdigit(it15->second.tunnus.at(j):" << isdigit(it15->second.tunnus.at(j)) << endl;
					// Etsi tahan jokin funktio joka tarkistaa etta it15 on luku valilla 0 .. 9
					cout << "it18->second.tunnus.at(" << k << "):" << it18->second.tunnus.at(k) << endl;
				}
				koelaskuri++;
				koelaskuri2--;
			}
		}
	}
	//vektori_matriisi.resize(koelaskuri);
	//if(koelaskuri == 4) exit(0);
	// Tulosta matriisin_tuloksen ykkosarvot matriisin sarakkeen kohdalta
	// jossa on ykkonen ja siita sarakkeen arvolla Taulukot muuttujan arvo...
	for (int m = 0; m < ii; m++) {
		cout << "m:" << m;
		
		if (matriisin_tulos[m] == 1 && !matriisin_apurivi[m]) {
			cout << " matriisin tulos: " << matriisin_tulos[m];
			// Saraketta alaspain kunnes tulee ykkosarvo
			for (int n = 0; n < laskuri33; n++) {
				cout << "n:" << n;
				if (matriisi[n][m] == 1) {
					cout << " matriisi:" << matriisi[n][m] << endl;
					// Ja nyt tulosta Taulukot muuttujan arvo
					for (int l = 0; l < vektori_matriisi[n].second.tunnus.size(); l++) {
						cout << "vektori_matriisi[n]->second.tunnus.at(" << l << "):" << vektori_matriisi[n].second.tunnus.at(l) << endl;
					}
				}
			}
		}
		cout << endl;
	}
	//exit(0);
}

void tulostaSOP(int muuttujatlkm, int pot) {
	int laskuri22 = 0;
	int laskuri38 = 0;
	int pari_laskuri = 0;
	int pari_laskuri2 = 0;
	int pareja = 0;
	int tripla = 0;
	int uniikki = 0;
	cout << "muuttujatlkm:" << muuttujatlkm << endl;
	cout << "taulukko4.size():" << taulukko4.size() << endl;
	cout << "vektori_matriisi:" << vektori_matriisi.size() << endl;
	cout << "laskuri39:" << laskuri39 << endl;
	cout << "taulukko2:" << taulukko2.size() << endl;
	cout << "ii:" << ii << endl;

	// Tulosta taulukko4:än tulokset: 0-- 
	cout << "Tulosta SOP lauseke: " << endl;
	cout << getF();
	if (!vektori_matriisi.empty()) {
		if (laskuri39 == ii && taulukko2.size() == 0 || muuttujatlkm == 1) {
			//cout << "laskuri39:" << laskuri39 << endl;
			//cout << "ii:" << ii << endl;
			cout << "(";
		}
		else {
			cout << "((";
		}
		for (auto it13 = vektori_matriisi.begin(); it13 != vektori_matriisi.end(); ++it13) {
			/*	cout << it13->second.tunnus.at(0) << ",";
				cout << it13->second.tunnus.at(1) << ",";
				cout << it13->second.tunnus.at(2) << ",";
				cout << it13->second.tunnus.at(3) << ",";
				cout << endl;*/
				// Vektori_matriisin binaariset muuttujat

			for (int h5 = 0; h5 < muuttujatlkm; h5++) {
				
				if (h5 == 0 && muuttujatlkm > 2) {
					if (it13->second.bin.at(h5) != '-' && it13->second.bin.at(h5 + 1) != '-' && it13->second.bin.at(muuttujatlkm - 1) != '-') {
						//cout << "h5:" << h5 << endl;
						//cout << "tripla (";
						cout << "(";
						tripla++;
					}
					if (it13->second.bin.at(h5) == '-' && it13->second.bin.at(h5 + 1) != '-' && it13->second.bin.at(muuttujatlkm - 1) == '-' && it13->second.bin.at(h5 + 1) == '0' ||
						it13->second.bin.at(h5) != '-' && it13->second.bin.at(h5 + 1) == '-' && it13->second.bin.at(muuttujatlkm - 1) == '-' && it13->second.bin.at(h5) == '0' ||
						it13->second.bin.at(h5) == '-' && it13->second.bin.at(h5 + 1) == '-' && it13->second.bin.at(muuttujatlkm - 1) != '-' && it13->second.bin.at(muuttujatlkm -1) == '0'){
						//cout << "uniikki";
						uniikki++;
					}
				}
				//cout << "joo" << endl;
				if (it13->second.bin.at(h5) == '0') {
				//	cout << "nolla";
					cout << merkit[h5] << "'";
					pari_laskuri++;
				}
				else if (it13->second.bin.at(h5) == '1') {
				//	cout << "yksi";
					cout << merkit[h5];
					pari_laskuri++;
				}else if (it13->second.bin.at(h5) == '-') {
				//	cout << "laskuri38++";
					laskuri38++;
				}
				
				//else 
				if (pari_laskuri == 2) {
					cout << ")";
					//cout << "pari_laskuri:" << pari_laskuri;
					pari_laskuri = 0;
					pareja++;
				}

				if (it13->second.bin.at(h5) != '-' && h5 < muuttujatlkm-1 && it13->second.bin.at(h5+1) != '-' ||
					it13->second.bin.at(h5) != '-' && h5 < muuttujatlkm-1 && it13->second.bin.at(muuttujatlkm-1) != '-') {
					//cout << "h5+muuttujat:" << h5 + (muuttujatlkm - 1);
					cout << "*";
				}
				
				
				/*
				if (it13->second.bin.at(h5) != '-' && h5 < muuttujatlkm-1 && it13->second.bin.at(h5+2) != '-') {
					cout << "*";
				}
				*/
				//cout << "h5:" << h5;
				/*
				if (it13->second.bin.at(h5+1) == '0' || it13->second.bin.at(h5+1) == '1') {
					cout << "*";
				}*/
			}
			if (uniikki > 0) {
				cout << ")";
				uniikki = 0;
			}
			
			//cout << "pari_laskuri2:" << pari_laskuri2;
			if (pareja == 0 && pari_laskuri2 == 1) {
				cout << ")";
				pari_laskuri2 = -1;
			}

			if (tripla > 0) {
				cout << ")";
				tripla = 0;
			}

			if (laskuri22 < vektori_matriisi.size() - 1) {
				cout << "+";
			}
			//if (pareja == 0 && pari_laskuri2 == -1 && laskuri22 < taulukko4.size() - 1) {
			if (laskuri22 < vektori_matriisi.size() - 1) {
				cout << "(";
			}
			// Lisää tähän vielä varmistus että tulos on 1 eikä 0 !!!
			if (laskuri38 == muuttujatlkm && laskuri39 == ii) {
				cout << "1";
			}
						
			//cout << "laskuri22:" << laskuri22 << endl;
			pari_laskuri = 0;
			laskuri22++;
			pari_laskuri2++;
		}
		cout << ")";
	}
	else {
		if (taulukot.empty()) {
			if (laskuri40 == pot) {
				cout << "(0)";
			}
		}
	}
	//exit(0);
}

void tulostaPOS2(int muuttujatlkm, int pot) {
	int pari_laskuri3 = 0;
	int pareja2 = 0;
	int pari_laskuri4 = 0;
	int laskuri23 = 0;
	int laskuri38 = 0;
	int tripla2 = 0;
	int uniikki2 = 0;
	cout << "muuttujatlkm:" << muuttujatlkm << endl;
	cout << "taulukko4.size():" << taulukko4.size() << endl;
	cout << "vektori_matriisi:" << vektori_matriisi.size() << endl;
	cout << "ii:" << ii << endl;
	cout << "laskuri39:" << laskuri39 << endl;
	cout << "laskuri38:" << laskuri38 << endl;

	cout << "\nTulosta POS lauseke: " << endl;
	cout << getF();
	// Jatka POS tulostusta!
	if (!vektori_matriisi.empty()) {
		if (laskuri39 == ii && taulukko2.size() == 0 || muuttujatlkm == 1) {
			//cout << "laskuri39:" << laskuri39 << endl;
			//cout << "ii:" << ii << endl;
			cout << "(";
		}else if(vektori_matriisi.size()  > 2){
			cout << "(((";
		}else {
			cout << "((";
		}

		for (auto it14 = vektori_matriisi.begin(); it14 != vektori_matriisi.end(); ++it14) {
			for (int koe = 0; koe < it14->second.tunnus.size(); koe++) {
			//	cout << it14->second.tunnus.at(koe) << ",";				
			}
				// Taulukon4 binaariset muuttujat
			//cout << endl;
			for (int h6 = 0; h6 < muuttujatlkm; h6++) {
				if (h6 == 0 && muuttujatlkm > 2) {
					if (it14->second.bin.at(h6) != '-' && it14->second.bin.at(h6 + 1) != '-' && it14->second.bin.at(muuttujatlkm - 1) != '-') {
						//cout << "h5:" << h5 << endl;
						cout << "(";
						tripla2++;
					}
					if (it14->second.bin.at(h6) == '-' && it14->second.bin.at(h6 + 1) != '-' && it14->second.bin.at(muuttujatlkm - 1) == '-' && it14->second.bin.at(h6 + 1) == '1' ||
						it14->second.bin.at(h6) != '-' && it14->second.bin.at(h6 + 1) == '-' && it14->second.bin.at(muuttujatlkm - 1) == '-' && it14->second.bin.at(h6) == '1' || 
						it14->second.bin.at(h6) == '-' && it14->second.bin.at(h6 + 1) == '-' && it14->second.bin.at(muuttujatlkm - 1) != '-' && it14->second.bin.at(muuttujatlkm - 1) == '1') {
						uniikki2++;
					}
					
				}
				if (it14->second.bin.at(h6) == '0') {
					cout << merkit[h6];
					pari_laskuri3++;
				}
				else if (it14->second.bin.at(h6) == '1') {
					cout << merkit[h6] << "'";
					pari_laskuri3++;
				}
				/*else if (h6 > 0 && it14->second.bin.at(h6) != '-') {
					cout << "+";
				}*/
				else if (it14->second.bin.at(h6) == '-') {
					laskuri38++;
				}
				
				if (pari_laskuri3 == 2) {
					cout << ")";
					//cout << "pari_laskuri3:" << pari_laskuri3;
					pari_laskuri3 = 0;
					pareja2++;
				}//else 
				
				if(pareja2 == 2 && vektori_matriisi.size() > 2){
					cout << ")";
					pari_laskuri3 = 0;
					pareja2++;
				}
								
				if (it14->second.bin.at(h6) != '-' && h6 < muuttujatlkm - 1 && it14->second.bin.at(h6 + 1) != '-' ||
					it14->second.bin.at(h6) != '-' && h6 < muuttujatlkm - 1 && it14->second.bin.at(muuttujatlkm - 1) != '-' ||
					it14->second.bin.at(h6) != '-' && h6 < muuttujatlkm -1 && it14->second.bin.at(muuttujatlkm -2) != '-') {
					//cout << "h5+muuttujat:" << h5 + (muuttujatlkm - 1);
					if(pari_laskuri3==1 && vektori_matriisi.size() > 1) cout << "+";
				}
				/*
				if (it13->second.bin.at(h5+1) == '0' || it13->second.bin.at(h5+1) == '1') {
					cout << "*";
				}*/
			}
			//cout << "pari_laskuri2:" << pari_laskuri2;
			if (uniikki2 > 0) {
				cout << ")";
				uniikki2 = 0;
			}

			if (pareja2 == 0 && pari_laskuri4 == 1 || pareja2 == 1 && pari_laskuri4 ==1) {
				cout << ")";
				pari_laskuri4 = -1;
			}

			if (tripla2 > 0) {
				cout << ")";
				tripla2 = 0;
			}
						
			if (laskuri23 < vektori_matriisi.size() - 1) {
				cout << "*";
			}
			
			//if (pareja2 == 0 && pari_laskuri4 == -1 && laskuri23 < taulukko4.size() - 1) {
			if(laskuri23 < vektori_matriisi.size()-1){
				cout << "(";
			}
			
			if(pareja2 == 3 && vektori_matriisi.size() > 2){
				cout << "(";
			}
			
			//cout << "laskuri38:" << laskuri38 << endl;
			if (laskuri38 == muuttujatlkm && laskuri39 == ii) {
				cout << "0";
			}
			/*
			if (tripla2 > 0) {
				cout << ")";
				tripla2 = 0;
			}*/
			//cout << "pari_laskuri4:" << pari_laskuri4 << endl;
			//cout << "pareja2:" << pareja2 << endl;
			pari_laskuri3 = 0;
			laskuri23++;
			pari_laskuri4++;
		}
		if(vektori_matriisi.size() > 2){
			cout << ")";
		}
		cout << ")";
	}
	else {
		if (taulukot.empty()) {
			if (laskuri41 == pot) {
				cout << "(1)";
			}
		}
	}
}

void tulostaBin(int *luku, int bittisyys){
	for(int f=bittisyys-1; f >= 0; f--){
		std::cout << luku[f];
	}
}

int laskeYkkoset(string luku, int bittisyys) {
	int ykkoset = 0;
	for (int g = bittisyys - 1; g >= 0; g--) {
		if (luku[g]=='1') {
			//std::cout << "laskeYkkoset:" << luku[g] << endl;
			ykkoset++;
		}
	}
	return ykkoset;
}

bool laskeXOR(char i, char j) {
	bool ii = false;
	bool jj = false;
	bool kk = false;
	bool ll = false;
	//std::cout << "LaskeXOR:" << endl;
	//cout << i << "," << j << endl;

	if (i == '0') {
		ii = false;
		//std::cout << "ii:" << ii;
	}
	else {
		ii = true;
		//std::cout << "ii:" << ii;
	}
	//cout << ",";

	if (j == '0') {
		jj = false;
		//std::cout << "jj:" << jj;
	}
	else {
		jj = true;
		//std::cout << "jj:" << jj;
	}
	//cout << endl;
	if (i > j) {
		
		kk = (ii ^ jj);
	}
	else {
		kk = (jj ^ ii);
	}
	
	//std::cout << kk << endl;
		//cout << j;
	//	cout << "=";
		
		return kk;
}

bool laskeAND(char i, char j) {
	bool ii = false;
	bool jj = false;
	bool kk = false;
	bool ll = false;

	if (i == '0') {
		ii = false;
		//	cout << ii;
	}
	else {
		ii = true;
		//	cout << ii;
	}
	//cout << ",";

	if (j == '0') {
		jj = false;
		//	cout << jj;
	}
	else {
		jj = true;
		//	cout << jj;
	}
	if (i > j) {
		ll = (ii & jj);
	}
	else {
		ll = (jj & ii);
	}

	return ll;
}

int vertaaTaulukko4(int eka, int toka, int kolmas, int neljas, int eka1, int toka1, int kolmas1, int neljas1) {
	int laskuri = 0;
	if (eka == eka1 || eka == toka1 || eka == kolmas1 || eka == neljas1) {
		laskuri++;
	}
	if (toka == eka1 || toka == toka1 || toka == kolmas1 || toka == neljas1) {
		laskuri++;
	}
	if (kolmas == eka1 || kolmas == toka1 || kolmas == kolmas1 || kolmas == neljas1) {
		laskuri++;
	}
	if (neljas == eka1 || neljas == toka1 || neljas == kolmas1 || neljas == neljas1) {
		laskuri++;
	}
	return laskuri;
}

int laskeIndeksi(int* luku, int bittisyys) {
	int indeksi = 0;
	for (int e = bittisyys - 1; e >= 0; e--) {
		//cout << "e:" << e << endl;

		// T�ss� on a:n muunnos
		if (luku[e] == 0 && e == bittisyys - 1) {
		//	cout << a << not;
		}
		else if (luku[e] == 1 && e == bittisyys - 1) {
		//	cout << a;
			indeksi++;
		}
		// T�ss� on b:n muunnos
		if (luku[e] == 0 && e == bittisyys - 2) {
		//	cout << b << not;
		}
		else if (luku[e] == 1 && e == bittisyys - 2) {
		//	cout << b;
			indeksi++;
		}
		// T�ss� on c:n muunnos
		if (luku[e] == 0 && e == bittisyys - 3) {
		//	cout << c << not;
		}
		else if (luku[e] == 1 && e == bittisyys - 3) {
		//	cout << c;
			indeksi++;
		}
		// T�ss� o d:n muunnos
		if (luku[e] == 0 && e == bittisyys - 4) {
		//	cout << d << not;
		}
		else if (luku[e] == 1 && e == bittisyys - 4) {
		//	cout << d;
			indeksi++;
		}
	}
	return indeksi;
}


// Palauta indeksi !
int tulostaKanooninen(int *luku, int bittisyys){
	int indeksi=0;
	// Tulosta t�ss� luvun binaarinen muoto kanoonisesti A'B jne.
	//cout << "tulostaKanooninen" << endl;
	for(int e=bittisyys-1; e >= 0; e--){
	//cout << "e:" << e << endl;
		
	// T�ss� on a:n muunnos
		if(luku[e]==0 && e==bittisyys-1){
			cout << ca << cnot;
		}else if(luku[e]==1 && e==bittisyys-1){
			cout << ca;
			indeksi++;
		}	
	// T�ss� on b:n muunnos
		if(luku[e]==0 && e==bittisyys-2){
			cout << cb << cnot;
		}else if(luku[e]==1 && e==bittisyys-2){
			cout << cb;
			indeksi++;
		}
	// T�ss� on c:n muunnos
		if(luku[e]==0 && e==bittisyys-3){
			cout << cc << cnot;
		}else if(luku[e]==1 && e==bittisyys-3){
			cout << cc;
			indeksi++;
		}
	// T�ss� o d:n muunnos
		if(luku[e]==0 && e==bittisyys-4){
			cout << cd << cnot;
		}else if(luku[e]==1 && e==bittisyys-4){
			cout << cd;
			indeksi++;
		}
	}
return indeksi;
}
