#ifndef CVMEDIAPLAYER_H
#define CVMEDIAPLAYER_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QImage>
#include <QTimer>
#include <QVideoFrame>
#include <QAbstractVideoSurface>
#include <QVideoSurfaceFormat>
#include <QDebug>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

class CVMediaPlayer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractVideoSurface * videoSurface READ videoSurface WRITE setVideoSurface NOTIFY videoSurfaceChanged)
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(CVMediaPlayer::PlaybackStatue PlayingState READ playingState NOTIFY playingStateChanged)

public:


    enum PlaybackStatue
    {
        PlayingState,
        PausedState,
        StoppedState
    };
    Q_ENUMS(PlaybackStatue)

    CVMediaPlayer();
    ~CVMediaPlayer();

    QAbstractVideoSurface * videoSurface() const { return mVideoSurface; }
    void setVideoSurface(QAbstractVideoSurface *videoSurface);

    QUrl source() { return QUrl::fromLocalFile(mSource); }
    void setSource(QUrl src);

    PlaybackStatue playingState() const { return mPlayingState; }

    Q_INVOKABLE void pause();
    Q_INVOKABLE void play();
    Q_INVOKABLE void stop();

signals:
    void videoSurfaceChanged();
    void sourceChanged();
    void playingStateChanged(PlaybackStatue);

private:
    void updateSurface();

    QString mSource;
    QAbstractVideoSurface * mVideoSurface;
    QVideoSurfaceFormat mVideoSurfaceFormat;
    QTimer * mTimer;
    cv::VideoCapture mVideoCapture;
    PlaybackStatue mPlayingState;
};

#endif // CVMEDIAPLAYER_H
