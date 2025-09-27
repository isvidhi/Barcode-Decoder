#include "barcodedecoder.h"
#include <QDebug>

BarcodeDecoder::BarcodeDecoder(QObject *parent)
    : QObject{parent}
    , m_lastResult("Scanning for barcode...")
    , m_isProcessing(false)
{
}

QString BarcodeDecoder::lastResult() const {
    return m_lastResult;
}

bool BarcodeDecoder::isProcessing() const {
    return m_isProcessing;
}

void BarcodeDecoder::processImage(const QImage &image) {
    if (m_isProcessing || image.isNull()) {
        return;
    }

    setIsProcessing(true);

    // Convert QImage to OpenCV Mat
    cv::Mat cvImage = qImageToCvMat(image);
    if (cvImage.empty()) {
        setIsProcessing(false);
        return;
    }

    // Preprocess image for better decoding
    cv::Mat processedImage = preprocessImage(cvImage);

    // Decode barcode
    QString result = decodeWithZXing(processedImage);

    if (!result.isEmpty()) {
        setLastResult(result);
        emit barcodeDetected(result, "Unknown");
    }

    setIsProcessing(false);
}

cv::Mat BarcodeDecoder::qImageToCvMat(const QImage &image) {
    // Convert QImage to RGB format if needed
    QImage rgbImage = image.convertToFormat(QImage::Format_RGB888);

    // Create OpenCV Mat
    cv::Mat mat(rgbImage.height(), rgbImage.width(), CV_8UC3,
                (void*)rgbImage.constBits(), rgbImage.bytesPerLine());

    // OpenCV uses BGR, Qt uses RGB, so convert
    cv::Mat bgrMat;
    cv::cvtColor(mat, bgrMat, cv::COLOR_RGB2BGR);

    return bgrMat.clone(); // Clone to ensure data ownership
}

cv::Mat BarcodeDecoder::preprocessImage(const cv::Mat &input) {
    cv::Mat processed;

    // Convert to grayscale for better barcode detection
    cv::cvtColor(input, processed, cv::COLOR_BGR2GRAY);

    // Optional: Resize if image is too large (for performance)
    if (processed.cols > 800 || processed.rows > 600) {
        cv::resize(processed, processed, cv::Size(800, 600));
    }

    // Optional: Enhance contrast
    cv::equalizeHist(processed, processed);

    return processed;
}

QString BarcodeDecoder::decodeWithZXing(const cv::Mat &image) {
    try {
        ZXing::ImageView imageView{
            image.data,
            image.cols,
            image.rows,
            ZXing::ImageFormat::Lum
        };

        // Use ReaderOptions instead of DecodeHints
        ZXing::ReaderOptions options;
        options.setFormats(ZXing::BarcodeFormat::Any);
        options.setTryHarder(true);
        options.setTryRotate(true);

        auto result = ZXing::ReadBarcode(imageView, options);

        if (result.isValid()) {
            return QString::fromStdString(result.text());
        }

    } catch (const std::exception &e) {
        qDebug() << "ZXing decode error:" << e.what();
    }

    return QString();
}

void BarcodeDecoder::setLastResult(const QString &result) {
    if (m_lastResult != result) {
        m_lastResult = result;
        emit lastResultChanged();
    }
}

void BarcodeDecoder::setIsProcessing(bool processing) {
    if (m_isProcessing != processing) {
        m_isProcessing = processing;
        emit isProcessingChanged();
    }
}
