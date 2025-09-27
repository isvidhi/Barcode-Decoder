#include "videomanager.h"

VideoManager::VideoManager(QObject *parent)
    : QObject{parent}
{}

QVideoSink *VideoManager::videoSink() const {
    return m_videoSink.get();
}

void VideoManager::setVideoSink(QVideoSink *newVideoSink) {
    if (m_videoSink == newVideoSink)
        return;
    if (m_videoSink) {
        disconnect(m_videoSink, nullptr, this, nullptr);
    }

    m_videoSink = newVideoSink;

    // Connect to new sink
    if (m_videoSink) {
        connect(m_videoSink, &QVideoSink::videoFrameChanged,
                this, &VideoManager::processFrame);
    }

    emit videoSinkChanged();
}

void VideoManager::processFrame(const QVideoFrame &frame)
{
    if(!frame.isValid()){
        return;
    }

    m_frameCounter++;
    if(m_frameCounter % 3 != 0) {
        return;
    }

    QImage image = convertFrameToImage(frame);
    if(!image.isNull()){
        emit frameReady(image);
    }

}

QImage VideoManager::convertFrameToImage(const QVideoFrame &frame)
{
    QVideoFrame clonedFrame(frame);
    clonedFrame.map(QVideoFrame::ReadOnly);

    QImage image = clonedFrame.toImage();

    clonedFrame.unmap();
    return image;
}

