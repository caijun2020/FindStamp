#include <QCoreApplication>
#include <QTextCodec>
#include <QTime>
#include <QDebug>
#include <windows.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

bool findStamp(QString fileName = "stamp005.jpg", int checkThres = 500);
void usage();
void getSysLanguage();

//#define USE_SYS_QTEXTCODEC


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Add the plugins path, so the picture will be displayed normally
    // SQL driver and TextCodec will be parsed normally
    //QCoreApplication::addLibraryPath("./plugins");

#ifdef USE_SYS_QTEXTCODEC
    QTextCodec *codec = QTextCodec::codecForName("UTF8");
    QTextCodec::setCodecForTr(codec);

#if 1
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
#else
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
#endif

#endif

    // Check Sys language
    getSysLanguage();

    if(argc == 2)
    {
        findStamp(QString(argv[1]));
    }
    else if(argc == 3)
    {
        findStamp(QString(argv[1]), QString(argv[2]).toInt());
    }
    else
    {
        findStamp();
        usage();
    }

    return 0;
    //return a.exec();
}

void usage()
{
    printf("Invalid arguments!\n");
    printf("Usage:\n");
    printf("\trecognize_stamp.exe fileName threshold[default=500]\n");
    printf("\t example1: recognize_stamp.exe stamp005.jpg 1000\n");
    printf("\t example2: recognize_stamp.exe stamp005.jpg\n");
}

bool findStamp(QString fileName, int checkThres)
{
    bool ret = false;
    Mat srcImage;
    Mat srcImage_B, srcImage_G, srcImage_R;
    const int thresholdValue = 170;
    bool SHOW_OPENCV_IMAGE = false;
    QTime runTime;

    runTime.restart();

    // Vector for BGR channel
    vector<Mat> channels_BGR;

    // Read source image
    srcImage = imread(fileName.toStdString());
    if (srcImage.empty())
    {
        cout << "Load image failed\n";
        return ret;
    }

    // RGB to HSV
    Mat hsv;
    cvtColor(srcImage, hsv, CV_RGB2HSV); // Need CV_RGB2HSV, CV_BGR2HSV not work well!

    Mat mask;

    // Make between lower_blue and upper_blue as 255(white), other as 0(black)
    inRange(hsv, Scalar(100, 30, 100), Scalar(150, 255, 255), mask);

    Mat res;
    // Keep white area, remove black area
    bitwise_and(srcImage, srcImage, res, mask=mask);

    // Split RGB to seperate channle data
    split(res, channels_BGR);

    // Get color info from Vector
    // 0 - Blue, 1 - Green,  2 - Red
    srcImage_B = channels_BGR.at(0);
    srcImage_G = channels_BGR.at(1);
    srcImage_R = channels_BGR.at(2);

    if(SHOW_OPENCV_IMAGE)
    {
        // show the image on window
        imshow("Src Image", srcImage);

        imshow("HSV", hsv);
        imshow("Mask", mask);
        imshow("Res", res);

        // Show R/G/B images
        imshow("srcImage_B", srcImage_B);
        imshow("srcImage_G", srcImage_G);
        imshow("srcImage_R", srcImage_R);
    }

    int count = 0;

    for(int i = 0; i < srcImage_R.rows; i++)
    {
        for(int j = 0; j < srcImage_R.cols; j++)
        {
            if(srcImage_R.at<uchar>(i, j) > thresholdValue)
            {
                count++;
            }
        }
    }

    qDebug() << "count = " << count;
    qDebug() << "runTime.elapsed() = " << runTime.elapsed() << " ms";

    if(count > checkThres)
    {
        ret = true;
        printf("Found red stamp\n");
        qDebug() << QString::fromUtf8("该图片有红章");

    }
    else
    {
        ret = false;
        printf("No red stamp\n");
        qDebug() << QString::fromUtf8("该图片没有红章");
    }

    return ret;
}

void getSysLanguage()
{
    UINT  nLanID   =   GetSystemDefaultLangID();
    WORD  PriLan   =   PRIMARYLANGID(nLanID);
    WORD  SubLan   =   SUBLANGID(nLanID);

    if( PriLan == LANG_ENGLISH )
    {
        qDebug() << "Sys language is English";
    }
    else if( PriLan == LANG_CHINESE )
    {
        if( SubLan == SUBLANG_CHINESE_SIMPLIFIED )
        {
            qDebug() << "Sys language is Chinese Simplified";
        }
        else if( SubLan == SUBLANG_CHINESE_TRADITIONAL )
        {
            qDebug() << "Sys language is Chinese Traditional";
        }
    }
}
