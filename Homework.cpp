/*                    题目描述
临近开学了，大家都忙着收拾行李准  备返校，但 I_Love_C 却不为此担心! 因为他的心思全在暑假作业上：目前为止还未开动。
暑假作业是很多张试卷，我们这些从试卷里爬出来的人都知道，卷子上的题目有选择题、填空题、简答题、证明题等。而做选择题的好处就在于工作量很少，但又因为选择题题目都普遍很长。如果有 5 张试卷，其中 4 张是选择题，最后一张是填空题，很明显做最后一张所花的时间要比前 4 张长很多。但如果你只做了选择题，虽然工作量很少，但表面上看起来也已经做了4/5的作业了。
I_Love_C决定就用这样的方法来蒙混过关，他统计出了做完每一张试卷所需的时间以及它做完后能得到的价值（按上面的原理，选择题越多价值当然就越高咯）。
现在就请你帮他安排一下，用他仅剩的一点时间来做最有价值的作业。
输入：
测试数据包括多组。每组测试数据以两个整数 M,N(1<M<20,1<N<10000) 开头，分别表示试卷的数目和 I_Love_C 剩下的时间。接下来有 M 行，每行包括两个整数 T,V(1<T<N,1<V<10000)分别表示做完这张试卷所需的时间以及做完后能得到的价值，输入以 0 0 结束。
输出：
对应每组测试数据输出 I_Love_C 能获得的最大价值。保留小数点 2 位
提示：float 的精度可能不够，你应该使用 double 类型。
*/
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;
// 建立试卷对象的数据结构
struct Paper
{
    double ratio;
    int time, value;
    // 多个试卷进行排序时，以价值/时间的比例作为唯一判优标准
    bool operator<(Paper x) const
    {
        return ratio < x.ratio;
    }
};
int main()
{
    Paper *input_papers;
    int n, t, m, v;
    while (true)
    {
        cin >> m >> n;
        input_papers = new Paper[m];
        // 程序退出的条件
        if (m == 0 && n == 0)
            break;
        for (int i = 0; i < m; i++)
        {
            cin >> t >> v;
            // 建立每一个试卷对象，写入属性
            input_papers[i].time = t;
            input_papers[i].value = v;
            input_papers[i].ratio = (double)v / t;
        }
        // 对试卷进行升序排序，排序结果：
        // 性价比低--------------------->性价比高
        sort(input_papers, input_papers + m);
        // 扫描指针初始位于数组底（性价比最高）
        Paper *it = input_papers + m - 1;
        int used_time = 0;
        double max_value = 0;
        //  循环从数组中选取性价比最高的试卷去完成 
        //   结束条件：超时或数组扫描完毕
        while (used_time <= n && it >= input_papers)
        {
            // 如果剩余的时间不够完成下一张完整的试卷，就做一部分（特判）
            if (used_time + it->time > n)
            {
                max_value += it->ratio * (n-used_time);
                break;
            }
            max_value += it->value;
            used_time += it->time;
            it--;
        }
        cout << setiosflags(ios::fixed) << setprecision(2) << max_value << endl;
    }
}