#include <cstdio>
#include <clocale>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <locale>
#include <vector>
#include <Windows.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <array>
#define _DEBUG

using namespace std;
namespace fs = std::filesystem;

string filename2("output.csv");
ofstream ofs(filename2, ios::out);



class CTri
{
private:
	float fv_xyz[3][3] = { {0,0,0},{0,0,0},{0,0,0} };
	std::vector<float> temp_area;
	//float* temp_area = new float[t];
	//float* fv_area = new float[m];
	float fv_side[3] = { 0,0,0 };
	int index = 0;
	float sum = 0;
	//float avg = 0;
	//int Tri_Num = 0;
	//int m = 0;
	//int t = 0;
	//int t_1 = 0;
	std::array<float, 6> xyz_minmax = { 0,0,0,0,0,0 };
	std::vector<std::array<float, 6>> temp_minmax;
	//float* temp_minmax = new float[t_1];


public:
	void calc_area();
	void set_val(int index, float x, float y, float z);
	void set_side();
	void cal_avg_area();
	void cal_minmax();
	void cal_count_tri(int Tri_Num);
	void show_count_tri();
	//void cal_temp_area(int t);
	void cal_temp_minmax();
	~CTri();
};


void CTri::calc_area()
{

	sum = (fv_side[0] + fv_side[1] + fv_side[2]) / 2;
	//fv_area[0] = sqrt(sum * ((sum - fv_side[0]) * (sum - fv_side[1])) * (sum - fv_side[2]));
	//cout << "fv_area :" << " " << fv_area[0] << endl;
	//cout << " " << endl;
	//temp_area[t] = fv_area[0];
	//t++;

	float fv_area = sqrt(sum * ((sum - fv_side[0]) * (sum - fv_side[1])) * (sum - fv_side[2]));
	cout << "fv_area :" << " " << fv_area << endl;
	temp_area.push_back(fv_area);

}

void CTri::set_val(int index, float x, float y, float z)
{

	fv_xyz[index][0] = x;
	fv_xyz[index][1] = y;
	fv_xyz[index][2] = z;
	cout << "fv_xyz[id][0]=" << fv_xyz[index][0] << "fv_xyz[id][1]=" << fv_xyz[index][1] << "fv_xyz[id][2]=" << fv_xyz[index][2] << endl;
	ofs << "fv_xyz[id][3]" << "," << fv_xyz[index][0] << "," << fv_xyz[index][1] << "," << fv_xyz[index][2] << "," << endl;

}

void CTri::set_side()
{
	float(*p)[3];
	p = fv_xyz;

	fv_side[0] = sqrt(pow(**(p + 1) - **p, 2) + pow(*(*(p + 1) + 1) - *(*p + 1), 2) + pow(*(*(p + 1) + 2) - *(*p + 2), 2));
	fv_side[1] = sqrt(pow(**(p + 2) - **p, 2) + pow(*(*(p + 2) + 1) - *(*p + 1), 2) + pow(*(*(p + 2) + 2) - *(*p + 2), 2));
	fv_side[2] = sqrt(pow(**(p + 2) - **(p + 1), 2) + pow(*(*(p + 2) + 1) - *(*(p + 1) + 1), 2) + pow(*(*(p + 2) + 2) - *(*(p + 1) + 2), 2));
	cout << "fv_side[0]=" << fv_side[0] << "fv_side[1]=" << fv_side[1] << "fv_side[2]=" << fv_side[2] << endl;
	//ofs << "fv_side[0]=" << fv_side[0] << "fv_side[1]=" << fv_side[1] << "fv_side[2]=" << fv_side[2] << endl;


}

/*void CTri::cal_temp_area(int t)
{

		cout << "temp_area[t] :" << temp_area[12] << endl;

}*/

void CTri::cal_avg_area()
{
	float sum2 = 0;

	//for (int j = 0; j < Tri_Num; j++)
	//{
	//	sum2 += temp_area[j];
	//	//cout << "test :" << temp_area[j] << endl;
	//}

	for (float f : temp_area)
	{
		sum += f;
	}

	float avg = sum2 / temp_area.size();
	cout << "avg_area:" << avg << " " << endl;
	ofs << "avg_area:" << "," << avg << " " << endl;
}

void CTri::cal_count_tri(int Tri_Num)
{
	Tri_Num++;
}

void CTri::show_count_tri()
{
	cout << "Tri_Num" << temp_minmax.size() << endl;
	ofs << "Tri_Num" << "," << temp_minmax.size() << endl;
}

void CTri::cal_minmax()
{
	std::array<float, 6>& firstMinMax = temp_minmax[0];
	float x_min = firstMinMax[0];
	float x_max = firstMinMax[1];
	float y_min = firstMinMax[2];
	float y_max = firstMinMax[3];
	float z_min = firstMinMax[4];
	float z_max = firstMinMax[5];

	/*cout << "tx_min:" << temp_minmax[0] << endl;
	cout << "tx_max:" << temp_minmax[1] << endl;
	cout << "ty_min:" << temp_minmax[2] << endl;
	cout << "ty_max:" << temp_minmax[3] << endl;
	cout << "tz_min:" << temp_minmax[4] << endl;
	cout << "tz_max:" << temp_minmax[5] << endl;
	cout << " " << endl;*/

	int count2 = (int)temp_minmax.size();
	for (int i = 1; i < count2; i++)
	{
		std::array<float, 6>& curMinMax = temp_minmax[i];
		x_min = min(x_min, curMinMax[0]);
		x_max = max(x_max, curMinMax[1]);
		y_min = min(y_min, curMinMax[2]);
		y_max = max(y_max, curMinMax[3]);
		z_min = min(z_min, curMinMax[4]);
		z_max = max(z_max, curMinMax[5]);
	}
	/*
	for (int i = 0; i < count2; i++)
	{
		int j = 6 * i;

		if (x_min >= temp_minmax[j])
		{
			x_min = temp_minmax[j];
		}
		if (y_min >= temp_minmax[j + 2])
		{
			y_min = temp_minmax[j + 2];
		}
		if (z_min >= temp_minmax[j + 4])
		{
			z_min = temp_minmax[j + 4];
		}
	}

	for (int z = 1; z < count2 + 1; z++)
	{
		int k = (6 * z - 5);

		if (x_max <= temp_minmax[k])
		{
			x_max = temp_minmax[k];
		}
		if (y_max <= temp_minmax[k + 2])
		{
			y_max = temp_minmax[k + 2];
		}
		if (z_max <= temp_minmax[k + 4])
		{
			z_max = temp_minmax[k + 4];
		}
	}
	*/

	cout << "x_min : " << x_min << "x_max : " << x_max << "y_min : " << y_min << "y_max : " << y_max << "z_min : " <<
		z_min << "z_max : " << z_max << endl;
	ofs << "x_min : " << "," << x_min << "," << "x_max : " << "," << x_max << "," << "y_min : " << "," << y_min << "," << "y_max : " << ","
		<< y_max << "," << "z_min : " << "," << z_min << "," << "z_max : " << "," << z_max << endl;
	cout << " " << endl;

}

void CTri::cal_temp_minmax()
{

	float x_min = fv_xyz[0][0];
	float x_max = fv_xyz[0][0];
	float y_min = fv_xyz[0][1];
	float y_max = fv_xyz[0][1];
	float z_min = fv_xyz[0][2];
	float z_max = fv_xyz[0][2];
	// 배열 첫번째 값을 최소 최대값으로 설정

	for (int i = 0; i < 3; i++)
	{

		if (x_min > fv_xyz[i][0])
		{
			x_min = fv_xyz[i][0];

		}
		if (x_max < fv_xyz[i][0])
		{
			x_max = fv_xyz[i][0];
		}
		if (y_min > fv_xyz[i][1])
		{
			y_min = fv_xyz[i][1];

		}
		if (y_max < fv_xyz[i][1])
		{
			y_max = fv_xyz[i][1];
		}
		if (z_min > fv_xyz[i][2])
		{
			z_min = fv_xyz[i][2];

		}
		if (z_max < fv_xyz[i][2])
		{
			z_max = fv_xyz[i][2];
		}
	}


	xyz_minmax[0] = x_min;
	xyz_minmax[1] = x_max;
	xyz_minmax[2] = y_min;
	xyz_minmax[3] = y_max;
	xyz_minmax[4] = z_min;
	xyz_minmax[5] = z_max;

	//temp_minmax[t_1] = xyz_minmax[0];
	//temp_minmax[t_1 + 1] = xyz_minmax[1];
	//temp_minmax[t_1 + 2] = xyz_minmax[2];
	//temp_minmax[t_1 + 3] = xyz_minmax[3];
	//temp_minmax[t_1 + 4] = xyz_minmax[4];
	//temp_minmax[t_1 + 5] = xyz_minmax[5];
	//m++;
	//t_1 = m * 6;

	temp_minmax.push_back(xyz_minmax);


	//return 0;
	cout << "x_min:" << xyz_minmax[0] << endl;
	cout << "x_max:" << xyz_minmax[1] << endl;
	cout << "y_min:" << xyz_minmax[2] << endl;
	cout << "y_max:" << xyz_minmax[3] << endl;
	cout << "z_min:" << xyz_minmax[4] << endl;
	cout << "z_max:" << xyz_minmax[5] << endl;
	cout << " " << endl;

}

CTri::~CTri()
{
	//delete[] temp_minmax;
	//temp_minmax = NULL;
	//delete[] temp_area;
	//temp_area = NULL;
	//delete[] fv_area;
	//fv_area = NULL;
}

int main()
{

	string s;
	string word = "endfacet";
	string vt_ = "vertex";

	int count1 = 0;
	int count2 = 0;
	int t = 0;

	float ptx = 0;
	float pty = 0;
	float ptz = 0;

	CTri t1;

	//filesystem::path p1("./*.STL");

	//cout << "Does " << p1 << " exist? [" << boolalpha << filesystem::exists(p1) << "]" << endl;
	//cout << "Is " << p1 << " file? [" << filesystem::is_regular_file(p1) << "]" << endl;

	string filename = "TEMP.STL";

	for (const auto& p : fs::directory_iterator("./"))
	{
		if (p.path().extension() == ".STL")
		{
			filename = p.path().filename().string();
		}
	}

	ifstream ifs(filename.c_str(), ios::binary);
	if (ifs.fail())
	{
		ifs.close();
		cout << "Read stl file error. It might be not binary stl file. Check it again~" << endl;
		return false;
	}


	if (ifs.is_open())
	{
		ifs >> s;
		using namespace std;

		while (!ifs.eof())
		{
			getline(ifs, s);
			int r = 0;
			if (s.find(word) != -1)
			{
				count2++;
				t1.cal_count_tri(count2);
			}

			if (s.find(vt_) != -1)
			{

				ptx = stof(s.substr(16, 12));
				pty = stof(s.substr(29, 12));
				ptz = stof(s.substr(42, 12));

				cout << "The ptx value :" << ptx << endl;
				cout << "The pty value :" << pty << endl;
				cout << "The ptz value :" << ptz << endl;

				t1.set_val(count1, ptx, pty, ptz);
				count1++;

				if ((count1) % 3 == 0 && count1 != 0 && count1 != 1 && count1 != 2)
				{
					t1.set_side();
					t1.calc_area();
					t1.cal_temp_minmax();
					count1 = 0;
				}



			}//vertex if문 종료

		} // while문 종료
		t1.show_count_tri();
		//t1.cal_temp_area(t);
		t1.cal_avg_area();
		t1.cal_minmax();

	}
	else
	{
		cout << "파일을 찾을 수 없습니다!" << endl;
	}



	ifs.close();
	ofs.close();

	t1.~CTri();
	return 0;
	return EXIT_SUCCESS;

	//끝~휴...어렵당...Coded by 배공민....
}



