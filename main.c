#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include <inttypes.h>

void print_pt_mine(void *arr, int len)
{
	void *ptr = arr;
	unsigned char type;

	while (arr - ptr < len)
	{
		printf("type: %hhu\n", *(unsigned char *)arr);
		type = *(unsigned char *)arr;
		arr += 4 * sizeof(unsigned char);

		printf("len: %d\n", *(unsigned int *)arr);
		arr += sizeof(unsigned int);

		printf("dedicator: ");
		while (*(char *)arr != '\0')
		{
			printf("%c", *(char *)arr);
			arr += sizeof(char);
		}
		arr += sizeof(char);
		printf("\n");

		printf("dedicatul: ");
		while (*(char *)arr != '\0')
		{
			printf("%c", *(char *)arr);
			arr += sizeof(char);
		}
		arr += sizeof(char);
		printf("\n");

		if (type == 1)
		{
			printf("suma1: %" PRId8 "\n", *(int8_t *)arr);
			arr += sizeof(int8_t);

			printf("suma2: %" PRId8 "\n", *(int8_t *)arr);
			arr += sizeof(int8_t);
		}

		else
		{
			if (type == 2)
			{
				printf("suma1: %" PRId16 "\n", *(int16_t *)arr);
				arr += sizeof(int16_t);

				printf("suma2: %" PRId32 "\n", *(int32_t *)arr);
				arr += sizeof(int32_t);
			}
			else
			{
				printf("suma1: %" PRId32 "\n", *(int32_t *)arr);
				arr += sizeof(int32_t);

				printf("suma2: %" PRId32 "\n", *(int32_t *)arr);
				arr += sizeof(int32_t);
			}
		}
	}
	arr = ptr;
}

void print(void *arr, int len)
{
	void *ptr = arr;
	unsigned char type;

	while (arr - ptr < len)
	{
		printf("Tipul %hhu\n", *(unsigned char *)arr);
		type = *(unsigned char *)arr;
		arr += 4 * sizeof(unsigned char);

		arr += sizeof(unsigned int);

		while (*(char *)arr != '\0')
		{
			printf("%c", *(char *)arr);
			arr += sizeof(char);
		}
		arr += sizeof(char);

		printf(" pentru ");

		while (*(char *)arr != '\0')
		{
			printf("%c", *(char *)arr);
			arr += sizeof(char);
		}
		arr += sizeof(char);

		printf("\n");

		if (type == 1)
		{
			printf("%" PRId8 "\n", *(int8_t *)arr);
			arr += sizeof(int8_t);

			printf("%" PRId8 "\n", *(int8_t *)arr);
			arr += sizeof(int8_t);
		}

		else
		{
			if (type == 2)
			{
				printf("%" PRId16 "\n", *(int16_t *)arr);
				arr += sizeof(int16_t);

				printf("%" PRId32 "\n", *(int32_t *)arr);
				arr += sizeof(int32_t);
			}
			else
			{
				printf("%" PRId32 "\n", *(int32_t *)arr);
				arr += sizeof(int32_t);

				printf("%" PRId32 "\n", *(int32_t *)arr);
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

	*arr += *len;

	memcpy(*arr, &(data->header->type), sizeof(data->header->type));
	*arr += 4 * sizeof(unsigned char);
	memcpy(*arr, &data->header->len, sizeof(data->header->len));
	*arr += sizeof(unsigned int);

	memcpy(*arr, data->data, data->header->len);

	*arr = ptr;
	*len += sizeof(data->header) + data->header->len;

	return 0;
}

int add_at(void **arr, int *len, data_structure *data, int index)
{

	if (index < 0)
		return 0;

	int contor = 0, current_len_arr = 0;
	unsigned int data_len;
	void *start_arr = *arr;

	while (contor != index && current_len_arr < *len)
	{
		*arr += 4 * sizeof(unsigned char);
		data_len = *(unsigned int *)*arr;
		// printf("data_len: %d\n", data_len);
		*arr += sizeof(unsigned int);
		*arr += data_len;
		current_len_arr += 4 * sizeof(unsigned char) + sizeof(unsigned int) + data_len;
		// printf("current_len: %d\nlen: %d\n", current_len_arr, *len);
		contor++;
	}

	*arr = start_arr;

	if (current_len_arr >= *len)
	{

		int ok = add_last(arr, len, data);
		return 1;
	}

	*arr = realloc(*arr, *len + sizeof(data->header) + data->header->len);
	start_arr = *arr;

	*arr += current_len_arr;
	memcpy(*arr + sizeof(data->header) + data->header->len, *arr, *len - current_len_arr);

	memcpy(*arr, &(data->header->type), sizeof(data->header->type));
	*arr += 4 * sizeof(unsigned char);
	memcpy(*arr, &data->header->len, sizeof(data->header->len));
	*arr += sizeof(unsigned int);

	memcpy(*arr, data->data, data->header->len);
	 *arr = start_arr;

	 *len += sizeof(data->header) + data->header->len;

	return 1;
}

void find(void *data_block, int len, int index)
{
	if (index < 0)
		return;

	int contor = 0, current_len_arr = 0;
	unsigned int data_len, elem_len;

	while (contor != index && current_len_arr < len)
	{
		data_block += 4 * sizeof(unsigned char);
		data_len = *(unsigned int *)data_block;
		data_block += sizeof(unsigned int);
		data_block += data_len;
		current_len_arr += 4 * sizeof(unsigned char) + sizeof(unsigned int) + data_len;
		contor++;
	}

	if (current_len_arr >= len)
		return;

	void *start = data_block;
	data_block += 4 * sizeof(unsigned char);
	data_len = *(unsigned int *)data_block;
	elem_len = 4 * sizeof(unsigned char) + sizeof(unsigned int) + data_len;

	data_block = start;
	print(data_block, elem_len);
}

int delete_at(void **arr, int *len, int index)
{
	if (index < 0)
		return 0;

	int contor = 0, current_len_arr = 0;
	unsigned int data_len;
	void *start_arr = *arr;

	while (contor != index && current_len_arr < *len)
	{
		*arr += 4 * sizeof(unsigned char);
		data_len = *(unsigned int *)*arr;
		*arr += sizeof(unsigned int);
		*arr += data_len;
		current_len_arr += 4 * sizeof(unsigned char) + sizeof(unsigned int) + data_len;
		contor++;
	}

	if (current_len_arr >= *len)
		return 0;

	*arr += 4 * sizeof(unsigned char);
	data_len = *(unsigned int *)*arr;
	*arr = start_arr + current_len_arr;

	memcpy(*arr, *arr + sizeof(head) + data_len, *len - current_len_arr - sizeof(head) - data_len);
	*arr = start_arr;
	*arr = realloc(*arr, *len - sizeof(head) - data_len);
	//printf("PT MARI: %d\n", *len - sizeof(head) - data_len);
	*len = *len - sizeof(head) - data_len;

	return 1;
}

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

	printf("dedicatul: ");
	while (*(char *)data->data != '\0')
	{
		printf("%c", *(char *)data->data);
		data->data += sizeof(char);
	}
	data->data += sizeof(char);
	printf("\n");

	if (data->header->type == 1)
	{
		printf("suma1: %" PRId8 "\n", *(int8_t *)data->data);
		data->data += sizeof(int8_t);

		printf("suma2: %" PRId8 "\n", *(int8_t *)data->data);
		data->data += sizeof(int8_t);
	}

	if (data->header->type == 2)
	{
		printf("suma1: %" PRId16 "\n", *(int16_t *)data->data);
		data->data += sizeof(int16_t);

		printf("suma2: %" PRId32 "\n", *(int32_t *)data->data);
		data->data += sizeof(int32_t);
	}

	if (data->header->type == 3)
	{
		printf("suma1: %" PRId32 "\n", *(int32_t *)data->data);
		data->data += sizeof(int32_t);

		printf("suma2: %" PRId32 "\n", *(int32_t *)data->data);
		data->data += sizeof(int32_t);
	}

	data->data = ptr;
}

void add_new_data(data_structure *new_data, unsigned char type, char *dedicator, char *dedicatul)
{
	new_data->header = malloc(sizeof(head));

	new_data->header->type = type;

	if (type == 1)
	{
		int8_t suma1, suma2;
		scanf("%s%" SCNd8 "%" SCNd8 "%s", dedicator, &suma1, &suma2, dedicatul);

		new_data->header->len = (strlen(dedicator) + strlen(dedicatul) + 2) * sizeof(char) + 2 * sizeof(int8_t);
		new_data->data = malloc(new_data->header->len);

		void *ptr = new_data->data;

		memcpy(new_data->data, dedicator, strlen(dedicator) + 1);
		new_data->data += strlen(dedicator) + 1;

		memcpy(new_data->data, dedicatul, strlen(dedicatul) + 1);
		new_data->data += strlen(dedicatul) + 1;

		memcpy(new_data->data, &suma1, sizeof(int8_t));
		new_data->data += sizeof(int8_t);

		memcpy(new_data->data, &suma2, sizeof(int8_t));
		new_data->data += sizeof(int8_t);

		new_data->data = ptr;
	}
	else
	{
		if (type == 2)
		{
			int16_t suma1;
			int32_t suma2;
			scanf("%s%" SCNd16 "%" SCNd32 "%s", dedicator, &suma1, &suma2, dedicatul);

			new_data->header->len = (strlen(dedicator) + strlen(dedicatul) + 2) * sizeof(char) + sizeof(int16_t) + sizeof(int32_t);
			new_data->data = malloc(new_data->header->len);

			void *ptr = new_data->data;

			memcpy(new_data->data, dedicator, strlen(dedicator) + 1);
			new_data->data += strlen(dedicator) + 1;

			memcpy(new_data->data, dedicatul, strlen(dedicatul) + 1);
			new_data->data += strlen(dedicatul) + 1;

			memcpy(new_data->data, &suma1, sizeof(int16_t));
			new_data->data += sizeof(int16_t);

			memcpy(new_data->data, &suma2, sizeof(int32_t));
			new_data->data += sizeof(int32_t);

			new_data->data = ptr;
		}
		else
		{
				int32_t suma1, suma2;
				scanf("%s%" SCNd32 "%" SCNd32 "%s", dedicator, &suma1, &suma2, dedicatul);

				new_data->header->len = (strlen(dedicator) + strlen(dedicatul) + 2) * sizeof(char) + 2 * sizeof(int32_t);
				new_data->data = malloc(new_data->header->len);

				void *ptr = new_data->data;

				memcpy(new_data->data, dedicator, strlen(dedicator) + 1);
				new_data->data += strlen(dedicator) + 1;

				memcpy(new_data->data, dedicatul, strlen(dedicatul) + 1);
				new_data->data += strlen(dedicatul) + 1;

				memcpy(new_data->data, &suma1, sizeof(int32_t));
				new_data->data += sizeof(int32_t);

				memcpy(new_data->data, &suma2, sizeof(int32_t));
				new_data->data += sizeof(int32_t);

				new_data->data = ptr;
		}
	}
	// print_data(new_data);
}

int main()
{
	void *arr = NULL;
	int len = 0, exit = 0, ok;
	char command[257], dedicator[257] = "ion", dedicatul[257] = "maria";
	unsigned char type;

	while (exit == 0)
	{
		scanf("%s", command);

		if (strcmp(command, "insert") == 0)
		{
			scanf("%hhu", &type);
			data_structure *new_data = (data_structure *)malloc(sizeof(data_structure));
			add_new_data(new_data, type, dedicator, dedicatul);

			ok = add_last(&arr, &len, new_data);

			free(new_data->header);
			free(new_data->data);
			free(new_data);
		}

		if (strcmp(command, "insert_at") == 0)
		{
			int index;
			scanf("%d", &index);
			scanf("%hhu", &type);
			data_structure *new_data = (data_structure *)malloc(sizeof(data_structure));
			add_new_data(new_data, type, dedicator, dedicatul);

			ok = add_at(&arr, &len, new_data, index);

			free(new_data->header);
			free(new_data->data);
			free(new_data);
		}

		if (strcmp(command, "delete_at") == 0)
		{
			int index;
			scanf("%d", &index);
			ok = delete_at(&arr, &len, index);
		}

		if (strcmp(command, "find") == 0)
		{
			int index;
			scanf("%d", &index);
			find(arr, len, index);
		}

		if (strcmp(command, "print") == 0)
			print(arr, len);

		if (strcmp(command, "exit") == 0)
			exit = 1;
	}

	free(arr);

	return 0;
}
