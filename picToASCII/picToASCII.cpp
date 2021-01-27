// picToASCII.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include<opencv2/opencv.hpp>
#include<stdio.h>
#include<string>
#include <fstream>
using namespace std;
using namespace cv;

void fileNameSanitization(string& f1, string& f2) {
	replace(f1.begin(), f1.end(), '\\', '/');
	replace(f2.begin(), f2.end(), '\\', '/');
}

bool sizeVerification(int w, int h) {
	if (w < 4 || h < 2) {
		cout << "Width or height must be >=4 characters big!" << endl;
		return false;
	}
	return true;
}

bool loadInputImg(string fileName, Mat& img) {
	img = imread(fileName, IMREAD_GRAYSCALE);
	if (img.empty()) return false;
	return true;
}

void showInputImg(string fileName) {
	Mat img_rgb = imread(fileName);
	string windowName = "output";
	namedWindow(windowName, WINDOW_KEEPRATIO);
	imshow(windowName, img_rgb);
	waitKey(0);
}

void convertToASCII(Mat& img, char** asciiArr, size_t w, size_t h) {
	Mat dst;
	string out, out_inverted;
	resize(img, dst, Size(w, h), 0, 0, INTER_AREA);		// resizes image to correspond ASCII array size

	for (int i=0;i<h;i++) {
		for (int j=0;j<w;j++) {
			int luminance = (int)(((float)dst.at<uchar>(i, j)/255)*12);  // calculates brigtness in scale from 0-12

			asciiArr[i][j] = "@$#*!=;:~-,."[luminance];					 // selects char based on luminance
			out.push_back(asciiArr[i][j]);								 // adds char to string
			out_inverted.push_back(".,-~:;!*#$@"[luminance]);			 // adds char to inverted color string
		};
		out.append("\n");
		out_inverted.append("\n");
	}

	cout << out << endl;			// prints non-inverted ASCII image
	cout << "Inverted:" << endl;
	cout << out_inverted;			// prints inverted ASCII image

	
}

void writeToText(char** asciiArr, size_t w, size_t h, string textFileName) {
	ofstream textFile;

	textFile.open(textFileName);
	if (!textFile.good()) return;
	
	for (int i = 0; i < h;i++) {
		for (int j = 0; j < w;j++) {
			textFile << asciiArr[i][j];	// appends ASCII characters to text file
		}
		textFile << "\n";
	}
	textFile.close();
}

int main(int argc, char* argv[])
{
	string startFileName = argv[1];		// image filename
	string textFileName = argv[2];		// text filename
	Mat img;							// image matrix
	size_t width = 100, height = 100;	// size to which the image should be scaled

	if (argc < 3)
	{
		cout << "Error, you must specify image and text file name! \n";
		return 1;
	}
	else if (argc > 5) {
		cout << "Error, you must specify image, text file name, width and height only! \n";
		return 1;
	}

	fileNameSanitization(startFileName, textFileName);	// removes backslash and inserts normal slash instead
	if (!loadInputImg(startFileName, img)) return -1;	// checks if the image can be loaded

	switch (argc) {										// calculates dimesions based on input
	case 4:
		width = (int)(strtol(argv[3], nullptr, 10));
		height = (int)((strtol(argv[3], nullptr, 10) * img.rows) / img.cols) * 0.5;
		break;
	case 5:
		width = (int)(strtol(argv[3], nullptr, 10));
		height = (int)(strtol(argv[4], nullptr, 10));
		break;
	}

	if (!sizeVerification(width, height)) return -1;	// checks if dimensions are correct

	char** asciiArr = new char* [height];				// creates a dynamic 2D char array to store ASCII characters
	for (int i = 0; i < height; i++)
		asciiArr[i] = new char[width];

	convertToASCII(img, asciiArr, width, height);		// converts image to ascii array and prints it out
	writeToText(asciiArr, width, height, textFileName); // writes ascii array to text file at specified location
	showInputImg(startFileName);						// shows starting image in a new window

	for (int i = 0; i < height; ++i)					// deletes dynamic 2D char array
		delete[] asciiArr[i];
	delete[] asciiArr;

	return 0;
}
