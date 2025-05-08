#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void dfs(vector<vector<int> > &g, int start, vector<int> &vis)
{
    vis[start] = 1;
    cout << start << " ";
    for (int i = 0; i < g[start].size(); i++)
    {
        int child = g[start][i];
        if (!vis[child])
        {
            dfs(g, child, vis);
        }
    }
}

void bfs(vector<vector<int> > &g, int start)
{
    vector<int> vis(g.size(), 0);
    queue<int> q;
    q.push(start);
    vis[start] = 1;

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        cout << cur << " ";

        for (int i = 0; i < g[cur].size(); i++)
        {
            int child = g[cur][i];
            if (!vis[child])
            {
                q.push(child);
                vis[child] = 1;
            }
        }
    }
}

int main()
{
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;
    vector<vector<int> > g(V);

    int E;
    cout << "Enter number of edges: ";
    cin >> E;
    for (int i = 0; i < E; i++)
    {
        int a, b;
        cout << "Enter edge " << i + 1 << " (format: u v): ";
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> vis(V, 0);
    cout << "DFS: ";
    dfs(g, 0, vis);
    cout << endl;

    cout << "BFS: ";
    bfs(g, 0);
    cout << endl;

    return 0;
}
