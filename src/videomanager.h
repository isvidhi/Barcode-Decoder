#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include <QObject>
#include <QPointer>
#include <QVideoSink>
#include <QQmlEngine>
#include <QTimer>
#include <QImage>
#include <QPainter>
#include <QSize>
#include <QVideoFrame>
#include <QRandomGenerator>
#include <QDateTime>

class VideoManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QVideoSink* videoSink READ videoSink WRITE setVideoSink NOTIFY videoSinkChanged)
public:
    explicit VideoManager(QObject *parent = nullptr);
    QVideoSink *videoSink() const;
    void setVideoSink(QVideoSink *newVideoSink);
signals:
    void videoSinkChanged();
    void frameReady(const QImage &image);

private slots:
    void processFrame(const QVideoFrame &frame);

private:
    QPointer<QVideoSink> m_videoSink;
    QImage convertFrameToImage(const QVideoFrame &frame);
    int m_frameCounter = 0;
};

#endif // VIDEOMANAGER_H
