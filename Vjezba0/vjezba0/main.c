#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int myStrlen(char* str)
{
	int count = 0;
	int i = 0;
	while (str[i] != '\0')
	{
		count++;
		i++;
	}

	return count;
}
void myStrcpy(char* str, char* str2)
{
	int i = 0;
	while (str[i] != '\0')
	{
		str2[i] = str[i];
		i++;
	}
	str2[i] = '\0';

}

int myStrcmp(char* str, char* str2)
{
	int i = 0;
	
	while (str[i] != '\0' || str2[i] != '\0')
	{
		if (str[i] < str2[i])
			return -1;
		else if (str[i] > str2[i])
			return 1;
		i++;
	}
	return 0;
}

void myStrcat(char* str, char* str2)
{
	int i = 0;
	int j = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	while (str2[j] != '\0')
	{
		str[i + j] = str2[j];
		str[i + j + 1] = '\0';
		j++;
	}
}

void myReverse(char* str, char* str2) {
	int i = 0, j = 0;

	while (str[i] != '\0') 
		i++;
	i--; 
	while (i >= 0) { 

		str2[j] = str[i];
		
		i--;
		j++;
	}
	str2[j] = '\0';

}

char* myStrStr(char* str, char* str2)
{
	while (*str)
	{
		char *pocetak = str;
		char *podstring = str2;

		while (*str && *podstring && *str == *podstring)
		{
			str++;
			podstring++;
		}
		
		if (!*podstring)
			return pocetak;

		str = pocetak + 1;	
	}
	return NULL;
}
	


void main()
{
	int length = 0;
	char str[30];
	char str2[30];
	char str3[30];
	printf("Unesi string: ");
	scanf("%s", str);
	str[myStrlen(str) + 1] = '\0';
	printf("Unesi drug string: ");
	scanf("%s", str2);
	str2[myStrlen(str2) + 1] = '\0';
	//printf("Unesi treci string: ");
	//scanf("%s", str3);
	//myStrcpy(str, str2);
	printf("Prvi string: %s \n", str);
	printf("Drugi string: %s \n", str2);
	//length=myStrlen(str);
	//printf("Duljina stringa je: %d \n", length);

	printf("usporedba: %d \n", myStrcmp(str, str2));
	//myStrcat(str, str2);
	//printf("Novonastali string je %s \n", str);
	//myReverse(str, str2);
	//printf("obrnuti string je %s \n", str2);
	
//	char* str_4 = myStrStr(str, str3);
	//printf("%s\n", str_4);
	//scanf("%s", str2);
	system("pause");
}