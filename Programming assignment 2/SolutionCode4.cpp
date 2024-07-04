#include<iostream>
#include<vector>
#include<cstdlib>

using namespace std;

// Function to check if a given number of positive segments are allowed
int areSegmentsAllowed(vector< vector<int> >& segments, int s, vector<int>& arr, int n, int k)
{
    // Calculate prefix sums for array 'arr'
    int prefixSum[n];
    for(int j = n - 1; j >= 0; j--)
    {
        if(j == (n - 1)) prefixSum[j] = arr[j];
        else
        {
            prefixSum[j] = prefixSum[j + 1] + arr[j];
        }
    }
    
    int currentPositive = 0;
    for(int j = 0; j < s && currentPositive < k; j++)
    {
        int left = segments[j][0] - 1;  // Adjust index to 0-based
        int right = segments[j][1];     // Segment end index
        int sum;
        if(right <= n - 1) sum = prefixSum[left] - prefixSum[right];
        else sum = prefixSum[left];
        if(sum > 0) currentPositive++;
    }
    
    if(currentPositive >= k) return 1;
    else return 0;
}

// Function to find the minimum number of queries needed
int findMinQueries(vector<int>& arr, int n, vector<int>& queries, int q, vector< vector<int> >& segments, int s, int k)
{
    int low = 0;
    int high = q;
    
    while(low < high)
    {
        vector<int> modifiedArray = arr;
        int mid = (low + high) / 2;
        
        // Mark positions in 'arr' as 1 based on queries
        for(int j = 0; j < mid; j++)
        {
            modifiedArray[queries[j] - 1] = 1;  // Adjust index to 0-based
        }
        
        if(areSegmentsAllowed(segments, s, modifiedArray, n, k)) 
        {
            high = mid;
        }
        else 
        {
            low = mid + 1;
        }
    }
    
    if(low > high) return -1;
    else
    {
        vector<int> modifiedArray = arr;
        
        // Mark positions in 'arr' as 1 based on queries up to 'low'
        for(int j = 0; j < low; j++)
        {
            modifiedArray[queries[j] - 1] = 1;  // Adjust index to 0-based
        }
        
        // Check if 'low' queries are sufficient
        if(areSegmentsAllowed(segments, s, modifiedArray, n, k)) return low;
        else return -1;
    } 
}

int main()
{
    int numTestCases;
    cin >> numTestCases;
    
    for(int i = 0; i < numTestCases; i++)
    {
        int n, s;
        cin >> n >> s;
        
        // Read the array 'arr'
        vector<int> arr;
        for(int j = 0; j < n; j++)
        {
            int temp;
            cin >> temp;
            arr.push_back(temp);
        }
        
        // Read the segments
        vector<vector<int> > segments;
        for(int j = 0; j < s; j++)
        {
            int l, r;
            cin >> l >> r;
            vector<int> temp = {l, r};
            segments.push_back(temp);
        }
        
        int q, k;
        cin >> q >> k;
        
        // Read the queries
        vector<int> queries;
        for(int j = 0; j < q; j++)
        {
            int temp;
            cin >> temp;
            queries.push_back(temp);
        }
        
        // Find and print the minimum number of queries needed
        cout << findMinQueries(arr, n, queries, q, segments, s, k) << endl;
    }
    
    return 0;
}
