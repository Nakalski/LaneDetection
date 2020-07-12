#include <iostream>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define X_warped 200
#define Y_warped 100
RNG rng(12345);
int main(int argc, char **argv)
{

    const int lowThreshold = 20;
    const int ratio = 3;

    cv::namedWindow("Video", cv::WINDOW_AUTOSIZE);
    cv::VideoCapture cap;
    std::string path = "2.avi";
    cap.open(path);
    cv::Point2f obj_pts[4], img_pts[4];
    img_pts[0].x = 150;
    img_pts[0].y = 280; //B
    img_pts[1].x = 50;
    img_pts[1].y = 340; //G
    img_pts[2].x = 530;
    img_pts[2].y = 280; //R
    img_pts[3].x = 630;
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
    invert(matrix, inverted_matrix);
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
        cv::circle(reduced_res, img_pts[3], 1, cv::Scalar(0, 255, 255), 3); */

        cv::warpPerspective(reduced_res, warped, matrix, cv::Size(X_warped, Y_warped));
        cv::cvtColor(warped, gray, cv::COLOR_RGB2GRAY);

        /////////////////////////////////////////////////////////////////////////////////
        /// CANNY FOR NOISE REMOVAL
        cv::Canny(warped, canny_test, lowThreshold, lowThreshold * ratio, 3, true);
        cv::dilate(canny_test, mask, Mat(), Point(-1, -1), 4, 1, 1);
        //////////////////////////////////////////////////////////////////////////////////
        /// OTSU 
        cv::threshold(gray, th, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
        cv::bitwise_and(th, mask, teste); /// MAS
        cv::HoughLinesP(teste, lines, 1, CV_PI / 180, 30, 15, 10);
        cv::Mat drawed_lines = cv::Mat::zeros(warped.size(), warped.type()), warped_lines = cv::Mat::zeros(reduced_res.size(), reduced_res.type());
        for (size_t i = 0; i < lines.size(); i++)
        {
            Vec4i l = lines[i];
            line(drawed_lines, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, cv::LINE_AA);
        }
        cv::warpPerspective(drawed_lines, warped_lines, matrix, reduced_res.size(), WARP_INVERSE_MAP, BORDER_TRANSPARENT);
        cv::addWeighted(reduced_res, 0.7, warped_lines, 0.3, 0, sum);
        ////////////////////////////////////////////////////////////////////////////////

        cv::imshow("Th", th);
        cv::imshow("Lines", warped_lines);
        cv::imshow("sum", sum);
        cv::imshow("WarpedPerspective", gray);
        cv::imshow("Video", reduced_res);
        cv::imshow("mask", teste);
        if (cv::waitKey(33) >= 0)
            break;
    }
    return 0;
}