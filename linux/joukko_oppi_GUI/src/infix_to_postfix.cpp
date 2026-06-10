#include <cmath>
#include <iostream>
#include <stack>
#include <ctype.h>
#include <vector>
#include <string>
#include "infix_to_postfix.h"
using namespace std;
/**
 * Infixist? postfix lauselogiikan lausekkein SULKEIN varusteltuna:
 * (a*b)+(a*c)
 */
int mlkm=0;
int em = 0;
int ii = 0;
string f;

int priority(wchar_t op){
	if(op == L'\u222A' || op == L'\u2229')
		return 1;
	if(op == L'\u223C' ||op == L'\u003D')
		return 2;
	if (op == L'\u2282')
		return 3;
	return 0;
}

// T?ss?kohdin on hieman viel? hiomista
int haeMlkm(){

return em;
}

int palautaKoko() {
	return ii;
}

int collectMlkm(string infix) {
	// F(A,B,C) =
	int a = 0, b = 0, c = 0, d = 0;
	int g = infix.find("(");
	int e = infix.find(")");
	cout << "collectMlkm, g:" << g << "e:" << e << endl;
	for (int j = g; j < e; j++) {
		if (infix[j] >= 'a' && infix[j] <= 'z' || infix[j] >= 'A' && infix[j] <= 'Z') {
			cout << infix[j] << endl;

			if (infix[j] == 'A' || infix[j] == 'a') {
				mlkm++;
			}
			else if (infix[j] == 'B' || infix[j] == 'b') {
				mlkm++;
			}
			else if (infix[j] == 'C' || infix[j] == 'c') {
				mlkm++;
			}
			else if (infix[j] == 'D' || infix[j] == 'd') {
				mlkm++;
			}
		}
	}
	return mlkm;
}

string concats(string infix) {
	int alku = infix.find("=");
	int loppu = infix.size();
	f = infix.substr(0, alku+1);
	//cout << f << endl;
	infix = infix.substr(alku+1, loppu);
	return infix;
}

string getF() {
	
	//int alku = infix.find("=");
	//int loppu = infix.size();
	//f = infix.substr(0, alku);
	//cout << f << endl;
	return f;
}

wstring convert(wstring infix){
	int i=0, i2=0;
	int a=0, b=0, c=0, d=0;
	int yksi = 0, nolla = 0;
	wstring postfix = (L"");
	stack <wchar_t>s;
	
	//while(infix[i]!='\0'){
	while(i < infix.size()){
		wcout << "kierros:" << i << endl;
		
		if(infix[i]>='w' && infix[i]<='z' || infix[i]>='W' && infix[i]<='Z' || infix[i]=='1' || infix[i]=='0') {
			postfix += infix[i];
			wcout << "infix[i]:" << infix[i] << endl;
			/*
			if((infix[i] == 'a' || infix[i] == 'A') && a==0 && b==0 && c==0 && d==0){
				em++;
				a++;
				cout << "elementMultiplier:" << em << endl;
			}else if((infix[i] == 'b' || infix[i] == 'B') && b==0 && c==0 && d==0){
				em++;
				if (a == 0) em++;
				b++;
				cout << "elementMultiplier: " << em << endl;
			}else if((infix[i] == 'c' || infix[i] == 'C') && c==0 && d==0){
				em++;
				if (a == 0 && b == 0) em = em + 2;
				else if (b == 0) em++;
				c++;
				cout << "elementMultiplier:" << em << endl;
			}else if((infix[i] == 'd' || infix[i] == 'D') && d==0){
				em++;
				//cout << "INFIX D !!!" << endl;
				if (a == 0 && b == 0 && c == 0) {
					em = em + 3;
				}
				else if (b == 0 && c == 0) {
					em = em + 2;
				}
				else if (c == 0) {
					em++;
				}
				
				d++;
				cout << "elementMultiplier:" << em << endl;								
			}*/
			i2++;
			i++;
		}else if(infix[i]=='('){
			s.push(infix[i]);
			i++;
		}else if(infix[i]==')'){
			while(s.top()!='('){
				postfix+=s.top();
				s.pop();
			}
			s.pop();
			i++;
		}else{
			while(!s.empty() && priority(infix[i]) <= priority(s.top())){
				postfix += s.top();
				s.pop();
			}
			s.push(infix[i]);
			i++;
			i2++;
		}        		
	}
	ii = i2;
	while(!s.empty()){
		postfix += s.top();
		s.pop();
	}

	wcout << "Postfix is : " << postfix;

	return postfix;
}


