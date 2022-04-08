/*                                     题目描述
三个法师康的工人每天早上6点到工厂开始到三条产品生产线上组装桔子手机。第一个工人在200时刻开始（从6点开始计时，以秒作为单位）在生产线上开始生产，一直到1000时刻。第二个工人，在700时刻开始，在1100时刻结束。第三个工人从1500时刻工作到2100时刻。期间最长至少有一个工人在生产线上工作的连续时间为900秒（从200时刻到1100时刻），而最长的无人生产的连续时间（从生产开始到生产结束）为400时刻（1100时刻到1500时刻）。
你的任务是用一个程序衡量N个工人在N条产品线上的工作时间列表（1≤N≤5000，以秒为单位）。
·最长的至少有一个工人在工作的时间段
·最长的无人工作的时间段（从有人工作开始计）

输入
输入第1行为一个整数N，第2-N+1行每行包括两个均小于1000000的非负整数数据，表示其中一个工人的生产开始时间与结束时间。

输出
输出为一行，用空格分隔开两个我们所求的数。

样例输入
3
200 1000
700 1100
1500 2100

样例输出
900 400
*/
#include <bits/stdc++.h>
#define MAX_TIME 1000000
using namespace std;
// 时间线：将一天中的时间抽象为一个数组，用time_line[i]是否为0表征i时刻是否有工人在工作
char time_line[MAX_TIME + 1];
int main()
{
    // min_s表示当天最早上班的时间，max_e表示当天最晚下班时间
    int n, s, e, min_s = MAX_TIME, max_e = 0;
    cin >> n;
    while (n--)
    {
        cin >> s >> e;
        min_s = min(min_s, s);
        max_e = max(max_e, e);
        // 将该工人的工作时间段在时间线上做非零标记
        memset(time_line + s, 1, e - s);
    }
    // cur为当前遍历的指针，pre表示前次遍历的指针（计算长度），p_end为遍历终点
    char *cur = time_line + min_s, *pre = time_line + min_s, *p_end = time_line + max_e;
    // max_work为最长连续工作时间 max_idle为最长连续空闲时间
    long max_work = 0, max_idle = 0, length;
    for (; cur <= p_end; cur++)
    {
        if (*pre != *cur)
        {
            length = cur - pre;
            if (*cur)
            // 如果pre为空闲，cur刚刚进入工作时间段，则length表示空闲的时间段
                max_idle = max(length, max_idle);
            else
            // 如果pre为工作时间，cur刚刚进入空闲时间段，则length表示工作的时间段
                max_work = max(length, max_work);
            // pre指针回归复位
            pre = cur;
        }
    }
    cout << max_work << ' ' << max_idle;
}