/**
*
Anna merkkijono käänteinen Lukasievich -muodossa esim. A B + A C + *
Anna merkkijono (A'*C)+(A'*B)+(A*B'*C') muodossa
Ohjelma laskee merkkijonon loogisen arvon.
Muoto voi olla myös lyhyempi, kuten AB*AC+*.
Huomaa unordered_map:in tuonti sovellukseen!!
((A'*C)+(A'*B)+(A*B'*C'))
((A'*C)+(B'))
*/
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <sstream>
#include <cmath>
#include <map>
#include <algorithm>
#include <vector>
#include <utility>
#include <functional>
#include <unordered_map>
#include "infix_to_postfix.h"
#include "quine_mccluskell.h"
using pari = pair<int, tietue>;
using namespace std;

#define MAXVAL	100
#define MAXOP	100
#define NUMBER	'0'
#define CHAR	'A'
#define BUFSIZE	100

char buf[BUFSIZE];
int bufp = 0;

int getch(void);
void ungetch(int);
int getop(char []);
void push(double);
double pop(void);

int sp = 0;
double val[MAXVAL];
int laskuri=0;
int jakojaannos=0;
int muuttujatlkm=0;
int pause=0;
int bb=16;
size_t koko = 16;
int A[4]={1, 3, 15, 255};
int B[4]={-1,5, 51, 3855};
int C[4]={-1,-1,85, 13107};
int D[4]={-1,-1,-1, 21845};


void push(double f){
	if(sp < MAXVAL)
		val[sp++] = f;
	else
		cout << "virhe: stack on täynnä, ei voi push \n" << f;
}

double pop(void){
	if(sp > 0)
		return val[--sp];
	else {
		cout << "virhe: stack on tyhjä" << endl;
		return 0.0;
	}
}

int getop(char s[]){
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if(!isdigit(c) && c != '.')
		return c;
	i=0;
	if(isdigit(c))
		while(isdigit(s[++i] = c = getch()))
			;
	if(c == '.')
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if(c != EOF)
		ungetch(c);
	return NUMBER;
}

int getch(void){
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
	if(bufp >= BUFSIZE)
		cout << "ungetch: liikaa merkkejä\n" << endl;
	else
		buf[bufp++] = c;
}

int laske(int bitti, int numero1, int numero2, char konnektiivi){
	int tulos=0;

	if(konnektiivi == 'K'){
		tulos = numero1 & numero2;	
	}else if(konnektiivi == 'A'){
		tulos = numero1 | numero2;
	}else if(konnektiivi == 'E'){
		tulos = numero1 ^ numero2;
	}
return tulos;
}

int not(int bitti, int numero1){
	int nr=0;
	//if(bitti == 4){
		//nr = ~numero1;
	
		//cout << "pow:" << bitti << endl;
		nr = pow(2, bitti)-1;
		nr = nr - numero1;
		//cout << "nr:" << nr << endl;
		//cout << "bitti == 4";
	//}
return nr;
}

int* muunnaBinaari(int bitti, int jakotulos, bool tulostus){
	int *tulos = new int[koko];
	laskuri=0;
	funktio:	
//laskuri++;

	//if(jakotulos > 2)
		jakojaannos = jakotulos;
		jakotulos = jakotulos/2;
		jakojaannos = jakojaannos%2;
	//else
	//	jakotulos = 2/jakotulos;
	tulos[laskuri]=jakojaannos;
	
	//if(jakotulos>0)goto funktio;
	//else goto end;
	if(laskuri == bitti-1){
		goto end;
	}else{
		//taulukko[laskuri]=0;
		if(jakotulos==0){
			//cout << "-" << endl;
		}
		laskuri++;
		goto funktio;
	}


end:
	if(tulostus){
		for(int a=bitti-1; a>=0; a--){
			cout << tulos[a];
		}
	}
return tulos;
}

string convert_int_to_string(int arr[], int size) {
	std::ostringstream os;
	int ii = size-1;
//	cout << "convert_int_to_string:" << endl;
//	cout << size << endl;

	for (int i = 0; i < size; i++) {
		os << arr[ii];
//		cout << arr[ii];
		ii--;
	}
//	cout << endl;
	std::string str(os.str());
	return str;
}

int main(){
	int type, laskuri, i=0, b=0, e=0;
	int luku1, luku2, pot=0, tulos, tulos2, indeksi=0;
	int tluku=0, tluku2=0, tlaskuri=0, tunnus1=0, tunnus2=0;
	int *tulos3, *tulos4;
	double op2;
	char s[MAXOP];
	char koe[2];
	string postfix;

	// jatka
	//evaluate("(A+B)*(A+C)");
	//string infix = "(a*b)+(a*c)";
	
	cout << "Anna lauseke:" << endl;
	cin.getline(s, 100);
	string infix(s);
	cout << "infix: " << infix << endl;
	postfix = convert(infix);
	muuttujatlkm = haeMlkm();
	cout << "Muuttujien lkm:" << muuttujatlkm << endl;
	
	const char* toinen = postfix.c_str();
	cout << "toinen:" << toinen << endl;
	
	/*cout << "Anna muuttujien lkm:" << endl;
	cin.getline (koe, 2);
	sscanf(koe, "%d", &muuttujatlkm);
	*/
	//cout << muuttujatlkm;
	//cout << "Anna lauseke:" << endl;
	laskuri = muuttujatlkm-1;

	while((type = toinen[i]) != '\0'){
	//while((type = getop(s)) != 10){
		switch (type){
			case 65:
				// JATKA TÄSTÄ, tarkkaile A:n arvoa !!!
				cout << "A:";
				//cout << "Muuttujien lkm:" << muuttujatlkm << endl;
				//cout << "A:";
				pot = pow(2, muuttujatlkm);
				// Tähän push()
				//cout << "pot:" << pot << endl;
				push(A[laskuri]);
				muunnaBinaari(pot, A[laskuri], true);
				cout << endl;
				break;
			case 66:
				cout << "B:";
				pot = pow(2, muuttujatlkm);
				push(B[laskuri]);
				muunnaBinaari(pot, B[laskuri], true);
				cout << endl;
				break;
			case 67:
				cout << "C:";
				pot = pow(2, muuttujatlkm);
				push(C[laskuri]);
				muunnaBinaari(pot, C[laskuri], true);
				cout << endl;
				break;
			case 68:
				cout << "D:";
				pot = pow(2, muuttujatlkm);
				push(D[laskuri]);
				muunnaBinaari(pot, D[laskuri], true);
				cout << endl;
				break;
			case NUMBER:
				push(atof(s));
				break;
			case 43:
				// Tähän laske pop() OR pop() ja push() pinoon
				// push(pop() + pop()
				
				luku2 = pop();
				luku1 = pop();
				pot = pow(2, muuttujatlkm);
				
				tulos = laske(pot, luku1, luku2, 'A');
				push(tulos);
				cout << "+:";
				tulos3 = muunnaBinaari(pot, tulos, true);
				cout << endl;
				break;
			case 42:
				// Tähän laske pop() AND pop() ja push() pinoon				
				//push(pop() * pop());
				luku2 = pop();
				luku1 = pop();
				pot = pow(2, muuttujatlkm);
				
				tulos = laske(pot, luku1, luku2, 'K');
				push(tulos);
				cout << "*:";
				tulos3 = muunnaBinaari(pot, tulos, true);
				cout << endl;
				break;
			case 39:
				// TÄMÄ ON NOT
				luku1 = pop();
				pot = pow(2, muuttujatlkm);
				//cout << "Not:" << luku1;
				//cout << "Luku2:" << luku2 << endl;
				//cout << "2 potenssi muuttujien lkm:" << pot << endl;
				
				tulos2 = not(bb, luku1);
				push(tulos2);
				cout << "':";
				tulos3 = muunnaBinaari(pot, tulos2, true);
				cout << endl;
				break;
			case 61:
				// Tähän laske pop() XOR pop() ja push() pinoon
				// push(pop() + pop()
				luku2 = pop();
				luku1 = pop();
				pot = pow(2, muuttujatlkm);
				tulos = laske(pot, luku1, luku2, 'E');

				tulos2 = not(bb, tulos);
				push(tulos2);
				cout << "=:";
				tulos3 = muunnaBinaari(pot, tulos2, true);
				cout << endl;
			case '\n':
				//cout << "Loppu:" << pop() << endl;
				break;
			default:
				cout << "Virhe: Tuntematon komento" << s << endl;
				break;
		}
	i++;
	}
	
	cout << "Lopputulos taulukosta tulos3:" << endl;
	std::unordered_map<int, tietue> taulukko;
	std::unordered_map<int, tietue> taulukko2;
	std::unordered_map<int, tietue> taulukko3;
	std::unordered_map<int, tietue> taulukko4;

	vector<pair<int, int>> iv;
	vector<pair<int, int>> iv2;
	vector<pair<int, int >> tunnusparit;
	vector<pair<int, int>> tunnus_id_muunnos;
		
	//vector<tietue> iv;
	
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
	
	//int tt[3] = { 0, 1, 1};

	//string st = convert_int_to_string(tt, 3);
	//cout << "convert_int_to_string:" << st << endl;
	// Tarkista tunnuksen muuntaminen jollain lausekkeella !

	for(int a=pot-1; a>=0; a--){		
		//cout << tulos3[a] << ",";
		// Täytä int taulukko indeksin mukaiseen järjestykseen !
		if(tulos3[a] == 1){
			tietue t;
			vector<int> v;
			tulos4 = muunnaBinaari(muuttujatlkm, b, false);
			
			indeksi += tulostaKanooninen(tulos4, muuttujatlkm);
			cout << " bin: ";
			tulostaBin(tulos4, muuttujatlkm);
			cout << " indeksi:" << indeksi << " tunnus:" << b << endl;
			// Katso delete funktiota !!
			v.push_back(b);
			cout << "v.at(0):" << v.at(0) << endl;

			t.bin = convert_int_to_string(tulos4, muuttujatlkm);
			t.r_indeksi = laskeYkkoset(t.bin, muuttujatlkm);			
			t.tunnus = v;
		
			cout << "laskeYkkoset:" << t.r_indeksi << endl;
			taulukko.insert(pair<int, tietue>(e, t));
			
			iv.emplace_back(t.r_indeksi, e);
			// new tietue(convert_int_to_string(tulos4, muuttujatlkm), v.push_back(b)
			
			e++;
		}
	indeksi=0;
	b++;
	}
	// Käännä ja aja !!
	//pis aa{ 2, "a" }, bb{ 1, "b" }, cc{ 1, "c" }, dd{ 1, "d" }, ee{ 3, "e" };
	//vector<pis> iv{pair<int, string>(5, "a"), pair<int, string>(3, "b"), pair<int, string>(4, "c"), pair<int, string>(3, "d"), pair<int, string>(3, "e") };	
	//pari p{ 1, t };
	//iv.insert(pair<int, tietue>(1, t));'
	
	stable_sort(iv.rbegin(), iv.rend());
	int ii = 0;


	//for (auto f : iv) {
	for (auto it2 = iv.rbegin(); it2 != iv.rend(); ++it2) {
		tietue t2;
		vector<int> v2;
		//std::cout << it2->first << "," << it2->second << endl;
		//cout << "bin:" << taulukko.at(it2->second).bin << ",";
		//cout << "r_indeksi:" << taulukko.at(it2->second).r_indeksi << ",";
		//cout << "tunnus:" << taulukko.at(it2->second).tunnus.at(0) << endl;
		v2.push_back(taulukko.at(it2->second).tunnus.at(0));

		t2.bin = taulukko.at(it2->second).bin;
		t2.r_indeksi = taulukko.at(it2->second).r_indeksi;
		//t2.tunnus = taulukko.at(it2->second).tunnus.at(0);
		t2.tunnus = v2;
		// Tulosta taulukon sisältö, joka nyt on järjestyksessä!
		taulukko2.insert(pair<int, tietue>(ii, t2));
		//cout << f.second << ", " << f.first << "," << endl;
		// Vapauta nämä kun tuntuu siltä!
		//	cout << taulukko2.at(ii).tunnus.at(0) << endl;
		//	cout << taulukko2.at(ii).r_indeksi << endl;
		cout << "bin:" << taulukko2.at(ii).bin << ",";
		cout << "r_indeksi:" << taulukko2.at(ii).r_indeksi << ",";
		cout << "tunnus:" << taulukko2.at(ii).tunnus.at(0) << endl;
		iv2.emplace_back(t2.r_indeksi, ii);
		
		cout << "tunnus:" << t2.r_indeksi << endl;
		//cout << f.first << endl;
		ii++;			
	}

	// Tee nyt sellainen silmukka joka parittaa termin tunnuksien avulla siten että indeksi on yhden suurempi kuin tunnus !!!
	for (auto it2 = iv2.begin(); it2 != iv2.end(); ++it2) {
		// Talletetaan ryhmä_id f:ään.
		int f = taulukko2.at(it2->second).r_indeksi;
		//cout << "it2->second.r_indeksi:" << taulukko2.at(it2->second).r_indeksi << endl;
		//cout << it2->first << "," << it2->second << endl;
		for (auto it3 = iv2.begin(); it3 != iv2.end(); ++it3) {
			
			// Talletetaan toinen ryhmä_id g:een
			int g = taulukko2.at(it3->second).r_indeksi;
		//	cout << "it3->second.r_indeksi:" << taulukko.at(it3->second).r_indeksi << endl;
			cout << "f:" << f << "g:" << g << endl;
			//cout << it2->second << "," << it3->second << endl;
			// Verrataan f ja g -ryhmiä
			if (f + 1 == g && taulukko2.at(it2->second).tunnus.at(0) < taulukko2.at(it3->second).tunnus.at(0)) {
				// Tallennetaan termin tunnus parit tunnusparit vektoriin
				
				tunnusparit.emplace_back(taulukko2.at(it2->second).tunnus.at(0), taulukko2.at(it3->second).tunnus.at(0));
				tunnus_id_muunnos.emplace_back(it2->second, it3->second);
				//cout << "(" <<  taulukko.at(it2->second).tunnus.at(0) << "," << taulukko.at(it3->second).tunnus.at(0) << ")" << endl;
				//	cout << " OK" << endl;
			}
		}
		//cout << f+1 << endl;
	}
	//stable_sort(tunnusparit.rbegin(), tunnusparit.rend());
	
	// Tulostetaan kaikki tunnusparit
	int laskuri2 = 0;
	int laskuri3 = 0;
	int laskuri4 = 0;
	int laskuri5 = 0;
	int laskuri6 = 0;
	int laskuri7 = 0;
	int laskuri8 = 0;
	int laskuri11 = 0;
	int laskuri12 = 0;
	

	for (auto it4 = tunnusparit.begin(); it4 != tunnusparit.end(); ++it4) {
		cout << "(" <<  it4->first << "," << it4->second << ")" << endl;
		// Tässä lasketaan binaarit (suurempi ensin 001 - 000)
		//if (it4->first < it4->second) {		
		laskuri2++;
		cout << endl;
	}
	
	
	// Tulostetaan kaikki tunnusparien binaariset arvot, niiden indeksien perusteella
	
	for (auto it5 = tunnus_id_muunnos.begin(); it5 != tunnus_id_muunnos.end(); ++it5) {
		//cout << it5->first << ",";
		//cout << it5->second;
	//for(auto it5=tunnus_id_muunnos.begin(); it5 != tunnus_id_muunnos.end(); ++it5){
		cout << taulukko2.at(it5->first).tunnus.at(0) << ",";
		cout << taulukko2.at(it5->second).tunnus.at(0);
		cout << endl;
		tietue t3;
		vector<int> v3;
		
		v3.push_back(taulukko2.at(it5->first).tunnus.at(0));
		v3.push_back(taulukko2.at(it5->second).tunnus.at(0));
		
		for (int h = 0; h < muuttujatlkm; h++) {
			
			char i = taulukko2.at(it5->first).bin.at(h);
			char j = taulukko2.at(it5->second).bin.at(h);
			//bool ii = false;
			//bool jj=false;
			bool kk=false;
			bool ll = false;
			cout << i << "," << j << endl;
			/*
				kk = laskeXOR(i, j);
			//	cout << kk;
				//t3.bin.at(h) = kk;
				
				if (kk == true) {
					cout << "-";
					t3.bin.append("-");
				}
				cout << "=";
				cout << kk;

				ll = laskeAND(i, j);

				if (ll == true && kk == false) {
					//cout << "1";
					t3.bin.append("1");
				}
				else if (ll == false && kk == false) {
					t3.bin.append("0");
				}*/
			//}
			//else {				
				//cout << (jj ^ ii);				
				//kk = (jj ^ ii);
				kk = laskeXOR(i, j);
				
				if (kk == true) {
					cout << "-";
					t3.bin.append("-");
				}				
				cout << "=";
				cout << kk;	
				
				ll = laskeAND(i, j);

				if (ll == true && kk == false) {
					//cout << "1";
					t3.bin.append("1");
					laskuri4++;
				} else if(ll == false && kk == false) {
					t3.bin.append("0");
				}
		//	}
		//cout << h;
		/* Ja nyt lasku rediksi !
		cout << ", ";*/
		
		cout << endl;
		}		
		
		t3.r_indeksi = laskuri4;
		t3.tunnus = v3;
		cout << t3.bin;
		cout << "r_id:" << t3.r_indeksi;
		cout << endl;
		taulukko3.insert(pair<int, tietue>(laskuri3, t3));
		laskuri3++;
		laskuri4 = 0;
	}
	bool osuma = false;

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

		cout << it6->second.r_indeksi << endl;
		tietue t4;
		vector<int> v4;
		
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
				//int eka2 = it7->first.tunnus.at(0);
				//int toka2 = it7 

				cout << kolmas << ",";
				cout << neljas << endl;
				cout << it7->second.bin << endl;
				// JATKA TÄSTÄ !! JA VERTAA NYT INDEKSILISTAA TOISEEN
				for (int h2 = 0; h2 < muuttujatlkm; h2++) {
					
					char k = it6->second.bin.at(h2);
					char l = it7->second.bin.at(h2);
					//bool ii = false;
					//bool jj = false;
					/*
					bool ll = false;

					ll = laskeAND(k, l);
					kk = laskeXOR(k, l);

					if (ll == true && kk == false) {
						//cout << "1";
						s1.append("1");
						laskuri5++;
					}
					else if (ll == false && kk == false) {
						s1.append("0");
					} else if (kk == true) {
						//cout << "-";
						s1.append("-");
					}
					*/					
					// Katso nyt t4.bin listaa kaksoisarvojen valossa !
					//cout << k << "," << l << endl;
					if (k == '-' && l == '-') {
						cout << "Osuma" << endl;
						// XOR:in tulos k ja l tallennetaan tietue t4:ään
						osuma = true;

						//if (kk == true) {
							//cout << "-";
						s1.append("-");
							
						//}
						//cout << "=";
						//cout << kk;
						/*
						ll = laskeAND(k, l);

						if (ll == true && kk == false) {
							//cout << "1";
							t4.bin.append("1");
							laskuri5++;
						}
						else if (ll == false && kk == false) {
							t4.bin.append("0");
						}*/
						
					} else if(k != '-' && l != '-') {
						bool ll = false;

						ll = laskeAND(k, l);
						kk = laskeXOR(k, l);

						if (ll == true && kk == false) {
							//cout << "1";
							s1.append("1");
							laskuri5++;
						}
						else if (ll == false && kk == false) {
							s1.append("0");
						}
						else if (kk == true) {
							//cout << "-";
							s1.append("-");
						}
					}
					else {
						if (k == '-') {
							s1.push_back(l);
						}
						else {
							s1.push_back(k);
						}
					}
					cout << "s1:" << s1 << endl;
				}
				if (osuma) {
					t4.bin = s1;
					cout << "t4.bin:" << endl;
					cout << t4.bin << endl;
					v4.push_back(it6->second.tunnus.at(0));
					v4.push_back(it6->second.tunnus.at(1));
					v4.push_back(kolmas);
					v4.push_back(neljas);
					t4.r_indeksi = laskuri5;
					t4.tunnus = v4;

					taulukko4.insert(pair<int, tietue>(laskuri6, t4));
					laskuri6++;
					osuma = false;
				}
				cout << endl;
			}
			
		}
		
		laskuri4 = 0;
	}

	int* laskuri9 = new int[laskuri6];
	// Ja nyt katso taulukko4:n tulokset ja poistetaan KAKSOISARVOT
	cout << "Vertaapa:" << endl;
	//cout << taulukko4.size() << endl;
	 
	for (auto it8 = taulukko4.begin(); it8 != taulukko4.end(); ++it8) {
		int eka = it8->second.tunnus.at(0);
		int toka = it8->second.tunnus.at(1);
		int kolmas = it8->second.tunnus.at(2);
		int neljas = it8->second.tunnus.at(3);
		cout << "Muuttuja 1" << endl;
		cout << laskuri11 << endl;
		//cout << eka << ",";
		//cout << toka << ",";
		//cout << kolmas << ",";
		//cout << neljas << endl;
		laskuri12 = laskuri11 + 1;
		
		//cout << it8->second.bin << endl;
		for (auto it9 = taulukko4.begin(laskuri12); it9 != taulukko4.end(); ++it9) {
			int eka1 = it9->second.tunnus.at(0);
			int toka1 = it9->second.tunnus.at(1);
			int kolmas1 = it9->second.tunnus.at(2);
			int neljas1 = it9->second.tunnus.at(3);
			cout << "Muuttuja 2" << endl;
			cout << laskuri12 << endl;
			//cout << eka1 << ",";
			//cout << toka1 << ",";
			//cout << kolmas1 << ",";
			//cout << neljas1 << endl;		
			if (eka == eka1 && toka == toka1 && kolmas == kolmas1 && neljas == neljas1) {
				// Ja nyt katso taulukko4:n tulokset
				for (int h3 = 0; h3 < muuttujatlkm; h3++) {

					char k = it8->second.bin.at(h3);
					char l = it9->second.bin.at(h3);
					if (k == l) {						
						laskuri8++;
					}
				}
				if (laskuri8 == muuttujatlkm) {
					cout << "Osuma" << endl;
					laskuri9[laskuri7] = it9->first;
					laskuri7++;
				}				
			}
		}		
		//laskuri7 = 0;
		laskuri8 = 0;
		laskuri11++;
	}
	cout << "Poistetaan kaksoisarvot:" << endl;
	cout << laskuri7 << endl;
	// Poistetaan kaksoisarvot
	for (int laskuri10 = 0; laskuri10 < laskuri7; laskuri10++) {
		cout << laskuri9[laskuri10] << endl;
		taulukko4.erase(laskuri9[laskuri10]);
	}
	
		//taulukko4.erase(it9);
		//	taulukko4.erase(1);
		//	taulukko4.erase(it9->first);	

	cout << "Tulosta taulukko4:" << endl;
	// Tulosta taulukko4
	/*
	for (auto it10 = taulukko4.begin(); it10 != taulukko4.end(); ++it10) {
		cout << it10->second.tunnus.at(0);
		cout << it10->second.tunnus.at(1); 
		cout << it10->second.tunnus.at(2);
		cout << it10->second.tunnus.at(3);
	}
	*/
	//taulukko2.
/*	taulukko.insert(pair<int, tietue>(1, t));
	taulukko.insert(pair<int, int>(2, 1));
	taulukko.insert(pair<int, int>(0, 2));
	taulukko.insert(pair<int,int>(1, 3));
	*/
	// Nyt järjestä unsorted map ryhmä indeksin mukaiseen järjestykseen !



	/*
	for (int c = 0; c < taulukko.size(); c++) {
		//jarjesta_unsortedmap(taulukko.at(c));
		tluku = taulukko.at(c).r_indeksi;
		tunnus1 = taulukko.at(c).tunnus.at(0);
		cout << "tunnus: " << tunnus1 << endl;
		//tluku = taulukko[c].r_indeksi;
		cout << "tluku: " << tluku << endl;
		
		for (int d = 0; d < taulukko.size(); d++) {
			//cout << "tluku2:" << taulukko.at(d).r_indeksi << endl;
			//if (c == d) {
				// Indeksit ovat samoja, ei verrata
			//} else {
				tluku2 = taulukko.at(d).r_indeksi;
				tunnus2 = taulukko.at(d).tunnus.at(0);
				//cout << tunnus2 << endl;
				//cout << "tluku2:" << tluku2 << endl;
				if (tluku <= tluku2 && tunnus1 <= tunnus2) {
					// Testataan tulostuuko oikeat numerot ! J A T K A !
					//cout << "Onnistui" << endl;
					//cout << "tluku: " << tluku << endl;					
				}
				else {
					//cout << "tluku:" << tluku << endl;
					//cout << "tlaskuri:" << tlaskuri << endl;
					tlaskuri++;
				}
			//}			
		}
		cout << endl;
		//tlaskuri = 0;
	}*/
	/*for (auto i = taulukko.begin(); i != taulukko.end(); i++) {
	
		cout << "first:" << i->first << endl;
		cout << "second:" << (tietue)i->second << endl;
	}
	*/
// Label funktio

	/*
	muunnaBinaari(bb, 255);
	cout << endl;
	muunnaBinaari(bb, 21845);
	cout << endl;
	int tulos = laske(bb, 255, 21845, 'A');
	//int tulos2 = not(bb, tulos);

	//cout << tulos << endl;
	muunnaBinaari(bb, tulos);
	*/
return 0;
}