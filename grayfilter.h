#ifndef GRAYFILTER_H
#define GRAYFILTER_H

#include <QAbstractVideoFilter>
#include <QVideoFilterRunnable>

class GrayFilterRunnable : public QVideoFilterRunnable {
public:
    QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags);
};

class GrayFilter : public QAbstractVideoFilter
{
public:
    QVideoFilterRunnable *createFilterRunnable() {
        return new GrayFilterRunnable;
    }
signals:
    void finished(QObject *result);
};

#endif // GRAYFILTER_H
