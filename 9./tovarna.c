#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int d[200];
bool delajo[18];

void izpisi(int *t, int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%d delavec -> %d stroju\n",i, t[i]);
    }
}


int maks = 0;

//t ima produktivnosti
int produktivnost(int stDelavcev, int stStrojev, int **t, int ix, bool *used, int *izp)
{
    if(ix == stDelavcev)
    {
        //izpisi(izp, ix);
        return 0;
    }


    int prod = 0;
    int maksProd = 0;

    for(int i = 0; i < stStrojev; i++)
    {
        if(!used[i])
        {
            used[i] = true;
            izp[ix] = i;
            prod = t[ix][i] + produktivnost(stDelavcev, stStrojev, t, ix + 1, used, izp);
            izp[ix] = -1;
            used[i] = false;
        }


        if(prod > maksProd)
        {
            maksProd = prod;
            // izpisi(izp, stDelavcev);
            // printf("maks = %d\n", maksProd);
            // printf("------\n");
        }
       
    }


   

    return maksProd;
}


int poisciMaks(int **t, int ix, int stDelavcev, int *prod)
{
    //grem po vrstici in iscem max
    int maks = 0;
    int ind = 0;
    for(int i = 0; i < stDelavcev; i++)
    {
        if(t[i][ix] > maks)
        {
            if(!delajo[i])
            {
                maks = t[i][ix];
                ind = i;

            }
            else
            {
                if(prod[i] < t[i][ix])
                {
                    maks = t[i][ix];
                    ind = i;
                }
            }
        }
    }
    delajo[ind] = true;
    prod[ind] = maks;
    return maks;
}




int main()
{

    int stDelavcev, stStrojev;
    scanf("%d%d", &stDelavcev, &stStrojev);

    int **t = (int **) malloc(stDelavcev * sizeof(int *));
    for(int i = 0; i < stDelavcev; i++)
    {
        t[i] = (int *) calloc(stStrojev, sizeof(int));
    }

    for(int i = 0; i < stDelavcev; i++)
    {
        for(int j = 0; j < stStrojev; j++)
        {
            scanf("%d", &t[i][j]);
        }
    }


    // for(int i = 0; i < stDelavcev; i++)
    // {
    //     for(int j = 0; j < stStrojev; j++)
    //     {
    //         if(j > 0)
    //         {
    //             printf(", ");
    //         }
    //         printf("%d", t[i][j]);
    //     }
    //     printf("\n");
    // }

    bool *used = (bool *) calloc(stStrojev, sizeof(bool));
    int *izp = (int *) malloc(stDelavcev * sizeof(int));

    
    int *prod = (int *) calloc(stDelavcev, sizeof(int));
    for(int i = 0; i < stDelavcev; i++)
    {
        izp[i] = -1;
    }

    if(stDelavcev > stStrojev)
    {
        int sum = 0;
        for(int i = 0; i < stStrojev; i++)
        {
            sum += poisciMaks(t, i, stDelavcev, prod);
        }
        printf("%d\n", sum);
    }   
    else
    {
        printf("%d\n", produktivnost(stDelavcev, stStrojev, t, 0, used, izp));
        // izpisi(izp, stDelavcev);

    }


    // for(int i = 0; i < stDelavcev; i++)
    // {

    //     printf("%d - ti delavec -> %d stroju\n",i, d[i]);
    // }


    return 0;
}