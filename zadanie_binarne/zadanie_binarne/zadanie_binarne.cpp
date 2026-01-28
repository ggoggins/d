#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct sprawdzanie {

	string linia;

	bool poprawnosc() const
	{
		if (linia.length() < 2) return false;

		int wynik = linia[0] - '0';

		for (int i = 1; i < linia.length(); i++)
		{
			int liczba = linia[i] - '0';

			if (i % 2 == 0) wynik = wynik & liczba;
			else wynik = wynik | liczba;
		}

		return wynik == 1;
	};

	string ilosc_liczb() const
	{
		int zera = 0;
		int jedynki = 0;

		for (char c : linia)
		{
			if (c == '0') zera++;
			if (c == '1') jedynki++;
		}
		return to_string(zera) + '/' + to_string(jedynki) + ';';
	};

	void zapis_wypis(string plik_wejscia, string plik_wyjscia)
	{

		ifstream wejscie(plik_wejscia);
		if (!wejscie.is_open()) {
			cerr << "Nie mozna otworzyc pliku";
			return;
		}
		ofstream wyjscie(plik_wyjscia);
		if (!wyjscie.is_open()) {
			cerr << "Nie mozna otworzyc pliku";
			return;
		}

		int liczba_linii = 0;
		while (getline(wejscie, linia))
		{
			liczba_linii++;
		}

		wejscie.clear();
		wejscie.seekg(0, ios::beg);

		wyjscie << "Ilosc linii w pliku: " << liczba_linii << ";\n";

		while (getline(wejscie, linia))
		{
			wyjscie << poprawnosc() << ", " << ilosc_liczb() << "\n";
		}

		wyjscie.close();
		wejscie.close();
		return;
	}
};

int main()
{
	sprawdzanie plik;

	plik.zapis_wypis("PLIK01.txt", "RAPORT01.txt");

	return 0;
}