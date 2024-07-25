/*
#include <stdio.h>
#include <stdlib.h>

// En az �� alana sahip. �leri i�aret�isi d���mden sonraki d���me i�aret etmekte.
// Geri ise d���mden �nce gelen d���me i�aret etmektedir.

struct dugum 
{
    int anahtar;
    struct dugum* ileri;
    struct dugum* geri;
};

// Listenin ilk ve son d��mlerine i�aret�ileri bar�nd�ran yap�.

struct ciftYonluListe 
{
    struct dugum* bas;
    struct dugum* son;
};

// Dinamik olarak d���m olu�turan fonksiyon.

struct dugum* dugumOlustur(int anahtar) 
{
    struct dugum* yeni;
    yeni = (struct dugum*)malloc(sizeof(struct dugum));

    if (yeni == NULL) 
    {
        printf("Hata, yer ayrilamadi. Sonlaniyor...");
        exit(1);
    }

    yeni->anahtar = anahtar;
    yeni->geri = yeni->ileri = NULL;

    return yeni;
}

// Listenin ilk ve son d���mlerini tutan i�aret�iler i�in heapten yer ay�rma.

void ciftYonluListeBaslat(struct ciftYonluListe** liste) 
{
    *liste = (struct ciftYonluListe*)malloc(sizeof(struct ciftYonluListe));

    if (*liste == NULL) 
    {
        printf("Hata, yer ayrilamadi. Sonlaniyor...");
        exit(1);
    }

    (*liste)->bas = (*liste)->son = NULL;
}

// Liste ba��na d���m ekleme.

void liste_basina_ekle(int anahtar, struct ciftYonluListe* liste) 
{
    struct dugum* yeni;
    yeni = dugumOlustur(anahtar);

    if (liste->son == NULL) liste->son = yeni;
    else 
    {
        liste->bas->geri = yeni;
        yeni->ileri = liste->bas;
    }

    liste->bas = yeni;
}

// Liste sonuna d���m ekleme ekle.

void liste_sonuna_ekle(int anahtar, struct ciftYonluListe* liste) 
{
    struct dugum* yeni;
    yeni = dugumOlustur(anahtar);

    if (liste->bas == NULL) liste->bas = yeni;
    else 
    {
        liste->son->ileri = yeni;
        yeni->geri = liste->son;
    }

    liste->son = yeni;
}

// Listenin yazd�r�lmas�.

void liste_yazdir(struct ciftYonluListe* liste) 
{
    struct dugum* bas;

    if (liste == NULL) return;

    bas = liste->bas;

    while (bas != NULL) 
    {
        printf("%4d ", bas->anahtar);
        bas = bas->ileri;
    }

    printf("\n");
}

// Listenin yanl�� olarak yazd�r�lmas�.

void liste_yazdir_yanlis(struct ciftYonluListe* liste) 
{
    // struct dugum *bas = liste->bas;

    while(liste->bas != NULL)
    {
        printf("%4d ", liste->bas->anahtar);
        liste->bas = liste->bas->ileri;
    }
}

// Listenin sondan ba�layarak yazd�r�lmas�.

void liste_yazdir_sondan(struct ciftYonluListe* liste) 
{
    struct dugum* son;

    if (liste == NULL) return;

    son = liste->son;

    while (son != NULL) 
    {
        printf("%4d ", son->anahtar);
        son = son->geri;
    }

    printf("\n");
}

// Listenin d���mlerinin silinerek bellek alanlar�n�n heape iade edilmesi.

void liste_yok_et(struct ciftYonluListe** liste) 
{
    struct dugum* a;

    if (*liste == NULL) return;

    while ((*liste)->bas != NULL) 
    {
        a = (*liste)->bas;
        (*liste)->bas = (*liste)->bas->ileri;
        free(a);
    }

    free(*liste);
    *liste = NULL;
}

int main(int argc, char** argv) 
{
    struct ciftYonluListe* liste;

    ciftYonluListeBaslat(&liste);

    liste_basina_ekle(40, liste);
    liste_sonuna_ekle(60, liste);
    liste_basina_ekle(90, liste);
    liste_sonuna_ekle(5, liste);
    liste_sonuna_ekle(15, liste);
    
    liste_yazdir(liste);
    // liste_yazdir_yanlis(liste);
    liste_yazdir_sondan(liste);

    liste_yok_et(&liste);

    return (EXIT_SUCCESS);
}
*/
