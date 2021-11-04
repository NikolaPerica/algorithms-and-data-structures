#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

int* podniz(int* niz, int start, int stop)
{
	int j = 0;
	int size = stop - start;
	int* pod = (int*)malloc(size * sizeof(int));
	for (int i = start; i < stop; i++)
	{
		pod[j] = niz[i];
		j++;
	}
	return pod;
}

int* filtriraj(int* niz, int n, int th, int* nth)
{
	int br = 0;
	int i, j = 0;
	for (i = 0; i < n; i++)
	{
		if (niz[i] < th)
			br++;
	}
	*nth = br;
	int* filtrirani = (int*)malloc(br * sizeof(int));
	for (i = 0; i < n; i++) {
		if (niz[i] < th) {
			filtrirani[j++] = niz[i];
		}
	}
	return filtrirani;
}

int** podijeli(int* niz, int n)
{
	int size = n / 2;
	int** pniz = (int**)malloc(2 * sizeof(int*));

	pniz[0] = (int*)malloc(size * sizeof(int));
	pniz[1] = (int*)malloc((n - size) * sizeof(int));

	int i;
	for (i = 0; i < size; i++)
	{
		pniz[0][i] = niz[i];
		pniz[1][i] = niz[i + size];
	}
	if (n % 2 == 1)
		pniz[1][i] = niz[i + size];
	return pniz;
}


typedef struct
{
	float x, y;
}Tocka;

typedef struct
{
	Tocka *vrhovi;
	int n;

}Poligon;

Poligon* novi_poligon(float* tocke_x, float* tocke_y, int n)
{
	Tocka* nizVrhova= (Tocka*)malloc(n*sizeof(Tocka));
	Poligon* novi;
	novi = (Poligon*)malloc(sizeof(Poligon));
	novi->n = n;
	int i;
	for (i = 0; i < n; i++)
	{
		nizVrhova[i].x = tocke_x[i];
		nizVrhova[i].y = tocke_y[i];
	}
	novi->vrhovi = nizVrhova;
	return novi;
}

Tocka** pozitivni(Poligon* p, int* np)
{
	*np = 0;
	int i;
	for (i = 0; i < p->n; i++) {
		if (p->vrhovi[i].x > 0 && p->vrhovi[i].y > 0)
			(*np)++;
	}
	Tocka** pozitivni = (Tocka**)malloc((*np) * sizeof(Tocka));
	*np = 0;
	for (int i = 0; i < p->n; i++)
	{
		if (p->vrhovi[i].x > 0 && p->vrhovi[i].y > 0)
		{
			pozitivni[*np] = &(p->vrhovi[i]);
			(*np)++;
		}
	}
	return pozitivni;
}



int main(void)
{/*
	int niz[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
	int n = sizeof(niz) / sizeof(int);
	int start = 2;
	int stop = 6;
	printf("Niz je: ");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", niz[i]);
	}
	printf("\n");
	int* novi = podniz(niz, start, stop);
	printf("Podniz je: ");
	for (int i = 0; i < (stop-start); i++)
	{
		printf("%d ", novi[i]);
	}
	printf("\n");

	int i;
	int nth;
	int th = 5;
	int* filter = filtriraj(niz, n, th, &nth);
	printf("Filtrirani niz je: ");
	for (i = 0; i < nth; i++)
	{
		printf("%d ", filter[i]);
	}
	printf("\n");
	int** split;
	split = podijeli(niz, n);
	printf("Prvi dio niza je: ");
	for (i = 0; i < n / 2; i++)
	{
		printf("%d ", split[0][i]);
	}
	printf("\n");
	printf("Drugi dio niza je: ");
	for (i = 0; i < n / 2; i++)
	{
		printf("%d ", split[1][i]);
	}
	if (n % 2 == 1)
	{
		printf("%d", split[1][i]);
	}
	*/

	float tocke_x[] = { 3.0, 2.0, 1.0, 12.0 };
	float tocke_y[] = { -4.0, 2.0, 4.0, -5.3 };

	int n = sizeof(tocke_x) / sizeof(int);

	Poligon* new_pol;
	new_pol = novi_poligon(tocke_x, tocke_y, n);

	for (int i = 0; i < n; i++)
	{
		printf("Tocka %d: (%.2f, %.2f)\n", i + 1, new_pol->vrhovi[i].x, new_pol->vrhovi[i].y);
	}

	int np;

	Tocka** pozit = pozitivni(new_pol, &np);

	printf("Pozitivne tocke su: ");
	for (int i = 0; i < np; i++)
	{
		printf("(%.2f, %.2f) ", pozit[i]->x, pozit[i]->y);
	}

	system("pause");
	return 0;

}