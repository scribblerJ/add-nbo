#include <stdio.h>    //fopen, fgets, fclose 함수가 선언된 헤더 파일
#include <stdint.h>   //uint32_t 자료형이 선언된 헤더파일
#include <winsock2.h> //ntohl 함수가 선언된 헤더파일 (윈도우 용)
#define FILE_NUM 2    //읽어들일 파일의 수
/*
# = 전처리기에게 컴파일 수행하기 전 이하 내용을 우선 처리하라는 표시
include = 전처리 내용?디렉토리 이름?
헤더파일 = 확장자 .h를 갖는 파일(라이브러리?)
*/

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
    /*
    fread(ptr, size, count, steram) = 읽어들인 count개의 원소를 갖는 ptr이 가리키는 배열을 stream이 가리키는 파일에서 읽는다.
    ptr = size * count의 크기를 갖는 배열을 가리키는 포인터
    size = 읽어들일 원소의 크기
    count = 읽어들일 원소의 갯수
    stream = 데이터를 입력받을 FILE 객체를 가리키는 포인터)
    리턴 값 = 읽어 드린 원소의 개수가 size_t형으로 리턴(정수 타입)
    만일 읽어들인 원소의 개수가 count와 다르거나, End OF File에 도달하면 오류 발생
    ferror 혹은 feof 함수를 이용해 오류 종류 확인 가능
    */
    fclose(file_stream);     //읽기용 스트림 닫기
    return ntohl(buffer[0]); //버퍼의 내용 리턴
}
int main(int argc, char *argv[])
/*
main = 운영체제에 의해 맨 처음 호출되고 맨 나중에 종료되는 함수
출력type 함수명 (입력type)

argument = 함수호출시 넘겨주는 값 (전달인자)
parameter = 함수의 힙에 저장되는 매개변수 (전달인자가 저장되는 곳) 

실행파일 호출과 함께 넣어주면 됨
ex) a.exe first_arg second_arg

argc = 메인함수에 전달되는 정보의 갯수
argv = 메인함수에 전달되는 정보 (문자열의 배열)
argv[0] = 실행경로 (ex. HelloWorld.exe)
argv[n] = n 번쨰 
*/
{
    int i;                    //반복문에 사용될 변수
    uint32_t nbo[FILE_NUM];   //각 파일 내 값의 hbo 변환 값
    uint32_t sum = 0;         //전체 파일 내 값의 hbo 변환값들의 총합
    if (argc != FILE_NUM + 1) //함수 호출 시 정해진 인자(=FILE_NUM)을 주지 않은 경우, 오류 메시지 출력 및 -1 반환
    {
        printf("syntax : add-nbo <file1> <file2>\nsample : add-nbo a.bin c.bin\n");
        return -1;
    }

    for (int i = 0; i < FILE_NUM; i++) //각 파일을 한번씩 읽어 옴
    {
        nbo[i] = read_file(argv[i + 1]); //read_file 호출(인자 = 파일 명)
        if (nbo[i] == 0)                 //파일 읽기 실패 시, 함수 중지 및 -1 반환
        {
            return -1;
        }
    }
    for (i = 0; i < FILE_NUM; i++) //각 파일 내 값의 hbo 변환 값 및 연산자 출력
    {
        printf("%d(0x%x)", nbo[i], nbo[i]);
        if (i == FILE_NUM - 1) // 마지막 hbo 변환 값 출력 후 등호 출력
        {
            printf(" = ");
        }
        else
        {
            printf(" + ");
        }
        sum += nbo[i]; //전체 파일 내 값의 hbo 변환값 등을 점층적으로 더함
    }
    printf("%d(0x%x)", sum, sum); //전체 파일 내 값의 hbo 변환값들의 총합 출력
    return 0;
}