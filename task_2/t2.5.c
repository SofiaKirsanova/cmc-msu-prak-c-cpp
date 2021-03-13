#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node // �����
{
    char elem[255];
    struct node *next;
} Node;

typedef Node *list;

int main()
{
    char str[255];
    list lst, ptr, tmp;
    scanf("%s", str);
    if(getchar() == EOF) /// ���� 1 �����
    {
        printf("%s", str);
        return 0;
    }
    lst = malloc(sizeof(Node));
    ptr = lst;
    strcpy(lst->elem, str);
    do /// �������� ������ �� �����
    {
        scanf("%s", str);
        lst->next = malloc(sizeof(Node));
        lst = lst->next;
        strcpy(lst->elem, str);
        lst->next = NULL;
    }
    while(getchar() != EOF);
    lst = ptr; /// ��������� ��������� �������
    while(lst->next != NULL) /// ���� ��������
    {
        if (strcmp(lst->elem, str) == 0)
        {
            if(lst == ptr) /// ������������� ����������
            {
                lst = lst->next;
                free(ptr);
                ptr = lst;
            }
            else
            {
                tmp->next = lst->next;
                free(lst);
                lst = tmp->next;
            }
        }
        else
        {
            tmp = lst;
            lst = lst->next;
        }
    }
    lst = ptr;
    while(lst != NULL)
    {
        printf("%s%s", lst->elem, (lst->next != NULL) ? " " : "\n");
        lst = lst->next;
    }
    return 0;
}
