#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int memo[60][60][60][60][3];


int nacini(int l, int d, int c, char *t, int ix, int n)
{


    //int prejsnji = (t[ix - 1] == 'L' ? 0 : (t[ix - 1] == 'C' ? 1 : 2));

    if(ix == n + 1)
    {
        //printf("%s\n", &t[1]);
        return 1;
    }
    // if(memo[d][c][l][ix][prejsnji] != 0)
    // {
    //     return memo[d][c][l][ix][prejsnji];
    // }

    if(c == 0 && l > 0 && d > 0)
    {
        return 0;
    }



    int nac = 0;

    //posedem levicarja
    if(t[ix - 1] != 'D' && l - 1 >= 0)
    {
        t[ix] = 'L';
        nac += nacini(l - 1, d, c, t, ix + 1, n);
        t[ix] = '\0';

    }


    //posedem centrista
    if(c - 1 >= 0)
    {
        t[ix] = 'C';
        nac += nacini(l, d, c - 1, t, ix + 1, n);
        t[ix] = '\0';
    }
   

    //posedem desnicarja
    if(t[ix - 1] != 'L' && d - 1 >= 0)
    {
        t[ix] = 'D';
        nac += nacini(l, d - 1, c, t, ix + 1, n);
        t[ix] = '\0';
    }

    // memo[d][c][l][ix][prejsnji] = nac;

    return nac;
}

int main()
{
    int l, d, c;
    scanf("%d%d%d", &l, &d, &c);

    int stSedezev = l + d + c;

    char *t = (char *) calloc(stSedezev + 10, sizeof(char));
   

    printf("%d\n", nacini(l, d, c, t, 1, stSedezev));

    free(t);

    return 0;
}