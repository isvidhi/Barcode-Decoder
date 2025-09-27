#ifndef BARCODEDECODER_H
#define BARCODEDECODER_H

#include <QObject>
#include <QImage>
#include <QQmlEngine>
#include <QString>

// OpenCV includes
#include <opencv2/opencv.hpp>

#include <ZXing/ReadBarcode.h>
#include <ZXing/DecodeHints.h>
#include <ZXing/Result.h>

class BarcodeDecoder : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString lastResult READ lastResult NOTIFY lastResultChanged)
    Q_PROPERTY(bool isProcessing READ isProcessing NOTIFY isProcessingChanged)

public:
    explicit BarcodeDecoder(QObject *parent = nullptr);

    QString lastResult() const;
    bool isProcessing() const;

public slots:
    void processImage(const QImage &image);

signals:
    void lastResultChanged();
    void isProcessingChanged();
    void barcodeDetected(const QString &result, const QString &format);

private:
    QString m_lastResult;
    bool m_isProcessing;

    cv::Mat qImageToCvMat(const QImage &image);
    cv::Mat preprocessImage(const cv::Mat &input);
    QString decodeWithZXing(const cv::Mat &image);

    void setLastResult(const QString &result);
    void setIsProcessing(bool processing);
};

#endif // BARCODEDECODER_H
