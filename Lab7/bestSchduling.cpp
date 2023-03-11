#include <bits/stdc++.h>

using namespace std;

int n;                // 任务数
int k;                // 机器数
int *t;               // 完成任务 i 需要的时间 为t[i]
int *robot;           // 第 i 个机器人完成被分配的任务所花的时间
int *task_robot;      // 任务与机器人的映射
int *seq;             // 最佳任务分配序列
int best = INT32_MAX; // 最佳时间

void BestScheduling(int i)
{
    if (best <= *max_element(robot, robot + k)) // 剪枝
    {
        return;
    }
    if (i > n - 1)
    {
        if (best > *max_element(robot, robot + k)) // 到达叶子结点，检查是否为更好的策略
        {
            for (int m = 0; m < n; m++)
            {
                seq[m] = task_robot[m]; // 更新分配序列
            }
            best = *max_element(robot, robot + k);
        }
        return;
    }
    else
    {
        // 剪枝，将k个机器视为等价，若任务的时间（时间和）相等，则也可以把任务视为等价
        for (int j = 0; j < k; j++)
        {
            int flag = 1;
            for (int m = 0; m < j; m++)
            {
                if (robot[j] == robot[m])
                {
                    flag = 0;
                    break;
                }
            }
            if (!flag)
            {
                continue;
            }

            if (robot[j] + t[i] < best) // 剪枝
            {
                robot[j] = robot[j] + t[i];
                task_robot[i] = j;
                BestScheduling(i + 1);
                robot[j] = robot[j] - t[i]; // 回溯
            }
        }
    }
    return;
}

void fun(string FileName)
{
    clock_t begin, end;
    ifstream infile(FileName, ios_base::in);
    infile >> n;
    infile >> k;
    t = new int[n];
    task_robot = new int[n];
    seq = new int[n];
    robot = new int[k];
    for (int i = 0; i < k; i++)
    {
        robot[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        infile >> t[i];
        task_robot[i] = -1;
        seq[i] = -1;
    }
    infile.close();
    // sort(t, t+n, greater<int>());
    begin = clock();
    BestScheduling(0);
    cout << "最佳时间为：" << best << endl;
    cout << "最佳调度为：" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "第" << i + 1 << "个任务由第" << seq[i] + 1 << "个机器完成" << endl;
    }
    end = clock();
    cout << "耗时 " << (double)(end - begin) / CLK_TCK << "s" << endl;
    delete [] t;
    delete [] task_robot;
    delete [] seq;
    delete [] robot;
    best = INT32_MAX;
    return;
}

int main()
{
    cout << "test1:" << endl;
    fun("test1.txt");    
    cout << "test2:" << endl;
    fun("test2.txt");
    cout << "test3:" << endl;
    fun("test3.txt");
    return 0;
}