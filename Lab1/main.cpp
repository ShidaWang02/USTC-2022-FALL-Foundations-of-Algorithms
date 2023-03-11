#include "QuickSort.cpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

int main()
{
    LARGE_INTEGER start, finish, tc;
    double TotalTime = 0;
    int Length;
    QuickSort A;
    vector<int> Arr;

    ifstream infile("data.txt", ios_base::in);
    if (!infile)
    {
        cout << "出错啦~这个文件出错啦！";
    }
    string s;
    infile >> s;
    Length = atoi(s.c_str());
    while (infile >> s)
    {
        Arr.push_back(atoi(s.c_str()));
        // cout << s << endl;
    }
    A.init(Arr, Length);
    QueryPerformanceFrequency(&tc);
    QueryPerformanceCounter(&start);
    // make_heap(A.Arr.begin(), A.Arr.end());
    // sort_heap(A.Arr.begin(), A.Arr.end());
    // sort(A.Arr.begin(), A.Arr.end());
    A.Sort(0, Arr.size() - 1, "fixed", "InsertSort"); // "fixed" "random" "middle";"normal" "InsertSort" "gathering"
    // A.InsertSort(0, Arr.size() - 1);
    QueryPerformanceCounter(&finish);
    TotalTime = (finish.QuadPart - start.QuadPart) / (double)tc.QuadPart * 1000;
    ofstream dataFile;
    dataFile.open("sorted.txt", ofstream::app);
    fstream file("sorted.txt", ios::out);
    for (int i = 0; i < (int)Arr.size(); i++)
    {
        dataFile << A.Arr[i] << ' ';
    }
    dataFile.close();

    cout << "TotalTime is " << TotalTime << " ms" << endl;
    return 0;
}