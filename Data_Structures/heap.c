/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Heapteki düðümler.

struct dugum 
{
    int key;
    // diðer bilgiler
};

// Heap veri yapýsý.

struct heap 
{
    struct dugum* dizi;
    int kapasite; // dizinin toplam tutabilecegi dugum sayisi
    int eleman_sayisi; // aktif dugum sayisi
};

// Kapasite tane düðüm alanýna sahip heap oluþturma.

struct heap* heap_olustur(int kapasite) 
{
    struct heap* gecici;
    gecici = (struct heap*)malloc(sizeof(struct heap));

    if (gecici == NULL) 
    {
        printf("Malloc basarisiz. Yer ayrilamadi...");
        exit(1);
    }

    gecici->dizi = (struct dugum*)malloc(kapasite * sizeof(struct dugum));

    if (gecici->dizi == NULL) 
    {
        printf("Malloc basarisiz. Yer ayrilamadi...");
        exit(1);
    }

    gecici->kapasite = kapasite;
    gecici->eleman_sayisi = 0;

    return gecici;
}

// Heapin verilerini yazdýrma.

void print_heap(struct heap* heap) 
{
    int i;
    for (i = 0; i < heap->eleman_sayisi; i++) printf("%5d", heap->dizi[i].key);
    printf("\n");
}

// Heape eleman_sayisi kadar düðüm ekleme, eklenen düðümlerin 
// anahtarlarý 0 ... aralik - 1 aralýðýndadýr.

void initialize_heap_data(struct heap* heap, int eleman_sayisi, int aralik) 
{
    int i, j;
    int yeni, cik;

    srand(time(NULL)); // zamana baðlý olarak rastgele anahtar üretme 
    heap->dizi[0].key = rand() % aralik;

    for (i = 1; i < eleman_sayisi; i++) 
    {
        while (1) 
        {
            cik = 1;
            yeni = rand() % aralik;

            for (j = 0; j < i; j++) 
            {
                if (yeni == heap->dizi[j].key) 
                {
                    cik = 0; break;
                }
            }

            if (cik == 0) continue;

            heap->dizi[i].key = yeni;
            break;
        }
    }

    heap->eleman_sayisi = eleman_sayisi;
}

// Buble Down fonksiyonu. Index pozisyonunda heap özelliðini yitirmiþ
// aðacý index'i kok kabul eden alt aðaç özelinde heap hale getirme.

void buble_down(struct heap* heap, int index) 
{
    int sol, sag;
    int large_key;
    int sol_buyuk;
    struct dugum temp_dugum;

    sol = 2 * index + 1;
    sag = 2 * index + 2;

    while (sol < heap->eleman_sayisi) 
    {
        sol_buyuk = 1;
        large_key = heap->dizi[sol].key;
        temp_dugum = heap->dizi[index];

        if (sag < heap->eleman_sayisi &&
            heap->dizi[sag].key >heap->dizi[sol].key) 
        {
            sol_buyuk = 0;
            large_key = heap->dizi[sag].key;
        }

        if (large_key < heap->dizi[index].key) break;

        if (sol_buyuk) 
        {
            heap->dizi[index] = heap->dizi[sol];
            heap->dizi[sol] = temp_dugum;
            index = 2 * index + 1;
        }
        else 
        {
            heap->dizi[index] = heap->dizi[sag];
            heap->dizi[sag] = temp_dugum;
            index = 2 * index + 2;
        }

        sol = 2 * index + 1;
        sag = 2 * index + 2;
    } // while 
}

// Veriyi heap haline getirme.(Heapify)

void heapify(struct heap* heap) 
{
    int i;
    for (i = heap->eleman_sayisi / 2 - 1; i >= 0; i--) buble_down(heap, i);
}

// Heape eleman ekleme iþleminde çaðrýlýyor. Önce dizinin en sonuna eleman ekleniyor.
// Daha sonra buble_up çaðrýlarak dizi tekrar heap haline dönüþtürülüyor.

void buble_up(struct heap* heap, int index) 
{
    int parent_index;
    struct dugum temp_dugum;
    parent_index = (index - 1) / 2;

    while (parent_index >= 0 && heap->dizi[parent_index].key < heap->dizi[index].key) 
    {
        temp_dugum = heap->dizi[parent_index];
        heap->dizi[parent_index] = heap->dizi[index];
        heap->dizi[index] = temp_dugum;
        index = parent_index;
        parent_index = (index - 1) / 2;
    }
}

// Dizideki en büyük eleman siliniyor. En sondaki düðüm baþa alýnýyor,
// sonra ilk düðümden itibaren buble_down uygulanarak veri yapýsý tekrar
// heap haline dönüþtürülüyor.

void delete_max(struct heap* heap) 
{
    struct dugum dugum;

    if (heap->eleman_sayisi > 1) 
    {
        dugum = heap->dizi[0];
        heap->dizi[0] = heap->dizi[heap->eleman_sayisi - 1];
        heap->dizi[heap->eleman_sayisi - 1] = dugum;
        heap->eleman_sayisi--;
        buble_down(heap, 0);
    }
}

// Heapte arama.

int heap_search(struct heap* heap, int key) 
{
    int i;

    for (i = 0; i < heap->eleman_sayisi; i++)
        if (heap->dizi[i].key == key) return 1;

    return 0;
}

// Heap veri yapýsýna eleman ekleme. Ekleme iþlemi sýrasýnda
// heap özelliði kaybediliyor, buble_up çaðrýlarak veriye tekrar heap özelliði
// kazandýrýlýyor.

void heap_insert(struct heap* heap, int key) 
{
    if (heap_search(heap, key)) return;

    if (heap->eleman_sayisi < heap->kapasite) 
    {
        heap->eleman_sayisi++;
        heap->dizi[heap->eleman_sayisi - 1].key = key;
        buble_up(heap, heap->eleman_sayisi - 1);
    }
}

// heap_sort 

void heap_sort(struct heap* heap) 
{
    int i;
    int temp = heap->eleman_sayisi;

    for (i = 1; i < temp; i++) 
    {
        delete_max(heap);
    }

    heap->eleman_sayisi = temp;
}



// ******************************
// Ýkili Aðaçlarla Heap Oluþturma

struct dugum 
{
    int anahtar;
    struct dugum* parent, * sol_link, * sag_link;
};

struct heap 
{
    struct dugum* kok;
    struct dugum* en_son_eklenen;
};

void heap_baslat(struct heap** heap) 
{
    *heap = (struct heap*)malloc(sizeof(struct heap));
    (*heap)->kok = (*heap)->en_son_eklenen = NULL;
}

void heap_insert(struct heap* heap, int key) 
{
    struct dugum* eklenen;
    struct dugum* parent;
    int yon;

    eklenen = (struct dugum*)malloc(sizeof(struct dugum));
    eklenen->parent = eklenen->sol_link = eklenen->sag_link = NULL;
    eklenen->anahtar = key;

    if (heap->kok == NULL) 
    {
        heap->kok = eklenen;
    }
    else 
    {
        if (heap->en_son_eklenen == heap->kok) 
        {
            parent = heap->kok;
            yon = 0;
        }
        else if (heap->en_son_eklenen ==
            heap->en_son_eklenen->parent->sol_link) 
        {
            parent = heap->en_son_eklenen->parent;
            yon = 1;
        }
        else 
        {
            struct dugum* d = heap->en_son_eklenen;

            while (d != heap->kok && d == d->parent->sag_link) d = d->parent;

            if (d != heap->kok) 
            {
                parent = d->parent->sag_link;
                yon = 0;
            }
            else 
            {
                parent = heap->kok;
                yon = 0;
            }
        }

        if (yon == 0) 
        {
            while (parent->sol_link != NULL) parent = parent->sol_link;

            parent->sol_link = eklenen;
        }
        else 
        {
            parent->sag_link = eklenen;
        }

        eklenen->parent = parent;
    }

    heap->en_son_eklenen = eklenen;
    parent = eklenen->parent;

    while (parent != NULL && parent->anahtar < eklenen->anahtar) 
    {
        int k;
        struct dugum* d;

        k = eklenen->anahtar;
        d = eklenen;

        eklenen->anahtar = parent->anahtar;
        parent->anahtar = k;
        eklenen = parent;
        parent = parent->parent;
    }
}

void delete_max(struct heap* heap) 
{
    if (heap->en_son_eklenen == heap->kok) 
    {
        free(heap->kok);
        heap->kok = heap->en_son_eklenen = NULL;
    }
    else if (heap->en_son_eklenen == heap->kok->sol_link) 
    {
        free(heap->kok);
        heap->kok = heap->en_son_eklenen;
    }
    else 
    {
        if (heap->en_son_eklenen ==
            heap->en_son_eklenen->parent->sag_link) 
        {
            struct dugum* d = heap->en_son_eklenen;

            heap->kok->anahtar = heap->en_son_eklenen->anahtar;
            heap->en_son_eklenen = heap->en_son_eklenen->parent->sol_link;
            heap->en_son_eklenen->parent->sag_link = NULL;

            free(d);
        }
        else 
        {
            struct dugum* d = heap->en_son_eklenen;

            while (d != heap->kok && d == d->parent->sol_link) d = d->parent;

            if (d != heap->kok) d = d->parent->sol_link;

            while (d->sag_link != NULL) d = d->sag_link;

            heap->kok->anahtar = heap->en_son_eklenen->anahtar;
            heap->en_son_eklenen->parent->sol_link = NULL;

            free(heap->en_son_eklenen);
            heap->en_son_eklenen = d;
        }
    }

    if (heap->kok) 
    {
        struct dugum* d = heap->kok;
        int i;

        while (1) 
        {
            if (d->sag_link && d->sag_link->anahtar > d->anahtar &&
                d->sag_link->anahtar > d->sol_link->anahtar) 
            {
                i = d->anahtar;
                d->anahtar = d->sag_link->anahtar;
                d->sag_link->anahtar = i;
                d = d->sag_link;
            }
            else if (d->sol_link && d->sol_link->anahtar > d->anahtar) 
            {
                i = d->anahtar;
                d->anahtar = d->sol_link->anahtar;
                d->sol_link->anahtar = i;
                d = d->sol_link;
            }
            else break;
        }
    }
}

void heap_print(struct dugum* kok) 
{
    if (kok == NULL) return;

    printf("%d  ", kok->anahtar);
    heap_print(kok->sol_link);
    heap_print(kok->sag_link);
}

int main(int argc, char** argv) {

    struct heap* heap;

    heap = heap_olustur(20);

    heap_insert(heap, 812);
    heap_insert(heap, 900);
    heap_insert(heap, 12);
    heap_insert(heap, 121);
    heap_insert(heap, 989);
    heap_insert(heap, 990);
    heap_insert(heap, 12);
    print_heap(heap);

    delete_max(heap);
    print_heap(heap);

    // printf("\nEnson eklenen: %d\n",heap->en_son_eklenen->anahtar);
    return (EXIT_SUCCESS);
}
*/
