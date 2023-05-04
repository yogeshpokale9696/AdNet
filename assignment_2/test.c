#include<stdio.h>

#include<time.h>
int main(){
	time_t t;
	t = time(NULL);
	struct tm tm = *localtime(&t);
	
	printf("current Date : %d-%d-%d" ,tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
	printf("\ncurrent Time : %d-%d-%d" ,tm.tm_hour,tm.tm_min,tm.tm_sec);


	return 0;
}
