#include "cvmediaplayer.h"

CVMediaPlayer::CVMediaPlayer()
    : mVideoSurface(nullptr)
    , mVideoSurfaceFormat(QVideoSurfaceFormat(QSize(640, 480), QVideoFrame::Format_RGB32))
    , mPlayingState(StoppedState)
{
    mTimer = new QTimer(this);
    mTimer->setInterval(100);
    connect(mTimer, &QTimer::timeout, this, &CVMediaPlayer::updateSurface);
}

CVMediaPlayer::~CVMediaPlayer()
{
    if(mVideoCapture.isOpened())
        mVideoCapture.release();
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
    mVideoCapture.open(mSource.toStdString());
    mPlayingState = PlayingState;
    emit playingStateChanged(mPlayingState);
}

void CVMediaPlayer::pause()
{
    mTimer->stop();
    mPlayingState = PausedState;
    emit playingStateChanged(mPlayingState);
}

void CVMediaPlayer::play()
{
    mTimer->start();
    mPlayingState = PlayingState;
    emit playingStateChanged(mPlayingState);
}

void CVMediaPlayer::stop()
{
    mTimer->stop();
    mVideoCapture.release();
    mVideoCapture.open(mSource.toStdString());
    mPlayingState = StoppedState;
    emit playingStateChanged(mPlayingState);
}
