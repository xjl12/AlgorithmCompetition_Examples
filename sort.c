#include <stdio.h>
#define MIN -500000

int main()
{
    int n, m, a[1000000], t, max;
    int *pa = a;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++, pa++)
        scanf("%d", pa);
    for (int i = 0; i < m; i++)
    {
        pa = a;
        max = *pa;
        t = 0;
        for (int j = 0; j < n; j++, pa++)
        {
            if (*pa > max)
            {
                max = *pa;
                t = j;
            }
        }
        printf(i == m - 1 ? "%d\n" : "%d ", max);
        a[t] = MIN;
    }
}