#include "appcontroller.h"

AppController::AppController(QObject *parent)
    : QObject{parent}
    , m_videoManager(new VideoManager(this))
    , m_barcodeDecoder(new BarcodeDecoder(this))
{
    // Connect VideoManager to BarcodeDecoder
    connect(m_videoManager, &VideoManager::frameReady,
            m_barcodeDecoder, &BarcodeDecoder::processImage);
}

VideoManager* AppController::videoManager() const {
    return m_videoManager;
}

BarcodeDecoder* AppController::barcodeDecoder() const {
    return m_barcodeDecoder;
}
