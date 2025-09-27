#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include <QQmlEngine>
#include "videomanager.h"
#include "barcodedecoder.h"

class AppController : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(VideoManager* videoManager READ videoManager CONSTANT)
    Q_PROPERTY(BarcodeDecoder* barcodeDecoder READ barcodeDecoder CONSTANT)

public:
    explicit AppController(QObject *parent = nullptr);

    VideoManager* videoManager() const;
    BarcodeDecoder* barcodeDecoder() const;

private:
    VideoManager* m_videoManager;
    BarcodeDecoder* m_barcodeDecoder;
};

#endif // APPCONTROLLER_H
