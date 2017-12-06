#include <stdio.h>

#include "list.h"

#define LIST_LEN 20

int main()
{
    List* lst = listCreate();
    int i = 0;
    for (i = 1; i < LIST_LEN; ++i)
    {
        if (i % 2)
            listPushBack(lst, i);
        else
            listPushFront(lst, i);
    }

    listPrint(lst);

    int search = 0;
    scanf("%d", &search);

    ListElement* res = listFindValue(lst, search);
    if (res)
        printf("Element %d adders is 0x[%p]\n", search, res);
    else
        printf("Element %d is not found\n", search);

    if (res)
    {
        listInsertBack(res, 716);
        listInsertFront(res, -716);
    }
    listPrint(lst);

    int index = 0;
    scanf("%d", &index);
    res = listIndexToPointer(lst, index);
    if (res)
        listDeleteElement(res);

    listPrint(lst);
    LIST_DUMP(lst);

    listDelete(lst);

    return 0;
}
