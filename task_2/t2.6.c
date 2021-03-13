#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    unsigned int key;
    struct node *left;
    struct node *right;
} Node;

typedef Node *tree;

void add(unsigned int x, tree *t)
{
    if(*t == NULL)
    {
        *t = malloc(sizeof(Node));
        (*t)->key = x;
        (*t)->right = NULL;
        (*t)->left = NULL;
        return;
    }
    if(x == (*t)->key)
    {
        return;
    }
    if(x < (*t)->key)
    {
        add(x, &(*t)->left);
    }
    else
    {
        add(x, &(*t)->right);
    }
    return;
}

void del(unsigned int x, tree *t)
{
    if(*t == NULL) return;
    if(x == (*t)->key)
    {
        if ((*t)->right != NULL)
        {
            tree tmp = (*t)->right;
            while(tmp->left != NULL)
            {
                tmp = tmp->left;
            }
            tmp->left = (*t)->left;
            tmp = (*t)->right;
            free(*t);
            *t = tmp;
        }
        else
        {
            *t = (*t)->left;
        }
        return;
    }
    if(x > (*t)->key)
    {
        del(x, &(*t)->right);
    }
    else
    {
        del(x, &(*t)->left);
    }
    return;
}

void search(unsigned int x, tree t)
{
    if(t == NULL)
    {
        printf("%u no\n", x);
        return;
    }
    if(t->key == x)
    {
        printf("%u yes\n", x);
        return;
    }
    if(x > t->key)
    {
        search(x, t->right);
    }
    else
    {
        search(x, t->left);
    }
    return;
}

void print(tree t)
{
    if(t != NULL)
    {
        printf("%d ", t->key);
        print(t->left);
        print(t->right);
    }
    return ;
}
int main()
{
    char sign;
    unsigned int number;
    tree tr = NULL;
    sign = getchar();
    while(sign != EOF)
    {
        scanf("%u", &number);
        switch(sign)
        {
            case '+':
                add(number, &tr);
                break;
            case '-':
                del(number, &tr);
                break;
            case '?':
                search(number, tr);
        }
        do
        {
            sign = getchar();
        }
        while(sign != '+' && sign != '-' && sign != '?' && sign != EOF);
    }
    print(tr);
    return 0;
}
