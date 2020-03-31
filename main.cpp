// Example program
#include <iostream>
#include <string>
#include "cuda.hpp"
#include "cpu.h"

#define M 8
#define N 4


using namespace std;

void print_matrix(short** input_matrix, int rows, int columns) {
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j) {
			printf(" %u", input_matrix[i][j]);
		}
		printf("\n");
	}

}
void print_linear_array(short* array, int rows, int columns) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j)
			printf("%d ", array[i*columns + j]);
		printf("\n");
	}
}

void copy_from_matrix_to_linear_array(short** src, short* dst, int rows, int columns) {
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < columns; ++j)
			dst[i * columns + j] = src[i][j];
}

bool check_for_equality(short** first, short* second, int rows, int columns) {
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < columns; ++j)
			if (first[i][j] != second[i*rows + j])
				return false;
	return true;
}

int main()
{
	short** A;
	short** B;
	short* A_linear;
	short* B_linear;

	A = allocate_matrix(N, M);
	B = allocate_matrix(N / 2, 2 * M);

	A_linear = (short*)malloc(N * M * sizeof(short));
	B_linear = (short*)malloc(N / 2 * M * 2 * sizeof(short));

	random_init(A, N, M);
	copy_from_matrix_to_linear_array(A, A_linear, N, M);

	replace_items(A, B, N, M);
	gpu(A_linear, B_linear, N, M);
	if (!check_for_equality(B, B_linear, N / 2, M * 2))
		printf("not equals\n");
	print_linear_array(A_linear, N, M);
	printf("********\n");
	print_linear_array(B_linear, N / 2, M * 2);

	printf("\n--------------------\n");

	print_matrix(A, N, M);
	printf("\n******\n");
	print_matrix(B, N / 2, M * 2);

	system("pause");

}
