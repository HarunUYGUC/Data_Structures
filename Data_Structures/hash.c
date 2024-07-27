/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Hash tablosundaki listelerdeki düðüm tanýmlamasý.

struct CELL 
{
    char* anahtar;
    struct CELL* next;
};

// Anahtarý verilen bir düðümün listede olup olmadýðýnýn belirlenmesi.

int lookup(char* anahtar, struct CELL* liste_basi) 
{
    if (liste_basi == NULL) return 0;
    else if (!strcmp(anahtar, liste_basi->anahtar)) return 1;
    else return lookup(anahtar, liste_basi->next);
}

// Liste sonuna düðüm ekleme.

int insert(char* anahtar, struct CELL** liste_basi) 
{
    if (*liste_basi == NULL) 
    {
        *liste_basi = (struct CELL*)malloc(sizeof(struct CELL));
        (*liste_basi)->anahtar = (char*)malloc((strlen(anahtar) + 1) * sizeof(char));
        strcpy((*liste_basi)->anahtar, anahtar);
        (*liste_basi)->next = NULL;
        return 1;
    }
    else if (strcmp(anahtar, (*liste_basi)->anahtar))
        return insert(anahtar, &((*liste_basi)->next));
    else return 0;
}

void print_list(struct CELL* liste_basi) 
{
    if (liste_basi != NULL) 
    {
        printf("%s ", liste_basi->anahtar);
        print_list(liste_basi->next);
    }
}

// Hash tablosu düðüm tanýmlamasý.

struct table_node 
{
    int counter;
    struct CELL* header;
};

// Hash tablosu tanýmlamasý.

struct hash_tablosu 
{
    struct table_node* tablo_basi;
    int tablo_uzunlugu;
    int multiplier;
};

// Hash fonksiyonu tanýmlamasý.
// Ýlgili anahtarýn deðerine göre 0 ... table_size - 1 aralýðýnda
// iþaretsiz bir tamsayý geri dödürür.

unsigned hash(char* anahtar, int multiplier, int table_size) 
{
    int i = 0;
    unsigned int value = 0;

    while (anahtar[i]) 
    {
        value = (anahtar[i] + multiplier * value) % table_size;
        i++;
    }

    return value;
}

// Boþ hash tablosu oluþturma.

void initialize_hash_table(struct hash_tablosu** hash_table,
    int multiplier, int table_size) 
{
    int i;
    *hash_table = (struct hash_tablosu*)malloc(sizeof(struct hash_tablosu));

    if (*hash_table == NULL) 
    {
        printf(" Hash tablosu icin yer ayrilamadi... Hata!!!");
        exit(1);
    }

    (*hash_table)->tablo_basi = (struct table_node*)malloc(table_size * sizeof(struct table_node));

    if ((*hash_table)->tablo_basi == NULL) 
    {
        printf(" Hash tablosu icin yer ayrilamadi... Hata!!!");
        exit(1);
    }

    (*hash_table)->tablo_uzunlugu = table_size;
    (*hash_table)->multiplier = multiplier;

    // Hash tablosundaki listeler baþlangýçta boþ.
    for (i = 0; i < table_size; i++) 
    {
        ((*hash_table)->tablo_basi + i)->counter = 0;
        ((*hash_table)->tablo_basi + i)->header = NULL;
    }
}

// Anahtar deðeri belli bir düðümü (kaydý) hash tablosuna ekleme.

void insert_hash_table(struct hash_tablosu* hash_table, char* anahtar) 
{
    int hash_index = hash(anahtar, hash_table->multiplier, hash_table->tablo_uzunlugu);

    if (insert(anahtar, &((hash_table->tablo_basi + hash_index)->header)))
        (hash_table->tablo_basi + hash_index)->counter++;
}

// Hash tablosundaki kayýtlarý ekrana yazdýrma.

void print_hash_table(struct hash_tablosu* hash_table) 
{
    if (hash_table) 
    {
        int index;
        printf("----- HASH TABLOSU -----\n");

        for (index = 0; index < hash_table->tablo_uzunlugu; index++) 
        {
            printf("%5d : (%2d) ", index, (hash_table->tablo_basi + index)->counter);
            //  printf("%5d : (%2d) ", index,hash_table->tablo_basi[index].counter);
            print_list((hash_table->tablo_basi + index)->header);
            printf("\n");
        }
    }

    else printf("Hash Tablosu Bos ...\n");
}

// Listeden düðüm silme. Düðüm silme baþarýlý ise geriye 1, aksi halde
// geriye 0 döndürülmektedir.

int delete_dugum_liste(struct CELL** header, char* anahtar) 
{
    struct CELL* simdiki, * onceki;
    simdiki = *header;

    while (simdiki && strcmp(simdiki->anahtar, anahtar)) 
    {
        onceki = simdiki;
        simdiki = simdiki->next;
    }

    if (!simdiki) return 0;

    if (simdiki == *header) 
    {
        *header = (*header)->next;
    }
    else 
    {
        onceki->next = simdiki->next;
    }

    free(simdiki->anahtar);
    free(simdiki);

    return 1;
}

// Hash tablosundan düðüm silme.

void delete_hash_table(struct hash_tablosu* table, char* anahtar) 
{
    int hash_index = hash(anahtar, table->multiplier, table->tablo_uzunlugu);

    if (delete_dugum_liste(&((table->tablo_basi + hash_index)->header), anahtar))
        (table->tablo_basi + hash_index)->counter--;
}

// Listeyi yok etme. Listedeki düðümlerin bellek alanlarý heape iade edilmektedir.

void liste_yok_et(struct CELL** liste_basi) 
{
    struct CELL* onceki;

    while (*liste_basi) 
    {
        onceki = *liste_basi;
        *liste_basi = (*liste_basi)->next;

        free(onceki->anahtar);
        free(onceki);
    }
}

// hash tablosunun tamamýnýn (listelerin, hash tablosunun,
// ve hash tablosu bilgilerini tutan veri yapýsýnýn) heape geri verilmesi.

void hash_table_yok_et(struct hash_tablosu** hash_table) 
{
    int index;

    if (*hash_table) 
    {
        for (index = 0; index < (*hash_table)->tablo_uzunlugu; index++)
            liste_yok_et(&((*hash_table)->tablo_basi + index)->header);

        free((*hash_table)->tablo_basi);
        free(*hash_table);
    }

    *hash_table = NULL;
}

// Hash tablosuna düðüm eklemeler sonucu bazý tablolarýn uzunluðu aþýrý
// artabilir. Bu durumda ekleme ve silme iþlemleri uzar. Bunu önlemek için
// hash tablosu büyütülerek liste boylarý azaltýlýr.

void hash_table_buyut(struct hash_tablosu** htable, int multiplier, int tablo_uzunlugu) 
{
    int i;
    struct CELL* liste_basi;
    struct hash_tablosu* yeni_tablo;

    if (*htable) 
    {
        initialize_hash_table(&yeni_tablo, multiplier, tablo_uzunlugu);

        for (i = 0; i < (*htable)->tablo_uzunlugu; i++) 
        {
            liste_basi = ((*htable)->tablo_basi + i)->header;

            while (liste_basi != NULL) 
            {
                insert_hash_table(yeni_tablo, liste_basi->anahtar);
                liste_basi = liste_basi->next;
            }
        }

        hash_table_yok_et(htable);
        *htable = yeni_tablo;
    }
}

// SÝL

void sil(struct hash_tablosu* htable, char* anahtar) 
{
    struct CELL* header, * x;

    header = (htable->tablo_basi + hash(anahtar, htable->multiplier, htable->tablo_uzunlugu))->header;
    x = header;

    while (x != NULL) 
    {
        if (strcmp(x->anahtar, anahtar) == 0) 
        {
            x = header;
            break;
        }

        x = x->next;
    }

    if (x == header) 
    {
        while (header != NULL) 
        {
            x = header;
            header = header->next;

            free(x->anahtar);
            free(x);
        }

        (htable->tablo_basi + hash(anahtar, htable->multiplier, htable->tablo_uzunlugu))->header = NULL;
    }
}

// LÝSTEYÝ HASH TABLOSUNA DÖNÜÞTÜRME

void listeyi_hash_tablosuna_donusturme(struct hash_tablosu* htable, struct CELL** liste_basi) 
{
    while (*liste_basi != NULL) 
    {
        struct CELL** header;
        int i;

        i = hash((*liste_basi)->anahtar, htable->multiplier, htable->tablo_uzunlugu);
        header = &((htable->tablo_basi + i)->header);

        if ((*header) == NULL) 
        {
            *header = *liste_basi;
            *liste_basi = (*liste_basi)->next;
            (*header)->next = NULL;
        }
        else 
        {
            while ((*header)->next != NULL) header = &((*header)->next);

            (*header)->next = *liste_basi;
            *liste_basi = (*liste_basi)->next;
            (*header)->next->next = NULL;
        }

        (htable->tablo_basi + i)->counter++;
    }
}

// LÝSTE SÝL

void liste_sil(struct hash_tablosu* htable, char* anahtar) 
{
    int h = hash(anahtar, htable->multiplier, htable->tablo_uzunlugu);
    struct CELL* header = htable->tablo_basi[h].header;
    int var = 0;

    while (header) 
    {
        if (!strcmp((header->anahtar), anahtar)) 
        {
            var = 1;
            break;
        }

        header = header->next;
    }

    if (var) 
    {
        header = htable->tablo_basi[h].header;

        while (header) 
        {
            struct CELL* onceki;
            onceki = header;
            header = header->next;
            free(onceki->anahtar);
            free(onceki);

        }

        htable->tablo_basi[h].header = NULL;
        htable->tablo_basi[h].counter = 0;
    }
}

// LÝSTEYÝ DÖNÜÞTÜRME

void listeye_donusturme(struct hash_tablosu* htable, struct CELL** liste_basi) 
{
    struct CELL* a, * header;
    int i;

    *liste_basi = NULL;
    a = NULL;

    for (i = 0; i < htable->tablo_uzunlugu; i++) 
    {
        header = (htable->tablo_basi + i)->header;

        while (header != NULL) 
        {
            if (*liste_basi == NULL) 
            {
                *liste_basi = header;
                a = header;
            }
            else 
            {
                a->next = header;
                a = a->next;
            }

            header = header->next;
        }

        (htable->tablo_basi + i)->header = NULL;
        (htable->tablo_basi + i)->counter = 0;
    }

    if (a) a->next = NULL;
}

int main(int argc, char** argv) 
{
    struct hash_tablosu* htable = NULL;

    initialize_hash_table(&htable, 5, 11);

    insert_hash_table(htable, "istanbul");
    insert_hash_table(htable, "izmir");
    insert_hash_table(htable, "tekirdag");
    insert_hash_table(htable, "adana");
    insert_hash_table(htable, "samsun");
    insert_hash_table(htable, "kocaeli");
    insert_hash_table(htable, "kayseri");
    insert_hash_table(htable, "everest");
    insert_hash_table(htable, "trabzon");
    insert_hash_table(htable, "canakkale");
    print_hash_table(htable);

    // delete_hash_table(htable, "kocaeli");
    print_hash_table(htable);

    hash_table_buyut(&htable, 11, 19);
    print_hash_table(htable);

    // delete_hash_table(htable,"kayseri");
    // print_hash_table(htable);

    return (EXIT_SUCCESS);
}
*/
