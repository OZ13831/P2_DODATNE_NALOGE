#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>




int dolzinaN(int m, int *st)
{

    int sum = 0;
    int ost = 0;

    while(m != 0)
    {
        ost = m % 10;
        m /= 10;
        sum += ost;
        *st = *st + 1;
    }
    //printf("st = %d, sum = %d\n", *st, sum);

    return sum;
}

long power(int a, int b)
{
    long vrni = 1;

    for(int i = 0; i < b; i++)
    {
        vrni *= a;
    }
    return vrni;
}


int main()
{
    long n, m;
    scanf("%ld%ld", &n, &m);

    //printf("%ld, %ld\n", n, m);
    int st = 0;


    int len = dolzinaN(m, &st);
    //printf("%d\n", len);


    //printf("pow = %ld\n", power(10, 2));
    int f = st;

    for(int i = 0; i < st; i++)
    {
        long deli1 = power(10, f - 1);
        int ost1 = m / deli1;
        m = m % deli1;
        f--;

        //printf("ost1 = %d, m = %ld\n", ost1, m);

        long deli2 = power(10, len - ost1);
        //printf("%ld\n", deli2);
        int ost2 = n / deli2;
        n = n % deli2;
        len -= ost1;
        //printf("ost2 = %d, n = %ld\n", ost2, n);

        //izpisem to kar ostane spredaj
        printf("%d\n", ost2);



    }


    return 0;
}