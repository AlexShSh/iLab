#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"


List* listCreate()
{
    List* lst = (List*) calloc(1, sizeof(List));
    assert(lst && "Failed to create new list");

    lst->first = NULL;
    lst->last = NULL;

    return lst;
}


void listPushBack(List* lst, value_t value)
{
    assert(lst && "Passed NULL pointer");

    ListElement* NewEl = (ListElement*) calloc(1, sizeof(ListElement));
    assert(NewEl && "Failed to create new list element");

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


void listPushFront(List* lst, value_t value)
{
    assert(lst && "Passed NULL pointer");

    ListElement* NewEl = (ListElement*) calloc(1, sizeof(ListElement));
    assert(NewEl && "Failed to create new list element");

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


ListElement* listInsertBack(ListElement* elem, value_t value)
{
    assert(elem && "Passed NULL pointer");

    ListElement* NewElem = (ListElement*) calloc(1, sizeof(ListElement));
    assert(NewElem && "Failed to create new list element");

    NewElem->value = value;
    NewElem->next = elem->next;
    elem->next = NewElem;
    NewElem->next->prev = NewElem;
    NewElem->prev = elem;

    return NewElem;
}


ListElement* listInsertFront(ListElement* elem, value_t value)
{
    assert(elem && "Passed NULL pointer");

    ListElement* NewElem = (ListElement*) calloc(1, sizeof(ListElement));
    assert(NewElem && "Failed to create new list element");

    NewElem->value = value;
    NewElem->prev = elem->prev;
    elem->prev = NewElem;
    NewElem->prev->next = NewElem;
    NewElem->next = elem;

    return NewElem;
}


void listPrint(List* lst)
{
    assert(lst && "Passed NULL pointer");

    ListElement* current = lst->first;
    while (current)
    {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}


ListElement* listFindValue(List* lst, value_t value)
{
    assert(lst && "Passed NULL pointer");

    ListElement* current = lst->first;
    while (current)
    {
        if (current->value == value)
            return current;
        current = current->next;
    }
    return NULL;
}


ListElement* listIndexToPointer(List* lst, int index)
{
    assert(lst && "Passed NULL pointer");

    ListElement* current = lst->first;
    int i = 0;
    for (i = 0; i < index && current; i++)
        current = current->next;

    return current;
}


void listDeleteElement(ListElement* elem)
{
    assert(elem && "Passed NULL pointer");

    elem->prev->next = elem->next;
    elem->next->prev = elem->prev;
    free(elem);
}


void listDelete(List* lst)
{
    assert(lst && "Passed NULL pointer");

    ListElement* current = lst->first;
    while (current)
    {
        ListElement* tmp = current->next;
        free(current);
        current = tmp;
    }
    free(lst);
}


void listDump(List* lst)
{
    assert(lst && "Passed NULL pointer");

    ListElement* current = lst->first;
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
