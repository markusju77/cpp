#pragma once
#include <string>
#include <iostream>
#include <gtk/gtk.h>

using namespace std;

class quine_mccluskell
{
public:
	quine_mccluskell(void);
	~quine_mccluskell(void);
};

bool lopputulos_SOP(int* tulos3, int pot, int muuttujatlkm);
bool tulostaPOS(int* tulos3, int pot, int muuttujatlkm);
void rakennaTaulukko2();
void muuttujienAlustus();
void muuttujienParitus1(int muuttujatlkm);
void muuttujienParitus2(int muuttujatlkm);
void vertaaTaulukkoja1(int muuttujatlkm);
void vertaaTaulukkoja2(int muuttujatlkm);
void poistaKaksoisarvot_ja_tulosta(int muuttujatlkm);
void uusioKaytto(int muuttujatlkm);
void poistaKaksoisarvot2(int muuttujatlkm);
void tulostaTaulukot5ja6(int muuttujatlkm);
void alusta_aseta_ja_tulosta_matriisi(int muuttujatlkm);
void poistaParilliset_ja_tulosta();
void asetaTaulukko_ja_tulostaTaulukko(int muuttujatlkm);
void poistaParilliset_ja_tulostaTaulukko2();
void asetaTaulukko_ja_tulosta2(int muuttujatlkm);
void matriisinTaytto_ja_lasku(int muuttujatlkm);
void siirraTaulukot_ja_laskeMatriisin_tulos();
void tulostaSOP(int muuttujatlkm, int pot, GtkWidget *sop);
void tulostaPOS2(int muuttujatlkm, int pot, GtkWidget *pos);
void tulostaBin(int *luku, int bittisyys);
int tulostaKanooninen(int *luku, int bittisyys);
int laskeIndeksi(int* luku, int bittisyys);
int laskeYkkoset(string luku, int bittisyys);
bool laskeXOR(char i, char j);
bool laskeAND(char i, char j);
int vertaaTaulukko4(int eka, int toka, int kolmas, int neljas, int eka1, int toka1, int kolmas1, int neljas1);
