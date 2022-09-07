#include <iostream>
//https://www.techiedelight.com/dynamic-memory-allocation-in-c-for-2d-3d-array/
int main()
{
    int N = 0; int M = 0; int L = 0;
    std::cout<<"Dimension N: " << std::endl;
    std::cin >> N;
    std::cout<<"Dimension M: " << std::endl;
    std::cin >> M;
    std::cout<<"Dimension L: " << std::endl;
    std::cin >> L;
    int* A = new int[N * M * L];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < L; k++) {
                *(A + i*M*L + j*L + k) = rand();
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < L; k++) {
                std::cout << *(A + i*M*L + j*L + k) << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    return 0;
}
