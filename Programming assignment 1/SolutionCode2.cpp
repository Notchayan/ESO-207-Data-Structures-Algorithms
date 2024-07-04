#include<iostream>
using namespace std;

void merge(long long data[], int start, int leftSize, int rightSize)
{
    long long left[leftSize];
    long long right[rightSize];
    for (int i = 0; i < leftSize + rightSize; i++) 
    {
        if (i < leftSize) left[i] = data[start + i];
        else right[i - leftSize] = data[start + i];
    }
    int i = 0;
    int j = 0;
    int k = start;
    while (i != leftSize && j != rightSize) 
    {
        if (left[i] <= right[j]) 
        {
            data[k] = left[i];
            i++;
            k++;
        } 
        else 
        {
            data[k] = right[j];
            j++;
            k++;
        }
    }
    while (i < leftSize) 
    {
        data[k] = left[i];
        i++;
        k++;
    }
    while (j < rightSize) 
    {
        data[k] = right[j];
        j++;
        k++;
    }
}

void mergesort(long long arr[], int start, int end)
{
    if (start == end) return;
    else
    {
        int mid = (start + end) / 2;
        mergesort(arr, start, mid);
        mergesort(arr, mid + 1, end);
        merge(arr, start, mid - start + 1, end - mid);
    }
}

int isAllowed(long long data[], int size, long long maxCost, long long height)
{
    int i = size - 1;
    long long cost = 0;
    while (cost <= maxCost && i >= 0)
    {
        cost += ((data[i] * (data[i] + 1)) / 2 - (height * (height + 1)) / 2);
        i--;
    }
    if (cost > maxCost) i++;
    if (i == -1 || data[i] <= height) return 1;
    else return 0;
}

long long findHeight(long long arr[], long long minHeight, long long maxHeight, long long maxCost, int size)
{
    if (minHeight == maxHeight) return maxHeight;
    else
    {
        long long mid = (minHeight + maxHeight) / 2;
        if (isAllowed(arr, size, maxCost, mid)) return findHeight(arr, minHeight, mid, maxCost, size);
        else return findHeight(arr, mid + 1, maxHeight, maxCost, size);
    }
}

int main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {  
        int num;
        long long maxCost;
        cin >> num;
        cin >> maxCost;
        long long data[num];
        for (int i = 0; i < num; i++)
        {
            cin >> data[i];
        }
        mergesort(data, 0, num - 1);
        cout << findHeight(data, 0, data[num - 1], maxCost, num) << endl;
    }
}
