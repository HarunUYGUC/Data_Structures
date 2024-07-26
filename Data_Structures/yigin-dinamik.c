/*
#include <stdio.h>
#include <stdlib.h>

#define SENTINEL -100000000

// D���M

struct dugum 
{
    int anahtar;
    struct dugum* sonraki;
};

// D���M OLU�TUR

struct dugum* dugum_olustur(int anahtar) 
{
    struct dugum* d;
    d = (struct dugum*)malloc(sizeof(struct dugum));

    if (d == NULL) 
    {
        printf("Yer ayrilamadi... exit...");
        exit(1);
    }

    d->anahtar = anahtar;
    d->sonraki = NULL;

    return d;
}

// EKLE

void ekle(int anahtar, struct dugum** yigin) 
{
    struct dugum* d = dugum_olustur(anahtar);
    d->sonraki = *yigin;
    *yigin = d;
}

// YAZDIR

void yazdir(struct dugum* yigin) 
{
    if (yigin == NULL) 
    {
        printf("Yigin bos\n");
        return;
    }

    while (yigin) 
    {
        printf("%4d ", yigin->anahtar);
        yigin = yigin->sonraki;
    }

    printf("\n");
}

// YAZDIR YANLI�

//void yazdir_yanlis(struct dugum **yigin_gostergesi)
//{
//   while(*yigin_gostergesi)
//   {
//       printf("%4d ", (*yigin_gostergesi)->icerik);
//       *yigin_gostergesi = (*yigin_gostergesi)->link;
//   }
//
//   printf("\n");
//}

// S�L

int sil(struct dugum** yigin) 
{
    struct dugum* d;
    int anahtar;

    if (*yigin == NULL) return SENTINEL;

    d = *yigin;
    *yigin = (*yigin)->sonraki;
    anahtar = d->anahtar;
    free(d);

    return anahtar;
}

// YI�IN BO� MU?

int yigin_bosmu(struct dugum* yigin) 
{
    if (yigin == NULL) return 1;
    else return 0;
}

// YI�INI YOK ET

void yigini_yok_et(struct dugum** yigin) 
{
    struct dugum* d;

    while (*yigin != NULL) 
    {
        d = *yigin;
        *yigin = (*yigin)->sonraki;
        free(d);
    }
}

// YI�IN YOK ET (RECURS�VE)

void yigin_yok_et_recursive(struct dugum** yigin) 
{
    struct dugum* d;

    if (*yigin == NULL) return;

    d = *yigin;
    yigin_yok_et_recursive(&(*yigin)->sonraki);
    free(d);
    *yigin = NULL;
}

// MAIN

int main(int argc, char** argv) 
{
    int a;
    struct dugum* yigin = NULL;

    ekle(100, &yigin);
    ekle(20, &yigin);
    ekle(60, &yigin);
    // yazdir(yigin_gostergesi);
    yazdir(yigin);

    a = sil(&yigin);

    if (a != SENTINEL) printf("Cikarilan: %4d \n", a);

    yazdir(yigin);
    yigin_yok_et_recursive(&yigin);
    yazdir(yigin);

    return (EXIT_SUCCESS);
}
*/
