#include "../include/MyAdjMat.h"

template <typename T, T diag_default_value>
MyAdjMat<T, diag_default_value>::MyAdjMat(int sideLength)
{
    this->sideLength = sideLength;
    memory = new Ptrlevel1[sideLength];

    // 为了节省空间和避免对称元不同带来的逻辑错误，我们只生成矩阵的下三角部分
    for (int i = 0; i < sideLength; i++)
    {
        memory[i] = new T[i + 1]; // 注意这里的逻辑
        // 在通过循环生成矩阵的同时，自动将主对角元设置为主对角元默认值
        memory[i][i] = diag_default_value;
    }
}

template <typename T, T diag_default_value>
MyAdjMat<T, diag_default_value>::~MyAdjMat()
{
    for (int i = 0; i < sideLength; i++)
    {
        delete[] memory[i];
    }
    delete[] memory;
}

// template <typename T, T diag_default_value>
// MyAdjMat<T, diag_default_value>::