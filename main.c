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
    printf("init app over\n");
	readArticleToArray(&art);
    printf("read The_Holy_Bible over\n");
	charProcess(&art);
    printf("process char over\n");
	wordCount(&art);
    printf("count The_Holy_Bible over\n");
	sort(&art);
    printf("sort The_Holy_Bible over\n");
	run(&art);
    printf("run over\n");
	return 0;
}
