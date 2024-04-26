#include <iostream>
void addVectors(int *A, int *B, int *C, int n)
{
    for (int i = 0; i < n; i++)
    {
        C[i] = A[i] + B[i];
    }
}
int main()
{
    int n = 1000000;
    int *A, *B, *C;
    A = new int[n];
    B = new int[n];
    C = new int[n];
    for (int i = 0; i < n; i++)
    {
        A[i] = i;
        B[i] = i * 2;
    }
    addVectors(A, B, C, n);
    for (int i = 0; i < 10; i++)
    {
        std::cout << C[i] << " ";
    }
    std::cout << std::endl;
    delete[] A;
    delete[] B;
    delete[] C;
    return 0;
}

/*
without gpu
1. sudo apt install nvidia-cuda-toolkit
2. nvcc B190244310.cu -o B190244310
3. ./B190244310
*/
