#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Histo
{
public:
	Histo();
	Histo(const Histo &o);//constructor de copia
	Histo & operator=(const Histo &o);
	void llegir_fitxer(ifstream & in_file,string nom_fitxer);
	void mostra_vector()const;
	void mostraResum()const;
	~Histo();

private:
	unsigned h_max;
	int *h_t;
	unsigned h_n;
	unsigned _words;
	unsigned _spaces;
	unsigned _chars;
	bool es_separador(char lletra)const;
	void passar_separadors(ifstream &infile);
	void passar_paraula(ifstream &in_file);
	void inicialitza_vector(int *v);
	int retorna_Max_position() const;
	unsigned retornPosicioMinim()const;
	void reserva();
	void expandir(int mida);
	void copiar(const Histo& o);
	void alliberar();
};

