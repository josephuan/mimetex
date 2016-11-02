
#ifdef ORIGINAL_TEST_CPP_IN_USE_CShape_DLL

#include <stdio.h>
#include <opencv2/opencv.hpp>
//#include"mimetex\mimetex.h"

using namespace cv;
using namespace std;

#define pixbyte  unsigned char
#define intbyte  unsigned char

#define	raster	struct raster_struct	/* "typedef" for raster_struct*/
raster
{
	/* -----------------------------------------------------------------------
	dimensions of raster
	------------------------------------------------------------------------ */
	int	width;				/* #pixels wide */
	int	height;				/* #pixels high */
	int	pixsz;				/* #bits per pixel, 1 or 8 */
	/* -----------------------------------------------------------------------
	memory for raster
	------------------------------------------------------------------------ */
	pixbyte *pixmap;		/* memory for width*height bits or bytes */
} ; /* --- end-of-raster_struct --- */

typedef void *((*HANDLER)());		/* ptr to function returning void* */
#define	mathchardef	struct mathchardef_struct /*typedef for mathchardef*/
mathchardef
  {
  /* -----------------------------------------------------------------------
  symbol name ("a", "\alpha", "1", etc)
  ------------------------------------------------------------------------ */
  char	*symbol;			/* as it appears in a source file */
  /* -----------------------------------------------------------------------
  components of \mathchardef hexadecimal code assigned to this symbol
  ------------------------------------------------------------------------ */
  int	charnum;			/* char# (as given in .gf file) */
  int	family;				/* font family e.g., 2=math symbol */
  int	class_;				/* e.g., 3=relation, TexBook pg.154*/
  /* ------------------------------------------------------------------------
  Extra info: some math "functions" require special processing (e.g., \frac)
  ------------------------------------------------------------------------ */
  /* --- function that performs special processing required by symbol --- */
  /* subraster *((*handler)()); -- handler is ultimately recast like this */
  HANDLER handler;			/* e.g., rastfrac() for \frac's */
  } ; /* --- end-of-mathchardef_struct --- */

#define	subraster struct subraster_struct /* "typedef" for subraster_struct*/
subraster
  {
  /* --- subraster type --- */
  int	type;				/* charcter or image raster */
  /* --- character info (if subraster represents a character) --- */
  mathchardef *symdef;			/* mathchardef identifying image */
  int	baseline;			/*0 if image is entirely descending*/
  int	size;				/* font size 0-4 */
  /* --- upper-left corner for bitmap (as overlaid on a larger raster) --- */
  int	toprow, leftcol;		/* upper-left corner of subraster */
  /* --- pointer to raster bitmap image of subraster --- */
  raster *image;			/*ptr to bitmap image of subraster*/
  } ; /* --- end-of-subraster_struct --- */


struct Data_Info
{
	char* substring;
	int top;
	int left;
	int height;
	int width;
	int Box_width;
	int Box_height;
};


struct Result_Data
{
	struct Data_Info* Location;
	intbyte* ImageData;
	int width;
	int height;
};

//extern _declspec(dllexport)struct Result_Data* _cdecl
//CreateGifFromEq(char *expression, char *gifFileName);

#ifdef __cplusplus
extern "C"
{
#endif

	extern _declspec(dllexport)struct Result_Data*
		CreateGifFromEq(char *expression, char *gifFileName);

#ifdef __cplusplus
}
#endif

struct Draw_Information
{
	char* str;
	CvRect rect;
};


struct Move_Info
{
	int x;
	int y;
	int dx;
	int dy;
	//float scale;
};

vector<int> process_new(struct Data_Info* DataROI, int left, int right);
int Adjust_Data(Data_Info* DataROI_New, Data_Info* DataROI_New_New, vector<int> Boundary, int &max_width, int &max_height, int cnt);
int Adjust_Data_new(Data_Info* DataROI_New, Data_Info* DataROI_New_New, vector<int> Boundary, int &max_width, int &max_height, int cnt);
void Extract_Data(Data_Info* DataROI_New_New, vector<Draw_Information> &Result, int count);
IplImage* Draw_Render_Image(IplImage* src, vector<Draw_Information> Result, int max_height, int max_width);
void Draw_Render_Move(IplImage* src);
void Draw_Render_Move_1(IplImage* dst);
void Draw_Render_Move_2(IplImage* dst);
void Draw_Render_Move_3(IplImage* dst);
void Draw_Render_Move_4(IplImage* dst);
void Draw_Render_Move_5(IplImage* dst);
void Draw_Render_Move_6(IplImage* dst);

#endif

#define pixbyte  unsigned char
#define intbyte  unsigned char


struct Data_Info
{
	char* substring;
	int top;
	int left;
	int height;
	int width;
	int Box_width;
	int Box_height;
};


struct Result_Data
{
    int Data_Info_Num;
	struct Data_Info* Location;
	intbyte* ImageData;
	int width;
	int height;
};

int *process_new(struct Data_Info* DataROI, int left, int right, int **nn_construct, int **n_Boundary);
int Adjust_Data_new(struct Data_Info* DataROI_New, struct Data_Info* DataROI_New_New, int *Boundary, int n_Boundary, int *max_width, int *max_height, int cnt);
void Extract_Data(struct Data_Info* DataROI_New_New, struct Data_Info *Result, int count, int *nn_Result);
