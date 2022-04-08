#include <iostream>
#include <algorithm>
using namespace std;
struct Node
{
    int s, e, l;
};
Node *nodes;
int n, m;
// 递归算法
int run(int t, int tt)
{
    int a = 0, b;
    for (int i = 0; i < n; i++)
    {
        if (nodes[i].s >= t && nodes[i].e <= tt)
        {
            b = run(nodes[i].e, tt);
            b++;
            if (b > a)
                a = b;
        }
    }
    return a;
}
bool cmp(Node a, Node b)
{
    if (a.s == b.s)
        return a.e < b.e;
    return a.s < b.s;
}
int main()
{
    int t, tt, c;
    cin >> n >> m;
    nodes = new Node[2 * n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &t, &tt);
        nodes[i].s = t;
        nodes[i].e = tt;
    }
    sort(nodes, nodes + n, cmp);
    while (m--)
    {
        cin >> t >> tt;
        cout << run(t, tt) << endl;
    }
}