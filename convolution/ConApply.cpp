#include"main.h"
#include <opencv2/opencv.hpp>
using namespace cv;

void GetConv(const ImageData& imageori, const char* kernel, ImageData& imagenew);

void basicconv()
{
    system("cls"); // 清屏函数
    cout << "正在进行卷积应用" << endl;
    //256*256
    Mat image_ori = imread("demolena.jpg"); // 图像的灰度值存放在格式为Mat的变量image中
    int row = image_ori.rows;
    int col = image_ori.cols;
    int imagesize = row * col;//图片大小
    //原图片的imagedata
    ImageData ImgData0(row, col);
    //赋值
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            ImgData0.value[i * col + j] = image_ori.at<uchar>(i, j * 3);
    //卷积核
    const int kersize = 3*3;
    char kerneL1[kersize] = {  1, 1, 1, 1, 1, 1, 1, 1, 1 };
    char kerneL2[kersize] = { -1,-2,-1, 0, 0, 0, 1, 2, 1 };
    char kerneL3[kersize] = { -1, 0, 1,-2, 0, 2,-1, 0, 1 };
    char kerneL4[kersize] = { -1,-1,-1,-1, 9,-1,-1,-1,-1 };
    char kerneL5[kersize] = { -1,-1, 0,-1, 0, 1, 0, 1, 1 };
    char kerneL6[kersize] = {  1, 2, 1, 2, 4, 2, 1, 2, 1 };
    //创建代表不同图片的数据
    ImageData ImgData1(row, col);
    ImageData ImgData2(row, col);
    ImageData ImgData3(row, col);
    ImageData ImgData4(row, col);
    ImageData ImgData5(row, col);
    ImageData ImgData6(row, col);
    //卷积运算
    GetConv(ImgData0, kerneL1, ImgData1);
    GetConv(ImgData0, kerneL2, ImgData2);
    GetConv(ImgData0, kerneL3, ImgData3);
    GetConv(ImgData0, kerneL4, ImgData4);
    GetConv(ImgData0, kerneL5, ImgData5);
    GetConv(ImgData0, kerneL6, ImgData6);
    //创建对应Mat数据
    Mat image1(row, col, CV_8UC1, ImgData1.value);
    Mat image2(row, col, CV_8UC1, ImgData2.value);
    Mat image3(row, col, CV_8UC1, ImgData3.value);
    Mat image4(row, col, CV_8UC1, ImgData4.value);
    Mat image5(row, col, CV_8UC1, ImgData5.value);
    Mat image6(row, col, CV_8UC1, ImgData6.value);
    //显示各图片
    imshow("Image-original", image_ori);
    moveWindow("Image-original", 0, 150);
    imshow("Image1", image1);
    moveWindow("Image1", 300, 0);
    imshow("Image2", image2);
    moveWindow("Image2", 600, 0);
    imshow("Image3", image3);
    moveWindow("Image3", 900, 0);
    imshow("Image4", image4);
    moveWindow("Image4", 300, 300);
    imshow("Image5", image5);
    moveWindow("Image5", 600, 300);
    imshow("Image6", image6);
    moveWindow("Image6", 900, 300);
    //等待输入
    if (waitKey(0))
        destroyAllWindows();


    wait_for_enter();
}

//struct的矩阵运算
void GetConv(const ImageData& imageori, const char* kernel, ImageData& imagenew)
{
    //卷积运算相关数据
    const int kersiz = 3; //卷积核边长
    const int padding = 1; //填充0
    const int stride = 1; //移动的步长
    const int dilation = 1; //扩展率

    //imagepad：填充后的原图像
    ImageData imagepad((imageori.col + padding * 2), (imageori.col + padding * 2));
    //在原矩阵的外围补一圈0
    for (int i = 0; i < imagepad.row; i++)
        for (int j = 0; j < imagepad.col; j++) {
            if (i == 0 || j == 0 || i == imagepad.row - 1 || j == imagepad.col - 1)
                imagepad.value[i * imagepad.col + j] = 0;//扩充部分，在边缘
            else//其余部分
                imagepad.value[i * imagepad.col + j] = imageori.value[(i - 1) * imageori.col + (j - 1)];
        }

    int kersum = 0;//卷积核总和
    for (int i = 0; i < kersiz * kersiz; i++)
        kersum += kernel[i];
    if (kersum == 0)
        kersum = 1;//不能为0

    //kernel卷积核
    //imagenew新图像

    //遍历进行卷积运算
    for (int i1 = 0; i1 < imagenew.row; i1++)
        for (int j1 = 0; j1 < imagenew.col; j1++) {
            float t1 = 0;
            //遍历 kersiz*kersiz
            for (int i2 = 0; i2 < kersiz; i2++)
                for (int j2 = 0; j2 < kersiz; j2++)
                    t1 += int(imagepad.value[(i1 + i2) * imagepad.col + (j1 + j2)])
                    * int(kernel[i2 * kersiz + j2]);

            t1 /= kersum;
            unsigned char t2 = unsigned char(t1);
            if (t1 < 0)//限制范围，抹平
                t2 = 0;
            else if (t1 > 255)
                t2 = 255;

            imagenew.value[i1 * imagenew.col + j1] = t2; //赋值
        }
}

//求阈值
unsigned char GetThreshold(Mat& img);
//OTSU二值化
void basicOTSU()
{
    system("cls"); // 清屏函数
    cout << "正在进行OSTU算法" << endl;

    Mat image_ori = imread("demolena.jpg"); // 图像的灰度值存放在格式为Mat的变量image中
    int row = image_ori.rows;
    int col = image_ori.cols;

    Mat image_new(row, col, CV_8UC1);//二值化后的图片
    unsigned char threshold = GetThreshold(image_ori);//阈值

    //根据阈值对像素进行二值化
    for (int i = 0; i < row; i++)//遍历
        for (int j = 0; j < col; j++) {
            if (image_ori.at<uchar>(i, j * 3) > threshold)
                image_new.at<uchar>(i, j) = unsigned char(255);
            else
                image_new.at<uchar>(i, j) = unsigned char(0);
        }         

    //显示图片
    imshow("Image_ori", image_ori);
    moveWindow("Image_ori", 300, 100);
    imshow("Image_afterOSTU", image_new);
    moveWindow("Image_afterOSTU", 600, 100);
    if (waitKey(0))
        destroyAllWindows();

    wait_for_enter();
}

//计算OSTU阈值
unsigned char GetThreshold(Mat& image)
{
    const int PIXEL_RANGE = 256;//灰度值变化的范围

    int row = image.rows;
    int col = image.cols;
    int size = row * col;

    unsigned char threshold = 0;//阈值
    double best_variance = 0;//最大方差

    //在0-255中遍历求使方差最大的阈值
    for (int t = 0; t < PIXEL_RANGE; t++) {
        double Nf = 0;//前景点，小于阈值，的像素点的个数
        double xftotal = 0;//前景点像素值的和
        double xbtotal = 0;//后景点像素值的和

        for (int i = 0; i < row; i++) //遍历，求前景点个数
            for (int j = 0; j < col; j++) 
                if (image.at<uchar>(i, j * 3) < t) {
                    Nf += 1;//计数+1
                    xftotal += image.at<uchar>(i, j * 3);
                }
                else
                    xbtotal += image.at<uchar>(i, j * 3);
        
        double Nb = size - Nf;//后景点的个数
        double xfa = xftotal / Nf;//前景点平均灰度值
        double xba = xbtotal / Nb;//后景点平均灰度值
        //计算方差
        double variance = (Nb / size) * (Nf / size) * (xfa - xba) * (xfa - xba);

        if (variance > best_variance){ //找到最大方差
            best_variance = variance;
            threshold = t;
        }

    }
    return threshold;
}

#include <stack>
//判断是否真的为背景
void GetIfBkg(bool* IfBkg, Mat image_new)//, uchar CheckValue
{
    //初始化
    for (int i = 0; i < image_new.rows * image_new.cols; i++)
        IfBkg[i] = 0;
    //判断
    stack<pair<int, int>> getblack;//判断是否为黑色的栈
    getblack.push({ 0, 0 });

    while (!getblack.empty()) {
        int i = getblack.top().first;
        int j = getblack.top().second;
        getblack.pop();//出栈
        //深度优先遍历，是否为连通的黑色
        if (image_new.at<uchar>(i, j) == 0) {//是黑色的
            IfBkg[i * image_new.cols + j] = 1;//为真背景
            if (i > 0 && IfBkg[(i - 1) * image_new.cols + j] == 0)
                getblack.push({ i - 1, j });

            if (i < image_new.rows - 1 && IfBkg[(i + 1) * image_new.cols + j] == 0)
                getblack.push({ i + 1, j });

            if (j > 0 && IfBkg[i * image_new.cols + j - 1] == 0)
                getblack.push({ i, j - 1 });

            if (j < image_new.cols - 1 && IfBkg[i * image_new.cols + j + 1] == 0)
                getblack.push({ i, j + 1});
        }
    }
}
//背景黑化
void OTSUblack(const char* imgname)
{
    Mat image_ori = imread(imgname); // 图像的灰度值存放在格式为Mat的变量image中
    int row = image_ori.rows;
    int col = image_ori.cols;
    
    Mat image_new(row, col, CV_8UC1);//二值化后的图片
    unsigned char threshold = GetThreshold(image_ori);//阈值

    //根据阈值对像素进行二值化
    for (int i = 0; i < row; i++)//遍历
        for (int j = 0; j < col; j++) {
            if (image_ori.at<uchar>(i, j * 3) < threshold)//大于阈值，后景
                image_new.at<uchar>(i, j) = unsigned char(0);
            else //前景保持不变
                image_new.at<uchar>(i, j) = image_ori.at<uchar>(i, j);
        }
    //消除误差黑点
    bool* IfBkg = new(nothrow) bool[row * col];//当前结点是否为真背景
    //1--是  0--不是
    if (IfBkg == NULL) {
        cout << "error";
        return;
    }

    GetIfBkg(IfBkg, image_new);

    for (int i = 0; i < row; i++)//遍历
        for (int j = 0; j < col; j++) 
            if (image_new.at<uchar>(i, j) == 0) { //为黑色
                if (IfBkg[i * col + j] == 0)//不是真背景，恢复原来的颜色
                    image_new.at<uchar>(i, j) = image_ori.at<uchar>(i, j);
            }

    //显示图片
    imshow("Image_ori", image_ori);
    //moveWindow("Image_ori", 300, 100);
    imshow("Image_new1", image_new);
    //moveWindow("Image_new1", 600, 100);
}

void moreOSTU()
{
    system("cls"); // 清屏函数
    cout << "正在进行背景黑化" << endl;

    OTSUblack("ship.jpg");
    
    if (waitKey(0))
        destroyAllWindows();
    wait_for_enter();
}