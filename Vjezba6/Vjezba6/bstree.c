#include <stdio.h>
#include <malloc.h>
#include "bstree.h"


BSTree NewBSTree()
{
	// Novo prazno stablo
	return NULL;
}

void AddNode(BSTree *bst, char *word)
{
	// Rekurzivno se traži mjesto za novi èvor u stablu. Ako rijeè postoji u stablu, ne dodaje se.
	// bst parametar je dvostruki pokazivaè.

	if (*bst == NULL) {
		BSTree tmp = (BSTree)malloc(sizeof(Node));
		tmp->left = tmp->right = NULL;
		tmp->word = word;
		*bst = tmp;
		return;
	}

	int rez = strcmp(word, (*bst)->word);
	if ((*bst)->left == NULL && (*bst)->right == NULL) {
		BSTree tmp = (BSTree)malloc(sizeof(Node));
		tmp->left = tmp->right = NULL;
		tmp->word = word;

		if (rez > 0)
			(*bst)->right = tmp;
		else if (rez < 0)
			(*bst)->left = tmp;
		return;
	}

	if (rez > 0)
		AddNode(&((*bst)->right), word);
	else if (rez < 0)
		AddNode(&((*bst)->left), word);
}

int BSTHeight(BSTree bst)
{
	// Rekurzivno se prolazi cijelo stablo da bi se pronašla najduža grana (visina stabla).
	if (bst == NULL)
		return 0;
	int prvi = BSTHeight(bst->left), drugi = BSTHeight(bst->right);
	if (prvi > drugi)
		return 1 + prvi;
	return 1 + drugi;
	return 0;
}

void PrintBSTree(BSTree bst)
{
	// Ispisuje rijeèi u stablu na ekran po abecednom redu.
	// In-order šetnja po stablu (lijevo dijete, èvor, desno dijete)
	if (bst == NULL)
		return;

	PrintBSTree(bst->left);
	puts(bst->word);
	PrintBSTree(bst->right);
}

void SaveBSTree(BSTree bst, FILE *fd)
{
	// Snima rijeè po rijeè iz stabla u tekstualnu datoteku. Rijeèi su odvojene razmakom.
	// Pre-order šetnja po stablu (ttenutni èvor pa djeca)
	if (bst == NULL)
		return;

	fprintf(fd, "%s\n", bst->word);
	SaveBSTree(bst->left, fd);
	SaveBSTree(bst->right, fd);
}

void DeleteBSTree(BSTree bst)
{
	// Briše stablo (string word i sam èvor) iz memorije.
	// Post-order šetnja po stablu (prvo djeca pa trenutni èvor)
	if (bst == NULL)
		return;

	DeleteBSTree(bst->left);
	DeleteBSTree(bst->right);
	free(bst->word);
	free(bst);
}

BSTree LoadBSTree(FILE *fd)
{
	// Uèitava rijeè po rijeè iz tekstualne datoteke i dodaje ih u stablo preko AddNode() funkcije.
	// Rijeè duplicirati sa strdup().

	//return NULL;
	char* buffer[1024];
	BSTree bst = NewBSTree();

	while (fgets(buffer, 1024, fd) != NULL)
		AddNode(&bst, _strdup(buffer));
	return bst;
}
