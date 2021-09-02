// 肖佳乐 模拟算法实现
#include <stdio.h>
#include <string.h>
//宏定义
#define KMAX 13   //定义K最大值
#define GOOD 1    //定义好人
#define BAD 0     //定义坏人
#define NOBODY -1 //定义数组末尾

/***************************************************************
* 该函数用于将location所指的人杀死，并将后面的人向前移动，补齐空位  *
* 例如：[1   1   1   0   0   0   -1] 欲处决第五个人              *
*       则将        指针 ↑  传入此函数即可                       *
*       处理结果为：[1   1   1   0   0   -1   -1]               *  
****************************************************************/
void moveForward(char *location)
{
    for (; *location != NOBODY; location++)
        *location = *(location + 1);
}

/*****************************************************************************
 * 程序说明：此程序分两步运行：首先构建表，再根据用户输入打表。                   *
 * 运行性能：在 0<k<14 的情况下运行一遍需0.050s （Windows Subsystem for Linux） *
 * 总体思路：将好人、坏人置于一数组中，数组末尾置结束标记（查找过程中遇结束标记     *
 *          会返回数组开头再查找），将 m 从小到大按如下公式取值代入循环体中：      *
 *              m = N * ( k + 1 ) 、m = N * (k + 1) + 1 (N为正整数)           *
 *           然后在内层循环体中不断模拟游戏过程，查找与处决指定的对象，若m符合条   *
 *           件，则跳出循环，将 m 值存入表results中。表构建好之后，根据输入打表。 *
 *****************************************************************************/
int main()
{
    int k, results[KMAX + 1];
    char data[2 * KMAX + 1],
        flag,
        *p_data;                          //指向待处决者
    for (k = 1; k <= KMAX; k++, flag = 0) // k从1到13循环取值，构建表
    {
        for (int m = k + 1;; m = flag ? m + k : m + 1, flag = !flag)
        {
            int num = 2 * k; //num指示当前剩余人数
            memset(data, GOOD, k);
            memset(data + k, BAD, k);
            data[2 * k] = NOBODY;
            //以上三步初始化data数组，将前k项置好人，后k项置坏人，末尾置结束标记
            p_data = data; //重置（初始化）指针位置
            while (1)
            {
                int count = (m - 1) % num + 1;
                /************************************************
                 * 开始遍历数组，查找被杀对象                     *
                 * 若遇指针后一项是末尾，则返回开头                *
                 ************************************************/
                for (int i = 1; i < count; i++)
                    p_data = *(p_data + 1) == NOBODY ? data : p_data + 1;
                if (*p_data == GOOD)
                    break;           //好人被杀，不符题意，中止循环
                moveForward(p_data); //处决坏人
                num--;
                if (*p_data == NOBODY) //若处决的是队伍最后一人，则指针将指向数组末尾，需将其向前移动
                    p_data = data;
            }
            //判断坏人是否杀完
            if (data[k] == NOBODY)
            {
                results[k] = m;
                break;
            }
        }
    }
    //  打表
    while (scanf("%d", &k) && k)
        printf("%d\n", results[k]);
}
