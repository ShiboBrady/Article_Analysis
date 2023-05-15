/*************************************************************************
> File Name: pretreatment.c
> Author: ZhangShibo
> Mail:453430198@qq.com
> Created Time: Mon 23 Jun 2014 02:23:17 AM PDT
************************************************************************/

#include "article.h"

void initArt(article *art, char *name)
{
	art->length = 0;
	art->word_count = 0;
	art->uni_word = 0;
	art->char_count = 0;
    art->all_words = malloc(sizeof(words) * WORD_MAX_NUM);
    art->all_lines_original = malloc(LINE_MAX_LENGTH * LINE_MAX_NUM);
    art->all_lines = malloc(LINE_MAX_LENGTH * LINE_MAX_NUM);
	strcpy(art->articleName, name);
}

void readArticleToArray(article *art)
{
	char *line_temp, *line;
	int len;
	FILE *fp;
	if (!(fp = fopen(art->articleName, "rb"))){
		perror("Open file error : ");
		exit(1);
	}
	while (!feof(fp)){
		line_temp = (char*)malloc(LINE_MAX_LENGTH * sizeof(char));
		fgets(line_temp, LINE_MAX_LENGTH, fp);
		line = (char*)malloc((strlen(line_temp) + 2) * sizeof(char));
		strcpy(line, line_temp);
		art->all_lines_original[art->length++] = line;
		free(line_temp);
	}
	fclose(fp);
}

void charProcess1(article *art)
{
	char ch, *line, *line_temp;
	int i = 0;
	FILE *fp_read, *fp_write;
	fp_read = fopen(art->articleName, "rb");
	fp_write = fopen("temp.txt", "wb");
	while (!feof(fp_read)){
		ch = fgetc(fp_read);
		if (ispunct(ch)){
			fputc(32, fp_write);
		}
		else if (isupper(ch)){
			fputc(ch + 32, fp_write);
		}
		else{
			fputc(ch, fp_write);
		}
		++art->char_count;
	}
	fclose(fp_read);
	fclose(fp_write);
	fp_read = fopen("temp.txt", "rb");
	while (!feof(fp_read)){
		line_temp = (char*)malloc(LINE_MAX_LENGTH * sizeof(char));
		fgets(line_temp, LINE_MAX_LENGTH, fp_read);
		line = (char*)malloc((strlen(line_temp) + 2) * sizeof(char));
		strcpy(line, line_temp);
		art->all_lines[i++] = line;
		free(line_temp);
	}
	fclose(fp_read);
}

void charProcess(article *art)
{
	char *temp, *line;
	int i, j, len;
	for (i = 0; i < art->length; ++i){
		temp = art->all_lines_original[i];
		len = strlen(temp);
		line = (char*)malloc((len + 1) * sizeof(char));
		art->all_lines[i] = line;
		for (j = 0; j < len; ++j){
			if (ispunct(temp[j]) || temp[j] == '\r' || temp[j] == '\n'){
				line[j] = 32;
			}
			else if (isupper(temp[j])){
				line[j] = temp[j] + 32;
			}
			else{
				line[j] = temp[j];
			}
			++art->char_count;
		}
		line[j] = '\0';
	}
}

int insertWord(char *word, article *art)
{
	int i;
	for (i = 0; i < art->uni_word; ++i){
		if (strcmp(word, art->all_words[i]->word) == 0){
			++art->all_words[i]->count;
			return 0;
		}
	}
	words *new_word = (words*)malloc(sizeof(words));
	strcpy(new_word->word, word);
	new_word->count = 1;
	art->all_words[i] = new_word;
	return 1;
}

void wordCount1(article *art)
{
	char word[WORD_MAX_LENGTH];
	FILE *fp_read;
	fp_read = fopen("temp.txt", "rb");
	while (!feof(fp_read)){
		fscanf(fp_read, "%s", word);
		if (insertWord(word, art)){
			art->uni_word++;
		}
		art->word_count++;
	}
}

void wordCount(article *art)
{
	char word[WORD_MAX_LENGTH];
	int i, pos;
	char *temp;
	for (i = 0; i < art->length; ++i){
		pos = 0;
		temp = art->all_lines[i];
		while(*temp == 32){
			++temp;
		}
		while (sscanf(temp + pos, "%s", word) == 1){
			if (insertWord(word, art)){
				art->uni_word++;
			}
			art->word_count++;
			pos += strlen(word) + 1;
			while(*(temp + pos) == 32){
				++pos;
			}
		}
	}
}

int partable(words **a, int n)
{
	int low = 0, high = n - 1;
	words *temp = a[low];
	while (low < high){
		while (low < high && a[high]->count <= temp->count){
			--high;
		}
		if (low < high){
			a[low] = a[high];
		}
		while (low < high && a[low]->count > temp->count){
			++low;
		}
		if (low < high){
			a[high] = a[low];
		}
	}
	a[high] = temp;
	return high;
}

void quickSort(words **a, int n)
{
	int pos;
	if (n > 0){
		pos = partable(a, n);
		quickSort(a, pos);
		quickSort(a + pos + 1, n - pos - 1);
	}
}

void sort(article *art)
{
	quickSort(art->all_words, art->uni_word);
}
