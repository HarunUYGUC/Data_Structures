/*
#include <stdio.h>
#include <stdlib.h>

#define SENTINEL -10000000

struct yigin 
{
    int* dizi; // Y���nda tutulan tam say�lara i�aret�i.
    int ust; // Y���na en son itilen tam say�ya index.
    int kapasite; // Y���nda en fazla ka� eleman tutulmaktad�r.
};

void kapasiteyi_artir(struct yigin**, int);
void kapasiteyi_artir_yeni(struct yigin**, int);

// Y���n olu�turma (kapasite parametre olarak al�n�yor).

struct yigin* yigin_olustur(int kapasite) 
{
    if (kapasite <= 0) 
    {
        printf("Kapasite pozitif bir tam sayi olmali... ");
        exit(1);
    }

    struct yigin* ptr = (struct yigin*)malloc(sizeof(struct yigin));

    ptr->dizi = (int*)malloc(kapasite * sizeof(int));
    ptr->ust = -1; // Y���n bo�.
    ptr->kapasite = kapasite;

    return ptr;
}

// Y���n�n adresi parametre olarak g�nderiliyor.

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

// YI�IN BO� MU?

int yigin_bosmu(struct yigin* y) 
{
    if (y->ust == -1) return 1;
    else return 0;
}

// YI�IN DOLU MU?

int yigin_dolumu(struct yigin* y) 
{
    if (y->ust == y->kapasite - 1) return 1;
    else return 0;
}

// YI�IN EKLE

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

// YI�IN YAZ

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

// YI�IN ELEMAN S�L

int yigin_eleman_sil(struct yigin* y) 
{
    if (yigin_bosmu(y)) return SENTINEL;
    return y->dizi[y->ust--];
}

// YI�IN YOK ET

void yigin_yok_et(struct yigin** y) 
{
    free((*y)->dizi);
    free(*y);
    *y = NULL;
}

// KAPAS�TEY� ARTIR

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

// KAPAS�TEY� ARTIR YEN�

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
