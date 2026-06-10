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

 Markus Juhala
 * */

#include <algorithm>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <set>
#include <numeric>
#include <sstream>
#include <iterator>
#include <locale>
#include <codecvt>
#include <string>
#include <cstring>
#include <math.h>
//#include <windows.h>
#include <cwchar>
#include <locale>
#include <codecvt>
#include <locale>
#include <iomanip>
#include "joukko.h"
#include "infix_to_postfix.h"

#define MAXVAL	100
#define MAXOP	100
#define NUMBER	'0'
#define CHAR	'A'
#define BUFSIZE	100

using namespace std;
//wchar_t s[MAXOP];
string s;
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
std::wstring_convert<std::codecvt_utf8<wchar_t>> muunnin;

void push(int* f, int fkoko) {
	//cout << "push:" << endl;
	int koko = 0;

	if (fkoko == 0) {
		koko = sizeof(f) / sizeof(int);
		cout << "sizeof(f):" << sizeof(sizeof(f)) << endl;
		cout << "sizeof(int):" << sizeof(int) << endl;
	}else{
		koko = fkoko;
		//cout << "fkoko:" << koko << endl;
		//cout << "\ntulos.size:" << sizeof(f) / sizeof(int*) << endl;
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
		cout << "virhe: stack on t�ynn�, ei voi push \n" << f;
	}
}

int* pop(void) {
	int* tyhja = { 0 };
	if (sp > 0)
		return val[--sp];
	else {
		cout << "pop virhe: stack on tyhj�" << endl;
		return tyhja;
	}
}

int size_pop(void) {
	int tyhja = 0;
	if (spi > 0)
		return ival[--spi];
	else {
		cout << "size_pop virhe: stack on tyhj�" << endl;
		return tyhja;
	}
}

int* tayta_joukot(int joukon_koko, int joukko_nro) {
	int muuttuja = 0;
	int* tulos = new int[joukon_koko];

	if (muuttujatlkm == 4 && joukko_nro == 0) {
		for (int a = 0; a < joukon_koko; a++) {
			cout << "Anna muuttuja:" << endl;
			cin >> muuttuja;
			tulos[a] = muuttuja;
			//joukko1.insert(muuttuja);
			muuttuja = 0;
		}
	}
	else if (muuttujatlkm == 4 && joukko_nro == 1) {
		for (int b = 0; b < joukon_koko; b++) {
			cout << "Anna muuttuja:" << endl;
			cin >> muuttuja;
			tulos[b] = muuttuja;
			//joukko2.insert(muuttuja);
			muuttuja = 0;
		}
	}
	else if (muuttujatlkm == 4 && joukko_nro == 2) {
		for (int c = 0; c < joukon_koko; c++) {
			cout << "Anna muuttuja:" << endl;
			cin >> muuttuja;
			tulos[c] = muuttuja;
			//joukko3.insert(muuttuja);
			muuttuja = 0;
		}
	}
	else if (muuttujatlkm == 4) {
		for (int d = 0; d < joukon_koko; d++) {
			cout << "Anna muuttuja:" << endl;
			cin >> muuttuja;
			tulos[d] = muuttuja;
			//joukko4.insert(muuttuja);
			muuttuja = 0;
		}
	}
	
	if (muuttujatlkm == 3 && joukko_nro == 0) {
		for (int a = 0; a < joukon_koko; a++) {
			cout << "Anna muuttuja:" << endl;
			cin >> muuttuja;
			tulos[a] = muuttuja;
			//joukko1.insert(muuttuja);
			muuttuja = 0;
		}
	}
	else if (muuttujatlkm == 3 && joukko_nro == 1) {
		for (int b = 0; b < joukon_koko; b++) {
			cout << "Anna muuttuja:" << endl;
			cin >> muuttuja;
			tulos[b] = muuttuja;
			//joukko2.insert(muuttuja);
			muuttuja = 0;
		}
	}else if(muuttujatlkm == 3){
		for(int c=0; c < joukon_koko; c++){
			cout << "Anna muuttuja:" << endl;
			cin >> muuttuja;
			tulos[c] = muuttuja;
			//joukko3.insert(muuttuja);
			muuttuja = 0;
		}		
	}
	
	if (muuttujatlkm == 2 && joukko_nro == 0) {
		cout << "Anna joukko1:" << endl;
		for (int a = 0; a < joukon_koko; a++) {
			cout << "Anna muuttuja:" << endl;
			std::cin >> muuttuja;
			//cin.get();
			tulos[a] = muuttuja;
			//joukko1.insert(muuttuja);
			muuttuja = 0;
		}
	}else if(muuttujatlkm == 2){
		cout << "Anna joukko2:" << endl;
		for(int b=0; b < joukon_koko; b++){
			cout << "Anna muuttuja:" << endl;
			cin >> muuttuja;
			tulos[b] = muuttuja;
			//joukko2.insert(muuttuja);
			muuttuja = 0;
		}				
	}

	if (muuttujatlkm == 1 && joukko_nro == 0) {
		cout << "Anna joukko1:" << endl;
		for (int d = 0; d < joukon_koko; d++) {
			cout << "Anna muuttuja:" << endl;
			cin >> muuttuja;
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
		
	cout << "Anna joukkojen lukumaara:" << endl;	
	cin >> muuttujatlkm;
	
	int e = 0, h=0;
	perusjoukko = new int[muuttujatlkm * 10];
	joukot = new int* [muuttujatlkm];
	joukon_koko = new int [muuttujatlkm];	

	for (int c = 0; c < muuttujatlkm; c++) {
		cout << "Joukon koko:" << endl;
		cin >> joukon_koko[c];
		
		joukot[c] = tayta_joukot(joukon_koko[c], c);
		//int* koe = tayta_joukot(joukon_koko, c);
		for (int j = 0; j != joukon_koko[c]; j++) {
			//joukot[c][j] = koe[j];
			cout << joukot[c][j] << endl;
			//cout << "joukot[" << c << "][" << j << "]:";
			//cout << koe[j] << endl;
		}
		//cout << "koe" << endl;		

		for (int d = 0; d < joukon_koko[c]+1; d++) {
			//cout << "d:" << d << endl;
			//cout << "joukot[" << c << "][" << d << "]:" << joukot[c][d] << endl;

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
	int koe = pow(2, muuttujatlkm);
	int g=0;
	universumi = new int[koe];
	cout << "pow:" << pow(2, muuttujatlkm) << endl;
	cout << "universumi:" << endl;

	for (g = 0; g < pow(2, muuttujatlkm); g++) {
		//universumi[g] = perusjoukko[g];
		universumi[g] = g;
		//cout << universumi[g] << ",";
	}
	//exit(0);
	std::vector<int> jarjestys(universumi, universumi + g);
	std::sort(jarjestys.begin(), jarjestys.begin() + g);

	for (std::vector<int>::iterator it2 = jarjestys.begin(); it2 != jarjestys.end(); ++it2) {
		universumi[h] = *it2;
		cout << ' ' << universumi[h];
		h++;
	}
	ukoko = g;
	for (int ddd = 0; ddd < 2; ddd++) {
		//cout << "joukot[" << 0 << "][" << ddd << "]:" << joukot[0][ddd] << endl;
	}
	return joukot;
}

bool osajoukko(int *joukko1, int *joukko2, int maara1, int maara2) {
	int tulos = 0;
	bool palautus = false;

	for (int eee = 0; eee < maara1; eee++) {
		for (int fff = 0; fff < maara2; fff++) {
			if (joukko1[eee] == joukko2[fff]) {
				cout << joukko1[eee] << ", " << joukko2[fff] << endl;
				tulos++;
			}
		}
	}
	if (tulos == maara1) {
		palautus = true;
	}
	return palautus;
}

string muunna_postfix() {
	
	
	cout << "\nAnna lauseke:" << endl;
	//std::locale::global(std::locale("fi_FI.UTF-8"));
	//std::wcin.imbue(std::locale());
	//std::wcout.imbue(std::locale());
	
	cin >> s;
	//std::getline(std::cin, s);
	string infix(s);
	
	//string infix(s);
	
	/*
	
	std::wstring infix;
	std::wcin.sync();
	std::getline(std::wcin, infix); // Read a full line of input into a wstring
	std::getline(std::wcin, infix);
	std::wcout << L"You entered: " << infix << std::endl;
	*/
	
	//wcout << L"infix: " << infix << endl;
	//muuttujatlkm = collectMlkm(infix);
	cout << "Muuttujien lkm:" << muuttujatlkm << endl;
	//infix = concats(infix);
	//cout << "infix:" << infix << endl;
	std::wstring winfix = muunnin.from_bytes(infix);
	
	mlkm2 = muuttujatlkm;
	wstring wpostfix = convert(winfix);
	std::string postfix = muunnin.to_bytes(wpostfix);
	//string postfix;
	return postfix;
}

int* muunnaBinaari(int* lopputulos, int koko) {
	int* tulos = new int[koko];
	int laskuri2 = 0;

	cout << "muunnaBinaari:" << endl;

	for (int zz = koko-1; zz >= 0; zz--) {
		if (lopputulos[zz] >= 0 && lopputulos[zz] < 32) {
			cout << 1;
		}
		else {
			cout << 0;
		}
	}

	return tulos;
}

int muunnaBinaari2(int* lopputulos, int koko) {
    int summa = 0;
    //cout << "koko:" << koko << endl;
    //cout << "lopputulos:" << lopputulos[0] << endl;
    //cout << "ukoko:" << ukoko << endl;
    /*if(koko == 1){
    	summa = pow(2, lopputulos[0]-ukoko);
    
    }else{*/

    	for (int i = 0; i < koko; i++) {
        int bitti = lopputulos[i];
        //cout << bitti << endl;
        
            //	if (bitti > 0) {    	
            // Jos luku on 1, lisätään 2^(1-1) = 1
            // Jos luku on 2, lisätään 2^(2-1) = 2
            // Jos luku on 3, lisätään 2^(3-1) = 4
            
        	    summa += pow(2, bitti);
      //  	    cout << "luku:" << summa << endl;
            //	}else{
        	// Tähän lisää nolla indeksi!!
        			    			
        			
			        	
            //	}
    	}
    //}
    //cout << "summa:" << summa << endl;

    return summa;
}

void muunnaBinaari(int desimaali, int koko){
	cout << "muunna binaariksi:" << endl;
	int jakotulos = desimaali;
	int jakojaannos = 0;
	int* tulos = new int[koko];
	int bb = koko-1;
	//cout << "koko:" << koko << endl;
	
	for(int aa=0; aa < koko; aa++){
		//cout << aa << endl;
		jakojaannos = jakotulos % 2;
		jakotulos = jakotulos / 2;
		tulos[bb]=jakojaannos;
		//cout << "bb:" << bb << endl;
		//cout << jakotulos << endl;
		bb--;
	}
	for(int cc=0; cc < koko; cc++){
		//cout << "cc:" << cc << endl;
		cout << tulos[cc] << setw(2);		
	}
	
}

void muunnaTaulukkoBinaariksi(int* syote, int koko) {
    std::cout << "Muunnos binaariksi:" << std::endl;

    for (int i = 0; i < koko; i++) {
        int luku = syote[i];
        std::string binaariStr = "";
        
        // Tallennetaan alkuperäinen luku tulostusta varten
        int alkuperainen = luku;

        // Algoritmi: jaetaan lukua 2:lla ja otetaan jakojäännös
        if (luku == 0) binaariStr = "0";
        
        while (luku > 0) {
            binaariStr += std::to_string(luku % 2);
            luku /= 2;
        }

        // Koska bittien haku menee "väärinpäin", käännetään merkkijono
        std::reverse(binaariStr.begin(), binaariStr.end());

        std::cout << alkuperainen << " on binaarina: " << binaariStr << std::endl;
    }
}

int* laske_lauseke(const wchar_t* toinen, int** tmp2) {
	std::vector<int> v;
	std::vector<int> vluku2;
	std::vector<int> vluku1;
	std::vector<int>::iterator it;
	wchar_t tyyppi;
	int* t3 = new int[0];
	bool oj = false;
	bool ohita=false;
	//int tyyppi=0, 
	int i = 0, j=0;
	int* luku1;
	int* luku2;
	int* tulos;
	int* tulos2;
	int* osajoukko2;
	int laskuri = 0;
	int mlaskuri = 0;
	int lkoko3 = 0;
	int lkoko4 = 0;
	int lkoko5 = 0;
	int lkoko = 0;
	int lkoko2 = 0;
	std::setlocale(LC_ALL, "fi_FI.UTF-8");
	std::wcout.imbue(std::locale(""));
	//cout << "toinen:" << toinen << endl;
	val = new int* [palautaKoko()];
	ival = new int [palautaKoko()];
	cout << "Lausekkeen koko:" << palautaKoko() << endl;

	laskuri = muuttujatlkm - 1;
	//laskuri = haeMlkm()-2;
	//cout << "haeMlkm:" << laskuri << endl;
	while ((tyyppi = toinen[i]) != '\0') {
		//while((type = getop(s)) != 10){
		std::string utf8_merkki = muunnin.to_bytes(toinen[i]);
		cout << u8"merkki[" << i << "]" << utf8_merkki << endl;
		//wcout << L"toinen[i]:" << toinen[i] << endl;
				
		switch (tyyppi) {
		case 0x2282:
			//cout << "Well congrats unicode!" << endl;
			luku2 = pop();
			luku1 = pop();
			lkoko = size_pop();
			lkoko2 = size_pop();
			oj = osajoukko(luku1, luku2, lkoko2, lkoko);
			std::cout << std::boolalpha;
			cout << u8"\u2282:\n";
			
			osajoukko2 = new int[1];
			//wcout << "osajoukko2:" << endl;
						
			if (oj) {
				cout << "TRUE" << endl;
				osajoukko2[0] = 1;
				push(osajoukko2, 1);
			}
			else {
				cout << "FALSE" << endl;
				osajoukko2[0] = 0;
				push(osajoukko2, 1);
			}
			luku2 = new int[0];
			luku1 = new int[0];
			lkoko = 0;
			lkoko2 = 0;
			oj = false;
			ohita = true;
			break;
		case 0x0057:
			for (int dd = 0; dd < 2; dd++) {
				//cout << "tmp2[" << 0 << "][" << dd << "]:" << tmp2[0][dd] << endl;
			}
			// JATKA T�ST�, tarkkaile W:n arvoa !!!
			cout << "W:";
			//cout << "Muuttujien lkm:" << muuttujatlkm << endl;
			mlaskuri++;
			// joukot[0] viittaa annettuun joukkoon W!!
			push(joukot[0], joukon_koko[0]);
			//cout << "joukot ohi" << endl;
			cout << endl;
			//cout << "laskuri:" << laskuri << endl;
			break;
		case 0x0058:
			cout << "X:";
			//cout << "laskuri:" << laskuri << endl;
			//pot = pow(2, muuttujatlkm);
			//cout << "pot:" << pot << endl;
			mlaskuri++;
			// joukot[1] viittaa annettuun joukkoon X!!
			push(joukot[1], joukon_koko[1]);
			//cout << "B(" << laskuri << "):" << B[laskuri] << endl;
			//muunnaBinaari(pot, B[laskuri], true);
			cout << endl;
			break;
		case 0x0059:
			cout << "Y:";
			mlaskuri++;
			//pot = pow(2, muuttujatlkm);
			push(joukot[2], joukon_koko[2]);
			//muunnaBinaari(pot, C[laskuri], true);
			cout << endl;
			break;
		case 0x005A:
			cout << "Z:";
			mlaskuri++;
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
		//case 0x222A:
		case L'\u222A':
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
			
			//cout << "lkoko3:" << lkoko3 << endl;
			//cout << "lkoko4:" << lkoko4 << endl;

			for (int dd = 0; dd < lkoko3; dd++) {
			//	cout << "luku2:" << luku2[dd] << endl;
				vluku2.push_back(luku2[dd]);
			}

			for (int ee = 0; ee < lkoko4; ee++) {
			//	cout << "luku1:" << luku1[ee] << endl;
				vluku1.push_back(luku1[ee]);
			}

			//cout << "vluku1 size:" << vluku1.size() << endl;
			//cout << "vluku2 size:" << vluku2.size() << endl;
			
			std::set_union(vluku1.begin(), vluku1.end(), 
						   vluku2.begin(), vluku2.end(), 
						   std::back_inserter(v));
			//it = std::set_union(luku1, luku1 + lkoko4, luku2, luku2 + lkoko3,
			//	v.begin());
			//v.resize(it - v.begin());
			//tulos = laske(pot, luku1, luku2, 'A');
			
			//cout << "+:";
			cout << u8"\u222A:";
			//cout << endl;
			tulos2 = new int[v.size()];
			//wcout << "v.size():" << v.size() << endl;

			for (it = v.begin(); it != v.end(); ++it) {
				tulos2[j] = *it;
				std::cout << ' ' << tulos2[j];
				t3[j] = *it;
				j++;
			}
			//cout << "j:" << j << endl;
			cout << endl;
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
			cout << endl;
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

			//cout << "lkoko:" << lkoko << endl;
			//cout << "lkoko2:" << lkoko2 << endl;

			for (int bb = 0; bb < lkoko; bb++) {
			//	cout << "luku2:" << luku2[bb] << endl;
				vluku2.push_back (luku2[bb]);
			}

			for (int cc = 0; cc < lkoko2; cc++) {
			//	cout << "luku1:" << luku1[cc] << endl;
				vluku1.push_back (luku1[cc]);
			}
			//pot = pow(2, muuttujatlkm);
			//lkoko = sizeof(luku1) / sizeof(luku1[0]);
			//cout << "\nluku2.size:" << sizeof(luku2) / sizeof(int*) << endl;

			//cout << "lkoko:" << lkoko << endl;
			//cout << "lkoko2:" << lkoko2 << endl;
			
			std::set_intersection(vluku2.begin(), vluku2.end(),	vluku1.begin(), vluku1.end(), std::back_inserter(v));

			//std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(),
			//	std::back_inserter(v_intersection));


			//it = set_intersection(luku2, luku2 + lkoko,
			//	luku1, luku1 + lkoko2, v.begin());

			//cout << "set_intersection ohi" << endl;
			//v.resize(it - v.begin());
			//cout << "v.size:" << v.size() << endl;

			tulos = new int[v.size()];
			//cout << "tulos.size:" << sizeof(tulos) / sizeof(int*) << endl;

			//cout << "*:";
			cout << u8"\u2229:";
			//cout << endl;
			for (it = v.begin(); it != v.end(); ++it) {
				tulos[j] = *it;
				std::cout << ' ' << tulos[j];
				t3[j] = *it;
				j++;
			}
			cout << endl;
			//tulos = laske(pot, luku1, luku2, 'K');
			cout << "j:" << j << endl;
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
		case 0x223C:
			// T�M� ON NOT
			luku1 = pop();
			// Hei, katso allaolevaa riviä vielä
			//lkoko5 = sizeof(luku1) / sizeof(luku1[0]);
			lkoko5 = joukon_koko[mlaskuri-1];
			//cout << "lkoko5:" << joukon_koko[mlaskuri-1] << endl;
			//cout << "luku1:" << luku1[0] << "," << luku1[1] << endl;
			v.resize(ukoko);
			//pot = pow(2, muuttujatlkm);
			//cout << "Not:" << luku1;
			//cout << "Luku2:" << luku2 << endl;
			//cout << "2 potenssi muuttujien lkm:" << pot << endl;
			it = set_difference(universumi, universumi + ukoko,
				luku1, luku1 + lkoko5, v.begin());
			v.resize(it - v.begin());
			//cout << "\nv.size():" << v.size() << endl;

			tulos = new int[v.size()];

			cout << "':";
			cout << endl;
			for (it = v.begin(); it != v.end(); ++it) {
				tulos[j] = *it;
				std::cout << ' ' << tulos[j];
				//t3[j] = *it;
				j++;
			}
			//tulos2 = not(bb, luku1);
			//cout << "\nj:n arvo on:" << j << endl;
			//cout << "\ntulos.size:" << sizeof(tulos) / sizeof(int*) << endl;
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
			cout << endl;
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
			cout << "=:";
			//t3 = muunnaBinaari(pot, tulos2, true);
			cout << endl;
			break;
		case '\n':
			cout << "Loppu:" << endl;
			break;
		default:
			cout << "Virhe: Tuntematon komento" << s << endl;
			break;
		}
		i++;
	}
	if(!ohita){
		lkoko = size_pop();		
		if(spi > 0)lkoko2 = size_pop();
		
		if(lkoko > 0)luku2 = pop();
		if(lkoko2 > 0)luku1 = pop();
		//cout << "size_luku1:" << luku1.size() << endl;
		cout << "lkoko:" << lkoko << endl;
		cout << "lkoko2:" << lkoko2 << endl;
		if(luku2 != 0){
			for (int bb = 0; bb < lkoko; bb++) {
				//cout << "luku2:" << luku2[bb] << endl;
			}
		}
		if(luku1 != 0){
			for (int cc = 0; cc < lkoko2; cc++) {
				//cout << "luku1:" << luku1[cc] << endl;
			}
		}
		//cout << "pow:" << pow(2, muuttujatlkm) << endl;
		//int * mb = muunnaBinaari(luku2, pow(2, muuttujatlkm));
		int bin = muunnaBinaari2(luku2, lkoko);
		muunnaBinaari(bin, ukoko);
		//muunnaTaulukkoBinaariksi(bin, pow(2, muuttujatlkm));
	}
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

int main(void) {
	int* tulos3;
	//_setmode(_fileno(stdin), _O_U16TEXT);
	//_setmode(_fileno(stdout), _O_U16TEXT);

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
	std::locale::global(std::locale(""));

	wchar_t input;
	std::wcout << L"Enter a Unicode character: ";
	std::wcin >> input;
	if (!std::wcin.good()) return -1;
	
	std::wcout << L"You entered: " << input << std::endl;
	*/
	//exit(0);
	char* lokaali = std::setlocale(LC_ALL, "");
    
    	if (lokaali == nullptr) {
        	std::cerr << "Lokaalin asettaminen epäonnistui!" << std::endl;
        
    	}

    	std::cout << "Käytössä oleva lokaali: " << lokaali << "\n";
    
    	// UTF-8 testaus
    	std::string testi = u8"Gentoossa ääkköset (äöå) toimivat! \u2713\n";
    	std::cout << testi;
    	/*
    	std::cout << "Kirjoita jotain (esim. ääkkösiä): ";
    	string st;
    // 3. Lue syöte suoraan wstringiin
    	if (std::cin >> st) {
        // Nyt 's' on wstring, joka sisältää syötteen
        	std::string infix(st); 

        	std::cout << "Infix-muuttujan sisältö: " << infix << std::endl;
        	std::cout << "Pituus merkkeinä: " << infix.length() << std::endl;
    	}	
	*/
	int** tmp = lauseke_postfix();	
	string lauseke = muunna_postfix();
	cout << "lauseke:" << lauseke << endl;
	
	std::wstring wlauseke = muunnin.from_bytes(lauseke);
	tulos3 = laske_lauseke(wlauseke.c_str(), tmp);
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

