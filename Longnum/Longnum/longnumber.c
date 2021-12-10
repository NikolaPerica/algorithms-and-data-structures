#include "longnumber.h"

LongNumber addElement(LongNumber list, int z) {
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
LongNumber reverse(LongNumber num) {
	LongNumber prev = NULL;
	LongNumber current = num;
	LongNumber next;
	
	while (current != NULL) {
		
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	num = prev;
	return num;
}

// cita broj iz tekstualne datoteke znamenku po znamenku i gradi listu (dugi broj)

LongNumber read_longnum(char* fname) {

	int buffer;

	FILE* fp;
	fp = fopen(fname, "r");

	LongNumber list;
	list = NULL;

	while (!feof(fp)) {
		buffer = fgetc(fp);
		if (buffer != EOF)
			list = addElement(list, buffer - '0');
	}

	list = reverse(list);
	return list;
}

// zapisuje broj u tekstualnu datoteku znamenku po znamenku
void write_longnum(LongNumber num, char* fname) {
	FILE* fp;
	fp = fopen(fname, "w");

	while (num != NULL) {
		fputc(num->z + '0', fp);
		num = num->next;
	}
}

// ispisuje broj na ekran 
void print_longnum(LongNumber num) {
	LongNumber s = num;
	while (s != NULL) {
		printf("%d", s->z);
		s = s->next;
	}
	printf("\n");
	
}

// oslobadja listu znamenaka
void delete_longnum(LongNumber num) {
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

// zbraja dva broja. 
// Algoritam zbraja znamenku po znamenku i prenosi ostatak na iducu znamenku.
// Gradi se potpuno nova lista (broj) kao rezultat.
LongNumber add_longnum(LongNumber numa, LongNumber numb) {
	LongNumber newNum;
	int overflow = 0;

	newNum = NULL;
	
	if (numa == NULL) {
		newNum = numb;
		return newNum;
	}
	else if (numb == NULL) {
		newNum = numa;
		return newNum;
	}

	LongNumber sa = numa, sb = numb;
	
	while (sa != NULL && sb != NULL) {

		newNum = addElement(newNum, (sa->z + sb->z + overflow) % 10);

		if ((sa->z + sb->z + overflow) > 9)
			overflow = 1;
		else
			overflow = 0;

		sa = sa->next;
		sb = sb->next;
	}
	if (sa == NULL)
		while (sb != NULL) {
			if (overflow) {
				newNum = addElement(newNum, sb->z + overflow);
				overflow = 0;
			}
			else
				newNum = addElement(newNum, sb->z + overflow);
			sb = sb->next;
		}
	else if (sb == NULL)
		while (sa != NULL) {
			if (overflow) {
				newNum = addElement(newNum, sa->z + overflow);
				overflow = 0;
			}
			else
				newNum = addElement(newNum, sa->z + overflow);
			sa = sa->next;
		}
	if (overflow)
		newNum = addElement(newNum, overflow);
	
	//newNum=reverse(newNum);
	return newNum;
}


// pomocna funkcija koja mnozi broj sa znamenkom (uz prenosenje ostatka na iducu znamenku). 
// Gradi se potpuno nova lista (broj) kao rezultat.
LongNumber mul_by_digit(LongNumber num, int z) {
	LongNumber d = NULL;
	int prijenos = 0, umnozak, tmpN;
	LongNumber tmp;
	tmp = reverse(num);
	
	while (tmp != NULL || prijenos > 0) {
		if (tmp == NULL) {
			tmpN = 0;
		}
		else {
			tmpN = tmp->z;
			tmp = tmp->next;
		}
		umnozak = tmpN * z + prijenos;
		
		if ((umnozak) > 9) {
			
			d = addElement(d, (umnozak % 10));
			prijenos = umnozak / 10;
		}
		else {
			d = addElement(d, umnozak);
			prijenos = 0;
		}
		if (num == NULL && prijenos > 10) {
			d = addElement(d, prijenos % 10);
			prijenos = prijenos / 10;
		}
		else if (num == NULL) {
			d = addElement(d, prijenos);
			prijenos = 0;
		}


	}
	//num = tmp;
	//d = reverse(d);
	return d;
}

// pomocna funkcija koja mnozi broj sa potencijom od 10 (odnosno dodaje nule na pocetak broja)
// Gradi se potpuno nova lista (broj) kao rezultat.
LongNumber mul_by_pow10(LongNumber num, int pow) {

	LongNumber tmp = reverse(num);
	if (tmp == NULL) {
		return NULL;
	}

	for (int i = 0; i < pow; i++) {
		tmp = addElement(tmp, 0);
	}

	return reverse(tmp);
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

LongNumber mul_longnum(LongNumber numa, LongNumber numb) {
	LongNumber rez = NULL;
	int _1 = 0, _2 = 0;
	while (numa || numb) {
		if (numa) {
			_1 = _1 * 10 + numa->z;
			numa = numa->next;
		}
		if (numb) {
			_2 = _2 * 10 + numb->z;
			numb = numb->next;
		}
	}
	int result = _1 * _2;
	while (result) {
		addElement(rez, result % 10);
		result /= 10;
	}
	print_longnum(rez);
	return rez;
	
}

