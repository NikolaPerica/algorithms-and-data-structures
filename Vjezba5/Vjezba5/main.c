#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>


typedef struct Element {
	int prioritet;
	void* podatak;
}Element;

void DodajElement(Element* niz, int* zadnji, int p) 
{
	niz[*zadnji].prioritet = p;
	PopraviPremaVrhu(niz, (*zadnji));
	(*zadnji)++;
}

int PopraviPremaVrhu(Element* niz, int index) 
{
	int temp;
	if (index == 0) 
	{
		return 0;
	}
	if (niz[index].prioritet > niz[(index - 1) / 2].prioritet) 
	{
		temp = niz[index].prioritet;
		niz[index].prioritet = niz[(index - 1) / 2].prioritet;
		niz[(index - 1) / 2].prioritet = temp;

		PopraviPremaVrhu(niz, (index - 1) / 2);
	}
	else 
	{
		return 0;
	}
}

void IzbrisiElement(Element* niz, int* zadnji) 
{
	niz[0].prioritet = niz[(*zadnji) - 1].prioritet;
	niz[(*zadnji) - 1].prioritet = NULL;
	(*zadnji)--;
	PopraviPremaDnu(niz, 0, *zadnji);
}

int PopraviPremaDnu(Element* niz, int index, int max) 
{
	int L = 2 * index + 1;
	int D = 2 * index + 2;
	int temp;

	if ((L > max) && (D > max)) 
	{
		return 0;
	}
	if (D > max)
	{
		if (niz[index].prioritet < niz[L].prioritet)
		{
			temp = niz[index].prioritet;
				niz[index].prioritet = niz[L].prioritet;
				niz[L].prioritet = temp;
				PopraviPremaDnu(niz, L, max);
		}
	}
	else if ((niz[index].prioritet < niz[L].prioritet) && (niz[L].prioritet > niz[D].prioritet))
	{
		if (niz[L].prioritet > niz[D].prioritet)
		{
			temp = niz[index].prioritet;
			niz[index].prioritet = niz[L].prioritet;
			niz[L].prioritet = temp;
			PopraviPremaDnu(niz, L, max);
		}
		else if ((niz[index].prioritet < niz[D].prioritet))
		{
			temp = niz[index].prioritet;
			niz[index].prioritet = niz[D].prioritet;
			niz[D].prioritet = temp;
			PopraviPremaDnu(niz, D, max);
		}
	}
	else 
	{
		return 0;
	}
}

void IspisiNiz(Element* niz, int n) 
{
	for (int i = 0; i < n; i++) {
		printf("%d ", niz[i].prioritet);
	}
}

void main() 
{

	Element gomila[10000] = { 100, 100, 100, 100, 100, 100, 100, 100, 100, 100 };
	int elCount = 0;

	DodajElement(gomila, &elCount, 5);
	DodajElement(gomila, &elCount, 4);
	DodajElement(gomila, &elCount, 3);
	DodajElement(gomila, &elCount, 2);
	//DodajElement(gomila, &elCount, 50);
	//DodajElement(gomila, &elCount, 6);
	//DodajElement(gomila, &elCount, 7);
	//DodajElement(gomila, &elCount, 8);
	//DodajElement(gomila, &elCount, 1);

	IzbrisiElement(gomila, &elCount);
	/*IzbrisiElement(gomila, &elCount);
	IzbrisiElement(gomila, &elCount);
	IzbrisiElement(gomila, &elCount);
	IzbrisiElement(gomila, &elCount);
	IzbrisiElement(gomila, &elCount);*/
	

	IspisiNiz(gomila, elCount);

}