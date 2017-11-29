#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"


pList ListCreate()
{
    pList lst = (pList) calloc(1, sizeof(List));
    lst->first = NULL;
    lst->last = NULL;

    return lst;
}


void PushBack(pList lst, int value)
{
    assert(lst);
    pListElement NewEl = (pListElement) calloc(1, sizeof(ListElement));
    assert(NewEl);
    NewEl->value = value;
    NewEl->next = NULL;
    if (lst->last)
    {
        NewEl->prev = lst->last;
        lst->last->next = NewEl;
        lst->last = NewEl;
    }
    else
    {
        lst->first = lst->last = NewEl;
        NewEl->prev = NULL;
    }
}


void PushFront(pList lst, int value)
{
    assert(lst);
    pListElement NewEl = (pListElement) calloc(1, sizeof(ListElement));
    assert(NewEl);
    NewEl->value = value;
    NewEl->prev = NULL;
    if (lst->first)
    {
        NewEl->next = lst->first;
        lst->first->prev = NewEl;
        lst->first = NewEl;
    }
    else
    {
        lst->first = lst->last = NewEl;
        NewEl->next = NULL;
    }
}


pListElement InsertBack(pListElement elem, int value)
{
    assert(elem);
    pListElement NewElem = (pListElement) calloc(1, sizeof(ListElement));
    assert(NewElem);
    NewElem->value = value;
    NewElem->next = elem->next;
    elem->next = NewElem;
    NewElem->next->prev = NewElem;
    NewElem->prev = elem;

    return NewElem;
}


pListElement InsertFront(pListElement elem, int value)
{
    assert(elem);
    pListElement NewElem = (pListElement) calloc(1, sizeof(ListElement));
    assert(NewElem);
    NewElem->value = value;
    NewElem->prev = elem->prev;
    elem->prev = NewElem;
    NewElem->prev->next = NewElem;
    NewElem->next = elem;

    return NewElem;
}


void PrintList(pList lst)
{
    assert(lst);
    pListElement current = lst->first;
    while (current)
    {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}


pListElement FindValue(pList lst, int value)
{
    assert(lst);
    pListElement current = lst->first;
    while (current)
    {
        if (current->value == value)
            return current;
        current = current->next;
    }
    return NULL;
}


pListElement IndexToPointer(pList lst, int index)
{
    assert(lst);
    pListElement current = lst->first;
    int i = 0;
    for (i = 0; i < index && current; i++)
        current = current->next;

    return current;
}


void DeleteElement(pListElement elem)
{
    assert(elem);
    elem->prev->next = elem->next;
    elem->next->prev = elem->prev;
    free(elem);
}


void DeleteList(pList lst)
{
    assert(lst);
    pListElement current = lst->first;
    while (current)
    {
        pListElement tmp = current->next;
        free(current);
        current = tmp;
    }
    free(lst);
}


void DumpList(pList lst)
{
    assert(lst);
    pListElement current = lst->first;
    printf("{\n");
    if (!current)
        printf("List is empty\n");
    else
        while(current)
        {
            printf("   0x[%p] <- 0x[%p] value = %5d  -> 0x[%p]\n", current->prev, current, current->value, current->next);
            current = current->next;
        }
    printf("}\n");
}
