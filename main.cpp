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

int main()
{
	short** A;
	short** B;

	A = allocate_matrix(N, M);
	B = allocate_matrix(N / 2, 2 * M);
	random_init(A, N, M);

	replace_items(A, B, N, M);

	print_matrix(A, N, M);
	printf("\n******\n");
	print_matrix(B, N / 2, M * 2);

	system("pause");

}
