#include "longnumber.h"
#include <stdio.h>
#include <stdlib.h>

LongNumber AddToHead(LongNumber list, int z) 
{
	LongNumber newNum;
	newNum = (LongNumber)malloc(sizeof(Digit));

	newNum->z = z;
	newNum->next = list;
	list = newNum;

	return list;
}

// pomocna funkcija koja okrece listu znamenaka, trebati ce na vise mjesta
// jer ce se operacije uglavnom oslanjati na dodavanje u glavu liste
// ne gradi novu listu nego preuredjuje dobivenu listu
LongNumber reverse(LongNumber num) 
{
	LongNumber rev = NULL;

	while (num != NULL) {
		LongNumber tmp = (LongNumber)malloc(sizeof(Digit));
		if (!tmp)
			return NULL;
		tmp->z = num->z;
		tmp->next = rev;
		rev = tmp;
		num = num->next;
	}

	return rev;
}

// cita broj iz tekstualne datoteke znamenku po znamenku i gradi listu (dugi broj)
LongNumber read_longnum(char* fname) 
{
	int buffer;

	FILE* fp;
	fp = fopen(fname, "r");

	LongNumber list;
	list = NULL;

	while (!feof(fp)) 
	{
		buffer = fgetc(fp);
		if (buffer != EOF)
			list = AddToHead(list, buffer - '0');
	}

	list = reverse(list);
	return list;
}

// zapisuje broj u tekstualnu datoteku znamenku po znamenku
void write_longnum(LongNumber num, char* fname) 
{
	FILE* fp;
	fp = fopen(fname, "w");

	while (num != NULL) 
	{
		fputc(num->z + '0', fp);
		num = num->next;
	}
}

// ispisuje broj na ekran 
void print_longnum(LongNumber num) 
{
	LongNumber s = num;
	while (s != NULL) 
	{
		printf("%d", s->z);
		s = s->next;
	}
	printf("\n");
}

// oslobadja listu znamenaka
void delete_longnum(LongNumber num) 
{
	if (num == NULL)
		return;
	LongNumber tmp1 = num, tmp2 = num->next;
	while (tmp2 != NULL) {
		free(tmp1);
		tmp1 = tmp2;
		tmp2 = tmp2->next;
	}
	free(tmp1);
}

LongNumber add_longnum(LongNumber numa, LongNumber numb) 
{
	LongNumber newNum;
	int overflow = 0;

	newNum = NULL;

	if (numa == NULL)
	{
		newNum = numb;
		return newNum;
	}
	else if (numb == NULL)
	{
		newNum = numa;
		return newNum;
	}

	LongNumber sa = reverse(numa);
	LongNumber sb = reverse(numb);

	while (sa != NULL && sb != NULL) 
	{

		newNum = AddToHead(newNum, (sa->z + sb->z + overflow) % 10);

		if ((sa->z + sb->z + overflow) > 9)
			overflow = 1;
		else
			overflow = 0;

		sa = sa->next;
		sb = sb->next;
	}
	if (sa == NULL)
		while (sb != NULL) 
		{
			if (overflow) 
			{
				newNum = AddToHead(newNum, sb->z + overflow);
				overflow = 0;
			}
			else
				newNum = AddToHead(newNum, sb->z + overflow);
			sb = sb->next;
		}
	else if (sb == NULL)
		while (sa != NULL) 
		{
			if (overflow) 
			{
				newNum = AddToHead(newNum, sa->z + overflow);
				overflow = 0;
			}
			else
				newNum = AddToHead(newNum, sa->z + overflow);
			sa = sa->next;
		}
	if (overflow)
		newNum = AddToHead(newNum, overflow);

	return newNum;
}

// zbraja dva broja. 
// Algoritam zbraja znamenku po znamenku i prenosi ostatak na iducu znamenku.
LongNumber mul_by_digit(LongNumber num, int z) 
{
	LongNumber s = reverse(num), newNum;
	int overflow = 0;

	newNum = NULL;

	if (num == NULL)
		return newNum;

	while (s != NULL) 
	{
		newNum = AddToHead(newNum, ((s->z) * z + overflow) % 10);
		overflow = ((s->z) * z + overflow) / 10;

		s = s->next;
	}
	while (overflow) 
	{
		newNum = AddToHead(newNum, overflow % 10);
		overflow /= 10;
	}

	return newNum;
}

// pomocna funkcija koja mnozi broj sa potencijom od 10 (odnosno dodaje nule na pocetak broja)
// Gradi se potpuno nova lista (broj) kao rezultat.
LongNumber mul_by_pow10(LongNumber num, int pow) 
{
	LongNumber newNum = reverse(num);
	for (int i = 0; i < pow; i++)
		newNum = AddToHead(newNum, 0);
	newNum = reverse(newNum);
	return newNum;
}
// mnozi dva broja oslanjanjuci se na prethodne funkcije. Primjer:
// 123 x 235
// ---------
//   123 * 10^0 * 5
//   123 * 10^1 * 3
// + 123 * 10^2 * 2
// --------
//  28905 
// Gradi se potpuno nova lista (broj) kao rezultat.
LongNumber mul_longnum(LongNumber numa, LongNumber numb) 
{
	numb = reverse(numb);
	LongNumber suma = NULL;
	LongNumber tmp = (LongNumber)malloc(sizeof(Digit));

	int i = 0;

	while (numb != NULL) {
		

		tmp = mul_by_digit(numa, numb->z);
		tmp = mul_by_pow10(tmp, i);

		if (suma != NULL) {
			suma = add_longnum(suma, tmp);
		}
		else {
			suma = tmp;
		}

		i++;

		numb = numb->next;
	}

	return suma;

}