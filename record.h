#ifndef __RECORD_H__
#define __RECORD_H__
 
/*
 * Record type
 */
typedef struct Record Record;
struct Record {
    char *name;
    int age;
    char *address;
    char *phone;
    Record *left; /* 자신보다 더 작은 노드 가리킴 */
    Record *right; /* 자신보다 더 큰 노드 가리킴 */
};

#define getname(re)		((re)->name)
#define getage(re)      ((re)->age)
#define getaddress(re)      ((re)->address)
#define getphone(re)    ((re)->phone)

/* 
 * newrecord: name, age, address, phone을 담고 있는 새로운 record를 생성한다. 
 */
Record *newrecord(const char *, int, const char *, const char *);

/* 
 * addrecord: treep에 newp를 추가하고 treep를 리턴한다. 
 * 만약 newp가 treep에 없다면 오류 메시지를 출력하고 출력하고 newp의 기억 공간을 해제시킨다.
 */
Record *addrecord(Record *, Record *);

/* 
 * delrecord:입력한 name을 가지는 record를 treep에서 삭제한다.
 */
Record *delrecord(Record *, const char *);

/* 
 * lookup_name: treep에서 name을 찾아 해당 record의 정보를 출력하고 해당 record를 리턴한다.  
 * 해당하는 record가 없다면 NULL을 리턴한다.
 */
Record *lookup_name(Record *, const char *);

/* 
 * lookup_phone: treep에서 phone을 찾아 해당 record의 정보를 출력하고 해당 record를 리턴한다. 
 * 해당하는 record가 없다면 NULL을 리턴한다.
 */
Record *lookup_phone(Record *, const char *);

/* 
 * apply_asc: treep에 L(left)->D(root)->R(right)의 순서로 fn을 실행한다. (inorder, 오름차순) 
 */
void apply_asc(Record *, void (*fn)(Record*, void*), void *);

/* 
 * apply_desc: treep에 R(right)->D(root)->L(left)의 순서로 fn을 실행한다. (내림차순) 
 */
void apply_desc(Record *, void (*fn)(Record*, void*), void *);

/* 
 * freeall: heap으로부터 할당된 모든 record의 저장 공간을 해제시킨다. 
 */
void freeall(Record *);

#endif
