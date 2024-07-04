#include<iostream>
#include<cstdlib>
#include<vector>

using namespace std;

long long mergeAndCount(vector<long long>& data, int start, int end)
{
    int left = start;
    int mid = (start + end) / 2;
    int right = mid + 1;
    vector<long long> temp;
    long long invCount = 0;
    while(left <= mid && right <= end)
    {
        if(data[left] <= data[right])
        {
            temp.push_back(data[left]);
            left++;
        }
        else
        {
            temp.push_back(data[right]);
            right++;
            invCount += (mid - left + 1);
        }
    }
    while(left <= mid)
    {
        temp.push_back(data[left]);
        left++;
    }
    while(right <= end)
    {
        temp.push_back(data[right]);
        right++;
    }
    for(int i = start, j = 0; i <= end; i++, j++)
    {
        data[i] = temp[j];
    }
    return invCount;
}

long long countInversions(vector<long long>& data, int start, int end)
{
    if(start == end) return 0;
    else
    {
        int mid = (start + end) / 2;
        long long leftInv = countInversions(data, start, mid);
        long long rightInv = countInversions(data, mid + 1, end);
        long long mergeInv = mergeAndCount(data, start, end);
        return leftInv + rightInv + mergeInv;
    }
}

int main()
{
    int testCases;
    cin >> testCases;
    for(int i = 0; i < testCases; i++)
    {
        int size;
        cin >> size;
        vector<long long> data;
        for(int j = 0; j < size; j++)
        {
            long long value;
            cin >> value;
            data.push_back(value);
        }
        cout << countInversions(data, 0, size - 1) << endl;
    }
}
