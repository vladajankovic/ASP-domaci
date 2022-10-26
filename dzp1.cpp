#include <iostream>
using namespace std;

static int id = 0;

struct Cvor {
	int broj;
	Cvor* sled;
};

struct ZaglavljeCvora {
	int broj_cvora;
	Cvor* pok;
};

void ispis(ZaglavljeCvora* graf, int n) {
	cout << "GRAF:" << endl;
	for (int i = 0; i < n; i++) {
		cout << "Cvor(" << graf[i].broj_cvora << ") -> ";
		if (graf[i].pok == nullptr) {			//ako cvor nije povezan 
			cout << "nullptr" << endl;
		}
		else {									//ako je cvor povezan, ispisuju se njegovi susedi
			Cvor* tek = graf[i].pok;
			while (tek) {
				cout << tek->broj << " -> ";
				tek = tek->sled;
			}
			cout << "nullptr" << endl;
		}
	}
	cout << endl;
}

void unosCvorova(ZaglavljeCvora*& graf, int& n, bool& postoji) {
	cout << "Stvara se novi graf." << endl << "Unesite koliko cvorova zelite da graf ima: ";
	while (1) {												//postupak sprecavanja gresaka
		char c;
		if (!(cin >> n) || (cin.get(c) && !isspace(c))) {
			cout << "UNELI STE VRDNOST KOJA NIJE CEO BROJ!" << endl <<
				"Pokusajte ponovo sa unosom broja cvorova: ";
			cin.clear();
			cin.ignore(500, '\n');
		}
		else {
			if (n<0) {
				cout << "NEISPRAVAN UNOS CVOROVA!" << endl <<
					"Pokusajte ponovo sa unosom broja cvorova: ";
			}
			else
				break;
		}
	}
	id = 0;							//kada se pri brisanju starog grafa kreira novi graf, pocetna vrednost cvorova se vraca na 1
	if (n == 0)
		cout << "Kreiran je prazan graf." << endl << endl;
	else if (n > 5000) {
		n = 5000;
		cout << "Uneli ste broj cvorova koji je preko 5000." << endl <<
			"Kreirace se graf sa najvise 5000 cvorova." << endl << endl;
	}
	else
		cout << "Kreiran je graf ciji je broj cvorova: " << n << endl << endl;
												//u slucaju da su svi cvorovi nepovezani, moze najvise oko 230 miliona zaglavlja da se alociraju
	graf = new ZaglavljeCvora [n];				//ali su onemogucene operacije umetanja i brisanja jer tada program puca od zauzeca memorije.
	for (int i = 0; i < n; i++) {				//za rad za svim datim operacijama je moguce sa naajvise oko 118 miliona zaglavlja nepovezanih cvorova
		graf[i].pok = nullptr;					//a ako su svi cvorovi u startu povezani sa svim ostalim cvorovima, da nebi doslo do prekida programa
		graf[i].broj_cvora = ++id;				//moguce je raditi sa oko 5000 cvorova.
	}
	postoji = true;					//postavljanje istinitosne vrednosti da je graf napravljen
}

void izborOperacija(int& op) {
	cout << "Pred vama su date sledece operacije sa grafom:" << endl <<
		"_____________________________________________" << endl <<
		"1. Kreiranje novog grafa." << endl << 
		"2. Dodavanje cvora u graf" << endl <<
		"3. Brisanje cvora iz grafa" << endl <<
		"4. Dodavanje grane izmedju dva cvora u grafu" << endl <<
		"5. Brisanje grane izmedju dva cvora u grafu" << endl <<
		"6. Ispis reprezentacije grafa" << endl <<
		"7. Brisanje grafa iz memorije" << endl <<
		"8. Izlaz iz programa" << endl <<
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
			if (op < 1 || op >8) {
				cout << "UNELI STE NEISPRAVAN BROJ OPERACIJE!" << endl <<
					"Pokusajte ponovo sa unosom: ";
			}
			else
				break;
		}
	}
	cout << endl;
}

void dodajCvor(ZaglavljeCvora*& graf, int& n) {
	n = n + 1;
	ZaglavljeCvora* graf1 = new ZaglavljeCvora [n];			//alokacija novog grafa sa jednom cvorom vise
	for (int i = 0; i < n-1; i++) {
		graf1[i].pok = graf[i].pok;							//prepisivanje vednosti starog grafa u novi
		graf1[i].broj_cvora = graf[i].broj_cvora;
	}
	graf1[n - 1].pok = nullptr;
	graf1[n - 1].broj_cvora = ++id;
	delete[] graf;											//brisanje starog grafa
	graf = graf1;											//stari graf postaje novi
	cout << "Dodat je cvor sa brojem " << graf1[n - 1].broj_cvora << endl << endl;
}

void brisiCvor(ZaglavljeCvora*& graf, int& n) {
	cout << "Unesite broj cvora koji zelite da obrisete: ";
	int broj;
	while (1) {												//postupak sprecavanja gresaka
		char c;
		if (!(cin >> broj) || (cin.get(c) && !isspace(c))) {
			cout << "UNELI STE VRDNOST KOJA NIJE CEO BROJ!" << endl <<
				"Pokusajte ponovo sa unosom: ";
			cin.clear();
			cin.ignore(500, '\n');
		}
		else {
			if (broj<1) {
				cout << "UNELI STE NEGATIVAN BROJ ILI NULU!" << endl <<
					"Pokusajte ponovo sa unosom: ";
			}
			else
				break;
		}
	}
	bool postoji = false;
	for (int i = 0; i < n; i++) {	//provera da li postoji dati cvor
		if (broj == graf[i].broj_cvora) {
			postoji = true;
			break;
		}
	} 
	if (postoji) {			//ako postoji
		for (int i = 0; i < n; i++) {			//provera svih cvorova
			if (graf[i].broj_cvora == broj) {	//ako je zaglavlje taj cvor
				while (graf[i].pok != nullptr) {//brisu se svi elementi u tom zaglavlju
					Cvor* tek = graf[i].pok;
					graf[i].pok = tek->sled;
					delete tek;
				}
			}
			else {								//ako zaglavlje nije taj cvor
				Cvor* tek = graf[i].pok;
				Cvor* pomocni = graf[i].pok;
				while (tek != nullptr) {		//provera da li je neki cvor povezan sa onim sto se brise
					if (tek->broj == broj) {	//ako jeste
						if (tek == graf[i].pok) {//ako je prvi posle zaglavlja
							graf[i].pok = tek->sled;
							delete tek;
							break;				//izlaz iz while petlje
						}
						while (pomocni->sled != tek)	//ako se nalazi negde u listi
							pomocni = pomocni->sled;
						pomocni->sled = tek->sled;
						delete tek;
						break;
					}
					tek = tek->sled;			//ako nije proverava se sledeci element
				}

			}
		}
		n = n - 1;
		ZaglavljeCvora* graf1 = new ZaglavljeCvora [n];				//stvaranje novog grafa
		for (int i = 0, i1 = 0; i < n; i++, i1++) {
			i1 = (graf[i].broj_cvora == broj) ? i1 + 1 : i1;		//za preskakanje cvora koji se brise
			graf1[i].broj_cvora = graf[i1].broj_cvora;
			graf1[i].pok = graf[i1].pok;
		}
		delete[] graf;												//brisanje starog grafa
		graf = graf1;												//stari graf postaje novi graf
		cout << "Obrisan je cvor sa brojem " << broj << endl << endl;
	}
	else {
		cout << "OVAJ CVOR NE POSTOJI U GRAFU!" << endl << endl;
	}
}

void dodajGranu(ZaglavljeCvora*& graf, int& n) {
	int c1, c2;
	bool postoji1 = false, postoji2 = false, isti = false;
	cout << "Unesite brojeve cvorova koje zelite da spojite granom." << endl;
	cout << "Prvi cvor: ";
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
			break;
		}
	}
	for (int i = 0; i < n; i++) {	//provera da li postoji cvor2
		if (c2 == graf[i].broj_cvora) {
			postoji2 = true;
			break;
		}
	}
	if (c1 == c2)									//provera da li se stvara petlja
		isti = true;
	if (postoji1 && postoji2 ) {			//ako je validan unos
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
		if (spojeni == false) {					//ako nisu spojeni
			if (isti) {							//ako se stvara petlja
				for (int i = 0; i < n; i++) {
					if (graf[i].broj_cvora == c1) {
						Cvor* novi = new Cvor;
						novi->broj = c1;
						novi->sled = nullptr;
						Cvor* tek = graf[i].pok;
						if (tek == nullptr) {	//da li je zaglavlje prazno
							graf[i].pok = novi;
						}
						else {					//umetanje na kraj liste
							while (tek->sled != nullptr)
								tek = tek->sled;
							tek->sled = novi;
						}
						break;
					}
				}
			}
			else {								//ako nisu isti
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
			}
			cout << "Cvorovi " << c1 << " i " << c2 << " su sada spojeni granom." << endl;
		}
		else {
			cout << "DATI CVOROVI SU VEC SPOJENI." << endl << endl;
		}
	}
	else {								//neispravan unos
		if (postoji1 == false)
			cout << "GRESKA PRI UNOSU BROJA PRVOG CVORA!" << endl;
		if (postoji2 == false)
			cout << "GRESKA PRI UNOSU BROJA DRUGOG CVORA!" << endl;
		cout << endl;
	}
}

void brisiGranu(ZaglavljeCvora*& graf, int& n) {
	int c1, c2;
	bool postoji1 = false, postoji2 = false, isti = false;
	cout << "Unesite brojeve cvorova kojima se uklanja grana." << endl;
	cout << "Prvi cvor: ";
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
			break;
		}
	}
	for (int i = 0; i < n; i++) {	//provera da li postoji cvor2
		if (c2 == graf[i].broj_cvora) {
			postoji2 = true;
			break;
		}
	}
	if (postoji1 && postoji2) {			//ako je validan unos
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
			if (isti) {
				for (int i = 0; i < n; i++) {
					if (graf[i].broj_cvora == c1) {					//nadjeno je zaglavlje
						Cvor* tek = graf[i].pok;
						Cvor* pomocni = tek;
						while (tek) {
							if (tek->broj == c1) {					//cvor je nadjen
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
						break;
					}
				}
			}
			else {
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
			}
			cout << "Uklonjena je grana izmedju cvorova " << c1 << " i " << c2 << endl;
		}
		else {
			cout << "DATI CVOROVI NISU SPOJENI." << endl << endl;
		}
	}
	else {								//neispravan unos
		if (postoji1 == false)
			cout << "GRESKA PRI UNOSU BROJA PRVOG CVORA!" << endl;
		if (postoji2 == false)
			cout << "GRESKA PRI UNOSU BROJA DRUGOG CVORA!" << endl;
		cout << endl;
	}

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
	int n = 0;
	bool rad = true, postoji = false;
	int op;
	while (rad) {
		izborOperacija(op);
		switch (op) {
			case 1: {
				if (postoji == true) {
					brisi(graf, n, postoji);
					cout << "Brise se stari graf." << endl;
					cout << "Graf je izbrisan iz memorije!" << endl;
				}
				unosCvorova(graf, n, postoji);
				break;
			}
			case 2: {
				if (postoji == false) {
					cout << "NEMOGUCE IZVRSITI OPERACIJU! Graf ne postoji. Napravite novi graf." << endl << endl;
					break;
				}
				dodajCvor(graf, n);
				break;
			}
			case 3: {
				if (postoji == false) {
					cout << "NEMOGUCE IZVRSITI OPERACIJU! Graf ne postoji. Napravite novi graf." << endl << endl;
					break;
				}
				brisiCvor(graf, n);
				break;
			}
			case 4: {
				if (postoji == false) {
					cout << "NEMOGUCE IZVRSITI OPERACIJU! Graf ne postoji. Napravite novi graf." << endl << endl;
					break;
				}
				dodajGranu(graf, n);
				break;
			}
			case 5: {
				if (postoji == false) {
					cout << "NEMOGUCE IZVRSITI OPERACIJU! Graf ne postoji. Napravite novi graf." << endl << endl;
					break;
				}
				brisiGranu(graf, n);
				break;
			}
			case 6: {
				if (postoji == false) {
					cout << "NEMOGUCE IZVRSITI OPERACIJU! Graf ne postoji. Napravite novi graf." << endl << endl;
					break;
				}
				ispis(graf, n);
				break;
			}
			case 7: {
				if (postoji == false) {
					cout << "NEMOGUCE IZVRSITI OPERACIJU! Graf ne postoji. Napravite novi graf." << endl << endl;
					break;
				}
				brisi(graf, n, postoji);
				cout << "Graf je izbrisan iz memorije!" << endl << endl;
				break;
			}
			case 8: {
				if (postoji == true) {
					brisi(graf, n, postoji);
				}
				cout << "Kraj rada." << endl;
				rad = false;
			}
		}
	}
	return 0;
}