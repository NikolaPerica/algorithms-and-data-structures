#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int usporedi(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

int* generiraj(int n) {
	int* niz = (int*)malloc(sizeof(int) * n);
	niz[0] = rand() % 5;
	for (int i = 1; i < n; i++) {
		niz[i] = niz[i - 1] + 1 + rand() % 5;
	}
	return niz;
}

void shuffle(int* niz, int n) {
	for (int i = 0; i < n; i++) {
		int j = (rand() * rand()) % n;
		int tmp = niz[i];
		niz[i] = niz[j];
		niz[j] = tmp;
	}
}

void print(int* niz, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", niz[i]);
	}
	printf("\n");
}

void presjek(int* niz1, int* niz2, int n1, int n2) {
	clock_t start_t, end_t;
	double total_t;
	start_t = clock();

	int n = (n1 > n2) ? n1 : n2;
	int* presjekniz1 = (int*)malloc(n * sizeof(int));

	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n2; j++) {
			if (niz1[i] == niz2[j]) presjekniz1[--n] = niz1[i];
		}
	}
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Ukupno vrijeme u sekundama: %f\n", total_t);
}

void presjek_sortiran(int* niz1, int* niz2, int n1, int n2) {
	clock_t start_t, end_t;
	double total_t;
	start_t = clock();

	int n = (n1 > n2) ? n1 : n2;
	int* presjekniz1 = (int*)malloc(n * sizeof(int));

	int* presjek;
	for (int i = 0; i < n; i++) {
		presjek = (int*)bsearch(&niz1[i], niz2, n, sizeof(int), usporedi);
		if (presjek != NULL) {
			presjekniz1[--n] = *presjek;
		}
	}

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Ukupno vrijeme u sekundama: %f\n", total_t);
}

void presjek_oba_sortirana(int* niz1, int* niz2, int n1, int n2) {
	clock_t start_t, end_t;
	double total_t;
	start_t = clock();

	int n = (n1 > n2) ? n1 : n2;
	int* presjekniz1 = (int*)malloc(n * sizeof(int));

	qsort(niz2, n, sizeof(int), usporedi);

	int* presjek;

	for (int i = 0; i < n; i++) {
		presjek = (int*)bsearch(&niz1[i], niz2, n, sizeof(int), usporedi);
		if (presjek != NULL) {
			presjekniz1[--n] = *presjek;
		}
	}

	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Ukupno vrijeme u sekundama: %f\n", total_t);
}

void main() {
	srand(time(NULL));
	int* niz1;
	int* niz2;
	int n1=400000, n2=400000;

	niz1 = generiraj(n1);
	shuffle(niz1, n1);
	//print(niz1, n1);

	niz2 = generiraj(n2);
	shuffle(niz2, n2);
	//print(niz2, n2);
	
	printf("Izracun presjeka dva ne sortirana: \n");
	presjek(niz1, niz2, n1, n2);
	free(niz1);
	free(niz2);
	printf("Izracun presjeka sortiranog i nesortiranog: \n");
	niz1 = generiraj(n1);
	shuffle(niz1, n1);
	niz2 = generiraj(n2);
	presjek_sortiran(niz1, niz2, n1, n2);
	free(niz1);
	free(niz2);
	printf("Izracun presjeka 2 sortirana: \n");
	niz1 = generiraj(n1);
	shuffle(niz1, n1);
	niz2 = generiraj(n2);
	presjek_oba_sortirana(niz1, niz2, n1, n2);
	free(niz1);
	free(niz2);
}