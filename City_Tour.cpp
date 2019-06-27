/*
 * City_Tour.cpp
 * Author:Yun Pei Chao 
 */
#include<iostream>
#include<fstream>
#include<cmath>
#include<iomanip>

using namespace std;
#define size 50

int **new_index_array;
int path_counter = 0;

struct coordinate
{
	int x, y;
	bool is_vertex = false;
};

double distance(coordinate a, coordinate b);
void swap(coordinate &a, coordinate &b);
void swap(int &a, int &b);
void permutation(int **index_array, int offset, int n, int &flag);

int main()
{
	int n = 0;
	coordinate station[size], bike[size];
	int map[size][size] = { 0 };

	fstream fin;
	fin.open("Input1.in", ios::in);
	fin >> n;
	fin.ignore();

	for (int i = 0; i < n; i++)
	{
		fin >> station[i].x;
		fin.ignore();
		fin >> station[i].y;
		fin.clear();
		fin.ignore();
		map[station[i].x][station[i].y] = 1;
		cout << station[i].x << " " << station[i].y << endl;
	}
	fin.ignore();

	for (int i = 0; i < n; i++)
	{
		fin >> bike[i].x;
		fin.ignore();
		fin >> bike[i].y;
		fin.clear();
		fin.ignore();
		map[bike[i].x][bike[i].y] = 2;
		cout << bike[i].x << " " << bike[i].y << endl;
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (map[i][j] == 0)
				cout << "囗";
			else if (map[i][j] == 1)
				cout << "Ｓ";
			else if (map[i][j] == 2)
				cout << "Ｔ";
		}
		cout << endl;
	}

	//=========================Question 1=========================

	cout << endl << "(1)哪兩個站點靠最近，其距離多少？ 最遠，其距離多少？" << endl;
	double min_distance = sqrt(size*size * 2);
	double max_distance = 0;
	double temp = 0;
	coordinate near_result1, near_result2, far_result1, far_result2;

	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			temp = distance(station[i], station[j]);
			if (temp <= min_distance)
			{
				min_distance = temp;
				near_result1.x = station[i].x;
				near_result1.y = station[i].y;
				near_result2.x = station[j].x;
				near_result2.y = station[j].y;
			}
			if (temp >= max_distance)
			{
				max_distance = temp;
				far_result1.x = station[i].x;
				far_result1.y = station[i].y;
				far_result2.x = station[j].x;
				far_result2.y = station[j].y;
			}
		}
	}
	cout << fixed << setprecision(2);
	cout << "座標(" << near_result1.x << "," << near_result1.y << ")和(" << near_result2.x << "," << near_result2.y << ")的兩個站點靠最近，其距離為" << min_distance << "單位。" << endl;
	cout << "座標(" << far_result1.x << "," << far_result1.y << ")和(" << far_result2.x << "," << far_result2.y << ")的兩個站點靠最遠，其距離為" << max_distance << "單位。" << endl;

	//=========================Question 2=========================

	cout << endl << "(2)哪兩台T-Bike靠最近，其距離多少？ 最遠，其距離多少？" << endl;
	min_distance = sqrt(size*size + size*size);
	max_distance = 0;
	temp = 0;
	near_result1 = {}, near_result2 = {}, far_result1 = {}, far_result2 = {};
	

	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			temp = distance(bike[i], bike[j]);
			if (temp <= min_distance)
			{
				min_distance = temp;
				near_result1.x = bike[i].x;
				near_result1.y = bike[i].y;
				near_result2.x = bike[j].x;
				near_result2.y = bike[j].y;
			}
			if (temp >= max_distance)
			{
				max_distance = temp;
				far_result1.x = bike[i].x;
				far_result1.y = bike[i].y;
				far_result2.x = bike[j].x;
				far_result2.y = bike[j].y;
			}
		}
	}
	cout << "座標(" << near_result1.x << "," << near_result1.y << ")和(" << near_result2.x << "," << near_result2.y << ")的兩台T-Bike靠最近，其距離為" << min_distance << "單位。" << endl;
	cout << "座標(" << far_result1.x << "," << far_result1.y << ")和(" << far_result2.x << "," << far_result2.y << ")的兩台T-Bike靠最遠，其距離為" << max_distance << "單位。" << endl;



	//=========================Question 3=========================

	cout << endl << "(3)n個站點與n台T-Bike散佈的範圍Convex-Hull有多大(求Convex-Hull，它的面積以及最遠的距離)？" << endl;

	coordinate *all_point;
	all_point = (coordinate*)malloc(sizeof(coordinate) * 2 * n);


	for (int i = 0; i < n; i++)
	{
		all_point[i] = station[i];
		all_point[i + n] = bike[i];
	}

	int side_flag = 0, side_check_flag;
	bool is_vertex = true;
	for (int i = 0; i < 2 * n; i++)
	{
		for (int j = i + 1; j < 2 * n; j++)
		{
			is_vertex = true;

			int first_check_point = 0;
			while (first_check_point == i || first_check_point == j)
				first_check_point++;

			side_flag = (all_point[j].x - all_point[i].x)*(all_point[first_check_point].y - all_point[i].y) - (all_point[j].y - all_point[i].y)*(all_point[first_check_point].x - all_point[i].x);
			//記錄第一個點在左側或右側
			if (side_flag > 0)//左側
				side_flag = 2;
			else if (side_flag < 0)//右側
				side_flag = 1;

			for (int k = 0; k < 2 * n; k++)
			{
				if (k != i&&k != j&&k != first_check_point)
				{
					side_check_flag = (all_point[j].x - all_point[i].x)*(all_point[k].y - all_point[i].y) - (all_point[j].y - all_point[i].y)*(all_point[k].x - all_point[i].x);
					if (side_check_flag > 0)//點在左側
						side_check_flag = 2;
					else if (side_check_flag < 0)//點在右側
						side_check_flag = 1;
					if (side_flag != side_check_flag)//只要跟第一個點在不同側就記錄然後break
					{
						is_vertex = false;
						break;
					}
				}
			}
			if (is_vertex == true)
			{
				all_point[i].is_vertex = true;
				all_point[j].is_vertex = true;
			}
		}
	}

	int vertex_counter = 0;
	coordinate *Convex_Hull_vertex;
	Convex_Hull_vertex = (coordinate*)malloc(sizeof(coordinate) * 2 * n);

	//把頂點加入至陣列
	for (int i = 0; i < 2 * n; i++)
	{
		if (all_point[i].is_vertex)
		{
			Convex_Hull_vertex[vertex_counter] = all_point[i];
			vertex_counter++;
		}
	}

	//順時針排序各個頂點
	coordinate line_1, line_2;
	for (int i = 0; i < vertex_counter; i++)
	{
		for (int j = i + 1; j < vertex_counter; j++)
		{
			for (int k = j + 1; k < vertex_counter; k++)
			{
				line_1.x = Convex_Hull_vertex[j].x - Convex_Hull_vertex[i].x;
				line_1.y = Convex_Hull_vertex[j].y - Convex_Hull_vertex[i].y;
				line_2.x = Convex_Hull_vertex[k].x - Convex_Hull_vertex[i].x;
				line_2.y = Convex_Hull_vertex[k].y - Convex_Hull_vertex[i].y;

				if ((line_1.x*line_2.y) - (line_2.x*line_1.y) >= 0)//line1到line2為逆時針轉，將兩個頂點在陣列內的順序互換
					swap(Convex_Hull_vertex[k], Convex_Hull_vertex[j]);
			}
		}
	}

	cout << "Convex-Hull的頂點分別為位於";
	for (int i = 0; i < vertex_counter; i++)
	{
		if (i != 0)
			cout << "、";
		cout << "(" << Convex_Hull_vertex[i].x << "," << Convex_Hull_vertex[i].y << ")";
	}
	cout << "的" << vertex_counter << "個點。" << endl;

	//計算面積
	double area = 0;
	Convex_Hull_vertex[vertex_counter] = Convex_Hull_vertex[0];
	for (int i = 0; i < vertex_counter; i++)
		area += Convex_Hull_vertex[i].x*Convex_Hull_vertex[i + 1].y - Convex_Hull_vertex[i + 1].x*Convex_Hull_vertex[i].y;
	cout << "Convex-Hull的面積為" << fabs(area) / 2 << "平方單位。" << endl;

	//計算最遠的距離
	max_distance = 0;
	for (int i = 0; i < vertex_counter; i++)
	{
		temp = distance(Convex_Hull_vertex[i], Convex_Hull_vertex[i + 1]);
		if (temp >= max_distance)
			max_distance = temp;
	}
	cout << "最遠的距離為" << max_distance << "單位。" << endl;


	//=========================Question 4=========================

	cout << endl << "(4)假如有一台T-Bike在某一站點上，他想要到所有的站點(古蹟或景點)觀光，然後再回到原本的站點歸還T-Bike，求最短的總距離(TSP的問題)？" << endl;
	
	double TSP_diatance = 0, TSP_min_diatance = sqrt(size*size * 2), path_index;

	double **path_length = new double*[n];
	for (int i = 0; i < n; i++)
		path_length[i] = new double[n];
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			path_length[i][j] = distance(station[i], station[j]);
	}

	int N = n-1;
	int path_number = 1;
	while (N > 0)
	{
		path_number *= N;
		N--;
	}

	int **index_array = new int*[path_number];
	for (int i = 0; i < path_number; i++)
		index_array[i] = new int[n];

	new_index_array = new int*[path_number];
	for (int i = 0; i < path_number; i++)
		new_index_array[i] = new int[n];

	for (int i = 0; i < path_number; i++)
	{
		for (int j = 0; j < n; j++)
			index_array[i][j] = j;
	}
	int flag = 0;

	permutation(index_array, 1, n, flag);


	for (int i = 0; i < path_counter; i++)
	{
		TSP_diatance = 0;
		new_index_array[i][n] = new_index_array[i][0];
		for (int j = 0; j < n; j++)
			TSP_diatance += path_length[new_index_array[i][j]][new_index_array[i][j + 1]];

		if (TSP_diatance < TSP_min_diatance)
			TSP_min_diatance = TSP_diatance;
	}
	cout << "最短的總距離為" << TSP_min_diatance << "單位。" << endl;



	//=========================Question 5=========================

	cout << endl << "(5)假設每一個站點只有一個空位，以最短總距離的方式n個人騎T-Bike分別停到分配的站點，要如何配對，以及求出最少的總距離和？" << endl;

	double S_T_min_distance = 0;
	double **S_T_distance = new double*[n];
	for (int i = 0; i < n; i++)
		S_T_distance[i] = new double[n];


	double **S_T_distance_COPY = new double*[n];
	for (int i = 0; i < n; i++)
		S_T_distance_COPY[i] = new double[n];


	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			S_T_distance[i][j] = distance(station[i], bike[j]);
			S_T_distance_COPY[i][j] = distance(station[i], bike[j]);
			cout << S_T_distance[i][j] << " ";
		}
		cout << endl;
	}


	//在各列中找最小值，將該列中各元素減去此值。
	double line_min_distance = sqrt(size*size * 2);

	for (int i = 0; i < n; i++)
	{
		line_min_distance = sqrt(size*size * 2);
		for (int j = 0; j < n; j++)
		{
			if (S_T_distance_COPY[i][j] < line_min_distance)
				line_min_distance = S_T_distance_COPY[i][j];
		}
		for (int j = 0; j < n; j++)
		{
			S_T_distance_COPY[i][j] -= line_min_distance;
		}
	}


	//在各行中找最小值，將該行中各元素減去此值。
	for (int i = 0; i < n; i++)
	{
		line_min_distance = sqrt(size*size * 2);
		for (int j = 0; j < n; j++)
		{
			if (S_T_distance_COPY[j][i] < line_min_distance)
				line_min_distance = S_T_distance_COPY[j][i];
		}
		for (int j = 0; j < n; j++)
			S_T_distance_COPY[j][i] -= line_min_distance;
	}

	cout << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << S_T_distance_COPY[i][j] << " ";
		cout << endl;
	}




	coordinate *zero_coordinate;
	zero_coordinate = (coordinate*)malloc(sizeof(coordinate) * pow(n, 2));
	int *zero_counter;
	zero_counter = (int*)malloc(sizeof(int) *n);//記錄每一列有幾個0
	int zero_number = 0;//記錄共有幾個0

	//檢查各列，對碰上之第一個零做記號，同列或同欄的其他零則設為-1
	for (int i = 0; i < n; i++)
		zero_counter[i] = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (S_T_distance_COPY[i][j] == 0)
			{
				zero_coordinate[zero_number].x = i;
				zero_coordinate[zero_number].y = j;
				zero_counter[i]++;
				zero_number++;
			}
		}
	}

	for (int i = 0; i < zero_number; i++)
		cout << zero_coordinate[i].x << "," << zero_coordinate[i].y << "   ";


	//從0較少的列開始
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (zero_counter[j] == i)//從j列開始
			{

				//删除与该零在同一列或同一欄的其他零
				for (int k = 0; k < n; k++)
				{
					if (zero_coordinate[k].x == j)
					{
						for (int m = k + 1; m < n; m++)
						{
							if (zero_coordinate[k].x == zero_coordinate[m].x&&S_T_distance_COPY[zero_coordinate[m].x][zero_coordinate[m].y] == 0)
								S_T_distance_COPY[zero_coordinate[m].x][zero_coordinate[m].y] = -1;
							if (zero_coordinate[k].y == zero_coordinate[m].y&&S_T_distance_COPY[zero_coordinate[m].x][zero_coordinate[m].y] == 0)
								S_T_distance_COPY[zero_coordinate[m].x][zero_coordinate[m].y] = -1;
						}
					}
				}
			}
		}
	}


	cout << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << S_T_distance_COPY[i][j] << " ";
		cout << endl;
	}



	bool finish = true;
	double **unfinished = new double*[n];
	for (int i = 0; i < n; i++)
		unfinished[i] = new double[n];


	//檢查可否完成僅含零的完全指派；若不能，則畫出最少數目的垂直與水平的刪除線來包含所有的零至少一次。
	//檢查是否每一行每一列都有0
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (S_T_distance_COPY[i][j] == 0)
				break;
			else
			{
				if (j == n - 1)
					finish = false;
			}
		}
	}
	for (int j = 0; j < n; j++)
	{
		for (int i = 0; i < n; i++)
		{
			if (S_T_distance_COPY[i][j] == 0)
				break;
			else
			{
				if (i == n - 1)
					finish = false;
			}
		}
	}
	
	while (finish != true)
	{

		//把-1還原
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (S_T_distance_COPY[i][j] == -1)
					S_T_distance_COPY[i][j] = 0;
			}
		}

		finish = true;
		bool **is_delete = new bool*[n];



		//畫出最少數目的垂直與水平的刪除線來包含所有的零至少一次。

		for (int i = 0; i < n; i++)
			is_delete[i] = new bool[n];
		int x_counter = 0, y_counter = 0;

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				is_delete[i][j] = false;
		}

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (S_T_distance_COPY[i][j] == 0 && !is_delete[i][j])
				{
					x_counter = 0;
					y_counter = 0;

					for (int k = 0; k < n; k++)
					{
						if (k != i && S_T_distance_COPY[k][j] == 0)
							x_counter++;
					}
					for (int k = 0; k < n; k++)
					{
						if (k != j && S_T_distance_COPY[i][k] == 0)
							y_counter++;
					}
					if (x_counter > y_counter)
					{
						for (int k = 0; k < n; k++)
							is_delete[k][j] = true;
					}
					else
					{
						for (int k = 0; k < n; k++)
							is_delete[i][k] = true;
					}
				}
			}
		}

		
		//找出未被畫線的元素中之最小值
		double min_undelete = sqrt(size*size * 2);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (!is_delete[i][j])
				{
					if (S_T_distance_COPY[i][j] < min_undelete)
						min_undelete = S_T_distance_COPY[i][j];
				}
			}
		}

		//將含有此些未被畫線的元素的各列所有元素減去最小值
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (!is_delete[i][j])
				{
					for (int k = 0; k < n; k++)
						S_T_distance_COPY[i][k] -= min_undelete;
					break;
				}
			}
		}



		//若造成負值，則將該欄加上最小值。形成新矩陣後回到step3
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (S_T_distance_COPY[i][j] < 0)
				{
					for (int k = 0; k < n; k++)
						S_T_distance_COPY[k][j] += min_undelete;
					break;
				}
			}
		}



		cout << endl;
		for (int i = 0; i < n; i++)
			zero_counter[i] = 0;

		//檢查各列，對碰上之第一個零做記號，同列或同欄的其他零則設為-1
		for (int i = 0; i < n; i++)
			zero_counter[i] = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (S_T_distance_COPY[i][j] == 0)
				{
					zero_coordinate[zero_counter[i]].x = i;
					zero_coordinate[zero_counter[i]].y = j;
					zero_counter[i]++;
				}
			}
		}

		//從0較少的列開始
		for (int i = 1; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (zero_counter[j] == i)//從j列開始
				{
					//删除与该零在同一列或同一欄的其他零
					for (int k = 0; k < n; k++)
					{
						for (int m = k + 1; m < n; m++)
						{
							if (zero_coordinate[k].x == j)
							{
								if (zero_coordinate[k].x == zero_coordinate[m].x&&S_T_distance_COPY[zero_coordinate[m].x][zero_coordinate[m].y] == 0)
									S_T_distance_COPY[zero_coordinate[m].x][zero_coordinate[m].y] = -1;
								if (zero_coordinate[k].y == zero_coordinate[m].y&&S_T_distance_COPY[zero_coordinate[m].x][zero_coordinate[m].y] == 0)
									S_T_distance_COPY[zero_coordinate[m].x][zero_coordinate[m].y] = -1;
							}
						}
					}
				}
			}
		}

		

		//檢查是否每一行每一列都有0，若否則重做
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (S_T_distance_COPY[i][j] == 0)
					break;
				else
				{
					if (j == n - 1)
						finish = false;
				}
			}
		}
		for (int j = 0; j < n; j++)
		{
			for (int i = 0; i < n; i++)
			{
				if (S_T_distance_COPY[i][j] == 0)
					break;
				else
				{
					if (i == n - 1)
						finish = false;
				}
			}
		}
	}


	cout << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << S_T_distance_COPY[i][j] << " ";
		cout << endl;
	}


	for (int j = 0; j < n; j++)
	{
		for (int i = 0; i < n; i++)
		{
			if (S_T_distance_COPY[i][j] == 0)
				S_T_min_distance += S_T_distance[i][j];
		}
	}
	cout << endl << S_T_min_distance;

	


	free(all_point);
	free(Convex_Hull_vertex);

	fin.close();

	system("PAUSE");
	return 0;
}

double distance(coordinate a, coordinate b)
{
	return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}


void swap(coordinate & a, coordinate & b)
{
	coordinate temp = a;
	a = b;
	b = temp;
}

void swap(int & a, int & b)
{
	int temp = a;
	a = b;
	b = temp;
}


void permutation(int **index_array, int offset, int n, int &flag)
{

	int i = 0, temp = 0;
	if (offset == n -1)
	{
		for (int j = 0; j < n; j++)
			new_index_array[path_counter][j] = index_array[flag][j];
		path_counter++;
	}

	else
	{
		for (i = offset; i < n; i++)
		{
			swap(index_array[flag][offset], index_array[flag][i]);//交換
			permutation(index_array, offset+ 1, n, flag);//遞迴
			swap(index_array[flag][i], index_array[flag][offset]);//將字首換回來，繼續做前一次排列
		}
	}
}
