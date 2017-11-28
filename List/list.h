#pragma once

#define DEBUG


typedef struct list_element
{
    int value;
    struct list_element* next;
    struct list_element* prev;
} ListElement, *pListElement;

typedef struct List
{
    pListElement first;
    pListElement last;
} List, *pList;


pList ListCreate();
void PushBack(pList lst, int value);
void PushFront(pList lst, int value);
pListElement InsertBack(pListElement elem, int value);
pListElement InsertFront(pListElement elem, int value);
void PrintList(pList lst);
pListElement FindValue(pList lst, int value);
pListElement IndexToPointer(pList lst, int index);
void DeleteElement(pListElement elem);
void DeleteList(pList lst);
void DumpList(pList lst);

#define DUMP_LIST(lst) printf("List '" #lst "' [0x%p] from %s %s() (%d)\n", lst, __FILE__,__PRETTY_FUNCTION__, __LINE__ );\
                    DumpList(lst);
