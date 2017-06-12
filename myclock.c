#include <stdio.h>
#include <time.h>

void myclock(void)
{
	while(1)
	{
		time_t t1 = time(NULL);
		struct tm* p_tm = localtime(&t1);
		int year 	= p_tm->tm_year + 1900;
		int month 	= p_tm->tm_mon + 1;
		int mday   	= p_tm->tm_mday;
		int hour	= p_tm->tm_hour;
		int min		= p_tm->tm_min;
		int sec		= p_tm->tm_sec;

		char date[32];
		sprintf(date, "%04d-%02d-%02d %02d:%02d:%02d", year, month, mday, hour, min, sec);
		printf("\r");
		printf("%s", date);
		fflush(stdout);
		usleep(500000);
	}

}

int main()
{
	myclock();
	return 0;
}

