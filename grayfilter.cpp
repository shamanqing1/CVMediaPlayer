#include "grayfilter.h"
#include <QDebug>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#include <iostream>

int i = 0;
QVideoFrame GrayFilterRunnable::run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, QVideoFilterRunnable::RunFlags flags)
{
    if (!input->isValid())
        return *input;
    input->map(QAbstractVideoBuffer::ReadOnly);
//    qDebug() << surfaceFormat;
//    qDebug() << flags;

    QImage image = input->image();
    image.convertTo(QImage::Format_Grayscale8);
    cv::Mat mat(image.height(), image.width(), CV_8UC1, image.bits(), image.bytesPerLine());
    cv::Mat edges;
    cv::Canny(mat, edges, 50, 80);
    QImage outImage(edges.data, edges.cols, edges.rows, edges.step, QImage::Format_Grayscale8);
    outImage.convertTo(QImage::Format_RGB32);

//    std::cout << mat;
//    cv::imwrite("test.jpg", mat);
//    QImage img = image.convertToFormat(QImage::Format_Grayscale8);
//    QString path = QString::number(i++) + ".jpg";
//    qDebug("%s", path.toStdString().c_str());

//    cv::Mat mat(img.height(), img.width(), CV_8UC3, img.bits(),img.bytesPerLine());
//    qDebug("opencv image width: %d height %d", mat.cols, mat.rows);
//    cv::Mat gray;
//    cv::cvtColor(mat, gray, cv::COLOR_BGR2GRAY);
//    cv::imwrite(path.toStdString(), gray);
//    QImage tmp((uchar*)gray.data, gray.cols, gray.rows, gray.step, QImage::Format_Grayscale8);
    if (input->isMapped())
        input->unmap();
    return QVideoFrame(outImage);
}
