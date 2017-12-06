#pragma once


#define LIST_DUMP(lst) printf("List '" #lst "' [0x%p] from %s %s() (%d)\n", lst, __FILE__,__PRETTY_FUNCTION__, __LINE__ );\
                    listDump(lst);


typedef int value_t;

typedef struct list_element
{
    value_t value;
    struct list_element* next;
    struct list_element* prev;
} ListElement;

typedef struct List
{
    ListElement* first;
    ListElement* last;
} List;


List* listCreate();
void listPushBack(List* lst, value_t value);
void listPushFront(List* lst, value_t value);
ListElement* listInsertBack(ListElement* elem, value_t value);
ListElement* listInsertFront(ListElement* elem, value_t value);
void listPrint(List* lst);
ListElement* listFindValue(List* lst, value_t value);
ListElement* listIndexToPointer(List* lst, int index);
void listDeleteElement(ListElement* elem);
void listDelete(List* lst);
void listDump(List* lst);
