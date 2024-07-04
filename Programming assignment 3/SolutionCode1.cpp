#include<iostream>
#include<vector>
#include<string>

using namespace std;

int queue[100000];
int front;
int rear;
int num;

void newqueue()
{
    num=0;
    front=0;
    rear=0;
}

void enqueue(int x)
{
    if(num==100000) return;
    queue[rear]=x;
    rear=(rear+1)%100000;
    num++;
}

int dequeue()
{
    int x=queue[front];
    front=(front+1)%100000;
    num--;
    return x;
}

int BFSsecond(vector<vector <int> >& edges,vector<int>& visited,vector<int>& distance,int n, int m,int vertex)
{
    newqueue();
    enqueue(vertex);
    while(num!=0)
    {
        int p=dequeue();
        int m=edges[p][0];
        for(int i=1;i<=m;i++)
        {
            int neighbour=edges[p][i];
            if(!visited[neighbour])
            {
                visited[neighbour]=1;
                distance[neighbour]=distance[p]+1;
                enqueue(neighbour);
            }
            else if(visited[neighbour])
            {
                if(distance[neighbour]==distance[p]) return 0;
            }
        }
    }
    return 1;
}

int BFS(vector<vector <int> >& edges,vector<int>& visited,vector<int>& distance,int n, int m)
{
    for(int i=1;i<n+1;i++)
    {
        if(!visited[i])
        {
            visited[i]=1;
            distance[i]=1;
            if(!BFSsecond(edges,visited,distance,n,m,i)) return 0;
        }
    }
    return 1;
}

int main()
{
    int n,m;
    cin>>n>>m;
    vector<vector <int> > edges;
    for(int i=0;i<n+1;i++)
    {
        vector<int> temp;
        temp.push_back(0);
        edges.push_back(temp);
    }
    for(int i=0;i<m;i++)
    {
        int p,q;
        cin>>p>>q;
        edges[p][0]++;
        edges[q][0]++;
        edges[p].push_back(q);
        edges[q].push_back(p);
    }
    vector<int> visited;
    vector<int> distance;
    for(int i=0;i<n+1;i++)
    {
        visited.push_back(0);
        distance.push_back(0);
    }
    if(BFS(edges,visited,distance,n,m))
    {
        cout<<"YES"<<endl;
        for(int i=1;i<=n;i++) cout<<distance[i]%2+1<<" ";
    }
    else cout<<"NO"<<endl;
}