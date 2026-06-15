/**
 * Joukko-oppi
 * Anna lauseke muodossa: ((W∪X)∩(Z∪Y))
 * (W∪X)
 * (W∪∼X)
 * ((W∪X)∩(X∪Y))
 * ((W∩X)∪(X∩Y))
 * (W⊂X)
 * Muista! Lausekkeiden unicode merkit merkistö -sovelluksen avulla! Lisäksi muista syöttää sovellukseen
 * näin: 
 Anna joukkojen lukumäärä: 2
 Joukon koko: 2
 Anna joukko1
 Anna muuttuja: 
 2
 Anna muuttuja:
 3
 Joukon koko:
 2
 Anna joukko2
 Anna muuttuja:
 1
 Anna muuttuja:
 3
 Anna lauseke:
 (W∪X)

 * */

#include <algorithm>
#include <vector>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <set>
#include <numeric>
#include <sstream>
#include <iterator>
#include <locale>
#include <codecvt>
#include <string>
//#include <windows.h>
#include <cwchar>
#include <cmath>
#include "joukko.h"
#include "infix_to_postfix.h"

#define MAXVAL	100
#define MAXOP	100
#define NUMBER	'0'
#define CHAR	'A'
#define BUFSIZE	100

using namespace std;
wchar_t s[MAXOP];
wchar_t osajoukko_m = u'\u2282';
int muuttujatlkm;
int* joukon_koko;
double mlkm2 = 0.0;
int sp = 0;
int spi = 0;
//int val[MAXVAL][MAXVAL];
int** val;
int* ival;
int* universumi;
int* perusjoukko;
int ukoko = 0;

typedef set<double, less<double> > set_type;
ostream& operator<<(ostream& out, const set_type& s) {
	copy(s.begin(), s.end(), std::ostream_iterator<set_type::value_type>(cout, " "));
	return out;
}
set_type joukko1, joukko2, joukko3, joukko4, u;
set_type tulos1, tulos2, tulos3;

int** joukot;
//int joukot[4][10];
//= new int[4][10];
std::vector<int> tulos(10);

void push(int* f, int fkoko) {
	wcout << "push:" << endl;
	int koko = 0;

	if (fkoko == 0) {
		koko = sizeof(f) / sizeof(int);
		wcout << "sizeof(f):" << sizeof(sizeof(f)) << endl;
		wcout << "sizeof(int):" << sizeof(int) << endl;
	}else{
		koko = fkoko;
		wcout << "fkoko:" << koko << endl;
		wcout << "\ntulos.size:" << sizeof(f) / sizeof(int*) << endl;
	}	
	/*
	for (int aa = 0; aa < koko; aa++) {
		cout << f[aa] << endl;
	}*/

	//cout << f[1] << endl;
	//cout << f[2] << endl;
	//cout << "sp:" << sp << endl;
	if (sp < MAXVAL) {
		//cout << "sp < MAXVAL" << endl;
		val[sp++] = f;
		ival[spi++] = fkoko;
		//cout << "ohi" << endl;
		//cout << val[0][0] << endl;
		//cout << val[0][1] << endl;
	}
	else {
		wcout << "virhe: stack on t�ynn�, ei voi push \n" << f;
	}
}

int* pop(void) {
	int* tyhja = { 0 };
	if (sp > 0)
		return val[--sp];
	else {
		wcout << "virhe: stack on tyhj�" << endl;
		return tyhja;
	}
}

int size_pop(void) {
	int tyhja = 0;
	if (spi > 0)
		return ival[--spi];
	else {
		wcout << "virhe: stack on tyhj�" << endl;
		return tyhja;
	}
}

int* tayta_joukot(int joukon_koko, int joukko_nro) {
	int muuttuja = 0;
	int* tulos = new int[joukon_koko];

	if (muuttujatlkm == 4 && joukko_nro == 0) {
		for (int a = 0; a < joukon_koko; a++) {
			wcout << "Anna muuttuja:" << endl;
			wcin >> muuttuja;
			tulos[a] = muuttuja;
			//joukko1.insert(muuttuja);
			muuttuja = 0;
		}
	}
	else if (muuttujatlkm == 4 && joukko_nro == 1) {
		for (int b = 0; b < joukon_koko; b++) {
			wcout << "Anna muuttuja:" << endl;
			wcin >> muuttuja;
			tulos[b] = muuttuja;
			//joukko2.insert(muuttuja);
			muuttuja = 0;
		}
	}
	else if (muuttujatlkm == 4 && joukko_nro == 2) {
		for (int c = 0; c < joukon_koko; c++) {
			wcout << "Anna muuttuja:" << endl;
			wcin >> muuttuja;
			tulos[c] = muuttuja;
			//joukko3.insert(muuttuja);
			muuttuja = 0;
		}
	}
	else if (muuttujatlkm == 4) {
		for (int d = 0; d < joukon_koko; d++) {
			wcout << "Anna muuttuja:" << endl;
			wcin >> muuttuja;
			tulos[d] = muuttuja;
			//joukko4.insert(muuttuja);
			muuttuja = 0;
		}
	}
	
	if (muuttujatlkm == 3 && joukko_nro == 0) {
		for (int a = 0; a < joukon_koko; a++) {
			wcout << "Anna muuttuja:" << endl;
			wcin >> muuttuja;
			tulos[a] = muuttuja;
			//joukko1.insert(muuttuja);
			muuttuja = 0;
		}
	}
	else if (muuttujatlkm == 3 && joukko_nro == 1) {
		for (int b = 0; b < joukon_koko; b++) {
			wcout << "Anna muuttuja:" << endl;
			wcin >> muuttuja;
			tulos[b] = muuttuja;
			//joukko2.insert(muuttuja);
			muuttuja = 0;
		}
	}else if(muuttujatlkm == 3){
		for(int c=0; c < joukon_koko; c++){
			wcout << "Anna muuttuja:" << endl;
			wcin >> muuttuja;
			tulos[c] = muuttuja;
			//joukko3.insert(muuttuja);
			muuttuja = 0;
		}		
	}
	
	if (muuttujatlkm == 2 && joukko_nro == 0) {
		wcout << "Anna joukko1:" << endl;
		for (int a = 0; a < joukon_koko; a++) {
			wcout << "Anna muuttuja:" << endl;
			std::wcin >> muuttuja;
			//cin.get();
			tulos[a] = muuttuja;
			//joukko1.insert(muuttuja);
			muuttuja = 0;
		}
	}else if(muuttujatlkm == 2){
		wcout << "Anna joukko2:" << endl;
		for(int b=0; b < joukon_koko; b++){
			wcout << "Anna muuttuja:" << endl;
			wcin >> muuttuja;
			tulos[b] = muuttuja;
			//joukko2.insert(muuttuja);
			muuttuja = 0;
		}				
	}

	if (muuttujatlkm == 1 && joukko_nro == 0) {
		wcout << "Anna joukko1:" << endl;
		for (int d = 0; d < joukon_koko; d++) {
			wcout << "Anna muuttuja:" << endl;
			std::wcin >> muuttuja;
			//cin.get();
			tulos[d] = muuttuja;
			//joukko1.insert(muuttuja);
			muuttuja = 0;
		}
	}
	
	return tulos;
}

bool ei_joukossa(int joukko1, int kohta, int koko, int maara) {
	int un = 0;
	//cout << endl;
	//cout << "maara:" << maara << endl;
	//cout << "kohta:" << kohta << endl;

	if (maara > 0) {
		for (int f = 0; f < maara; f++) {
		//	cout << "f:" << f << endl;
			//cout << "joukot[kohta][f]:" << joukot[kohta][f] << endl;
		//	cout << "perusjoukko[f]:" << perusjoukko[f] << endl;
		//	cout << "joukko1:" << joukko1 << endl;

			if (perusjoukko[f] != joukko1) {
		//		cout << "un:" << un << endl;
				un++;
			}

			/*
			if (joukot[kohta][f] != joukko1) {
				cout << "un:" << un << endl;
				un++;
			}*/
		}
		if (un == maara) {
			return true;
		}
		else {
		//	cout << "false" << endl;
			return false;
		}
	}
	else {
	//	cout << "true" << endl;
		return true;
	}
}

int** lauseke_postfix() {		
		
	wcout << "Anna joukkojen lukumaara:" << endl;	
	wcin >> muuttujatlkm;
	
	int e = 0, h=0;
	perusjoukko = new int[muuttujatlkm * 10];
	joukot = new int* [muuttujatlkm];
	joukon_koko = new int [muuttujatlkm];	

	for (int c = 0; c < muuttujatlkm; c++) {
		wcout << "Joukon koko:" << endl;
		wcin >> joukon_koko[c];
		
		joukot[c] = tayta_joukot(joukon_koko[c], c);
		//int* koe = tayta_joukot(joukon_koko, c);
		for (int j = 0; j != joukon_koko[c]; j++) {
			//joukot[c][j] = koe[j];
			wcout << joukot[c][j] << endl;
			//cout << "joukot[" << c << "][" << j << "]:";
			//cout << koe[j] << endl;
		}
		//cout << "koe" << endl;		

		for (int d = 0; d < joukon_koko[c]; d++) {
			wcout << "joukot[" << c << "][" << d << "]:" << joukot[c][d] << endl;

			if (ei_joukossa(joukot[c][d], c, joukon_koko[c], e)) {
				//cout << "ei joukossa:" << joukot[c][d] << endl;
				perusjoukko[e] = joukot[c][d];
				//universumi[e] = joukot[c][d];
				//cout << "universumi:" << universumi[e] << endl;
				//cout << "e:" << e << endl;
				e++;				
			}
		}
		
	}
	
	universumi = new int[e];
	wcout << "universumi:" << endl;

	for (int g = 0; g < e; g++) {
		universumi[g] = perusjoukko[g];
		//cout << universumi[g] << ",";
	}

	std::vector<int> jarjestys(universumi, universumi + e);
	std::sort(jarjestys.begin(), jarjestys.begin() + e);

	for (std::vector<int>::iterator it2 = jarjestys.begin(); it2 != jarjestys.end(); ++it2) {
		universumi[h] = *it2;
		std::wcout << ' ' << universumi[h];
		h++;
	}
	ukoko = e;
	for (int ddd = 0; ddd < 2; ddd++) {
		wcout << "joukot[" << 0 << "][" << ddd << "]:" << joukot[0][ddd] << endl;
	}
	return joukot;
}

bool osajoukko(int *joukko1, int *joukko2, int maara1, int maara2) {
	int tulos = 0;
	bool palautus = false;

	for (int eee = 0; eee < maara1; eee++) {
		for (int fff = 0; fff < maara2; fff++) {
			if (joukko1[eee] == joukko2[fff]) {
				wcout << joukko1[eee] << ", " << joukko2[fff] << endl;
				tulos++;
			}
		}
	}
	if (tulos == maara1) {
		palautus = true;
	}
	return palautus;
}

wstring muunna_postfix() {
	
	wcout << L"Anna lauseke:" << endl;
	
	wcin >> s;
	wstring infix(s);
	
	/*
	
	std::wstring infix;
	std::wcin.sync();
	std::getline(std::wcin, infix); // Read a full line of input into a wstring
	std::getline(std::wcin, infix);
	std::wcout << L"You entered: " << infix << std::endl;
	*/
	
	//wcout << L"infix: " << infix << endl;
	//muuttujatlkm = collectMlkm(infix);
	wcout << "Muuttujien lkm:" << muuttujatlkm << endl;
	//infix = concats(infix);
	wcout << L"infix:" << infix << endl;
	
	mlkm2 = muuttujatlkm;
	wstring postfix = convert(infix);
	
	return postfix;
}

int* muunnaBinaari(int* lopputulos, int koko) {
	int* tulos = new int[koko];
	int laskuri2 = 0;

	wcout << "muunnaBinaari:" << endl;

	for (int zz = koko-1; zz >= 0; zz--) {
		if (lopputulos[zz] >= 0 && lopputulos[zz] < 32) {
			wcout << 1;
		}
		else {
			wcout << 0;
		}
	}

	return tulos;
}

int* laske_lauseke(const wchar_t* toinen, int** tmp2) {
	std::vector<int> v;
	std::vector<int> vluku2;
	std::vector<int> vluku1;
	std::vector<int>::iterator it;
	wchar_t tyyppi;
	int* t3 = new int[0];
	bool oj = false;
	//int tyyppi=0, 
	int i = 0, j=0;
	int* luku1;
	int* luku2;
	int* tulos;
	int* tulos2;
	int* osajoukko2;
	int laskuri = 0;
	int lkoko3 = 0;
	int lkoko4 = 0;
	int lkoko5 = 0;
	int lkoko = 0;
	int lkoko2 = 0;

	wcout << "toinen:" << toinen << endl;
	val = new int* [palautaKoko()];
	ival = new int [palautaKoko()];
	wcout << "Lausekkeen koko:" << palautaKoko() << endl;

	laskuri = muuttujatlkm - 1;
	//laskuri = haeMlkm()-2;
	//cout << "haeMlkm:" << laskuri << endl;
	while ((tyyppi = toinen[i]) != '\0') {
		//while((type = getop(s)) != 10){
		wcout << "toinen[i]:" << toinen[i] << endl;
		switch (tyyppi) {
		case 0x2282:
			wcout << "Well congrats unicode!" << endl;
			luku2 = pop();
			luku1 = pop();
			lkoko = size_pop();
			lkoko2 = size_pop();
			oj = osajoukko(luku1, luku2, lkoko2, lkoko);
			std::wcout << std::boolalpha;
			wcout << L"\u2282:\n";
			
			osajoukko2 = new int[1];
			//wcout << "osajoukko2:" << endl;
						
			if (oj) {
				wcout << 1 << endl;
				osajoukko2[0] = 1;
				push(osajoukko2, 1);
			}
			else {
				wcout << 0 << endl;
				osajoukko2[0] = 0;
				push(osajoukko2, 1);
			}
			luku2 = new int[0];
			luku1 = new int[0];
			lkoko = 0;
			lkoko2 = 0;
			oj = false;
			break;
		case 0x0057:
			for (int dd = 0; dd < 2; dd++) {
				wcout << "tmp2[" << 0 << "][" << dd << "]:" << tmp2[0][dd] << endl;
			}
			// JATKA T�ST�, tarkkaile W:n arvoa !!!
			wcout << "W:";
			//cout << "Muuttujien lkm:" << muuttujatlkm << endl;
			
			// joukot[0] viittaa annettuun joukkoon W!!
			push(joukot[0], joukon_koko[0]);
			wcout << "joukot ohi" << endl;
			wcout << endl;
			//cout << "laskuri:" << laskuri << endl;
			break;
		case 0x0058:
			wcout << "X:";
			//cout << "laskuri:" << laskuri << endl;
			//pot = pow(2, muuttujatlkm);
			//cout << "pot:" << pot << endl;

			// joukot[1] viittaa annettuun joukkoon X!!
			push(joukot[1], joukon_koko[1]);
			//cout << "B(" << laskuri << "):" << B[laskuri] << endl;
			//muunnaBinaari(pot, B[laskuri], true);
			wcout << endl;
			break;
		case 0x0059:
			cout << "Y:";
			//pot = pow(2, muuttujatlkm);
			push(joukot[2], joukon_koko[2]);
			//muunnaBinaari(pot, C[laskuri], true);
			cout << endl;
			break;
		case 0x005A:
			cout << "Z:";
			//pot = pow(2, muuttujatlkm);
			push(joukot[3], joukon_koko[3]);
			//muunnaBinaari(pot, D[laskuri], true);
			cout << endl;
			break;
		case 0x0030:
			cout << "0:";
			//push(nolla[laskuri]);
			//muunnaBinaari(pot, nolla[laskuri], true);
			//cout << endl;
			break;
		case 0x0031:
			cout << "1:";
			//pot = pow(2, muuttujatlkm);
			//cout << "Numero:" << yksi[laskuri] << endl;
			//push(yksi[laskuri]);
			//muunnaBinaari(pot, yksi[laskuri], true);
			cout << endl;
			break;
		case 0x222A:
			// T�h�n laske pop() OR pop() ja push() pinoon
			// push(pop() + pop()
			j = 0;
			// Laske tässä kohdassa UNIONI
			luku2 = pop();
			luku1 = pop();
			lkoko3 = size_pop();
			lkoko4 = size_pop();
			//pot = pow(2, muuttujatlkm);
			//lkoko3 = sizeof(luku1) / sizeof(luku1[0]);
			//lkoko4 = sizeof(luku2) / sizeof(luku2[0]);
			
			wcout << "lkoko3:" << lkoko3 << endl;
			wcout << "lkoko4:" << lkoko4 << endl;

			for (int dd = 0; dd < lkoko3; dd++) {
				wcout << "luku2:" << luku2[dd] << endl;
				vluku2.push_back(luku2[dd]);
			}

			for (int ee = 0; ee < lkoko4; ee++) {
				wcout << "luku1:" << luku1[ee] << endl;
				vluku1.push_back(luku1[ee]);
			}

			wcout << "vluku1 size:" << vluku1.size() << endl;
			wcout << "vluku2 size:" << vluku2.size() << endl;
			
			std::set_union(vluku1.begin(), vluku1.end(), 
						   vluku2.begin(), vluku2.end(), 
						   std::back_inserter(v));
			//it = std::set_union(luku1, luku1 + lkoko4, luku2, luku2 + lkoko3,
			//	v.begin());
			//v.resize(it - v.begin());
			//tulos = laske(pot, luku1, luku2, 'A');
			
			//cout << "+:";
			wcout << L"\u222A:\n";

			wcout << endl;
			tulos2 = new int[v.size()];
			//wcout << "v.size():" << v.size() << endl;

			for (it = v.begin(); it != v.end(); ++it) {
				tulos2[j] = *it;
				std::wcout << ' ' << tulos2[j];
				t3[j] = *it;
				j++;
			}
			//cout << "j:" << j << endl;
			wcout << endl;
			push(tulos2, j);
			//t3 = muunnaBinaari(pot, tulos, true);
			/*for (auto it = v.begin(); it != v.end(); ++it) {
				it = v.erase(it);
			}*/
			v.clear();
			vluku1.clear();
			vluku2.clear();
			//memset(luku2, 0, lkoko3);
			//memset(luku1, 0, lkoko4);
			wcout << endl;
			break;
		case 0x2229:
			// T�h�n laske pop() AND pop() ja push() pinoon				
			//push(pop() * pop());
			//std::vector<int>::iterator it;
			// Laske tässä kohdassa LEIKKAUS
			//cout << "*" << endl;
			j = 0;
			luku2 = pop();
			luku1 = pop();
			lkoko = size_pop();
			lkoko2 = size_pop();			

			wcout << "lkoko:" << lkoko << endl;
			wcout << "lkoko2:" << lkoko2 << endl;

			for (int bb = 0; bb < lkoko; bb++) {
				wcout << "luku2:" << luku2[bb] << endl;
				vluku2.push_back (luku2[bb]);
			}

			for (int cc = 0; cc < lkoko2; cc++) {
				wcout << "luku1:" << luku1[cc] << endl;
				vluku1.push_back (luku1[cc]);
			}
			//pot = pow(2, muuttujatlkm);
			//lkoko = sizeof(luku1) / sizeof(luku1[0]);
			wcout << "\nluku2.size:" << sizeof(luku2) / sizeof(int*) << endl;

			//cout << "lkoko:" << lkoko << endl;
			//cout << "lkoko2:" << lkoko2 << endl;
			
			std::set_intersection(vluku2.begin(), vluku2.end(),	vluku1.begin(), vluku1.end(), std::back_inserter(v));

			//std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(),
			//	std::back_inserter(v_intersection));


			//it = set_intersection(luku2, luku2 + lkoko,
			//	luku1, luku1 + lkoko2, v.begin());

			wcout << "set_intersection ohi" << endl;
			//v.resize(it - v.begin());
			wcout << "v.size:" << v.size() << endl;

			tulos = new int[v.size()];
			wcout << "tulos.size:" << sizeof(tulos) / sizeof(int*) << endl;

			//cout << "*:";
			wcout << L"\u2229:\n";

			wcout << endl;
			for (it = v.begin(); it != v.end(); ++it) {
				tulos[j] = *it;
				std::wcout << ' ' << tulos[j];
				t3[j] = *it;
				j++;
			}
			wcout << endl;
			//tulos = laske(pot, luku1, luku2, 'K');
			//cout << "j:" << j << endl;
			//cout << "\ntulos.size:" << sizeof(tulos) / sizeof(int*) << endl;
			push(tulos, j);	
			//cout << "push ohi" << endl;
			//t3 = muunnaBinaari(pot, tulos, true);
			
			/*for (auto it = v.begin(); it != v.end(); ++it) {
				it = v.erase(it);				 
			}*/
			
			v.clear();
			vluku1.clear();
			vluku2.clear();
			//memset(luku2, 0, lkoko2);
			//memset(luku1, 0, lkoko);

			break;
		case 0x0027:
			// T�M� ON NOT
			luku1 = pop();
			// Hei, katso allaolevaa riviä vielä
			lkoko5 = sizeof(luku1) / sizeof(luku1[0]);
			wcout << "luku1:" << luku1[0] << "," << luku1[1] << endl;
			//pot = pow(2, muuttujatlkm);
			//cout << "Not:" << luku1;
			//cout << "Luku2:" << luku2 << endl;
			//cout << "2 potenssi muuttujien lkm:" << pot << endl;
			it = set_difference(universumi, universumi + ukoko,
				luku1, luku1 + lkoko5, v.begin());
			v.resize(it - v.begin());
			wcout << "\nv.size():" << v.size() << endl;

			tulos = new int[v.size()];

			wcout << "':";
			wcout << endl;
			for (it = v.begin(); it != v.end(); ++it) {
				tulos[j] = *it;
				std::wcout << ' ' << tulos[j];
				//t3[j] = *it;
				j++;
			}
			//tulos2 = not(bb, luku1);
			wcout << "\nj:n arvo on:" << j << endl;
			wcout << "\ntulos.size:" << sizeof(tulos) / sizeof(int*) << endl;
			push(tulos, j);
			/*
			for (auto it = v.begin(); it != v.end(); ++it) {
				it = v.erase(it);
			}
			*/
			v.clear();
			//memset(luku2, 0, lkoko2);
			memset(luku1, 0, lkoko);
			//cout << "':";
			//t3 = muunnaBinaari(pot, tulos2, true);
			wcout << endl;
			break;
		case 0x22BB:
			// T�h�n laske pop() XOR pop() ja push() pinoon
			// push(pop() + pop()
			luku2 = pop();
			luku1 = pop();
			//pot = pow(2, muuttujatlkm);
			//tulos = laske(pot, luku1, luku2, 'E');
			//tulos2 = not(bb, tulos);
			//push(tulos2);
			wcout << "=:";
			//t3 = muunnaBinaari(pot, tulos2, true);
			wcout << endl;
			break;
		case '\n':
			//cout << "Loppu:" << pop() << endl;
			break;
		default:
			wcout << "Virhe: Tuntematon komento" << s << endl;
			break;
		}
		i++;
	}

	luku2 = pop();
	luku1 = pop();
	lkoko = size_pop();
	lkoko2 = size_pop();

	wcout << "lkoko:" << lkoko << endl;
	wcout << "lkoko2:" << lkoko2 << endl;

	for (int bb = 0; bb < lkoko; bb++) {
		wcout << "luku2:" << luku2[bb] << endl;
	}

	for (int cc = 0; cc < lkoko2; cc++) {
		wcout << "luku1:" << luku1[cc] << endl;
	}
	wcout << "pow:" << pow(2, muuttujatlkm) << endl;
	int * mb = muunnaBinaari(luku2, pow(2, muuttujatlkm));

	return 0;
}
/*
void SetFontExample(HDC hdc) {
	HFONT hFont = CreateFont(
		24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("Arial")
	);

	SelectObject(hdc, hFont);
	TextOut(hdc, 10, 10, TEXT("Hello, World!"), 13);

	DeleteObject(hFont);
}
	*/
/*
int* muunnaBinaari(int* lopputulos, int koko) {
	int* tulos = new int[koko];
	int laskuri2 = 0;

	wcout << "muunnaBinaari:" << endl;

	for (int zz = 0; zz < koko; zz++) {
		if (lopputulos[zz] > -1) {
			wcout << 1;
		}
		else {
			wcout << 0;
		}		 
	}

	return tulos;
}
*/

/*
* Huomaa että setmode -funktio tarvitsee stdin sekä stdout -määreet jotta sisäänpäin kulkeva tieto on
* unicode muodossa!
*/

//int wmain(void) {
int main(){
	int* tulos3;
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);

	/*
	const wchar_t teksti = L'\u2229';
	//std::wcout << L"Hello, ⊃ or \u2282!\n";
	if (teksti == L'\u2229') {
		std::wcout << teksti << endl;
	}
	else {
		std::cout << "Ei ole!" << endl;
	}
	//SetConsoleOutputCP(CP_UTF8);
	//SetConsoleCP(CP_UTF8);
	
	//std::wcin.imbue(std::locale("en_US.UTF-8")); // Set UTF-8 locale for input
	//std::wcout.imbue(std::locale("en_US.UTF-8")); // Set UTF-8 locale for output
	
	//std::locale::global(std::locale(""));

	wchar_t input;
	std::wcout << L"Enter a Unicode character: ";
	std::wcin >> input;
	if (!std::wcin.good()) return -1;
	
	std::wcout << L"You entered: " << input << std::endl;
	
	exit(0);	
	*/
	int** tmp = lauseke_postfix();	
	wstring lauseke = muunna_postfix();
	wcout << "lauseke:" << lauseke << endl;	

	tulos3 = laske_lauseke(lauseke.c_str(), tmp);
	exit(0);

	int t1[] = {0,1};
	int t2[] = {1,2,3};
	int m1 = 2;
	int m2 = 3;
	std::cout << std::boolalpha;
	cout << "osajoukko:" << osajoukko(t1, t2, m1, m2) << endl;
/*
	set_type joukko1, joukko2, joukko3, joukko4, joukko5, u;
	joukko1.insert(2);
	joukko1.insert(3);
	cout << joukko1 << endl;
	joukko2.insert(1);
	joukko2.insert(3);
	cout << joukko2 << endl;
	u.insert(0);
	u.insert(1);
	u.insert(2);
	u.insert(3);

	set_union(joukko1.begin(), joukko1.end(), joukko2.begin(), joukko2.end(),
		inserter(joukko3, joukko3.begin()));

	cout << "Yhdiste on:" << joukko3 << endl;

	set_intersection(joukko1.begin(), joukko1.end(),
		joukko2.begin(), joukko2.end(), inserter(joukko4, joukko4.begin()));

	cout << "Leikkaus on:" << joukko4 << endl;

	set_difference(u.begin(), u.end(),
		joukko1.begin(), joukko1.end(), inserter(joukko5, joukko5.begin()));

	cout << "Komplementti on:" << joukko5 << endl;*/
	//cin.get();

	return 0;
}

