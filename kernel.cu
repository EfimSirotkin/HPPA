#include "cuda.hpp"

#define BLOCK_SIZE 32

#include <stdio.h>

__global__ void gpu_copy(const short *src, short *dst, const int N, const int M, const int src_pitch, const int dst_pitch)
{
    int i = blockIdx.y * blockDim.y + threadIdx.y;
    int j = blockIdx.x * blockDim.x + threadIdx.x;
    __shared__ short block_memory[BLOCK_SIZE][BLOCK_SIZE];
    if (i < N && j < M)
    {
        size_t src_offset = i * src_pitch + j;
        block_memory[threadIdx.y][threadIdx.x] = src[src_offset];
		__syncthreads();
		size_t dst_offset = i / 2 * dst_pitch + 2 * j;
		dst[dst_offset] = block_memory[threadIdx.y][threadIdx.x];
		__syncthreads();

		src_offset = (i + 1) * src_pitch + j;
		block_memory[threadIdx.y][threadIdx.x] = src[src_offset];
		__syncthreads();
		dst_offset = i / 2 * dst_pitch + 2 * (j + 1);
		dst[dst_offset] = block_memory[threadIdx.y][threadIdx.x];
		__syncthreads();


		src_offset = (i + 2) * src_pitch + j;
		block_memory[threadIdx.y][threadIdx.x] = src[src_offset];
		__syncthreads();
		dst_offset = (i + 1) / 2 * dst_pitch + 2 * j;
		dst[dst_offset] = block_memory[threadIdx.y][threadIdx.x];


		src_offset = (i + 3) * src_pitch + j;
		block_memory[threadIdx.y][threadIdx.x] = src[src_offset];
		__syncthreads();
		dst_offset = (i + 1) / 2 * dst_pitch + 2 * (j + 1);
		__syncthreads();
    }
}

#include <iomanip>
void gpu(short *src, short *dst, int N, int M)
{
    short *device_orig_matrix = nullptr;
    size_t orig_matrix_memory_pitch = -1;
    cudaMallocPitch((void **)&device_orig_matrix, &orig_matrix_memory_pitch, M * sizeof(short), N);

    short *device_dst_matrix = nullptr;
    size_t dst_matrix_memory_pitch = -1;
    cudaMallocPitch((void **)&device_dst_matrix, &dst_matrix_memory_pitch, 2 * M * sizeof(short), N / 2);

    cudaMemcpy2D(device_orig_matrix, orig_matrix_memory_pitch,
                 src, sizeof(short) * M,
                 sizeof(short) * M, N,
                 cudaMemcpyHostToDevice);

    dim3 block(BLOCK_SIZE, BLOCK_SIZE),
        grid((M + BLOCK_SIZE - 1) / BLOCK_SIZE, (N + BLOCK_SIZE - 1) / BLOCK_SIZE);

    gpu_copy<<<grid, block>>>(device_orig_matrix, device_dst_matrix, N, M, orig_matrix_memory_pitch / 2, dst_matrix_memory_pitch / 2); // WTF ??
    cudaDeviceSynchronize();

    cudaMemcpy2D(dst, sizeof(short) * M * 2,
                 device_dst_matrix, dst_matrix_memory_pitch,
                 2 * sizeof(short) * M, N / 2,
                 cudaMemcpyDeviceToHost);
    cudaFree(device_dst_matrix);
    cudaFree(device_orig_matrix);
}
