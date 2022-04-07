/*                                      题目描述

排序是一种很频繁的计算任务。一个实际的例子是，当我们给某项竞赛的优胜者按金银铜牌排序的时候。在这个任务中可能的值只有三种1，2和3。我们用交换的方法把他排成升序的。
写一个程序计算出，计算出的一个包括1、2、3三种值的数字序列，排成升序所需的最少交换次数。

输入
输入第1行为类别的数量N（1≤N≤1000）
输入第2行到第N+1行，每行包括一个数字（1或2或3）。

输出
输出包含一行，为排成升序所需的最少交换次数。

样例输入
9
2
2
1
3
3
3
2
3
1
样例输出
4

*/
#include <bits/stdc++.h>
using namespace std;
/******************************* 
 * 本题约定，输入的数称为原始值
 * 排过序的值称为“正确的值”
 * 例如输入：2 1 3
 * 对于第一个位置而言
 * 2为其原始值，1为正确的值
******************************/
int main()
{
    // ans为答案，counts[i]为输入中数值为 i 的数量
    int n, t, ans = 0, counts[4] = {};
    cin >> n;
    int *input_dat = new int[n];
    // 读入数据并计数
    for (int i = 0; i < n; i++)
    {
        cin >> input_dat[i];
        counts[input_dat[i]]++;
    }
    // 建立子数组，sub_dat[i]表示应该存放 i 的空间，即排过序的数组第 i 段
    int *sub_dat[] = {NULL, 
                      input_dat,                           
                      input_dat + counts[1],               
                      input_dat + counts[1] + counts[2]};
    // 外层循环扫描，处理第type段（只需扫描1，2段即可，3段自然理顺）
    for (int type = 1; type < 3; type++)
    {
        // 内层循环扫描子段，目的是找出位置不匹配的位置（需要进行交换）
        for (int sub = 0; sub < counts[type]; sub++)
        {
            if (sub_dat[type][sub] != type)
            {
                // t就表示原始值，type就是正确的值
                t = sub_dat[type][sub];
                // 循环原始值对应的子段，看看能不能一次交换成功，例如：2 1 3
                for (int i = 0; i < counts[t]; i++)
                {
                    if (sub_dat[t][i] == type)
                    {
                        // 找到这样的数，交换并记录
                        swap(sub_dat[type][sub], sub_dat[t][i]);
                        ans++;
                        break;
                    }
                }
                // 如果没有找到，那就意味着sub_dat[type][sub]没有改变
                // 这种情况属于要交换两次，例如：2 3 1
                // 对此我们不交换，由于这种情况会遇到两次（type 取1，2），所以ans自增1就够了
                if (t == sub_dat[type][sub])
                    ans++;
            }
        }
    }
    cout << ans;
}