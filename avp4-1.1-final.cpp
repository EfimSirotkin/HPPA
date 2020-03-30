// Example program
#include <iostream>
#include <string>

#define M 16
#define N 4
#define GAP 2


using namespace std;

void random_init(short** input_matrix, int rows, int columns) {
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < columns; ++j) {
			input_matrix[i][j] = rand() % 10;
		}
}

void replace_items(short** input_matrix, short** output_matrix, int rows, int columns) {
	for (int i = 0; i < rows; i += 4)
		for (int j = 0; j < columns; ++j) {
			output_matrix[i / GAP][j * GAP] = input_matrix[i][j];
			output_matrix[i / GAP][j * GAP + 1] = input_matrix[i + 1][j];
			output_matrix[i / GAP + 1][j * GAP] = input_matrix[i + 2][j];
			output_matrix[i / GAP + 1][j * GAP + 1] = input_matrix[i + 3][j];
		}
}

void print_matrix(short** input_matrix, int rows, int columns) {
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j) {
			printf(" %u", input_matrix[i][j]);
		}
		printf("\n");
	}

}

short** allocate_matrix(int rows, int columns) {
	short** temp_matrix = (short**)malloc(rows * sizeof(short*));

	for (int i = 0; i < rows; ++i)
		temp_matrix[i] = (short*)malloc(columns * sizeof(short));

	return temp_matrix;
}

int main()
{
	short** A;
	short** B;

	A = allocate_matrix(M, N);
	B = allocate_matrix(M / 2, 2 * N);
	random_init(A, M, N);
	
	replace_items(A, B, M, N);

	print_matrix(A, M, N);
	print_matrix(B, M / 2, N * 2);

	system("pause");

}
