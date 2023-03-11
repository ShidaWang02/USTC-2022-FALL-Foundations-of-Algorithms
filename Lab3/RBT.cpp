#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

enum Colour //颜色
{
    RED,
    BLACK,
};

typedef struct node
{
    Colour color;
    int key;
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
                cout << 1;
            }
            else
            {
                if (z == z->p->right)
                {
                    z = z->p;         // case2
                    LeftRotate(T, z); // case2
                    cout << 2;
                }
                z->p->color = BLACK;     // case3
                z->p->p->color = RED;    // case3
                RightRotate(T, z->p->p); // case3
                cout << 3;
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
                cout << 4;
            }
            else
            {
                if (z == z->p->left)
                {
                    z = z->p;          // case5
                    RightRotate(T, z); // case5
                    cout << 5;
                }
                z->p->color = BLACK;    // case6
                z->p->p->color = RED;   // case6
                LeftRotate(T, z->p->p); // case6
                cout << 6;
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
    z->p = y;// 插入根结点时让根节点父节点指向NIL
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
    RBInsertFixup(T, z);
    return;
}

void FirstOrder(pRBTree T, pRBNode t)
{
    ofstream outfile("NLR.txt", ios_base::app);
    if (t == T->NIL)
    {
        return;
    }
    outfile << t->key << " ";
    if (t->color == RED)
    {
        outfile << "red" << endl;
    }
    else
    {
        outfile << "black" << endl;
    }
    FirstOrder(T, t->left);
    FirstOrder(T, t->right);
    return;
}

void InOrder(pRBTree T, pRBNode t)
{
    ofstream outfile("LNR.txt", ios_base::app);
    if (t == T->NIL)
    {
        return;
    }
    InOrder(T, t->left);
    outfile << t->key << " ";
    if (t->color == RED)
    {
        outfile << "red" << endl;
    }
    else
    {
        outfile << "black" << endl;
    }
    InOrder(T, t->right);
    return;
}

void FloorOrder(pRBTree T, pRBNode t)
{
    ofstream outfile("LOT.txt", ios_base::app);
    if (t == T->NIL)
    {
        return;
    }
    queue<pRBNode> q;
    q.push(t);
    while (!q.empty())
    {
        outfile << q.front()->key << " ";
        if (q.front()->color == RED)
        {
            outfile << "red" << endl;
        }
        else
        {
            outfile << "black" << endl;
        }
        if (q.front()->left != T->NIL)
        {
            q.push(q.front()->left);
        }
        if (q.front()->right != T->NIL)
        {
            q.push(q.front()->right);
        }
        q.pop();
    }
    return;
}

int main()
{
    int num, i = 0;
    ifstream infile("insert.txt", ios_base::in);
    if (!infile)
    {
        cout << "文件不存在!";
        return 0;
    }
    infile >> num;
    int key[num];
    while (infile >> key[i])
    {
        i++;
    }
    pRBTree T = new RBTree;
    RBTInit(T);
    for (int i = 0; i < num; i++)
    {
        cout << key[i] << "插入时经历的情况：" << endl;
        pRBNode z = new RBNode;
        z->key = key[i];
        z->color = RED;
        RBInsert(T, z);
        cout << endl;
    }
    FirstOrder(T, T->root);
    InOrder(T, T->root);
    FloorOrder(T, T->root);
    return 0;
}