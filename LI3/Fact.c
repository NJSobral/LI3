#include "Fact.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_FACT 100000

typedef struct avl_table TFact;

typedef struct InfFact {
    float total;
    float fN;
    float fP;
    int uni;
    int N;
    int P;
} InfFact;

typedef struct LFact {
    char* cod;
    int vt1;
    int vt2;
    int vt3;
    InfFact filial1[12];
    InfFact filial2[12];
    InfFact filial3[12];
    struct LFact *next;
} LFact;

typedef struct EFact {
    TFact *tree;
    LFact *lista;
} EFact;

typedef struct ListFact{
    char* fact[MAX_FACT];
    int n;
};

int compare_strings3(const void *pa, const void *pb) {
    const LFact *a = pa;

    const LFact *b = pb;

    return strcmp(a->cod, b->cod);
}

int travessia_tree_q4(const struct avl_node *node, int n, List list, int tipo) {    
    LFact *old = node->avl_data;
    if (node->avl_link[0] != NULL){
        n = travessia_tree_q4(node->avl_link[0], n, list, tipo);
    }
    switch(tipo){
        case 0:
        if(old->vt1 == 0 && old->vt2 == 0 && old->vt3 == 0){
            list = add_string_l(list, old->cod);
            n++;
        }
        break;
        case 1:
        if(old->vt1 == 0){
            list = add_string_l(list, old->cod);
            n++;
        }
        break;
        case 2:
        if(old->vt2 == 0){
            list = add_string_l(list, old->cod);
            n++;
        }
        break;
        case 3:
        if(old->vt3 == 0){
            list = add_string_l(list, old->cod);
            n++;
        }
        break;
    }
    if(node->avl_link[1] != NULL){
        n = travessia_tree_q4(node->avl_link[1], n, list, tipo);
    }    
    
    return n;
}

List q3(Fact fact, List list, int mes, char* cod, int tipo){
    int n;
    char* res = (char*) malloc(sizeof(char*)*50);
    LFact *novo = (LFact*) malloc(sizeof (LFact));
    novo->cod = strdup(cod);
    novo = avl_find(fact->tree, novo);
    
    if(novo != NULL){
        switch(tipo){
            case 0:
                sprintf(res, "Unidades ->  N:%d P:%d\n", ((novo->filial1[mes].N)+(novo->filial2[mes].N)+(novo->filial3[mes].N)), ((novo->filial1[mes].P)+(novo->filial2[mes].P)+(novo->filial3[mes].P)));                
                list = add_string_l(list, res);
                sprintf(res, "Facturacao-> N:%.3f P:%.3f T:%.3f\n", ((novo->filial1[mes].fN)+(novo->filial2[mes].fN)+(novo->filial3[mes].fN)), ((novo->filial1[mes].fP)+(novo->filial2[mes].fP)+(novo->filial3[mes].fP)), ((novo->filial1[mes].total)+(novo->filial2[mes].total)+(novo->filial3[mes].total)));
                list = add_string_l(list, res);
                
            break;
            case 1:
                sprintf(res, "%d    %d\n", (novo->filial1[mes].N), (novo->filial1[mes].P));                
                list = add_string_l(list, res);
            break;
            case 2:
                sprintf(res, "%d    %d\n", (novo->filial2[mes].N), (novo->filial2[mes].P));                
                list = add_string_l(list, res);
            break;
            case 3:
                sprintf(res, "%d    %d\n", (novo->filial3[mes].N), (novo->filial3[mes].P));                
                list = add_string_l(list, res);
            break;                
        }
    }
        
}

List q4(Fact fact, List list, int tipo){
    int n;
    n = travessia_tree_q4(fact->tree->avl_root, 0, list, tipo);

    
    return list;
}

InfFact novo_filial() {
    InfFact novo;
    novo.N = 0;
    novo.P = 0;
    novo.fN = 0;
    novo.fP = 0;
    novo.total = 0;
    novo.uni = 0;

    return novo;
}

Fact insert_vendasF(Fact fact, char* prod, float valor, int uni, char* promo, int mes, int filial) {

    LFact *novo = (LFact*) malloc(sizeof (LFact));
    LFact *old;
    novo->cod = (char*) malloc(sizeof (prod));
    strcpy(novo->cod, prod);

    old = avl_find(fact->tree, novo);

    if (old != NULL)
        switch (filial) {
            case 1:
                if (promo == 'N') {
                    old->filial1[mes].N += uni;
                    old->filial1[mes].fN += valor;
                    old->filial1[mes].total += valor;
                    old->filial1[mes].uni += uni;
                } else {
                    old->filial1[mes].P += uni;
                    old->filial1[mes].fP += valor;
                    old->filial1[mes].total += valor;
                    old->filial1[mes].uni += uni;
                }
                old->vt1 += uni;
                break;
            case 2:
                if (promo == 'N') {
                    old->filial2[mes].N += uni;
                    old->filial2[mes].fN += valor;
                    old->filial2[mes].total += valor;
                    old->filial2[mes].uni += uni;
                } else {
                    old->filial2[mes].P += uni;
                    old->filial2[mes].fP += valor;
                    old->filial2[mes].total += valor;
                    old->filial2[mes].uni += uni;
                }
                old->vt2 += uni;
                break;
            case 3:
                if (promo == 'N') {
                    old->filial3[mes].N += uni;
                    old->filial3[mes].fN += valor;
                    old->filial3[mes].total += valor;
                    old->filial3[mes].uni += uni;
                } else {
                    old->filial3[mes].P += uni;
                    old->filial3[mes].fP += valor;
                    old->filial3[mes].total += valor;
                    old->filial3[mes].uni += uni;
                }
                old->vt3 += uni;
                break;
        }
        

    return fact;

}



Fact insert_produtosF(Fact fact, char* prod) {
    LFact *novo = (LFact*) malloc(sizeof (LFact));
    int i = 0;
    novo->cod = (char*) malloc(sizeof (prod));

    strcpy(novo->cod, prod);
    for(i = 0; i<= 12; i++){
        novo->filial1[i] = novo_filial();
        novo->filial2[i] = novo_filial();
        novo->filial3[i] = novo_filial();
    }
    novo->vt1 = 0;
    novo->vt2 = 0;
    novo->vt3 = 0;
    novo->next = fact->lista;
    fact->lista = novo;

    avl_insert(fact->tree, novo);

    return fact;
}

void teste(Fact fact, char* prod) {
    LFact *novo = (LFact*) malloc(sizeof (LFact));
    LFact *old;
    novo->cod = (char*) malloc(sizeof (prod));
    strcpy(novo->cod, prod);

    old = avl_find(fact->tree, novo);
    
}

Fact criar_fact() {
    TFact *tree;
    LFact *list;
    Fact fact;

    tree = avl_create(compare_strings3, NULL, NULL);
    list = (LFact*) malloc(sizeof (LFact));


    fact = (Fact*) malloc(sizeof (Fact));

    fact->lista = list;
    fact->tree = tree;


    return fact;
}
/*
print_tree_structure(const struct avl_node *node, int level) {
    /* You can set the maximum level as high as you like.
       Most of the time, you'll want to debug code using small trees,
       so that a large |level| indicates a ``loop'', which is a bug. 
    if (level > 100) {
        printf("[...]");
        return;
    }

    if (node == NULL)
        return;

    printf("%s", *(int *) node->avl_data);
    if (node->avl_link[0] != NULL || node->avl_link[1] != NULL) {
        putchar('(');

        print_tree_structure(node->avl_link[0], level + 1);
        if (node->avl_link[1] != NULL) {
            putchar(',');
            print_tree_structure(node->avl_link[1], level + 1);
        }

        putchar(')');
    }
}

void print_whole_tree(const struct avl_table *tree, const char *title) {
    printf("%s: ", title);
    print_tree_structure(tree->avl_root, 0);
    putchar('\n');
}

void *print(Fact clientes){
    print_whole_tree(clientes->tree, "Cenas");
    printf("Count: %d", clientes->tree->avl_count);
}*/