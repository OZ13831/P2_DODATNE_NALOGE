#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_LENGTH 1000000

char niz[MAX_LENGTH + 1];




void preberi()
{

    int i = 0; 
    char znak = '\0';

    while((znak = getc(stdin)) != '\n')
    {
        niz[i] = znak;
        i++;
    }



}

void izpisi(char znak, int n)
{

    if(znak == '#')
    {
        printf("##%d#", n);
    }
    else
    {
        if(n <= 4)
        {
            for(int i = 0; i < n; i++)
            {
                printf("%c", znak);
            }
        }
        else
        {
            printf("#%c%d#", znak, n);
        }
    }


}

void code()
{
    int i = 0;
    char znak = '\0';

    bool start = true;
    int st = 1;


    while(niz[i] != '\0')
    {

        if(start)
        {
            st = 1;
            znak = niz[i];
            start = false;
        }
        else if(niz[i] != znak)
        {
            // printf("%d, ", st);
            // printf("%c\n", znak);


            izpisi(znak, st);
            //tukaj vem kateri znak je kolikokrat
            st = 1;
            znak = niz[i];
        }
        else if(niz[i] == znak)
        {
            st++;
        }


        i++;
    }


    // printf("%d, ", st);
    // printf("%c\n", znak);
    izpisi(znak, st);
    printf("\n");

}



void ven(char znak, int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("%c", znak);
    }
}

int preberi4(int start)
{
    int koliko = 0;
    int vrni = 3;

    if(niz[start + 1] == '#')
    {
        //izpisem #
        koliko = niz[start + 2] - 48;
        int a = 1;
        while(niz[start + 2 + a] >= 48 && niz[start +2 + a] <= 58)
        {
            koliko *= 10;
            koliko += niz[start + 2 + a] - 48;
        //     printf("niz[start + 2 + a] = %d\n", niz[start + 2 + a]);
            a++;
            vrni++;
        }
        ven('#', koliko);
    }
    else
    {
        char znak = niz[start + 1];
        koliko = niz[start + 2] - 48;
        int a = 1;
        while(niz[start + 2 + a] >= 48 && niz[start +2 + a] <= 58)
        {
            koliko *= 10;
            koliko += niz[start + 2 + a] - 48;
        //     printf("niz[start + 2 + a] = %d\n", niz[start + 2 + a]);
            a++;
            vrni++;
        }
        //printf("koliko = %d\n", koliko);
        ven(znak, koliko);
    }

    // printf("\n");

    //printf("i = %d\n", start);
    //printf("vrni = %d\n", vrni);
    return vrni;
}

void decode()
{
    int i = 0;
    char znak = '\0';
    bool start = true;

    int st = 1;

    while(niz[i] != '\0')
    {   
        if(start)
        {
            start = false;
            znak = niz[i];
            if(znak == '#')
            {
                i += preberi4(i);
                start = true;
            }
            else
            {
                st = 1;

            }
        }
        else if(niz[i] != znak)
        {   
            // printf("%d, ", st);
            // printf("%c\n", znak);

            //imam koliko in kateri znak
            ven(znak, st);

            st = 1;
            znak = niz[i];

            if(znak == '#')
            {
               
                i += preberi4(i);
                start = true;
            }
            else
            {
                st = 1;
            }
        }
        else if(niz[i] == znak)
        {
            st++;
        }
        //printf("i = %d\n", i);
        
        i++;
    }

    // printf("%d, ", st);
    // printf("%c\n", znak);
    if(znak != '#')
    {
        ven(znak, st);
    }

    printf("\n");
}


int main()
{

    int ukaz;
    scanf("%d", &ukaz);

    
    getc(stdin);
    preberi();


    //printf("%s\n", niz);


    if(ukaz == 1)
    {
        //kodiraj
        code();
    }
    else if(ukaz == 2)
    {
        //dekodiraj
        decode();
    }


    return 0;
}