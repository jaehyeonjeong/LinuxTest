//표준 입출력 함수를 이용해서 파일을 복사하는 코드를 작성
//여기에서는 출력 방향을 정하는 함수인 fprintf()함수와 표준에서를 이용해서 지정한다.
#include <stdio.h> //표준 입출력 함수를 위한 헤더 파일 

int main(int argc, char** argv)
{
	int n;
	FILE *in, *out;
	char buf[BUFSIZ];

	//명령행 인수로 복사할 파일명이 없는 경우에 에러를 출력하고 종료한다.
	if(argc != 3){
		fprintf(stderr, "Usage : fcopy file1 file2\n");
		return -1;
	}
	//입출력을 위한 두 개의 스트림을 fopen() 함수를 이용해서 각각 연다.
	//복사의 원본이 되는 파일을 읽기 모드로 연다.
	if((in = fopen(argv[1], "r")) == NULL){ //읽은 파일은 r옵션을 사용하여 읽기 모드로 열었고,
		perror(argv[1]);
		return -1;
	}

	//복사할 결과 파일을 쓰기 모드(새로운 파일 생성 | 기존에 파일 내용 지움)로 연다.
	if((out = fopen(argv[2], "w")) == NULL){ //쓸 파일을 w옵션을 사용하여 쓰기 모드로 열었다.
		perror(argv[2]);
		return -1;
	}

	//원본 파일에서 파일 내용을 읽어서 복사할 파일에 쓴다.
	while((n = fread(buf, sizeof(char), BUFSIZ, in)) > 0) 
		//fread() 함수를 사용하여 첫번째 스트림으로부터 데이터를 읽고, 
		fwrite(buf, sizeof(char), n, out);
		//fwrite() 함수를 사용하여 두번째 스트림에 읽은 데이터를 쓴다.
		//이 작업을 파일의 씉에 도달할대까지 반복한다.
		//복사가 완료되면 flclose()함수를 이용하여

	//열린 파일들을 닫는다.
	fclose(out);
	fclose(in);

	return 0;
}
