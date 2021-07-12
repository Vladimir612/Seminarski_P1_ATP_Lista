#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "dvostruko_spregnuta_lista_specifikacija.h"

// GLAVNE FUNKCIJE
void ubaci(FILE* lista, int broj) {
	if (lista == NULL) {
		printf("Lista ne postoji, pa se ne moze promeniti broj!\n");
		return;
	}

	//Ubacivanje elementa na kraj liste!
	if (fwrite(&broj, sizeof(int), 1, lista) == 1) {
		printf("Uspesno dodat element u listu!\n");
		fflush(lista);
	}
	else {
		printf("Neuspesno dodat element u listu!\n");
	}
}

void izbaci(FILE* lista, int pozicija) {
	if (lista == NULL) {
		printf("Lista ne postoji, pa se ne moze promeniti broj!\n");
		return;
	}

	fseek(lista, 0, SEEK_END);
	int n = ftell(lista) / sizeof(int);
	fseek(lista, 0, SEEK_SET);

	if (pozicija >= n || pozicija < 0) {
		printf("Pozicija premasuje granice liste, mozete uneti poziciju u granici [0 do %d]", n - 1);
		return;
	}

	/*Pravljenje pomocne datoteke u koje ce biti upisani 
	svi clanovi liste osim onog sto se brise*/

	FILE* pom_dat = fopen("pomocna_lista.dat", "wb+");

	for (int i = 0; i < n; i++) {
		int pom;
		fread(&pom, sizeof(int), 1, lista);

		if (pozicija != i) {
			fwrite(&pom, sizeof(int), 1, pom_dat);
		}
	}

	fflush(pom_dat);
	//Zatvaranje trenutnih datoteka da bi mogla da se obrise prethodna datoteka
	fclose(lista);
	fclose(pom_dat);
	remove(datoteka_sa_listom);

	//Preimenovanje nove datoteke u naziv koju je stara imala
	rename("pomocna_lista.dat", datoteka_sa_listom);

	lista = fopen(datoteka_sa_listom, "ab+");
	printf("Element je uspesno izbacen iz liste!\n");
}

void promeni(FILE* lista, int pozicija, int broj) {
	if (lista == NULL) {
		printf("Lista ne postoji, pa se ne moze promeniti broj!\n");
		return;
	}

	fseek(lista, 0, SEEK_END);
	int n = ftell(lista) / sizeof(int);
	fseek(lista, 0, SEEK_SET);

	if (pozicija >= n || pozicija < 0) {
		printf("Pozicija premasuje granice liste, mozete uneti poziciju u granici [0 do %d]", n - 1);
		return;
	}

	//Postavljanje pozicije u listi na trazenu poziciju
	fseek(lista, pozicija * sizeof(int), SEEK_SET);

	//Overwrite-ovanje preko clana koji se nalazi na toj poziciji
	if (fwrite(&broj, sizeof(int), 1, lista) == 1) {
		printf("Broj je uspesno promenjen u listi\n");
		fflush(lista);
	}
	else {
		printf("Broj nije promenjen!\n");
	}
}

void prikazi(FILE* lista) {
	if (lista == NULL) {
		printf("Lista ne postoji, pa se ne moze promeniti broj!\n");
		return;
	}

	fseek(lista, 0, SEEK_END);
	int n = ftell(lista) / sizeof(int);
	fseek(lista, 0, SEEK_SET);

	for (int i = 0; i < n; i++) {
		int pom;
		fread(&pom, sizeof(int), 1, lista);
		printf("%d\t", pom);
	}
}

int nadji(FILE* lista, int element) {
	if (lista == NULL) {
		printf("Lista ne postoji, pa se ne moze promeniti broj!\n");
		return;
	}

	fseek(lista, 0, SEEK_END);
	int n = ftell(lista) / sizeof(int); //Utvrdjivanje duzine lista
	fseek(lista, 0, SEEK_SET); //Vracanje na pocetak liste

	int pom;
	for (int i = 0; i < n; i++) {
		fread(&pom, sizeof(int), 1, lista);
		if (pom == element) return i;
	}

	return -1;
}

void sortiraj(FILE* lista) {
	int br_elemenata, i, j, br_i, br_j;
	if (lista == NULL) {
		printf("Lista ne postoji, pa se ne moze promeniti broj!\n");
		return;
	}
	
	fseek(lista, 0, SEEK_END);
	br_elemenata = ftell(lista) / sizeof(int);

	for (i = 0; i < br_elemenata - 1; i++) {
		for (j = i + 1; j < br_elemenata; j++) {

			fseek(lista, i * sizeof(int), SEEK_SET);
			fread(&br_i, sizeof(int), 1, lista);
			fseek(lista, j * sizeof(int), SEEK_SET);
			fread(&br_j, sizeof(int), 1, lista);

			if (br_i > br_j) {
				fseek(lista, i * sizeof(int), SEEK_SET);
				fwrite(&br_j, sizeof(int), 1, lista);
				fseek(lista, j * sizeof(int), SEEK_SET);
				fwrite(&br_i, sizeof(int), 1, lista);
				fflush(lista);
			}
		}
	}
}

// KORISNIÈKI MENI

void korisnicki_meni() {
	printf("Dobrodosli u program za manipulisanje dvostruko ulancanom listom\n\n");
	printf("Unesite 1 ako zelite da ubacite novi element novu listu: \n");
	printf("Unesite 2 ako zelite da izbacite element iz liste: \n");
	printf("Unesite 3 ako zelite da promenite element na odredjenoj poziciji: \n");
	printf("Unesite 4 ako zelite da prikazete listu: \n");
	printf("Unesite 5 ako zelite da nadjete na kojoj se poziciji javlja prvo pojavljivanje elementa: \n");
	printf("Unesite 6 ako zelite da sortirate listu: \n");

	printf("Unesite 0 za kraj programa: \n");

	//Inicijalizacija liste iz datoteke
	FILE* lista;

	lista = fopen(datoteka_sa_listom, "wb+");

	if (lista == NULL) {
		printf("Lista ne postoji!!!\n");
		return;
	}

	int izbor = 0;

	int broj, pozicija;

	do {
		printf("\nVas izbor: \n");
		scanf("%d", &izbor);

		switch (izbor) {
		case 0:		break;
		case 1:
			printf("Unesi broj koji zelis da uneses u listu\n");
			scanf("%d", &broj);
			ubaci(lista, broj);
			break;
		case 2:
			printf("Unesi poziciju na kojoj zelis da izbacis element\n");
			scanf("%d", &pozicija);
			izbaci(lista, pozicija);
			break;
		case 3:
			printf("Unesi broj koji zelis da uneses na odredjenoj poziciji\n");
			scanf("%d", &broj);
			printf("Unesi poziciju na kojoj zelis da promenis element\n");
			scanf("%d", &pozicija);
			promeni(lista, pozicija, broj);
			break;
		case 4:		prikazi(lista);		break;
		case 5:
			printf("Unesi broj za koji zelis da saznas na kojoj je poziciji u listi\n");
			scanf("%d", &broj);
			pozicija = nadji(lista, broj);
			pozicija != -1 ? printf("Nalazi se na poziciji %d", pozicija) : printf("Ne postoji element\n");
			break;
		case 6:		sortiraj(lista);	break;
		default:	printf("Niste uneli odgovarajuci broj, probajte opet!\n");
		}
	} while (izbor != 0);

	fclose(lista);
}