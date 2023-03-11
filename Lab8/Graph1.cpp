#include <bits/stdc++.h>

using namespace std;


//边上权类型
typedef int EdgeType;

//最大顶点数
#define MaxVEX 100

// 颜色
enum Color
{
    White,
    Black,
    Grey
};

//邻接矩阵
typedef struct MGraph
{
    //顶点表
    Color vex[MaxVEX];
    //邻接矩阵，边表
    EdgeType edge[MaxVEX][MaxVEX];

    //图中当前的顶点数和边数
    int numVertexes, numEdges;
} MGraph;

MGraph G;


void BFS(int v)
{
    if (G.vex[v] != White)
    {
        return;
    }
    queue<int> q;
    q.push(v);
    G.vex[v] = Grey;
    while (!q.empty())
    {
        int temp = q.front();
        q.pop();
        cout << temp + 1 << "   ";
        for (int i = 0; i < G.numVertexes; i++)
        {
            if ((G.edge[temp][i] == 1) && (G.vex[i] == White))
            {
                q.push(i);
                G.vex[i] = Grey;
            }
        }
        G.vex[temp] = Black;
    }
    return;
}


int main()
{
    int p, q;
    int numEdges = 0, numVertexes = 0;
    string str;
    set<string> s;
    ifstream infile("data.txt", ios_base::in);
    while (infile >> str)
    {
        s.insert(str);
        numEdges++;
    }
    infile.close();
    infile.clear(ios::goodbit);  // 恢复流的状态
    numEdges /= 2;
    numVertexes = s.size();
    G.numEdges = numEdges;
    G.numVertexes = numVertexes;
    for (int i = 0; i < G.numVertexes; i++) {
        G.vex[i] = White;       // 结点颜色初始化
        for (int j = 0; j < G.numVertexes; j++) {
            //邻接矩阵初始化
            G.edge[i][j] = 0;
        }
    }
    infile.open("data.txt", ios_base::in);
    for (int i = 0; i < G.numEdges; i++)
    {
        infile >> p;
        infile >> q;
        G.edge[p - 1][q - 1] = 1;
        G.edge[q - 1][p - 1] = 1;
    }
    // for (int i = 0; i < G.numVertexes; i++)
    // {
    //     for (int j = 0; j < G.numVertexes; j++)
    //     {
    //         printf("%4d", G.edge[i][j]);
    //     }
    //     printf("\n");
    // }
    for (int i = 0; i < G.numVertexes; i++)
    {
        BFS(i);
    }
    return 0;
}
