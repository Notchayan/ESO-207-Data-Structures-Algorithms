#include<iostream>
#include<vector>

using namespace std;

void calculateMaxTreeHeight(vector<int>& heights, vector<int>& result, int left, int right, int currentHeight)
{
    if(left == right)
    {
        result[left] = currentHeight;
    }
    else
    {
        int maxHeight = heights[left];
        int maxIndex = left;
        for(int i = left; i <= right; i++)
        {
            if(heights[i] > maxHeight)
            {
                maxHeight = heights[i];
                maxIndex = i;
            }
        }
        if(maxIndex > left && maxIndex < right)
        {
            calculateMaxTreeHeight(heights, result, left, maxIndex - 1, currentHeight + 1);
            result[maxIndex] = currentHeight;
            calculateMaxTreeHeight(heights, result, maxIndex + 1, right, currentHeight + 1);
        }
        else if(maxIndex == left)
        {
            result[left] = currentHeight;
            calculateMaxTreeHeight(heights, result, maxIndex + 1, right, currentHeight + 1);
        }
        else if(maxIndex == right)
        {
            result[right] = currentHeight;
            calculateMaxTreeHeight(heights, result, left, maxIndex - 1, currentHeight + 1);
        }
    }
}

int main()
{
    int numTestCases;
    cin >> numTestCases;
    for(int i = 0; i < numTestCases; i++)
    {
        int size;
        cin >> size;
        vector<int> heights;
        for(int j = 0; j < size; j++)
        {
            int value;
            cin >> value;
            heights.push_back(value);
        }
        vector<int> result(size, 0);
        calculateMaxTreeHeight(heights, result, 0, size - 1, 0);
        for(int j = 0; j < size; j++)
        {
            cout << result[j] << " ";
        }
        cout << endl;
    }
}
