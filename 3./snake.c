#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define LENG 100



typedef struct Predmet{
    long x;
    long y;
    int vrsta;
} Predmet;





Predmet * posodobi(Predmet *kaca, int *head, int *pr, int lenK, int x, int y, int **t)
{

    if(*pr < lenK)
    {
        //povecam kaco

        //nova kaca
        Predmet *p = (Predmet *) malloc(lenK * sizeof(Predmet));
        //glava kace
        //preverim ce se je zabila
        if(t[x][y] != -1)
        {
            p[0].x = x;
            p[0].y = y;
            t[x][y] = -1;

        }
        else
        {
            return NULL;
        }


        int i = 0;
        
        //najprej posodobim, saj head kaze na zadnji dodan element v tabelo
        int zadnji = *head;
        while(*head != 0)
        {
            *head = (*head - 1);
            p[i + 1].x = kaca[*head].x;
            p[i + 1].y = kaca[*head].y;
            i++;
        }

        //printf("zad = %d\n", zadnji);
        *head = *pr - 1;
        while(*head != zadnji)
        {
            p[i + 1].x = kaca[*head].x;
            p[i + 1].y = kaca[*head].y;
            i++;
            *head = (*head - 1);
        }
        p[i + 1].x = kaca[*head].x;
        p[i + 1].y = kaca[*head].y;

        //posodobim head da kaze na najstarejsega
        *head = lenK - 1;


        // for(int i = 0; i < lenK; i++)
        // {
            
        //     printf("p[i].x = %ld, p[i].y = %ld\n", p[i].x, p[i].y);
        //     t[p[i].x][p[i].y] = -1;

        // }
        
        
        *pr = lenK;
        return p;
    }

    if(t[x][y] != -1)
    {
        t[kaca[*head].x][kaca[*head].y] = 0;
        kaca[*head].x = x;
        kaca[*head].y = y;
        t[kaca[*head].x][kaca[*head].y] = -1;
        *head = (*head + 1) % *pr;
    }
    else
    {
        return NULL;
    }
    


    return kaca;
}


void kaca(Predmet *pr, int n, int k, int **t)
{
    //spremenljiva dolzina kace
    int lenK = 1;

    //zacetna pozicija ( namesto (0, 0) je (LEN, LEN))
    long xK = LENG;
    long yK = LENG;


    bool gor = true;
    bool levo = false; 
    bool desno = false; 
    bool dol = false;
    
    //tam kjer je kaca bo -1;
    t[xK][yK] = -1;


    //spreminjajoca tabela kace
    Predmet *kaca = (Predmet *) malloc(lenK * sizeof(Predmet));
    kaca[0].x = xK;
    kaca[0].y = yK;

    int head = 0;
    // pr == prejsnji len
    int pre = lenK;
    bool konec = false;
    bool prestavi = false;

    int stevec = 0;

    while(!konec)
    {

        if(gor)
        {
            prestavi = false;
            while(!konec && !prestavi)
            {
                //en korak gor
                if(gor)
                {
                    yK++;
                }
                //preveri kje je kaca
                if(t[xK][yK] == 1)
                {
                    lenK++;
                }
                else if(t[xK][yK] == 2)
                {
                    gor = false;
                    levo = true;
                    xK--;
                    prestavi = true;
                    stevec++;
                }
                else if(t[xK][yK] == 3)
                {
                    gor = false;
                    desno = true;
                    xK++;
                    prestavi = true;
                    stevec++;
                }
                //simulira premikanje kace in posodablja pr(prejsnji len kace)
                //spremeni za 1 korak dalje
                kaca = posodobi(kaca, &head, &pre, lenK, xK, yK, t);



                // preveri ce se je kaca zaletela
                if(kaca == NULL)
                {
                    printf("%d %ld %ld\n", 0, xK, yK);
                    //nism zihr mogoce je pa treba prejsnje koordinate
                    konec = true;
                }
                printf("stevec = %d\n", stevec);
                printf("glava = (%ld, %ld)\n", xK - 100, yK - 100);
                printf("%d\n", t[xK][yK]);

                stevec++;
                if(stevec == k)
                {
                    konec = true;
                }

            }
        }
        else if(levo)
        {
            prestavi = false;
            while(!konec && !prestavi)
            {
                //en korak glevo
                if(levo)
                {
                    xK--;
                }
                //preveri kje je kaca
                if(t[xK][yK] == 1)
                {
                    lenK++;
                }
                else if(t[xK][yK] == 2)
                {
                    levo = false;
                    dol = true;
                    yK--;
                    prestavi = true;
                    stevec++;
                }
                else if(t[xK][yK] == 3)
                {
                    levo = false;
                    gor = true;
                    yK++;
                    prestavi = true;
                    stevec++;
                }

                kaca = posodobi(kaca, &head, &pre, lenK, xK, yK, t);

                // preveri ce se je kaca zaletela
                if(kaca == NULL)
                {
                    printf("%d %ld %ld\n", 0, xK, yK);
                    //nism zihr mogoce je pa treba prejsnje koordinate
                    konec = true;
                }
                printf("stevec = %d\n", stevec);
                printf("glava = (%ld, %ld)\n", xK - 100, yK - 100);
                printf("%d\n", t[xK][yK]);
                stevec++;
                if(stevec == k)
                {
                    konec = true;
                }
            }


        }
        else if(desno)
        {
            prestavi = false;
            while(!konec && !prestavi)
            {
                //en korak glevo
                if(desno)
                {
                    xK++;
                }
                //preveri kje je kaca
                if(t[xK][yK] == 1)
                {
                    lenK++;
                }
                else if(t[xK][yK] == 2)
                {
                    desno = false;
                    gor = true;
                    yK++;
                    prestavi = true;
                    //ce se zavije se poveca stevec
                    stevec++;
                }
                else if(t[xK][yK] == 3)
                {
                    desno = false;
                    dol = true;
                    yK--;
                    prestavi = true;
                    stevec++;
                }

                kaca = posodobi(kaca, &head, &pre, lenK, xK, yK, t);
                
                // preveri ce se je kaca zaletela
                if(kaca == NULL)
                {
                    printf("%d %ld %ld\n", 0, xK, yK);
                    //nism zihr mogoce je pa treba prejsnje koordinate
                    konec = true;
                }
                printf("stevec = %d\n", stevec);
                printf("glava = (%ld, %ld)\n", xK - 100, yK - 100);
                printf("%d\n", t[xK][yK]);
                
                stevec++;


                if(stevec == k)
                {
                    konec = true;
                }
            }
        }
        else 
        {
            prestavi = false;
            while(!konec && !prestavi)
            {
                //en korak glevo
                if(dol)
                {
                    yK--;
                }
                //preveri kje je kaca
                if(t[xK][yK] == 1)
                {
                    lenK++;
                }
                else if(t[xK][yK] == 2)
                {
                    dol = false;
                    desno = true;
                    xK++;
                    prestavi = true;
                    stevec++;
                }
                else if(t[xK][yK] == 3)
                {
                    dol = false;
                    levo = true;
                    xK--;
                    prestavi = true;
                    stevec++;
                }

                kaca = posodobi(kaca, &head, &pre, lenK, xK, yK, t);

                // preveri ce se je kaca zaletela
                if(kaca == NULL)
                {
                    printf("%d %ld %ld\n", 0, xK, yK);
                    konec = true;
                    //nism zihr mogoce je pa treba prejsnje koordinate
                }
                printf("stevec = %d\n", stevec);
                printf("glava = (%ld, %ld)\n", xK - 100, yK - 100);
                printf("%d\n", t[xK][yK]);
                stevec++;
                if(stevec == k)
                {
                    konec = true;
                }
            }
        }


    }

        printf("%d %ld %ld\n", lenK, xK - 100, yK - 100);
        printf("stevec = %d\n", stevec);


}





int main()
{   
    int n;
    scanf("%d", &n);

    //tabela predmetov in njihovih lokacij
    Predmet *pr = (Predmet *) malloc(n * sizeof(Predmet));

    //imam polozaje


    int **t = (int **) malloc(200 * sizeof(int));
    for(int i = 0; i < 200; i++)
    {
        t[i] = (int *) calloc(200, sizeof(int));
    }

    //preberem predmete
    for(int i = 0; i < n; i++)
    {
        scanf("%ld%ld%d", &pr[i].x, &pr[i].y, &pr[i].vrsta);

        //naredim meni ugodno igralno povrsino
        pr[i].x += LENG;
        pr[i].y += LENG;

        t[pr[i].x][pr[i].y] = pr[i].vrsta;
    }

    //preberem st korakov izvajanja
    int k;
    scanf("%d", &k);








    // printf("-----\n");
    // for(int i = 0; i < n; i++)
    // {
    //     printf("%d, %d, %d\n", pr[i].x, pr[i].y, pr[i].vrsta);
    // }


    // int **t = (int **) malloc(200* sizeof(int));
    // for(int i = 0; i < 200; i++)
    // {
    //     t[i] = (int *) calloc( 200, sizeof(int));
    // }


    //test posodobi ---> DELA
    // int head = 0;
    // int pre = 3;
    // Predmet *p = (Predmet *) malloc(3 * sizeof(Predmet));
    // for(int i = 0; i < 3; i++)
    // {
    //     scanf("%ld%ld", &p[i].x, &p[i].y);
    // }


    // p = posodobi(p, &head, &pre, 4, 4, 5, t);
    // for(int i = 0; i < pre; i++)
    // {
    //     printf("%ld, %ld\n", p[i].x, p[i].y);
    // }

    // printf("a = %d\n", pre);
    // printf("head = %d\n", head);



    //igra kace
    kaca(pr, n, k, t);


    return 0;
}
