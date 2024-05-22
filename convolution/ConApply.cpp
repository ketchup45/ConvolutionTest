#include"main.h"
#include <opencv2/opencv.hpp>
using namespace cv;

void GetConv(const ImageData& imageori, const char* kernel, ImageData& imagenew);

void basicconv()
{
    system("cls"); // ��������
    cout << "���ڽ��о��Ӧ��" << endl;
    //256*256
    Mat image_ori = imread("demolena.jpg"); // ͼ��ĻҶ�ֵ����ڸ�ʽΪMat�ı���image��
    int row = image_ori.rows;
    int col = image_ori.cols;
    int imagesize = row * col;//ͼƬ��С
    //ԭͼƬ��imagedata
    ImageData ImgData0(row, col);
    //��ֵ
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            ImgData0.value[i * col + j] = image_ori.at<uchar>(i, j * 3);
    //�����
    const int kersize = 3*3;
    char kerneL1[kersize] = {  1, 1, 1, 1, 1, 1, 1, 1, 1 };
    char kerneL2[kersize] = { -1,-2,-1, 0, 0, 0, 1, 2, 1 };
    char kerneL3[kersize] = { -1, 0, 1,-2, 0, 2,-1, 0, 1 };
    char kerneL4[kersize] = { -1,-1,-1,-1, 9,-1,-1,-1,-1 };
    char kerneL5[kersize] = { -1,-1, 0,-1, 0, 1, 0, 1, 1 };
    char kerneL6[kersize] = {  1, 2, 1, 2, 4, 2, 1, 2, 1 };
    //��������ͬͼƬ������
    ImageData ImgData1(row, col);
    ImageData ImgData2(row, col);
    ImageData ImgData3(row, col);
    ImageData ImgData4(row, col);
    ImageData ImgData5(row, col);
    ImageData ImgData6(row, col);
    //�������
    GetConv(ImgData0, kerneL1, ImgData1);
    GetConv(ImgData0, kerneL2, ImgData2);
    GetConv(ImgData0, kerneL3, ImgData3);
    GetConv(ImgData0, kerneL4, ImgData4);
    GetConv(ImgData0, kerneL5, ImgData5);
    GetConv(ImgData0, kerneL6, ImgData6);
    //������ӦMat����
    Mat image1(row, col, CV_8UC1, ImgData1.value);
    Mat image2(row, col, CV_8UC1, ImgData2.value);
    Mat image3(row, col, CV_8UC1, ImgData3.value);
    Mat image4(row, col, CV_8UC1, ImgData4.value);
    Mat image5(row, col, CV_8UC1, ImgData5.value);
    Mat image6(row, col, CV_8UC1, ImgData6.value);
    //��ʾ��ͼƬ
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
    //�ȴ�����
    if (waitKey(0))
        destroyAllWindows();


    wait_for_enter();
}

//struct�ľ�������
void GetConv(const ImageData& imageori, const char* kernel, ImageData& imagenew)
{
    //��������������
    const int kersiz = 3; //����˱߳�
    const int padding = 1; //���0
    const int stride = 1; //�ƶ��Ĳ���
    const int dilation = 1; //��չ��

    //imagepad�������ԭͼ��
    ImageData imagepad((imageori.col + padding * 2), (imageori.col + padding * 2));
    //��ԭ�������Χ��һȦ0
    for (int i = 0; i < imagepad.row; i++)
        for (int j = 0; j < imagepad.col; j++) {
            if (i == 0 || j == 0 || i == imagepad.row - 1 || j == imagepad.col - 1)
                imagepad.value[i * imagepad.col + j] = 0;//���䲿�֣��ڱ�Ե
            else//���ಿ��
                imagepad.value[i * imagepad.col + j] = imageori.value[(i - 1) * imageori.col + (j - 1)];
        }

    int kersum = 0;//������ܺ�
    for (int i = 0; i < kersiz * kersiz; i++)
        kersum += kernel[i];
    if (kersum == 0)
        kersum = 1;//����Ϊ0

    //kernel�����
    //imagenew��ͼ��

    //�������о������
    for (int i1 = 0; i1 < imagenew.row; i1++)
        for (int j1 = 0; j1 < imagenew.col; j1++) {
            float t1 = 0;
            //���� kersiz*kersiz
            for (int i2 = 0; i2 < kersiz; i2++)
                for (int j2 = 0; j2 < kersiz; j2++)
                    t1 += int(imagepad.value[(i1 + i2) * imagepad.col + (j1 + j2)])
                    * int(kernel[i2 * kersiz + j2]);

            t1 /= kersum;
            unsigned char t2 = unsigned char(t1);
            if (t1 < 0)//���Ʒ�Χ��Ĩƽ
                t2 = 0;
            else if (t1 > 255)
                t2 = 255;

            imagenew.value[i1 * imagenew.col + j1] = t2; //��ֵ
        }
}

//����ֵ
unsigned char GetThreshold(Mat& img);
//OTSU��ֵ��
void basicOTSU()
{
    system("cls"); // ��������
    cout << "���ڽ���OSTU�㷨" << endl;

    Mat image_ori = imread("demolena.jpg"); // ͼ��ĻҶ�ֵ����ڸ�ʽΪMat�ı���image��
    int row = image_ori.rows;
    int col = image_ori.cols;

    Mat image_new(row, col, CV_8UC1);//��ֵ�����ͼƬ
    unsigned char threshold = GetThreshold(image_ori);//��ֵ

    //������ֵ�����ؽ��ж�ֵ��
    for (int i = 0; i < row; i++)//����
        for (int j = 0; j < col; j++) {
            if (image_ori.at<uchar>(i, j * 3) > threshold)
                image_new.at<uchar>(i, j) = unsigned char(255);
            else
                image_new.at<uchar>(i, j) = unsigned char(0);
        }         

    //��ʾͼƬ
    imshow("Image_ori", image_ori);
    moveWindow("Image_ori", 300, 100);
    imshow("Image_afterOSTU", image_new);
    moveWindow("Image_afterOSTU", 600, 100);
    if (waitKey(0))
        destroyAllWindows();

    wait_for_enter();
}

//����OSTU��ֵ
unsigned char GetThreshold(Mat& image)
{
    const int PIXEL_RANGE = 256;//�Ҷ�ֵ�仯�ķ�Χ

    int row = image.rows;
    int col = image.cols;
    int size = row * col;

    unsigned char threshold = 0;//��ֵ
    double best_variance = 0;//��󷽲�

    //��0-255�б�����ʹ����������ֵ
    for (int t = 0; t < PIXEL_RANGE; t++) {
        double Nf = 0;//ǰ���㣬С����ֵ�������ص�ĸ���
        double xftotal = 0;//ǰ��������ֵ�ĺ�
        double xbtotal = 0;//�󾰵�����ֵ�ĺ�

        for (int i = 0; i < row; i++) //��������ǰ�������
            for (int j = 0; j < col; j++) 
                if (image.at<uchar>(i, j * 3) < t) {
                    Nf += 1;//����+1
                    xftotal += image.at<uchar>(i, j * 3);
                }
                else
                    xbtotal += image.at<uchar>(i, j * 3);
        
        double Nb = size - Nf;//�󾰵�ĸ���
        double xfa = xftotal / Nf;//ǰ����ƽ���Ҷ�ֵ
        double xba = xbtotal / Nb;//�󾰵�ƽ���Ҷ�ֵ
        //���㷽��
        double variance = (Nb / size) * (Nf / size) * (xfa - xba) * (xfa - xba);

        if (variance > best_variance){ //�ҵ���󷽲�
            best_variance = variance;
            threshold = t;
        }

    }
    return threshold;
}

#include <stack>
//�ж��Ƿ����Ϊ����
void GetIfBkg(bool* IfBkg, Mat image_new)//, uchar CheckValue
{
    //��ʼ��
    for (int i = 0; i < image_new.rows * image_new.cols; i++)
        IfBkg[i] = 0;
    //�ж�
    stack<pair<int, int>> getblack;//�ж��Ƿ�Ϊ��ɫ��ջ
    getblack.push({ 0, 0 });

    while (!getblack.empty()) {
        int i = getblack.top().first;
        int j = getblack.top().second;
        getblack.pop();//��ջ
        //������ȱ������Ƿ�Ϊ��ͨ�ĺ�ɫ
        if (image_new.at<uchar>(i, j) == 0) {//�Ǻ�ɫ��
            IfBkg[i * image_new.cols + j] = 1;//Ϊ�汳��
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
//�����ڻ�
void OTSUblack(const char* imgname)
{
    Mat image_ori = imread(imgname); // ͼ��ĻҶ�ֵ����ڸ�ʽΪMat�ı���image��
    int row = image_ori.rows;
    int col = image_ori.cols;
    
    Mat image_new(row, col, CV_8UC1);//��ֵ�����ͼƬ
    unsigned char threshold = GetThreshold(image_ori);//��ֵ

    //������ֵ�����ؽ��ж�ֵ��
    for (int i = 0; i < row; i++)//����
        for (int j = 0; j < col; j++) {
            if (image_ori.at<uchar>(i, j * 3) < threshold)//������ֵ����
                image_new.at<uchar>(i, j) = unsigned char(0);
            else //ǰ�����ֲ���
                image_new.at<uchar>(i, j) = image_ori.at<uchar>(i, j);
        }
    //�������ڵ�
    bool* IfBkg = new(nothrow) bool[row * col];//��ǰ����Ƿ�Ϊ�汳��
    //1--��  0--����
    if (IfBkg == NULL) {
        cout << "error";
        return;
    }

    GetIfBkg(IfBkg, image_new);

    for (int i = 0; i < row; i++)//����
        for (int j = 0; j < col; j++) 
            if (image_new.at<uchar>(i, j) == 0) { //Ϊ��ɫ
                if (IfBkg[i * col + j] == 0)//�����汳�����ָ�ԭ������ɫ
                    image_new.at<uchar>(i, j) = image_ori.at<uchar>(i, j);
            }

    //��ʾͼƬ
    imshow("Image_ori", image_ori);
    //moveWindow("Image_ori", 300, 100);
    imshow("Image_new1", image_new);
    //moveWindow("Image_new1", 600, 100);
}

void moreOSTU()
{
    system("cls"); // ��������
    cout << "���ڽ��б����ڻ�" << endl;

    OTSUblack("ship.jpg");
    
    if (waitKey(0))
        destroyAllWindows();
    wait_for_enter();
}