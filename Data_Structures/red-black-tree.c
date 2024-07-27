/*
#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

// RED BLACK NODE

struct red_black_node 
{
    int colour;
    int key;
    struct red_black_node* left, * right, * parent;
};

// RED BLACK TREE

struct red_black_tree 
{
    struct red_black_node* root;
};

// RED BLACK TREE OLUÞTUR

void red_black_tree_olustur(struct red_black_tree** agac) 
{
    *agac = (struct red_black_tree*)malloc(sizeof(struct red_black_tree));

    if (*agac == NULL) 
    {
        printf("Heapte gerekli yer ayrilamadi... exit ...\n");
        exit(1);
    }

    (*agac)->root = NULL;
}

// RED BLACK DÜÐÜM OLUÞTUR

struct red_black_node* red_black_dugum_olustur() 
{
    struct red_black_node* d = (struct red_black_node*)malloc(sizeof(struct red_black_node));

    if (d == NULL) 
    {
        printf("Heapte gerekli yer ayrilamadi... exit ...\n");
        exit(1);
    }

    // d->key = key;
    d->left = d->right = NULL;
    // d->colour = BLACK;

    return d;
}

// RED BLACK TREE PREORDER YARDIMCI

void red_black_tree_preorder_yardimci(struct red_black_node* root) 
{

    if (root == NULL) return;

    if (root->left != NULL && root->right != NULL) printf("%5d", root->key);
    else printf("  ex");

    if (root->colour == RED) printf("(R)");
    else printf("(B)");

    red_black_tree_preorder_yardimci(root->left);
    red_black_tree_preorder_yardimci(root->right);
}

// RED BLACK TREE PREORDER

void red_black_tree_preorder(struct red_black_tree* T) 
{
    if (T == NULL || T->root == NULL) 
    {
        printf("Agac Bos ......\n");
        return;
    }

    red_black_tree_preorder_yardimci(T->root);
    printf("\n");
}

// LEFT ROTATE

void left_rotate(struct red_black_tree* T, struct red_black_node* x) 
{
    struct red_black_node* y;
    y = x->right;

    x->right = y->left;

    if (y->left != NULL) y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL) T->root = y;
    else 
    {
        if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

// RIGHT ROTATE

void right_rotate(struct red_black_tree* T, struct red_black_node* x) 
{
    struct red_black_node* y;

    y = x->left;
    x->left = y->right;

    if (y->right != NULL) y->right->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL) T->root = y;
    else 
    {
        if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
    }

    y->right = x;
    x->parent = y;
}

// RED BLACK TREE EKLE

void red_black_tree_ekle(struct red_black_tree* T, int key) 
{
    struct red_black_node* dugum;
    struct red_black_node* d, * d1;
    struct red_black_node* x, * y;

    x = red_black_dugum_olustur();
    x->key = key;
    x->colour = RED;

    if (T->root == NULL) 
    {
        x->parent = NULL;
        T->root = x;

        d = red_black_dugum_olustur(); // external node
        d->colour = BLACK;
        d->parent = x;
        x->left = d;

        d = red_black_dugum_olustur(); // external node
        d->colour = BLACK;
        d->parent = x;
        x->right = d;

        // return;  
        // T->root->colour = black;
        // return;        
    }
    else 
    {
        d = T->root;

        while (d->left != NULL && d->right != NULL) 
        {
            if (key < d->key) d = d->left;
            else if (key > d->key) d = d->right;
            else return;
        }

        x->left = d;
        x->right = red_black_dugum_olustur(); // external dugum
        x->right->colour = BLACK;
        x->parent = d->parent;

        if (d == d->parent->left) 
        {
            d->parent->left = x;
        }
        else
        {
            d->parent->right = x;
        }

        x->left->parent = x->right->parent = x;
        x->colour = RED;
    }

    while ((x != T->root) && (x->parent->colour == RED)) 
    {
        if (x->parent == x->parent->parent->left) 
        {
            y = x->parent->parent->right; // y is x's uncle

            if (y->colour == RED) 
            {
                // case 1 - change the colours
                x->parent->colour = BLACK;
                y->colour = BLACK;
                x->parent->parent->colour = RED;
                x = x->parent->parent; // move up the tree
            }
            else 
            {
                // y is a black node
                if (x == x->parent->right) {
                    // case 2 - move x up and rotate
                    x = x->parent;
                    left_rotate(T, x);
                }
                // case 3 - x->parent->colour =black;
                x->parent->colour = BLACK;
                x->parent->parent->colour = RED;
                right_rotate(T, x->parent->parent);
            }
        }
        else {
            y = x->parent->parent->left; // y is x's uncle
            if (y->colour == RED) {
                // case 1 - change the colours
                x->parent->colour = BLACK;
                y->colour = BLACK;
                x->parent->parent->colour = RED;
                x = x->parent->parent; // move up the tree
            }
            else {
                // y is a black node
                if (x == x->parent->left) 
                {
                    // case 2 - move x up and rotate
                    x = x->parent;
                    right_rotate(T, x);
                }

                // case 3 - x->parent->colour =black;
                x->parent->colour = BLACK;
                x->parent->parent->colour = RED;
                left_rotate(T, x->parent->parent);
            }
        }
    }

    T->root->colour = BLACK;
}

// Agacin binary search tree (ikili arama agaci ozelligini saglayip saglamadigini test ediyor.)

int binary_search_tree_yardimci(struct red_black_node* node, struct red_black_tree* T) 
{
    struct red_black_node* a;

    if (node == NULL) return 1;
    else if (node->left == NULL) return 1; // external node

    a = T->root;

    while (a->left != NULL && a != node) 
    {
        if (node->key < a->key) a = a->left;
        else if (node->key > a->key) a = a->right;
        else break;
    }

    if (a != node) return 0;

    if (binary_search_tree_yardimci(node->left, T))
        return binary_search_tree_yardimci(node->right, T);

    return 0;
}

// BINARY SEARCH TREE MÝ?

int binary_search_tree_mi(struct red_black_tree* T) 
{
    return binary_search_tree_yardimci(T->root, T);
}

// RENK KONTROLÜ YARDIMCI

int renk_kontrolu_yardimci(struct red_black_node* root) 
{

    if (root->parent == NULL && root->colour == RED) return 0; // root'un rengi kirmizi olamaz

    if (root->left == NULL) {
        if (root->colour == RED) return 0;   // external dugumun rengi kirmizi olamaz
        return 1;                         // external dugumun rengi siyah  
    }

    if (root->colour == RED && (root->left->colour == RED || root->right->colour == RED))
        return 0;                         // kirmizi parentin kirmizi cocugu olmaz  

    if (renk_kontrolu_yardimci(root->left) == 1) return renk_kontrolu_yardimci(root->right);

    return 0;
}

// RENK KONTROLÜ

int renk_kontrolu(struct red_black_tree* T)
{
    return renk_kontrolu_yardimci(T->root);
}

// SÝYAH DÜÐÜM SAYILARI KONTORLÜ YARDIMCI

int siyah_dugum_sayilari_kontrolu_yardimci(struct red_black_node* root, int sayi) 
{
    if (root == NULL) return 1;

    if (root->left == NULL) 
    {
        struct red_black_node* node = root;
        int say = 0;

        while (node != NULL) 
        {
            if (node->colour == BLACK) say++;
            node = node->parent;
        }

        if (say != sayi) return 0;

        return 1;
    }

    if (siyah_dugum_sayilari_kontrolu_yardimci(root->left, sayi) == 1)
        return siyah_dugum_sayilari_kontrolu_yardimci(root->right, sayi);

    return 0;
}

// SÝAH DÜÐÜM SAYILARI KONTORLÜ

int siyah_dugum_sayilari_kontrolu(struct red_black_tree* T) 
{
    struct red_black_node* node = T->root;
    int en_sol_yol_siyah_dugum_sayisi = 0;

    while (node != NULL) 
    {
        if (node->colour == BLACK) en_sol_yol_siyah_dugum_sayisi++;
        node = node->left;
    }

    return siyah_dugum_sayilari_kontrolu_yardimci(T->root, en_sol_yol_siyah_dugum_sayisi);
}

// RED BLACK TREE MÝ?

int red_black_tree_mi(struct red_black_tree* T) 
{
    return binary_search_tree_mi(T) && renk_kontrolu(T) && siyah_dugum_sayilari_kontrolu(T);
}

// RED BLACK TREE SÝL

void red_black_tree_sil(struct red_black_tree* T, int key) 
{
    struct red_black_node* z, * y, * x, * w;

    if (T == NULL || T->root == NULL) return;

    z = T->root;

    while (z->left != NULL && z->right != NULL) 
    {
        if (key < z->key) z = z->left;
        else if (key > z->key)  z = z->right;
        else break;
    }

    if (z->left == NULL) return; // Silinmeye calisan dugum agacta yok.

    if (z->left->left == NULL || z->right->left == NULL) y = z;
    else 
    {
        y = z->right;

        while (y->left->left != NULL) y = y->left;
    }

    if (y == T->root && y->left->left == NULL && y->right->left == NULL) 
    { 
        // Agacta sadece tek dugum varsa.
        free(y->left);
        free(y->right);
        free(y);

        T->root = NULL;
        return;
    }

    if (y->left->left != NULL)x = y->left;
    else x = y->right;

    if (x == x->parent->left) free(x->parent->right); // External dugum yok et.
    else free(x->parent->left);

    x->parent = y->parent;

    if (y->parent == NULL) T->root = x;
    else if (y == y->parent->left) y->parent->left = x;
    else y->parent->right = x;

    if (y != z) 
    {
        z->key = y->key;
        // z->colour = y->colour;
        // z->left = y->left;
        // z->right = y->right;
    }

    if (y->colour == BLACK) 
    {
        while (x != T->root && x->colour == BLACK) 
        {
            if (x == x->parent->left) 
            {
                w = x->parent->right;

                if (w->colour == RED) 
                {
                    w->colour = BLACK; // case 1
                    x->parent->colour = RED; // case 1
                    left_rotate(T, x->parent); // case 1
                    w = x->parent->right; // case 1
                }

                if (w->left->colour == BLACK && w->right->colour == BLACK) 
                {
                    w->colour = RED; // case 2
                    x = x->parent; // case 2
                }
                else 
                {
                    if (w->right->colour == BLACK) 
                    {
                        w->left->colour = BLACK; // case 3
                        w->colour = RED;  // case 3
                        right_rotate(T, w); // case 3
                        w = x->parent->right; // case 3
                    }

                    w->colour = x->parent->colour; // case 4
                    x->parent->colour = BLACK; // case 4
                    w->right->colour = BLACK; // case 4

                    left_rotate(T, x->parent); // case 4
                    x = T->root; // case 4
                }
            }
            else 
            {
                w = x->parent->left;

                if (w->colour == RED) 
                {
                    w->colour = BLACK; // case 1
                    x->parent->colour = RED; // case 1
                    right_rotate(T, x->parent); // case 1
                    w = x->parent->left; // case 1
                }

                if (w->right->colour == BLACK && w->left->colour == BLACK) 
                {
                    w->colour = RED; // case 2
                    x = x->parent; // case 2
                }
                else 
                {
                    if (w->left->colour == BLACK) 
                    {
                        w->right->colour = BLACK; // case 3
                        w->colour = RED; // case 3
                        left_rotate(T, w); // case 3
                        w = x->parent->left; // case 3
                    }

                    w->colour = x->parent->colour; // case 4
                    x->parent->colour = BLACK; // case 4
                    w->left->colour = BLACK; // case 4

                    right_rotate(T, x->parent); // case 4
                    x = T->root; // case 4
                }
            } // else
        } // while

        x->colour = BLACK;
    } // if(y->colour == BLACK)

    free(y);
}

// MAIN

int main(int argc, char** argv) {
    struct red_black_tree* T = NULL;

    red_black_tree_olustur(&T);
    red_black_tree_preorder(T);

    red_black_tree_ekle(T, 10);
    red_black_tree_ekle(T, 80);
    red_black_tree_ekle(T, 40);
    red_black_tree_ekle(T, 4);
    red_black_tree_ekle(T, 58);
    red_black_tree_ekle(T, 78);
    red_black_tree_ekle(T, 16);
    red_black_tree_ekle(T, 74);
    red_black_tree_ekle(T, 178);
    red_black_tree_ekle(T, 116);
    red_black_tree_ekle(T, 743);
    red_black_tree_ekle(T, 750);
    red_black_tree_ekle(T, 3);
    red_black_tree_ekle(T, 70);

    red_black_tree_preorder(T);

    T->root->right->left->colour = RED;

    printf("Red Black Tree mi :%d\n", red_black_tree_mi(T));
    printf("Binary Search Tree mi: %d\n", binary_search_tree_mi(T));
    printf("Renk Kontrolu: %d\n", renk_kontrolu(T));
    printf("Siyah Dugum sayilari Kontrolu: %d\n", siyah_dugum_sayilari_kontrolu(T));

    return (EXIT_SUCCESS);
}
*/
