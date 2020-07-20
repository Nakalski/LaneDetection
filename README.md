
# Lane Detection
A simple lane detector  using C++ and OpenCV that identifies the lanes and track them. Be Aware that everything here is in development


### Initial Goal
Since i already knew something about OpenCV in Python, I decided to try to learn the same library but in C++, thus this small project was born. It detect lanes and track the point’s.

### Algorithm
This subsection will explain the pipeline of the Algorithm step by step. Some of the intermidiate images for example purposes are in [Here](https://github.com/Nakalski/LaneDetection/blob/master/images/)

- Block Diagram

The proposed algorithm follows a straight forward pipeline with several steps as shown in the following block diagram. It will iterate through every frame of the video and do the following steps in each of them:

![Block Diagram](https://github.com/Nakalski/LaneDetection/blob/master/images/Diagrama.png)

- Input Frame

 The input video resolution is 1280x720. Then for preprocessing is applied a Gaussian Pyramid which reduces the resolution in both axis in half and applies a Gaussian Filter for smoothing the image.
 
![Input Frame](https://github.com/Nakalski/LaneDetection/blob/master/images/input_frame.png)

- Perspective Transform
 
 The perspective transform is used to convert the sideways view of the frame into a top one. The algorithm does this using a transformation matrix based on four points. For this type of application this transformation is also called Bird's Eye View.
 

- Otsu Thresholding
 
 Otsu Thresholding is a image processing technique which is used to perform image thresholding. In the simplest form, the algorithm returns a single intensity threshold that separate pixels into two classes, foreground and background. This threshold is determined by minimizing intra-class intensity variance, or equivalently, by maximizing inter-class variance. 
 

- Canny Edge Detection

Canny edge detection is a multi-step algorithm that can detect edges with noise supression at the same time. If you wanna know more about the step by step of the algorith you can check on this link: [CannyWiki](https://en.wikipedia.org/wiki/Canny_edge_detector).

- Morphology Operations
 
 On this step the output of the Canny Edge Detector goes through some morphology operations to remove unwanted edges and to highlight the ones that matter.
 
- Inverse Perspective Transform
 
 Simply the inverse operation of the first perspective tranform.
 
- Output Frame
 
  The output frame is simply an addition of two images, the detected lanes and the input frame.
  
![Output Frame](https://github.com/Nakalski/LaneDetection/blob/master/images/3.png)
