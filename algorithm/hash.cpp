#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    char* name;
    char* desc;
    struct _node* next; // 桶
} node;

#define HASHSIZE 101
node* hashtab[HASHSIZE];

void inithashtab()
{
    int i ;
    for (i = 0; i < HASHSIZE; ++i) {
        hashtab[i] = NULL;
    }
}

unsigned int hash(char* s)
{
    unsigned int h = 0;
    for (; *s; ++s) {
        h = *s + h * 31;
    }
    return h % HASHSIZE;
}

// 桶
node* lookup(char* n)
{
    unsigned int hi = hash(n);
    node* np = hashtab[hi];
    for (; np != NULL; np = np->next) {
        if (!strcmp(np->name, n)) {
            return np;
        }
    }
    return NULL;
}

char* strdup(char* c)
{
    int l = strlen(c) + 1;
    char* ns = (char*)malloc(l * sizeof(char));
    strcpy(ns, c);
    return (ns == NULL) ? NULL : ns;
}

char* get(char* name)
{
    node* n = lookup(name);
    return (n == NULL) ? NULL : n->desc;
}


int install(char* name, char* desc)
{
    unsigned int hi;
    node* np;
    if ((np = lookup(name)) == NULL) {
        hi = hash(name);
        np = (node*)malloc(sizeof(node));
        if (np == NULL) {
            return 0;
        }
        np->name = strdup(name);
        if (np->name == NULL) {
            return 0;
        }
        // 此处构成一个环
        np->next = hashtab[hi];
        hashtab[hi] = np;
    } else {
        free(np->desc);
    }
    np->desc = strdup(desc);
    if (np->desc == NULL) {
        return 0;
    }
    return 1;
}

void displaytable()
{
    int i;
    node* t;
    for (i = 0; i < HASHSIZE; ++i) {
        if (hashtab[i] == NULL) {
            printf("()");
        } else {
            t = hashtab[i];
            printf("(");
            for (; t != NULL; t = t->next) {
                printf("(%s.%s) ", t->name, t->desc);
            }
            printf(".)");
        }
        if (i % 5 == 0) {
            printf("\n");
        }
    }
}

void cleanup()
{
    int i;
    node *np, *t;
    for (i = 0; i < HASHSIZE; ++i) {
        if (hashtab[i] != NULL) {
            np = hashtab[i];
            while (np != NULL) {
                t = np->next;
                free(np->name);
                free(np->desc);
                free(np);
                np = t;
            }
        }
    }
}

int main(void)
{
    int i;
    char* names[] = {"name", "address", "phone", "k101", "k110"};
    char* desc[] = {"Sourav", "Sinagor", "2300788", "Value1", "Value2"};

    inithashtab();
    for (i = 0; i < 5; ++i) {
        install(names[i], desc[i]);
    }

    printf("Done\n");
    printf("If we didn't no anything wrong..., we should see %s\n", get("k110"));

    install("phone", "9433120451");

    printf("Again if we go right, we have %s and %s\n", get("k101"), get("phone"));

    displaytable();

    cleanup();

    return 0;
}
