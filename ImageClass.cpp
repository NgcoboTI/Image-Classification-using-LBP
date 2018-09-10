//Image Classifiication using LDP method from a given data set.

#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

Mat LDP(Mat a)
{
	int i, d, j, k, l, p, r, s, rws, temp, clms, sigF, ldp;
	int m[8], temp0[8];
	Mat LDP;
	r = 0;

	rws = a.rows;
	clms = a.cols;
	//Kirsch Masks
	Mat m1 = (Mat_<double>(3, 3) << -3, -3, 5, -3, 0, 5, -3, -3, 5);		//East
	Mat m2 = (Mat_<double>(3, 3) << -3, 5, 5, -3, 0, 5, -3, -3, -3);		//North-East
	Mat m3 = (Mat_<double>(3, 3) << 5, 5, 5, -3, 0, -3, -3, -3, -3);		//North
	Mat m4 = (Mat_<double>(3, 3) << 5, 5, -3, 5, 0, -3, -3, -3, -3);		//North-West
	Mat m5 = (Mat_<double>(3, 3) << 5, -3, -3, 5, 0, -3, 5, -3, -3);		//West
	Mat m6 = (Mat_<double>(3, 3) << -3, -3, -3, 5, 0, -3, 5, 5, -3);		//South-West
	Mat m7 = (Mat_<double>(3, 3) << -3, -3, -3, -1, 5, -1, 5, 5, 5);		//South
	Mat m8 = (Mat_<double>(3, 3) << -3, -3, -3, -1, 5, -1, -3, 5, 5);		//South-East
	Mat Kirsch[8] = { m1, m2, m3, m4, m5, m6, m7, m8 };

	//LDP Calculation
	for (i = 2; i <= rws - 1; i++)
	{
		for (j = 2; j <= clms - 1; j++)
		{
			for (p = 0; p <= 7; p++)
			{
				temp = 0;
				ldp = 0;
				for (k = -1; k <= 1; k++)
				{
					for (l = 1; l <= 1; l++)
					{
						temp = temp + Kirsch[p].at<uchar>(k + 1, l + 1) * a.at<uchar>(i + k, j + l);		//Applying Masks
					}
				}
				m[p] = temp;
			}
			for (int h = 0; h <= 7; h++)
			{
				temp0[h] = m[h];
			}
			sort(temp0[8], 8);
			sigF = temp0[2];			//Using N = 3 for significant figure
			for (d = 0; d <= 7; d++)		//Ldp
			{
				int temp1 = m[d] - sigF;
				if (temp1 >= 0)
				{
					s = 1;
				}
				else if (temp1 < 0)
				{
					s = 0;
				}
				ldp = ldp + s * (2 ^ (d));
			}
			LDP.at<uchar>(i, j) = ldp;
		}
	}
	return LDP;
}

int main()
{
	Mat image;		         // input image
	Mat imageGrayScale;       // grayscale of input image

							  //Reading in the input images
	image = imread("image.png", CV_LOAD_IMAGE_COLOR);

	//Check if image was loaded in correctly
	if (!image.data)
	{
		cout << "No image detected";
		return -1;
	}

	//Obtain Grayscale image
	cvtColor(image, imageGrayScale, CV_BGR2GRAY);       // convert to grayscale
														//Obtain LDP
	LDP(imageGrayScale);

	waitKey(0);
	return 0;

}