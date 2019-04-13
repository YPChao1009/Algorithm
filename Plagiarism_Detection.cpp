/*
 * Plagiarism_Detection.cpp
 * Author:Yun Pei Chao 
 */
#include<iostream>
#include<string>
#include<windows.h>
#include<fstream>
#include<iomanip>
#include<math.h>

using namespace std;
int min_Value(int a, int b, int c)
{
	if (b < a)
		a = b;
	if (c < a)
		a = c;
	return a;
}

int min_Value(int a, int b)
{
	if (b < a)
		a = b;
	return a;
}

int max_Value(int a, int b)
{
	if (b > a)
		a = b;
	return a;
}
int Edit_Distance(string a, string b)
{
	int length_a = a.length();
	int length_b = b.length();
	int *distance = (int*)malloc(sizeof(int)*(length_b + 1));

	int upper_left, temp; //upper_left記錄左上角的值

	for (int j = 0; j <= length_b; j++)
		distance[j] = j;

	for (int i = 1; i <= length_a; i++)
	{
		upper_left = i - 1;
		distance[0] = i;
		for (int j = 1; j <= length_b; j++)
		{
			temp = distance[j];
			//字串a、b從1開始，陣列從0開始
			if (a[i - 1] == b[j - 1])//相符就取左上角的值
				distance[j] = upper_left;
			else//不相符就選上、左、左上的值中較小的值再+1
				distance[j] = min_Value(distance[j], distance[j - 1], upper_left) + 1;
			upper_left = temp;
		}
	}
	return distance[length_b];
}

int Levenshtein_Distance(string a, string b)
{
	int length_a = a.length();
	int length_b = b.length();
	int *distance;
	distance = (int*)malloc(sizeof(int)*(length_b + 1));

	int upper_left, temp;

	for (int j = 0; j <= length_b; j++)
		distance[j] = j;

	for (int i = 1; i <= length_a; i++)
	{
		upper_left = i - 1;
		distance[0] = i;
		for (int j = 1; j <= length_b; j++)
		{
			temp = distance[j];
			if (a[i - 1] == b[j - 1])
				distance[j] = upper_left;
			else
				distance[j] = min_Value(distance[j], distance[j - 1]) + 1;
			upper_left = temp;
		}
	}
	return distance[length_b];
}


int main()
{

	string S1 , S2;
	

	cout << "------第一題------" << endl;
	cout << "Enter S1>";
	cin >> S1;
	cout << "Enter S2>";
	cin >> S2;

	

	cout << endl << "Minimum Edit Distances: " << Edit_Distance(S1, S2) << endl;
	cout << "Levenshtein Distance: " << Levenshtein_Distance(S1, S2)<< endl;

	

	//----------(1)整篇比對----------

	string input, filename1, filename2;
	string original = "", comparison = "";
	ifstream fin1, fin2;
	cout << endl << "------第二題------" << endl;

	cout << "Please input the file name>";
	cin >> filename1;
	fin1.open(filename1, ios::in);

	while (!fin1)
	{
		filename1 = {};
		cout << endl << "Fail to open file!!\n\n";
		cout << "Please input the file name>";
		cin >> filename1;
		fin1.open(filename1, ios::in);
	}

	cout << "Please input the comparison file name>";
	cin >> filename2;
	fin2.open(filename2, ios::in);

	while (!fin2)
	{
		filename2 = {};
		cout << endl << "Fail to open file!!\n\n";
		cout << "Please input the comparison file name>";
		cin >> filename2;
		fin2.open(filename2, ios::in);
	}

	double E_similarity = 0, L_similarity = 0;
	double max_length = 0;

	while (fin1)
	{
		getline(fin1, input);
		original.append(input);
	}

	while (fin2)
	{
		getline(fin2, input);
		comparison.append(input);
	}

	int ED = 0, LD = 0;
	clock_t start1 = clock();
	ED = Edit_Distance(original, comparison);
	clock_t end1 = clock();
	double time1 = difftime(end1, start1);
	clock_t start2 = clock();
	LD = Levenshtein_Distance(original, comparison);
	clock_t end2 = clock();
	double time2 = difftime(end2, start2);
	max_length = (double)max_Value(original.length(), comparison.length());

	fin1.close();
	fin2.close();


	cout << endl << "(1)Whole article comparison" << endl;
	E_similarity = 1 - (double)ED / max_length;
	if (E_similarity < 0)
		E_similarity = 0;
	cout << "Degree of plagiarism(Minimum Edit Distances):" << E_similarity * 100 << "%\n";
	cout<<"total time =>"<< time1 / CLOCKS_PER_SEC<<" seconds\n\n";
	L_similarity = 1 - (double)LD / max_length;
	if (L_similarity < 0)
		L_similarity = 0;
	cout << "Degree of plagiarism(Levenshtein Distance):" << L_similarity * 100 << "%\n";
	cout << "total time =>" << time2 / CLOCKS_PER_SEC << " seconds\n\n";

	//----------(2)分段比對----------

	fin1.open(filename1, ios::in);

	original = "";
	comparison = "";
	int c = 0;
	double total_E_similarity = 0, total_L_similarity = 0;
	double max_E_similarity_array[100], max_L_similarity_array[100];

	while (true)
	{
		ED = 0, LD = 0;

		getline(fin1, input, '\n');
		original = input;

		double max_E_similarity = 0, max_L_similarity = 0;
		fin2.open(filename2, ios::in);
		while (true)
		{
			getline(fin2, input, '\n');
			comparison = input;

			max_length = (double)max_Value(original.length(), comparison.length());

			ED = Edit_Distance(original, comparison);
			E_similarity = 1 - (double)ED / max_length;
			if (E_similarity > max_E_similarity)
				max_E_similarity = E_similarity;

			LD = Levenshtein_Distance(original, comparison);
			L_similarity = 1 - (double)LD / max_length;
			if (L_similarity > max_L_similarity)
				max_L_similarity = L_similarity;

			if (fin2.eof())
			{
				fin2.close();
				break;
			}
		}
		max_E_similarity_array[c] = max_E_similarity;
		max_L_similarity_array[c] = max_L_similarity;
		c++;
		total_E_similarity += max_E_similarity;
		total_L_similarity += max_L_similarity;


		if (fin1.eof())
			break;
	}

	cout << endl << "(2)Segmented article comparison" << endl;

	cout << "a." << endl;
	double E_similarity_avg = total_E_similarity / c;
	double L_similarity_avg = total_L_similarity / c;
	cout << "Degree of plagiarism(Minimum Edit Distances):" << E_similarity_avg * 100 << "%\n";
	cout << "Degree of plagiarism(Levenshtein Distance):" << L_similarity_avg * 100 << "%\n";


	cout << endl << "b." << endl;
	double E_Var = 0, L_Var = 0;

	for (int i = 0; i < c; i++)
	{
		E_Var += pow(max_E_similarity_array[i] - E_similarity_avg, 2);
		L_Var += pow(max_L_similarity_array[i] - L_similarity_avg, 2);
	}
	E_Var = E_Var / c;
	L_Var = L_Var / c;

	cout << "Variance(Minimum Edit Distances)為" << setprecision(10) << E_Var<< endl;
	cout << "Variance(Levenshtein Distance)為" << setprecision(10) << L_Var<< endl;


	cout << endl << "c." << endl;
	cout << "Standard deviation(Minimum Edit Distances):" << setprecision(10) <<sqrt(E_Var) << endl;
	cout << "Standard deviation(Levenshtein Distance):" << setprecision(10) << sqrt(L_Var) << endl;


	system("PAUSE");
	return 0;
}


