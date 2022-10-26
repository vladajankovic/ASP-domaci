#include <iostream>
using namespace std;

struct Cvor {
	int broj;
	Cvor* sled;
};

struct ZaglavljeCvora {
	int broj_cvora;
	int xk, yk;
	int gore, dole, levo, desno;
	bool sgore, sdole, slevo, sdesno, ulaz, izlaz, visit;
	Cvor* pok;
};

void ispis(ZaglavljeCvora* graf, int m, int n, int ncvorova) {
	cout << " ";
	for (int i = 0; i < n; i++)
		if (graf[i].ulaz)
			cout << "o  ";
		else if(graf[i].izlaz)
			cout << "x  ";
		else
			cout << "__ ";
	for (int i = 0; i < ncvorova; i++) {
		if(i%n == 0)
			cout << endl;
		if (graf[i].levo == -1)
			if (graf[i].ulaz && i >= n && i < ncvorova - n)
				cout << "o";
			else if (graf[i].izlaz && i >= n && i<ncvorova-n)
				cout << "x";
			else
				cout << "|";
		if (graf[i].dole == -1)
			if (graf[i].ulaz && i >=n)
				cout << "o ";
			else if (graf[i].izlaz && i >=n)
				cout <<  "x ";
			else cout << "__";
		else if (!graf[i].sdole)
			cout << "__";
		else
			cout << "  ";
		if(graf[i].desno == -1)
			if (graf[i].ulaz && i >= n && i < ncvorova - n)
				cout << "o";
			else if (graf[i].izlaz && i >= n && i < ncvorova - n)
				cout << "x";
			else cout << "|";
		else if (!graf[i].sdesno || n == 1)
			cout << "|";
		else
			cout << " ";
	}
	cout << endl;
}

void kreirajGraf(ZaglavljeCvora*& graf, int& m, int& n, int& ncvorova, bool& postoji) {
	cout << "Faza kriranja Lavirinta." << endl <<
		"Unesite dimenzije Lavitinta." << endl;
	cout << "Broj vrsta: ";
	while (1) {												//postupak sprecavanja gresaka
		char c;
		if (!(cin >> m) || (cin.get(c) && !isspace(c))) {
			cout << "UNELI STE VRDNOST KOJA NIJE CEO BROJ!" << endl <<
				"Pokusajte ponovo sa unosom broja vrsta: ";
			cin.clear();
			cin.ignore(500, '\n');
		}
		else {
			if (m < 1) {
				cout << "NEISPRAVAN UNOS, MORA BITI POZITIVAN BROJ!" << endl <<
					"Pokusajte ponovo sa unosom broja vrsta: ";
			}
			else
				break;
		}
	}
	cout << "Broj kolona: ";
	while (1) {												//postupak sprecavanja gresaka
		char c;
		if (!(cin >> n) || (cin.get(c) && !isspace(c))) {
			cout << "UNELI STE VRDNOST KOJA NIJE CEO BROJ!" << endl <<
				"Pokusajte ponovo sa unosom broja kolona: ";
			cin.clear();
			cin.ignore(500, '\n');
		}
		else {
			if (n < 1) {
				cout << "NEISPRAVAN UNOS, MORA BITI POZITIVAN BROJ!" << endl <<
					"Pokusajte ponovo sa unosom broja kolona: ";
			}
			else
				break;
		}
	}
	if (m > 80) {
		m = 80;
		cout << "Maksimalan broj vrsta je 80." << endl;
	}
	if (n > 50) {
		n = 50;
		cout << "Maksimalan broj kolona je 50." << endl;
	}

	ncvorova = m * n;
	graf = new ZaglavljeCvora[ncvorova];
	for (int i = 0, xkoordinata = 0, ykoordinata = 0; i < ncvorova; i++) {
		if (i % n == 0 && i != 0) {
			xkoordinata++;
			ykoordinata = 0;
		}
		graf[i].broj_cvora = i + 1;
		graf[i].xk = xkoordinata;
		graf[i].yk = ykoordinata++;
		graf[i].levo = (graf[i].broj_cvora - 1) % n != 0 ? graf[i].broj_cvora - 1 : -1;
		graf[i].desno = (graf[i].broj_cvora + 1) % n != 1 ? graf[i].broj_cvora + 1 : -1;
		graf[i].gore = (graf[i].broj_cvora - n) > 0 ? graf[i].broj_cvora - n : -1;
		graf[i].dole = (graf[i].broj_cvora + n) <= m * n ? graf[i].broj_cvora + n : -1;
		graf[i].sdesno = graf[i].sdole = graf[i].sgore = graf[i].slevo = graf[i].ulaz = graf[i].izlaz = graf[i].visit = false;
		graf[i].pok = nullptr;
	}
	ispis(graf, m, n, ncvorova);
	int xu, yu, xi, yi;
	cout << "Odredite ulaz i izlaz Lavirinta. Ulaz i izlaz Lavirinta se nalazi na njegovim stranicama." << endl <<
		"Unesite koordinate ulaza i izlaza. Pritom, barem jedna od koordinata ulaza i izlaza mora imati vrdnost 0 ili " << n - 1<<" za kolone ili "<<m-1<<" za vrste." << endl;
	{
		cout << "Koordinate ulaza X i Y: ";
		while (1) {												//postupak sprecavanja gresaka
			char c;
			if (!(cin >> xu) || (cin.get(c) && !isspace(c))) {
				cout << "UNELI STE VRDNOST KOJA NIJE CEO BROJ!" << endl <<
					"Pokusajte ponovo sa unosom X-koordinate ulaza: ";
				cin.clear();
				cin.ignore(500, '\n');
			}
			if (!(cin >> yu) || (cin.get(c) && !isspace(c))) {
				cout << "UNELI STE VRDNOST KOJA NIJE CEO BROJ!" << endl <<
					"Pokusajte ponovo sa unosom X-koordinate ulaza: ";
				cin.clear();
				cin.ignore(500, '\n');
			}
			else {
				if (xu != 0 && xu != m - 1 && yu != 0 && yu != n - 1) {
					cout << "NEISPRAVAN UNOS, BAREM JEDNA KOORDINATA MORA BITI ILI 0 ILI BROJ " << n - 1 << " ZA KOLONE ILI "<<m-1<<" ZA VRSTE!" << endl <<
						"Pokusajte ponovo sa unosom X i Y koordinata ulaza: ";
				}
				else if (xu > m - 1 || yu > n - 1)
					cout << "NEISPRAVAN UNOS, KOORDINATA VAN OPSEGA!" << endl <<
					"Pokusajte ponovo sa unosom X i Y koordinata ulaza: ";
				else
					break;
			}
		}
	}
	{
		cout << "Koordinate izlaza X i Y: ";
		while (1) {												//postupak sprecavanja gresaka
			char c;
			if (!(cin >> xi) || (cin.get(c) && !isspace(c))) {
				cout << "UNELI STE VRDNOST KOJA NIJE CEO BROJ!" << endl <<
					"Pokusajte ponovo sa unosom X-koordinate izlaza: ";
				cin.clear();
				cin.ignore(500, '\n');
			}
			if (!(cin >> yi) || (cin.get(c) && !isspace(c))) {
				cout << "UNELI STE VRDNOST KOJA NIJE CEO BROJ!" << endl <<
					"Pokusajte ponovo sa unosom X-koordinate izlaza: ";
				cin.clear();
				cin.ignore(500, '\n');
			}
			else {
				if (xi != 0 && xi != m - 1 && yi != 0 && yi != n - 1) {
					cout << "NEISPRAVAN UNOS, BAREM JEDNA KOORDINATA MORA BITI ILI 0 ILI BROJ " << n - 1 << " ZA KOLONE ILI " << m - 1 << " ZA VRSTE!" << endl <<
						"Pokusajte ponovo sa unosom X i Y koordinata izlaza: ";
				}
				else if (xi == xu && yi == yu && m*n !=1) {
					cout << "IZLAZ NE MOZE IMATI ISTE KOORDINATE KAO I ULAZ!" << endl << "Pokusajte ponovo sa unosom X i Y koordinata izlaza: ";
				}
				else if (xi > m - 1 || yi > n - 1)
					cout << "NEISPRAVAN UNOS, KOORDINATA VAN OPSEGA!" << endl <<
					"Pokusajte ponovo sa unosom X i Y koordinata ulaza: ";
				else
					break;
			}
		}
	}
	int k1 = n * xu + yu;
	int k2 = n * xi + yi;
	graf[k1].ulaz = true;
	graf[k2].izlaz = true;
	cout << "Kreiran je Lavirint dimenzija " << m << "x" << n << endl << endl;
	postoji = true;
}

void izborOperacija(int& op) {
	cout << "Pred vama su date sledece operacije sa grafom:" << endl <<
		"_____________________________________________" << endl <<
		"1. Kreiranje novog Lavirinta." << endl <<
		"2. Brisanje zida izmedju susednih polja" << endl <<
		"3. Dodavanje zida izmedju susednih polja" << endl <<
		"4. Ispis izgleda Lavirinta" << endl <<
		"5. Resavanje Lavirinta" << endl <<
		"6. Brisanje Lavirinta" << endl <<
		"7. Izlaz iz programa" << endl <<
		"_____________________________________________" << endl <<
		"Izaberite jednu od datih operacija unosom njenog broja. Izvrsavanje operacije broj: ";
	while (1) {												//postupak sprecavanja gresaka
		char c;
		if (!(cin >> op) || (cin.get(c) && !isspace(c))) {
			cout << "UNELI STE VRDNOST KOJA NIJE CEO BROJ!" << endl <<
				"Pokusajte ponovo sa unosom: ";
			cin.clear();
			cin.ignore(500, '\n');
		}
		else {
			if (op < 1 || op >7) {
				cout << "UNELI STE NEISPRAVAN BROJ OPERACIJE!" << endl <<
					"Pokusajte ponovo sa unosom: ";
			}
			else
				break;
		}
	}
	cout << endl;
}

void dodajGranu(ZaglavljeCvora*& graf, int& n) {
	int c1, c2, k1, k2;
	bool postoji1 = false, postoji2 = false, isti = false, susedi = false;
	cout << "Unesite brojeve susednih polja koje zelite da povezete." << endl;
	cout << "Prvo polje: ";
	while (1) {												//postupak sprecavanja gresaka
		char c;
		if (!(cin >> c1) || (cin.get(c) && !isspace(c))) {
			cout << "UNELI STE VRDNOST KOJA NIJE CEO BROJ!" << endl <<
				"Pokusajte ponovo sa unosom: ";
			cin.clear();
			cin.ignore(500, '\n');
		}
		else {
			if (c1 < 1) {
				cout << "UNELI STE NEGATIVAN BROJ ILI NULU!" << endl <<
					"Pokusajte ponovo sa unosom: ";
			}
			else
				break;
		}
	}
	cout << "Drugi cvor: ";
	while (1) {												//postupak sprecavanja gresaka
		char c;
		if (!(cin >> c2) || (cin.get(c) && !isspace(c))) {
			cout << "UNELI STE VRDNOST KOJA NIJE CEO BROJ!" << endl <<
				"Pokusajte ponovo sa unosom: ";
			cin.clear();
			cin.ignore(500, '\n');
		}
		else {
			if (c2 < 1) {
				cout << "UNELI STE NEGATIVAN BROJ ILI NULU!" << endl <<
					"Pokusajte ponovo sa unosom: ";
			}
			else
				break;
		}
	}
	for (int i = 0; i < n; i++) {	//provera da li postoji cvor1
		if (c1 == graf[i].broj_cvora) {
			postoji1 = true;
			k1 = i;
		}
		if (c2 == graf[i].broj_cvora) {
			postoji2 = true;
			k2 = i;
		}
	}
	if (c1 == c2)									//provera da li se bira isto polje
		isti = true;
	if (postoji1 && postoji2 && !isti) {			//ako je validan unos
		int cmin = c1 < c2 ? c1 : c2;
		int cmax = c1 > c2 ? c1 : c2;
		bool spojeni = false;
		if (graf[k1].desno == c2 || graf[k1].dole == c2 || graf[k1].gore == c2 || graf[k1].levo == c2)		//provera da li su susedni
			susedi = true;
		for (int i = 0; i < n; i++) {			//provera da li su vec spojeni
			if (graf[i].broj_cvora == cmin) {
				Cvor* tek = graf[i].pok;
				while (tek) {
					if (tek->broj == cmax) {
						spojeni = true;
						break;
					}
					tek = tek->sled;
				}
				break;
			}
		}
		if (spojeni == false && susedi) {					//ako nisu spojeni i susedni su
			for (int i = 0; i < n; i++) {
				if (graf[i].broj_cvora == cmin) { //nadje se prvo zaglavlje cvora sa manjim brojem
					Cvor* novi = new Cvor;
					novi->broj = cmax;
					novi->sled = nullptr;
					Cvor* tek = graf[i].pok;
					if (tek == nullptr) {		//da li je zaglavlje prazno
						graf[i].pok = novi;
					}
					else {						//umetanje na kraj zaglavlja
						while (tek->sled != nullptr)
							tek = tek->sled;
						tek->sled = novi;
					}
				}
				if (graf[i].broj_cvora == cmax) { //nadje se zatim zaglavlje cvora za vecim brojem
					Cvor* novi = new Cvor;
					novi->broj = cmin;
					novi->sled = nullptr;
					Cvor* tek = graf[i].pok;
					if (tek == nullptr) {			//da li je zaglavlje prazno
						graf[i].pok = novi;
					}
					else {							//umetanje na kraj zaglavlja
						while (tek->sled != nullptr)
							tek = tek->sled;
						tek->sled = novi;
					}
					break;
				}
			}
			if (graf[k1].desno == c2) {
				graf[k1].sdesno = true;
				graf[k2].slevo = true;
			}
			if (graf[k1].levo == c2) {
				graf[k1].slevo = true;
				graf[k2].sdesno = true;
			}
			if (graf[k1].gore == c2) {
				graf[k1].sgore = true;
				graf[k2].sdole = true;
			}
			if (graf[k1].dole == c2) {
				graf[k1].sdole = true;
				graf[k2].sgore = true;
			}
			cout << "Polja " << c1 << " i " << c2 << " su sada spojena prolazom." << endl;
		}
		else {
			if (!susedi)
				cout << "POLJA NISU SUSEDNA!" << endl << endl;
			else
				cout << "DATA POLJA SU VEC POVEZANA." << endl << endl;
		}
	}
	else {								//neispravan unos
		if (postoji1 == false)
			cout << "GRESKA PRI UNOSU BROJA PRVOG POLJA!" << endl;
		if (postoji2 == false)
			cout << "GRESKA PRI UNOSU BROJA DRUGOG POLJA!" << endl;
		if (isti)
			cout << "POLJA MORAJU BITI RAZLICITA!" << endl;
		cout << endl;
	}
}

void brisiGranu(ZaglavljeCvora*& graf, int& n) {
	int c1, c2, k1, k2;
	bool postoji1 = false, postoji2 = false, isti = false;
	cout << "Unesite brojeve polja kojima se postavlja zid." << endl;
	cout << "Prvo polje: ";
	while (1) {												//postupak sprecavanja gresaka
		char c;
		if (!(cin >> c1) || (cin.get(c) && !isspace(c))) {
			cout << "UNELI STE VRDNOST KOJA NIJE CEO BROJ!" << endl <<
				"Pokusajte ponovo sa unosom: ";
			cin.clear();
			cin.ignore(500, '\n');
		}
		else {
			if (c1 < 1) {
				cout << "UNELI STE NEGATIVAN BROJ ILI NULU!" << endl <<
					"Pokusajte ponovo sa unosom: ";
			}
			else
				break;
		}
	}
	cout << "Drugo polje: ";
	while (1) {												//postupak sprecavanja gresaka
		char c;
		if (!(cin >> c2) || (cin.get(c) && !isspace(c))) {
			cout << "UNELI STE VRDNOST KOJA NIJE CEO BROJ!" << endl <<
				"Pokusajte ponovo sa unosom: ";
			cin.clear();
			cin.ignore(500, '\n');
		}
		else {
			if (c2 < 1) {
				cout << "UNELI STE NEGATIVAN BROJ ILI NULU!" << endl <<
					"Pokusajte ponovo sa unosom: ";
			}
			else
				break;
		}
	}
	for (int i = 0; i < n; i++) {	//provera da li postoji cvor1
		if (c1 == graf[i].broj_cvora) {
			postoji1 = true;
			k1 = i;
		}
	}
	for (int i = 0; i < n; i++) {	//provera da li postoji cvor2
		if (c2 == graf[i].broj_cvora) {
			postoji2 = true;
			k2 = i;
		}
	}
	if (c1 == c2)									//provera da li se stvara petlja
		isti = true;
	if (postoji1&& postoji2 && !isti) {			//ako je validan unos
		int cmin = c1 < c2 ? c1 : c2;
		int cmax = c1 > c2 ? c1 : c2;
		bool spojeni = false;
		for (int i = 0; i < n; i++) {			//provera da li su vec spojeni
			if (graf[i].broj_cvora == cmin) {
				Cvor* tek = graf[i].pok;
				while (tek) {
					if (tek->broj == cmax) {
						spojeni = true;
						break;
					}
					tek = tek->sled;
				}
				break;
			}
		}
		if (spojeni == true) {										//ako jesu spojeni sklanja im se grana
			for (int i = 0; i < n; i++) {
				if (graf[i].broj_cvora == cmin) {
					Cvor* tek = graf[i].pok;
					Cvor* pomocni = tek;
					while (tek) {
						if (tek->broj == cmax) {				//cvor je nadjen
							if (tek == graf[i].pok) {			//cvor je kod zaglavlja
								graf[i].pok = tek->sled;
								delete tek;
								break;
							}
							while (pomocni->sled != tek)
								pomocni = pomocni->sled;
							pomocni->sled = tek->sled;
							delete tek;
							break;
						}
						tek = tek->sled;
					}
				}
				if (graf[i].broj_cvora == cmax) {
					Cvor* tek = graf[i].pok;
					Cvor* pomocni = tek;
					while (tek) {
						if (tek->broj == cmin) {				//cvor je nadjen
							if (tek == graf[i].pok) {			//cvor je kod zaglavlja
								graf[i].pok = tek->sled;
								delete tek;
								break;
							}
							while (pomocni->sled != tek)
								pomocni = pomocni->sled;
							pomocni->sled = tek->sled;
							delete tek;
							break;
						}
						tek = tek->sled;
					}

				}
			}
			if (graf[k1].desno == c2) {
				graf[k1].sdesno = false;
				graf[k2].slevo = false;
			}
			if (graf[k1].levo == c2) {
				graf[k1].slevo = false;
				graf[k2].sdesno = false;
			}
			if (graf[k1].gore == c2) {
				graf[k1].sgore = false;
				graf[k2].sdole = false;
			}
			if (graf[k1].dole == c2) {
				graf[k1].sdole = false;
				graf[k2].sgore = false;
			}
			cout << "Postavljen je zid izmedju polja " << c1 << " i " << c2 << endl;
		}
		else {
			cout << "DATA POLJA NISU SPOJENA." << endl << endl;
		}
	}
	else {								//neispravan unos
		if (postoji1 == false)
			cout << "GRESKA PRI UNOSU BROJA PRVOG POLJA!" << endl;
		if (postoji2 == false)
			cout << "GRESKA PRI UNOSU BROJA DRUGOG POLJA!" << endl;
		if (isti)
			cout << "POLJA MORAJU BITI RAZLICITA!" << endl;
		cout << endl;
	}
}

void resiLavirint(ZaglavljeCvora*& graf, int& m, int& n, int& ncvorova) {
	int** matrica;
	matrica = new int* [ncvorova];
	for (int i = 0; i < ncvorova; i++) {			//Inicijalizacija matrice dostiznosti
		matrica[i] = new int[ncvorova];
		for (int j = 0; j < ncvorova; j++) {
			matrica[i][j] = 0;
			if (i == j)
				continue;
			Cvor* tek = graf[i].pok;
			while (tek) {
				if (tek->broj == j + 1) {
					matrica[i][j] = 1;
					break;
				}
				tek = tek->sled;
			}
		}
	}
	cout << "Izgled inicijalne matrice dostiznosti:" << endl;
	for (int i = 0; i < ncvorova; i++) {
		for (int j = 0; j < ncvorova; j++) {
			cout << matrica[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int k = 0; k < ncvorova; k++) {				//Floyd-Warshall-ov algoritam sa optimizacijom
		for (int i = 0; i < ncvorova; i++) {
			if (matrica[i][k] == 1) {
				for (int j = 0; j < ncvorova; j++)
					matrica[i][j] = matrica[i][j] || matrica[k][j];
			}
		}
	}
	cout << "Izgled gorove matrice dostiznosti:" << endl;
	for (int i = 0; i < ncvorova; i++) {
		for (int j = 0; j < ncvorova; j++) {
			cout << matrica[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	int ulaz = 0, izlaz = 0, stek = 0;
	for (int i = 0; i < ncvorova; i++) {			//lociranje polja ulaza i izlaza
		if (graf[i].ulaz == true) {
			ulaz = graf[i].broj_cvora - 1;
		}
		if (graf[i].izlaz == true) {
			izlaz = graf[i].broj_cvora - 1;
		}
	}
	if (matrica[ulaz][izlaz] == 1) {				//pronalazenje puta od ulaza do izlaza
		int* niz = new int[ncvorova];
		for (int i = 0; i < ncvorova; i++)
			niz[i] = 0;
		niz[0] = graf[ulaz].broj_cvora;
		stek++;
		graf[ulaz].visit = true;
		int* tek = niz;
		Cvor* tekcv = graf[ulaz].pok;
		while (1) {
			while (tekcv) {
				while (graf[tekcv->broj - 1].visit == false) {
					tek = tek + 1;
					*tek = tekcv->broj;
					stek++;
					graf[tekcv->broj - 1].visit = true;
					tekcv = graf[tekcv->broj - 1].pok;
				}
				tekcv = tekcv->sled;
			}
			if (*tek != graf[izlaz].broj_cvora) {
				*tek = 0;
				tek = tek - 1;
				stek--;
				tekcv = graf[*tek - 1].pok;
			}
			else {
				tek = niz;
				break;
			}
		}
		cout << "Koraci potrebni da se dodje od ulaza do izlaza Lavirinta:" << endl;
		while (stek--) {
			cout << "(" << graf[*tek - 1].xk << "," << graf[*tek - 1].yk << ")";
			if (*tek != graf[izlaz].broj_cvora)
				cout << " -> ";
			tek = tek + 1;
		}
		cout << endl << endl;
		for (int i = 0; i < ncvorova; i++) {					//brisanje matrice dostiznosti i niza
			delete[] matrica[i];
			graf[i].visit = false;
		}
		delete[] matrica;
		delete[] niz;
	}
	else
		cout << "Ne postoji put od ulaza do izlaza Lavirinta!" << endl;
}

void brisi(ZaglavljeCvora*& graf, int& n, bool& postoji) {
	for (int i = 0; i < n; i++) {
		while (graf[i].pok != nullptr) {		//brisanje liste suseda jedan po jedan
			Cvor* tek = graf[i].pok;
			graf[i].pok = tek->sled;
			delete tek;
		}
	}
	delete[] graf;
	n = 0;
	postoji = false;
}

int main() {
	ZaglavljeCvora* graf = nullptr;
	int broj_cvorova = 0;
	int m = 0, n = 0;
	bool rad = true, postoji = false;
	int op;
	while (rad) {
		izborOperacija(op);
		switch (op) {
			case 1: {
				if (postoji == true) {
					brisi(graf, broj_cvorova, postoji);
					cout << "Brise se stari Lavirint." << endl;
					cout << "Lavirint je izbrisan iz memorije!" << endl;
				}
				kreirajGraf(graf, m, n, broj_cvorova, postoji);
				ispis(graf, m, n, broj_cvorova);
				break;
			}
			case 2: {
				if (postoji == false) {
					cout << "NEMOGUCE IZVRSITI OPERACIJU! Lavirint ne postoji. Napravite novi Lavirint." << endl << endl;
					break;
				}
				dodajGranu(graf, broj_cvorova);
				break;
			}
			case 3: {
				if (postoji == false) {
					cout << "NEMOGUCE IZVRSITI OPERACIJU! Lavirint ne postoji. Napravite novi Lavirint." << endl << endl;
					break;
				}
				brisiGranu(graf, broj_cvorova);
				break;

			}
			case 4: {
				if (postoji == false) {
					cout << "NEMOGUCE IZVRSITI OPERACIJU! Lavirint ne postoji. Napravite novi Lavirint." << endl << endl;
					break;
				}
				ispis(graf, m, n, broj_cvorova);
				break;
			}
			case 5: {
				if (postoji == false) {
					cout << "NEMOGUCE IZVRSITI OPERACIJU! Lavirint ne postoji. Napravite novi Lavirint." << endl << endl;
					break;
				}
				if (m * n == 1) {
					cout << "Lavirint je dimenzije 1x1 pa je jedino moguce da je ulaz ujedno i izlaz." << endl << endl;
					break;
				}
				resiLavirint(graf, m, n, broj_cvorova);
				break;
			}
			case 6: {
				if (postoji == false) {
					cout << "NEMOGUCE IZVRSITI OPERACIJU! Lavirint ne postoji. Napravite novi Lavirint." << endl << endl;
					break;
				}
				brisi(graf, broj_cvorova, postoji);
				cout << "Lavirint je izbrisan iz memorije!" << endl << endl;
				break;
			}
			case 7: {
				if (postoji == true) {
					brisi(graf, broj_cvorova, postoji);
				}
				cout << "Kraj rada." << endl;
				rad = false;
			}
		}
	}
	return 0;
}
