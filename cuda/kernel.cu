
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <iostream>

void printGPUInfo()
{
	int device;
	cudaGetDevice(&device);

	cudaDeviceProp prop;
	cudaGetDeviceProperties(&prop, device);

	std::cout << "GPU Name: " << prop.name << "\n";
	std::cout << "Total SMs: " << prop.multiProcessorCount << "\n";
	std::cout << "Max threads per SM: " << prop.maxThreadsPerMultiProcessor << "\n";
	std::cout << "Max threads per block: " << prop.maxThreadsPerBlock << "\n";
	std::cout << "Warp size: " << prop.warpSize << "\n";
	std::cout << "Registers per SM: " << prop.regsPerMultiprocessor << "\n";
	std::cout << "Shared memory per SM (bytes): " << prop.sharedMemPerMultiprocessor << "\n";
	std::cout << "Shared memory per block (bytes): " << prop.sharedMemPerBlock << "\n";
}

// Kernel function that runs on the GPU
__global__ void helloFromGPU() {
// threadIdx.x: thread index within the current block
// blockIdx.x: block index within the grid
    int tid = threadIdx.x;
    int bid = blockIdx.x;
    printf("Hello World from Block %d, Thread %d\n", bid, tid);
}

__global__ void vectorAddKernel(float* a, float* b, float* c)
{
    int idx = threadIdx.x;
    // each thread adds one element
    c[idx] = a[idx] + b[idx];
}

__global__ void vectorAddKernel(float* a, float* b, float* c, unsigned int size)
{
    // threadIdx.x: thread index within the current block
    // blockIdx.x: block index within the grid
    // blockDim.x: size of block
    int idx = (blockDim.x * blockIdx.x) + threadIdx.x;
    // check size so not to go over
    if (idx < size) c[idx] = a[idx] + b[idx];
}


int main() {
    // <<< #blocks, #threads>>>
    // dictates number of threads launched

    int size = 1 << 8; // 256 elements
    float *ha = new float[size]; // host arrays
    float *hb = new float[size];
    float *hc = new float[size];

    for (int i = 0; i < size; i++) {
        ha[i] = static_cast<float>(i);
        hb[i] = static_cast<float>(i * 2);
    }

    float *da, *db, *dc; // device arrays

    // allocate device memory
    cudaMalloc(&da, size * sizeof(float));
    cudaMalloc(&db, size * sizeof(float));
    cudaMalloc(&dc, size * sizeof(float));

    // Copy data from host to device
    cudaMemcpy(da, ha, size * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(db, hb, size * sizeof(float), cudaMemcpyHostToDevice);
    //cudaMemcpy(dc, hc, size * sizeof(float), cudaMemcpyHostToDevice);

    // Launch kernel with 1 block of 'size' threads
    // still launch kernel 1 thread per element but use blocks
    unsigned int threads = 256;
    int blocks = (size + threads - 1) / threads;
    std::cout << "Blocks: " << blocks << std::endl;
    vectorAddKernel <<<blocks, threads>>> (da, db, dc, size);
    cudaDeviceSynchronize();

    // CUDA error checking
    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess) {
        std::cout << "CUDA Error: " << cudaGetErrorString(err) << std::endl;
    }

    // Copy result back to host
    cudaMemcpy(hc, dc, size * sizeof(float), cudaMemcpyDeviceToHost);

    // print result
    for (int i = 0; i < size; i++) {
        std::cout << hc[i] << " ";
    }

    return 0;
}
