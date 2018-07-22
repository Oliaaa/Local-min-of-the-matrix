#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>

enum { M = 10, N = 13 };

void enterMatrix(int A[M][N])
{
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			scanf("%d", &A[i][j]);
}

void writeMatrixInFile(char* file_name, int A[M][N])
{
	FILE* file;

	if ((file = fopen(file_name, "w")) == NULL)
		printf("�� ������� ������� ���� ��� ������\n");

	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
			fprintf(file, "%d ", A[i][j]);

		fputc('\n', file);
	}

	if (fclose(file) != 0)
		printf("������ �������� ����� ��� ������\n");
}

void writeCountFile(char* file_result, int count)
{
	FILE* file;

	if (((file = fopen(file_result, "w")) == NULL))
		printf("�� ������� ������� ���� ��� ������\n");

	fprintf(file, "���������� ��������� ��������� � ������� 10 � 13: %d\n", count);

	if (fclose(file) != 0)
		printf("������ �������� ����� ��� ������\n");
}


bool isLocalMin(int A[M][N], int i, int j)
{
	if (0 <= i - 1)	           //If the element does not go beyond the left border					                  
	{
		if (A[i - 1][j] <= A[i][j])
			return false;
		//If the element does not exceed the upper limit  
		if (0 <= j - 1 && A[i - 1][j - 1] <= A[i][j])
			return false;
		//If the element does not exceed the lower limit
		if (j + 1 < N && A[i - 1][j + 1] <= A[i][j])
			return false;
	}

	if (i + 1 < M)		     //If the element does not go beyond the right border
	{
		if (A[i + 1][j] <= A[i][j])
			return false;
		if (0 <= j - 1 && A[i + 1][j - 1] <= A[i][j])
			return false;
		if (j + 1 < N && A[i + 1][j + 1] <= A[i][j])
			return false;
	}

	if (0 <= j - 1 && A[i][j - 1] <= A[i][j])
		return false;
	if (j + 1 < N && A[i][j + 1] <= A[i][j])
		return false;

	return true;
}

//Search for the number of local minimum
int countLocalMins(int A[M][N])
{
	int count = 0;

	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			if (isLocalMin(A, i, j))
				count++;

	return count;
}

void main()
{
	UINT old_in = GetConsoleCP();
	UINT old_out = GetConsoleOutputCP();

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int A[M][N], count;

	printf("������� �������:\n");
	enterMatrix(A);
	writeMatrixInFile("file.txt", A);

	count = countLocalMins(A);

	printf("���������� ��������� ���������: %d\n", count);
	writeCountFile("result.txt", count);

	SetConsoleCP(old_in);
	SetConsoleOutputCP(old_out);
}
