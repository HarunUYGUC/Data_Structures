/*
#include <stdio.h>
#include <stdlib.h>

// Liste d���m� tan�m�. D���mde en az iki alan mevcuttur.

struct dugum 
{
    int anahtar; // D���me ait anahtar, her bir d���m i�in anahtar farkl�d�r.
    // Dasit olsun diye anahtar�n tipini int olarak belirledik.
    struct dugum* sonraki; // Sonraki d���me i�aret�i.
};

// Dinamik olarak d���m�n heapte olu�turulmas�.

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

// Listenin ba��na d���m ekleme. Bu i�lemden sonra liste ba�� i�aret�isi
// yeni eklenen d���me i�aret etmeli.

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

// Listenin "iteratif (d�ng�sel)" yazd�r�m�.

void liste_yaz(struct dugum* liste_basi) 
{
    while (liste_basi != NULL) 
    {
        printf("%4d ", liste_basi->anahtar);
        liste_basi = liste_basi->sonraki;
    }

    printf("\n");
}

// Listenin "rek�rsif" yazd�r�m�.

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

// Listenin tersten yazd�r�m�. En son d���m ilk, ilk d���m en son yazd�r�l�r.

void tersten_liste_yaz_recursive(struct dugum* liste_basi) 
{
    if (liste_basi != NULL) 
    {
        tersten_liste_yaz_recursive(liste_basi->sonraki);
        printf("%4d ", liste_basi->anahtar);
    }

}

// Listenin yok edilip d���mlerinin kaplad��� bellek b�lgelerinin heape 
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

// D���mlerin anahtarlar�na g�re s�ral� listeye s�ralamay� bozmadan yeni bir
// d���m�n eklenmesi.
// (???) Anlad���m kadar�yla k���kten b�y��e s�ral�.

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

// Anahar� verilen bir d���m�n listeden silinip d���m�n bellek alan�n�n heape
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

// Verilen bir listenin s�ralanmas�.

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

// D���mlerde tutulan i�aret�i de�eri de�i�tirilerek listenin ters �evrilmesi.
// Liste ba�� i�aretcisi ilk listenin en sonki d���m�ne i�aret edecektir.

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

// anahtar1 ve anahtar2 de�erleri ard���k iki d���m�n anahatarlar�na kar��l�k
// gelip gelmedi�ini belirleyen fonksiyon.

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

// anahar de�eri verilen anahatar de�erinden k���k olan d���mlerin
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
