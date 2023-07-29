#include <stdio.h>
#ifndef POLA
# define POLA 5
#endif
#ifndef WIERSZE
# define WIERSZE 26
#endif
#ifndef KOLUMNY
# define KOLUMNY 26
#endif
#ifndef WYBOR
# define WYBOR 1000
#endif
int ocenaplanszyprawy(char tablica[][WIERSZE])/*funkcja dokonuje oceny planszy
z perspektywy prawego w taki sposób w jaki był zadany w zadaniu*/
{
    int licznik=0;
    int  ruchyprawego=0;
    int  ruchylewego=0;
        for(int i=0;i<KOLUMNY;i++)//pętla porusza się po kolumanch tablicy
        {
            for(int j=0;j<WIERSZE;j++)//pętla porusza się po wierszach tablicy
            {
                if(tablica[i][j]=='.')//jeśli natrafimy na puste pole
                licznik++;//zwiększamy licznik o 1
                if(tablica[i][j]=='#')//jeśli natrafimy na zajęte pole
                licznik=0;//zerujemy licznik
                if(licznik==POLA)//jeśli licznik osiągnie wartość POLA oznacza to, że ruch jest możliwy
                {
                    ruchylewego++;//zwiększamy ilość ruchów lewego
                    licznik=0;
                }
            }
            licznik=0;
        }
        licznik=0;
        for(int j=0;j<WIERSZE;j++)//te pętle wykonują analogiczne czynności, tylko dla gracza prawego
        {
            for(int i=0;i<KOLUMNY;i++)
            {
                if(tablica[i][j]=='.')
                licznik++;
                if(tablica[i][j]=='#')
                licznik=0;
                if(licznik==POLA)
                {
                    ruchyprawego++;
                    licznik=0;
                }
            }
            licznik=0;
        }
    return ruchyprawego-ruchylewego;//na końcu jako ocenę planszy zwracamy różnicę ruchów
}

int ruchprawego(char tablica[][WIERSZE])/*Funkcja wykonuje ruch za gracza prawego zgodnie z wytycznymi z zadania*/
{
    int A[KOLUMNY][WIERSZE];//Alokujemy pomocniczą tablicę typu int
    for(int j=0;j<WIERSZE;j++)
    {
        for(int i=0;i<KOLUMNY;i++)
        {
            A[i][j]=-1000000;//Pomocniczą tablicę wypełniamy wartościami, które nie są możliwe do otrzymania przez ocenę funkcji
        }
    }
    int mozliwyruch=0;//zmienna określająca czy ruch jest możliwy, gdy osiągnie POLA to jest możliwy
    int ilosc_mozliwych_ruchow=0;//zmienna określająca możliwość ruchów
    for(int j=0;j<WIERSZE;j++)
    {
        for(int i=0; i<KOLUMNY;i++)
        {
            mozliwyruch=0;
            for(int k=i; k<POLA+i&&i<=KOLUMNY-POLA;k++)//sprawdzam czy ruch jest mozliwy do wykonania
            {
                if(tablica[k][j]=='.')//sprawdzajac czy w kolumnie znajduje się po sobie POLE pustych elemetnów
                {
                mozliwyruch++;
                }
            }
            if(mozliwyruch==POLA)//jeśli tak to zapełniam je #
            {
                ilosc_mozliwych_ruchow++;
            for(int k=i; k<POLA+i&&i<=KOLUMNY-POLA;k++)
            {
            tablica[k][j]='#';
            }
            A[i][j]=ocenaplanszyprawy(tablica);//dokonuje oceny planszy dla podanego ruchu
            
            for(int k=i; k<POLA+i&&i<=KOLUMNY-POLA;k++)//ta pętla cofa podany ruch
            {
            tablica[k][j]='.';//cofam podany ruch
            }
            mozliwyruch=0;
            }
        }
        mozliwyruch=0;
    }
    //po tym etapie Tablica A jest wypełniona ocenami planszy dla komórek w których ruch jest możliwy,
    //oraz wartościami -1000000 dla komórek, w kótrych ruch nie jest możliwy
    int ocena_planszy=-1000;//para parametrów pozwalająca znaleźć największą wartość oceny planszy
    int maksymalna_ocena_planszy=-1000;
    int ilosc_maksymalnych_ocen=0;//pozwala zanleźć ilość maksymalnych ocen planszy
    for(int j=0;j<WIERSZE;j++)//poznajemy tutaj maksymalną ocenę planszy, oraz ilość maksymalnych ocen
    {
        for(int i=0; i<KOLUMNY;i++)
        {
            ocena_planszy=A[i][j];
            if(ocena_planszy>maksymalna_ocena_planszy)
            {
            maksymalna_ocena_planszy=ocena_planszy;
            ilosc_maksymalnych_ocen=0;
            }
            if(ocena_planszy==maksymalna_ocena_planszy)
            ilosc_maksymalnych_ocen++;
        }
    }
    int wykonaj_ruch_nr;//wybieramy kolejność ruchu zgodnie z wytycznymi z zadania
    if (ilosc_maksymalnych_ocen != 0)
        {
          wykonaj_ruch_nr=WYBOR%ilosc_maksymalnych_ocen;
        } else {
         wykonaj_ruch_nr = 0;
                }
   
    //wiemy już, który ruch chcemy wykonać, teraz wystraczy przejść się po tablicy A[][] w celu znalezienia i oraz j
    //a następnie wykonać podany ruch w tablicy[][]
    int mozliwosc_nr=-1;
    int kolumna_wykonania=-1;
    int wiersz_wykonania=-1;
    int wykonano=0;//pilnuje abyśmy wykonali tylko 1 ruch
    for(int j=0; j<WIERSZE;j++)
    {
        for(int i=0; i<KOLUMNY;i++)
        {
            if(A[i][j]==maksymalna_ocena_planszy)
            mozliwosc_nr++;//za każdym razem gdy trafimy na ruch o maksymalnej ocenie planszy
            //zwiększamy numer możliwości na której, aktulanie jesteśmy, gdy mozliwosc_nr==wykonaj_ruch_nr wykonujemyruch
            if(mozliwosc_nr==wykonaj_ruch_nr&&wykonano==0)
            {
                wykonano=1;
                for(int k=i; k<POLA+i;k++)
                {
                tablica[k][j]='#';
                }
                //zapamiętujemy współrzędne punktów, na których wykonaliśmy ruch,
                //ponieważ będą one potrzebne do zwrócenia współrzędnych ruchu
                kolumna_wykonania=i;
                wiersz_wykonania=j;
            }
        }
    }
    //chcemy zwrócić, albo współrzędne wykonania ruchu, albo '.', jeśli ruch jest niemożliwy
    //i odpowiada za kolumne i oznaczamy go wielkimi literami
    //j odpowiada za wiersz i oznaczamy go małymi literami
    
    if(ilosc_mozliwych_ruchow==0)
    {
    printf(".\n");//wypisuje '.', jeśli nie ma możliwych ruchów do wykonania
    return -1;
    }else{
    printf("%c%c\n",wiersz_wykonania+97,kolumna_wykonania+65);//wypisuje ruch, który wykonaliśmy,
    //jeśli wykonanie ruchu było możliwe
    }
    return 0;
}
void ruchgraczalewego(int y, int x, char tablica[][WIERSZE])
{ int licznik=0;
    while(licznik<POLA)
    {
        tablica[y-65][x-97+licznik]='#';//wykonuje ruch lewego wpisując do tablicy POLA razy #
        licznik++;
    }
}
int main()
{
    char tablica[KOLUMNY][WIERSZE];//alokuje tablicę do rozgrywki
    for(int j=0; j<WIERSZE; j++)
    {
      for(int i=0; i<KOLUMNY; i++) 
      {
        tablica[i][j]='.';//te pętle wypełniają ją pustymi miejscami
      }
    }
    int x=1;//parametry potrzebne do wprowadzania danych i przerwania pętli
    int wiersz=1;//pobierają współrzędne ruchu lewego i przekazują do funkcji ruchgraczalewego
    int kolumna=1;
    int enter=1;

     kolumna=getchar();
     if(kolumna=='-')//możliwość oddania pierwszego ruchu
     {
     enter=getchar();
     x=ruchprawego(tablica);
     while(x!=-1&&kolumna!='.')//ruchy wykonywane w kółko, aż do poddania, któregoś z graczy
     {
         kolumna=getchar();
         if(kolumna!='.')
         wiersz=getchar();
         enter=getchar();
         if(kolumna!='.')
         ruchgraczalewego(kolumna,wiersz,tablica);
         if(kolumna!='.')
         x=ruchprawego(tablica);
     }
     }
     if(kolumna!='-'&&x!=-1&&kolumna!='.')
     {
         wiersz=getchar();
         enter=getchar();
         ruchgraczalewego(kolumna,wiersz,tablica);
         while(x!=-1&&kolumna!='.')
         {
             x=ruchprawego(tablica);
             if(x!=-1)
             kolumna=getchar();
             if(kolumna!='.'&&x!=-1)
             {
             wiersz=getchar();
             enter=getchar();
             }
             if(kolumna!='.'&&x!=-1)
             ruchgraczalewego(kolumna,wiersz,tablica);
             
         }
     }
     x=enter;
    return 0;
}