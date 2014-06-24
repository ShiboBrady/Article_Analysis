/*************************************************************************
> File Name: main.c
> Author: ZhangShibo
> Mail:453430198@qq.com
> Created Time: Mon 23 Jun 2014 05:27:37 AM PDT
************************************************************************/

#include "article.h"

int main()
{
	article art;
	initArt(&art, "The_Holy_Bible.txt");
	readArticleToArray(&art);
	charProcess(&art);
	wordCount(&art);
	sort(&art);
	run(&art);
	return 0;
}
