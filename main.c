#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include <inttypes.h>

// void alloc_mem(void *arr, int *len)
// {
// 	if (type == '1')
// 	{
// 		if (arr == NULL)
// 		arr = malloc()
// 	}
// 	else
// 	{
// 		if (type == '2')
// 		{
// 		}
// 		else if (type == '3')
// 		{
// 		}
// 	}
// }

void print(void *arr, int len)
{
	void *ptr = arr;
	int i;
	// printf("arr: %p\n", arr);
	// printf("len: %d\n", len);
	while(arr-ptr < len)
	{
		// printf("1arr: %p\n", arr);
		printf("type: %c\n", *(char *)arr);
		arr += 4 * sizeof(char);

		// printf("2arr: %p\n", arr);
		printf("len: %d\n", *(int *)arr);
		arr += sizeof(int);

		// // printf("3arr: %p\n", arr);
		// printf("dedicator: %s\n", *(char **)arr);
		// arr += sizeof(char *);

		// // printf("4arr: %p\n", arr);
		// printf("suma1: %d\n", *(int *)arr);
		// arr += sizeof(int);

		// // printf("5arr: %p\n", arr);
		// printf("suma2: %d\n", *(int *)arr);
		// arr += sizeof(int);

		// // printf("6arr: %p\n", arr);
		// printf("dedicatul: %s\n", *(char **)arr);
		// arr += sizeof(char *);

		// // printf("7arr: %p\n", arr);

		printf("dedicator: ");
		while (*(char *)arr != '\0')
		{
			printf("%c", *(char *)arr);
			arr += sizeof(char);
		}
		arr += sizeof(char);
		printf("\n");

		printf("suma1: %d\n", *(int *)arr);
		arr += sizeof(int);

		printf("suma2: %d\n", *(int *)arr);
		arr += sizeof(int);

		printf("dedicatul: ");
		while (*(char *)arr != '\0')
		{
			printf("%c", *(char *)arr);
			arr += sizeof(char);
		}
		arr += sizeof(char);
		printf("\n");
	}
	arr = ptr;
	// printf("arr at end print: %p\n", arr);
}

int add_last(void **arr, int *len, data_structure *data)
{
	// printf("arr in add_last: %p\n", *arr);
	if (*len == 0)
		*arr = malloc(sizeof(data->header) + data->header->len);
	else if (*len > 0)
		*arr = realloc(*arr, *len + sizeof(data->header) + data->header->len);

	void *ptr = *arr, *ptr2 = data->data;

	*arr += *len;
	// printf("size head: %d\n", sizeof(head));
	// printf("size arr: %d\n", sizeof(data->header->len) + sizeof(data->header->type));

	memcpy(*arr, &(data->header->type), sizeof(data->header->type));
	*arr += 4 * sizeof(unsigned char);
	memcpy(*arr, &data->header->len, sizeof(data->header->len));
	*arr += sizeof(unsigned int);

	memcpy(*arr, data->data, data->header->len);
	// // arr += sizeof(head);

	// // memcpy(arr + sizeof(data->header), data->data, 24);

	// // printf("dedicator: %s\n", *(char **)data->data);
	// memcpy(*arr, data->data, sizeof(char *));
	// // printf("dedicator: %s\n", *(char **)arr);
	// data->data += sizeof(char *);
	// *arr += sizeof(char *);

	// // printf("char* %d\n", sizeof(char*));

	// // printf("suma1: %d\n", *(int *)data->data);
	// memcpy(*arr, data->data, sizeof(int));
	// // printf("suma1: %d\n", *(int *)arr);
	// data->data += sizeof(int);
	// *arr += sizeof(int);

	// // printf("suma2: %d\n", *(int *)data->data);
	// memcpy(*arr, data->data, sizeof(int));
	// // printf("suma2: %d\n", *(int *)arr);
	// data->data += sizeof(int);
	// *arr += sizeof(int);

	// // printf("dedicatul: %s\n", *(char **)data->data);
	// memcpy(*arr, data->data, sizeof(char *));
	// // printf("dedicatul: %s\n", *(char **)arr);

	*arr = ptr;
	data->data = ptr2;
	*len += sizeof(data->header) + data->header->len;
	// printf("!!!!!!!1arr: %p\n", arr);
	// print(*arr, *len);
	// printf("arr in end add: %p\n", *arr);
	return 1;
}

// int add_at(void **arr, int *len, data_structure *data, int index)
// {

// }

// void find(void *data_block, int len, int index)
// {

// }

// int delete_at(void **arr, int *len, int index)
// {

// }

void print_data(data_structure *data)
{
	void *ptr = data->data;

	printf("dedicator: ");
	while (*(char *)data->data != '\0')
	{
		printf("%c", *(char *)data->data);
		data->data += sizeof(char);
	}
	data->data += sizeof(char);
	printf("\n");

	printf("suma1: %d\n", *(int *)data->data);
	data->data += sizeof(int);

	printf("suma2: %d\n", *(int *)data->data);
	data->data += sizeof(int);

	printf("dedicatul: ");
	while (*(char *)data->data != '\0')
	{
		printf("%c", *(char *)data->data);
		data->data += sizeof(char);
	}
	printf("\n");

	data->data = ptr;
}

void add_new_data(data_structure *new_data, char *dedicator, int suma1, int suma2, char *dedicatul)
{
	new_data->header = malloc(sizeof(head));

	new_data->header->type = '1';
	new_data->header->len = (strlen(dedicator) + strlen(dedicatul) + 2)*sizeof(char) + 2 * sizeof(int);
	printf("len in add1: %d\n", new_data->header->len);
	new_data->data = malloc(new_data->header->len);

	void *ptr = new_data->data;

	memcpy(new_data->data, dedicator, strlen(dedicator) + 1);
	new_data->data += strlen(dedicator) + 1;

	memcpy(new_data->data, &suma1, sizeof(int));
	new_data->data += sizeof(int);

	memcpy(new_data->data, &suma2, sizeof(int));
	new_data->data += sizeof(int);

	memcpy(new_data->data, dedicatul, strlen(dedicatul) + 1);

	new_data->data = ptr;

	//new_data->header->len = sizeof(new_data->data);
	//printf("len in add2: %d\n", new_data->header->len);

	//print_data(new_data);
}

int main()
{
	void *arr = NULL;
	int len = 0, exit = 0, suma1 = 7, suma2 = 13, ceva = 7;
	char command[257], dedicator[30] = "ion", dedicatul[30] = "maria";

	while (exit == 0)
	{
		scanf("%s", command);

		if (strcmp(command, "insert") == 0)
		{
			scanf("%s%d%d%s", dedicator, &suma1, &suma2, dedicatul);
			fflush(stdin);

			data_structure *new_data = (data_structure *)malloc(sizeof(data_structure));
			add_new_data(new_data, dedicator, suma1, suma2, dedicatul);

			 int ok = add_last(&arr, &len, new_data);
			//  printf("arr in main: %p\n", arr);

			free(new_data->header);
			free(new_data->data);
			free(new_data);
		}

		if (strcmp(command, "print") == 0)
		{
			// printf("placintica\n");
			print(arr, len);
		}

		if (strcmp(command, "exit") == 0)
			exit = 1;
	}

	free(arr);

	return 0;
}
