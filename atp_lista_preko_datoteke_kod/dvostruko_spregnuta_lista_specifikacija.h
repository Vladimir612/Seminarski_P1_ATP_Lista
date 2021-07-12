#define _CRT_SECURE_NO_WARNINGS

#ifndef _DVOSTRUKO_SPREGNUTA_LISTA_SPECIFIKACIJA_H
#define _DVOSTRUKO_SPREGNUTA_LISTA_SPECIFIKACIJA_H

#include <stdio.h>
#include <stdlib.h>

//DATOTEKA SA LISTOM
#define datoteka_sa_listom "lista.dat"

// GLAVNE FUNKCIJE
void	ubaci		(FILE* lista, int broj);
void	izbaci		(FILE* lista, int pozicija);
void	promeni		(FILE* lista, int pozicija, int broj);
void	prikazi		(FILE* lista);
int		nadji		(FILE* lista, int element);
void	sortiraj	(FILE* lista);

// KORISNIÈKI MENI
void korisnicki_meni();

#endif