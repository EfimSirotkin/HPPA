#include "cpu.h"
#define GAP 2

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

short** allocate_matrix(int rows, int columns) {
	short** temp_matrix = (short**)malloc(rows * sizeof(short*));

	for (int i = 0; i < rows; ++i)
		temp_matrix[i] = (short*)malloc(columns * sizeof(short));

	return temp_matrix;
}
