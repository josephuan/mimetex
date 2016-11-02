
#include "Render.h"


#ifdef ORIGINAL_TEST_CPP_IN_USE_CShape_DLL
//#include <afxwin.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include "Render.h"
//#include"mimetex\mimetex.h"

#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CLIENTBLOCK
#endif
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif


//#define USE

//#define COLOR_IMAGE
struct Data_Info* DataROI_New;
struct Data_Info* DataROI_New_New;
struct Result_Data* Result_Out;

struct Data_Info* create_memory(struct Data_Info* DaytaROI);
int GetSamplePath(string FilePath, vector<string>& Information);
string findchar(string L, string S);//查找子串

char equation[100][500] = {
							"y=\\frac {-b\\pm \\sqrt {b^{2}-4ac}} {2a}",
							"\\frac {\\left( x^{2}-4y^{2}\\right) } {\\sqrt {a+\\frac {x_{i}} {3}}}=y",   //有问题
							"\\frac {x^{2}} {\\frac {3} {y}}=a+b",
							"LaTex",
							"\\frac {\\sqrt {3} {x}} {\\sqrt {x}}x\\left( 2a+1\\right) ",
							"f(\\frac {c}{2})=\\frac {5}{2}",
							"\\frac{\\frac{2222222} {333333}} {444444}",
							"\\sqrt{1-cos^{2}b}",
							"y=\\frac {4-tan a -tan^{2} a }{2tan^{2} a + 5}",
							"y=\\begin{cases} a+b\\\\ c+2\\end{cases} ",
							"f=b_o+\\frac{a_1}{b_1+\\frac{a_2}{b_2+\\frac{a_3}{b_3+a_4}}}", //10
							"e^x=\\sum_{n=0}^\\infty\\frac{x^n}{n!}",
							"f(x)={\\frac1{\\sqrt{2\\pi}}}",
							"{x|0<x\\leq{1}}",
							"0<m>\\frac {1}{2}\\leq{2}\\geq{3}",
							"\\frac {7}{6}-\\frac{6n+7}{2^{2}3^{n+1}}",
							"x=\\frac {2n+1}{2n-1}>1",
							"cos(a+\\frac {\\pi}{6})=-\\frac {4}{5}",
							"log_{a}\\frac {t+1}{2}\\geq{}log_{a}\\sqrt{t}",
							"\\frac {\\frac {1}{2}(1-\\frac {1}{2^{n-2}})}{1-\\frac {1}{2}}",
							"p(a)=c_{4}^{1}(\\frac {1}{3})(\\frac {2}{3})^{2}(\\frac {2}{3})+(\\frac {2}{3})^{4}", //20
							"\\frac {32}{50} + 100%=64%",
							"0123456789",
							"abcdefghijklmn",
							"opqrstuvwyz",
							"!-+=%{}()<>",
							"\\frac {cos{\\frac {a}{2}}} {3+1}",
							"\\frac{\\sqrt[3]{17} - x^2}{\\sqrt{x+y}}",
							"\\sqrt[3]{17+x^2}",
							"y=\\begin{cases} a+b=\\sqrt{a+b^2} \\\\ 25a+5b+c=0.1100 \\\\ a+10b+c=0.3 \\end{cases}",
							"\\frac {1}{2\\sqrt{\\frac {2}{|d|}+|d|}}=\\frac {\\sqrt{2}}{4}",                       //30
							"\\frac {\\sqrt{48}-\\sqrt{3}}{\\sqrt{3}}-\\sqrt{\\frac {1}{7}}\\pm\\sqrt{14}",
							"y=log_{\\frac{1}{2}}^{2}",
							"\\frac {11\\lambda\\-3n^{2}}{(n+1)(n+2)}\\leq 11(T_{n}-\\frac {3}{2})",
							"e^x=\\prod_{n=0}^\\infty\\frac{x^n}{n!}",
							"\\int_{0}^{\\infty} (-x+x^2)",
							"|-3|+(-1)^{2011}\\times (\\pi -3)^{2}-\\sqrt[3]{27}+(\\frac {1}{2})^{-2}",
							"e^x=\\lim_{n\\to\\infty} \\left(1+\\frac xn\\right)^n",
							"f^\\prime(x)\\ = \\lim_{\\ x\\to 0}\\frac{f(x+x)-f(x)}{x}",
							"f(x)=cos{(2x-\\frac {\\pi}{3})}+2sin^{2}(x+\\frac {\\pi}{2})",
							"ABCDEFGHIJKLMNOPQRSTUVWXYZ",                                                           //40
							"\\begin{equation}\\begin{cases}x^{2}=q\\\\\nxy=6\\end{cases}\\end{equation}",
							"-\\{x^2+y^2}",
							"2+\\sqrt[1]{4}",
							"2+\\frac{2}{1}",
							"\\sqrt{x}^2"
 };

void check_miniunit(vector<string> tree[10][40][40], vector<string> tree_assist[10][40][40], int x, int y, int z);
int find_uint(vector<string> tree[10][40][40], vector<string> &uint, int i, int j, int k);

extern char latex[300][200];

#endif // ORIGINAL_TEST_CPP_IN_USE_CShape_DLL

/*
#if 0

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
	HMODULE hDll = LoadLibrary("MimeTeX.dll");
	vector<string> ImagePath;
	vector<string> Latex;

	string image_file = "image_file.txt";

	GetSamplePath(image_file,ImagePath);;

	char save_image[256];
	char save_image1[256];
	char save_image2[256];

	if(!Result_Out)
	{
		Result_Out = (struct Result_Data*)malloc(sizeof(struct Result_Data));
		Result_Out->ImageData = (intbyte*)malloc(30000*sizeof(intbyte));
		DataROI_New = create_memory(DataROI_New);
		DataROI_New_New = create_memory(DataROI_New_New);
	}
	else
	{
		for(int ii = 0; ii < 200; ii++)
		{
			Result_Out->Location[ii].substring = "";
			Result_Out->Location[ii].left = -1;
			Result_Out->Location[ii].top = -1;
			Result_Out->Location[ii].width = -1;
			Result_Out->Location[ii].height = -1;
			Result_Out->Location[ii].Box_width = -1;
			Result_Out->Location[ii].Box_height = -1;
			DataROI_New[ii] = Result_Out->Location[ii];
			DataROI_New_New[ii] = Result_Out->Location[ii];
		}
	}

	if (hDll)
    {
		typedef DWORD (*MYFUNC)(char* expr, char* filename);
		MYFUNC getDevNum = NULL;

		getDevNum = (MYFUNC)GetProcAddress(hDll,"CreateGifFromEq");
		raster* border_raster(), *Image=NULL;

		if(getDevNum)
		{
			for(int k = 0; k < 200; k++)
			{

				printf_s("\n\n");
				printf_s("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@正在处理第%d张图片\n", k);
				printf_s("%s\n",latex[k]);
				printf_s("\n\n");

				char tempGifFilePath[256] = "D:\\vs2012\\USE_CShape_DLL\\USE_CShape_DLL\\test.gif";

 				Result_Out = (Result_Data*)getDevNum(latex[k], tempGifFilePath);

				uchar* data = (uchar*)Result_Out->ImageData;
				int width = data[0] + data[1];
				int height = data[2] + data[3];

				IplImage* dst = cvCreateImage(cvSize(width, height), 8, 1);

				int count = 0;
				for(int i = 0; i < height; i++)
				{
					for(int j = 0; j < width; j++)
					{
						if(count < 2)
						{
							((uchar*)(dst->imageData + i * dst->widthStep))[j] = 0;
						}
						else
						{
							((uchar*)(dst->imageData + i * dst->widthStep))[j] = *data;
						}
						data++;
						count++;
					}
				}

				clock_t start, finish;
				double duration;
				start = clock();
#if 1
				int cnt = 200;

				vector<Draw_Information> Result;
				//将数据复制给新的结构体数组
				for (int i = 0; i < 200; i++)
				{
					DataROI_New[i] = Result_Out->Location[i];
				}

				vector<int> Boundary = process_new(DataROI_New, 0, cnt);

				//显示调整后的数据
				int max_width = 0;
				int max_height = 0;

				int count_ = Adjust_Data_new(DataROI_New, DataROI_New_New, Boundary, max_width, max_height, cnt);

				printf_s("================================1================================\n");
				for(int i = 0; i < count_; i++)
				{
					if(DataROI_New_New[i].left > -1)
					{
						printf_s("%s  %d  %d  %d  %d  %d  %d\n", DataROI_New_New[i].substring, DataROI_New_New[i].left, DataROI_New_New[i].top, DataROI_New_New[i].width, DataROI_New_New[i].height, DataROI_New_New[i].Box_width, DataROI_New_New[i].Box_height);
					}
				}

				//显示调整后的数据
				printf_s("==================================================================\n\n");

				Extract_Data(DataROI_New_New, Result, count_);

				finish = clock();
				duration = (double)(finish - start) / CLOCKS_PER_SEC;
				printf_s("%f seconds\n", duration);
				//画渲染图片
				Draw_Render_Image(dst, Result, max_height, max_width);
#endif

				finish = clock();
				duration = (double)(finish - start) / CLOCKS_PER_SEC;
				printf_s("%f seconds\n", duration);

				sprintf(save_image, "picture\\%s_render.png", ImagePath[k].c_str());
 				sprintf(save_image1, "C:\\Users\\Administrator\\Desktop\\公式标注\\%s.png", ImagePath[k].c_str());
				sprintf(save_image2, "picture\\%s.png", ImagePath[k].c_str());
				IplImage *SS = cvLoadImage(save_image1);
				IplImage *BB = cvLoadImage("0.jpg");

#if 1
				clock_t start_1, finish_1;
				double duration_1;
				start_1 = clock();
				Draw_Render_Move(BB);
				//Draw_Render_Move_1(BB);
				//Draw_Render_Move_2(BB);
				//Draw_Render_Move_3(BB);
				//Draw_Render_Move_4(BB);
				//Draw_Render_Move_5(BB);
				finish_1 = clock();
				duration_1 = (double)(finish_1 - start_1) / CLOCKS_PER_SEC;
				printf_s("%f seconds\n", duration_1);
#endif

				cvShowImage("2", BB);
				cvSaveImage(save_image2, SS);
				cvSaveImage(save_image, BB);
				cvReleaseImage(&SS);
				cvReleaseImage(&BB);

				//cvSaveImage("1.jpg", dst);
				//cvShowImage("1", dst);
				cvWaitKey(0);
				cvReleaseImage(&dst);
			}
		}
		//释放动态连接库。
		FreeLibrary(hDll);
		free(getDevNum);
    }

	free(DataROI_New);
	free(DataROI_New_New);
	free(Result_Out);
	//system("pause");
	return 0;
}
#else*/
/*
int main(int argc, char **argv)
{
	HMODULE hDll = LoadLibrary("MimeTeX.dll");
	vector<string> ImagePath;
	vector<string> Latex;

	string image_file = "image_file.txt";

	GetSamplePath(image_file,ImagePath);


	if(!Result_Out)
	{
		Result_Out = (struct Result_Data*)malloc(sizeof(struct Result_Data));
		DataROI_New = create_memory(DataROI_New);
		DataROI_New_New = create_memory(DataROI_New_New);
	}
	else
	{
		for(int ii = 0; ii < 400; ii++)
		{
			Result_Out->Location[ii].substring = "";
			Result_Out->Location[ii].left = -1;
			Result_Out->Location[ii].top = -1;
			Result_Out->Location[ii].width = -1;
			Result_Out->Location[ii].height = -1;
			Result_Out->Location[ii].Box_width = -1;
			Result_Out->Location[ii].Box_height = -1;
			DataROI_New[ii] = Result_Out->Location[ii];
			DataROI_New_New[ii] = Result_Out->Location[ii];
		}
	}

	if (hDll)
    {
		typedef DWORD (*MYFUNC)(char* expr, char* filename);
		MYFUNC getDevNum = NULL;

		getDevNum = (MYFUNC)GetProcAddress(hDll,"CreateGifFromEq");
		raster* border_raster(), *Image=NULL;

		if(getDevNum)
		{

			//char equation[256] = " e^x=\\sum_{n=0}^\\infty\\frac{x^n}{n!} ";
			//char equation[256] = " \\frac {\\sqrt {x^{2}+5}} {\\sqrt {2}}\\times \\frac {2} {3}=a^{3} ";
			//char
			int Index_C = 45;
			while(Index_C < 46)
			{
				char tempGifFilePath[256] = "test.gif";

#ifdef USE
				int length = strlen(argv[1]);
#else
				int length = strlen(equation[Index_C]);
#endif

				if(length == 0)
				{
					break;
				}
				else if (length > 150)
				{
					break;
				}
				else if(length == 1)
				{
					//strcat(argv[1], "\\quad");
#ifdef USE
					string A(argv[1]);
#else
					string A(equation[Index_C]);
#endif
					A = A + "\\quad";
					char file_name[7] = "";
					for(int iter = 0; iter < A.size(); iter++)
					{
						file_name[iter] = A[iter];
					}
					//argv[1] = "2\\quad";
					Result_Out = (Result_Data*)getDevNum(file_name, tempGifFilePath);
					//sprintf(argv[1], "%s%s", argv[1], "\\quad");
				}
				else
				{
#ifdef USE
					string B(argv[1]);
					if(B == "\\left [ \\right ]")
					{
						char file_name[20] = "No \\quad Answer";
						Result_Out = (Result_Data*)getDevNum(file_name, tempGifFilePath);
					}
					else if( B == "Not Support" || B == "Not Supported")
					{
						char file_name[20] = "No \\quad Answer";
						Result_Out = (Result_Data*)getDevNum(file_name, tempGifFilePath);
					}
					else if(argv[1][0] == '-')
					{
						string A(argv[1]);
#else
					string B(equation[Index_C]);
					if(B == "\\left [ \\right ]")
					{
						char file_name[10] = "NULL";
						Result_Out = (Result_Data*)getDevNum(file_name, tempGifFilePath);
					}
					else if(equation[Index_C][0] == '-' )
					{
						string A(equation[Index_C]);
#endif
						if(B.size() < 0)
							A.insert(0, "\\quad ");
						else
							A.insert(0, "\\-");
						char file_name[1000] = "";
						for(int iter = 0; iter < A.size(); iter++)
						{
							file_name[iter] = A[iter];
						}
#ifdef USE
						Result_Out = (Result_Data*)getDevNum(file_name, tempGifFilePath);
#else
						Result_Out = (Result_Data*)getDevNum(file_name, tempGifFilePath);
#endif
					}
					else
					{
 						//Result_Out = (Result_Data*)getDevNum(argv[1], tempGifFilePath);
						//printf("%s\n", argv[1]);

#ifdef USE
						string C(argv[1]);
						string D = findchar(C, "\\rightarrow");
						       D = findchar(D, "\\leftarrow");
						char file_name_[1000] = "";
						for(int iter = 0; iter < D.size(); iter++)
						{
							file_name_[iter] = D[iter];
						}
						//printf("ooooo %s\n", file_name_);
						//system("pause");
						Result_Out = (Result_Data*)getDevNum(file_name_, tempGifFilePath);
#else
						string C(equation[Index_C]);
						string D = findchar(C, "\\rightarrow");
						       D = findchar(D, "\\leftarrow");
						char file_name[1000] = "";
						for(int iter = 0; iter < D.size(); iter++)
						{
							file_name[iter] = D[iter];
						}
						Result_Out = (Result_Data*)getDevNum(file_name, tempGifFilePath);
#endif
					}
				}

				uchar* data = (uchar*)Result_Out->ImageData;
				int width = data[0] + data[1] + data[2] + data[3];
				int height = data[4] + data[5] + data[6] + data[7];

				if(width == 0 && height == 0)
				{
					break;
				}
				IplImage* dst = cvCreateImage(cvSize(width, height), 8, 1);

				int count = 0;
				for(int i = 0; i < height; i++)
				{
					for(int j = 0; j < width; j++)
					{
						if(count < 2)
						{
							((uchar*)(dst->imageData + i * dst->widthStep))[j] = 0;
						}
						else
						{
							((uchar*)(dst->imageData + i * dst->widthStep))[j] = *data;
						}
						data++;
						count++;
					}
				}


#if 1
				int cnt = 400;

				vector<Draw_Information> Result;
				//将数据复制给新的结构体数组
				for (int i = 0; i < 400; i++)
				{
					DataROI_New[i] = Result_Out->Location[i];
				}
				vector<int> Boundary = process_new(DataROI_New, 0, cnt);

				//显示调整后的数据
				int max_width = 0;
				int max_height = 0;

				int count_ = Adjust_Data_new(DataROI_New, DataROI_New_New, Boundary, max_width, max_height, cnt);

				printf("================================1================================\n");
				for(int i = 0; i < count_; i++)
				{
					if(DataROI_New_New[i].left > -1)
					{
						printf("%s  %d  %d  %d  %d  %d  %d\n", DataROI_New_New[i].substring, DataROI_New_New[i].left, DataROI_New_New[i].top, DataROI_New_New[i].width, DataROI_New_New[i].height, DataROI_New_New[i].Box_width, DataROI_New_New[i].Box_height);
					}
				}

				//显示调整后的数据
				printf("==================================================================\n\n");
				Extract_Data(DataROI_New_New, Result, count_);

				//画渲染图片
				Draw_Render_Image(dst, Result, max_height, max_width);
#endif
				IplImage* BB = cvLoadImage("0.png");
				Draw_Render_Move_6(BB);
				cvShowImage("2", BB);
				cvSaveImage("1.png", dst);
				cvShowImage("1", dst);
				cvWaitKey(0);
				cvReleaseImage(&dst);
				cvReleaseImage(&BB);
				Index_C++;
			}
		}
		//释放动态连接库。
		FreeLibrary(hDll);
    }

	//system("pause");
	return 0;
}
*/

#define LATEX_LL  400
#ifdef ORIGINAL_TEST_CPP_IN_USE_CShape_DLL
/////////////////////////////////////////////////
int main(int argc, char **argv)
{



	//HMODULE hDll = LoadLibrary("MimeTeX.dll");
	vector<string> ImagePath;
	vector<string> Latex;

	string image_file = "image_file.txt";

	GetSamplePath(image_file, ImagePath);


	if (!Result_Out)
	{
		Result_Out = (struct Result_Data*)malloc(sizeof(struct Result_Data));
		DataROI_New = create_memory(DataROI_New);
		DataROI_New_New = create_memory(DataROI_New_New);
	}
	else
	{
		for (int ii = 0; ii < LATEX_LL; ii++)
		{
			Result_Out->Location[ii].substring = "";
			Result_Out->Location[ii].left = -1;
			Result_Out->Location[ii].top = -1;
			Result_Out->Location[ii].width = -1;
			Result_Out->Location[ii].height = -1;
			Result_Out->Location[ii].Box_width = -1;
			Result_Out->Location[ii].Box_height = -1;
			DataROI_New[ii] = Result_Out->Location[ii];
			DataROI_New_New[ii] = Result_Out->Location[ii];
		}
	}

	{
		raster* border_raster(), *Image = NULL;

		//if (getDevNum)
		{

			//char equation[256] = " e^x=\\sum_{n=0}^\\infty\\frac{x^n}{n!} ";
			//char equation[256] = " \\frac {\\sqrt {x^{2}+5}} {\\sqrt {2}}\\times \\frac {2} {3}=a^{3} ";
			//char
			int Index_C = 39;
			while (Index_C < 40)
			{
				char tempGifFilePath[256] = "test.gif";


				int length = strlen(equation[Index_C]);


				if (length == 0)
				{
					break;
				}
				else if (length > LATEX_LL)
				{
					break;
				}
				else if (length == 1)
				{
					//strcat(argv[1], "\\quad");

					string A(equation[Index_C]);

					A = A + "\\quad";
					char file_name[7] = "";
					for (int iter = 0; iter < A.size(); iter++)
					{
						file_name[iter] = A[iter];
					}
					//argv[1] = "2\\quad";
					//Result_Out = (Result_Data*)getDevNum(file_name, tempGifFilePath);
					Result_Out = (Result_Data*)CreateGifFromEq(file_name, tempGifFilePath);
					//sprintf(argv[1], "%s%s", argv[1], "\\quad");
				}
				else
				{

					string B(equation[Index_C]);
					if (B == "\\left [ \\right ]")
					{
						char file_name[10] = "NULL";
						Result_Out = (Result_Data*)CreateGifFromEq(file_name, tempGifFilePath);
					}
					else if (equation[Index_C][0] == '-')
					{
						string A(equation[Index_C]);

						if (B.size() < 0)
							A.insert(0, "\\quad ");
						else
							A.insert(0, "\\-");
						char file_name[1000] = "";
						for (int iter = 0; iter < A.size(); iter++)
						{
							file_name[iter] = A[iter];
						}

						Result_Out = (Result_Data*)CreateGifFromEq(file_name, tempGifFilePath);

					}
					else
					{
						string C(equation[Index_C]);
						string D = findchar(C, "\\rightarrow");
						D = findchar(D, "\\leftarrow");
						char file_name[1000] = "";
						for (int iter = 0; iter < D.size(); iter++)
						{
							file_name[iter] = D[iter];
						}
						Result_Out = (Result_Data*)CreateGifFromEq(file_name, tempGifFilePath);

					}
				}

				uchar* data = (uchar*)Result_Out->ImageData;
				int width = Result_Out->width;// data[0] + data[1] + data[2] + data[3];
				int height = Result_Out->height;// data[4] + data[5] + data[6] + data[7];
				printf("%d ,%d--------------------------", width, height);

				if (width == 0 && height == 0)
				{
					break;
				}
				IplImage* dst = cvCreateImage(cvSize(width, height), 8, 1);




				for (int i = 0; i < height; i++)
				{
					for (int j = 0; j < width; j++)
					{
						((uchar*)(dst->imageData + i * dst->widthStep))[j] = *data;
						data++;
					}
				}

				cvSaveImage("testr.png", dst);
				//FILE *fp = fopen("tgif.gif", "w+");

				//fwrite(Result_Out->ImageData, sizeof((const char*)Result_Out->ImageData),1, fp);
				//fclose(fp);
#if 1
				int cnt = LATEX_LL;

				vector<Draw_Information> Result;
				//将数据复制给新的结构体数组
				for (int i = 0; i < LATEX_LL; i++)
				{
					DataROI_New[i] = Result_Out->Location[i];
				}
				vector<int> Boundary = process_new(DataROI_New, 0, cnt);

				//显示调整后的数据
				int max_width = 0;
				int max_height = 0;

				int count_ = Adjust_Data_new(DataROI_New, DataROI_New_New, Boundary, max_width, max_height, cnt);

				printf("================================1================================\n");
				for (int i = 0; i < count_; i++)
				{
					if (DataROI_New_New[i].left > -1)
					{
						printf("%s  %d  %d  %d  %d  %d  %d\n", DataROI_New_New[i].substring, DataROI_New_New[i].left, DataROI_New_New[i].top, DataROI_New_New[i].width, DataROI_New_New[i].height, DataROI_New_New[i].Box_width, DataROI_New_New[i].Box_height);
					}
				}

				//显示调整后的数据
				printf("==================================================================\n\n");
				Extract_Data(DataROI_New_New, Result, count_);

				//画渲染图片
				IplImage * dataimg = Draw_Render_Image(dst, Result, max_height, max_width);
#endif
				//IplImage* BB = cvLoadImage("0.png");

				//cvShowImage("2", BB);
				//cvShowImage("1", dataimg);
				cvWaitKey(0);
				//cvReleaseImage(&BB);

				cvReleaseImage(&dst);
				//if (dataimg != NULL) { cvReleaseImage(&dataimg); dataimg = NULL; }

				Index_C++;
			}
		}

	}

	//=========================解析位置关系=====================
	FILE* fp = fopen("d:\\test.txt", "r");
	vector<string> latex;
	char img_buf[256];
	while (!feof(fp))
	{
		fscanf(fp, "%s", img_buf);
		string str(img_buf);
		latex.push_back(str);
	}
	fclose(fp);

	if (latex.size() > 5)
	{
		vector<string> latex_new;
		vector<int> index;
		vector<bool> index_bool;
		int count = 0;
		for (int i = 0; i < latex.size() - 1; i++)
		{
			latex_new.push_back(latex[i]);
			if (latex_new[i] == "{")
			{
				count++;
				index.push_back(count);
				index_bool.push_back(true);
			}
			else
			{
				index.push_back(0);
				index_bool.push_back(false);
			}
			printf("%s", latex_new[i].c_str());
		}

		for (int i = 0; i < latex_new.size(); i++)
		{
			if (latex_new[i] == "}")
			{
				for (int j = i; j > -1; j--)
				{
					if (index_bool[j])
					{
						index[i] = index[j];
						index_bool[j] = false;
						break;
					}
				}
			}
		}

		// by huanwang
		//  formula structure json description generation code
	    // 王庆丰：就是获取结构那的代码，及最后结果。
		vector<string> tree[10][40][40];
		vector<string> tree_assist[10][40][40];
		tree[0][0][0] = latex_new;

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 40; j++)
			{
				for (int k = 0; k < 40; k++)
				{
					if (tree[i][j][k].size() > 1)
						check_miniunit(tree, tree_assist, i, j, k);
				}
			}
		}
		printf("\n\n");
		vector<string> uint;
		find_uint(tree, uint, 0, 0, 0);
		int value = 0;
	}
	return 0;
}
//#endif


int find_uint(vector<string> tree[10][40][40], vector<string> &uint, int x, int y, int z)
{
	if (tree[x][y][z].size() > 0)
	{
		for (int n = 0; n < tree[x][y][z].size(); n++)
			printf("%s", tree[x][y][z][n].c_str());
		printf("\n");
	}

	if (tree[x][y][z].size() > 1)//不是叶子节点，遍历下一层
	{
		int index = 0;
		for (int i = 0; i < 40; i++)
		{
			if (tree[x + 1][i][y].size() > 0)
			{
				index = i;
				break;
			}
		}
		find_uint(tree, uint, x + 1, index, y);
	}
	else if (tree[x][y][z].size() == 1)//是叶子节点
	{
		uint.push_back(tree[x][y][z][0]);//存储叶子节点
		if (tree[x][y + 1][z].size() > 0)//叶节点有兄弟节点，遍历兄弟节点
			find_uint(tree, uint, x, y + 1, z);
		else//没有兄弟节点
		{
			//============找到上一级的父节点===========
			int index = 0;
			for (int i = 0; i < 40; i++)
			{
				if ((x - 1) < 0)
					return 0;
				if (tree[x - 1][z][i].size()>0)
				{
					index = i;
					break;
				}
			}
			if (tree[x - 1][z + 1][index].size() > 0) //父节点有兄弟节点, 遍历兄弟节点
				find_uint(tree, uint, x - 1, z + 1, index);
			else//父节点没有兄弟节点，寻找爷节点
			{
				int index_ = 0;
				for (int j = 0; j < 40; j++)
				{
					if ((x - 2) < 0)
						return 0;
					if (tree[x - 2][index][j].size() > 0)
					{
						index_ = j;
						break;
					}
				}
				if (tree[x - 2][index + 1][index_].size() > 0)//爷节点的兄弟节点存在，遍历它
					find_uint(tree, uint, x - 2, index + 1, index_);
			}
		}
	}
}

void check_miniunit(vector<string> tree[10][40][40], vector<string> tree_assist[10][40][40], int x, int y, int z)
{
	//===========================找到表达式包含{}结构模块==========================
	vector<int> index;
	vector<bool> index_bool;

	int count = 0;
	for (int i = 0; i < tree[x][y][z].size(); i++)
	{
		if (tree[x][y][z][i] == "{")
		{
			count++;
			index.push_back(count);
			index_bool.push_back(true);
		}
		else
		{
			index.push_back(0);
			index_bool.push_back(false);
		}
	}

	for (int i = 0; i < tree[x][y][z].size(); i++)
	{
		if (tree[x][y][z][i] == "}")
		{
			for (int j = i; j > -1; j--)
			{
				if (index_bool[j])
				{
					index[i] = index[j];
					index_bool[j] = false;
					break;
				}
			}
		}
	}
	//=============================================================================

	//===========================找到表达式包含[]的结构模块========================
	vector<int> index_;
	vector<bool> index_bool_;

	int count_ = 0;
	for (int i = 0; i < tree[x][y][z].size(); i++)
	{
		if (tree[x][y][z][i] == "[")
		{
			count_++;
			index_.push_back(count_);
			index_bool_.push_back(true);
		}
		else
		{
			index_.push_back(0);
			index_bool_.push_back(false);
		}
	}

	for (int i = 0; i < tree[x][y][z].size(); i++)
	{
		if (tree[x][y][z][i] == "]")
		{
			for (int j = i; j > -1; j--)
			{
				if (index_bool_[j])
				{
					index_[i] = index_[j];
					index_bool_[j] = false;
					break;
				}
			}
		}
	}
	//===========================================================================

	for (int i = 0; i < tree[x][y][z].size(); i++)
	{
		if (tree[x][y][z][i] == "{")//查看表达式中是否含有根号，除法，右上角标等结构
		{
			int right = 0;
			for (int j = i + 1; j < tree[x][y][z].size(); j++)
			{
				if (index[j] == index[i])
				{
					right = j;
					break;
				}
			}
			for (int j = 0; j < 40; j++)//找该层没有使用的元组
			{
				if (tree[x+1][j][y].size() == 0)
				{
					for (int k = i + 1; k < right; k++)//将结构块赋给该元组
					{
						tree[x + 1][j][y].push_back(tree[x][y][z][k]);
					}
					if ((i - 1) > -1)//标注除法，根号，右上下角标结构
					{
						if (tree[x][y][z][i - 1] == "frac")
							tree_assist[x + 1][j][y].push_back("frac");
						else if (tree[x][y][z][i - 1] == "sqrt")
							tree_assist[x + 1][j][y].push_back("sqrt");
						else if (tree[x][y][z][i - 1] == "subscript")
							tree_assist[x + 1][j][y].push_back("subscript");
						else if (tree[x][y][z][i - 1] == "supscript")
							tree_assist[x + 1][j][y].push_back("supscript");
					}

					break;
				}
			}
			i = right;

		}
		else if (tree[x][y][z][i] == "[") //查看是否存在除法的分子、分母结构
		{
			int right = 0;
			for (int j = i + 1; j < tree[x][y][z].size(); j++)
			{
				if (index_[j] == index_[i])
				{
					right = j;
					break;
				}
			}

			for (int j = 0; j < 40; j++)//找该层没有使用的元组
			{
				if (tree[x + 1][j][y].size() == 0)
				{
					for (int k = i + 1; k < right; k++)//将结构块赋给该元组
					{
						tree[x + 1][j][y].push_back(tree[x][y][z][k]);
					}
					break;
					if ((i - 2) > -1 && tree[x][y][z][i - 1] == "{" && tree[x][y][z][i - 2] == "sqrt")//标注根号左上角标结构
						tree_assist[x + 1][j][y].push_back("topleft");

				}
			}
			i = right;
		}
		else if (tree[x][y][z][i] == "top" || tree[x][y][z][i] == "bottom" || tree[x][y][z][i] == "frac" || tree[x][y][z][i] == "sqrt" || tree[x][y][z][i] == "subscript" || tree[x][y][z][i] == "supscript")
		{
			continue;
		}
		else
		{
			for (int j = 0; j < 40; j++)//找该层没有使用的元组,然后将unit单元，赋给元组
			{
				if (tree[x + 1][j][y].size() == 0)
				{
					tree[x + 1][j][y].push_back(tree[x][y][z][i]);
					break;
				}
			}
		}
	}
}
#endif

struct Data_Info* create_memory(struct Data_Info* DataROI)
{
	int i = 0;
	DataROI = (struct Data_Info*)malloc(LATEX_LL*sizeof(struct Data_Info));
	for (i = 0; i < LATEX_LL; i++)
	{
		DataROI[i].substring = "";
		DataROI[i].left = -1;
		DataROI[i].top = -1;
		DataROI[i].width = -1;
		DataROI[i].height = -1;
		DataROI[i].Box_width = -1;
		DataROI[i].Box_height = -1;
	}
	return DataROI;
}


#ifdef ORIGINAL_TEST_CPP_IN_USE_CShape_DLL
int GetSamplePath(string FilePath, vector<string>& Information)
{
	FILE *pfile = fopen(FilePath.c_str(), "r");
	if (pfile == NULL)
	{
		printf("open file:\"%s\" error!\n", FilePath.c_str());
		return -1;
	}
	char img_buf[1024];

	IplImage* temp;
	int count = 0;
	while (!feof(pfile))
	{
		fscanf(pfile, "%s\n", img_buf);
		string str(img_buf);
		Information.push_back(str);
	}
	return 0;
}


string findchar(string L, string S)//查找子串
{
	string Out = L;
	int pos = -1;
	if(L.size() < S.size())
		return L;
	else if(L.size() == S.size() && L == S)
		return L;
	else
	{
		for(int i = 0; i < L.size()- S.size(); i++)
		{
			bool find = true;
			for(int j = 0; j < S.size(); j++)
			{
				if(L[i+j] != S[j])
					find = false;
			}
			if(find)
				Out.insert(i + S.size(), " ");
		}
		return Out;
	}
}
#endif

#include "Render.h"

#ifdef DEBUG
int main(int argc, char* argv[])
#else
char *mimetex_parse(char *expression, char *gifFileName)
#endif
{
    char full_parse_str[4096];

    int ii;

    if (!Result_Out)
	{
		Result_Out = (struct Result_Data*)malloc(sizeof(struct Result_Data));
		DataROI_New = create_memory(DataROI_New);
		DataROI_New_New = create_memory(DataROI_New_New);
	}
	else
	{
		for (int ii = 0; ii < LATEX_LL; ii++)
		{
			Result_Out->Location[ii].substring = "";
			Result_Out->Location[ii].left = -1;
			Result_Out->Location[ii].top = -1;
			Result_Out->Location[ii].width = -1;
			Result_Out->Location[ii].height = -1;
			Result_Out->Location[ii].Box_width = -1;
			Result_Out->Location[ii].Box_height = -1;
			memcpy(&(DataROI_New[ii]),&(Result_Out->Location[ii]), sizeof(struct Data_Info)) ;
			memcpy(&(DataROI_New_New[ii]),&(Result_Out->Location[ii]), sizeof(struct Data_Info)) ;
		}
	}

    int length = strlen(expression),i;


    // initialize string to parse
    strcpy(full_parse_str, expression);

    if (length == 0)
    {
        return "";
    }
    else if (length > LATEX_LL)
    {
        break;
    }
    else if (length == 1)
    {
        strcat(full_parse_str, "\\quad");
        Result_Out = (Result_Data*)CreateGifFromEq(full_parse_str, gifFileName);
    }
    else
    {


        if (!strcmp(expression, "\\left [ \\right ]")
        {
            return "":
        }
        else if (expression[0] == '-')
        {

            for(i=0; i<=strlen(expression); i++)
                full_parse_str[i+1]=full_parse_str[i];
            full_parse_str[0]='-';

            Result_Out = (Result_Data*)CreateGifFromEq(full_parse_str, gifFileName);

        }
        else
        {
#ifdef ANSWSERED_BY_WANGQINGFENG
            string C(equation[Index_C]);
            string D = findchar(C, "\\rightarrow");
            D = findchar(D, "\\leftarrow");
            char file_name[1000] = "";x
            for (int iter = 0; iter < D.size(); iter++)
            {
                file_name[iter] = D[iter];
            }
            Result_Out = (Result_Data*)CreateGifFromEq(file_name, gifFileName);
#endif // ANSWSERED_BY_WANGQINGFENG
            ;

        }
    }

#ifdef OPENCV_WRITE_IMAGE
    uchar* data = (uchar*)Result_Out->ImageData;
    int width = Result_Out->width;// data[0] + data[1] + data[2] + data[3];
    int height = Result_Out->height;// data[4] + data[5] + data[6] + data[7];
    printf("%d ,%d--------------------------", width, height);

    if (width == 0 && height == 0)
    {
        break;
    }
    IplImage* dst = cvCreateImage(cvSize(width, height), 8, 1);




    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ((uchar*)(dst->imageData + i * dst->widthStep))[j] = *data;
            data++;
        }
    }

    cvSaveImage("testr.png", dst);

    //FILE *fp = fopen("tgif.gif", "w+");

    //fwrite(Result_Out->ImageData, sizeof((const char*)Result_Out->ImageData),1, fp);
    //fclose(fp);

#endif // OPENCV_WRITE_IMAGE


    int cnt = LATEX_LL;


    //将数据复制给新的结构体数组
    for (i = 0; i < LATEX_LL; i++)
    {
        memcpy(&(DataROI_New[i]),&(Result_Out->Location[i]), sizeof(struct Data_Info)) ;

    }

    int n_Boundary, n_construct;
    int *Boundary = process_new(DataROI_New, 0, cnt, &n_construct, &n_Boundary);

    //显示调整后的数据
    int max_width = 0;
    int max_height = 0;

    struct Data_Info DataROI_New_New[LATEX_LL], Result[LATEX_LL];
    int n_Result;

    int count_ = Adjust_Data_new(DataROI_New, DataROI_New_New, Boundary, n_Boundary, &max_width, &max_height, cnt);

    printf("================================1================================\n");
    for (int i = 0; i < count_; i++)
    {
        if (DataROI_New_New[i].left > -1)
        {
            printf("%s  %d  %d  %d  %d  %d  %d\n", DataROI_New_New[i].substring, DataROI_New_New[i].left, DataROI_New_New[i].top, DataROI_New_New[i].width, DataROI_New_New[i].height, DataROI_New_New[i].Box_width, DataROI_New_New[i].Box_height);
        }
    }

    //显示调整后的数据
    printf("==================================================================\n\n");

    Extract_Data(DataROI_New_New, Result, count_, &n_Result);

#ifdef OPENCV_RENDER_IMAGE
    //画渲染图片
    IplImage * dataimg = Draw_Render_Image(dst, Result, max_height, max_width);

    //IplImage* BB = cvLoadImage("0.png");

    //cvShowImage("2", BB);
    //cvShowImage("1", dataimg);
    cvWaitKey(0);
    //cvReleaseImage(&BB);

    cvReleaseImage(&dst);
    //if (dataimg != NULL) { cvReleaseImage(&dataimg); dataimg = NULL; }
#endif


}
