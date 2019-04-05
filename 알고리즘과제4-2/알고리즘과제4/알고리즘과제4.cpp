#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<time.h>

typedef struct {
	char *ip;
	char *time;
	char *url;
	char *status;
}webLog ;
webLog web_data[16000];

typedef char str[4];
str month[12] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
str month_rank[12] = { "1","2","3","4","5","6","7","8","9","10","11","12" };

char *cont = NULL;
char buffer[1000];
int cnt = 0;

int CompareByTime(const void *v1, const void *v2)//Time으로 비교 함수
{
	const webLog *m1 = (const webLog *)v1;
	const webLog *m2 = (const webLog *)v2;
	char *time1, *time2;
	char *time_token1[6], *time_token2[6]; //0.일 1.월 2.년 3.시 4.분 5.초 

	time1 = _strdup(m1->time);
	time2 = _strdup(m2->time);
	time_token1[0] = strtok_s(time1, "/:", &cont);
	for (int i = 1; i <= 5; i++)
		time_token1[i] = strtok_s(cont, "/:", &cont);

	time2 = _strdup(m2->time);
	time_token2[0] = strtok_s(time2, "/:", &cont);
	for (int i = 1; i <= 5; i++)
		time_token2[i] = strtok_s(cont, "/:", &cont);
	for (int i = 0; i <= 11; i++)
	{
		if (strcmp(time_token1[1], _strdup(month[i])) == 0)	
			time_token1[1] = _strdup(month_rank[i]);
		if (strcmp(time_token2[1], _strdup(month[i])) == 0)
			time_token2[1] = _strdup(month_rank[i]);
	}
	for (int i = 2; i >= 0; i--)
	{
		if (strcmp(time_token1[i], time_token2[i]) != 0)
			return strcmp(time_token1[i], time_token2[i]);
	}
		
	for (int i = 3; i <= 5; i++)	//시->분->초
	{
		if (strcmp(time_token1[i], time_token2[i]) != 0)	
			return strcmp(time_token1[i], time_token2[i]);
	}

	return strcmp(time_token1[5], time_token2[5]);
}

void sort_t()
{
	qsort(web_data, cnt, sizeof(webLog), CompareByTime);
	for (int i = 0; i < cnt; i++)
	{
		printf("%s\n", web_data[i].time);
		printf("\tIP    :%s\n", web_data[i].ip);
		printf("\tURL   :%s\n", web_data[i].url);
		printf("\tStatus:%s\n", web_data[i].status);
	}
}

int CompareByIP(const void *v1, const void *v2)//IP로 비교 함수
{
	const webLog *m1 = (const webLog *)v1;
	const webLog *m2 = (const webLog *)v2;
	if (strcmp(m1->ip, m2->ip) ==0)
		return CompareByTime(m1, m2);
	return  strcmp(m1->ip, m2->ip);
}

void sort_ip()
{
	qsort(web_data, cnt, sizeof(webLog), CompareByIP);
	for (int i = 0; i < cnt; i++)
	{	
		printf("%s ", web_data[i].ip);
		printf("\tTime    :%s\n", web_data[i].time);
		printf("\tURL   :%s\n", web_data[i].url);
		printf("\tStatus:%s\n", web_data[i].status);
	}
}

int main()
{
	FILE *fp;
	char *token[4];

	fopen_s(&fp,"webLog.csv", "r");
	if (fp == NULL)
	{
		printf("webLog.csv 파일 오픈 불가\n");    //화면에 오류 표시
		fclose(fp);
	}
	
	fgets(buffer, sizeof(buffer), fp);
	while (!feof(fp)) {
		fgets(buffer, sizeof(buffer), fp);
		token[0] = strtok_s(buffer, ",", &cont);
		for (int i = 1; i <= 3; i++)
			token[i] = strtok_s(cont, ",", &cont);
	
		web_data[cnt].ip = _strdup(token[0]);
		web_data[cnt].time = _strdup(token[1]);
		web_data[cnt].url = _strdup(token[2]);
		web_data[cnt++].status = _strdup(token[3]); 
		
	}
	printf("============== 시간순============\n");
	sort_t();
	printf("==============  IP순 ============\n");
	sort_ip();
	fclose(fp);
	return 0;
}




