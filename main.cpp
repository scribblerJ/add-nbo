#include <stdio.h>   //printf 함수가 선언된 헤더 파일
#include <stdint.h>  //uint32_t 자료형이 선언된 헤더파일
#include "add-nbo.h" //read_file이 담긴 헤더파일(자체 제작?)

int main(int argc, char *argv[]) //argc = 메인함수에 전달되는 정보의 갯수, argv = 메인함수에 전달되는 정보 (문자열의 배열)
{
    if (argc != 3) //함수 호출 시 정해진 인자 (3개)를 주지 않은 경우, 오류 메시지 출력 및 -1 반환
    {
        printf("syntax : add-nbo <file1> <file2>\nsample : add-nbo a.bin c.bin\n");
        return -1;
    }
    uint32_t hbo_1 = read_file(argv[1]); //첫번쨰 파일 내 값의 hbo 변환값
    uint32_t hbo_2 = read_file(argv[2]); //두번쨰 파일 내 값의 hbo 변환값

    printf("%d(0x%x) + %d(0x%x) =%d(0x%x)", hbo_1, hbo_1, hbo_2, hbo_2, hbo_1 + hbo_2, hbo_1 + hbo_2); //결과 출력
    return 0;
}