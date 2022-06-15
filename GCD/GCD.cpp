/*
 * GCD.cpp
 * Author:Yun Pei Chao 
 */
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define max 1e8

int Iterative(int m, int n);
int Recursive(int x, int y);
int Consecutive(int m, int n);
int Middle_School(int m, int n);

int main(void) {

	int m, n, error, status;
	char skip_ch;

	double time1,time2,time3,time4;
	do {                                                   //防呆
		error = 0;
		printf("Enter m => ");
		status = scanf("%d", &m);

		if (status != 1) {
			error = 1;
			scanf("%c", &skip_ch);
			printf("Invalid character!!\n");
		}
		else if (m < 0) {
			error = 1;
			printf("Invalid number!!\n");
		}
		do
			scanf("%c", &skip_ch);
		while (skip_ch != '\n');

	} while (error);

	do {
		error = 0;
		printf("Enter n => ");
		status = scanf("%d", &n);

		if (status != 1) {
			error = 1;
			scanf("%c", &skip_ch);
			printf("Invalid character!!\n");
		}
		else if (n < 0) {
			error = 1;
			printf("Invalid number!!\n");
		}
		do
			scanf("%c", &skip_ch);
		while (skip_ch != '\n');

	} while (error);




	clock_t start1 = clock();                                      //程式開始執行時間
	
	printf("\nEuclid’s algorithm – Iterative version:\nGCD => %d\n", Iterative(m, n));            //Iterative
	clock_t end1 = clock();                                        //程式結束執行時間
	time1 = difftime(end1, start1) / max;     
printf("total time => %2.50f seconds\n\n", time1 / CLOCKS_PER_SEC); //計算程式時間


clock_t start2 = clock();
for (int i = 0; i < max; i++) {
	Recursive(m, n);
}printf("Euclid’s algorithm – Recursive version:\nGCD => %d\n", Recursive(m, n));               //Recursive
clock_t end2 = clock();
time2 = difftime(end2, start2) / max;
printf("total time => %2.50f seconds\n\n", (time2/ CLOCKS_PER_SEC));


clock_t start3 = clock();
printf("Consecutive integer checking algorithm:\nGCD => %d\n", Consecutive(m, n));                 //Consecutive
clock_t end3 = clock();
time3 = difftime(end3, start3) / max;
printf("total time => %2.50f seconds\n\n", (time3 / CLOCKS_PER_SEC));

clock_t start4 = clock();
for (int i = 0; i < max; i++) {
	Middle_School(m, n);
}
printf("Middle-school procedure:\nGCD => %d\n", Middle_School(m, n));                 //Middle school
clock_t end4= clock();
time4 = difftime(end4, start4) / max;
printf("total time => %2.50f seconds\n\n", (time4 / CLOCKS_PER_SEC));

	system("pause");
	return 0;
}

int Iterative(int m, int n)
{
	for (int i = 0; i < max; i++) {

		while (n != 0) {
			int r = m % n;
			m = n;
			n = r;
		}

	}
	return m;
}

int Recursive(int x, int y)
{
	
		if (y == 0) return x;
		else Recursive(y, x%y);
	
}

int Consecutive(int m, int n)
{
	int t, gcd;
	if (m > n) {
		t = n;
	}
	else {
		t = m;
	}
	for (int i = 0; i < max; i++) {
		while (t > 0) {
			if ((m%t == 0) && (n%t == 0)) {
				gcd = t;
				break;
			}

			t -= 1;

		}
	}
	return gcd;
}

int Middle_School(int m, int n)
{
	int i, j = 0, num1 = 0;
	int arr1[200], arr2[200];
	
		for (i = 2; i <= m; i++)                        //m的質因數分解
		{
			while (m%i == 0)
			{


				m /= i;
				arr1[j] = i;
				j++;


			}
		}
		num1 = j;
		int c, d = 0, num2 = 0;
		for (c = 2; c <= n; c++)                      //n的質因數分解
		{
			while (n%c == 0)
			{


				n /= c;
				arr2[d] = c;
				d++;


			}
		}
		num2 = d;
		int ans = 1;
		for (int a = 0; a < num1; a++) {

			for (int b = 0; b < num2; b++) {

				if (arr1[a] == arr2[b]) {                  //比對相同的質因數
					ans *= arr2[b];
					arr2[b] = 0;
					break;
				}

			}
		}

		return ans;
	
}

