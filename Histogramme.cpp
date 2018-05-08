// Histogramme.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include<iostream>
#include<string>
#include"Histo.h"
using namespace std;

int main()

{

	//obro el fitxer 
	Histo histo;
	cout << "NOM FITXER:" << endl;
	string nom_fitxer;
	cin >> nom_fitxer;
	ifstream in_file(nom_fitxer.c_str());
	if (in_file.is_open()) {
		histo.llegir_fitxer(in_file,nom_fitxer);
		histo.mostraResum();
		histo.mostra_vector();
	}
	else {
		cout << "FITXER INEXISTENT" << endl;
	}
	return 0;
}