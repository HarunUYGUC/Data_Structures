/*
#include <stdio.h>
#include <stdlib.h>

#define SENTINEL -10000000

struct yigin 
{
    int* dizi; // Yýðýnda tutulan tam sayýlara iþaretçi.
    int ust; // Yýðýna en son itilen tam sayýya index.
    int kapasite; // Yýðýnda en fazla kaç eleman tutulmaktadýr.
};

void kapasiteyi_artir(struct yigin**, int);
void kapasiteyi_artir_yeni(struct yigin**, int);

// Yýðýn oluþturma (kapasite parametre olarak alýnýyor).

struct yigin* yigin_olustur(int kapasite) 
{
    if (kapasite <= 0) 
    {
        printf("Kapasite pozitif bir tam sayi olmali... ");
        exit(1);
    }

    struct yigin* ptr = (struct yigin*)malloc(sizeof(struct yigin));

    ptr->dizi = (int*)malloc(kapasite * sizeof(int));
    ptr->ust = -1; // Yýðýn boþ.
    ptr->kapasite = kapasite;

    return ptr;
}

// Yýðýnýn adresi parametre olarak gönderiliyor.

void yigin_olustur_parametre_ile(int kapasite, struct yigin** y) 
{
    if (kapasite <= 0) 
    {
        printf("Kapasite pozitif bir tam sayi olmali... ");
        exit(1);
    }

    *y = (struct yigin*)malloc(sizeof(struct yigin));

    (*y)->dizi = (int*)malloc(kapasite * sizeof(int));
    (*y)->ust = -1;
    (*y)->kapasite = kapasite;
}

// YIÐIN BOÞ MU?

int yigin_bosmu(struct yigin* y) 
{
    if (y->ust == -1) return 1;
    else return 0;
}

// YIÐIN DOLU MU?

int yigin_dolumu(struct yigin* y) 
{
    if (y->ust == y->kapasite - 1) return 1;
    else return 0;
}

// YIÐIN EKLE

void yigin_ekle(int eleman, struct yigin** y) 
{
    if (yigin_dolumu(*y)) 
    {
        // printf("Yigin dolu, ekleme yapilamiyor...");
        // return;
        kapasiteyi_artir_yeni(y, 2);
    }

    (*y)->dizi[++(*y)->ust] = eleman;
}

// YIÐIN YAZ

void yigin_yaz(struct yigin* y) 
{
    int i;

    if (y == NULL) 
    {
        printf("Yigin icin yer ayrilmamis. Cikiyorum...\n");
        return;
    }

    printf("Yigin Kapasitesi       :%4d\n", y->kapasite);
    printf("Yigindaki Eleman Sayisi:%4d\n", y->ust + 1);

    for (i = y->ust; i >= 0; i--) 
    {
        printf("%4d ", y->dizi[i]);
    }

    printf("\n");
}

// YIÐIN ELEMAN SÝL

int yigin_eleman_sil(struct yigin* y) 
{
    if (yigin_bosmu(y)) return SENTINEL;
    return y->dizi[y->ust--];
}

// YIÐIN YOK ET

void yigin_yok_et(struct yigin** y) 
{
    free((*y)->dizi);
    free(*y);
    *y = NULL;
}

// KAPASÝTEYÝ ARTIR

void kapasiteyi_artir(struct yigin** ptr, int kackat) 
{
    struct yigin* yeni;
    yeni = yigin_olustur(kackat * ((*ptr)->kapasite));
    int i;

    for (i = 0; i <= (*ptr)->ust; i++) yeni->dizi[i] = (*ptr)->dizi[i];

    yeni->ust = (*ptr)->ust;
    yigin_yok_et(&(*ptr)); // yigin_yok_et(ptr);
    *ptr = yeni;
}

// KAPASÝTEYÝ ARTIR YENÝ

void kapasiteyi_artir_yeni(struct yigin** yigin, int kackat) 
{
    (*yigin)->dizi = (int*)realloc((*yigin)->dizi, kackat * (*yigin)->kapasite * sizeof(int));
    (*yigin)->kapasite = 2 * (*yigin)->kapasite;
}

// MAIN

int main(int argc, char** argv) 
{
    struct yigin* yigin = NULL;
    yigin = yigin_olustur(3);

    yigin_ekle(10, &yigin);
    yigin_ekle(40, &yigin);
    yigin_ekle(5, &yigin);
    yigin_yaz(yigin);

    // A=kapasiteyi_artir(&A, 2);

    yigin_ekle(-10, &yigin);
    yigin_ekle(-40, &yigin);
    yigin_ekle(25, &yigin);
    yigin_yaz(yigin);
    yigin_ekle(89, &yigin);
    yigin_ekle(189, &yigin);
    yigin_yaz(yigin);

    yigin_eleman_sil(yigin);
    yigin_yaz(yigin);

    return (EXIT_SUCCESS);
}
*/
