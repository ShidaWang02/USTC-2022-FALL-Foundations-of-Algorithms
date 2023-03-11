#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

enum Colour //颜色
{
    RED,
    BLACK,
};

typedef struct Interval //区间
{
    int low;
    int high;
} interval;

typedef struct node
{
    Colour color;
    interval inter;
    int key;
    int max;
    struct node *left, *right, *p;
} RBNode, *pRBNode;

typedef struct nodeTree
{
    pRBNode root, NIL;
} RBTree, *pRBTree;

void RBTInit(pRBTree T)
{
    if (T == NULL)
    {
        return;
    }
    T->NIL = new RBNode;
    T->NIL->color = BLACK;
    T->NIL->max = INT32_MIN; // 将NIL结点的max值设为负无穷，即可省去很多判断
    T->root = T->NIL;
    T->root->p = T->NIL;
    return;
}

void LeftRotate(pRBTree T, pRBNode x)
{
    pRBNode y;
    y = x->right;
    x->right = y->left;
    if (y->left != T->NIL)
    {
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == T->NIL)
    {
        T->root = y;
    }
    else if (x == x->p->left)
    {
        x->p->left = y;
    }
    else
    {
        x->p->right = y;
    }
    y->left = x;
    x->p = y;
    x->max = max(max(x->left->max, x->right->max), x->inter.high);    // x->max 按照公式更新
    x->p->max = max(max(x->max, x->p->right->max), x->p->inter.high); // y->max 按照公式更新
    return;
}

void RightRotate(pRBTree T, pRBNode x)
{
    pRBNode y;
    y = x->left;
    x->left = y->right;
    if (y->right != T->NIL)
    {
        y->right->p = x;
    }
    y->p = x->p;
    if (x->p == T->NIL)
    {
        T->root = y;
    }
    else if (x == x->p->left)
    {
        x->p->left = y;
    }
    else
    {
        x->p->right = y;
    }
    y->right = x;
    x->p = y;
    x->max = max(max(x->left->max, x->right->max), x->inter.high);   // x->max 按照公式更新
    x->p->max = max(max(x->max, x->p->left->max), x->p->inter.high); // y->max 按照公式更新
    return;
}

// 自底向上更新max值
void FixMax(pRBTree T, pRBNode z)
{
    pRBNode x = z;
    while (x != T->NIL)
    {
        x->max = max(max(x->left->max, x->right->max), x->inter.high); // 更新max
        x = x->p;                                                      // 向上移动
    }
    return;
}

void RBInsertFixup(pRBTree T, pRBNode z)
{
    pRBNode y;
    while (z->p->color == RED)
    {
        if (z->p == z->p->p->left)
        {
            y = z->p->p->right;
            if (y->color == RED)
            {
                z->p->color = BLACK;  // case1
                y->color = BLACK;     // case1
                z->p->p->color = RED; // case1
                z = z->p->p;          // case1
            }
            else
            {
                if (z == z->p->right)
                {
                    z = z->p;         // case2
                    LeftRotate(T, z); // case2
                }
                z->p->color = BLACK;     // case3
                z->p->p->color = RED;    // case3
                RightRotate(T, z->p->p); // case3
            }
        }
        else
        {
            y = z->p->p->left;
            if (y->color == RED)
            {
                z->p->color = BLACK;  // case4
                y->color = BLACK;     // case4
                z->p->p->color = RED; // case4
                z = z->p->p;          // case4
            }
            else
            {
                if (z == z->p->left)
                {
                    z = z->p;          // case5
                    RightRotate(T, z); // case5
                }
                z->p->color = BLACK;    // case6
                z->p->p->color = RED;   // case6
                LeftRotate(T, z->p->p); // case6
            }
        }
    }
    T->root->color = BLACK;
    return;
}

void RBInsert(pRBTree T, pRBNode z)
{
    pRBNode y = T->NIL;
    pRBNode x = T->root;
    while (x != T->NIL)
    {
        y = x;
        if (z->key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    z->p = y; // 插入根结点时让根节点父节点指向NIL
    if (y == T->NIL)
    {
        T->root = z;
    }
    else if (z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    z->left = T->NIL;
    z->right = T->NIL;
    z->color = RED;
    FixMax(T, z); // 每次插入结束自底向上更新一次max值
    RBInsertFixup(T, z);
    return;
}

// 判断区间是否重叠
int overlap(interval x, interval y)
{
    if (x.high < y.low || x.low > y.high)
    {
        return 0;
    }
    return 1;
}

// 重叠区间的查找算法
pRBNode IntervalSearch(pRBTree T, interval i)
{
    pRBNode x = T->root;
    while (x != T->NIL && !overlap(i, x->inter))
    {
        if (x->left != T->NIL && x->left->max >= i.low)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    return x;
}

void InOrder(pRBTree T, pRBNode t, ofstream &outfile)
{

    if (t == T->NIL)
    {
        return;
    }
    InOrder(T, t->left, outfile);
    outfile << "[" << t->inter.low << "," << t->inter.high << "]"
            << " ";
    if (t->color == RED)
    {
        outfile << "red" << endl;
    }
    else
    {
        outfile << "black" << endl;
    }
    InOrder(T, t->right, outfile);
    return;
}

int main()
{
    int num, i = 0, j = 0;
    ifstream infile("insert.txt", ios_base::in);
    if (!infile)
    {
        cout << "文件不存在!";
        return 0;
    }
    infile >> num;
    int key[num];
    int high[num];
    for (i = 0; i < 2 * num; i++)
    {
        if (i % 2 == 0)
        {
            infile >> key[j];
        }
        else
        {
            infile >> high[j];
            j++;
        }
    }
    pRBTree T = new RBTree;
    RBTInit(T);
    for (int i = 0; i < num; i++)
    {
        pRBNode z = new RBNode;
        z->key = key[i];
        z->inter.low = key[i];
        z->inter.high = high[i];
        z->max = high[i];
        z->color = RED;
        RBInsert(T, z);
    }
    ofstream outfile("LNR.txt", ios_base::out);
    InOrder(T, T->root, outfile);
    pRBNode result;
    interval goal;
    while (true)
    {
        cout << "请输入要查找的区间：" << endl;
        cin >> goal.low >> goal.high;
        if (goal.high < goal.low)
        {
            cout << "区间左端点不能大于右端点！";
            return 0;
        }

        result = IntervalSearch(T, goal);
        if (result == T->NIL)
        {
            cout << "区间树内没有重叠区间！" << endl;
            continue;
        }

        cout << "[" << result->inter.low << "," << result->inter.high << "]" << endl;
    }

    return 0;
}