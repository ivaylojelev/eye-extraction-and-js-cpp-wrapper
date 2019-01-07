
#include "libopencvjs.h"
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"


#include "CPPWrapper.h"

extern "C" { // Cause of name mangling in C++, we use extern C here
/***/
int abs(int x) {if(x>0) {return x; } return -x;}


/**
* Isolates the two patches that correspond to the user's eyes
* @param  {Canvas} imageCanvas - canvas corresponding to the webcam stream
* @param  {Number} width - of imageCanvas
* @param  {Number} height - of imageCanvas
* @return {Object} the two eye-patches, first left, then right eye
*/
	eyeObj * getEyePatches(int* workingImage, int imWidth, int imHeight)
	{


		RectC face = detectFace(workingImage, imWidth, imHeight);

		//offsets of the working image from the top left corner of the video canvas
		int offsetX = 0;
		int offsetY = 0;

		int width = face.width;
		int height = floor(face.height / 2);
		//offset from detected face
		offsetX = face.x;
		offsetY = face.y;

		int* workingImageEyes = new int[width*height];
		for (int i = offsetX; i < offsetX + width; i++)
		{
			for (int j = offsetY; j < offsetY + height; j++) workingImageEyes[i++] = workingImage[i*imWidth + j];
		}
		delete[] workingImage;
		RectC* eyes = detectEyes(workingImageEyes, width, height);
		//if (eyes == null){
		//    return null;
		//}

		eyeObj* eyeObjs = new eyeObj();

		int** leftImageData = new int*[width];
		for (int i = 0; i < width; i++) leftImageData[i] = new int[height];
		for (int i = eyes[0]->x + offsetX; i <= eyes[0]->x + offsetX + eyes[0]->width; i++)
		{
			for (int j = eyes[0]->y + offsetY; j <= eyes[0]->y + offsetY + eyes[0]->height; j++)
				leftImageData[i - offsetX][j - offsetY] = workingImage[i][j];
		}
		eye* left = new eye();
		left->patch = leftImageData;
		left->imagex: eyes[0]->x + offsetX;
		left->imagey: eyes[0]->y + offsetY;
		left->width: eyes[0]->width;
		left->height: eyes[0]->height;


		int** rightImageData = new int*[width];
		for (int i = 0; i < width; i++) rightImageData[i] = new int[height];
		for (int i = eyes[1]->x + offsetX; i <= eyes[1]->x + offsetX + eyes[1]->width; i++)
		{
			for (int j = eyes[1]->y + offsetY; j <= eyes[1]->y + offsetY + eyes[1]->height; j++)
				rightImageData[i - offsetX][j - offsetY] = workingImage[i][j];
		}
		eye* right = new eye();
		right->patch = rightImageData,
		right->imagex: eyes[0]->x + offsetX;
		right->imagey: eyes[0]->y + offsetY;
		right->width: eyes[0]->width;
		right->height: eyes[0]->height;

		eyeObjs->left = left;
		eyeObjs->right = right;

		return eyeObjs;
	}

	/**
	* Performs eye detection on the passed working image
	* @param {ImageData} workingImage - either the whole canvas or the upper half of the head
	* @param {Number} width - width of working image
	* @param {Number} height - height of working image
	* @return {Array} eyes - array of rectangle information.
	*/
	RectC * detectEyes(int* pixels, int width, int height)
	{
		int length;
		RectC* intermediateEyes = violaJonesEyes(pixels, length);
		RectC* eyes = new int[2];
		if (length>1) {
			//find the two eyes with the shortest y distance
			int minimumYDistance = 1000;

			for (int i = 0; i < length; i++) {
				for (int j = i + 1; j < length; j++) {
					int YDistance = abs(floor(intermediateEyes[i]->y) - floor(intermediateEyes[j]->y));
					if (YDistance <= minimumYDistance) {
						minimumYDistance = YDistance;
						eyes[0] = intermediateEyes[i];
						eyes[1] = intermediateEyes[j];
					}
				}
			}

			//eyes.sort(function(a,b) {
			//  return a[0]-b[0]
			//});
			delete[] intermediateEyes;
			return eyes;
		}
		else
		{
			return null;
		}
	}

	/**
	* Performs face detection on the passed canvas
	* @param {ImageData} workingImage - whole video canvas
	* @param {Number} width - width of imageCanvas
	* @param {Number} height - height of imageCanvas
	* @return {Array} face - array of rectangle information
	*/
	RectC detectFace(int *pixels, int width, int height) {
		int length;
		RectC* intermediateFaces = violaJonesFaces(pixels, length);
		RectC face = findLargestRectangle(intermediateFaces, length);
		delete[] intermediateFaces;
		return face;
	}

	/**
	* Goes through an array of rectangles and returns the one with the largest area
	* @param {Array.<Array.<Number>>} rectangles - array of arrays of format [xCoordinate, yCoordinate, width, height]
	* @return {Array} largestRectangle = [xCoordinate, yCoordinate, width, height]
	*/
	RectC findLargestRectangle(RectC* rectangles, int length) {
		int largestArea = 0;
		int area = 0;
		RectC largestRectangle = (rectangles[0]);
		for (int i = 0; i < length; ++i) {
			area = rectangles[i].width * rectangles[i].height;
			if (area > largestArea) {
				largestArea = area;
				largestRectangle = rectangles[i];
			}
		}
		return largestRectangle;
	}
}