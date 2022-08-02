#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"
#include "memcheck.h"

/* 
 * newrecord: name, age, address, phone을 담고 있는 새로운 record를 생성한다. 
 */
Record *newrecord(const char *name, int age, const char *address, const char *phone)
{
    Record *newp;
    newp = (Record *)malloc(sizeof(Record));
    if (newp == NULL) {
        fprintf(stderr, "No more memory to add a new record.\n");
        exit(1);
    }
    newp->name = (char *)name;
    newp->age = age;
    newp->address = (char *)address;
    newp->phone = (char *)phone;
    newp->left = newp->right = NULL;
    return newp;
}

/* 
 * addrecord: treep에 newp를 추가하고 treep를 리턴한다. 
 * 만약 newp가 중복된다면 오류 메시지를 출력하고 newp의 기억 공간을 해제시킨다.
 */
Record *addrecord(Record *treep, Record *newp)
{
    /* 트리가 비어 있을 때 */
    if(treep == NULL) {
        treep = newp;
        return newp;
    }
    /* 중복되는 값을 확인하기 위해 탐색하며 위치 선정 */
    Record *travp = treep;  
    while (travp != NULL) {
        int cmp_phone = strcmp(newp->phone, travp->phone);
        /* phone이 중복될 때 */
        if (cmp_phone == 0) {    
            fprintf(stderr, "addrecord: duplicate entry %s are not allowed.\n", newp->phone);
            free(newp);
            return treep;
        }
        int cmp_name = strcmp(newp->name, travp->name);
        /* name이 중복될 때 */
        if (cmp_name == 0) {  
            fprintf(stderr, "addrecord: duplicate entry %s are not allowed.\n", newp->name);
            free(newp);
            return treep;
        }
        /* 왼쪽 서브 트리로 이동한다. */
        else if (cmp_name < 0) {
             /* 왼쪽 서브 트리에 추가한다. */
            if(travp->left == NULL) {  
                travp->left = newp;
                return treep;
            }
            else 
                travp = travp->left;
        }
        /* 오른쪽 서브 트리로 이동한다. */
        else { 
            /* 왼쪽 서브 트리에 추가한다. */
            if (travp->right == NULL) { 
                travp->right = newp;
                return treep;
            }
            else 
                travp = travp->right;
        }
    }
}

/* 
 * 이진 검색 트리(BST)가 비어 있지 않으면 treep 안의 가장 작은 키 값을 가진 노드를 반환한다.
 * 전체 treep를 검색하지 않아도 된다. (delrecord에 사용)
 */
static Record *minValueNode(Record *treep)
{ 
    Record *current = treep; 
    /* 가장 왼쪽에 있는 값을 찾기 위해 밑으로 내려간다. */
    while (current && current->left != NULL) 
        current = current->left; 
    return current; 
} 


/* 
 * delrecord: 입력한 name을 가지는 record를 treep에서 삭제한다.
 */
Record *delrecord(Record *treep, const char *name)
{
    /* base case */
    if (treep == NULL)
        return treep; 
    int cmp = strcmp(name, treep->name);
    /* 삭제할 key가 root의 key보다 작다면 왼쪽 subtree에 위치한다. */
    if (cmp < 0)
        treep->left = delrecord(treep->left, name); 
    /* 삭제할 key가 root의 key보다 크다면 오른쪽 subtree에 위치한다. */
    else if (cmp > 0)
        treep->right = delrecord(treep->right, name); 
    /* 삭제할 key가 root의 key와 같다면 해당 노드를 삭제한다. */
    else { 
        /* 노드가 left 또는 right 하나와 연결되어 있거나 두쪽 다 연결되어 있지 않을 때 */
        if (treep->left == NULL) { 
            Record *temp = treep->right;
            free(treep);
            return temp; 
        } else if (treep->right == NULL) { 
            Record *temp = treep->left;
            free(treep); 
            return temp; 
        } 
        /* 노드가 left와 right 모두 연결되어 있을 때: 오른쪽의 subtree에서 가장 작은 값을 후계자로 만든다. */
        Record *temp = minValueNode(treep->right); 
        /* 삭제할 노드의 값을 후계자 노드의 값으로 변경한다. */ 
        treep->name = temp->name; 
        treep->age = temp->age;
        treep->address = temp->address;
        treep->phone = temp->phone;
        /* 후계자를 삭제한다. */
        treep->right = delrecord(treep->right, temp->name); 
    } 
    return treep;
}

/* 
 * lookup_name: treep에서 name을 찾아 해당 record의 정보를 출력하고 해당 record를 리턴한다.  
 * 해당하는 record가 없다면 NULL을 리턴한다.
 */
Record *lookup_name(Record *treep, const char *name)
{
    int cmp;
    if (treep == NULL)
        return NULL;
    cmp = strcmp(name, treep->name);
    if (cmp == 0)
        return treep;
    else if (cmp < 0)
        return lookup_name(treep->left, name);
    else
        return lookup_name(treep->right, name);
}

/* 
 * lookup_phone: treep에서 phone을 찾아 해당 record의 정보를 출력하고 해당 record를 리턴한다. 
 * 해당하는 record가 없다면 NULL을 리턴한다.
 */
Record *lookup_phone(Record *treep, const char *phone)
{
    int cmp;
    if (treep == NULL)
        return NULL;
    cmp = strcmp(phone, treep->phone);
    if (cmp == 0)
        return treep;
    else if (cmp < 0)
        return lookup_phone(treep->left, phone);
    else
        return lookup_phone(treep->right, phone);
}

/* 
 * apply_asc: treep에 L(left)->D(root)->R(right)의 순서로 fn을 실행한다. (inorder, 오름차순) 
 */
void apply_asc(Record *treep, void (*fn)(Record*, void*), void *arg)
{
    if (treep == NULL)
        return;
    apply_asc(treep->left, fn, arg);
    (*fn)(treep, arg);
    apply_asc(treep->right, fn, arg);
}

/* 
 * apply_desc: treep에 R(right)->D(root)->L(left)의 순서로 fn을 실행한다. (내림차순) 
 */
void apply_desc(Record *treep, void (*fn)(Record*, void*), void *arg)
{
    if (treep == NULL)
        return;
    apply_desc(treep->right, fn, arg);
    (*fn)(treep, arg);
    apply_desc(treep->left, fn, arg);
}

/* 
 * heap에서 할당된 모든 record의 저장공간을 해제 시켜준다. 
 */
void freeall(Record *treep)
{
    if (treep == NULL)
        return;
    freeall(treep->left);
    freeall(treep->right);
    free(treep);
}
