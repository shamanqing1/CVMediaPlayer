#include "cvmediaplayer.h"

CVMediaPlayer::CVMediaPlayer()
    : mVideoSurface(nullptr)
    , mVideoSurfaceFormat(QVideoSurfaceFormat(QSize(640, 480), QVideoFrame::Format_RGB32))
{
    mTimer = new QTimer(this);
    mTimer->setInterval(100);
    connect(mTimer, &QTimer::timeout, this, &CVMediaPlayer::updateSurface);
}

void CVMediaPlayer::setVideoSurface(QAbstractVideoSurface *videoSurface)
{
    if(mVideoSurface && mVideoSurface != videoSurface && mVideoSurface->isActive())
        mVideoSurface->stop();
    mVideoSurface = videoSurface;
    if(mVideoSurface && mVideoSurfaceFormat.isValid()) {
        mVideoSurfaceFormat = mVideoSurface->nearestFormat(mVideoSurfaceFormat);
        mVideoSurface->start(mVideoSurfaceFormat);
    }
}

void CVMediaPlayer::updateSurface()
{
    cv::Mat mat;
    if(mVideoCapture.isOpened()) {
        mVideoCapture >> mat;
        QImage image = QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_BGR888);
        auto imageFormat = QVideoFrame::imageFormatFromPixelFormat(mVideoSurfaceFormat.pixelFormat());
        image.convertTo(imageFormat);
        QVideoFrame frame = QVideoFrame(image);
        if(mVideoSurfaceFormat.frameSize() != frame.size()) {
            mVideoSurfaceFormat.setFrameSize(frame.size());
            mVideoSurface->stop();
            mVideoSurface->start(mVideoSurfaceFormat);
        }
        mVideoSurface->present(frame);
    }
}

void CVMediaPlayer::setSource(QUrl src)
{
    mSource = src.path();
    mTimer->start();
    mVideoCapture = cv::VideoCapture(mSource.toStdString());
}
