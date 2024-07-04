#include<iostream>
using namespace std;

int maxFace;
long long powerOf2(int exp)
{
    if(exp == 0) return 1;
    else return 2 * powerOf2(exp - 1);
}

long long** multiplyMatrices(long long** mat)
{
    long long** result = new long long*[maxFace];
    for(int i = 0; i < maxFace; i++) result[i] = new long long[maxFace];
    for(int i = 0; i < maxFace; i++)
    {
        for(int j = 0; j < maxFace; j++)
        {
            result[i][j] = 0;
            for(int p = 0; p < maxFace; p++)
            {
                result[i][j] += (mat[i][p] * mat[p][j]);
                result[i][j] %= 998244353;
            }
        }
    }
    return result;
}

long long** multiplyMatrixWithColumn(long long** mat1, long long** mat2)
{
    long long** result = new long long*[maxFace];
    for(int i = 0; i < maxFace; i++) result[i] = new long long;
    for(int i = 0; i < maxFace; i++)
    {
        result[i][0] = 0;
        for(int j = 0; j < maxFace; j++)
        {
            result[i][0] += (mat1[i][j] * mat2[j][0]);
            result[i][0] %= 998244353;
        }
    }
    return result;
}

long long** multiplySquareMatrices(long long** mat1, long long** mat2)
{
    long long** result = new long long*[maxFace];
    for(int i = 0; i < maxFace; i++) result[i] = new long long[maxFace];
    for(int i = 0; i < maxFace; i++)
    {
        for(int j = 0; j < maxFace; j++)
        {
            result[i][j] = 0;
            for(int p = 0; p < maxFace; p++)
            {
                result[i][j] += (mat1[i][p] * mat2[p][j]);
                result[i][j] %= 998244353;
            }
        }
    }
    return result;
}

long long** powerMatrix(long long** mat, long long exp)
{
    if(exp == 1) return mat;
    else
    {
        long long** result = new long long*[maxFace];
        for(int i = 0; i < maxFace; i++) result[i] = new long long[maxFace];
        result = multiplyMatrices(powerMatrix(mat, exp / 2));
        if(exp % 2 == 1) result = multiplySquareMatrices(result, mat);
        return result;
    }
}

long long compute(long long num)
{
    long long** mat = new long long*[maxFace];
    for(int i = 0; i < maxFace; i++)
    {
        mat[i] = new long long[maxFace];
        for(int j = 0; j < maxFace; j++)
        {
            if(i == 0) mat[i][j] = 1;
            else if(i - j == 1) mat[i][j] = 1;
            else mat[i][j] = 0;
        }
    }
    long long** init = new long long*[maxFace];
    for(int i = 0; i < maxFace; i++)
    {
        init[i] = new long long;
        init[i][0] = powerOf2(maxFace - i - 1);
    }
    
    long long** result = new long long*[maxFace];
    for(int i = 0; i < maxFace; i++) result[i] = new long long[maxFace];
    result = powerMatrix(mat, num - maxFace);
    init = multiplyMatrixWithColumn(result, init);
    return init[0][0];
}

int main()
{
    int testCases;
    cin >> testCases;
    for(int i = 0; i < testCases; i++)
    {
        long long sum;
        cin >> sum;
        cin >> maxFace;
        if(sum > maxFace) cout << compute(sum) << endl;
        else if(sum >= 1) cout << powerOf2(sum - 1) << endl;
        else cout << "0" << endl;
    }
}
