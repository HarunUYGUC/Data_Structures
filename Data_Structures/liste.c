/*
#include <stdio.h>
#include <stdlib.h>

// Liste düðümü tanýmý. Düðümde en az iki alan mevcuttur.

struct dugum 
{
    int anahtar; // Düðüme ait anahtar, her bir düðüm için anahtar farklýdýr.
    // Dasit olsun diye anahtarýn tipini int olarak belirledik.
    struct dugum* sonraki; // Sonraki düðüme iþaretçi.
};

// Dinamik olarak düðümün heapte oluþturulmasý.

struct dugum* dugum_olustur(int anahtar) 
{
    struct dugum* a;
    a = (struct dugum*)malloc(sizeof(struct dugum));

    if (a == NULL) 
    {
        printf("Heap alaninda yer ayrilamadi ...\n");
        exit(1);
    }

    a->anahtar = anahtar;
    a->sonraki = NULL;

    return a;
}

// Listenin baþýna düðüm ekleme. Bu iþlemden sonra liste baþý iþaretçisi
// yeni eklenen düðüme iþaret etmeli.

void liste_basina_ekle(int anahtar, struct dugum** liste_basi) 
{
    struct dugum* a = dugum_olustur(anahtar);
    a->sonraki = *liste_basi;
    *liste_basi = a;
}

// Liste sonuna ekleme yapan fonksiyon.

void liste_sonuna_ekle(int icerik, struct dugum** liste_basi) 
{
    struct dugum* a = dugum_olustur(icerik);

    if (*liste_basi == NULL) 
    {
        a->sonraki = *liste_basi;
        *liste_basi = a;
    }
    else 
    {
        struct dugum* x = *liste_basi;

        while (x->sonraki != NULL) 
        {
            x = x->sonraki;
        }

        x->sonraki = a;
    }
}

// Listenin "iteratif (döngüsel)" yazdýrýmý.

void liste_yaz(struct dugum* liste_basi) 
{
    while (liste_basi != NULL) 
    {
        printf("%4d ", liste_basi->anahtar);
        liste_basi = liste_basi->sonraki;
    }

    printf("\n");
}

// Listenin "rekürsif" yazdýrýmý.

void liste_yaz_recursive(struct dugum* liste_basi) 
{
    if (liste_basi != NULL) 
    {
        printf("%4d ", liste_basi->anahtar);
        liste_yaz_recursive(liste_basi->sonraki);
    }
    else 
    {
        printf("\n");
    }
}

// Listenin tersten yazdýrýmý. En son düðüm ilk, ilk düðüm en son yazdýrýlýr.

void tersten_liste_yaz_recursive(struct dugum* liste_basi) 
{
    if (liste_basi != NULL) 
    {
        tersten_liste_yaz_recursive(liste_basi->sonraki);
        printf("%4d ", liste_basi->anahtar);
    }

}

// Listenin yok edilip düðümlerinin kapladýðý bellek bölgelerinin heape 
// geri verilmesi.

void liste_yok_et(struct dugum** liste_basi) 
{
    struct dugum* simdiki;

    while (*liste_basi != NULL) 
    {
        // simdiki = (*liste_basi);
        // *liste_basi = (*liste_basi)->sonraki;
        // free(simdiki);

        free(*liste_basi);
        *liste_basi = (*liste_basi)->sonraki;
    }
}

// Düðümlerin anahtarlarýna göre sýralý listeye sýralamayý bozmadan yeni bir
// düðümün eklenmesi.
// (???) Anladýðým kadarýyla küçükten büyüðe sýralý.

void liste_sirali_ekle(int anahtar, struct dugum** liste_basi) 
{
    struct dugum *a, *b, *eklenen;
    b = *liste_basi;

    while (b != NULL && b->anahtar <= anahtar) 
    {
        if (b->anahtar == anahtar) return;
        a = b;
        b = b->sonraki;
    }

    eklenen = dugum_olustur(anahtar);

    if (b == *liste_basi) 
    {
        eklenen->sonraki = *liste_basi;
        *liste_basi = eklenen;
    }
    else 
    {
        a->sonraki = eklenen;
        eklenen->sonraki = b;
    }
}

// Anaharý verilen bir düðümün listeden silinip düðümün bellek alanýnýn heape
// iade edilmesi.

void liste_eleman_sil(int anahtar, struct dugum** liste_basi) 
{
    struct dugum* temp = *liste_basi;
    struct dugum* once;

    while (temp != NULL && temp->anahtar != anahtar) 
    {
        once = temp;
        temp = temp->sonraki;
    }

    if (temp == NULL) return;
    else 
    {
        if (temp == *liste_basi) *liste_basi = (*liste_basi)->sonraki;
        else once->sonraki = temp->sonraki;

        free(temp);
    }
}

// Verilen bir listenin sýralanmasý.

void liste_sirala(struct dugum** liste_basi) 
{
    struct dugum *a, *b, *c, *d;

    if (*liste_basi == NULL || (*liste_basi)->sonraki == NULL) return;

    d = (*liste_basi)->sonraki;
    (*liste_basi)->sonraki = NULL;

    while (d != NULL) 
    {
        c = d;
        d = d->sonraki;
        b = *liste_basi;

        while (b != NULL && b->anahtar < c->anahtar) 
        {
            a = b;
            b = b->sonraki;
        }
        if (b == *liste_basi) 
        {
            c->sonraki = *liste_basi;
            *liste_basi = c;
        }
        else 
        {
            a->sonraki = c;
            c->sonraki = b;
        }
    }
}

// Düðümlerde tutulan iþaretçi deðeri deðiþtirilerek listenin ters çevrilmesi.
// Liste baþý iþaretcisi ilk listenin en sonki düðümüne iþaret edecektir.

void liste_ters_cevir(struct dugum** liste_basi) 
{
    struct dugum *a, *b;
    a = NULL;

    while (*liste_basi != NULL) 
    {
        b = *liste_basi;
        *liste_basi = (*liste_basi)->sonraki;
        b->sonraki = a;
        a = b;
    }

    *liste_basi = a;
}

// anahtar1 ve anahtar2 deðerleri ardýþýk iki düðümün anahatarlarýna karþýlýk
// gelip gelmediðini belirleyen fonksiyon.

int ardisik_mi(struct dugum* liste_basi, int anahtar1, int anahtar2) 
{
    struct dugum* onceki;
    onceki = NULL;

    while (liste_basi != NULL) 
    {
        if (liste_basi->anahtar == anahtar1) break;

        onceki = liste_basi;
        liste_basi = liste_basi->sonraki;
    }

    if (liste_basi != NULL && (onceki != NULL && onceki->anahtar == anahtar2 ||
        liste_basi->sonraki != NULL && liste_basi->sonraki->anahtar == anahtar2))
        return 1;

    return 0;
}

// anahar deðeri verilen anahatar deðerinden küçük olan düðümlerin
// listeden silinmesi.

void listeden_cikar(struct dugum** liste_basi, int anahtar) 
{
    struct dugum *b = *liste_basi, *a = *liste_basi;

    while (b != NULL) 
    {
        if (anahtar > b->anahtar) 
        {
            if (b == *liste_basi) 
            {
                *liste_basi = (*liste_basi)->sonraki;
                free(b);
                a = b = *liste_basi;
            }
            else 
            {
                a->sonraki = b->sonraki;
                free(b);
                b = a->sonraki;
            }
        }
        else 
        {
            a = b;
            b = b->sonraki;
        }
    } //while
}

// FONK

void fonk(int* dizi_A, int* dizi_B, int** dizi_sonuc, int uzunluk) 
{
    *dizi_sonuc = (int*)malloc(sizeof(int) * uzunluk);

    for (int i = 0; i < uzunluk; i++) 
    {
        // *(*dizi_sonuc + i) = dizi_A[i] + dizi_B[i];
        (*dizi_sonuc)[i] = dizi_A[i] + dizi_B[i];
    }
}

// MAIN

int main(int argc, char** argv) 
{
    struct dugum* liste = NULL;
    liste_basina_ekle(20, &liste);

    liste_basina_ekle(30, &liste);
    liste_basina_ekle(200, &liste);
    liste_basina_ekle(40, &liste);
    liste_basina_ekle(80, &liste);
    liste_basina_ekle(10, &liste);
    liste_yaz(liste);
    printf("\n");

    listeden_cikar(&liste, 41);
    liste_yaz(liste);
    printf("\n");

    return (EXIT_SUCCESS);
}
*/
