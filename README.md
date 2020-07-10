
# Lane Detection
A simple lane detector  using C++ and OpenCV that identifies the lanes and track them. Be Aware that everything here is in development


**Initial Goal**
Since i already knew something about OpenCV in Python, I decided to try to learn the same library but in C++, thus this small project was born. It detect lanes and track the point’s movement to determine if the vehicle is turning or changing slope.

**Algorithm**
This subsection will explain the pipeline of the Algorithm step by step.

- Block Diagram

The proposed algorithm follows a straight forward pipeline with several steps as shown in the following block diagram. It will iterate through every frame of the video and do the following steps in each of them:

```mermaid 
graph LR
A(( )) --> B[Input Frame]
B --> D[Gaussian Pyramid]
D --> C[Set a Region of Interest]
C --> E[Perpective Transformation]
E --> F[Otsu Threshold]
F --> G[Hough Line Detection]
G --> H[Draw Lanes]
H --> I[Inverse Persp. Transf.]
I --> J(( ))
B --> J
J --> K[Combined Images]

```
