# address_book_project
주소록의 주요한 기능 중에는 정렬된 순의 record를 출력과 빈번한 검색이 있다. 
또, 사용자가 내림차순을 원할지 오름차순을 원할지는 상황에 따라 다르기 때문에 요구가 들어올 때 정렬하는 것이 아닌 정렬된 상태로 데이터 구조가 유지되길 원했고 이에 이진 탐색 트리(BST)를 사용하였다. 

## 소스파일 구성
main : 주소록.

record : 주소록 안의 데이터를 관리하며 데이터 구조에 맞게 주소록의 기능을 구현함.

addrs : 주소록의 데이터를 담는 틀을 가리키며 record의 상위 모듈로 주소록 전체 데이터의 관점에서 데이터 구조에 맞게 주소록의 기능을 구현함.

## 주소록 (main) 사용 설명서
한 사람의 이름, 나이, 주소, 전화번호를 저장할 수 있다.

기능들은 다음과 같다.

1) 주소록 생성
Addrs *addrs = Addrs_create() : addrs의 자리에는 사용할 주소록의 이름 작성한다.

2) 주소록 추가
Addrs_add(addrs, "1번", 2번, "3번", "4번")

1번 : 새로운 record의 이름

2번 : 새로운 record의 나이

3번 : 새로운 record의 주소

4번 : 새로운 record의 전화번호

추가하려는 record가 주소록 안에 있는 record의 이름 또는 전화번호가 중복된다면 추가가 되지 않는다.

3) 주소록 삭제
Addrs_delete(addrs, "1번")

1번 : 주소록에서 삭제할 record의 이름

4) 주소록 안의 이름 검색
Addrs_search_name(addrs, "1번")

1번 : 주소록에서 검색할 record의 이름

5) 주소록 안의 전화번호 검색
Addrs_search_phone(addrs, "1번")

1번 : 주소록에서 검색할 record의 전화번호

6) 주소록의 record 순차적 실행
Addrs_apply(addrs, 1번, 2번, "3번")

* 현재 사용할 수 있는 함수는 printrecord가 있음.
* 
1번 : 사용할 함수명, 함수는 void (Record *, void *)형

2번 : 함수 내에 사용할 void 포인터

3번 : 순차적으로 접근할 방법 지정,

asc을 입력하면 오름차순으로, desc을 입력하면 내림차순으로 접근

7) 주소록 안의 record 갯수
Addrs_count(addrs)

결과형이 정수이므로 출력해서 사용

8) 주소록 정보 출력
Addrs_info(addrs, "1번")

1번 : 오름차순 출력을 원한다면 asc을,

내림차순 출력을 원한다면 dsec을 입력

10) 주소록 해제
Addrs_free(addrs) : 메모리를 해제한다.

특정 record의 이름, 나이, 주소, 전화번호를 출력하고자 하면
getname(record) getage(record) getaddress(record) getphone(record)를 사용하면 된다.
