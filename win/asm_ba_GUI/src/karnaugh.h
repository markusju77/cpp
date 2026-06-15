#pragma once
#include <unordered_map>
using namespace std;
class karnaugh
{
};
/*
int arvotNelja[4] = {0,2,1,3};
int arvotKasi[8] = {0,2,6,4,1,3,7,5};
int arvotKuustoista[16] = {0,4,12,8,1,5,13,9,3,7,15,11,2,6,14,10};
int tyhjienlkm = 0;

// Taulukko5 on Karnaughin kartta
std::unordered_map<int, int> taulukko5;
// Iterator12 on Karnaughin kartta
std::unordered_map<int, int>::iterator it12;*/
void alustaTaulukko(int lkm, int mlkm);
void tulostaTaulukko(int lkm, int mlkm);
void asetaTaulukko(int pluku, int arvo);
void nollaaTyhjienlkm();

