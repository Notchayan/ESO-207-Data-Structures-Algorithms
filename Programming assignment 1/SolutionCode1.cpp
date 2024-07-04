#include<iostream>
using namespace std;

int main()
{
    int t;
    cin >> t;
    for(int i = 0; i < t; i++)
    {
        int len;
        cin >> len;
        long long data[len];
        for(int j = 0; j < len; j++) cin >> data[j];
        for(int j = len - 1; j >= 0; j--)
        {
            if(j != len - 1)
            {
                if(data[j + 1] > 0) data[j] += data[j + 1];
            }
        }
        for(int k = 0; k < len; k++) cout << data[k] << " ";
        cout << endl;
    }
}
