/**
*
Anna merkkijono käänteinen Lukasievich -muodossa esim. A B + A C + *
Anna merkkijono (A'*C)+(A'*B)+(A*B'*C') muodossa
Ohjelma laskee merkkijonon loogisen arvon.
Muoto voi olla myös lyhyempi, kuten AB*AC+*.
Huomaa unordered_map:in tuonti sovellukseen!!
F(A,B,C)=((A'*C)+(A'*B)+(A*B'*C')) OK OK <= TÄMÄ LAUSEKE ON VÄÄRÄNLAINEN ÄLÄ KÄYTÄ TÄTÄ!
F(A,B,C)=((A'*C)+(A'*B)+((A*B')*C')) TÄSSÄ TOINEN VERSIO LAUSEKKEESTA  J A T K A ! !
POS:
F(A,B,C)=((A'+C')*(A'+B')*((A+B)+C))
SOP:
F(A,B,C)=((A'*C)+(A'*B)+((A*B')*C'))

SOP:
F(A,B,C)=((A'*C)+(B')) OK OK
POS:
F(A,B,C)=((B'+C)*(A'+B')) OK

F(A,B,C)=((A*(B+C))') OK OK 

F(A,B,C)=((A*B)+(A*C)) OK OK 

F(A,B,C)=((A*(B+C))) OK	OK		Katso myös max termit(c:\users\marku\ba.txt)
Joka on F(A,B,C)=(((A*(B+C)))=((A*B)+(A*C)))=((A'+C)+(B+A)) OK OK
F(A,B,C)=((A'+B')+(C'+C)+(B+A)) OK OK
F(B,C,D)=((B*C')+(B*D)) OK NOT WORKING
F(A)=((A'+A)) OK OK
												
Ylläoleva lauseke on oikein
Parittomien testaukseen:
F(A,B,C)=(((A'*B'*C')+(A*B'*C)+(A*B*C)))=((A*C)+(A'*B'*C'))  OK OK
F(A,B,C)=((A'*B'*C')+(A'*B*C)+(A*B'*C)) OK OK
Neljän muuttujan testaus:
F(A,B,C,D)=((A*B)+(C*D)) OK OK
F(B,C,D)=((B*C')+(B*D)) OK
F(D)=((D*D')) OK
Kolmen muuttujan testaus:
F(B,C)=((B*C)+(B'*C')) OK
F(C)=((C*C')) OK

Uusi päivitetty versio syötettävän lauseen syöttö formaatissa:
F(A,B,C)=((A'+A)) OK
F(A,B)=((A+(A*B))) OK OK
jotta saadaan kahdeksan bittinen tulos!
Uusin päivitetty versio ottaa vastaan yhtä ja nollaa! Seuraavat lauseet toimivat:
F(A)=((A+0)) OK
F(A)=((A*0)) OK
F(A)=((A+1)) OK
F(A)=((A*1)) TÄMÄ !!! MELKEIN KAIKKI OK
Nyt lisätään sovellukseen lausekkeen syöttö parametrinä!

SOP, jonka tulos on 1:
F(A,B,C)=((A'+B')+(C'+C)+(B+A)) OK
POS:
G(A,B,C)=((A'+B')+(C'+C)+(B+A))

SOP, jonka tulos on 0:
F(A,B,C)=((A*B)*(C*C')*(B'*A')) OK
F(A,B)=(((A*B)+A))
Käännä sovellus
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
#include <string>
#include "infix_to_postfix.h"
#include "quine_mccluskell.h"
#include "karnaugh.h"
#include "asm_ba.h"
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
//int laskuri3 = 0;
int jakojaannos=0;

double mlkm2 = 0.0;
int pause=0;
int bb=16;

int b = 0;

size_t koko = 16;
char s[MAXOP];

int A[4]={1, 3, 15, 255};
int B[4]={-1,5, 51, 3855};
int C[4]={-1,-1,85, 13107};
int D[4]={-1,-1,-1, 21845};

int nolla[4] = {0,0,0,0};
int yksi[4] = {3, 15, 255, 65535};

//char merkit[4] = {'A','B','C','D'};

int pot;
int muuttujatlkm;

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
	int laskuri2=0;
	funktio:	
//laskuri++;

	//if(jakotulos > 2)
		jakojaannos = jakotulos;
		jakotulos = jakotulos/2;
		jakojaannos = jakojaannos%2;
	//else
	//	jakotulos = 2/jakotulos;
	tulos[laskuri2]=jakojaannos;
	
	//if(jakotulos>0)goto funktio;
	//else goto end;
	if(laskuri2 == bitti-1){
		goto end;
	}else{
		//taulukko[laskuri]=0;
		if(jakotulos==0){
			//cout << "-" << endl;
		}
		laskuri2++;
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

std::string convert_int_to_string(int arr[], int size) {
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

string lauseke_postfix() {	
	cout << "Anna lauseke:" << endl;
	cin.getline(s, 100);
	string infix(s);
	//cout << "infix: " << infix << endl;
	muuttujatlkm = collectMlkm(infix);
	//cout << "Muuttujien lkm:" << muuttujatlkm << endl;
	infix = concats(infix);
	//cout << "infix:" << infix << endl;
	mlkm2 = muuttujatlkm;
	return convert(infix);
}

string pura_parametrit(int argc, char* argv[]) {
	//string infix2;
	int count = 0;

	cout << "\nKomentorivin argumentit:\n";
	for (count = 0; count < argc; count++) {
		cout << "  argv[" << count << "]   "
			<< argv[count] << "\n";

	}
	string infix2(argv[1]);
	//cout << "infix2:" << infix2 << endl;
	muuttujatlkm = collectMlkm(infix2);
	//cout << "Muuttujien lkm:" << muuttujatlkm << endl;
	infix2 = concats(infix2);
	//cout << "infix2:" << infix2 << endl;
	mlkm2 = muuttujatlkm;
	return convert(infix2);
}

int* laske_lauseke(const char* toinen) {
	int* t3;
	int type, i = 0;
	int luku1, luku2;
	int tulos, tulos2;

	//cout << "toinen:" << toinen << endl;
	
	laskuri = muuttujatlkm-1;
	//laskuri = haeMlkm()-2;
	//cout << "haeMlkm:" << laskuri << endl;
	while ((type = toinen[i]) != '\0') {
		//while((type = getop(s)) != 10){
		switch (type) {
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
			//cout << "laskuri:" << laskuri << endl;
			break;
		case 66:
			cout << "B:";
			//cout << "laskuri:" << laskuri << endl;
			pot = pow(2, muuttujatlkm);
			//cout << "pot:" << pot << endl;
			push(B[laskuri]);
			//cout << "B(" << laskuri << "):" << B[laskuri] << endl;
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
		case 48:
			cout << "0:";
			push(nolla[laskuri]);
			muunnaBinaari(pot, nolla[laskuri], true);
			cout << endl;
			break;
		case 49:
			cout << "1:";
			pot = pow(2, muuttujatlkm);
			//cout << "Numero:" << yksi[laskuri] << endl;
			push(yksi[laskuri]);
			muunnaBinaari(pot, yksi[laskuri], true);
			cout << endl;
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
			t3 = muunnaBinaari(pot, tulos, true);
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
			t3 = muunnaBinaari(pot, tulos, true);
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
			t3 = muunnaBinaari(pot, tulos2, true);
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
			t3 = muunnaBinaari(pot, tulos2, true);
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
	return t3;
}

int main(int argc, char* argv[]){
	int* tulos3;
	string postfix;

	if (argc > 1)
		postfix = pura_parametrit(argc, argv);
	else
		postfix = lauseke_postfix();
	
	tulos3 = laske_lauseke(postfix.c_str());
	//const char* toinen = postfix.c_str();
	//cout << "tulos3:" << tulos3 << endl;
	//cout << "Lopputulos taulukosta tulos3 SOP:" << endl;
	bool bs = lopputulos_SOP(tulos3, pot, muuttujatlkm);		
			
	//cout << "\nrakennaTaulukko2:" << endl;
	rakennaTaulukko2();
	muuttujienAlustus();
	//cout << "muuttujienParitus1:" << endl;
	muuttujienParitus1(muuttujatlkm);
	muuttujienParitus2(muuttujatlkm);
	vertaaTaulukkoja1(muuttujatlkm);
	vertaaTaulukkoja2(muuttujatlkm);
	poistaKaksoisarvot_ja_tulosta(muuttujatlkm);
	uusioKaytto(muuttujatlkm);
	poistaKaksoisarvot2(muuttujatlkm);
	tulostaTaulukot5ja6(muuttujatlkm);
	// Allaoleva funktio ei ole pakollinen; kommentoi se jos videoi!
	//alusta_aseta_ja_tulosta_matriisi(muuttujatlkm);
	poistaParilliset_ja_tulosta();
	//asetaTaulukko_ja_tulostaTaulukko(muuttujatlkm);
	poistaParilliset_ja_tulostaTaulukko2();
	asetaTaulukko_ja_tulosta2(muuttujatlkm);
	
	//cout << "Matriisin taytto ja lasku" << endl;
	matriisinTaytto_ja_lasku(muuttujatlkm);
	//cout << "\nSiirraTaulukot_ja_laske matriisin tulos!" << endl;
	siirraTaulukot_ja_laskeMatriisin_tulos();
	//cout << "TulostaSOP:" << endl;
	tulostaSOP(muuttujatlkm, pot);

	//cout << "\nTulosta POS:" << endl;
	bool bs2 = tulostaPOS(tulos3, pot, muuttujatlkm);
	//cout << "\nrakennaTaulukko2:" << endl;
	rakennaTaulukko2();
	muuttujienAlustus();
	
	//cout << "muuttujienParitus1:" << endl;
	muuttujienParitus1(muuttujatlkm);
	muuttujienParitus2(muuttujatlkm);
	vertaaTaulukkoja1(muuttujatlkm);
	vertaaTaulukkoja2(muuttujatlkm);
	poistaKaksoisarvot_ja_tulosta(muuttujatlkm);
	uusioKaytto(muuttujatlkm);
	poistaKaksoisarvot2(muuttujatlkm);
	tulostaTaulukot5ja6(muuttujatlkm);
	poistaParilliset_ja_tulosta();
	//cout << "\npoistaParilliset_ja_tulostaTaulukko2:" << endl;
	poistaParilliset_ja_tulostaTaulukko2();
	//cout << "\nasetaTaulukko_ja_tulosta2:" << endl;
	asetaTaulukko_ja_tulosta2(muuttujatlkm);
	//cout << "\nMatriisin taytto ja lasku:" << endl;
	matriisinTaytto_ja_lasku(muuttujatlkm);
	//cout << "\nSiirraTaulukot_ja_laske matriisin tulos!" << endl;
	siirraTaulukot_ja_laskeMatriisin_tulos();
	// TulostaPOS2 on kommentissa siihen saakka, että saadaan aikaan POS -tulos ja
	// tulostus on (-00)' = B+C ja (0--)' = A ja sitä rataa. Se täytyy korjata tulostaPOS2 funktioon!
	
	tulostaPOS2(muuttujatlkm, pot);	
						
return 0;
}