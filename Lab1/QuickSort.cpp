#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>

using namespace std;

struct parameter
{
    int begin, leftMid, rightMid, end;
};

class QuickSort
{

public:
    int length;
    vector<int> Arr;
    parameter P;
    void init(vector<int> &A, int Length);
    int Partition(int p, int r, string base);
    void GatherPartition(int p, int r);
    void InsertSort(int p, int r);
    void Sort(int p, int r, string base, string optimization);
};

void QuickSort::init(vector<int> &A, int Length)
{
    Arr = A;
    length = Length;
}

int QuickSort::Partition(int p, int r, string base)
{
    int x, i, mid;

    if (base == "random")
    {
        srand((unsigned)time(NULL));
        i = rand() % (r - p + 1) + p;
        swap(Arr[r], Arr[i]);
    }
    if (base == "middle")
    {
        mid = p + ((r - p) >> 1);
        if (Arr[mid] > Arr[p])
        {
            swap(Arr[mid], Arr[p]);
        }
        if (Arr[r] > Arr[p])
        {
            swap(Arr[r], Arr[p]);
        }
        if (Arr[mid] > Arr[r])
        {
            swap(Arr[mid], Arr[r]);
        }
    }
    x = Arr[r];
    i = p - 1;
    for (int j = p; j < r; j++)
    {
        if (Arr[j] <= x)
        {
            i += 1;
            swap(Arr[i], Arr[j]);
        }
    }
    swap(Arr[i + 1], Arr[r]);
    return i + 1;
}

void QuickSort::GatherPartition(int p, int r)
{
    int i = p, x, k;
    for (int j = p; j < r; j++)
    {
        if (Arr[j] == Arr[r])
        {
            swap(Arr[j], Arr[i]);
            i++;
        }
    }
    swap(i, p);
    x = Arr[r];
    k = p - 1;
    for (int j = p; j < r; j++)
    {
        if (Arr[j] <= x)
        {
            k += 1;
            swap(Arr[k], Arr[j]);
        }
    }
    swap(Arr[k + 1], Arr[r]);
    for (int j = i; j < p; j++)
    {
        swap(Arr[j], Arr[k - (j - i)]);
    }
    P.begin = i;
    P.leftMid = k - (p - i);
    P.rightMid = k + 2;
    P.end = r;
    return;
}

void QuickSort::InsertSort(int p, int r)
{
    int temp, i, j;
    for (i = p; i <= r; ++i)
    {
        temp = Arr[i];
        for (j = i - 1; j >= p && Arr[j] > temp; --j)
        {
            Arr[j + 1] = Arr[j];
        }
        Arr[j + 1] = temp;
    }
    return;
}

void QuickSort::Sort(int p, int r, string base = "fixed", string optimization = "normal")
{
    int q;

    if ((base != "fixed") && (base != "random") && (base != "middle"))
    {
        cout << "没有这样的的基准！" << endl;
        return;
    }
    if ((optimization != "normal") && (optimization != "InsertSort") && (optimization != "gathering"))
    {
        cout << "没有这样的的优化方法！" << endl;
        return;
    }
    if (optimization == "InsertSort")
    {
        
    }
    if (optimization == "gathering")
    {
        if (p < r)
        {
            (*this).GatherPartition(p, r);
            //for (int i = 0; i < length; ++i)
                //cout << Arr[i] << " ";
            (*this).Sort(P.begin, P.leftMid, base);
            (*this).Sort(P.rightMid, P.end, base);
        }
        return;
    }

    if (r - p < 15)
    {
        (*this).InsertSort(p, r);
        return;
    }

    
    if (p < r)
    {
        q = (*this).Partition(p, r, base);
        (*this).Sort(p, q - 1, base);
        (*this).Sort(q + 1, r, base);
    }
    return;
    
}