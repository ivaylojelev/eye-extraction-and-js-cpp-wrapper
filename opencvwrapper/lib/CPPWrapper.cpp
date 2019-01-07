#include "libopencvjs.h"

#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

using namespace cv;
using namespace std;

RectC* violaJonesEyes(InputArray face, int & length)
{
	CascadeClassifier eyes_cascade;
	vector<Rect> intEyes = eyes_cascade.detectMultiScale(face);
		int len = intEyes.size();
		RectC* eyes = new RectC[len];
		RectC* workingRect = new RectC();
		for(int i = 0; i < len; i++)
		{
			workingRect->x = intEyes[i].x;
			workingRect->y = intEyes[i].y;
			workingRect->width = intEyes[i].width;
			workingRect->height = intEyes[i].height;
			memcpy(&eyes[i], workingRect, sizeof(RectC));
		}
		delete workingRect;
		return eyes;
}
RectC* violaJonesFaces(InputArray pixels, int & length)
{

	CascadeClassifier fc;
	vector<Rect> intFace = fc.detectMultiScale(pixels);
	const len = intFace.size();
	RectC* Face = new RectC[len];
	RectC* workingRect = new RectC();
	for (int i = 0; i < len; i++)
	{
		workingRect->x = intFace[i].x;
		workingRect->y = intFace[i].y;
		workingRect->width = intFace[i].width;
		workingRect->height = intFace[i].height;
		memcpy(&Face[i], workingRect, sizeof(RectC));
	}
	delete workingRect;
	return Face;
}