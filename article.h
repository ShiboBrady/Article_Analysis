/*************************************************************************
> File Name: article.h
> Author: ZhangShibo
> Mail:453430198@qq.com
> Created Time: Mon 23 Jun 2014 02:08:13 AM PDT
************************************************************************/

#ifndef ARTICLE_H
#define ARTICLE_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#define WORD_MAX_NUM 1000000
#define LINE_MAX_NUM 100000
#define	WORD_MAX_LENGTH 20
#define LINE_MAX_LENGTH 1000
typedef struct Words
{
	char word[WORD_MAX_LENGTH];
	int count;
}words;

typedef struct Article
{
	long word_count;
	long uni_word;
	long char_count;
	long length;
	char articleName[300];
	words **all_words;
	char **all_lines_original;
	char **all_lines;
}article;

void run(article *art);

void initArt(article *art, char *name);

void readArticleToArray(article *art);

void charProcess(article *art);

void wordCount(article *art);

void sort(article *art);

int command_format(char *str, char *param, int *val);

void wc(article *art, char c);

void top(article *art, int n);

void search(article *art, char *str);
#endif
