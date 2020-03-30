#pragma once
#include <iostream>
#include <string>



void random_init(short** input_matrix, int rows, int columns);

void replace_items(short** input_matrix, short** output_matrix, int rows, int columns);

short** allocate_matrix(int rows, int columns);