
# Lane Detection
A simple lane detector  using C++ and OpenCV that identifies the lanes and track them. Be Aware that everything here is in development


**Initial Goal**
Since i already knew something about OpenCV in Python, I decided to try to learn the same library but in C++, thus this small project was born. It detect lanes and track the point’s movement to determine if the vehicle is turning or changing slope.

**Algorithm**
This subsection will explain the pipeline of the Algorithm step by step.

- Block Diagram

The proposed algorithm follows a straight forward pipeline with several steps as shown in the following block diagram. It will iterate through every frame of the video and do the following steps in each of them:

![Block Diagram](https://github.com/Nakalski/LaneDetection/blob/master/images/Diagrama.png)

- Input Frame

 The input video resolution is 1280x720. Then for preprocessing is applied a Gaussian Pyramid which reduces the resolution in both axis in half and applies a Gaussian Filter for smoothing the image.
 
![Input Frame](https://github.com/Nakalski/LaneDetection/blob/master/images/input_frame.png)

- Perspective Transform
 
![Perspective Transform](https://github.com/Nakalski/LaneDetection/blob/master/images/transform.png)

- Otsu Thresholding
 
 Otsu Thresholding is a image processing technique which is used to perform image thresholding. In the simplest form, the algorithm returns a single intensity threshold that separate pixels into two classes, foreground and background. This threshold is determined by minimizing intra-class intensity variance, or equivalently, by maximizing inter-class variance. 
 
![Otsu](https://github.com/Nakalski/LaneDetection/blob/master/images/otsu.png)

- Inverse Perspective Transform
 
![Inverse Transform](https://github.com/Nakalski/LaneDetection/blob/master/images/inverse_transform.png)

- Output Frame
 
![Output Frame](https://github.com/Nakalski/LaneDetection/blob/master/images/output_frame.png)
