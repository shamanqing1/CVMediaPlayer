#include "grayfilter.h"
#include <QDebug>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

int i = 0;
QVideoFrame GrayFilterRunnable::run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, QVideoFilterRunnable::RunFlags flags)
{
    if (!input->isValid())
        return *input;
    input->map(QAbstractVideoBuffer::ReadOnly);

    QImage image = input->image();
    QImage img = image.convertToFormat(QImage::Format_BGR888);
    QString path = QString::number(i++) + ".jpg";
//    qDebug("%s", path.toStdString().c_str());

//    cv::Mat mat(img.height(), img.width(), CV_8UC3, img.bits(),img.bytesPerLine());
//    qDebug("opencv image width: %d height %d", mat.cols, mat.rows);
//    cv::Mat gray;
//    cv::cvtColor(mat, gray, cv::COLOR_BGR2GRAY);
//    cv::imwrite(path.toStdString(), gray);
//    QImage tmp((uchar*)gray.data, gray.cols, gray.rows, gray.step, QImage::Format_Grayscale8);
    *input = QVideoFrame(img);
    if (input->isMapped())
        input->unmap();
    return *input;
}
