#include <iostream>
void matmul(int *A, int *B, int *C, int N)
{
    for (int Row = 0; Row < N; Row++)
    {
        for (int Col = 0; Col < N; Col++)
        {
            int Pvalue = 0;
            for (int k = 0; k < N; k++)
            {
                Pvalue += A[Row * N + k] * B[k * N + Col];
            }
            C[Row * N + Col] = Pvalue;
        }
    }
}
int main()
{
    int N;
    std::cout<<"\nEnter number of rows: ";
    std::cin>>N;
    int size = N * N * sizeof(int);
    int *A, *B, *C;
    A = new int[N];
    B = new int[N];
    C = new int[N];
    // Initialize matrices A and B
    std::cout<<"\nEnter elements in matrix 1: ";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            std::cin>>A[i * N + j];
            B[i * N + j] = j * N + i;
        }
    }
    std::cout<<"\nEnter elements in matrix 2: ";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            std::cin>>B[i * N + j];
        }
    }
    // Perform matrix multiplication
    matmul(A, B, C, N);
    // Print the result (just printing the first 10x10 elements)
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            std::cout << C[i * N + j] << " ";
        }
        std::cout << std::endl;
    }
    // Free memory
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
