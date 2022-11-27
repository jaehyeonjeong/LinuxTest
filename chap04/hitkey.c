/*fcntl()함수는 일반 파일이나 파일 디스크럽터와 관련된 연산을 위해 사용되는데, 
 이미 열린 파일의 성질을 바꿀 수 있다. 함수가 성공적으로 호출되면 두 번째 인자(cmd)의 값에 따라
 서로 다른 결과를 반환하고 실패하면 -1을 반환한다.*/

/*fcntl() 함수는 현재 파일 디스크럽터의 복사, 파일 디스크럽터 값 설정/획득
 파일의 상태 플래그 값 설정/획득, 비동기 입출력 소유권 설정/획득, 레코드 잠금 설정/획득
 등의 다양한 기능을 제공한다.*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

/*kbhit()함수는 키보드의 입력을 감지하는 함수인데 유닉스에서는 fcntl()함수와 터미널 제어를 이용해서 구현할 수 있다.*/
/*키보드 입력을 처리하기 위한 함수*/
int kbhit(void)
{
	struct termios oldt, newt;					/*터미널에 대한 구조체*/
	int ch, oldf;

	tcgetattr(0, &oldt);						/*현재 터미널에 설정된 정보를 가져온다.*/
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);			/*정규 모드 입력과 에코를 해제한다.*/
	tcsetattr(0, TCSANOW, &newt);				/*새로운 값으로 터미널을 설정한다.*/
	oldf = fcntl(0, F_GETFL, 0);				/*파일 테이블에 저장되어 있는 파일 상태 플래그를 반환한다.*/
	fcntl(0, F_SETFL, oldf | O_NONBLOCK);		/*입력을 논블로킹 모드로 설정한다.*/
	ch = getchar();								/*문자 버퍼를 입력받고 화면에 출력하지 않는다.*/

	tcsetattr(0, TCSANOW, &oldt);				/*기존의 값으로 터미널의 속성을 바로 적용한다.*/
	fcntl(0, F_SETFL, oldf);					/*파일 상태 플래그를 설정(O_APPEND, O_NONBLOCK, O_SYNC등)한다.*/

	if(ch != EOF){								/*문자 버퍼가 파일이 끝날때까지*/
		ungetc(ch, stdin);						/*앞에서 읽으며 꺼낸 문자를 다시 넣는다.*/
		return 1;
	}

	return 0;
}

int main(int argc, char** argv[1])
{
	int i = 0;

	for(i = 0; ; i++){
		if(kbhit()){							/*키보드가 눌러졌는지 확인한다.*/
			switch(getchar()){					/*문자를 읽는다.*/
				case 'q':						/*읽은 문자가 q이면 종료한다.*/
					goto END;
					break;
			};
		}
		printf("%20d\t\t\r", i);				/*현재 카운터한 숫자를 출력한다.*/
		usleep(1000000);							/*100밀리초 동안 잠시 쉰다.*/
	}
END:
	printf("Good Bye!\n");
	return 0;
}



