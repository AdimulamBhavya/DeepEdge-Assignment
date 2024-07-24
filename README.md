# DeepEdge-Assignment

We'll use OpenCV's cv::resize function to resize the image using three different interpolation methods: INTER_NEAREST, INTER_LINEAR, and INTER_CUBIC.

**pip install opencv-python**  //by using this command install opencv.

Then for resizing the image execute the file called **"resize.py"**.

To perform our own image resizing. This function will replace OpenCV's cv::resize and we will compare its correctness and performance.
Compile and run **"myresize.py"** to compare the performance and correctness of your implementation. 
You will need to link against OpenCV libraries when compiling. That is : g++ -o resize my_resize.cpp `pkg-config --cflags --libs opencv4`
