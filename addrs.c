#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "addrs.h"
#include "memcheck.h"
/*
 * Addrs를 생성하고 사용 가능한 상태로 초기화시켜준다.
 */
Addrs *Addrs_create(void)
{
    Addrs *a = (Addrs *)malloc(sizeof(Addrs));
    if (a == NULL) {
        fprintf(stderr, "No more memory to create addrs.\n");
        exit(1);
    }
    a->records = NULL;
    return a;
}

/*
 * Addrs에 새로운 record를 추가한다.
 */
void Addrs_add(Addrs *addrs, const char *name, int age, const char *address, const char *phone)
{
    addrs->records = addrecord(addrs->records, newrecord(name, age, address, phone));
}

/*
 * 현재 Addrs에서 주어진 name에 해당하는 record를 삭제한다.
 */
void Addrs_delete(Addrs *addrs, const char *name) 
{
    addrs->records = delrecord(addrs->records, (char *)name);
}   

/*
 * 주어진 name을 가진 record를 찾는다. 
 * address 안에 있으면 해당 record의 정보를 출력하고 true를 리턴하며, 
 * 없으면 주소록 안에 없다는 메시지와 false를 리턴한다.
 */
bool Addrs_search_name(Addrs *addrs, const char *name)
{
    Record *p = lookup_name(addrs->records, (char *)name);
    if (p == NULL) {
        printf("There is not %s in address.\n", (char *)name);
        return false;
    }
    else {
        printf("Search result <Name : %s Age : %d Address : %s Phone : %s>\n", p->name, p->age, p->address, p->phone);
        return true;
    }
}

/*
 * 주어진 phone을 가진 record를 찾는다. 
 * address 안에 있으면 해당 record의 정보를 출력하고 true를 리턴하며, 
 * 없으면 주소록 안에 없다는 메시지와 false를 리턴한다.
 */
bool Addrs_search_phone(Addrs *addrs, const char *phone)
{
    Record *p = lookup_phone(addrs->records, (char *)phone);
    if (p == NULL) {
        printf("There is not %s in address.\n", (char *)phone);
        return false;
    }
    else {
        printf("Search result <Name : %s Age : %d Address : %s Phone : %s>\n", p->name, p->age, p->address, p->phone);
        return true;
    }
}

/*
 * 모든 record에 하나씩 접근하여 proc 함수를 수행한다.
 * 오름차순 또는 내림차순 중 어떤 방식으로 순회할 것인지를 선택할 수 있다.
 */
void Addrs_apply(Addrs *addrs, void (*proc)(Record *, void *), void *arg, const char *choice)
{
    int cmp = strcmp("asc", (char *)choice);
    if (cmp == 0)
        apply_asc(addrs->records, proc, arg);
    else {
        cmp = strcmp("desc", (char *)choice);
        if (cmp == 0)
            apply_desc(addrs->records, proc, arg);
        else
            fprintf(stderr, "Addrs_apply: %s is not allowed except for asc or desc.\n", (char *)choice);
    }
}
/*
 * record의 정보를 순서대로 출력한다.
 */
static void printre_and_count(Record *re, void *count)
{
    printf("Name : %s Age : %d Address : %s Phone : %s\n", re->name, re->age, re->address, re->phone);
    (*(int *)count)++;
}

/*
 * 현재 유지하고 있는 record의 갯수를 조회한다.
 */
static void check_count(Record *re, void *count)
{
    (*(int *)count)++;
}

/*
 * 현재 유지하고 있는 record의 갯수를 세서 리턴한다.
 */
int Addrs_count(Addrs *addrs)
{
    int count = 0;
    apply_asc(addrs->records, check_count, &count);
    return count;
}


/*
 * Addrs가 유지하고 있는 모든 record의 정보를 오름차순 또는 내림차순 정렬된 형태로 출력해주며,
 * 유지하고 있는 record의 갯수도 함께 출력한다.
 */
void Addrs_info(Addrs *addrs, const char *choice)
{
    int count = 0;
    int cmp = strcmp("asc", (char *)choice);
    if (cmp == 0) {
        apply_asc(addrs->records, (void (*)(Record *, void *))printre_and_count, &count);
        printf("There are %d records.\n", count);
    }
    else {
        cmp = strcmp("desc", (char *)choice);
        if (cmp == 0) {
            apply_desc(addrs->records, (void (*)(Record *, void *))printre_and_count, &count);
            printf("There are %d records.\n", count);
        }
        else
            fprintf(stderr, "Addrs_info : %s is not allowed except for asc or desc.\n", (char *)choice);
    }
}

/*
 * 동적으로 할당된 모든 데이터들의 저장공간을 해제 시켜준다.
 */
void Addrs_free(Addrs *addrs)
{
    freeall(addrs->records);
    free(addrs);
}
