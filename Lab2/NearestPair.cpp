#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

struct Point
{
    int num;
    double x, y;
} point[10000], pointByX[10000], pointByY[10000];

int pos1, pos2;
int n, temp[10000];

bool cmpX(const Point &A, const Point &B)
{
    return A.x < B.x;
}
bool cmpY(const Point &A, const Point &B)
{
    return A.y < B.y;
}

double Distance(Point a, Point b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double ViolentFind(Point t[], int length)
{
    double dis;
    double temp = Distance(t[0], t[1]);
    pos1 = 0;
    pos2 = 1;
    for (int i = 0; i < length; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            dis = Distance(t[i], t[j]);
            if (temp > dis)
            {
                temp = dis;
                pos1 = i;
                pos2 = j;
            }
        }
    }
    return temp;
}

double NearestPair(Point tempX[], Point tempY[], int length, Point &a, Point &b)
{
    double d1, d2, dis;
    Point a1, b1, a2, b2;
    int i, j;
    if (length == 3)
    {
        dis = ViolentFind(tempX, length);
        a = tempX[pos1];
        b = tempX[pos2];
    }
    else if (length == 2)
    {
        a = tempX[0];
        b = tempX[1];
        dis = Distance(tempX[0], tempX[1]);
    }
    else
    {
        Point ptl[length];
        Point ptr[length];
        Point ptrY[length];
        Point ptlY[length];
        double mid = tempX[(length - 1) / 2].x;
        for (i = 0; i <= (length - 1) / 2; i++)
        {
            ptl[i] = tempX[i];
        }
        i = (length - 1) / 2 + 1;
        for (j = 0; i < length; i++)
        {
            ptr[j++] = tempX[i];
        }
        for (i = 0; i < length; i++)
        {
            if (tempY[i].x <= mid)
            {
                ptlY[i] = tempY[i];
            }
            else
            {
                ptrY[i] = tempY[i];
            }
        }

        d1 = NearestPair(ptl, ptlY, (length - 1) / 2 + 1, a1, b1);
        d2 = NearestPair(ptr, ptrY, length - (length - 1) / 2 - 1, a2, b2);
        if (d1 < d2)
        {
            dis = d1;
            a = a1;
            b = b1;
        }
        else
        {
            dis = d2;
            a = a2;
            b = b2;
        }

        // cout << d1 << " " << d2 << " " << dis << endl;

        Point ptm[length];
        int k = 0;
        for (i = 0; i < length; i++)
        {
            if (abs(tempY[i].x - mid) <= dis)
            {
                ptm[k++] = tempY[i];
            }
        }

        for (i = 0; i < k; i++)
        {
            if (ptm[i].x - mid > 0)
            {
                for (j = i + 1; j <= i + 7 && j < k; j++)
                {
                    if (ptm[j].x - mid <= 0)
                    {
                        if (Distance(ptm[i], ptm[j]) < dis)
                        {
                            dis = Distance(ptm[i], ptm[j]);
                            a = ptm[i];
                            b = ptm[j];
                        }
                    }
                }
            }
            else
            {
                for (j = i + 1; j <= i + 7 && j < k; j++)
                {
                    if (ptm[j].x - mid > 0)
                    {
                        if (Distance(ptm[i], ptm[j]) < dis)
                        {
                            dis = Distance(ptm[i], ptm[j]);
                            a = ptm[i];
                            b = ptm[j];
                        }
                    }
                }
            }
        }
    }
    return dis;
}

int main()
{
    LARGE_INTEGER start, finish, tc;
    double TotalTime = 0;
    Point a, b;
    double dis;
    int i = 1;
    int j = -1;
    ifstream infile("data.txt", ios_base::in);
    if (!infile)
    {
        cout << "文件不存在!";
        return 0;
    }
    double temp;
    while (infile >> temp)
    {
        if (i % 3 == 1)
        {
            j++;
            point[j].num = temp;
        }
        else if (i % 3 == 2)
        {
            point[j].x = temp;
        }
        else
        {
            point[j].y = temp;
        }
        i++;
    }
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&start);
    sort(point, point + 10000, cmpX);
    for (i = 0; i < 10000; i++)
    {
        pointByX[i] = point[i];
    }
    sort(point, point + 10000, cmpY);
    for (i = 0; i < 10000; i++)
    {
        pointByY[i] = point[i];
    }
    
    dis = NearestPair(pointByX, pointByY, 10000, a, b);
    //dis = ViolentFind(point, 10000);
    QueryPerformanceCounter(&finish);
    TotalTime = (finish.QuadPart - start.QuadPart) / (double)tc.QuadPart * 1000;
    cout << a.num << " " << b.num << " " << dis;
    /*
    cout << point[pos1].num << " "
         << point[pos2].num << " "
         << dis;
    */
    

    cout << endl
         << "TotalTime is " << TotalTime << " ms" << endl;
    return 0;
}