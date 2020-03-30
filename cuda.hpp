#include "cuda_runtime.h"
#include "device_launch_parameters.h"

__global__ void gpu_copy(const int *src, int *dst, const int N, const int M, const int src_pitch, const int dst_pitch);

void gpu(int *src, int *dst, int N, int M);