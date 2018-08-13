#include "stdafx.h"
#include "opencv2\opencv.hpp"
#include <iostream>
#include <filesystem>

#ifdef _DEBUG
#pragma comment (lib, "opencv_world400d.lib")
#else
#pragma comment (lib, "opencv_world400.lib")
#endif

using namespace cv;
using namespace std;
namespace fs = std::experimental::filesystem;

int main(int argc, char* argv[]) {
	vector<Mat> images, img;
	string FilePath = "PanoImages/";
	int cunt = 0;
	for (auto & Path : fs::directory_iterator(FilePath)) {
		images.push_back(imread(Path.path().string()));
		img.push_back(imread(Path.path().string()));
		if (images[cunt].data == NULL) {
			cout << "Could not open or find the images !!" << endl;
			cout << "Error on image " << cunt + 1 << " | Path : " << Path.path().string() << endl;
			getchar();
			return -1;
		}
		else {
			resize(img[cunt], img[cunt], Size(200, 200));
		}
		cout << Path << endl;
		cunt++;
	}
	cout << "Load Images Successful" << endl;
	Mat result, together;
	unsigned long startT = 0, endT = 0;
	Stitcher stitcher = Stitcher::createDefault();
	startT = getTickCount();
	Stitcher::Status status = stitcher.stitch(images, result);
	endT = getTickCount();
	printf("\nStitching processing time : %.2lf sec \n", (endT - startT) / getTickFrequency());
	if (status == Stitcher::OK) {
		namedWindow("Stitch Result", 0);
		//resizeWindow("Stitch Result", Size(600, 400));
		imshow("Stitch Result", result);
		imwrite("StitchCPP.jpg", result);
		hconcat(img, together);
		namedWindow("Show Together Images", 0);
		//resizeWindow("Show Together Images", Size(600, 200));
		imshow("Show Together Images", together);
		imwrite("TogetherCPP.jpg", together);
	}
	else {
		printf("Stitching failed !!");
		getchar();
		return -1;
	}
	waitKey();
	return 0;
}
