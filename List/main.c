#include <stdio.h>

#include "list.h"

#define LIST_LEN 20

int main()
{
    pList lst = ListCreate();
    int i = 0;
    for (i = 1; i < LIST_LEN; ++i)
    {
        if (i % 2)
            PushBack(lst, i);
        else
            PushFront(lst, i);
    }

    PrintList(lst);

    int search = 0;
    scanf("%d", &search);
    pListElement res = FindValue(lst, search);
    if (res)
        printf("Element %d adders is 0x[%p]\n", search, res);
    else
        printf("Element %d is not found\n", search);
    if (res)
    {
        InsertBack(res, 716);
        InsertFront(res, -716);
    }
    PrintList(lst);
    int index = 0;
    scanf("%d", &index);
    res = IndexToPointer(lst, index);
    if (res)
        DeleteElement(res);
    PrintList(lst);
    DUMP_LIST(lst);

    DeleteList(lst);

    return 0;
}
