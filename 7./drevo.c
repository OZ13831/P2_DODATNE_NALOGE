#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int maxSt = 0;

void izpisi2(int vozlisce, int **t, int presledki, bool prvo, int meja, int zgoraj)
{
    if(vozlisce == -1)
    {
        return;
    }
    int j = 0;

    //printf("zgoraj = %d, presl = %d\n", zgoraj, presledki);
    if(presledki != 0)
    {
        for(int i = 0; i < presledki; i++)
        {
            if(i % 4 == 0 && i < zgoraj && i >= meja)
            {
                printf("|");
            }
            else
            {
                printf(" ");
            }
        }
    }
    if(!prvo)
    {
        printf("+-- ");
    }
    printf("%d\n", vozlisce);

    while(t[vozlisce][j] != -1)
    {

        if(prvo)
        {
            if(t[vozlisce][j + 1] == -1)
            {
                meja += 4;
            }
            izpisi2(t[vozlisce][j], t, presledki, false, meja, zgoraj);
        }
        else
        {
            presledki += 4;
            // if(t[vozlisce][j + 1] != -1)
            // {
                zgoraj = presledki;
            // }
            izpisi2(t[vozlisce][j], t, presledki, false, meja, zgoraj);
            presledki -= 4;
        } 
        
        j++;
    }

}


void izpisi1(int vozlisce, int **t)
{
    if(vozlisce == -1)
    {
        return;
    }
    int j = 0;
    printf("%d", vozlisce);

    if(t[vozlisce][j] != -1)
    {
        printf("[");
        while(t[vozlisce][j] != -1)
        {
            if(j > 0)
            {
                printf(", ");
            }
            izpisi1(t[vozlisce][j], t);
            j++;
        }
        printf("]");
    }

    return;
}


int nivoji(int vozlisce, int h, int **t)
{
    if(h == 0)
    {
        return 1;
    }

    int j = 0;
    int vrni = 0;

    while(t[vozlisce][j] != -1)
    {
        vrni += nivoji(t[vozlisce][j], h - 1, t);
        j++;
    }

    return vrni;
}


int visina(int vozlisce, int **t)
{
    if(vozlisce == -1)
    {
        return 0;
    }

    int j = 0;
    int dolzina = 0;
    int maksLen = 0;

    while(t[vozlisce][j] != -1)
    {
        //printf("t[vozlisce][j] = %d\n", t[vozlisce][j]);
        dolzina = 1 + visina(t[vozlisce][j], t);
        if(dolzina > maksLen)
        {
            maksLen = dolzina;
        }
        j++;
    }
  

    return maksLen;
}


void naj_stevilka(int vozlisce, int **t)
{
    if(vozlisce == -1)
    {
        return;
    }

    int j = 0;
    if(vozlisce > maxSt)
    {
        maxSt = vozlisce;
    }
    

    while(t[vozlisce][j] != -1)
    {
        naj_stevilka(t[vozlisce][j], t);
        j++;
    }


    return;
}


int st_vozlisc(int vozlisce, int **t)
{
    if(vozlisce == -1)
    {
        return 0;
    }

    int j = 0;
    int stevilo = 0;

    while(t[vozlisce][j] != -1)
    {
        stevilo += 1 + st_vozlisc(t[vozlisce][j], t);
        j++;
    }

    return stevilo;
}


int **preberiListe(int len, int **t, int ix)
{

    for(int i = 0; i < len; i++)
    {
        scanf("%d", &t[ix][i]);
    }   
    t[ix][len] = -1;
    return t;

}


void izpisi(int **t, int len)
{
    for(int i = 1; i <= len; i++)
    {
        int j = 0;
        printf("i = %d -> ", i);
        while(t[i][j] != -1)
        {
            if(j > 0)
            {
                printf(", ");
            }
            printf("%d", t[i][j]);
            j++;
        }
        if(t[i][j] == -1)
        {
            printf(" -1");
        }
        printf("\n");
    }
}


int main()
{
    int n;
    scanf("%d", &n);

    int **t = (int **) malloc((n + 2) * sizeof(int*));

    int stListov;

    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &stListov);
        t[i] = calloc(stListov + 1, sizeof(int));
        t = preberiListe(stListov, t, i);
        if(stListov == 0)
        {
            t[i][0] = -1;
        }
    }

    // printf("----\n");
    // izpisi(t, n);

    //imam podatke o vozliscih

    int k;
    scanf("%d", &k);

    int ukaz, par;

    for(int i = 0; i < k; i++)
    {
        scanf("%d%d", &ukaz, &par);
        switch(ukaz)
        {
            case 1:
                //izpise stevilo vozlisc v poddrevesu(s korenom par)
                printf("%d\n", st_vozlisc(par, t) + 1);
                // + 1 ker ne steje zacetnega vozlisca

                break;
            case 2:
                //izpise vozlisce z najvecjo stevilko v podanem poddrevesu
                naj_stevilka(par, t);
                printf("%d\n", maxSt);
                maxSt = 0;

                break;
            case 3:
                //izpise visino poddrevesa
                printf("%d\n", visina(par, t));

                break;
            case 4:
                //izpise st vozlisc na najvisjem nivoju drevesa(najbolj spodaj)
                printf("%d\n", nivoji(par, visina(par, t), t));

                break;
            case 5:
                //izpise poddrevo na en nacin
                izpisi1(par, t);
                printf("\n");

                break;
            case 6:
                //izpise poddrevo na drug nacin
                printf("\n");
                izpisi2(par, t, 0, true, 0, 0);

                break;
        }
    }



    return 0;
}
