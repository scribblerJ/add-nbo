CC = g++ #컴파일러는 g++로 설정
CFLAGS = -W -Wall#에러 메시지 알림
TARGET = add-nbo #최종 결과물 이름 지정
OBJS = main.o read_file.o #종속항목 변수

all: $(TARGET) #최종적으로 만들고 싶은 결과물

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lws2_32
#$@ 현재 타겟의 이름
#$^ 현재 타겟의 종속항목 리스트

# clean:# 불필요한 부산물(ex. 객체 파일)삭제 실패?
# 	rm  -f *.o $(TARGET)