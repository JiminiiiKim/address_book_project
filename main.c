#include <stdio.h>
#include <stdlib.h>
#include "addrs.h"
#include "memcheck.h"

/*
 * printrecord: arg에 사용된 형식으로 record를 출력한다.
 */
void printrecord(Record *p, void *arg)
{
    printf((char *)arg, getname(p), getage(p), getaddress(p), getphone(p));
}

int main()
{
    Addrs *addrs = Addrs_create();
    Addrs_add(addrs, "jimin", 26, "Yecheon, Gyeongsangbuk-do", "010-5341-4218");
    Addrs_add(addrs, "subin", 22, "Seoul", "010-8911-1299");
    Addrs_add(addrs, "gyomin", 20, "Busan", "010-3465-4134");
    printf("print all record for descending...\n");
    Addrs_info(addrs, "desc");
    printf("\n");
    
    Addrs_add(addrs, "bomi", 24, "Haenam, Jeollanam-do", "010-3745-1253");
    Addrs_add(addrs, "minju", 24, "Jeonju, Jeollabuk-do", "010-4752-3641");
    printf("print all record for ascending...\n");
    Addrs_info(addrs, "asc");
    printf("\n");
    
    Addrs_delete(addrs, "jimin");
    Addrs_add(addrs, "taeho", 28, "Seoul", "010-1423-1253");
    Addrs_add(addrs, "taeho", 28, "Seoul", "010-1423-1252");
    Addrs_add(addrs, "inae", 25, "Daejeon", "010-1274-3476");
    printf("print all record after delete jimin...\n");
    Addrs_info(addrs, "asc");
    printf("\n");
    
    printf("print all record using printrecord...\n");
    Addrs_apply(addrs, printrecord, "%s %d %s %s\n", "asc");
    printf("\n");
    
    printf("search for name bomi in address...\n");
    Addrs_search_name(addrs, "bomi");
    printf("\n");
    
    Addrs_add(addrs, "yumi", 31, "Busan", "010-2346-3645");
    Addrs_add(addrs, "eunjung", 28, "Andong, Gyeongsangbuk-do", "010-2531-2346");
    printf("print all record for ascending...\n");
    Addrs_info(addrs, "desc");
    printf("\n");
    
    Addrs_free(addrs);
    print_memory_leaks();
}
