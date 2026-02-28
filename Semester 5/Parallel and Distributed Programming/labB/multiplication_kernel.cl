__kernel void naive_poly_mul(__global const long *A, __global const long *B,
                             __global long *Result, int n, int m) {
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