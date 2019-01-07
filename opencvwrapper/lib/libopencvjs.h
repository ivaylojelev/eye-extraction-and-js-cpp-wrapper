#ifndef LIBOPENCVJS
#define LIBOPENCVJS

extern "C"
{
	struct RectC
	{
		int x; int y; int width; int height;
	};
	struct eye
	{
		int *patch;
		int imagex;
		int imagey;
		int width;
		int height;
	};
	struct eyeObj
	{
		eye* left; eye* right;
	};
	RectC findLargestRectangle(RectC*, int);
	RectC detectFace(int*, int, int);
	RectC* detectEyes(int*, int, int);
	eyeObj* getEyePatches(int* , int , int );
}
#endif