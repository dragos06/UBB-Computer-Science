#define CL_TARGET_OPENCL_VERSION 300

#include "OpenCLMultiplication.h"
#include <CL/cl.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

cl_context g_context = NULL;
cl_command_queue g_queue = NULL;
cl_program g_program = NULL;
cl_kernel g_kernel = NULL;
cl_device_id g_device = NULL;
bool g_isInitialized = false;

void checkErr(cl_int err, const char *name)
{
    if (err != CL_SUCCESS)
    {
        std::cerr << "ERROR: " << name << " (" << err << ")" << std::endl;
        exit(EXIT_FAILURE);
    }
}

std::string loadKernelSource(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        return R"(
            __kernel void naive_poly_mul(__global const long* A, __global const long* B, __global long* Result, int n, int m) {
                int k = get_global_id(0);
                int resultSize = n + m - 1;
                if (k < resultSize) {
                    long sum = 0;
                    int start_i = (k >= m) ? (k - m + 1) : 0;
                    int end_i = (k < n) ? k : (n - 1);
                    for (int i = start_i; i <= end_i; ++i) {
                        sum += A[i] * B[k - i];
                    }
                    Result[k] = sum;
                }
            }
        )";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void initOpenCL()
{
    if (g_isInitialized)
        return;

    cl_int err;
    cl_uint num_platforms;

    err = clGetPlatformIDs(0, NULL, &num_platforms);
    checkErr(err, "clGetPlatformIDs (count)");

    if (num_platforms == 0)
    {
        std::cerr << "ERROR: No OpenCL platforms found." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<cl_platform_id> platforms(num_platforms);
    err = clGetPlatformIDs(num_platforms, platforms.data(), NULL);
    checkErr(err, "clGetPlatformIDs (fetch)");

    bool gpuFound = false;
    for (const auto &plat : platforms)
    {
        cl_uint num_devices;
        err = clGetDeviceIDs(plat, CL_DEVICE_TYPE_GPU, 1, &g_device, &num_devices);

        if (err == CL_SUCCESS)
        {
            std::cout << "Found GPU on platform." << std::endl;
            gpuFound = true;
            break;
        }
    }

    if (!gpuFound)
    {
        std::cerr << "WARNING: No GPU found on any platform. Falling back to CPU." << std::endl;
        err = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_CPU, 1, &g_device, NULL);
        checkErr(err, "clGetDeviceIDs (CPU Fallback)");
    }

    g_context = clCreateContext(NULL, 1, &g_device, NULL, NULL, &err);
    checkErr(err, "clCreateContext");

    g_queue = clCreateCommandQueueWithProperties(g_context, g_device, 0, &err);
    checkErr(err, "clCreateCommandQueueWithProperties");

    std::string sourceStr = loadKernelSource("multiplication_kernel.cl");
    const char *sourceCStr = sourceStr.c_str();
    g_program = clCreateProgramWithSource(g_context, 1, &sourceCStr, NULL, &err);
    checkErr(err, "clCreateProgramWithSource");

    err = clBuildProgram(g_program, 1, &g_device, NULL, NULL, NULL);
    if (err != CL_SUCCESS)
    {
        size_t len;
        clGetProgramBuildInfo(g_program, g_device, CL_PROGRAM_BUILD_LOG, 0, NULL, &len);
        std::vector<char> log(len);
        clGetProgramBuildInfo(g_program, g_device, CL_PROGRAM_BUILD_LOG, len, log.data(), NULL);
        std::cerr << "Build Log: " << log.data() << std::endl;
        exit(1);
    }

    g_kernel = clCreateKernel(g_program, "naive_poly_mul", &err);
    checkErr(err, "clCreateKernel");

    g_isInitialized = true;

    char deviceName[128];
    clGetDeviceInfo(g_device, CL_DEVICE_NAME, 128, deviceName, NULL);
    std::cout << "OpenCL Initialized on device: " << deviceName << std::endl;
}

void cleanupOpenCL()
{
    if (g_kernel)
        clReleaseKernel(g_kernel);
    if (g_program)
        clReleaseProgram(g_program);
    if (g_queue)
        clReleaseCommandQueue(g_queue);
    if (g_context)
        clReleaseContext(g_context);
    g_isInitialized = false;
}

Polynomial multiplyOpenCLNaive(const Polynomial &A, const Polynomial &B)
{
    if (!g_isInitialized)
        initOpenCL();
    if (A.empty() || B.empty())
        return {};

    size_t n = A.size();
    size_t m = B.size();
    size_t resultSize = n + m - 1;
    Polynomial result(resultSize, 0);
    cl_int err;

    cl_mem bufferA = clCreateBuffer(g_context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(long long) * n, (void *)A.data(), &err);
    cl_mem bufferB = clCreateBuffer(g_context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(long long) * m, (void *)B.data(), &err);
    cl_mem bufferRes = clCreateBuffer(g_context, CL_MEM_WRITE_ONLY, sizeof(long long) * resultSize, NULL, &err);

    int n_int = (int)n;
    int m_int = (int)m;
    err = clSetKernelArg(g_kernel, 0, sizeof(cl_mem), &bufferA);
    err |= clSetKernelArg(g_kernel, 1, sizeof(cl_mem), &bufferB);
    err |= clSetKernelArg(g_kernel, 2, sizeof(cl_mem), &bufferRes);
    err |= clSetKernelArg(g_kernel, 3, sizeof(int), &n_int);
    err |= clSetKernelArg(g_kernel, 4, sizeof(int), &m_int);
    checkErr(err, "clSetKernelArg");

    size_t globalWorkSize = resultSize;
    err = clEnqueueNDRangeKernel(g_queue, g_kernel, 1, NULL, &globalWorkSize, NULL, 0, NULL, NULL);
    checkErr(err, "clEnqueueNDRangeKernel");

    err = clEnqueueReadBuffer(g_queue, bufferRes, CL_TRUE, 0, sizeof(long long) * resultSize, result.data(), 0, NULL, NULL);
    checkErr(err, "clEnqueueReadBuffer");

    clReleaseMemObject(bufferA);
    clReleaseMemObject(bufferB);
    clReleaseMemObject(bufferRes);

    return result;
}

Polynomial multiplyOpenCLKaratsuba(const Polynomial &A, const Polynomial &B)
{
    size_t n = A.size();

    if (n <= 2048)
    {
        return multiplyOpenCLNaive(A, B);
    }

    size_t k = n / 2;

    Polynomial A0(A.begin(), A.begin() + k);
    Polynomial A1(A.begin() + k, A.end());
    Polynomial B0(B.begin(), B.begin() + k);
    Polynomial B1(B.begin() + k, B.end());

    Polynomial A0B0 = multiplyOpenCLKaratsuba(A0, B0);
    Polynomial A1B1 = multiplyOpenCLKaratsuba(A1, B1);

    Polynomial sumA;
    addPoly(sumA, A0, A1);
    Polynomial sumB;
    addPoly(sumB, B0, B1);

    Polynomial Mid = multiplyOpenCLKaratsuba(sumA, sumB);

    Polynomial result(2 * n - 1, 0);

    for (size_t i = 0; i < A0B0.size(); ++i)
        result[i] += A0B0[i];

    for (size_t i = 0; i < A1B1.size(); ++i)
    {
        if (i + 2 * k < result.size())
            result[i + 2 * k] += A1B1[i];
        else
            result.push_back(A1B1[i]);
    }

    for (size_t i = 0; i < Mid.size(); ++i)
    {
        long long val = Mid[i];
        if (i < A0B0.size())
            val -= A0B0[i];
        if (i < A1B1.size())
            val -= A1B1[i];

        if (i + k < result.size())
            result[i + k] += val;
        else
            result.push_back(val);
    }

    return result;
}