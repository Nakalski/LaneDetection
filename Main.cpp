#include <iostream>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    cv::namedWindow("Video", cv::WINDOW_AUTOSIZE);
    cv::VideoCapture cap;
    std::string path = "TestVideo.avi";
    cap.open(path);
    cv::Point2f obj_pts[4], img_pts[4];
    img_pts[0].x = 210;    img_pts[0].y = 295; //B
    img_pts[1].x = 100;    img_pts[1].y = 340; //G
    img_pts[2].x = 460;    img_pts[2].y = 295; //R
    img_pts[3].x = 580;    img_pts[3].y = 340; //Y
    obj_pts[0].x = 0;    obj_pts[0].y = 0; 
    obj_pts[1].x = 0;    obj_pts[1].y = 100; 
    obj_pts[2].x = 200;  obj_pts[2].y = 0; 
    obj_pts[3].x = 200;  obj_pts[3].y = 100; 
    int n;
    cv::Mat matrix, warped, gray, th, sum, inverted_matrix, frame, reduced_res;
    matrix = cv::getPerspectiveTransform(img_pts, obj_pts);
    invert(matrix, inverted_matrix);
    for (;;)
    {
        cap >> frame;
        if (frame.empty())
            break;
        std::vector<cv::Vec4i> lines;
        cv::pyrDown(frame, reduced_res);
        /*
        cv::circle(reduced_res, img_pts[0], 1, cv::Scalar(255, 0, 0), 3);
        cv::circle(reduced_res, img_pts[1], 1, cv::Scalar(0, 255, 0), 3);      DRAWS THE CIRCLES THAT 
        cv::circle(reduced_res, img_pts[2], 1, cv::Scalar(0, 0, 255), 3);      MARKS THE EDGES OF THE
        cv::circle(reduced_res, img_pts[3], 1, cv::Scalar(0, 255, 255), 3);    PERPECTIVE TRANSFORMATION    */ 
        cv::warpPerspective(reduced_res, warped, matrix, cv::Size(200, 100));
        cv::cvtColor(warped, gray, cv::COLOR_RGB2GRAY);
        cv::threshold(gray, th, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
        cv::HoughLinesP(th, lines, 1, CV_PI / 180, 30, 15, 10);
        cv::Mat drawed_lines = cv::Mat::zeros(warped.size(), warped.type()), warped_lines = cv::Mat::zeros(reduced_res.size(), reduced_res.type());
        for (size_t i = 0; i < lines.size(); i++)
        {
            Vec4i l = lines[i];
            line(drawed_lines, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, cv::LINE_AA);
        }
        cv::warpPerspective(drawed_lines, warped_lines, matrix, reduced_res.size(), WARP_INVERSE_MAP, BORDER_TRANSPARENT);
        cv::addWeighted(reduced_res, 0.7, warped_lines, 0.3, 0, sum);
        cv::imshow("Th", th);
        cv::imshow("Lines", warped_lines);
        cv::imshow("sum", sum);
        cv::imshow("WarpedPerspective", warped);
        cv::imshow("Video", reduced_res);
        if (cv::waitKey(33) >= 0)
            break;
    }
    return 0;
}