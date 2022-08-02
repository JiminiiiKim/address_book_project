#ifndef __ADDRS_H__
#define __ADDRS_H__

#include <stdio.h>
#include <stdbool.h>
#include "record.h"

/*
 * Addrs type
 */
typedef struct {
   Record *records;
} Addrs;

/*
 * Addrs를 생성하고 사용 가능한 상태로 초기화시켜준다.
 */
Addrs *Addrs_create(void);

/*
 *  Addrs에 새로운 record를 추가한다.
 */
void Addrs_add(Addrs *, const char *, int, const char *, const char *);

/*
 * 현재 Addrs에서 주어진 name에 해당하는 record를 삭제한다.
 */
void Addrs_delete(Addrs *, const char *);

/*
 * 주어진 key에 해당되는 name을 가진 record를 찾는다. 
 * address 안에 있으면 해당 record의 정보를 출력하고 true를 리턴하며, 
 * 없으면 주소록 안에 없다는 메시지와  false를 리턴한다.
 */
bool Addrs_search_name(Addrs *, const char *);

/*
 * 주어진 key에 해당되는 phone을 가진 record를 찾는다. 
 * address 안에 있으면 해당 record의 정보를 출력하고 true를 리턴하며, 
 * 없으면 주소록 안에 없다는 메시지와  false를 리턴한다.
 */
bool Addrs_search_phone(Addrs *, const char *);

/*
 * 현재 유지하고 있는 record의 갯수를 세서 리턴한다.
 */
int Addrs_count(Addrs *);

/*
 * 모든 record에 하나씩 접근하여 proc 함수를 수행한다.
 * 오름차순 또는 내림차순 중 어떤 방식으로 순회할 것인지를 선택할 수 있다.
 */
void Addrs_apply(Addrs *, void (*proc)(Record *, void *), void *, const char *);

/*
 * Addrs가 유지하고 있는 모든 record의 정보를 오름차순 또는 내림차순 정렬된 형태로 출력해주며,
 * 유지하고 있는 record의 갯수도 함께 출력한다.
 */
void Addrs_info(Addrs *, const char *);

/*
 * 동적으로 할당된 모든 데이터들의 저장공간을 해제 시켜준다.
 */
void Addrs_free(Addrs *);

#endif
