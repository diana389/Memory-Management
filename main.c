#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include <inttypes.h>

void print(void *arr, int len)
{
	void *ptr = arr;
	unsigned char type;

	while (arr - ptr < len) // se verifica sa nu se depaseasca lungimea vectorului cu deplasarea
	{
		printf("Tipul %hhu\n", *(unsigned char *)arr); // se afiseaza tipul
		type = *(unsigned char *)arr;
		arr += 4 * sizeof(unsigned char);

		arr += sizeof(unsigned int);

		while (*(char *)arr != '\0') // se afiseaza caracterele primului sir
		{
			printf("%c", *(char *)arr);
			arr += sizeof(char);
		}
		arr += sizeof(char);

		printf(" pentru ");

		while (*(char *)arr != '\0') // se afiseaza caracterele celui de-al doilea sir
		{
			printf("%c", *(char *)arr);
			arr += sizeof(char);
		}
		arr += sizeof(char);

		printf("\n");

		if (type == 1)
		{
			printf("%" PRId8 "\n", *(int8_t *)arr); // se afiseaza prima suma
			arr += sizeof(int8_t);

			printf("%" PRId8 "\n", *(int8_t *)arr); // se afiseaza a doua suma
			arr += sizeof(int8_t);
		}

		else
		{
			if (type == 2)
			{
				printf("%" PRId16 "\n", *(int16_t *)arr); // se afiseaza prima suma
				arr += sizeof(int16_t);

				printf("%" PRId32 "\n", *(int32_t *)arr); // se afiseaza a doua suma
				arr += sizeof(int32_t);
			}
			else
			{
				printf("%" PRId32 "\n", *(int32_t *)arr); // se afiseaza prima suma
				arr += sizeof(int32_t);

				printf("%" PRId32 "\n", *(int32_t *)arr); // se afiseaza a doua suma
				arr += sizeof(int32_t);
			}
		}
		printf("\n");
	}

	arr = ptr;
}

int add_last(void **arr, int *len, data_structure *data)
{
	if (*len == 0)
		*arr = malloc(sizeof(data->header) + data->header->len);
	else
		*arr = realloc(*arr, *len + sizeof(data->header) + data->header->len);

	void *ptr = *arr;

	*arr += *len; // se muta la finalul elementelor din vector

	memcpy(*arr, &(data->header->type), sizeof(data->header->type)); // se copiaza tipul
	*arr += 4 * sizeof(unsigned char);
	memcpy(*arr, &data->header->len, sizeof(data->header->len)); // se copiaza lungimea
	*arr += sizeof(unsigned int);

	memcpy(*arr, data->data, data->header->len); // se copiaza datele

	*arr = ptr; // se revine la pozitia initiala
	*len += sizeof(data->header) + data->header->len; // creste lungimea vectorului

	return 0;
}

int add_at(void **arr, int *len, data_structure *data, int index)
{

	if (index < 0)
		return 0;

	int contor = 0, current_len_arr = 0;
	unsigned int data_len;
	void *start_arr = *arr;

	while (contor != index && current_len_arr < *len) // se parcurge vectorul pana la indice sau pana se depaseste dimensiunea
	{
		*arr += 4 * sizeof(unsigned char);
		data_len = *(unsigned int *)*arr;
		*arr += sizeof(unsigned int);
		*arr += data_len;
		current_len_arr += 4 * sizeof(unsigned char) + sizeof(unsigned int) + data_len;
		contor++;
	}

	*arr = start_arr;

	if (current_len_arr >= *len) // cazul in care indexul e mai mare decat numarul de elemente
	{

		int ok = add_last(arr, len, data); // se adauga la final 
		return 1;
	}

	*arr = realloc(*arr, *len + sizeof(data->header) + data->header->len); // se realoca pentru a incapea elementul nou
	start_arr = *arr;

	*arr += current_len_arr; // se ajunge la pozitia la care trebuie inserat elementul
	memcpy(*arr + sizeof(data->header) + data->header->len, *arr, *len - current_len_arr); // se copiaza datele urmatoare spre dreapta

	memcpy(*arr, &(data->header->type), sizeof(data->header->type)); // se copiaza tipul
	*arr += 4 * sizeof(unsigned char);
	memcpy(*arr, &data->header->len, sizeof(data->header->len)); // se copiaza lungimea
	*arr += sizeof(unsigned int);

	memcpy(*arr, data->data, data->header->len); // se copiaza datele
	*arr = start_arr; // se revine la pozitia initiala

	*len += sizeof(data->header) + data->header->len; // creste lungimea

	return 1;
}

void find(void *data_block, int len, int index)
{
	if (index < 0)
		return;

	int contor = 0, current_len_arr = 0;
	unsigned int data_len, elem_len;

	while (contor != index && current_len_arr < len) // se parcurge vectorul pana la indice sau pana se depaseste dimensiunea
	{
		data_block += 4 * sizeof(unsigned char);
		data_len = *(unsigned int *)data_block;
		data_block += sizeof(unsigned int);
		data_block += data_len;
		current_len_arr += 4 * sizeof(unsigned char) + sizeof(unsigned int) + data_len;
		contor++;
	}

	if (current_len_arr >= len) // cazul in care indexul e mai mare decat numarul de elemente
		return;

	void *start = data_block;
	data_block += 4 * sizeof(unsigned char);
	data_len = *(unsigned int *)data_block;
	elem_len = 4 * sizeof(unsigned char) + sizeof(unsigned int) + data_len; // se afla dimensiunea elementului pentru a il afisa

	data_block = start; // se revine la pozitia initiala
	print(data_block, elem_len); // se afiseaza
}

int delete_at(void **arr, int *len, int index)
{
	if (index < 0)
		return 0;

	int contor = 0, current_len_arr = 0;
	unsigned int data_len;
	void *start_arr = *arr;

	while (contor != index && current_len_arr < *len) // se parcurge vectorul pana la indice sau pana se depaseste dimensiunea
	{
		*arr += 4 * sizeof(unsigned char);
		data_len = *(unsigned int *)*arr;
		*arr += sizeof(unsigned int);
		*arr += data_len;
		current_len_arr += 4 * sizeof(unsigned char) + sizeof(unsigned int) + data_len;
		contor++;
	}

	if (current_len_arr >= *len) // cazul in care indexul e mai mare decat numarul de elemente
		return 0;

	*arr += 4 * sizeof(unsigned char);
	data_len = *(unsigned int *)*arr;
	*arr = start_arr + current_len_arr; // se ajunge la pozitia la care incepe elementul

	memcpy(*arr, *arr + sizeof(head) + data_len, *len - current_len_arr - sizeof(head) - data_len); // se copiaza datele urmatoare peste element
	*arr = start_arr; // se revine la pozitia initiala
	*arr = realloc(*arr, *len - sizeof(head) - data_len); // se realoca pentru noua dimensiune
	*len = *len - sizeof(head) - data_len; // se modifica lungimea vectorului

	return 1;
}

void add_new_data(data_structure *new_data, unsigned char type, char *dedicator, char *dedicatul)
{
	new_data->header = malloc(sizeof(head));

	new_data->header->type = type; // se completeaza tipul

	if (type == 1)
	{
		int8_t suma1, suma2;
		scanf("%s%" SCNd8 "%" SCNd8 "%s", dedicator, &suma1, &suma2, dedicatul);

		new_data->header->len = (strlen(dedicator) + strlen(dedicatul) + 2) * sizeof(char) + 2 * sizeof(int8_t); // se calculeaza dimensiunea datelor
		new_data->data = malloc(new_data->header->len);

		void *ptr = new_data->data;

		memcpy(new_data->data, dedicator, strlen(dedicator) + 1); // se copiaza primul sir in "data"
		new_data->data += strlen(dedicator) + 1; // se trece la pozitia de dupa primul sir

		memcpy(new_data->data, dedicatul, strlen(dedicatul) + 1); // se copiaza al doilea sir in "data"
		new_data->data += strlen(dedicatul) + 1; // se trece la pozitia de dupa al doilea sir

		memcpy(new_data->data, &suma1, sizeof(int8_t)); // se copiaza prima suma in "data"
		new_data->data += sizeof(int8_t); // se trece la pozitia de dupa prima suma

		memcpy(new_data->data, &suma2, sizeof(int8_t)); // se copiaza a doua suma in "data"
		new_data->data += sizeof(int8_t); // se trece la pozitia de dupa a doua suma

		new_data->data = ptr; // se revine la pozitia initiala
	}
	else
	{
		if (type == 2)
		{
			int16_t suma1;
			int32_t suma2;
			scanf("%s%" SCNd16 "%" SCNd32 "%s", dedicator, &suma1, &suma2, dedicatul);

			new_data->header->len = (strlen(dedicator) + strlen(dedicatul) + 2) * sizeof(char) + sizeof(int16_t) + sizeof(int32_t); // se calculeaza dimensiunea datelor
			new_data->data = malloc(new_data->header->len);

			void *ptr = new_data->data;

			memcpy(new_data->data, dedicator, strlen(dedicator) + 1); // se copiaza primul sir in "data"
			new_data->data += strlen(dedicator) + 1; // se trece la pozitia de dupa primul sir

			memcpy(new_data->data, dedicatul, strlen(dedicatul) + 1); // se copiaza al doilea sir in "data"
			new_data->data += strlen(dedicatul) + 1; // se trece la pozitia de dupa al doilea sir

			memcpy(new_data->data, &suma1, sizeof(int16_t)); // se copiaza prima suma in "data"
			new_data->data += sizeof(int16_t); // se trece la pozitia de dupa prima suma

			memcpy(new_data->data, &suma2, sizeof(int32_t)); // se copiaza a doua suma in "data"
			new_data->data += sizeof(int32_t); // se trece la pozitia de dupa a doua suma

			new_data->data = ptr; // se revine la pozitia initiala
		}
		else
		{
			int32_t suma1, suma2;
			scanf("%s%" SCNd32 "%" SCNd32 "%s", dedicator, &suma1, &suma2, dedicatul);

			new_data->header->len = (strlen(dedicator) + strlen(dedicatul) + 2) * sizeof(char) + 2 * sizeof(int32_t); // se calculeaza dimensiunea datelor
			new_data->data = malloc(new_data->header->len);

			void *ptr = new_data->data;

			memcpy(new_data->data, dedicator, strlen(dedicator) + 1); // se copiaza primul sir in "data"
			new_data->data += strlen(dedicator) + 1; // se trece la pozitia de dupa primul sir

			memcpy(new_data->data, dedicatul, strlen(dedicatul) + 1); // se copiaza al doilea sir in "data"
			new_data->data += strlen(dedicatul) + 1; // se trece la pozitia de dupa al doilea sir

			memcpy(new_data->data, &suma1, sizeof(int32_t)); // se copiaza prima suma in "data"
			new_data->data += sizeof(int32_t); // se trece la pozitia de dupa prima suma

			memcpy(new_data->data, &suma2, sizeof(int32_t)); // se copiaza a doua suma in "data"
			new_data->data += sizeof(int32_t); // se trece la pozitia de dupa a doua suma

			new_data->data = ptr; // se revine la pozitia initiala
		}
	}
}

int main()
{
	void *arr = NULL;
	int len = 0, exit = 0, ok;
	char command[257], dedicator[257], dedicatul[257];
	unsigned char type;

	while (exit == 0)
	{
		scanf("%s", command);

		if (strcmp(command, "insert") == 0)
		{
			scanf("%hhu", &type);
			data_structure *new_data = (data_structure *)malloc(sizeof(data_structure));
			add_new_data(new_data, type, dedicator, dedicatul); // se completeaza datele in structura

			ok = add_last(&arr, &len, new_data); // se adauga in vector

			free(new_data->header); // se elibereaza memora
			free(new_data->data);
			free(new_data);
		}

		if (strcmp(command, "insert_at") == 0)
		{
			int index;
			scanf("%d", &index);
			scanf("%hhu", &type);
			data_structure *new_data = (data_structure *)malloc(sizeof(data_structure));
			add_new_data(new_data, type, dedicator, dedicatul); // se completeaza datele in structura

			ok = add_at(&arr, &len, new_data, index); // se adauga in vector

			free(new_data->header); // se elibereaza memora
			free(new_data->data);
			free(new_data);
		}

		if (strcmp(command, "delete_at") == 0)
		{
			int index;
			scanf("%d", &index);
			ok = delete_at(&arr, &len, index); // se sterge elementul din vector
		}

		if (strcmp(command, "find") == 0)
		{
			int index;
			scanf("%d", &index);
			find(arr, len, index); // se cauta elementul in vector si se afiseaza
		}

		if (strcmp(command, "print") == 0)
			print(arr, len);

		if (strcmp(command, "exit") == 0)
			exit = 1;
	}

	free(arr); // se elibereaza memoria
	return 0;
}