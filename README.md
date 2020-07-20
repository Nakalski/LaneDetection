
# Lane Detection
A simple lane detector  using C++ and OpenCV that identifies the lanes and track them. Be Aware that everything here is in development


**Initial Goal**
Since i already knew something about OpenCV in Python, I decided to try to learn the same library but in C++, thus this small project was born. It detect lanes and track the point’s.

**Algorithm**
This subsection will explain the pipeline of the Algorithm step by step.

- Block Diagram

The proposed algorithm follows a straight forward pipeline with several steps as shown in the following block diagram. It will iterate through every frame of the video and do the following steps in each of them:

![Block Diagram](https://github.com/Nakalski/LaneDetection/blob/master/images/Diagrama.png)

- Input Frame

 The input video resolution is 1280x720. Then for preprocessing is applied a Gaussian Pyramid which reduces the resolution in both axis in half and applies a Gaussian Filter for smoothing the image.
 
![Input Frame](https://github.com/Nakalski/LaneDetection/blob/master/images/input_frame.png)

- Perspective Transform
 
 The perspective transform is used to convert the sideways view of the frame into a top one. The algorithm does this using a transformation matrix based on four points. For this type of application this transformation is also called Bird's Eye View.
 
![Perspective Transform](https://github.com/Nakalski/LaneDetection/blob/master/images/2.png)

- Otsu Thresholding
 
 Otsu Thresholding is a image processing technique which is used to perform image thresholding. In the simplest form, the algorithm returns a single intensity threshold that separate pixels into two classes, foreground and background. This threshold is determined by minimizing intra-class intensity variance, or equivalently, by maximizing inter-class variance. 
 
![Otsu](https://github.com/Nakalski/LaneDetection/blob/master/images/otsu2.png)

- Canny Edge Detection

![Canny](https://github.com/Nakalski/LaneDetection/blob/master/images/canny.png)

- Inverse Perspective Transform
 
 (PERSP. TRANSF. EXPLANATION HERE).
 
![Inverse Transform](https://github.com/Nakalski/LaneDetection/blob/master/images/1.png)

- Output Frame
 
  The output frame is simply an addition of two images, the detected lanes and the input frame.
  
![Output Frame](https://github.com/Nakalski/LaneDetection/blob/master/images/3.png)
