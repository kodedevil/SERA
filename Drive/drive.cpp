#include<unistd.h>
#include<sys/syscall.h>
#include<stdio.h>
#include <termios.h>
#include <stdlib.h>

#define PATH  "/home/pi/SERA/Pipes/p_serial"
#define COMPASS "/home/pi/SERA/Pipes/p_compass"

void serial(char input);
char getch(void);
int angle(void);

int main ()
{
	while(1){
		char input = getch();
		serial(input);
	}

    return (0);
}

int angle(){
	FILE* fp;
	char readbuf[10];
	int angle;
	fp = fopen(COMPASS, "r");
	fgets(readbuf, 10, fp);
	fclose(fp);

	angle = atoi(readbuf);
	return angle;
}

void serial(char input)
{
	FILE* fp;
	fp = fopen(PATH, "w");
	fputs(&input, fp);
	fclose(fp);
}

char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}
