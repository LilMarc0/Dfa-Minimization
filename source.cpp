// Tema1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>
using namespace std;

class automat {
private:
	string alfabet;
	map<pair<int, char>, int> tranz;
	map<pair<int, char>, int> tranz2;
	vector<int> st_fn;
	vector<int> st;
	int s0,s_curr;
	bool lambda;
public:

	// Constructor / Destructor
	automat() {
		alfabet = "";
		s0 = 0;
		s_curr = 0;
	}

	automat(const automat& x){
		s0 = x.s0;
		lambda = x.lambda;
		this->set_stfn(x.st_fn);
		st = x.st;
		tranz = x.tranz;
		this->set_alfa(x.alfabet);
		s_curr = 0;
	}

	automat(string alf, int s, int nr, vector<int> sf){
		alfabet = alf;	s0 = s;
		s_curr = s;	st.resize(nr);
		for (size_t i = 0; i < st.size(); i++)
			st[i] = i;
		st_fn.resize(sf.size());
		for (size_t i = 0; i < sf.size(); i++)
			st_fn[i] = sf[i];
	}

	~automat(){
		alfabet = "";
		tranz.clear();
		st_fn.clear();
		st.clear();
	}
	
	// Set / Get
	void set_tranz(int i, char j, int r){tranz[pair<int, char>(i, j)] = r;}

	void set_tranz2(int i, char j, int r) { tranz2[pair<int, char>(i, j)] = r; }

	bool isTranz(int i, char j){ return tranz[pair<int, char>(i, j)] ? true : false;}

	bool isTranzSpec(int i, char j, int r){ return tranz[pair<int, char>(i, j)] == r ? true :  false; }

	int getTranz(int i, char j) {return tranz[pair<int, char>(i, j)];}

	void set_alfa(string s){ this->alfabet = s;}

	vector<int> getstari(){ return st;}

	void print_tranz(){
		string alf = alfabet;
		cout << "\ntranz: ";
		for (size_t i = 0; i < get_st_size(); i++)
			for (size_t k = 0; k < get_alf().size(); k++)
				if(isTranz(i, alf[k]) )
					cout << endl << i << ", " << alf[k] << " -> " << getTranz(i, alf[k]);
	}

	string get_alf() { return alfabet; }

	void set_s0(int s) {s0 = s;}

	int get_st_at(int i) { return st[i]; }

	void set_stfn(vector<int> sf){
		st_fn = sf;
		for (size_t i = 0; i < st_fn.size(); i++)
			if (st_fn[i] == s0)
				lambda = true;
	}

	bool isFinal(int stare){
		for (size_t i = 0; i < st_fn.size(); i++)
			if (st_fn.at(i) == stare)
				return true;
		return false;
	}

	void set_st(size_t nr){
		st.resize(nr);
		for (size_t i = 0; i < nr; i++)
			st[i] = i;
	}

	void erase_tranz() { tranz.erase(tranz.begin(), tranz.end());
	tranz = tranz2;
	}

	vector<int> get_st_fn()  { return st_fn; }

	void set_lmb(bool x){ lambda = x; }

	int get_st_size() { return st.size(); }
	
	// Evaluare
	void test_cuvant(string x) {
		cout << x.size();
		char op;
		cout << "Cuvinte sau litere?(c/v) "; cin >> op;
		if (op == 'c')
		{
			if (x.size() == 1)
			{
				if (lambda && x == "!") {
					cout << "\n Cuvant acceptat ( lambda )"; return;
				}
				else {
					cout << "\n Cuvant respins";
					return;
				}
			}

			for (size_t i = 0; i < st_fn.size(); i++)
			{

				if (s_curr == st_fn[i])
				{
					cout << "\nCuvant acceptat";
					return;
				}
			}
			cout << "\nCuvant respins";
		}
		if (x.size() == 1)
		{
			if (lambda && x == "!") {
				cout << "\n Cuvant acceptat ( lambda )"; return;
			}
			else {
				cout << "\n Cuvant respins";
				return;
			}
		}
		cout << "\nPentru cuvantul: "; cout << x;
		for (size_t i = 0; i < x.size(); i++)
		{
			if (alfabet.find(x[i]) == string::npos)
			{
				cout << "\nCuvand respins";
				return;
			}
			
		}
		for (size_t i = 0; i < x.size(); i++)
		{
			cout << "\nCurent: " << s_curr << " primesc:" << x[i] << " merg in:" << tranz[pair<int, char>(s_curr, x[i])];
			s_curr = tranz[pair<int, char>(s_curr, x[i])];
		}
		for (size_t i = 0; i < st_fn.size(); i++)
		{
			
			if (s_curr == st_fn[i])
			{
				cout << "\nCuvant acceptat";
				return;
			}
		}
		cout << "\nCuvant respins";
	}

	friend ostream& operator<<(ostream&, const automat&);
};

ostream& operator<<(ostream& out, automat& x)
{
	string alf = x.get_alf();
	vector<int> stfn = x.get_st_fn();

	out << "\n alfabet: " << alf << " stare initiala: " << x.get_st_at(0) << " numar stari: " << x.get_st_size() << " stari finale: ";
	for (size_t i = 0; i < x.get_st_fn().size(); i++)
	{
		out << stfn[i] << " ";
	}
	cout << endl << "tranzitii: ";
	for (size_t i = 0; i < x.get_st_size(); i++)
		for (size_t k = 0; k < x.get_alf().size(); k++)
			if(x.isTranz(i, alf[k])) cout << endl << i << ", " << alf[k] << " -> " << x.getTranz(i, alf[k]);
	return out;
}

int getIndex(int nr)
{
	int i;
	if (nr == 1) return 0;
	cout << "\n\t ---> Dati indexul: ";
	do {
		cin >> i;
		if (i<0 || i>nr) cout << "\n !!! Index invalid !!!\n";
	} while (i<0 || i>nr);
	return i;
}

void convert_to_minimal(automat x)
{
	automat minimal;
	minimal.print_tranz(); cout << 1;
	x.set_alfa("01");
	x.set_st(6);
	x.set_tranz(0, '0', 1);
	x.set_tranz(1, '0', 0);
	x.set_tranz(0, '1', 2);
	x.set_tranz(1, '1', 3);
	x.set_tranz(2, '0', 4);
	x.set_tranz(3, '1', 5);
	x.set_tranz(3, '0', 4);
	x.set_tranz(2, '1', 5);
	x.set_tranz(4, '1', 5);
	x.set_tranz(4, '0', 4);
	x.set_tranz(5, '0', 5);
	x.set_tranz(5, '1', 5);
	x.set_stfn({ 2,3,4 });
	minimal.print_tranz(); cout << 2;
	vector<vector<int>> v;
	vector<int> newstari = x.getstari();
	vector<int> l;
	string alf = x.get_alf();
	int scoase = 0;
	bool** S;
	S = new bool*[x.get_st_size()];
	for (int i = 1; i < x.get_st_size();i++)
	{
		S[i] = new bool[i];
		for (int j = 0; j <i; j++)
			S[i][j] = false;
	}
	
	for (int i = 1; i < x.get_st_size(); i++)
		for (int j = 0; j <i; j++) {
			if (x.isFinal(i) && x.isFinal(j) == false)
				S[i][j] = true;
			if (x.isFinal(i) == false && x.isFinal(j))
				S[i][j] = true;
		}

	bool still = false;
	do {
		still = false;
		for (int i = 1; i < x.get_st_size(); i++)
			for (int j = 0; j < i; j++)
			{
				if (S[i][j]) {
					continue;
				}
				if(S[i][j] == false)
				for (size_t k = 0; k < alf.size(); k++)
				{
					int s1, s2;
					s1 = x.getTranz(i, alf[k]);
					s2 = x.getTranz(j, alf[k]);
					if(s2 <= s1)
						if (S[s1][s2] == 1)
						{
							S[i][j] = true;
							still = true;
						}
				}

			}
		cout << endl;
	} while (still);

	for (int i = 1; i < x.get_st_size(); i++)
	{
		for (int j = 0; j < i; j++) {
			if (S[i][j] == 1)
				continue;
			else {
				bool gasiti = false, gasitj = false;
				size_t aux;
				vector<int>::iterator iti,itj;
				l.clear();
				l.push_back(i); ; l.push_back(j);
				for (size_t k = 0; k < v.size(); k++) {
					iti = find(v[k].begin(), v[k].end(), i);
					if(iti != v[k].end())
					{
						gasiti = true; 
						aux = k;
					}
					itj = find(v[k].begin(), v[k].end(), j);
					if (itj != v[k].end())
					{
						gasitj = true;
						aux = k;
					}
				}
				if (!gasiti && !gasitj)
				{
					v.push_back(l);
					newstari.erase(newstari.begin() + abs(j - scoase)); scoase++;
					newstari.erase(newstari.begin() + abs(i - scoase)); scoase++;
					continue;
				}
				if (gasiti)
				{
					if (gasitj == false)
					{
						v[aux].push_back(j);
						newstari.erase(newstari.begin() + abs(j - scoase)); scoase++;
					}
				}
				if (gasitj)
				{
					if (gasiti == false){
						v[aux].push_back(i);
					newstari.erase(newstari.begin() + abs(i - scoase)); scoase++;
				}
				}

			}
		}
	}
	minimal.print_tranz(); cout << 3;
	vector<int> newstfn;
	for (size_t i = 0; i < v.size(); i++)
	{
		cout << endl;
		for (size_t j = 0; j < v[i].size(); j++){
			//cout << v[i][j] << " ";
		}
		if (x.isFinal(v[i][0])){
			newstfn.push_back(i);
		}
		newstari.push_back(i);
		//cout << " devin starea " << i;
	}
	//cout << endl << " au ramas: ";
	minimal.print_tranz(); cout << 4;
	for (size_t i = 0; i < newstari.size() - v.size(); i++)
	{
		vector<int> de_adaug;
		de_adaug.push_back(newstari[i]);
		v.push_back(de_adaug);
		//cout << newstari[i] << " ";
	}
	for (size_t i = 0; i < v.size(); i++)
	{
		cout << endl;
		//for (size_t j = 0; j < v[i].size(); j++)
			//cout << v[i][j] << " ";
	}
	//normalizare
	for (size_t i = 0; i < newstari.size(); i++)
		newstari[i] = i;
	// creare obiect
	minimal.set_st(newstari.size());
	minimal.set_stfn(newstfn);
	minimal.print_tranz(); cout << 5;
	minimal.set_alfa(alf);
	minimal.print_tranz(); cout << 6;
	cout << endl;
	minimal.print_tranz(); cout << 7;
	for (size_t i = 0; i < v.size(); i++)
		for (size_t j = 0; j < v.size(); j++)
			for (size_t k = 0; k < x.get_alf().size(); k++)
			{
				if (x.isTranzSpec(v[i][0], alf[k], v[j][0]))
				{
					cout << "in minimal: " << i << ", " << alf[k] << " --> " << j<<"s"<<endl;
					minimal.set_tranz(i, alf[k], j);
				}
			}
	cout << endl <<minimal;
}

int main()
{
	vector<int> f;
	vector<automat> autos;
	int nra=0;
	system("pause");
	// Meniu
	do {
		int op;
		cout << "\n 1) Lista automate";
		cout << "\n 2) Creeaza un automat";
		cout << "\n 3) Seteaza alfabetul";
		cout << "\n 4) Seteaza starea initiala";
		cout << "\n 5) Seteaza numarul de stari";
		cout << "\n 6) Seteaza starile finale";
		cout << "\n 7) Adauga tranzitii";
		cout << "\n 8) Evalueaza cuvant";
		cout << "\n 9) Sterge automat";
		cout << "\n 10) Conversie minimal";
		cout << "\n 11) Exit";
		cout << "\n\t ---> Alegeti optiunea: "; cin >> op;
		switch (op) {
		case 1: {
			for (int i = 0; i < nra; i++)
				cout << "\n Automatul "<<i<<": "<<autos[i];
			break;
		}
		case 2: {
			automat de_adaugat;
			autos.push_back(de_adaugat);
			nra++;
			break;
		}
		case 3:
		{
			string alf;
			bool lmb;
			int index = getIndex(nra);
			cout << "\n Lambda? (1/0)"; cin >> lmb;
			autos.at(index).set_lmb(lmb);
			cout << "\n Introduceti alfabetul, fara spatii: "; 
			do {
				cin >> alf;
				if(alf.find(" ") != string ::npos) cout << "\n AM SPUS FARA SPATII!";
			} while (alf.find(" ") != string::npos);
			autos.at(index).set_alfa(alf);
			break;
		}
		case 4: {
			int s,index = getIndex(nra);
			cout << "\n Introduceti starea initiala: ";
			do {
				cin >> s;
				if (s<0 || s>autos.at(index).get_st_size()) cout<<"\n Nu se afla printre stari \n";
			} while (s<0 || s>autos.at(index).get_st_size());
			autos.at(index).set_s0(s);
			break;
		}
		case 5: {
			int nr, index = getIndex(nra);
			cout << "\n Introduceti nr de stari: "; cin >> nr;
			autos.at(index).set_st(nr);
			break;
		}
		case 6: {
			size_t nr;
			int x,index = getIndex(nra);
			vector<int> stf;
			cout << "\n Cate stari finale va avea automatul? "; cin >> nr;
			for (size_t i = 0; i < nr; i++)
			{
				cout << "\n stare_finala " << i + 1 << ": "; cin >> x;
				stf.push_back(x);
			}
			autos.at(index).set_stfn(stf);
			break;
		}
		case 8: {
			string s;
			int index = getIndex(nra);
			cout << "\n Cuvantul care trebuie evaluat: "; cin >> s;
			autos.at(index).test_cuvant(s);
			break;
		}
		case 9: {
			int index = getIndex(nra);
			autos.erase(autos.begin() + index);
			break;
		}
		case 7: {
			int nr,index=getIndex(nra),from, to;
			char cv;
			cout << "\n Cate tranzitii adaugati? "; cin >> nr;
			for (int i = 0; i < nr; i++)
			{
				cout << "\n\t Starea de inceput: "; cin >> from;

				cout << "\n\t Input: "; cin >> cv;

				cout << "\n\t Starea finala: "; cin >> to;

				autos.at(index).set_tranz(from, cv, to);
			}
			break;
		}
		case 10: {
			int nr, index = getIndex(nra);
			cout << "\n Automatul minimal corespunzator este: ";
			convert_to_minimal(autos.at(index));
			system("pause");
			break;
		}
		case 11: {
			system("exit");
		}
		}
	} while (1);
	system("pause");
    return 0;
}

