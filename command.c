/*************************************************************************
> File Name: command.c
> Author: ZhangShibo
> Mail:453430198@qq.com
> Created Time: Mon 23 Jun 2014 05:12:31 AM PDT
************************************************************************/

#include "article.h"

int findSubstr(char *str, char *sub)
{
	int strLen, subLen, i, j;
	strLen = strlen(str);
	subLen = strlen(sub);
	for (i = 0; i <= strLen - subLen; ++i){
		for (j = 0; j < subLen; ++j){
			if (str[i + j] != sub[j]){
				break;
			}
		}
		if (j == subLen){
			return i;
		}
	}
	return -1;
}

int is_num(char *str)
{
	char numstr[100];
	char *p = str, *q = numstr;
	int sum = 0;
	while (*p != 0){
		if (*p != 32){
			*(q++) = *p;
		}
		++p;
	}
	*q = 0;
	q = numstr;
	while (*q != 0){
		if (!(*q <= '9' && *q >= '0')){
			break;
		}
		sum = sum * 10 + (*q) - 48;
		++q;
	}
	if (*q != 0)
		return -1;
	else
		return sum;
}


int command_format(char *str, char *param, int *val)
{
	int value;
	char substr_wc[3] = "wc";
	char substr_top[4] = "Top";
	char substr_search[7] = "search";
	char para_l[3] = "-l";
	char para_w[3] = "-w";
	char para_c[3] = "-c";
	char *p = str, *q;
    //忽略开头的空格
	while (*p == 32) {
        ++p;
	}
	switch (*p){
	case 'w':
        //执行统计命令
		if ((value = findSubstr(p, substr_wc)) != -1){
			if ((value = findSubstr(p + 2, para_l)) != -1){
				return 1;
			}
			if ((value = findSubstr(p + 2, para_w)) != -1){
				return 2;
			}
			if ((value = findSubstr(p + 2, para_c)) != -1){
				return 3;
			}
		}
		break;
	case 't':
        //转成T
		*p -= 32;
	case 'T':
        //执行Top N命令
		if ((value = findSubstr(p, substr_top)) != -1){
			if ((value = is_num(p + 4)) != -1){
				*val = value;
				return 4;
			}
		}
		break;
	case 's':
        //执行search word命令
		if ((value = findSubstr(p, substr_search)) != -1){
			p += 6;
			while (*p == 32 && *p != 0){
				++p;
			}
			if (*p != 0){
				strcpy(param, p);
				return 5;
			}
		}
		break;
	}
	return 0;
}

void wc(article *art, char c)
{
	switch (c)
	{
	case 'l':
		printf("Totle lines is : %d \n", (*art).length);
		break;
	case 'w':
		printf("Totle words is :%d \n", (*art).word_count);
		break;
	case 'c':
		printf("Totle charactor is :%d \n", (*art).char_count);
		break;
	}
}

void top(article *art, int n)
{
	int i;
	for (i = 0; i < n; ++i){
		printf("%10s : %10d \n", (*art).all_words[i]->word, (*art).all_words[i]->count);
	}
}

void search(article *art, char *str)
{
	int i, value;
	for (i = 0; i < (*art).length; ++i){
		if ((value = findSubstr((*art).all_lines_original[i], str)) != -1){
			printf("%d:%s\n", i + 1, (*art).all_lines_original[i]);
			continue;
		}
	}
}
