/*************************************************************************
> File Name: run.c
> Author: ZhangShibo
> Mail:453430198@qq.com
> Created Time: Mon 23 Jun 2014 11:03:51 AM PDT
************************************************************************/

#include "article.h"

void run(article *art)
{
	char cmd[100], param[100];
	int k, value;
	printf("Please input command: [eg: wc -l; Top 5; search xxx]\n");
	while (fflush(stdin), gets(cmd) != NULL){
		k = command_format(cmd, param, &value);
		switch (k){
		case 1:
			wc(art, 'l');
			break;
		case 2:
			wc(art, 'w');
			break;
		case 3:
			wc(art, 'c');
			break;
		case 4:
			top(art, value);
			break;
		case 5:
			search(art, param);
			break;
		case 0:
			printf("Input wrong, please try again!\n");

		}
		printf("Please input command \n:");
	}
}
