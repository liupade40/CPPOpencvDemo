#include<opencv2\opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
    CascadeClassifier face_detector;
    face_detector.load("");
    if (face_detector.empty())
    {
        cerr << "load detector failed" << endl;
        return;
    }

    return 0;
}