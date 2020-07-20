#include <iostream>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define X_warped 320
#define Y_warped 240

vector<Point2f> slidingWindow(Mat image, Rect window)
{
    vector<Point2f> points;
    const Size imgSize = image.size();
    bool shouldBreak = false;
    while (true)
    {
        float currentX = window.x + window.width * 0.5f;
        Mat roi = image(window);
        vector<Point2f> locations;
        cv::findNonZero(roi, locations);
        float avgX = 0.0f;

        for (int i = 0; i < locations.size(); ++i)
        {
            float x = locations[i].x;
            avgX += window.x + x;
        }

        avgX = locations.empty() ? currentX : avgX / locations.size();
        Point point(avgX, window.y + window.height * 0.5f);
        points.push_back(point);
        window.y -= window.height;
        if (window.y < 0)
        {
            window.y = 0;
            shouldBreak = true;
        }
        window.x += (point.x - currentX);
        if (window.x < 0)
            window.x = 0;
        if (window.x + window.width >= imgSize.width)
            window.x = imgSize.width - window.width - 1;
        if (shouldBreak)
            break;
    }
    return points;
}

int main(int argc, char **argv)
{
    const int lowThreshold = 20;
    const int ratio = 3;
    cv::VideoCapture cap;
    //std::string path = std::string(argv[1]);
    std::string path = "Videos/TestVideo.avi";
    cap.open(path);
    cv::Point2f obj_pts[4], img_pts[4];
    /*img_pts[0].x = 150;
    img_pts[0].y = 280; //B
    img_pts[1].x = 50;
    img_pts[1].y = 340; //G
    img_pts[2].x = 530;
    img_pts[2].y = 280; //R
    img_pts[3].x = 630;
    img_pts[3].y = 340; //Y*/
    img_pts[0].x = 260;
    img_pts[0].y = 280; //B
    img_pts[1].x = 120;
    img_pts[1].y = 350; //G
    img_pts[2].x = 380;
    img_pts[2].y = 280; //R
    img_pts[3].x = 480;
    img_pts[3].y = 340; //Y
    obj_pts[0].x = 0;
    obj_pts[0].y = 0;
    obj_pts[1].x = 0;
    obj_pts[1].y = Y_warped;
    obj_pts[2].x = X_warped;
    obj_pts[2].y = 0;
    obj_pts[3].x = X_warped;
    obj_pts[3].y = Y_warped;
    int n;
    cv::Mat matrix, warped, gray, th, sum, inverted_matrix, frame, reduced_res, canny_test, mask, masked_drawed_lines, teste;
    matrix = cv::getPerspectiveTransform(img_pts, obj_pts);
    Mat invertedPerspectiveMatrix;
    invert(matrix, invertedPerspectiveMatrix);
    for (;;)
    {
        cap >> frame;
        if (frame.empty())
            break;
        std::vector<cv::Vec4i> lines;
        cv::pyrDown(frame, reduced_res);

        /*cv::circle(reduced_res, img_pts[0], 1, cv::Scalar(255, 0, 0), 3);
        cv::circle(reduced_res, img_pts[1], 1, cv::Scalar(0, 255, 0), 3);
        cv::circle(reduced_res, img_pts[2], 1, cv::Scalar(0, 0, 255), 3);
        cv::circle(reduced_res, img_pts[3], 1, cv::Scalar(0, 255, 255), 3);*/

        cv::warpPerspective(reduced_res, warped, matrix, cv::Size(X_warped, Y_warped));
        cv::cvtColor(warped, gray, cv::COLOR_RGB2GRAY);
        cv::Canny(warped, canny_test, lowThreshold, lowThreshold * ratio, 3, true);
        cv::dilate(canny_test, mask, Mat(), Point(-1, -1), 5, 1, 1);
        cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(10, 10)));
        cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(10, 10)));
        cv::morphologyEx(mask, mask, cv::MORPH_CLOSE, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(10, 10)));
        cv::threshold(gray, th, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
        cv::bitwise_and(th, mask, teste); 
        vector<Point2f> pts = slidingWindow(teste, Rect(0, Y_warped-10, X_warped/4, 10));
        vector<Point2f> ptsE, ptsD;
        cv::perspectiveTransform(pts, ptsE, invertedPerspectiveMatrix);
        //ptsE=pts;
        vector<Point> allPts;
        vector<Point2f> outPts;
        cv::perspectiveTransform(pts, outPts, invertedPerspectiveMatrix);
        for (int i = 0; i < outPts.size() - 1; ++i)
        {
            cv::line(reduced_res, outPts[i], outPts[i + 1], Scalar(255, 0, 0), 3);
            allPts.push_back(Point(outPts[i].x, outPts[i].y));
        }
        allPts.push_back(Point(outPts[outPts.size() - 1].x, outPts[outPts.size() - 1].y));
        Mat out;
        cv::cvtColor(teste, out, COLOR_GRAY2BGR);
        for (int i = 0; i < pts.size() - 1; ++i)
            line(out, pts[i], pts[i + 1], Scalar(255, 0, 0));
        pts = slidingWindow(teste, Rect(X_warped/2, Y_warped-10, X_warped/2, 10));
        //ptsD=pts;
        cv::perspectiveTransform(pts, ptsD, invertedPerspectiveMatrix);
        cv::perspectiveTransform(pts, outPts, invertedPerspectiveMatrix);
        for (int i = 0; i < outPts.size() - 1; ++i)
        {
            cv::line(reduced_res, outPts[i], outPts[i + 1], Scalar(0, 0, 255), 3);
            allPts.push_back(Point(outPts[outPts.size() - i - 1].x, outPts[outPts.size() - i - 1].y));
        }
        allPts.push_back(Point(outPts[0].x - (outPts.size() - 1), outPts[0].y));
        for (int i = 0; i < pts.size() - 1; ++i)
        {
            line(out, pts[i], pts[i + 1], Scalar(0, 0, 255));
            cv::Point2f p1((ptsD[i].x+ptsE[i].x)/2,(ptsD[i].y+ptsE[i].y)/2 ), p2((ptsD[i+1].x+ptsE[i+1].x)/2,(ptsD[i+1].y+ptsE[i+1].y)/2 );
            line(out,p1, p2 , Scalar(0, 255, 255), 5);
        }
        vector<vector<Point>> arr;
        arr.push_back(allPts);
        Mat overlay = Mat::zeros(reduced_res.size(), reduced_res.type());
        cv::fillPoly(overlay, arr, Scalar(30, 30, 30));
        for (int i = 0; i < pts.size() - 1; ++i)
        {
            cv::Point2f p1((ptsD[i].x+ptsE[i].x)/2,(ptsD[i].y+ptsE[i].y)/2 ), p2((ptsD[i+1].x+ptsE[i+1].x)/2,(ptsD[i+1].y+ptsE[i+1].y)/2 );
            line(overlay,p1, p2 , Scalar(0, 255, 255), 5);
        }
        cv::addWeighted(reduced_res, 1, overlay, 0.5, 0, reduced_res); //Overlay it
        cv::imshow("Preprocess", out);
        cv::imshow("src", reduced_res);
        cv::imshow("WarpedPerspective", gray);
        if (cv::waitKey(33) >= 0)
            break;
    }
    return 0;
}