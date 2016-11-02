#ifdef ORIGINAL_TEST_CPP_IN_USE_CShape_DLL
#include "Render.h"
#include "Render_L.h"
#include <time.h>
//#include "simple_svg_1.0.0.hpp"
//#include FT_FREETYPE_H
//#include <opencv2/opencv.hpp>

//using namespace std;


string Key_W0 = "\\frac";
string Key_W1 = "\\sqrt";
string Key_W2 = "left";
string Key_W3 = "right";
string Key_W4 = "-1";
string Key_W5 = "part";

int SCALES = 3;
#define MAX 100
int Step = 30;

CvRect rect_render;

//using namespace svg;

char file_render[110][50] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
"a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
"k", "l", "m", "n", "o", "p", "q", "r", "s", "t",
"u", "v", "w", "x", "y", "z", "+", "-", "(", ")",
"{", "}", "!", "-1", "-2", "-3", "-4", "-5", "-6",
"-7", "-8", "-9", "infty", "sum", "pi", "%", "=", "Big{", "Big}",
",", "lambda", "alpha", "theta", "beta", "delta", "ast", "div", "ne", "prod",
"int", "in", "[", "]", "to", "'", "A1", "B1", "C1", "D1",
"E1", "F1", "G1", "H1", "I1", "J1", "K1", "L1", "M1", "N1",
"O1", "P1", "Q1", "R1", "S1", "T1", "U1", "V1", "W1", "X1", "cup",
"Y1", "Z1", ":", "tilde", "backslash", "-10", "larrow", "rarrow" };

char exmaple_temp[30][15] = { "m", "n", "u", "w", "M", "N", "U", "W", "=", "\\Bigsum", "\\infty", "x", "\\theta", "\\beta", "\\to", "\\prime", "\\cup", "\\leftarrow", "\\rightarrow" };
char exmaple_temp_[70][10] = { "0", "2", "3", "4", "5", "6", "7", "8", "9", "a",
"b", "c", "d", "e", "g", "h", "k", "o", "p", "q",
"r", "s", "t", "v", "y", "z", "A", "B", "C", "D",
"E", "F", "G", "H", "K", "O", "P", "Q", "R", "S",
"T", "V", "X", "Y", "Z", "+", "\\leq", "\\geq", ">", "<",
"\\pi", "\\pm", "\\times", "%", ".", "\\lambda", "\\alpha", "\\cdot", "\\ast", "\\div",
"\\ne", "\\in", "\\lt", "\\gt" };

char exmaple_temp__[70][12] = { "1", "f", "g", "h", "i", "j", "l", "!", "I", "J",
"(", "\\big(", "\\bigg(", "\\Big(", "\\Bigg(",
")", "\\big)", "\\bigg)", "\\Big)", "\\Bigg)",
"{", "\\big{", "\\bigg{", "\\Big{", "\\Bigg{",
"}", "\\big}", "\\bigg}", "\\Big}", "\\Bigg}",
"[", "\\big[", "\\bigg[", "\\Big[", "\\Bigg[",
"]", "\\big]", "\\bigg]", "\\Big]", "\\Bigg]",
"\\int", "\\bigint", "\\biggint", "\\Bigint", "\\Biggint",
"\\prod", "\\bigprod", "\\biggprod", "\\Bigprod", "\\Biggprod",
"\\bigsum", "\\biggsum", "\\sum", "\\Bigsum", "\\Biggsum",
"L", ",", "|", "\\delta", "/", ":", "\\tilde", "\\backslash", "?" };

//#define PRINT_INF

//Dimensions dimensions(500, 300);
//Document doc("my_svg.svg", Layout(dimensions, Layout::BottomLeft));
//Document doc("my_svg.svg", Layout(dimensions, Layout::TopLeft));

vector<int> process_new(struct Data_Info* DataROI, int left, int right)
{
	vector<int> Boundary;
	vector<CvPoint> construct;
	for (i = 0; i < right; i++)
	{
		CvPoint a;
		a.x = -1;
		a.y = -1;
		construct.push_back(a);
	}
	//Boundary[n_Boundary++]=(left);

	for (i = left; i < right - 1; i++)
	{
		if (DataROI[i].left > -1 && DataROI[i + 1].left > -1)
		{
			string str_0 = DataROI[i - 1].substring;
			string str_1 = DataROI[i].substring;
			string str_2 = DataROI[i + 1].substring;

			string str_1_substring = str_1.substr(0, 4);
			string str_2_substring = str_2.substr(0, 4);

			index_left = -1;
			index_right = -1;
			for (j = i - 1; j > left - 1; j--)
			{
				string str_3 = DataROI[j].substring;
				if (DataROI[i].width == DataROI[j].Box_width && DataROI[i].height == DataROI[j].Box_height)
				{
					if (DataROI[j].Box_width == DataROI[j].width && DataROI[j].Box_height == DataROI[j].height)
					{
						continue;
					}
					else
					{
						Index_left = j;
						j = left - 1;
					}
				}
				/*2016.1.21修改
				超过根号10c次方以上次幂会渲染出错问题
				*/
				else if(j > 0 && ((DataROI[i].width == ((DataROI[j].width + DataROI[j - 1].width) - 2) ||
					DataROI[i].width == ((DataROI[j].width + DataROI[j - 1].width) - 3)) &&
					DataROI[i].height == (DataROI[j].height - 3) && str_3 == str_1_substring) )
				{
					Index_left = j;
					j = left - 1;
				}
			}
			for (j = i - 1; j > left - 1; j--)
			{
				string str_3 = DataROI[j].substring;
				if (DataROI[i + 1].width == DataROI[j].Box_width && DataROI[i + 1].height == DataROI[j].Box_height)
				{
					if (DataROI[j].Box_width == DataROI[j].width && DataROI[j].Box_height == DataROI[j].height)
					{
						//continue;
						break;
					}
					else
					{
						Index_right = j;
						j = left - 1;
					}
				}
				else if (DataROI[i + 1].width == DataROI[j].Box_width && (abs(DataROI[j].Box_height - DataROI[i + 1].height) < 5) && str_2 == str_3)
				{
					if (DataROI[j].Box_width == DataROI[j].width && DataROI[j].Box_height == DataROI[j].height)
					{
						//continue;
						break;
					}
					else if (DataROI[i + 1].width == (DataROI[i].width - 1) && DataROI[i + 1].height == (DataROI[i].height - 1) && DataROI[i + 1].Box_height == (DataROI[i].Box_height - 1) && DataROI[i + 1].Box_width == (DataROI[i].Box_width - 1))
					{
						break;
					}
					else
					{
						Index_right = j;
						j = left - 1;
					}
				}
				//2016.1.18修改
				//(DataROI[i+1].height == (DataROI[j].Box_height - 2) && DataROI[i+1].width == DataROI[j].Box_width && str_2_substring == "\\fra") 针对除法次方情况： 比如 2^(5/8)
				//(DataROI[i+1].width == DataROI[j].Box_width && ( (DataROI[i].height*0.5 + DataROI[i+1].height) == DataROI[j].Box_height) 针对左上或者右上box大小变动
				//=====================================================================================================================================================================
				else if ( ( (DataROI[i + 1].width == DataROI[j].Box_width && ((DataROI[i].height*0.5 + DataROI[i + 1].height) == DataROI[j].Box_height)
					&& (DataROI[i].height - DataROI[i + 1].height) < 5) || (DataROI[i + 1].height == (DataROI[j].Box_height - 2)
					&& DataROI[i + 1].width == DataROI[j].Box_width && str_2_substring == "\\fra") ) )
					//=====================================================================================================================================================================
				{
					if ((DataROI[j].Box_width == DataROI[j].width && DataROI[j].Box_height == DataROI[j].height) || str_3 == "left" /*|| str_3 == "right"*/)
					{
						//continue;
						break;
					}
					else if (abs(DataROI[i + 1].height - DataROI[j].Box_height) > 7)
					{
						break;
					}
					else
					{
						Index_right = j;
						j = left - 1;
					}
				}
			}


			if (str_2 == Key_W2)
			{
				continue;
			}

			//2016.1.18修改
			//如果右边找到的块在前，都是{ [等符号，不可能是“+”号
			//=============================================================================================
			if (Index_right < Index_left && str_2_substring == "+")
			{
				Index_right = -1;
				DataROI[i + 1].width = DataROI[i + 1].width - 1;   //防止后面将“+”当成重复的字符删掉
				//DataROI[i+1].height = DataROI[i+1].height - 1;
			}
			//防止同一个字符错误找到前面的box
			if (DataROI[i + 1].width == (DataROI[i].width - 1) && DataROI[i + 1].height == (DataROI[i].height - 1) && DataROI[i + 1].Box_height == (DataROI[i].Box_height - 1) && DataROI[i + 1].Box_width == (DataROI[i].Box_width - 1))
			{
				Index_right = Index_left;
			}
			//=============================================================================================


			//===============================================================================================
			/*以下根据Index_left和Index_right的情况判断合并属于哪一种情况?
			常见的情况有三种：
			1. 左边是大块，右边是一个小单元合并情况， Index_left > left && Index_right = -1
			2. 左边是大块，右边也是大块情况，Index_left > left && Index_right > left
			3. 大块的开始，没有合并的情况，Index_left = -1 && Index_right = -1
			*/
			//情况0： \\frac情况
			if (str_1 == Key_W2 && str_2 == Key_W3)
			{
				//找到分子，分母的分界线middle,已经分子的最左边边界
				int middle = -1;
				int min_Boundary = -1;
				for (j = i - 1; j > left; j--)
				{
					string str_1_1 = DataROI[j].substring;
					if (str_1_1 == "-1")
					{
						middle = j;
						DataROI[j].substring = "1";
					}
					if (str_1_1 == "\\frac" && DataROI[j].left == -1)
					{
						min_Boundary = j;
						DataROI[j].substring = "1";
						j = left;
					}
				}

				for (j = i + 1; j < 200; j++)
				{
					string str_1_1 = DataROI[j].substring;
					if (str_1_1 == "\\frac")
					{
						DataROI[j].substring = "1";
						j = 200;
					}
				}

#ifdef PRINT_INF
				printf("====================================================\n");
				for (j = left; j < right; j++)
				{
					printf("%s \n", DataROI[j].substring);
				}
				printf("=====================================================\n");
#endif
				//左边最大宽高
				int max_width_left = -1;
				int max_height_left = -1;
				for (j = middle; j > min_Boundary; j--)
				{
					if (DataROI[j].Box_width > max_width_left)
					{
						max_width_left = DataROI[j].Box_width;
					}
					if (DataROI[j].Box_height > max_height_left)
					{
						max_height_left = DataROI[j].Box_height;
					}
				}

				//右边最大宽高
				int max_width_right = -1;
				int max_height_right = -1;
				for (j = i - 1; j > middle; j--)
				{
					if (DataROI[j].Box_width > max_width_right)
					{
						max_width_right = DataROI[j].Box_width;
					}
					if (DataROI[j].Box_height > max_height_right)
					{
						max_height_right = DataROI[j].Box_height;
					}
				}

				construct[i][0] = min_Boundary;
				construct[i][1] = i;
				construct[i + 1][0] = min_Boundary;
				construct[i + 1][1] = i + 1;

#ifdef PRINT_INF
				for (j = 0; j < i + 2; j++)
				{
					printf("construct%d: %d  %d\n", j, construct[j].x, construct[j].y);
				}
				printf("=======================================================\n");
#endif

				//左块一致修改左上坐标点位置
				for (j = middle; j > min_Boundary; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i].left + DataROI[i].width - max_width_left;
						DataROI[j].top = DataROI[j].top + DataROI[i].top + DataROI[i].height - max_height_left;
					}
				}

				//右块一致修改左上坐标点位置
				for (j = i - 1; j > middle; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i + 1].left + DataROI[i + 1].width - max_width_right;
						DataROI[j].top = DataROI[j].top + DataROI[i + 1].top + DataROI[i + 1].height - max_height_right;
					}
				}
			}
			//array情况
			else if (str_1_substring == Key_W5 && str_2_substring == Key_W5)
			{
				//找到part及array关键字
				int left_left = -1;
				int left_right = -1;
				int right_right = -1;
				for (j = i - 1; j > left; j--)
				{
					string str_1_1 = DataROI[j].substring;
					if (str_1_1 == str_1)
					{
						left_right = j;
					}
					if (str_1_1 == "\\array")
					{
						left_left = j;
					}
					if (str_1_1 == str_2)
					{
						right_right = j;
					}
				}


#ifdef PRINT_INF
				printf("====================================================\n");
				for (j = left; j < right; j++)
				{
					printf("%s \n", DataROI[j].substring);
				}
				printf("=====================================================\n");
#endif

				construct[i][0] = left_left;
				construct[i][1] = i;
				construct[i + 1][0] = left_left;
				construct[i + 1][1] = i + 1;

#ifdef PRINT_INF
				for (j = 0; j < i + 2; j++)
				{
					printf("construct%d: %d  %d\n", j, construct[j].x, construct[j].y);
				}
				printf("=======================================================\n");
#endif

				//左块一致修改左上坐标点位置
				for (j = left_right; j > left_left; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i].left;
						DataROI[j].top = DataROI[j].top + DataROI[i].top;
					}
				}

				//右块一致修改左上坐标点位置
				for (j = right_right; j > left_right; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i + 1].left;
						DataROI[j].top = DataROI[j].top + DataROI[i + 1].top;
					}
				}
			}
			//情况1
			else if (Index_left > left && Index_right == -1 && (i - Index_left) < 5)
			{
				//寻找最左边的边界
				//int min_dis = 10000;
				//int min_Boundary = 0;
				//for (j = 0; j < Boundary.size(); j++)
				//{
				//	int value = Index_left - Boundary[j];
				//	if (value > 0 && value < min_dis)
				//	{
				//		min_dis = value;
				//		min_Boundary = Boundary[j];
				//	}
				//}
				int min_Boundary = construct[Index_left].x;

				construct[i][0] = min_Boundary;
				construct[i][1] = i;
				construct[i + 1][0] = min_Boundary;
				construct[i + 1][1] = i + 1;

#ifdef PRINT_INF
				for (j = 0; j < i + 2; j++)
				{
					printf("construct%d: %d  %d\n", j, construct[j].x, construct[j].y);
				}
				printf("=======================================================\n");
#endif

				//左块一致修改左上坐标点位置
				for (j = i - 1; j > min_Boundary; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i].left;
						DataROI[j].top = DataROI[j].top + DataROI[i].top;
					}
				}
			}
			//情况2
			else if (Index_left > left && Index_right > left && Index_right > Index_left)
			{
				//寻找最左边的边界
				//int min_dis = 10000;
				//int min_Boundary = 0;
				//for (j = 0; j < Boundary.size(); j++)
				//{
				//	int value = Index_left - Boundary[j];
				//	if (value > 0 && value < min_dis)
				//	{
				//		min_dis = value;
				//		min_Boundary = Boundary[j];
				//	}
				//}
				int min_Boundary = construct[Index_left].x;
				construct[i][0] = min_Boundary;
				construct[i][1] = i;
				construct[i + 1][0] = min_Boundary;
				construct[i + 1][1] = i + 1;

#ifdef PRINT_INF
				for (j = 0; j < i + 2; j++)
				{
					printf("construct%d: %d  %d\n", j, construct[j].x, construct[j].y);
				}
				printf("=======================================================\n");
#endif

				//左块一致修改左上坐标点位置
				for (j = Index_left; j > min_Boundary; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i].left;
						DataROI[j].top = DataROI[j].top + DataROI[i].top;
					}
				}

				//右块一致修改左上坐标点位置
				for (j = Index_right; j > Index_left; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i + 1].left;
						DataROI[j].top = DataROI[j].top + DataROI[i + 1].top;
					}
				}
			}
			//情况3
			else if (Index_left > left && Index_right > left && Index_right < Index_left)
			{
				int min_Boundary = construct[Index_right].x;
				construct[i][0] = min(construct[Index_right].x, construct[Index_left].x);
				construct[i][1] = i;
				construct[i + 1][0] = min(construct[Index_right].x, construct[Index_left].x);
				construct[i + 1][1] = i + 1;

#ifdef PRINT_INF
				for (j = 0; j < i + 2; j++)
				{
					printf("construct%d: %d  %d\n", j, construct[j].x, construct[j].y);
				}
				printf("=======================================================\n");
#endif

				if (construct[Index_left].x > min_Boundary)
				{
					//左块一致修改左上坐标点位置
					for (j = Index_left; j > Index_right; j--)
					{
						if (DataROI[j].left > -1)
						{
							DataROI[j].left = DataROI[j].left + DataROI[i].left;
							DataROI[j].top = DataROI[j].top + DataROI[i].top;
						}
					}
				}
				else
				{
					//左块一致修改左上坐标点位置
					for (j = Index_left; j > construct[Index_left].x; j--)
					{
						if (j < min_Boundary || j > Index_right)
						{
							if (DataROI[j].left > -1)
							{
								DataROI[j].left = DataROI[j].left + DataROI[i].left;
								DataROI[j].top = DataROI[j].top + DataROI[i].top;
							}
						}
					}
				}

				//右块一致修改左上坐标点位置
				for (j = Index_right; j > min_Boundary; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i + 1].left;
						DataROI[j].top = DataROI[j].top + DataROI[i + 1].top;
					}
				}
			}
			else if (Index_left > left && Index_right > left && Index_right == Index_left)
			{
				for (j = Index_right - 2; j > left - 1; j--)
				{
					if (DataROI[i].width == DataROI[j].Box_width && DataROI[i].height == DataROI[j].Box_height)
					{
						Index_left = j;
						j = left - 1;
					}
				}

				int Boundary_left = construct[Index_left].x;
				int Boundary_right = construct[Index_right].x;
				construct[i][0] = Boundary_left;
				construct[i][1] = i;
				construct[i + 1][0] = Boundary_left;
				construct[i + 1][1] = i + 1;

#ifdef PRINT_INF
				for (j = 0; j < i + 2; j++)
				{
					printf("construct%d: %d  %d\n", j, construct[j].x, construct[j].y);
				}
				printf("=======================================================\n");
#endif

				//左块一致修改左上坐标点位置
				for (j = Index_left; j > Boundary_left; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i].left;
						DataROI[j].top = DataROI[j].top + DataROI[i].top;
					}
				}

				//右块一致修改左上坐标点位置
				for (j = Index_right; j > Boundary_right; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i + 1].left;
						DataROI[j].top = DataROI[j].top + DataROI[i + 1].top;
					}
				}
			}
			//情况4
			else if (Index_left == -1 && Index_right == -1 && str_0 != Key_W1)
			{
				Boundary[n_Boundary++]=(i - 1);

				construct[i][0] = i - 1;
				construct[i][1] = i;
				construct[i + 1][0] = i - 1;
				construct[i + 1][1] = i + 1;

#ifdef PRINT_INF
				for (j = 0; j < i + 2; j++)
				{
					printf("construct%d: %d  %d\n", j, construct[j].x, construct[j].y);
				}
				printf("=======================================================\n");
#endif

			}
			//情况4.1
			else if (Index_left == -1 && Index_right == -1 && str_0 == Key_W1 && str_2 == Key_W1)
			{
				Boundary[n_Boundary++]=(i - 1);

				construct[i][0] = i - 1;
				construct[i][1] = i;
				construct[i + 1][0] = i - 1;
				construct[i + 1][1] = i + 1;

#ifdef PRINT_INF
				for (j = 0; j < i + 2; j++)
				{
					printf("construct%d: %d  %d\n", j, construct[j].x, construct[j].y);
				}
				printf("=======================================================\n");
#endif

			}
			//情况4.2
			else if (Index_left == -1 && Index_right == -1 && str_0 == Key_W1 && str_2 != Key_W1 && str_1 != "Box")
			{
				Boundary[n_Boundary++]=(i - 1);

				construct[i][0] = i - 1;
				construct[i][1] = i;
				construct[i + 1][0] = i - 1;
				construct[i + 1][1] = i + 1;

#ifdef PRINT_INF
				for (j = 0; j < i + 2; j++)
				{
					printf("construct%d: %d  %d\n", j, construct[j].x, construct[j].y);
				}
				printf("=======================================================\n");
#endif

			}
			//情况5
			else if (Index_left == -1 && Index_right == -1 && str_0 == Key_W1 && str_1 == "Box")
			{
				int min_Boundary = 0;
				for (j = i - 2; j > left - 1; j--)
				{
					string str_1_1 = DataROI[j].substring;
					if (str_1_1 == Key_W1)
					{
						min_Boundary = j;
						j = left - 1;
					}
				}

				construct[i][0] = min_Boundary;
				construct[i][1] = i;
				construct[i + 1][0] = min_Boundary;
				construct[i + 1][1] = i + 1;

#ifdef PRINT_INF
				for (j = 0; j < i + 2; j++)
				{
					printf("construct%d: %d  %d\n", j, construct[j].x, construct[j].y);
				}
				printf("=======================================================\n");
#endif

				//左边最大宽高
				int max_width_left = -1;
				int max_height_left = -1;
				for (j = i - 2; j > min_Boundary; j--)
				{
					if (DataROI[j].Box_width > max_width_left)
					{
						max_width_left = DataROI[j].Box_width;
					}
					if (DataROI[j].Box_height > max_height_left)
					{
						max_height_left = DataROI[j].Box_height;
					}
				}

				//左块一致修改左上坐标点位置
				for (j = i - 2; j > min_Boundary; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i].left + DataROI[i].width - max_width_left;
						DataROI[j].top = DataROI[j].top + DataROI[i].top + DataROI[i].height - max_height_left;
					}
				}
			}

#if 1
			//情况6：一般都是\\sqrt \\prac等造成的， 左边找到了边界，右边没有找到边界
			else if (Index_left > left && Index_right == -1 && (i - Index_left) > 5)
			{
				////寻找最左边的边界
				//int min_dis = 10000;
				//int min_Boundary = 0;
				//for (j = 0; j < Boundary.size(); j++)
				//{
				//	int value = Index_left - Boundary[j];
				//	if (value > 0 && value < min_dis)
				//	{
				//		min_dis = value;
				//		min_Boundary = Boundary[j];
				//	}
				//}

				int min_Boundary = construct[Index_left].x;
				construct[i][0] = min_Boundary;
				construct[i][1] = i;
				construct[i + 1][0] = min_Boundary;
				construct[i + 1][1] = i + 1;

#ifdef PRINT_INF
				for (j = 0; j < i + 2; j++)
				{
					printf("construct%d: %d  %d\n", j, construct[j].x, construct[j].y);
				}
				printf("=======================================================\n");
#endif

				//左块一致修改左上坐标点位置
				for (j = Index_left; j > min_Boundary; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i].left;
						DataROI[j].top = DataROI[j].top + DataROI[i].top;
					}
				}

				//右块一致修改左上坐标点位置
				int max_batch_width = 0;
				int max_batch_height = 0;

				for (j = i - 1; j > Index_left; j--)
				{
					if (DataROI[j].Box_width > max_batch_width)
					{
						max_batch_width = DataROI[j].Box_width;
					}
					if (DataROI[j].Box_height > max_batch_height)
					{
						max_batch_height = DataROI[j].Box_height;
					}
				}

				for (j = i - 1; j > Index_left; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i + 1].left + DataROI[i + 1].width - max_batch_width;
						DataROI[j].top = DataROI[j].top + DataROI[i + 1].top + DataROI[i + 1].height - max_batch_height;
					}
				}
			}
			//情况7：左边没有找到边界，右边找到边界
			else if (Index_left == -1 && Index_right > left && str_1 != Key_W2)
			{
				//寻找最左边的边界
				//int min_dis = 10000;
				//int min_Boundary = 0;
				//for (j = 0; j < Boundary.size(); j++)
				//{
				//	int value = Index_right - Boundary[j];
				//	if (value > 0 && value < min_dis)
				//	{
				//		min_dis = value;
				//		min_Boundary = Boundary[j];
				//	}
				//}

				int min_Boundary = construct[Index_right].x;
				construct[i][0] = min_Boundary;
				construct[i][1] = i;
				construct[i + 1][0] = min_Boundary;
				construct[i + 1][1] = i + 1;

#ifdef PRINT_INF
				for (j = 0; j < i + 2; j++)
				{
					printf("construct%d: %d  %d\n", j, construct[j].x, construct[j].y);
				}
				printf("=======================================================\n");
#endif

				//右块一致修改左上坐标点位置
				for (j = Index_right; j > min_Boundary; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i + 1].left;
						DataROI[j].top = DataROI[j].top + DataROI[i + 1].top;
					}
				}

			}
#endif

		}

		//printf("******************************************************************\n\n");
		//for (j = 0; j < i+1; j++)
		//{
		//	printf("%s  ", DataROI[j].substring);
		//	if (DataROI[j].left > -1 && DataROI[j].left < 10000)
		//	{
		//		printf("%d  %d  %d  %d  %d  %d", DataROI[j].left, DataROI[j].top, DataROI[j].width, DataROI[j].height, DataROI[j].Box_width, DataROI[j].Box_height);
		//	}
		//	printf("\n");
		//}
		//printf("##########(%d)\n", i+1);
	}
	return Boundary;
}

int Adjust_Data(Data_Info* DataROI_New, Data_Info* DataROI_New_New, vector<int> Boundary, int &max_width, int &max_height, int cnt)
{
	//printf("******************************************************************\n\n");
	for (i = 0; i < cnt; i++)
	{
		//printf("%s  ", DataROI_New[i].substring);
		//if (DataROI_New[i].left > -1 && DataROI_New[i].left < 10000)
		//{
		//	printf("%d  %d  %d  %d  %d  %d", DataROI_New[i].left, DataROI_New[i].top, DataROI_New[i].width, DataROI_New[i].height, DataROI_New[i].Box_width, DataROI_New[i].Box_height);
		//}
		//printf("\n");
		if (DataROI_New[i].Box_width > max_width)
		{
			max_width = DataROI_New[i].Box_width;
		}
		if (DataROI_New[i].Box_height > max_height)
		{
			max_height = DataROI_New[i].Box_height;
		}
	}

	int count = 0;
	for (i = 1; i < cnt - 1; i++)
	{
		if (DataROI_New[i].left > -1)
		{
			string str_1_1 = DataROI_New[i - 1].substring;
			string str_1_3 = DataROI_New[i].substring;
			string str_1_2 = DataROI_New[i + 1].substring;

			index_left = -1;
			index_right = -1;
			if (DataROI_New[i].left > -1 && DataROI_New[i + 1].left > -1)
			{
				for (j = i - 1; j > 0; j--)
				{
					if (DataROI_New[i].width == DataROI_New[j].Box_width && DataROI_New[i].height == DataROI_New[j].Box_height)
					{
						Index_left = j;
						j = 0;
					}
				}
				for (j = i - 1; j > 0; j--)
				{
					if (DataROI_New[i + 1].width == DataROI_New[j].Box_width && DataROI_New[i + 1].height == DataROI_New[j].Box_height)
					{
						Index_right = j;
						j = 0;
					}
				}
			}

			if (str_1_3 == "right" || str_1_3 == "left" || str_1_3 == "Box")
			{
				continue;
			}
			else if (Index_left > -1 && Index_right > -1)
			{
				if ((DataROI_New[i].width - DataROI_New[i + 1].width) == 1 && (DataROI_New[i].height - DataROI_New[i + 1].height) == 1)
				{
					DataROI_New_New[count] = DataROI_New[i];
					count++;
				}
				else if ((DataROI_New[i].width - DataROI_New[i - 1].width) == -1 && (DataROI_New[i].height - DataROI_New[i - 1].height) == -1)
				{
					continue;
				}
				else if (DataROI_New[Index_left].width == DataROI_New[Index_left].Box_width && DataROI_New[Index_left].height == DataROI_New[Index_left].Box_height)
				{
					DataROI_New_New[count] = DataROI_New[i];
					count++;
				}
				else if (DataROI_New[Index_right].width == DataROI_New[Index_right].Box_width && DataROI_New[Index_right].height == DataROI_New[Index_right].Box_height)
				{
					continue;
				}
				else
				{
					i = i + 1;
				}
			}//这里存在漏洞，有时间必须修改这里代码！！！！！！！！！！！！！！！！！！！
			else if (DataROI_New[i - 1].left == -1 && DataROI_New[i].left > -1 && (DataROI_New[i + 1].left > DataROI_New[i].left || DataROI_New[i + 1].top > DataROI_New[i].top) && (str_1_1 != Key_W1 && str_1_1 != Key_W0))
			{
				DataROI_New_New[count] = DataROI_New[i];
				count++;
			}//这里存在漏洞，有时间必须修改这里代码！！！！！！！！！！！！！！！！！！！
			else if (DataROI_New[i + 1].left == -1 && DataROI_New[i].left > -1 && (DataROI_New[i].left > DataROI_New[i - 1].left || DataROI_New[i].top > DataROI_New[i - 1].top) && (str_1_2 != Key_W1 && str_1_2 != Key_W0))
			{
				DataROI_New_New[count] = DataROI_New[i];
				count++;
			}
			else
			{
				for (j = 0; j < Boundary.size(); j++)
				{
					if (Boundary[j] == (i - 1) && DataROI_New[i].left > -1)
					{
						DataROI_New_New[count] = DataROI_New[i];
						count++;
					}
				}
			}
		}
	}
	return count;
}

int Adjust_Data_new(Data_Info* DataROI_New, Data_Info* DataROI_New_New, vector<int> Boundary, int &max_width, int &max_height, int cnt)
{
#ifdef PRINT_INF
	//printf("******************************************************************\n\n");
#endif
	for (i = 0; i < cnt; i++)
	{
#ifdef PRINT_INF
		printf("%s  ", DataROI_New[i].substring);
		if (DataROI_New[i].left > -1 && DataROI_New[i].left < 10000)
		{
			printf("%d  %d  %d  %d  %d  %d", DataROI_New[i].left, DataROI_New[i].top, DataROI_New[i].width, DataROI_New[i].height, DataROI_New[i].Box_width, DataROI_New[i].Box_height);
		}
		printf("\n");
#endif
		if (DataROI_New[i].Box_width > max_width)
		{
			max_width = DataROI_New[i].Box_width;
		}
		if (DataROI_New[i].Box_height > max_height)
		{
			max_height = DataROI_New[i].Box_height;
		}
	}

	int count = 0;
	for (i = 1; i < cnt - 1; i++)
	{
		if (DataROI_New[i].left > -1)
		{
			string str = DataROI_New[i].substring;
			bool condition1 = false;
			bool condition2 = false;
			bool condition3 = false;
			bool condition4 = false;
			bool condition5 = false;
			for (j = 0; j < 30; j++)
			{
				if (str == exmaple_temp[j])
				{
					condition1 = true;
				}
			}
			for (j = 0; j < 70; j++)
			{
				if (str == exmaple_temp_[j])
				{
					condition2 = true;
				}
			}
			for (j = 0; j < 70; j++)
			{
				if (str == exmaple_temp__[j])
				{
					condition3 = true;
				}
			}


			if (DataROI_New[i - 1].left  > -1)
			{
				if ((DataROI_New[i - 1].Box_height - DataROI_New[i].Box_height == 1) && (DataROI_New[i - 1].Box_width - DataROI_New[i].Box_width == 1))
				{
					continue;
				}
			}

			if (!strcmp(str,"right" || !strcmp(str,"left" || !strcmp(str,"Box")
			{
				continue;
			}

			if (!strcmp(str,"(" || !strcmp(str,"\\big(" || !strcmp(str,"\\bigg(" || !strcmp(str,"\\Big(" || !strcmp(str,"\\Bigg(" ||
				!strcmp(str,")" || !strcmp(str,"\\big)" || !strcmp(str,"\\bigg)" || !strcmp(str,"\\Big)" || !strcmp(str,"\\Bigg)" ||
				!strcmp(str,"{" || !strcmp(str,"\\big{" || !strcmp(str,"\\bigg{" || !strcmp(str,"\\Big{" || !strcmp(str,"\\Bigg{" ||
				!strcmp(str,"}" || !strcmp(str,"\\big}" || !strcmp(str,"\\bigg}" || !strcmp(str,"\\Big}" || !strcmp(str,"\\Bigg}" ||
				!strcmp(str,"[" || !strcmp(str,"\\big[" || !strcmp(str,"\\bigg[" || !strcmp(str,"\\Big[" || !strcmp(str,"\\Bigg[" ||
				!strcmp(str,"]" || !strcmp(str,"\\big]" || !strcmp(str,"\\bigg]" || !strcmp(str,"\\Big]" || !strcmp(str,"\\Bigg]" ||
				!strcmp(str,"\\int" || !strcmp(str,"\\bigint" || !strcmp(str,"\\biggint" || !strcmp(str,"\\Bigint" || !strcmp(str,"\\Biggint" ||
				!strcmp(str,"\\prod" || !strcmp(str,"\\bigprod" || !strcmp(str,"\\biggprod" || !strcmp(str,"\\Bigprod" || !strcmp(str,"\\Biggprod" ||
				!strcmp(str,"\\bigsum" || !strcmp(str,"\\biggsum" || !strcmp(str,"\\sum" || !strcmp(str,"\\Bigsum" || !strcmp(str,"\\Biggsum" ||
				!strcmp(str,"/" || !strcmp(str,":" || !strcmp(str,"\\tilde" || !strcmp(str,"\\backslash" || !strcmp(str,"?")
				//if(!strcmp(str,"\\Bigsum" || !strcmp(str,"\\bigg{" || !strcmp(str,"\\Big(" || !strcmp(str,"\\Big)" || !strcmp(str,"\\Big{" || !strcmp(str,"\\Bigg{" || !strcmp(str,"\\Bigprod" || !strcmp(str,"\\Bigint"
				//	|| !strcmp(str,"[" || str =="]" || !strcmp(str,"/" || !strcmp(str,"\\big(" || !strcmp(str,"\\big)" || !strcmp(str,"\\big{" || !strcmp(str,"\\big}"  || !strcmp(str,"\\bigg}" || !strcmp(str,"\\Bigg[" || !strcmp(str,"\\Bigg]"
				//	|| !strcmp(str,"\\Big[" || !strcmp(str,"\\Big]" || !strcmp(str,"\\big[" || !strcmp(str,"\\big]" || !strcmp(str,"\\bigg[" || !strcmp(str,"\\bigg]" || !strcmp(str,":" || !strcmp(str,"{" || !strcmp(str,"}" || !strcmp(str,"Bigg}"
				//	|| !strcmp(str,"Big}")
			{
				if (max(DataROI_New[i].width, DataROI_New[i].height) > 80)
					continue;
			}
			else
			{
				if (max(DataROI_New[i].width, DataROI_New[i].height) > 30)
					continue;
			}

			for (j = 0; j < Boundary.size(); j++)
			{
				if (Boundary[j] == (i - 2) && DataROI_New[i].left > -1)
				{
					condition4 = true;
				}
			}

			for (j = i - 1; j > -1; j--)
			{
				string str1 = DataROI_New[j].substring;
				if (DataROI_New[i].width == DataROI_New[j].Box_width && DataROI_New[i].height == DataROI_New[j].Box_height)
				{
					if (DataROI_New[j].width != DataROI_New[j].Box_width || DataROI_New[j].height != DataROI_New[j].Box_height)
					{
						condition5 = true;
					}
					break;
				}
				if (j > 0)
				if ((DataROI_New[i].width == ((DataROI_New[j].width + DataROI_New[j - 1].width) - 2) || DataROI_New[i].width == ((DataROI_New[j].width + DataROI_New[j - 1].width) - 3)) && DataROI_New[i].height == (DataROI_New[j].Box_height - 3) && str1 == DataROI_New[i].substring)
				{
					condition5 = true;
				}
			}

			if (condition5)
			{
				continue;
			}


			if (condition1 && (DataROI_New[i].width - DataROI_New[i].height < 15))
			{
				DataROI_New_New[count] = DataROI_New[i];
				count++;
			}
			else if (condition4)
			{
				DataROI_New_New[count] = DataROI_New[i];
				count++;
			}
			else if (!strcmp(str,"-" && DataROI_New[i].height == 1)
			{
				DataROI_New_New[count] = DataROI_New[i];
				count++;
			}
			else if (condition2 && (DataROI_New[i].width - DataROI_New[i].height < 8))
			{
				DataROI_New_New[count] = DataROI_New[i];
				count++;
			}
			else if (condition3 && (DataROI_New[i].width < DataROI_New[i].height))
			{
				DataROI_New_New[count] = DataROI_New[i];
				count++;
			}
		}
	}
	return count;
}

void Extract_Data(Data_Info* DataROI_New_New, vector<Draw_Information> &Result, int count)
{
	for (i = 0; i < count; i++)
	{
		if (i > 0 && DataROI_New_New[i].left > -1)
		{
			bool keep_on = false;
			string str = DataROI_New_New[i].substring;
			for (j = i - 1; j > 0; j--)
			{
				string str1 = DataROI_New_New[j].substring;
				if (DataROI_New_New[i].width == DataROI_New_New[j].Box_width && DataROI_New_New[i].height == DataROI_New_New[j].Box_height /*&& DataROI_New_New[j].width != DataROI_New_New[j].Box_width && DataROI_New_New[j].height != DataROI_New_New[j].Box_height*/)
				{
					keep_on = true;
					if (DataROI_New_New[i].width == DataROI_New_New[i].Box_width && DataROI_New_New[i].height == DataROI_New_New[i].Box_height)
					{
						keep_on = false;
					}
					if (DataROI_New_New[j].width == DataROI_New_New[j].Box_width && DataROI_New_New[j].height == DataROI_New_New[j].Box_height)
					{
						keep_on = false;
					}
					if ((str1 == str && DataROI_New_New[j].width != DataROI_New_New[i].width) || (str1 == str && (DataROI_New_New[j].height != DataROI_New_New[i].height)))
					{
						keep_on = true;
					}
					if (DataROI_New_New[i].left > DataROI_New_New[i - 1].left)
					{
						keep_on = false;
					}
					if (str1 == str && (DataROI_New_New[j].width != DataROI_New_New[j].Box_width || DataROI_New_New[j].height != DataROI_New_New[j].Box_height))
					{
						keep_on = false;
					}
					j = 0;
				}
				else if (DataROI_New_New[i].width == DataROI_New_New[j].Box_width && ((DataROI_New_New[j].Box_height - DataROI_New_New[i].height) == 4 || (DataROI_New_New[j].Box_height - DataROI_New_New[i].height) == 2 /*|| (DataROI_New_New[i].height - DataROI_New_New[j].Box_height) == 1*/) && str == str1)
				{
					keep_on = true;
				}
			}
			if (keep_on)
			{
				continue;
			}

			if (DataROI_New_New[i].width * DataROI_New_New[i].height > 1000 && DataROI_New_New[i].height < 50)
			{
				continue;
			}
		}
#ifdef PRINT_INF
		printf("%s  ", DataROI_New_New[i].substring);
		if (DataROI_New_New[i].left > -1 && DataROI_New_New[i].left < 10000)
		{
			printf("%d  %d  %d  %d  %d  %d", DataROI_New_New[i].left, DataROI_New_New[i].top, DataROI_New_New[i].width, DataROI_New_New[i].height, DataROI_New_New[i].Box_width, DataROI_New_New[i].Box_height);
		}
		printf("\n");
#endif

		Draw_Information result;
		CvRect rect;
		rect.x = DataROI_New_New[i].left;
		//rect.y = max_height - (DataROI_New_New[i].top + DataROI_New_New[i].height);
		rect.y = DataROI_New_New[i].top;
		rect.width = DataROI_New_New[i].width;
		rect.height = DataROI_New_New[i].height;
		result.str = DataROI_New_New[i].substring;
		result.rect = rect;
		Result.push_back(result);
	}
}

IplImage* Draw_Render_Image(IplImage* src, vector<Draw_Information> Result, int max_height, int max_width)
{
	vector<DataInfo> Data_MY;
	int Step_width_left = 0;
	int Step_width_right = 0;
	for (i = 0; i < src->width; i++)
	{
		for (j = 0; j < src->height; j++)
		{
			int value = ((uchar*)(src->imageData + j * src->widthStep))[i];
			if (value > 0)
			{
				Step_width_left = i;
				i = src->width;
				j = src->height;
			}
		}
	}

	int max_width_new = src->width - (Step_width_left);
	int max_height_new = max_height;

	IplImage* src_new_ = cvCreateImage(cvSize(max_width_new, max_height_new), 8, 1);
	IplImage* src_new__ = cvCreateImage(cvSize(max_width_new + 2, max_height_new + 2), 8, 1);
	IplImage* src_new_gray = cvCreateImage(cvSize(max_width_new * SCALES, max_height_new * SCALES + 40), 8, 3);
	IplImage* src_new_gray_copy = cvCreateImage(cvSize(max_width_new * SCALES, max_height_new * SCALES + 40), 8, 1);
	IplImage* src_new_show = cvCreateImage(cvSize(max_width_new * SCALES + 200, max_height_new * SCALES + 200), 8, 3);
	cvZero(src_new_);
	cvZero(src_new__);

	int move_height = 0;
	int move_width = max_width_new - max_width;

	for (i = 0; i < max_height_new; i++)
	{
		for (j = Step_width_left; j < src->width; j++)
		{
			if (i < src->height)
			{
				int value = ((uchar*)(src->imageData + i * src->widthStep))[j];
				if (value >100)
				{
					index = j - (Step_width_left) / 2;// floor((src->width - max_width_new)*0.5);
					((char*)(src_new_->imageData + i * src_new_->widthStep))[index] = 255;
					//cvSetReal2D(src_new_, i, j - floor((src->width - max_width_new)*0.5), 255);
				}
			}
		}
	}
	//cvShowImage("9", src);
	//cvShowImage("3", src_new_);
	//cvWaitKey(0);

	for (i = 0; i < src_new_show->height; i++)
	{
		for (j = 0; j < src_new_show->width; j++)
		{
			//cvSet2D(src_new_show, i, j, CV_RGB(255, 255, 255));
			((uchar*)(src_new_show->imageData + i * src_new_show->widthStep))[j * 3 + 0] = 255;
			((uchar*)(src_new_show->imageData + i * src_new_show->widthStep))[j * 3 + 1] = 255;
			((uchar*)(src_new_show->imageData + i * src_new_show->widthStep))[j * 3 + 2] = 255;
			if (i < src_new_gray->height && j < src_new_gray->width)
			{
				((uchar*)(src_new_gray->imageData + i * src_new_gray->widthStep))[j * 3 + 0] = 255;
				((uchar*)(src_new_gray->imageData + i * src_new_gray->widthStep))[j * 3 + 1] = 255;
				((uchar*)(src_new_gray->imageData + i * src_new_gray->widthStep))[j * 3 + 2] = 255;
			}
		}
	}

#if 1

	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contour = 0;
	CvRect rect_;
	rect_.x = 1;
	rect_.y = 1;
	rect_.width = src_new_->width;
	rect_.height = src_new_->height;
	cvSetImageROI(src_new__, rect_);
	cvCopy(src_new_, src_new__);
	cvResetImageROI(src_new__);


	for (i = 0; i < Result.size(); i++)
	{
		for (int m = Result[i].rect.y + move_height; m < Result[i].rect.y + move_height + Result[i].rect.height; m++)
		{
			for (int n = Result[i].rect.x + Step_width_left; n < Result[i].rect.x + Step_width_left + Result[i].rect.width; n++)
			{
				if (m < 0)
					continue;
				if (m > src_new_->height - 1)
					continue;
				if (n < 0)
					continue;
				if (n > src_new_->width - 1)
					continue;

				//cvSetReal2D(src_new_, m, n, 255);
				((uchar*)(src_new_->imageData + m * src_new_->widthStep))[n] = 255;
			}
		}
	}
	//cvShowImage("3", src_new_copy);
	//cvWaitKey(0);



	// 提取轮廓
	vector<CvRect> Result_new;
	int contour_num = cvFindContours(src_new__, storage, &contour, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	for (; contour != 0; contour = contour->h_next)
	{
		CvRect aRect = cvBoundingRect(contour, 0);
		aRect.x = aRect.x - 1;
		aRect.y = aRect.y - 1;
		double rate = double(aRect.width) / double(aRect.height);


		double count_x = 0;
		for (int m = aRect.y; m < aRect.y + aRect.height; m++)
		{
			for (int n = aRect.x; n < aRect.x + aRect.width; n++)
			{
				int value = ((uchar*)(src_new_->imageData + m * src_new_->widthStep))[n];
				if (value > 50)
				{
					count_x++;
				}
			}
		}
		float rate_1 = count_x / (aRect.width*aRect.height);


		if (rate > 3 && aRect.height < 3)
		{
			bool control = true;
			//for (j = 0; j < Result.size(); j++)
			//{
			//	if ((aRect.x - (Result[j].rect.x + move_width)) < 3 && (aRect.y - (Result[j].rect.y + move_height)) < 3 && ((aRect.width / double(aRect.height)) - (Result[j].rect.width / (double)(Result[j].rect.height)) < 3.0))
			//	{
			//		control = false;
			//	}
			//}
			if (control)
			{
				//aRect.y = aRect.y ;
				Result_new.push_back(aRect);
			}
		}


		if (rate_1 < 0.85)//根号
		{
			bool control = false;
			for (j = 0; j < Result.size(); j++)
			{
				if ((aRect.x - (Result[j].rect.x + move_width)) < 3 && (aRect.y - (Result[j].rect.y + move_height)) < 3 && (aRect.width - Result[j].rect.width) < 2 && (aRect.height - Result[j].rect.height) < 2)
				{
					control = true;
				}
			}
			if (control)
			{
				continue;
			}


			CvPoint R1, R2, R3, R4;
			//最左边的点
			for (int m = aRect.x; m < aRect.x + aRect.width; m++)
			{
				for (int n = aRect.y; n < aRect.y + aRect.height; n++)
				{
					int value = ((uchar*)(src_new_->imageData + n * src_new_->widthStep))[m];
					if (value > 10)
					{
						R1.x = m;
						R1.y = n;
						n = aRect.y + aRect.height;
						m = aRect.x + aRect.width;
					}
				}
			}

			//最下面的点
			for (int m = aRect.y + aRect.height - 1; m > aRect.y; m--)
			{
				for (int n = aRect.x; n < aRect.x + aRect.width; n++)
				{
					int value = ((uchar*)(src_new_->imageData + m * src_new_->widthStep))[n];
					if (value > 10)
					{
						R2.x = n;
						R2.y = m;
						m = aRect.y;
						n = aRect.x + aRect.width;
					}
				}
			}

			//最右边的点
			for (int m = aRect.x + aRect.width - 1; m > aRect.x; m--)
			{
				for (int n = aRect.y; n < aRect.y + aRect.height; n++)
				{
					int value = ((uchar*)(src_new_->imageData + n * src_new_->widthStep))[m];
					if (value > 10)
					{
						R3.x = m;
						R3.y = n;
						m = aRect.x;
						n = aRect.y + aRect.height;
					}
				}
			}
			int count = 0;
			for (int m = R3.x - 3; m < R3.x + 1; m++)
			{
				int value = ((uchar*)(src_new_->imageData + R3.y * src_new_->widthStep))[m];
				if (value > 10)
					count++;
			}

			R4.x = R2.x + R2.x - R1.x;
			R4.y = R3.y;

			R1.y = (R2.y + R3.y)*0.5;

			R1.x = R1.x + 2;
			R2.x = R2.x + 2;
			R3.x = R3.x + 2;
			R4.x = R4.x + 2;

			if ((R2.y - R1.y) > 2 && (rate > 1.0 || count == 4) && rate_1 < 0.8)
			{
				cvLine(src_new_gray, cvPoint(R1.x * SCALES, R1.y * SCALES), cvPoint(R2.x * SCALES, R2.y * SCALES), CV_RGB(0, 0, 0), max(2, SCALES / 2), CV_AA, 0);
				cvLine(src_new_gray, cvPoint(R2.x * SCALES, R2.y * SCALES), cvPoint(R4.x * SCALES, R4.y * SCALES), CV_RGB(0, 0, 0), max(2, SCALES / 2), CV_AA, 0);
				cvLine(src_new_gray, cvPoint(R4.x * SCALES, R4.y * SCALES), cvPoint(R3.x * SCALES, R3.y * SCALES), CV_RGB(0, 0, 0), max(2, SCALES / 2), CV_AA, 0);
			}
		}
	}
	cvCvtColor(src_new_gray, src_new_gray_copy, CV_RGB2GRAY);


	for (i = 0; i < Result.size(); i++)
	{
		string str = Result[i].str;
		string str_my = str;

		if (!strcmp(str,"\\pm")
		{
			str = "-1";
			str_my = "117";
		}
		else if (!strcmp(str,"\\big(" || !strcmp(str,"\\bigg(" || !strcmp(str,"(" || !strcmp(str,"\\Big(" || !strcmp(str,"\\Bigg(")
		{
			str = "(";
			str_my = "(";
		}
		else if (!strcmp(str,"\\big)" || !strcmp(str,"\\bigg)" || !strcmp(str,")" || !strcmp(str,"\\Big)" || !strcmp(str,"\\Bigg)")
		{
			str = ")";
			str_my = ")";
		}
		else if (!strcmp(str,"\\times")
		{
			str = "-2";
			str_my = "120";
		}
		else if (!strcmp(str,"\\bigg{" || !strcmp(str,"\\big{" || !strcmp(str,"{" || !strcmp(str,"\\Big{" || !strcmp(str,"\\Bigg{")
		{
			str = "{";
			str_my = "{";
		}
		else if (!strcmp(str,"\\bigg}" || !strcmp(str,"\\big}" || !strcmp(str,"}" || !strcmp(str,"\\Big}" || !strcmp(str,"\\Bigg}")
		{
			str = "}";
			str_my = "}";
		}
		else if (!strcmp(str,"\\bigsum" || !strcmp(str,"\\biggsum" || !strcmp(str,"\\sum" || !strcmp(str,"\\Bigsum" || !strcmp(str,"\\Biggsum")
		{
			str = "sum";
			str_my = "55";
		}
		else if (!strcmp(str,"\\infty")
		{
			str = "infty";
			str_my = "105";
		}
		else if (!strcmp(str,"\\pi")
		{
			str = "pi";
			str_my = "84";
		}
		else if (!strcmp(str,"<" || !strcmp(str,"\\lt")
		{
			str = "-3";
			str_my = "32";
		}
		else if (!strcmp(str,">" || !strcmp(str,"\\gt")
		{
			str = "-4";
			str_my = "34";
		}
		else if (!strcmp(str,"\\leq")
		{
			str = "-5";
			str_my = "103";
		}
		else if (!strcmp(str,"\\geq")
		{
			str = "-6";
			str_my = "119";
		}
		else if (!strcmp(str,"|")
		{
			str = "-7";
			str_my = "129";
		}
		else if (!strcmp(str,"A")
		{
			str = "A1";
			str_my = "A";
		}
		else if (!strcmp(str,"B")
		{
			str = "B1";
			str_my = "B";
		}
		else if (!strcmp(str,"C")
		{
			str = "C1";
			str_my = "C";
		}
		else if (!strcmp(str,"D")
		{
			str = "D1";
			str_my = "D";
		}
		else if (!strcmp(str,"E")
		{
			str = "E1";
			str_my = "E";
		}
		else if (!strcmp(str,"F")
		{
			str = "F1";
			str_my = "F";
		}
		else if (!strcmp(str,"G")
		{
			str = "G1";
			str_my = "G";
		}
		else if (!strcmp(str,"H")
		{
			str = "H1";
			str_my = "H";
		}
		else if (!strcmp(str,"I")
		{
			str = "I1";
			str_my = "I";
		}
		else if (!strcmp(str,"J")
		{
			str = "J1";
			str_my = "J";
		}
		else if (!strcmp(str,"K")
		{
			str = "K1";
			str_my = "K";
		}
		else if (!strcmp(str,"L")
		{
			str = "L1";
			str_my = "L";
		}
		else if (!strcmp(str,"M")
		{
			str = "M1";
			str_my = "M";
		}
		else if (!strcmp(str,"N")
		{
			str = "N1";
			str_my = "N";
		}
		else if (!strcmp(str,"O")
		{
			str = "O1";
			str_my = "O";
		}
		else if (!strcmp(str,"P")
		{
			str = "P1";
			str_my = "P";
		}
		else if (!strcmp(str,"Q")
		{
			str = "Q1";
			str_my = "Q";
		}
		else if (!strcmp(str,"R")
		{
			str = "R1";
			str_my = "R";
		}
		else if (!strcmp(str,"S")
		{
			str = "S1";
			str_my = "S";
		}
		else if (!strcmp(str,"T")
		{
			str = "T1";
			str_my = "T";
		}
		else if (!strcmp(str,"U")
		{
			str = "U1";
			str_my = "U";
		}
		else if (!strcmp(str,"V")
		{
			str = "V1";
			str_my = "V";
		}
		else if (!strcmp(str,"W")
		{
			str = "W1";
			str_my = "W";
		}
		else if (!strcmp(str,"X")
		{
			str = "X1";
			str_my = "X";
		}
		else if (!strcmp(str,"Y")
		{
			str = "Y1";
			str_my = "Y";
		}
		else if (!strcmp(str,"Z")
		{
			str = "Z1";
			str_my = "Z";
		}
		else if (!strcmp(str,".")
		{
			str = "-8";
			str_my = "100";
		}
		else if (!strcmp(str,"\\lambda")
		{
			str = "lambda";
			str_my = "80";
		}
		else if (!strcmp(str,"\\alpha")
		{
			str = "alpha";
			str_my = "69";
		}
		else if (!strcmp(str,"\\theta")
		{
			str = "theta";
			str_my = "85";
		}
		else if (!strcmp(str,"\\beta")
		{
			str = "beta";
			str_my = "70";
		}
		else if (!strcmp(str,"\\delta")
		{
			str = "delta";
			str_my = "72";
		}
		else if (!strcmp(str,"\\cdot")
		{
			str = "-8";
			str_my = "100";
		}
		else if (!strcmp(str,"\\ast")
		{
			str = "ast";
			str_my = "14";
		}
		else if (!strcmp(str,"\\div")
		{
			str = "div";
			str_my = "124";
		}
		else if (!strcmp(str,"\\ne")
		{
			str = "ne";
			str_my = "125";
		}
		else if (!strcmp(str,"\\bigprod" || !strcmp(str,"\\biggprod" || !strcmp(str,"\\prod" || !strcmp(str,"\\Bigprod" || !strcmp(str,"\\Biggprod")
		{
			str = "prod";
			str_my = "52";
		}
		else if (!strcmp(str,"\\bigint" || !strcmp(str,"\\biggint" || !strcmp(str,"\\int" || !strcmp(str,"\\Bigint" || !strcmp(str,"\\Biggint")
		{
			str = "int";
			str_my = "182";
		}
		else if (!strcmp(str,"\\in")
		{
			str = "in";
			str_my = "146";
		}
		else if (!strcmp(str,"/")
		{
			str = "-9";
			str_my = "104";
		}
		else if (!strcmp(str,"\\to")
		{
			str = "to";
			str_my = "114";
		}
		else if (!strcmp(str,"\\prime")
		{
			str = "'";
			str_my = "'";
		}
		else if (!strcmp(str,"\\cup")
		{
			str = "cup";
			str_my = "140";
		}
		else if (!strcmp(str,"\\Bigg[" || !strcmp(str,"\\Big[" || !strcmp(str,"[" || !strcmp(str,"\\big[" || !strcmp(str,"\\bigg[")
		{
			str = "[";
			str_my = "63";
		}
		else if (!strcmp(str,"\\Bigg]" || !strcmp(str,"\\Big]" || !strcmp(str,"]" || !strcmp(str,"\\big]" || !strcmp(str,"\\bigg]")
		{
			str = "]";
			str_my = "65";
		}
		else if (!strcmp(str,":")
		{
			str = "-7";
			str_my = "30";
		}
		else if (!strcmp(str,"\\tilde")
		{
			str = "tilde";
			str_my = 98;
		}
		else if (!strcmp(str,"\\backslash")
		{
			str = "backslash";
			str_my = 109;
		}
		else if (!strcmp(str,"?")
		{
			str = "-10";
			str_my = 35;
		}
		else if (!strcmp(str,"\\rightarrow")
		{
			str = "rarrow";
			str_my = 314;
		}
		else if (!strcmp(str,"\\leftarrow")
		{
			str = "larrow";
			str_my = 312;
		}

		char file_[255] = "temp";
		bool keep_on = false;
		for (i = 0; i < 110; i++)
		{
			string str_1(file_render[i]);
			if (str == str_1)
			{
				keep_on = true;
				break;
			}
		}

		if (keep_on)
		{
			sprintf(file_, "%s\\%s.png", file_, str.c_str());
#ifdef PRINT_INF
			printf("%s\n", file_);
#endif
			//IplImage* temp = cvLoadImage(file_);
			//IplImage* temp_re = cvCreateImage(cvSize(Result[i].rect.width * SCALES, Result[i].rect.height * SCALES), 8, 3);
			//cvResize(temp, temp_re, 3);


			//Polyline polyline_a(Stroke(3, Color::Silver));
			//polyline_a << Point_L(10, 20) << Point_L(10, 50);
			//doc << polyline_a;



			CvRect rect;
			rect.x = (Result[i].rect.x + move_width) * SCALES < 0 ? 0 : (Result[i].rect.x + move_width) * SCALES;
			rect.y = (Result[i].rect.y + move_height) * SCALES < 0 ? 0 : (Result[i].rect.y + move_height) * SCALES;
			rect.width = Result[i].rect.width * SCALES;
			rect.height = Result[i].rect.height * SCALES;


			DataInfo Data_temp;
			Data_temp.str = str_my;
			Data_temp.x = rect.x;
			Data_temp.y = rect.y;
			Data_temp.width = rect.width;
			Data_temp.height = rect.height;


			Data_MY.push_back(Data_temp);

			//cvSetImageROI(src_new_gray, rect);
			//cvCopy(temp_re, src_new_gray);
			//cvResetImageROI(src_new_gray);
			//cvReleaseImage(&temp);
			//cvReleaseImage(&temp_re);
		}

		//cvRectangle(src_new_gray, cvPoint(Result[i].rect.x*10, Result[i].rect.y*10), cvPoint((Result[i].rect.x+Result[i].rect.width)*10, (Result[i].rect.y + Result[i].rect.height)*10), CV_RGB(255, 0, 255), 1, 8, 0);
	}
	//doc.save();
	Render(src_new_gray_copy, Data_MY);
	//cvShowImage("srcnewgray_copy", src_new_gray_copy);
	//cvShowImage("srcnewgray1", src_new_gray);

	for (i = 0; i < Result_new.size(); i++)
	{
		int count = 0;
		//cvRectangle(src_new_gray, cvPoint(Result_new[i].x * 10, Result_new[i].y * 10), cvPoint((Result_new[i].x + Result_new[i].width), Result_new[i].y * 10 + 10), CV_RGB(255, 0, 0), 3, 8, 0);
		for (int m = Result_new[i].y * SCALES; m < Result_new[i].y * SCALES + SCALES * 0.5; m++)
		{
			for (int n = Result_new[i].x * SCALES; n < (Result_new[i].x + Result_new[i].width) * SCALES; n++)
			{
				int value = ((uchar*)(src_new_gray->imageData + m * src_new_gray->widthStep))[n * 3 + 0];
				if (value < 255)
				{
					count++;
				}
			}
		}
		if (count == 0)
		{
			cvLine(src_new_gray, cvPoint(Result_new[i].x * SCALES + Step_width_left*SCALES, Result_new[i].y * SCALES), cvPoint((Result_new[i].x + Result_new[i].width) * SCALES, Result_new[i].y * SCALES), CV_RGB(0, 0, 0), max(2, SCALES / 2), CV_AA, 0);

			int count_black = 0;
			for (int m = Result_new[i].x * SCALES + Step_width_left * SCALES; m < (Result_new[i].x + Result_new[i].width + Step_width_left) * SCALES; m++)
			{
				for (int n = Result_new[i].y * SCALES; n < (Result_new[i].y + Result_new[i].height) * SCALES; n++)
				{
					if (n >(src_new_gray_copy->height - 1) || m > src_new_gray_copy->width - 1)
					{
						continue;
					}
					else
					{
						//cvSetReal2D(src_new_gray_copy, n, m, 0);
						int value = ((uchar*)(src_new_gray_copy->imageData + n * src_new_gray_copy->widthStep))[m];
						if (value < 200)
						{
							count_black++;
						}
					}
				}
			}
			if (count_black == 0)
			{
				for (int m = Result_new[i].x * SCALES + Step_width_left * SCALES; m < (Result_new[i].x + Result_new[i].width + Step_width_left) * SCALES; m++)
				{
					for (int n = Result_new[i].y * SCALES; n < (Result_new[i].y + Result_new[i].height) * SCALES; n++)
					{
						if (n >(src_new_gray_copy->height - 1) || m > src_new_gray_copy->width - 1)
						{
							continue;
						}
						else
						{
							cvSetReal2D(src_new_gray_copy, n, m, 0);
						}
					}
				}
			}
		}
	}


	cvSetImageROI(src_new_show, cvRect(100, 100, src_new_gray->width, src_new_gray->height));
	rect_render.x = 100;
	rect_render.y = 100;
	rect_render.width = src_new_gray->width;
	rect_render.height = src_new_gray->height;

	cvCopy(src_new_gray, src_new_show);
	cvResetImageROI(src_new_show);


	//=======================背景显示====================
#if 0
	for (i = 0; i < src_new_show->height; i += 5)
	{
		for (j = 0; j < src_new_show->width; j += 5)
		{
			if (cvGet2D(src_new_show, i, j).val[0] > 20)
			{
				cvSet2D(src_new_show, i, j, CV_RGB(128, 128, 128));
			}
		}
	}

	for (i = 0; i < src_new_show->height; i += 20)
	{
		for (j = 0; j < src_new_show->width; j++)
		{
			if (cvGet2D(src_new_show, i, j).val[0] > 128)
			{
				cvSet2D(src_new_show, i, j, CV_RGB(210, 230, 226));
			}
		}
	}

	for (i = 0; i < src_new_show->width; i += 20)
	{
		for (j = 0; j < src_new_show->height; j++)
		{
			if (cvGet2D(src_new_show, j, i).val[0] > 128)
			{
				cvSet2D(src_new_show, j, i, CV_RGB(210, 230, 226));
			}
		}
	}
#endif
	//===============================================

	//cvNamedWindow("2", 0);
	//cvShowImage("2", src_new_show);
	//调整src_new_gray_copy图像的高
	//int top_y = 0;
	//int bottom_y = 0;
	//for(i = 0; i < src_new_gray_copy->height; i++)
	//{
	//	for(j = 0; j < src_new_gray_copy->width; j++)
	//	{
	//		if(cvGetReal2D(src_new_gray_copy, i, j) < 255)
	//		{
	//			top_y = i;
	//			i = src_new_gray_copy->height;
	//			j = src_new_gray_copy->width;
	//		}
	//	}
	//}
	//for(i = src_new_gray_copy->height - 1; i > -1; i--)
	//{
	//	for(j = 0; j < src_new_gray_copy->width; j++)
	//	{
	//		if(cvGetReal2D(src_new_gray_copy, i, j) < 255)
	//		{
	//			bottom_y = i;
	//			i = -1;
	//			j = src_new_gray_copy->width;
	//		}
	//	}
	//}
	//if(bottom_y > top_y)
	//{
	//	IplImage* src_new_gray_copy_cut = cvCreateImage(cvSize(src_new_gray_copy->width, bottom_y - top_y + 1), 8, 1);
	//	cvSetImageROI(src_new_gray_copy, cvRect(0, top_y, src_new_gray_copy->width, src_new_gray_copy_cut->height));
	//	cvCopy(src_new_gray_copy, src_new_gray_copy_cut);
	//	cvResetImageROI(src_new_gray_copy);
	//	cvSaveImage("00.png", src_new_gray_copy_cut);
	//	cvReleaseImage(&src_new_gray_copy_cut);
	//}
	//else
	//{
	//	cvSaveImage("00.png", src_new_gray_copy);
	//}
	cvSaveImage("00.png", src_new_gray_copy);
	cvShowImage("3", src_new_gray_copy);
	cvSaveImage("0.png", src_new_show);

	//cvShowImage("srcnewgray", src_new_gray);


	cvShowImage("-1", src_new_gray);
	//cvWaitKey(0);

#endif

	//释放空间
	cvReleaseImage(&src_new_);
	cvReleaseImage(&src_new__);
	cvReleaseImage(&src_new_gray);
	cvReleaseImage(&src_new_show);
	//cvReleaseImage(&src_new_gray_copy);
	//cvReleaseMemStorage(&storage);
	return src_new_gray_copy;
}

void Draw_Render_Move(IplImage* dst)
{
	srand((unsigned)time(NULL));

	IplImage* src = cvCreateImage(cvSize(dst->width, dst->height), 8, 1);
	IplImage* show = cvCreateImage(cvSize(dst->width, dst->height), 8, 3);

	for (i = 0; i < show->height; i++)
	{
		for (j = 0; j < show->width; j++)
		{
			((uchar*)(show->imageData + i * show->widthStep))[3 * j + 0] = 255;
			((uchar*)(show->imageData + i * show->widthStep))[3 * j + 1] = 255;
			((uchar*)(show->imageData + i * show->widthStep))[3 * j + 2] = 255;
		}
	}


	cvCvtColor(dst, src, CV_RGB2GRAY);
	//cvShowImage("2", src);

	for (i = 0; i < src->height; i++)
	{
		for (j = 0; j < src->width; j++)
		{
			int value = ((uchar*)(src->imageData + i * src->widthStep))[j];
			if (value > 244)
			{
				((uchar*)(src->imageData + i * src->widthStep))[j] = 0;
				//cvSetReal2D(src, i, j, 0);
				//cvSet2D(dst, i, j, CV_RGB(255, 255, 255));
			}
			else
			{
				((uchar*)(src->imageData + i * src->widthStep))[j] = 255;
				//cvSetReal2D(src, i, j, 255);
				//cvSet2D(dst, i, j, CV_RGB(0, 0, 0));
			}
		}
	}
	//cvShowImage("3", src);

	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contour = 0;
	vector<CvRect> Result_new;
	int contour_num = cvFindContours(src, storage, &contour, sizeof(CvContour), CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	for (; contour != 0; contour = contour->h_next)
	{
		CvRect aRect = cvBoundingRect(contour, 0);

		if (aRect.x > 20)
		{
			Result_new.push_back(aRect);
		}
	}


	vector<Move_Info> Info;

	for (i = 0; i < Result_new.size(); i++)
	{
		int x = Result_new[i].x + (rand() % 8 - 4) * Step;
		int y = Result_new[i].y + (rand() % 8 - 4) * Step;

		if (x > dst->width || x < 0)
		{
			x = Result_new[i].x;
		}
		if (y > dst->height || y < 0)
		{
			y = Result_new[i].y;
		}
		//printf("x = %d, y = %d\n", x, y);
		int dx = (Result_new[i].x - x) / Step;
		int dy = (Result_new[i].y - y) / Step;

		Move_Info temp;

		temp.x = x;
		temp.y = y;
		temp.dx = dx;
		temp.dy = dy;
		Info.push_back(temp);
	}

#if 1
	for (i = 0; i < Step; i++)
	{
		//printf("处理%d\n", i);
		for (int m = 0; m < show->height; m++)
		{
			for (int n = 0; n < show->width; n++)
			{
				((uchar*)(show->imageData + m * show->widthStep))[n * 3 + 0] = 255;
				((uchar*)(show->imageData + m * show->widthStep))[n * 3 + 1] = 255;
				((uchar*)(show->imageData + m * show->widthStep))[n * 3 + 2] = 255;
				//cvSet2D(show, m, n, CV_RGB(255, 255, 255));
			}
		}

		if (i < Step - 1)
		{
			for (j = 0; j < Result_new.size(); j++)
			{
				cvSetImageROI(dst, Result_new[j]);


				IplImage* TT = cvCreateImage(cvSize(Result_new[j].width, Result_new[j].height), 8, 3);
				cvCopy(dst, TT);

				CvRect rect;
				rect.x = Info[j].x + i*Info[j].dx;;
				rect.y = Info[j].y + i*Info[j].dy;
				rect.width = Result_new[j].width;
				rect.height = Result_new[j].height;

				cvSetImageROI(show, rect);
				cvCopy(TT, show);


				cvResetImageROI(dst);
				cvResetImageROI(show);

				cvReleaseImage(&TT);
			}
		}
		else
		{
			for (j = 0; j < Result_new.size(); j++)
			{
				cvSetImageROI(dst, Result_new[j]);


				IplImage* TT = cvCreateImage(cvSize(Result_new[j].width, Result_new[j].height), 8, 3);
				cvCopy(dst, TT);

				CvRect rect;
				rect.x = Result_new[j].x;
				rect.y = Result_new[j].y;
				rect.width = Result_new[j].width;
				rect.height = Result_new[j].height;

				cvSetImageROI(show, rect);
				cvCopy(TT, show);

				cvResetImageROI(dst);
				cvResetImageROI(show);

				cvReleaseImage(&TT);
			}
		}

		cvShowImage("4 ", show);
		cvWaitKey(1);
	}
#endif

	cvReleaseMemStorage(&storage);
	cvReleaseImage(&src);
	cvReleaseImage(&show);

	//cvWaitKey(0);
}

void Draw_Render_Move_1(IplImage* dst)
{
	IplImage* src = cvCreateImage(cvSize(dst->width, dst->height), 8, 3);
	for (i = 0; i < src->height; i++)
	{
		for (j = 0; j < src->width; j++)
		{
			cvSet2D(src, i, j, CV_RGB(255, 255, 255));
		}
	}

	cvSetImageROI(dst, rect_render);

	int dis = src->height - (rect_render.y + rect_render.height);

	for (i = src->height - rect_render.height; i > rect_render.y - 1; i -= 2)
	{
		cvSetImageROI(src, cvRect(rect_render.x, i, rect_render.width, rect_render.height));
		cvCopy(dst, src);
		cvResetImageROI(src);
		cvShowImage("4", src);
		cvWaitKey(1);
	}
	cvResetImageROI(dst);
	cvReleaseImage(&src);
}

void Draw_Render_Move_2(IplImage* dst)
{
	IplImage* src = cvCreateImage(cvSize(dst->width, dst->height), 8, 3);


	cvSetImageROI(dst, rect_render);

	int dis = src->height - (rect_render.y + rect_render.height);

	int count = 0;
	int height = 0;
	index = 0;
	for (i = height; i < rect_render.y + 1; i += 2)
	{
		for (int o = 0; o < src->height; o++)
		{
			for (int p = 0; p < src->width; p++)
			{
				cvSet2D(src, o, p, CV_RGB(255, 255, 255));
			}
		}
		cvSetImageROI(src, cvRect(Index, i, rect_render.width, rect_render.height));
		//cvSetImageROI(src, cvRect(rect_render.x, i, rect_render.width, rect_render.height));
		cvCopy(dst, src);
		cvResetImageROI(src);
		cvShowImage("4", src);
		cvWaitKey(1);
		if (i > rect_render.y - 1)
		{
			count++;
			height = 0.25 * count * rect_render.y;
			for (j = rect_render.y; j > height; j -= 2)
			{
				for (int o = 0; o < src->height; o++)
				{
					for (int p = 0; p < src->width; p++)
					{
						cvSet2D(src, o, p, CV_RGB(255, 255, 255));
					}
				}
				cvSetImageROI(src, cvRect(Index, j, rect_render.width, rect_render.height));
				//cvSetImageROI(src, cvRect(rect_render.x, j, rect_render.width, rect_render.height));
				cvCopy(dst, src);
				cvResetImageROI(src);
				cvShowImage("4", src);
				cvWaitKey(1);
				Index++;
			}
			i = height;
		}
		Index++;
	}

	cvResetImageROI(dst);
	cvReleaseImage(&src);
}

void Draw_Render_Move_3(IplImage* dst)
{
	IplImage* src = cvCreateImage(cvSize(dst->width, dst->height), 8, 3);
	for (i = 0; i < dst->height; i++)
	{
		for (j = 0; j < dst->width; j++)
		{
			if (i % 4 == 0 && j % 4 == 0)
			{
				CvScalar value;
				value = cvGet2D(dst, i, j);
				value.val[0] = value.val[0] - 128;
				value.val[1] = value.val[1] - 128;
				value.val[2] = value.val[2] - 128;
				cvSet2D(src, i, j, value);
			}
		}
	}

	for (i = 0; i < dst->height * 0.5 + 2; i++)
	{
		for (j = 0; j < dst->width; j++)
		{
			cvSet2D(src, i, j, cvGet2D(dst, i, j));
			cvSet2D(src, src->height - 1 - i, j, cvGet2D(dst, src->height - 1 - i, j));
		}
		cvShowImage("4", src);
		cvWaitKey(1);
	}
	cvReleaseImage(&src);
}

void Draw_Render_Move_4(IplImage* dst)
{
	IplImage* src = cvCreateImage(cvSize(dst->width, dst->height), 8, 3);
	for (i = 0; i < src->height; i++)
	{
		for (j = 0; j < src->width; j++)
		{
			cvSet2D(src, i, j, CV_RGB(255, 255, 255));
		}
	}

	for (i = rect_render.y; i < rect_render.y + rect_render.height; i++)
	{
		for (j = rect_render.x; j < rect_render.x + rect_render.width; j++)
		{
			if (i % 3 == 1 && j % 3 == 1)
			{
				cvSet2D(src, i, j, cvGet2D(dst, i, j));
			}
		}
	}
	cvShowImage("4", src);
	cvWaitKey(120);

	for (i = rect_render.y; i < rect_render.y + rect_render.height; i++)
	{
		for (j = rect_render.x; j < rect_render.x + rect_render.width; j++)
		{
			if (i % 3 == 0 && j % 3 == 2)
			{
				cvSet2D(src, i, j, cvGet2D(dst, i, j));
			}
		}
	}
	cvShowImage("4", src);
	cvWaitKey(120);


	for (i = rect_render.y; i < rect_render.y + rect_render.height; i++)
	{
		for (j = rect_render.x; j < rect_render.x + rect_render.width; j++)
		{
			if (i % 3 == 0 && j % 3 == 0)
			{
				cvSet2D(src, i, j, cvGet2D(dst, i, j));
			}
		}
	}
	cvShowImage("4", src);
	cvWaitKey(120);


	for (i = rect_render.y; i < rect_render.y + rect_render.height; i++)
	{
		for (j = rect_render.x; j < rect_render.x + rect_render.width; j++)
		{
			if (i % 3 == 2 && j % 3 == 2)
			{
				cvSet2D(src, i, j, cvGet2D(dst, i, j));
			}
		}
	}
	cvShowImage("4", src);
	cvWaitKey(120);

	for (i = rect_render.y; i < rect_render.y + rect_render.height; i++)
	{
		for (j = rect_render.x; j < rect_render.x + rect_render.width; j++)
		{
			if (i % 3 == 1 && j % 3 == 0)
			{
				cvSet2D(src, i, j, cvGet2D(dst, i, j));
			}
		}
	}
	cvShowImage("4", src);
	cvWaitKey(120);

	for (i = rect_render.y; i < rect_render.y + rect_render.height; i++)
	{
		for (j = rect_render.x; j < rect_render.x + rect_render.width; j++)
		{
			if (i % 3 == 2 && j % 3 == 1)
			{
				cvSet2D(src, i, j, cvGet2D(dst, i, j));
			}
		}
	}
	cvShowImage("4", src);
	cvWaitKey(120);

	for (i = rect_render.y; i < rect_render.y + rect_render.height; i++)
	{
		for (j = rect_render.x; j < rect_render.x + rect_render.width; j++)
		{
			if (i % 3 == 0 && j % 3 == 1)
			{
				cvSet2D(src, i, j, cvGet2D(dst, i, j));
			}
		}
	}
	cvShowImage("4", src);
	cvWaitKey(120);

	for (i = rect_render.y; i < rect_render.y + rect_render.height; i++)
	{
		for (j = rect_render.x; j < rect_render.x + rect_render.width; j++)
		{
			if (i % 3 == 1 && j % 3 == 2)
			{
				cvSet2D(src, i, j, cvGet2D(dst, i, j));
			}
		}
	}
	cvShowImage("4", src);
	cvWaitKey(120);

	for (i = rect_render.y; i < rect_render.y + rect_render.height; i++)
	{
		for (j = rect_render.x; j < rect_render.x + rect_render.width; j++)
		{
			if (i % 3 == 2 && j % 3 == 0)
			{
				cvSet2D(src, i, j, cvGet2D(dst, i, j));
			}
		}
	}
	cvShowImage("4", src);
	cvWaitKey(120);

	cvReleaseImage(&src);
}

void Draw_Render_Move_5(IplImage* dst)
{
	srand((unsigned)time(NULL));

	IplImage* src = cvCreateImage(cvSize(dst->width, dst->height), 8, 3);

	cvSetImageROI(dst, rect_render);

	for (int k = 0; k < 30; k++)
	{
		int dx = rand() % 60 - 30;
		int dy = rand() % 40 - 20;

		CvRect rect;
		rect.x = rect_render.x + dx;
		rect.y = rect_render.y + dy;
		rect.width = rect_render.width;
		rect.height = rect_render.height;

		for (i = 0; i < src->height; i++)
		{
			for (j = 0; j < src->width; j++)
			{
				cvSet2D(src, i, j, CV_RGB(255, 255, 255));
			}
		}

		cvLine(src, cvPoint(rect.x + 0.5 * rect.width, 0), cvPoint(rect.x + 0.5 * rect.width, rect.y), CV_RGB(128, 128, 128), 2, CV_AA, 0);
		cvLine(src, cvPoint(rect.x + 0.5 * rect.width, rect.y + rect.height), cvPoint(rect.x + 0.5 * rect.width, src->height - 1), CV_RGB(128, 128, 128), 2, CV_AA, 0);
		cvLine(src, cvPoint(0, rect.y + 0.5 * rect.height), cvPoint(rect.x, rect.y + 0.5 * rect.height), CV_RGB(128, 128, 128), 2, CV_AA, 0);
		cvLine(src, cvPoint(rect.x + rect.width, rect.y + 0.5 * rect.height), cvPoint(src->width, rect.y + 0.5 * rect.height), CV_RGB(128, 128, 128), 2, CV_AA, 0);
		cvRectangle(src, cvPoint(rect.x - 1, rect.y - 1), cvPoint(rect.x + rect.width + 2, rect.y + rect.height + 2), CV_RGB(128, 128, 128), 1, CV_AA, 0);

		cvSetImageROI(src, rect);
		cvCopy(dst, src);
		cvResetImageROI(src);

		for (i = rect.y; i < rect.y + rect.height + 2; i++)
		{
			for (j = rect.x; j < rect.x + rect.width + 2; j++)
			{
				if (((uchar*)(src->imageData + i * src->widthStep))[j * 3] > 100)
				{
					cvSet2D(src, i, j, CV_RGB(120, 120, 120));
				}
				if (i == rect.y)
				{
					cvSet2D(src, i, j, CV_RGB(100, 0, 0));
				}
				if (i == rect.y + rect.height + 1)
				{
					cvSet2D(src, i, j, CV_RGB(100, 0, 0));
				}
				if (j == rect.x)
				{
					cvSet2D(src, i, j, CV_RGB(100, 0, 0));
				}
				if (j == rect.x + rect.width + 1)
				{
					cvSet2D(src, i, j, CV_RGB(100, 0, 0));
				}
			}
		}

		cvShowImage("4", src);
		cvWaitKey(1);
	}
	//cvCopy(dst, src);
	cvShowImage("4", src);
	cvWaitKey(1);

	cvResetImageROI(dst);
	cvReleaseImage(&src);

}

void Draw_Render_Move_6(IplImage* dst)
{
	IplImage* src = cvCreateImage(cvSize(dst->height, dst->width), 8, 3);

}

void Draw_Render_SVG(IplImage* src, vector<Draw_Information> Result, int max_height, int max_width)
{

}
#endif

#include "Render.h"
#include "mimetex.h"

#define MAX_SYMBOLS 400

char* Key_W0 = "\\frac";
char* Key_W1 = "\\sqrt";
char* Key_W2 = "left";
char* Key_W3 = "right";
char* Key_W4 = "-1";
char* Key_W5 = "part";

int *process_new(struct Data_Info* DataROI, int left, int right, int *nn_construct, int *nn_Boundary)
{

    int Boundary[MAX_SYMBOLS];
    int n_Boundary=0;

	int construct[MAX_SYMBOLS][2];
	int n_construct=0;

	int i,j;

	for ( i = 0; i < right; i++)
	{
		construct[i][0]=-1;
		construct[i][1]=-1;
	}
	n_construct=right;

	*nn_construct=n_construct;

	for ( i = left; i < right - 1; i++)
	{
		if (DataROI[i].left > -1 && DataROI[i + 1].left > -1)
		{
			char *str_0 = DataROI[i - 1].substring;
			char * str_1 = DataROI[i].substring;
			char * str_2 = DataROI[i + 1].substring;

            char str_1_substring[1024];
            char str_2_substring[1024];

            for(j=0;j<4;j++)
            {
                str_1_substring[j] = str_1[j];
                str_2_substring[j] = str_2[j];
            }
            str_1_substring[j]='\0';
            str_2_substring[j]='\0';



			index_left = -1;
			index_right = -1;
			for ( j = i - 1; j > left - 1; j--)
			{
				char * str_3 = DataROI[j].substring;
				if (DataROI[i].width == DataROI[j].Box_width && DataROI[i].height == DataROI[j].Box_height)
				{
					if (DataROI[j].Box_width == DataROI[j].width && DataROI[j].Box_height == DataROI[j].height)
					{
						continue;
					}
					else
					{
						Index_left = j;
						j = left - 1;
					}
				}
				/*2016.1.21修改
				超过根号10c次方以上次幂会渲染出错问题
				*/
				else if(j > 0 && ((DataROI[i].width == ((DataROI[j].width + DataROI[j - 1].width) - 2) ||
					DataROI[i].width == ((DataROI[j].width + DataROI[j - 1].width) - 3)) &&
					DataROI[i].height == (DataROI[j].height - 3) && !strcmp(str_3, str_1_substring) )
				{
					Index_left = j;
					j = left - 1;
				}
			}
			for ( j = i - 1; j > left - 1; j--)
			{
				char *str_3 = DataROI[j].substring;
				if (DataROI[i + 1].width == DataROI[j].Box_width && DataROI[i + 1].height == DataROI[j].Box_height)
				{
					if (DataROI[j].Box_width == DataROI[j].width && DataROI[j].Box_height == DataROI[j].height)
					{
						//continue;
						break;
					}
					else
					{
						Index_right = j;
						j = left - 1;
					}
				}
				else if (DataROI[i + 1].width == DataROI[j].Box_width && (abs(DataROI[j].Box_height - DataROI[i + 1].height) < 5) && !strcmp(str_2 , str_3))
				{
					if (DataROI[j].Box_width == DataROI[j].width && DataROI[j].Box_height == DataROI[j].height)
					{
						//continue;
						break;
					}
					else if (DataROI[i + 1].width == (DataROI[i].width - 1) && DataROI[i + 1].height == (DataROI[i].height - 1) && DataROI[i + 1].Box_height == (DataROI[i].Box_height - 1) && DataROI[i + 1].Box_width == (DataROI[i].Box_width - 1))
					{
						break;
					}
					else
					{
						Index_right = j;
						j = left - 1;
					}
				}
				//2016.1.18修改
				//(DataROI[i+1].height == (DataROI[j].Box_height - 2) && DataROI[i+1].width == DataROI[j].Box_width && str_2_substring == "\\fra") 针对除法次方情况： 比如 2^(5/8)
				//(DataROI[i+1].width == DataROI[j].Box_width && ( (DataROI[i].height*0.5 + DataROI[i+1].height) == DataROI[j].Box_height) 针对左上或者右上box大小变动
				//=====================================================================================================================================================================
				else if ( ( (DataROI[i + 1].width == DataROI[j].Box_width && ((DataROI[i].height*0.5 + DataROI[i + 1].height) == DataROI[j].Box_height)
					&& (DataROI[i].height - DataROI[i + 1].height) < 5) || (DataROI[i + 1].height == (DataROI[j].Box_height - 2)
					&& DataROI[i + 1].width == DataROI[j].Box_width && !strcmp(str_2_substring , "\\fra") ) ))
					//=====================================================================================================================================================================
				{
					if ((DataROI[j].Box_width == DataROI[j].width && DataROI[j].Box_height == DataROI[j].height) || !strcmp(str_3, "left") /*|| str_3 == "right"*/)
					{
						//continue;
						break;
					}
					else if (abs(DataROI[i + 1].height - DataROI[j].Box_height) > 7)
					{
						break;
					}
					else
					{
						Index_right = j;
						j = left - 1;
					}
				}
			}


			if (!strcmp(str_2 , Key_W2))
			{
				continue;
			}

			//2016.1.18修改
			//如果右边找到的块在前，都是{ [等符号，不可能是“+”号
			//=============================================================================================
			if (Index_right < Index_left && !strcmp(str_2_substring , "+"))
			{
				Index_right = -1;
				DataROI[i + 1].width = DataROI[i + 1].width - 1;   //防止后面将“+”当成重复的字符删掉
				//DataROI[i+1].height = DataROI[i+1].height - 1;
			}
			//防止同一个字符错误找到前面的box
			if (DataROI[i + 1].width == (DataROI[i].width - 1) && DataROI[i + 1].height == (DataROI[i].height - 1) && DataROI[i + 1].Box_height == (DataROI[i].Box_height - 1) && DataROI[i + 1].Box_width == (DataROI[i].Box_width - 1))
			{
				Index_right = Index_left;
			}
			//=============================================================================================


			//===============================================================================================
			/*以下根据Index_left和Index_right的情况判断合并属于哪一种情况?
			常见的情况有三种：
			1. 左边是大块，右边是一个小单元合并情况， Index_left > left && Index_right = -1
			2. 左边是大块，右边也是大块情况，Index_left > left && Index_right > left
			3. 大块的开始，没有合并的情况，Index_left = -1 && Index_right = -1
			*/
			//情况0： \\frac情况
			if (!strcmp(str_1 , Key_W2) && !strcmp(str_2 , Key_W3))
			{
				//找到分子，分母的分界线middle,已经分子的最左边边界
				int middle = -1;
				int min_Boundary = -1;
				for (j = i - 1; j > left; j--)
				{
					char * str_1_1 = DataROI[j].substring;
					if (!strcmp(str_1_1 , "-1"))
					{
						middle = j;
						DataROI[j].substring = "1";
					}
					if (!strcmp(str_1_1 , "\\frac") && DataROI[j].left == -1)
					{
						min_Boundary = j;
						DataROI[j].substring = "1";
						j = left;
					}
				}

				for (j = i + 1; j < 200; j++)
				{
					char * str_1_1 = DataROI[j].substring;
					if (!strcmp(str_1_1 , "\\frac"))
					{
						DataROI[j].substring = "1";
						j = 200;
					}
				}

#ifdef PRINT_INF
				printf("====================================================\n");
				for (j = left; j < right; j++)
				{
					printf("%s \n", DataROI[j].substring);
				}
				printf("=====================================================\n");
#endif
				//左边最大宽高
				int max_width_left = -1;
				int max_height_left = -1;
				for (j = middle; j > min_Boundary; j--)
				{
					if (DataROI[j].Box_width > max_width_left)
					{
						max_width_left = DataROI[j].Box_width;
					}
					if (DataROI[j].Box_height > max_height_left)
					{
						max_height_left = DataROI[j].Box_height;
					}
				}

				//右边最大宽高
				int max_width_right = -1;
				int max_height_right = -1;
				for (j = i - 1; j > middle; j--)
				{
					if (DataROI[j].Box_width > max_width_right)
					{
						max_width_right = DataROI[j].Box_width;
					}
					if (DataROI[j].Box_height > max_height_right)
					{
						max_height_right = DataROI[j].Box_height;
					}
				}

				construct[i][0] = min_Boundary;
				construct[i][1] = i;
				construct[i + 1][0] = min_Boundary;
				construct[i + 1][1] = i + 1;

#ifdef PRINT_INF
				for (j = 0; j < i + 2; j++)
				{
					printf("construct%d: %d  %d\n", j, construct[j].x, construct[j].y);
				}
				printf("=======================================================\n");
#endif

				//左块一致修改左上坐标点位置
				for (j = middle; j > min_Boundary; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i].left + DataROI[i].width - max_width_left;
						DataROI[j].top = DataROI[j].top + DataROI[i].top + DataROI[i].height - max_height_left;
					}
				}

				//右块一致修改左上坐标点位置
				for (j = i - 1; j > middle; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i + 1].left + DataROI[i + 1].width - max_width_right;
						DataROI[j].top = DataROI[j].top + DataROI[i + 1].top + DataROI[i + 1].height - max_height_right;
					}
				}
			}
			//array情况
			else if (str_1_substring == Key_W5 && str_2_substring == Key_W5)
			{
				//找到part及array关键字
				int left_left = -1;
				int left_right = -1;
				int right_right = -1;
				for (j = i - 1; j > left; j--)
				{
					char *str_1_1 = DataROI[j].substring;
					if (!strcmp(str_1_1 , str_1))
					{
						left_right = j;
					}
					if (!strcmp(str_1_1 , "\\array"))
					{
						left_left = j;
					}
					if (!strcmp(str_1_1 ,str_2))
					{
						right_right = j;
					}
				}


#ifdef PRINT_INF
				printf("====================================================\n");
				for (j = left; j < right; j++)
				{
					printf("%s \n", DataROI[j].substring);
				}
				printf("=====================================================\n");
#endif

				construct[i][0] = left_left;
				construct[i][1] = i;
				construct[i + 1][0] = left_left;
				construct[i + 1][1] = i + 1;

#ifdef PRINT_INF
				for (j = 0; j < i + 2; j++)
				{
					printf("construct%d: %d  %d\n", j, construct[j].x, construct[j].y);
				}
				printf("=======================================================\n");
#endif

				//左块一致修改左上坐标点位置
				for (j = left_right; j > left_left; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i].left;
						DataROI[j].top = DataROI[j].top + DataROI[i].top;
					}
				}

				//右块一致修改左上坐标点位置
				for (j = right_right; j > left_right; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i + 1].left;
						DataROI[j].top = DataROI[j].top + DataROI[i + 1].top;
					}
				}
			}
			//情况1
			else if (Index_left > left && Index_right == -1 && (i - Index_left) < 5)
			{
				//寻找最左边的边界
				//int min_dis = 10000;
				//int min_Boundary = 0;
				//for (j = 0; j < Boundary.size(); j++)
				//{
				//	int value = Index_left - Boundary[j];
				//	if (value > 0 && value < min_dis)
				//	{
				//		min_dis = value;
				//		min_Boundary = Boundary[j];
				//	}
				//}
				int min_Boundary = construct[Index_left].x;

				construct[i][0] = min_Boundary;
				construct[i][1] = i;
				construct[i + 1][0] = min_Boundary;
				construct[i + 1][1] = i + 1;

#ifdef PRINT_INF
				for (j = 0; j < i + 2; j++)
				{
					printf("construct%d: %d  %d\n", j, construct[j].x, construct[j].y);
				}
				printf("=======================================================\n");
#endif

				//左块一致修改左上坐标点位置
				for (j = i - 1; j > min_Boundary; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i].left;
						DataROI[j].top = DataROI[j].top + DataROI[i].top;
					}
				}
			}
			//情况2
			else if (Index_left > left && Index_right > left && Index_right > Index_left)
			{
				//寻找最左边的边界
				//int min_dis = 10000;
				//int min_Boundary = 0;
				//for (j = 0; j < Boundary.size(); j++)
				//{
				//	int value = Index_left - Boundary[j];
				//	if (value > 0 && value < min_dis)
				//	{
				//		min_dis = value;
				//		min_Boundary = Boundary[j];
				//	}
				//}
				int min_Boundary = construct[Index_left].x;
				construct[i][0] = min_Boundary;
				construct[i][1] = i;
				construct[i + 1][0] = min_Boundary;
				construct[i + 1][1] = i + 1;

#ifdef PRINT_INF
				for (j = 0; j < i + 2; j++)
				{
					printf("construct%d: %d  %d\n", j, construct[j].x, construct[j].y);
				}
				printf("=======================================================\n");
#endif

				//左块一致修改左上坐标点位置
				for (j = Index_left; j > min_Boundary; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i].left;
						DataROI[j].top = DataROI[j].top + DataROI[i].top;
					}
				}

				//右块一致修改左上坐标点位置
				for (j = Index_right; j > Index_left; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i + 1].left;
						DataROI[j].top = DataROI[j].top + DataROI[i + 1].top;
					}
				}
			}
			//情况3
			else if (Index_left > left && Index_right > left && Index_right < Index_left)
			{
				int min_Boundary = construct[Index_right].x;
				construct[i][0] = min(construct[Index_right].x, construct[Index_left].x);
				construct[i][1] = i;
				construct[i + 1][0] = min(construct[Index_right].x, construct[Index_left].x);
				construct[i + 1][1]= i + 1;

#ifdef PRINT_INF
				for (j = 0; j < i + 2; j++)
				{
					printf("construct%d: %d  %d\n", j, construct[j].x, construct[j].y);
				}
				printf("=======================================================\n");
#endif

				if (construct[Index_left].x > min_Boundary)
				{
					//左块一致修改左上坐标点位置
					for (j = Index_left; j > Index_right; j--)
					{
						if (DataROI[j].left > -1)
						{
							DataROI[j].left = DataROI[j].left + DataROI[i].left;
							DataROI[j].top = DataROI[j].top + DataROI[i].top;
						}
					}
				}
				else
				{
					//左块一致修改左上坐标点位置
					for (j = Index_left; j > construct[Index_left].x; j--)
					{
						if (j < min_Boundary || j > Index_right)
						{
							if (DataROI[j].left > -1)
							{
								DataROI[j].left = DataROI[j].left + DataROI[i].left;
								DataROI[j].top = DataROI[j].top + DataROI[i].top;
							}
						}
					}
				}

				//右块一致修改左上坐标点位置
				for (j = Index_right; j > min_Boundary; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i + 1].left;
						DataROI[j].top = DataROI[j].top + DataROI[i + 1].top;
					}
				}
			}
			else if (Index_left > left && Index_right > left && Index_right == Index_left)
			{
				for (j = Index_right - 2; j > left - 1; j--)
				{
					if (DataROI[i].width == DataROI[j].Box_width && DataROI[i].height == DataROI[j].Box_height)
					{
						Index_left = j;
						j = left - 1;
					}
				}

				int Boundary_left = construct[Index_left].x;
				int Boundary_right = construct[Index_right].x;
				construct[i][0] = Boundary_left;
				construct[i][1] = i;
				construct[i + 1][0] = Boundary_left;
				construct[i + 1][1] = i + 1;

#ifdef PRINT_INF
				for (j = 0; j < i + 2; j++)
				{
					printf("construct%d: %d  %d\n", j, construct[j].x, construct[j].y);
				}
				printf("=======================================================\n");
#endif

				//左块一致修改左上坐标点位置
				for (j = Index_left; j > Boundary_left; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i].left;
						DataROI[j].top = DataROI[j].top + DataROI[i].top;
					}
				}

				//右块一致修改左上坐标点位置
				for (j = Index_right; j > Boundary_right; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i + 1].left;
						DataROI[j].top = DataROI[j].top + DataROI[i + 1].top;
					}
				}
			}
			//情况4
			else if (Index_left == -1 && Index_right == -1 && str_0 != Key_W1)
			{
				Boundary[n_Boundary++]=(i - 1);

				construct[i][0] = i - 1;
				construct[i][1] = i;
				construct[i + 1][0] = i - 1;
				construct[i + 1][1] = i + 1;

#ifdef PRINT_INF
				for (j = 0; j < i + 2; j++)
				{
					printf("construct%d: %d  %d\n", j, construct[j].x, construct[j].y);
				}
				printf("=======================================================\n");
#endif

			}
			//情况4.1
			else if (Index_left == -1 && Index_right == -1 && str_0 == Key_W1 && str_2 == Key_W1)
			{
				Boundary[n_Boundary++]=(i - 1);

				construct[i][0] = i - 1;
				construct[i][1] = i;
				construct[i + 1][0] = i - 1;
				construct[i + 1][1] = i + 1;

#ifdef PRINT_INF
				for (j = 0; j < i + 2; j++)
				{
					printf("construct%d: %d  %d\n", j, construct[j].x, construct[j].y);
				}
				printf("=======================================================\n");
#endif

			}
			//情况4.2
			else if (Index_left == -1 && Index_right == -1 && str_0 == Key_W1 && str_2 != Key_W1 && str_1 != "Box")
			{
				Boundary[n_Boundary++]=(i - 1);

				construct[i][0] = i - 1;
				construct[i][1] = i;
				construct[i + 1][0] = i - 1;
				construct[i + 1][1] = i + 1;

#ifdef PRINT_INF
				for (j = 0; j < i + 2; j++)
				{
					printf("construct%d: %d  %d\n", j, construct[j].x, construct[j].y);
				}
				printf("=======================================================\n");
#endif

			}
			//情况5
			else if (Index_left == -1 && Index_right == -1 && str_0 == Key_W1 && str_1 == "Box")
			{
				int min_Boundary = 0;
				for (j = i - 2; j > left - 1; j--)
				{
					char * str_1_1 = DataROI[j].substring;
					if (!strcmp(str_1_1 , Key_W1))
					{
						min_Boundary = j;
						j = left - 1;
					}
				}

				construct[i][0] = min_Boundary;
				construct[i][1] = i;
				construct[i + 1][0] = min_Boundary;
				construct[i + 1][1] = i + 1;

#ifdef PRINT_INF
				for (j = 0; j < i + 2; j++)
				{
					printf("construct%d: %d  %d\n", j, construct[j].x, construct[j].y);
				}
				printf("=======================================================\n");
#endif

				//左边最大宽高
				int max_width_left = -1;
				int max_height_left = -1;
				for (j = i - 2; j > min_Boundary; j--)
				{
					if (DataROI[j].Box_width > max_width_left)
					{
						max_width_left = DataROI[j].Box_width;
					}
					if (DataROI[j].Box_height > max_height_left)
					{
						max_height_left = DataROI[j].Box_height;
					}
				}

				//左块一致修改左上坐标点位置
				for (j = i - 2; j > min_Boundary; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i].left + DataROI[i].width - max_width_left;
						DataROI[j].top = DataROI[j].top + DataROI[i].top + DataROI[i].height - max_height_left;
					}
				}
			}

#if 1
			//情况6：一般都是\\sqrt \\prac等造成的， 左边找到了边界，右边没有找到边界
			else if (Index_left > left && Index_right == -1 && (i - Index_left) > 5)
			{
				////寻找最左边的边界
				//int min_dis = 10000;
				//int min_Boundary = 0;
				//for (j = 0; j < Boundary.size(); j++)
				//{
				//	int value = Index_left - Boundary[j];
				//	if (value > 0 && value < min_dis)
				//	{
				//		min_dis = value;
				//		min_Boundary = Boundary[j];
				//	}
				//}

				int min_Boundary = construct[Index_left].x;
				construct[i][0] = min_Boundary;
				construct[i][1] = i;
				construct[i + 1][0] = min_Boundary;
				construct[i + 1][1] = i + 1;

#ifdef PRINT_INF
				for (j = 0; j < i + 2; j++)
				{
					printf("construct%d: %d  %d\n", j, construct[j].x, construct[j].y);
				}
				printf("=======================================================\n");
#endif

				//左块一致修改左上坐标点位置
				for (j = Index_left; j > min_Boundary; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i].left;
						DataROI[j].top = DataROI[j].top + DataROI[i].top;
					}
				}

				//右块一致修改左上坐标点位置
				int max_batch_width = 0;
				int max_batch_height = 0;

				for (j = i - 1; j > Index_left; j--)
				{
					if (DataROI[j].Box_width > max_batch_width)
					{
						max_batch_width = DataROI[j].Box_width;
					}
					if (DataROI[j].Box_height > max_batch_height)
					{
						max_batch_height = DataROI[j].Box_height;
					}
				}

				for (j = i - 1; j > Index_left; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i + 1].left + DataROI[i + 1].width - max_batch_width;
						DataROI[j].top = DataROI[j].top + DataROI[i + 1].top + DataROI[i + 1].height - max_batch_height;
					}
				}
			}
			//情况7：左边没有找到边界，右边找到边界
			else if (Index_left == -1 && Index_right > left && str_1 != Key_W2)
			{
				//寻找最左边的边界
				//int min_dis = 10000;
				//int min_Boundary = 0;
				//for (j = 0; j < Boundary.size(); j++)
				//{
				//	int value = Index_right - Boundary[j];
				//	if (value > 0 && value < min_dis)
				//	{
				//		min_dis = value;
				//		min_Boundary = Boundary[j];
				//	}
				//}

				int min_Boundary = construct[Index_right].x;
				construct[i][0] = min_Boundary;
				construct[i][1] = i;
				construct[i + 1][0] = min_Boundary;
				construct[i + 1][1] = i + 1;

#ifdef PRINT_INF
				for (j = 0; j < i + 2; j++)
				{
					printf("construct%d: %d  %d\n", j, construct[j].x, construct[j].y);
				}
				printf("=======================================================\n");
#endif

				//右块一致修改左上坐标点位置
				for (j = Index_right; j > min_Boundary; j--)
				{
					if (DataROI[j].left > -1)
					{
						DataROI[j].left = DataROI[j].left + DataROI[i + 1].left;
						DataROI[j].top = DataROI[j].top + DataROI[i + 1].top;
					}
				}

			}
#endif

		}

		//printf("******************************************************************\n\n");
		//for (j = 0; j < i+1; j++)
		//{
		//	printf("%s  ", DataROI[j].substring);
		//	if (DataROI[j].left > -1 && DataROI[j].left < 10000)
		//	{
		//		printf("%d  %d  %d  %d  %d  %d", DataROI[j].left, DataROI[j].top, DataROI[j].width, DataROI[j].height, DataROI[j].Box_width, DataROI[j].Box_height);
		//	}
		//	printf("\n");
		//}
		//printf("##########(%d)\n", i+1);
	}

	*nn_Boundary=n_Boundary;

	return Boundary;

}



char file_render[110][50] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
"a", "b", "c", "d", "e", "f", "g", "h", "i", "j",
"k", "l", "m", "n", "o", "p", "q", "r", "s", "t",
"u", "v", "w", "x", "y", "z", "+", "-", "(", ")",
"{", "}", "!", "-1", "-2", "-3", "-4", "-5", "-6",
"-7", "-8", "-9", "infty", "sum", "pi", "%", "=", "Big{", "Big}",
",", "lambda", "alpha", "theta", "beta", "delta", "ast", "div", "ne", "prod",
"int", "in", "[", "]", "to", "'", "A1", "B1", "C1", "D1",
"E1", "F1", "G1", "H1", "I1", "J1", "K1", "L1", "M1", "N1",
"O1", "P1", "Q1", "R1", "S1", "T1", "U1", "V1", "W1", "X1", "cup",
"Y1", "Z1", ":", "tilde", "backslash", "-10", "larrow", "rarrow" };

char exmaple_temp[30][15] = { "m", "n", "u", "w", "M", "N", "U", "W", "=", "\\Bigsum", "\\infty", "x", "\\theta", "\\beta", "\\to", "\\prime", "\\cup", "\\leftarrow", "\\rightarrow" };
char exmaple_temp_[70][10] = { "0", "2", "3", "4", "5", "6", "7", "8", "9", "a",
"b", "c", "d", "e", "g", "h", "k", "o", "p", "q",
"r", "s", "t", "v", "y", "z", "A", "B", "C", "D",
"E", "F", "G", "H", "K", "O", "P", "Q", "R", "S",
"T", "V", "X", "Y", "Z", "+", "\\leq", "\\geq", ">", "<",
"\\pi", "\\pm", "\\times", "%", ".", "\\lambda", "\\alpha", "\\cdot", "\\ast", "\\div",
"\\ne", "\\in", "\\lt", "\\gt" };

char exmaple_temp__[70][12] = { "1", "f", "g", "h", "i", "j", "l", "!", "I", "J",
"(", "\\big(", "\\bigg(", "\\Big(", "\\Bigg(",
")", "\\big)", "\\bigg)", "\\Big)", "\\Bigg)",
"{", "\\big{", "\\bigg{", "\\Big{", "\\Bigg{",
"}", "\\big}", "\\bigg}", "\\Big}", "\\Bigg}",
"[", "\\big[", "\\bigg[", "\\Big[", "\\Bigg[",
"]", "\\big]", "\\bigg]", "\\Big]", "\\Bigg]",
"\\int", "\\bigint", "\\biggint", "\\Bigint", "\\Biggint",
"\\prod", "\\bigprod", "\\biggprod", "\\Bigprod", "\\Biggprod",
"\\bigsum", "\\biggsum", "\\sum", "\\Bigsum", "\\Biggsum",
"L", ",", "|", "\\delta", "/", ":", "\\tilde", "\\backslash", "?" };

int Adjust_Data_new(Data_Info* DataROI_New, Data_Info* DataROI_New_New, int *Boundary, , int n_Boundary, int *max_width, int *max_height, int cnt)
{
    int i;
#ifdef PRINT_INF
	//printf("******************************************************************\n\n");
#endif
	for (i = 0; i < cnt; i++)
	{
#ifdef PRINT_INF
		printf("%s  ", DataROI_New[i].substring);
		if (DataROI_New[i].left > -1 && DataROI_New[i].left < 10000)
		{
			printf("%d  %d  %d  %d  %d  %d", DataROI_New[i].left, DataROI_New[i].top, DataROI_New[i].width, DataROI_New[i].height, DataROI_New[i].Box_width, DataROI_New[i].Box_height);
		}
		printf("\n");
#endif
		if (DataROI_New[i].Box_width > *max_width)
		{
			*max_width = DataROI_New[i].Box_width;
		}
		if (DataROI_New[i].Box_height > *max_height)
		{
			*max_height = DataROI_New[i].Box_height;
		}
	}

	int count = 0;
	for (i = 1; i < cnt - 1; i++)
	{
		if (DataROI_New[i].left > -1)
		{
			char * str = DataROI_New[i].substring;
			bool condition1 = false;
			bool condition2 = false;
			bool condition3 = false;
			bool condition4 = false;
			bool condition5 = false;
			for (j = 0; j < 30; j++)
			{
				if (!strcmp(str , exmaple_temp[j]))
				{
					condition1 = true;
				}
			}
			for (j = 0; j < 70; j++)
			{
				if (!strcmp(str , exmaple_temp_[j]))
				{
					condition2 = true;
				}
			}
			for (j = 0; j < 70; j++)
			{
				if (!strcmp(str , exmaple_temp[j]__))
				{
					condition3 = true;
				}
			}


			if (DataROI_New[i - 1].left  > -1)
			{
				if ((DataROI_New[i - 1].Box_height - DataROI_New[i].Box_height == 1) && (DataROI_New[i - 1].Box_width - DataROI_New[i].Box_width == 1))
				{
					continue;
				}
			}

			if (!strcmp(str , "right") || !strcmp(str , "left")  || !strcmp(str , "Box") )
			{
				continue;
			}

			if (!strcmp(str , "(")  || !strcmp(str , "\\big(") || !strcmp(str,"\\bigg(") || !strcmp(str,"\\Big(") || !strcmp(str,"\\Bigg(") ||
				!strcmp(str,")") || !strcmp(str,"\\big)") || !strcmp(str,"\\bigg)") || !strcmp(str,"\\Big)") || !strcmp(str,"\\Bigg)") ||
				!strcmp(str,"{") || !strcmp(str,"\\big{") || !strcmp(str,"\\bigg{") || !strcmp(str,"\\Big{") || !strcmp(str,"\\Bigg{") ||
				!strcmp(str,"}") || !strcmp(str,"\\big}") || !strcmp(str,"\\bigg}") || !strcmp(str,"\\Big}") || !strcmp(str,"\\Bigg}") ||
				!strcmp(str,"[") || !strcmp(str,"\\big[") || !strcmp(str,"\\bigg[") || !strcmp(str,"\\Big[") || !strcmp(str,"\\Bigg[") ||
				!strcmp(str,"]") || !strcmp(str,"\\big]") || !strcmp(str,"\\bigg]") || !strcmp(str,"\\Big]") || !strcmp(str,"\\Bigg]") ||
				!strcmp(str,"\\int") || !strcmp(str,"\\bigint") || !strcmp(str,"\\biggint") || !strcmp(str,"\\Bigint") || !strcmp(str,"\\Biggint") ||
				!strcmp(str,"\\prod") || !strcmp(str,"\\bigprod") || !strcmp(str,"\\biggprod") || !strcmp(str,"\\Bigprod") || !strcmp(str,"\\Biggprod") ||
				!strcmp(str,"\\bigsum") || !strcmp(str,"\\biggsum") || !strcmp(str,"\\sum") || !strcmp(str,"\\Bigsum") || !strcmp(str,"\\Biggsum") ||
				!strcmp(str,"/") || !strcmp(str,":") || !strcmp(str,"\\tilde") || !strcmp(str,"\\backslash") || !strcmp(str,"?")
				//if(!strcmp(str,"\\Bigsum" || !strcmp(str,"\\bigg{" || !strcmp(str,"\\Big(" || !strcmp(str,"\\Big)" || !strcmp(str,"\\Big{" || !strcmp(str,"\\Bigg{" || !strcmp(str,"\\Bigprod" || !strcmp(str,"\\Bigint"
				//	|| !strcmp(str,"[" || str =="]" || !strcmp(str,"/" || !strcmp(str,"\\big(" || !strcmp(str,"\\big)" || !strcmp(str,"\\big{" || !strcmp(str,"\\big}"  || !strcmp(str,"\\bigg}" || !strcmp(str,"\\Bigg[" || !strcmp(str,"\\Bigg]"
				//	|| !strcmp(str,"\\Big[" || !strcmp(str,"\\Big]" || !strcmp(str,"\\big[" || !strcmp(str,"\\big]" || !strcmp(str,"\\bigg[" || !strcmp(str,"\\bigg]" || !strcmp(str,":" || !strcmp(str,"{" || !strcmp(str,"}" || !strcmp(str,"Bigg}"
				//	|| !strcmp(str,"Big}")
			{
				if (max(DataROI_New[i].width, DataROI_New[i].height) > 80)
					continue;
			}
			else
			{
				if (max(DataROI_New[i].width, DataROI_New[i].height) > 30)
					continue;
			}

			for (j = 0; j < n_Boundary; j++)
			{
				if (Boundary[j] == (i - 2) && DataROI_New[i].left > -1)
				{
					condition4 = true;
				}
			}

			for (j = i - 1; j > -1; j--)
			{
				char * str1 = DataROI_New[j].substring;
				if (DataROI_New[i].width == DataROI_New[j].Box_width && DataROI_New[i].height == DataROI_New[j].Box_height)
				{
					if (DataROI_New[j].width != DataROI_New[j].Box_width || DataROI_New[j].height != DataROI_New[j].Box_height)
					{
						condition5 = true;
					}
					break;
				}
				if (j > 0)
				if ((DataROI_New[i].width == ((DataROI_New[j].width + DataROI_New[j - 1].width) - 2) || DataROI_New[i].width == ((DataROI_New[j].width + DataROI_New[j - 1].width) - 3)) && DataROI_New[i].height == (DataROI_New[j].Box_height - 3) && !strcmp(str1 , DataROI_New[i].substring))
				{
					condition5 = true;
				}
			}

			if (condition5)
			{
				continue;
			}


			if (condition1 && (DataROI_New[i].width - DataROI_New[i].height < 15))
			{

				memcpy(&(DataROI_New_New[count]), &(DataROI_New[i]),sizeof(struct Data_Info));
				count++;
			}
			else if (condition4)
			{
				memcpy(&(DataROI_New_New[count]), &(DataROI_New[i]),sizeof(struct Data_Info));
				count++;
			}
			else if (!strcmp(str,"-" && DataROI_New[i].height == 1)
			{
				memcpy(&(DataROI_New_New[count]), &(DataROI_New[i]),sizeof(struct Data_Info));
				count++;
			}
			else if (condition2 && (DataROI_New[i].width - DataROI_New[i].height < 8))
			{
				memcpy(&(DataROI_New_New[count]), &(DataROI_New[i]),sizeof(struct Data_Info));
				count++;
			}
			else if (condition3 && (DataROI_New[i].width < DataROI_New[i].height))
			{
				memcpy(&(DataROI_New_New[count]), &(DataROI_New[i]),sizeof(struct Data_Info));
				count++;
			}
		}
	}



	return count;
}


void Extract_Data(struct Data_Info* DataROI_New_New, struct Data_Info *Result, int *nn_Result, int count)
{

    int i;
    int n_Result=0;

    for (i = 0; i < count; i++)
	{
		if (i > 0 && DataROI_New_New[i].left > -1)
		{
			bool keep_on = false;
			char *str = DataROI_New_New[i].substring;
			for (j = i - 1; j > 0; j--)
			{
				char *str1 = DataROI_New_New[j].substring;
				if (DataROI_New_New[i].width == DataROI_New_New[j].Box_width && DataROI_New_New[i].height == DataROI_New_New[j].Box_height /*&& DataROI_New_New[j].width != DataROI_New_New[j].Box_width && DataROI_New_New[j].height != DataROI_New_New[j].Box_height*/)
				{
					keep_on = true;
					if (DataROI_New_New[i].width == DataROI_New_New[i].Box_width && DataROI_New_New[i].height == DataROI_New_New[i].Box_height)
					{
						keep_on = false;
					}
					if (DataROI_New_New[j].width == DataROI_New_New[j].Box_width && DataROI_New_New[j].height == DataROI_New_New[j].Box_height)
					{
						keep_on = false;
					}
					if ((str1 == str && DataROI_New_New[j].width != DataROI_New_New[i].width) || (str1 == str && (DataROI_New_New[j].height != DataROI_New_New[i].height)))
					{
						keep_on = true;
					}
					if (DataROI_New_New[i].left > DataROI_New_New[i - 1].left)
					{
						keep_on = false;
					}
					if (str1 == str && (DataROI_New_New[j].width != DataROI_New_New[j].Box_width || DataROI_New_New[j].height != DataROI_New_New[j].Box_height))
					{
						keep_on = false;
					}
					j = 0;
				}
				else if (DataROI_New_New[i].width == DataROI_New_New[j].Box_width && ((DataROI_New_New[j].Box_height - DataROI_New_New[i].height) == 4 || (DataROI_New_New[j].Box_height - DataROI_New_New[i].height) == 2 /*|| (DataROI_New_New[i].height - DataROI_New_New[j].Box_height) == 1*/) && !strcmp(str, str1))
				{
					keep_on = true;
				}
			}
			if (keep_on)
			{
				continue;
			}

			if (DataROI_New_New[i].width * DataROI_New_New[i].height > 1000 && DataROI_New_New[i].height < 50)
			{
				continue;
			}
		}
#ifdef PRINT_INF
		printf("%s  ", DataROI_New_New[i].substring);
		if (DataROI_New_New[i].left > -1 && DataROI_New_New[i].left < 10000)
		{
			printf("%d  %d  %d  %d  %d  %d", DataROI_New_New[i].left, DataROI_New_New[i].top, DataROI_New_New[i].width, DataROI_New_New[i].height, DataROI_New_New[i].Box_width, DataROI_New_New[i].Box_height);
		}
		printf("\n");
#endif



		memcpy(&(Result[n_Result++]), &(DataROI_New_New[i]),sizeof(struct Data_Info));
	}


	*nn_Result=n_Result;
}



