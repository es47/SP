#include "apue.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int out_num, num, flag;
char *seg[100], *out_seg[100];

int insert(int i);
int newline();
int proper(int i);
int upper(int i);
int lower(int i);
int reverse(int i);

int main(int argc, char *argv[])
{
	char buf[MAXLINE];
	int in_fd, out_fd, i, count;
	FILE *in_fp, *out_fp;
	char *ptr, dev[] = "<>";
	in_fd = open (argv[1], O_RDONLY, 0644);
	out_fd = open ("test.out", O_RDWR | O_CREAT);
	if (in_fd < 0)
		err_quit("Open %s Error!\n", argv[1]);
	if (out_fd < 0)
		err_quit("Open test.out Error!\n");
	in_fp = fopen(argv[1], "r");
	out_fp = fopen("test.out", "w");
	count = 0;
	while (fgets(buf, MAXLINE, in_fp) != NULL)
	{
		count++;
		ptr = strtok(buf, dev);
		num = 0;
		while(ptr != NULL)
		{
			seg[num++] = ptr;
			ptr = strtok(NULL, dev);
		}
		out_num = 0;
		flag = 0;
		for (i = 0; i < num; i++)
		{
			if (strncmp(seg[i], "Insert", 6) == 0)
				insert(i);
			else if (strcmp(seg[i], "Newline") == 0)
				newline();
			else if (strcmp(seg[i], "Proper") == 0)
				i = proper(i);
			else if (strcmp(seg[i], "Upper") == 0)
				i = upper(i);
			else if (strcmp(seg[i], "Lower") == 0)
				i = lower(i);
			else if (strcmp(seg[i], "Reverse") == 0)
				i = reverse(i);
			else
			{
				out_seg[out_num] = seg[i];
				out_num++;
			}
		}
		if (flag == 2)
			err_quit("ERROR! In %s Line %d : Pairs of tags are interleaved!", argv[1], count);
		for (i = 0; i < out_num; i++)
			printf("%s", out_seg[i]);
		for (i = 0; i < out_num; i++)
			fprintf(out_fp, "%s", out_seg[i]);
	}
	fclose(in_fp);
	fclose(out_fp);
	close(in_fd);
	close(out_fd);
	exit(0);
}

int insert (int i)
{
	char *ptr, dev[] = "'", *letter;
	int num, j;
	ptr = strtok(seg[i], dev);
	ptr = strtok(NULL, dev);
	letter = ptr;
	ptr = strtok(NULL, dev);
	ptr = strtok(NULL, dev);
	num = atoi(ptr);
	for (j = 0; j < num; j++)
	{
		out_seg[out_num] = letter;
		out_num++;
	}
}

int newline()
{
	out_seg[out_num] = "\n";
	out_num++;
}

int proper(int i)
{
	int j, in_num;
	char *ptr;
	j = i + 2;
	if (strcmp(seg[j], "/Proper") == 0)
	{
        	in_num = out_num;
		j--;
		ptr = strtok(seg[j], " ");
		while(ptr != NULL)
		{
			if (ptr[0] >= 'a' && ptr[0] <= 'z')
				ptr[0] -= 32;
			out_seg[out_num] = ptr;
			out_num++;
			ptr = strtok(NULL, " ");
			if (ptr != NULL)
			{
				out_seg[out_num] = " ";
				out_num++;
			}
		}
		i = j + 1;
		if (flag == 1)
		{
			seg[i - 2] = seg[i - 1];
			for (; j < num - 2; j++)
			{
				seg[j] = seg[j + 2];
			}
			num -= 2;
			out_num = in_num;
			i -= 4;
			flag = 0;
		}
	}
	else
	{
		for (j += 2; j < num; j += 2)
		{
			if (strcmp(seg[j], "/Proper") == 0)
				flag = 1;
		}
		if (flag == 0)
			flag = 2;
	}
	return i;
}

int upper(int i)
{
	int j, k, in_num;
	char *ptr;
	j = i + 2;
	if (strcmp(seg[j], "/Upper") == 0)
	{
	    	in_num = out_num;
		j--;
		ptr = strtok(seg[j], " ");
		while(ptr != NULL)
		{
			for (k = 0; k < strlen(ptr); k++)
			{
				if (ptr[k] >= 'a' && ptr[k] <= 'z')
					ptr[k] -= 32;
			}
			out_seg[out_num] = ptr;
			out_num++;
			ptr = strtok(NULL, " ");
			if (ptr != NULL)
			{
				out_seg[out_num] = " ";
				out_num++;
			}
		}
		i = j + 1;
		if (flag == 1)
		{
			seg[i - 2] = seg[i - 1];
			for (; j < num - 2; j++)
			{
				seg[j] = seg[j + 2];
			}
			num -= 2;
			out_num = in_num;
			i -= 4;
			flag = 0;
		}
	}
	else
	{
		for (j += 2; j < num; j += 2)
		{
			if (strcmp(seg[j], "/Upper") == 0)
				flag = 1;
		}
		if (flag == 0)
			flag = 2;
	}
	return i;
}

int lower(int i)
{
	int j, k, in_num;
	char *ptr;
	j = i + 2;
	if (strcmp(seg[j], "/Lower") == 0)
	{
		in_num = out_num;
		j--;
		ptr = strtok(seg[j], " ");
		while(ptr != NULL)
		{
			for (k = 0; k < strlen(ptr); k++)
			{
				if (ptr[k] >= 'A' && ptr[k] <= 'Z')
					ptr[k] += 32;
			}
			out_seg[out_num] = ptr;
			out_num++;
			ptr = strtok(NULL, " ");
			if (ptr != NULL)
			{
				out_seg[out_num] = " ";
				out_num++;
			}
		}
		i = j + 1;
		if (flag == 1)
		{
			seg[i - 2] = seg[i - 1];
			for (; j < num - 2; j++)
			{
				seg[j] = seg[j + 2];
			}
			num -= 2;
			out_num = in_num;
			i -= 4;
			flag = 0;
		}
	}
	else
	{
		for (j += 2; j < num; j += 2)
		{
			if (strcmp(seg[j], "/Lower") == 0)
				flag = 1;
		}
		if (flag == 0)
			flag = 2;
	}
	return i;
}

int  reverse(int i)
{
	int j, k, l, in_num;
	char *ptr, temp;
	j = i + 2;
	if (strcmp(seg[j], "/Reverse") == 0)
	{
	   	in_num = out_num;
		j--;
		ptr = strtok(seg[j], " ");
		while(ptr != NULL)
		{
		    	l = 0;
			for (k = strlen(ptr); k > strlen(ptr) / 2; k--)
			{
				temp = ptr[l];
                		ptr[l] = ptr[strlen(ptr) - l - 1];
				ptr[strlen(ptr) - l - 1] = temp;
                		l++;
			}
			out_seg[out_num] = ptr;
			out_num++;
			ptr = strtok(NULL, " ");
			if (ptr != NULL)
			{
				out_seg[out_num] = " ";
				out_num++;
			}
		}
		i = j + 1;
        if (flag == 1)
		{
			seg[i - 2] = seg[i - 1];
			for (; j < num - 2; j++)
			{
				seg[j] = seg[j + 2];
			}
			num -= 2;
			out_num = in_num;
			i -= 4;
			flag = 0;
		}
	}
	else
	{
		for (j += 2; j < num; j += 2)
		{
			if (strcmp(seg[j], "/Reverse") == 0)
				flag = 1;
		}
		if (flag == 0)
			flag = 2;
	}
	return i;
}
