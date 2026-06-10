#pragma once
#include <string>
#include <iostream>
#include <vector>
//using namespace std;

class tietue
{
public:
	int r_indeksi=0;
	std::string bin;
	std::vector<int> tunnus;
	
	tietue() {}
	tietue(int r_id, std::vector<int> t,  std::string s) {
		r_indeksi = r_id;
		bin = s;
		tunnus = t;
		
	}	
};

int priority(char op);
int collectMlkm(std::string infix);
std::string concats(std::string infix);
std::string getF();
std::string convert(std::string infix);
int haeMlkm();
