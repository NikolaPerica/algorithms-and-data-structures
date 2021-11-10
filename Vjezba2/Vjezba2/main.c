#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct VrhTrokuta 
{
	float T1x, T1y, T1z;
	float T2x, T2y, T2z;
	float T3x, T3y, T3z;
}VrhTrokuta;

typedef struct Trokut 
{
	float Nx, Ny, Nz;
	VrhTrokuta Vrhovi;
	unsigned short bojaTrokuta;
}Trokut;

typedef struct Objekt3D 
{
	Trokut* nizTrokuta;
	unsigned int brojTrokuta;
}Objekt3D;


Objekt3D* ReadFromFile(FILE* fp, Objekt3D* obj) {


	fseek(fp, 80, SEEK_SET);

	fread(&obj->brojTrokuta, sizeof(unsigned int), 1, fp);
	int n = obj->brojTrokuta;


	obj->nizTrokuta = malloc(sizeof(Trokut) * n);

	for (int i = 0; i < n; i++) {
		fread(&obj->nizTrokuta[i].Nx, sizeof(float), 1, fp);
		fread(&obj->nizTrokuta[i].Ny, sizeof(float), 1, fp);
		fread(&obj->nizTrokuta[i].Nz, sizeof(float), 1, fp);

		fread(&obj->nizTrokuta[i].Vrhovi.T1x, sizeof(float), 1, fp);
		fread(&obj->nizTrokuta[i].Vrhovi.T1y, sizeof(float), 1, fp);
		fread(&obj->nizTrokuta[i].Vrhovi.T1z, sizeof(float), 1, fp);
		fread(&obj->nizTrokuta[i].Vrhovi.T2x, sizeof(float), 1, fp);
		fread(&obj->nizTrokuta[i].Vrhovi.T2y, sizeof(float), 1, fp);
		fread(&obj->nizTrokuta[i].Vrhovi.T2z, sizeof(float), 1, fp);
		fread(&obj->nizTrokuta[i].Vrhovi.T3x, sizeof(float), 1, fp);
		fread(&obj->nizTrokuta[i].Vrhovi.T3y, sizeof(float), 1, fp);
		fread(&obj->nizTrokuta[i].Vrhovi.T3z, sizeof(float), 1, fp);

		fread(&obj->nizTrokuta[i].bojaTrokuta, sizeof(unsigned short), 1, fp);
	}

	return obj;
}

void WriteToFile(FILE* fwp, Objekt3D* obj) {
	char buffer[80] = { 0 };

	fwrite(buffer, 1, 80, fwp);
	int n = obj->brojTrokuta;
	fwrite(&n, 4, 1, fwp);

	for (int i = 0; i < n; i++) {
		fwrite(&obj->nizTrokuta[i].Nx, sizeof(float), 1, fwp);
		fwrite(&obj->nizTrokuta[i].Ny, sizeof(float), 1, fwp);
		fwrite(&obj->nizTrokuta[i].Nz, sizeof(float), 1, fwp);

		fwrite(&obj->nizTrokuta[i].Vrhovi.T1x, sizeof(float), 1, fwp);
		fwrite(&obj->nizTrokuta[i].Vrhovi.T1y, sizeof(float), 1, fwp);
		fwrite(&obj->nizTrokuta[i].Vrhovi.T1z, sizeof(float), 1, fwp);
		fwrite(&obj->nizTrokuta[i].Vrhovi.T2x, sizeof(float), 1, fwp);
		fwrite(&obj->nizTrokuta[i].Vrhovi.T2y, sizeof(float), 1, fwp);
		fwrite(&obj->nizTrokuta[i].Vrhovi.T2z, sizeof(float), 1, fwp);
		fwrite(&obj->nizTrokuta[i].Vrhovi.T3y, sizeof(float), 1, fwp);
		fwrite(&obj->nizTrokuta[i].Vrhovi.T3y, sizeof(float), 1, fwp);
		fwrite(&obj->nizTrokuta[i].Vrhovi.T3z, sizeof(float), 1, fwp);

		fwrite(&obj->nizTrokuta[i].bojaTrokuta, sizeof(unsigned short), 1, fwp);
	}


}

void WriteToTextFile(FILE* fwtp, Objekt3D* obj) {

	fprintf(fwtp, "solid OpenSCAD_Model\n");

	int n = obj->brojTrokuta;
	for (int i = 0; i < n; i++) {
		fprintf(fwtp, "facet normal %f %f %f\n", obj->nizTrokuta[i].Nx, obj->nizTrokuta[i].Ny, obj->nizTrokuta[i].Nz);
		fprintf(fwtp, "\t outer loop\n");
		fprintf(fwtp, "\t\t vertex %f %f %f\n", obj->nizTrokuta[i].Vrhovi.T1x, obj->nizTrokuta[i].Vrhovi.T1y, obj->nizTrokuta[i].Vrhovi.T1z);
		fprintf(fwtp, "\t\t vertex %f %f %f\n", obj->nizTrokuta[i].Vrhovi.T2x, obj->nizTrokuta[i].Vrhovi.T2y, obj->nizTrokuta[i].Vrhovi.T2z);
		fprintf(fwtp, "\t\t vertex %f %f %f\n", obj->nizTrokuta[i].Vrhovi.T3x, obj->nizTrokuta[i].Vrhovi.T3y, obj->nizTrokuta[i].Vrhovi.T3z);
		fprintf(fwtp, "\t endloop\n");
		fprintf(fwtp, "endfacet\n\n");
	}
	fprintf(fwtp, "endsolid OpenSCAD_Model\n");

}

void DeleteObjekt3D(Objekt3D* obj) {
	free(obj->nizTrokuta);
	free(obj);
}


void main() {

	FILE* fp;
	FILE* fpwb;
	FILE* fpwt;
	Objekt3D* obj = (Objekt3D*)malloc(sizeof(Objekt3D));

	fp = fopen("primjerbin.stl", "rb");
	if (fp == NULL) {
		printf("File ne postoji. \n");
	}
	else {
		obj = ReadFromFile(fp, obj);
	}
	fclose(fp);

	fpwb = fopen("binSTL.stl", "wb");
	if (fpwb == NULL) {
		printf("File ne postoji. \n");
	}
	else {
		WriteToFile(fpwb, obj);
	}
	fclose(fpwb);


	fpwt = fopen("txtSTL.stl", "wt");
	if (fpwt == NULL) {
		printf("File ne postoji. \n");
	}
	else {
		WriteToTextFile(fpwt, obj);
	}
	fclose(fpwt);
}