#include <unistd.h>				//유닉스 표준 시스템 콜을 위한 헤더 파일
#include <fcntl.h>			
#include <stdio.h>				//perror() 함수
#include <sys/stat.h>
#include <sys/types.h>

//애플리케이션을 실행하면 명령행 인수로 2개의 파일명을 입력받고 2개의 파일을 열거나
//생성한 후 첫번째 파일에서 데이터를 읽어서 두 번째 파일로 쓰면 된다.

int main(int argc, char** argv)
{
	int n, in, out;
	char buf[1024];
	//명령행 인수로 복사할 파일명이 없는 경우에 에러를 출력하고 종료한다.
	if(argc < 3){
		write(2, "Usage : copy file1 file2\n", 25);	//숫자 2는 표준 에러
		//출력을 할 때 C언어에서 표준 입출력 라이브러리를 이용하는 경우에 printf() 함수를 사용할 수 있겠지만,
		//저수준 입출력만을 이용하는 경우에는 write()함수를 사용한다.
		//에러를 출력하고 싶은 경우에 모니터와 연결된 표준에러가 2번이므로 write()시 첫 번째 인자의 값을 '2'로 지정
		return -1;
	}
	//두 개의 파일을 open()함수를 이용해서 따로 연다.
	//복사의 원본이 되는 파일을 읽기 모드로 연다.
	if((in = open(argv[1], O_RDONLY)) < 0){	//읽어 들일 파일은 O_RDONLY옵션을 사용하였고
		perror(argv[1]);
		return -1;
	}

	//복사할 결과 파일을 쓰기 모드(새로운 파일 생성 | 기존에 파일 내용 지움)로 연다.
	if((out = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR)) < 0){
		//쓸 파일은 O_WRONLY로 열었다.
		//쓸 파일의 경우에는 파일이 없는 경우도 있기 때문에 파일을 새로 생성할 수 있도록 O_CREAT 를 사용 
		//기존의 파일이 있는 경우에는 기존에 내용을 추가하는 것이 아니라 
		//새로운 내용으로 덮어야 하기 위해 O_TRUNC를 사용한다.

		perror(argv[2]);
		return -1;
	}
	
	//원본 파일의 내용을 읽어서 복사할 파일에 쓴다.
	while((n = read(in, buf, sizeof(buf))) > 0) //read() 함수를 이용해서 데이터를 읽고
		write(out, buf, n);	//두 번째 파일에는 write()함수를 이용해서 읽은 데이터를 쓰는데,
		//파일의 끝까지 작업을 반복한다.
		//복사 작업이 완료되면 close()함수를 이용해서 두 개의 파일을 모두 닫는다.

	//열린 파일들을 닫는다.
	close(out);
	close(in);

	//프로그램의 정상 종료 시 0을 반환한다.
	return 0;
}


