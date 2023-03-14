#include "AdptArray.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct AdptArray_ {
    PElement *elementArr;
    int size;
    COPY_FUNC cpy;
    DEL_FUNC del;
    PRINT_FUNC pnt;
} AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC cpy, DEL_FUNC del, PRINT_FUNC pnt) {
    PAdptArray arr = (PAdptArray) malloc(sizeof(AdptArray));
    if (!arr) exit(1);
    arr->elementArr = NULL;
    arr->size = 0;
    arr->cpy = cpy;
    arr->del = del;
    arr->pnt = pnt;
    return arr;
}

void DeleteAdptArray(PAdptArray array) {
    if (!array) return;
    for (int i = 0; i < array->size; ++i) {
        if (array->elementArr[i] != NULL)
            array->del((array->elementArr)[i]);
    }
    free(array->elementArr);
    free(array);
}

Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem) {
    PElement *newpElemArr;
    if (pArr == NULL)
        return FAIL;
    if (idx >= pArr->size) {
        if ((newpElemArr = (PElement *) calloc((idx + 1), sizeof(PElement))) == NULL)
            return FAIL;
        memcpy(newpElemArr, pArr->elementArr, (pArr->size) * sizeof(PElement));
        if (pArr->elementArr != NULL)
            free(pArr->elementArr);
        pArr->elementArr = newpElemArr;
    }
    if (pArr->elementArr[idx] != NULL)
        pArr->del((pArr->elementArr)[idx]);
    (pArr->elementArr)[idx] = pArr->cpy(pNewElem);

    pArr->size = (idx >= pArr->size) ? (idx + 1) : pArr->size;
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray array, int index) {
    if (!array) return NULL;
    if(array->elementArr[index] == NULL) return NULL;
    PElement elem = array->cpy(array->elementArr[index]);
    return elem;
}

int GetAdptArraySize(PAdptArray arr) {
    if (!arr) return -1;
    return arr->size;
}

void PrintDB(PAdptArray arr) {
    if (!arr) return;
    for (int i = 0; i < arr->size; ++i) {
        if (arr->elementArr[i] != NULL)
            arr->pnt(arr->elementArr[i]);
    }
}
