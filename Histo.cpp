//#include "stdafx.h"
#include "Histo.h"
#include<iomanip>

Histo::Histo()
{
	h_max =100;
	h_n = h_max;
	reserva();
	_words = 0;
	_chars = 0;
	_spaces = 0;
	inicialitza_vector(h_t);
}
Histo::Histo( const Histo& o)
{
	copiar(o);
}

Histo::~Histo()
{
	alliberar();
}

void Histo::reserva() {
	h_t = new int[h_max];
}
void Histo::expandir(int mida) {
	h_max =2*h_max;
	h_n = h_max;
	int *aux = new int[h_max];
	inicialitza_vector(aux);
	for (int i = 0; i < h_n; i++)aux[i] = h_t[i];
	delete[]h_t;
	h_t = aux;
	mostra_vector();
}
void Histo::copiar(const Histo& o) {
	h_max = o.h_max;
	h_n = o.h_n;
	h_t = new int[h_max];
	for (int i = 0; i < h_n; i++)h_t[i] = o.h_t[i];
}
void Histo::alliberar() {
	delete[]h_t;
}

Histo &Histo:: operator=(const Histo& o) {
	if (this != &o) {
		alliberar();
		copiar(o);
	}
	return *this;
}

bool Histo:: es_separador(char lletra) const{
	/*Pre: cert
	Post: retorna cert si lletra és un separador, fals altrament */
	bool separador = true;
	if (lletra >= 'a' && lletra <= 'z') separador = false;
	else if (lletra >= 'A' && lletra <= 'Z') separador = false;
	//else if (lletra >= '0' && lletra <= '9') separador = false; 
	//else if (lletra == EOS) separador = false; //només si susa marca de fi lògica 
	else { //considerem els caràcters especials catalans i castellans 

	}
	return separador;
}

void Histo:: passar_separadors(ifstream &in_file) {
	/*Pre: fitxer obert
	Post: shan llegit tots els separadors del fitxer*/
	char lletra;
	in_file.get(lletra);
	while (!in_file.eof() && es_separador(lletra)) {
		_spaces++;
		lletra = in_file.get();
	}
	//separador.separadors- 1; 
	if (!in_file.eof())in_file.unget(); //pot no ser necessari 
}

void Histo:: passar_paraula(ifstream &in_file) {
	/*Pre: fitxer vàlid i apunt de llegir el 1r carácter duna paraula
	Post: sha llegit tota una paraula del fitxer */
	char lletra = in_file.get();
	 int countador = 0;
	if (!es_separador(lletra)) _words++;
	while (!in_file.eof() && !es_separador(lletra)) {
		//tractar, si cal, el caràcter llegit (lletra) 
		countador++;
		_chars++;
		in_file.get(lletra);
	}
	if (countador > h_max)expandir(countador);
	h_t[countador]++;
	if (!in_file.eof()) in_file.unget(); //pot no ser necessari 
}


void Histo:: llegir_fitxer(ifstream &in_file,string nom_fitxer) {
	//pre:cert 
	//post:0<=n<=CAPACITY vec[0..n-1] con n valors entrats 
	passar_separadors(in_file);
	while (!in_file.eof()) {
		passar_paraula(in_file);
		passar_separadors(in_file);
		
	}
}
void Histo::mostraResum()const {
	cout << "CARÀCTERS: " << _chars +_spaces << endl;
	cout << "LLETRES: " << _chars << endl;
	cout << "MOTS: " << _words << endl;
}
void Histo:: inicialitza_vector(int *v) {
	for (unsigned i = 0; i < h_max; i++) {
		v[i] = 0;
	}
}
int Histo::retorna_Max_position() const {
	int comptador = h_n - 1;
	bool trobat = false;
	while (comptador>0 && !trobat) {
		if (h_t[comptador] >= 1) trobat = true;
		comptador--;
	}
	return comptador;
}
unsigned Histo:: retornPosicioMinim()const {
	bool trobat = false;
	unsigned countador = 0;
	while (!trobat && countador< h_n) {
		if (h_t[countador] >= 1) trobat = true;
		countador++;
	}
	if (trobat)return countador;
	else return 0;
}
void Histo::mostra_vector()const {
	double paraules = static_cast<double>(_words);
	unsigned mini_posicio = retornPosicioMinim() - 1;
	unsigned max_position = static_cast<unsigned>(retorna_Max_position()) + 1;
	if (mini_posicio != 0) {
		for (unsigned i = mini_posicio; i <= max_position; i++) 
			cout << "[" << i << "]" << " = " << fixed << setprecision(3) << (h_t[i] / paraules) * 100 << endl;
	}
	else { 
		cout << "fitxer sence paraules " << endl;
	}
}