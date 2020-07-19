#include <stdio.h>    //fopen, fgets, fclose 함수가 선언된 헤더 파일
#include <stdint.h>   //uint32_t 자료형이 선언된 헤더파일
#include <winsock2.h> //ntohl 함수가 선언된 헤더파일 (윈도우 용)
#include "add-nbo.h"  //read_file이 담긴 헤더파일(자체 제작?)

int read_file(char *file_name) //파일 1개를 읽어 그 값을 nbo 에서 hbo로 변환해 반환하는 함수 (인자 = 파일 명)
{
    // uint32_t *buffer;                        //버퍼 포인터 생성 실패?
    uint32_t buffer[1];                         //버퍼
    FILE *file_stream = fopen(file_name, "rb"); //읽기 용 파일 스트림
    if (file_stream == NULL)                    //파일 읽기에 실패 할 경우, 오류 메시지 출력 및 0 반환
    {
        printf("Failed to open %s", file_name);
        return 0;
    }
    fread(buffer, sizeof(uint32_t), 1, file_stream); //파일 읽어서 buffer에 넣기
    fclose(file_stream);                             //읽기용 스트림 닫기
    return ntohl(buffer[0]);                         //버퍼의 내용 리턴
}