#include "websocketpackage.h"

QByteArray WebSocketPackage::MakePackage(const QJsonObject &obj, const QByteArray &key) {
    auto dataPart = QJsonDocument(obj).toJson(QJsonDocument::Compact)
            .toBase64(QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals);
    auto signaturePart = QMessageAuthenticationCode::hash(dataPart, key, QCryptographicHash::Sha256)
            .toBase64(QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals);
    return QByteArray(dataPart).append(".").append(signaturePart);
}

QJsonObject WebSocketPackage::ReadPackage(const QByteArray &data, const QByteArray &key) {
    auto dot = data.indexOf(".");
    auto dataPart = data.left(dot);
    auto signaturePart = data.right(data.length() - dot - 1);

    auto generatedSignature = QMessageAuthenticationCode::hash(dataPart, key, QCryptographicHash::Sha256);
    auto obtainedSignature = QByteArray::fromBase64(signaturePart, QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals);
    if (generatedSignature != obtainedSignature) {
        qInfo("JWT::ReadJWT : Unvertified - Returning Empty Object.");
        return QJsonObject();
    }
    auto out = QByteArray::fromBase64(dataPart, QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals);
    return QJsonDocument::fromJson(out).object();
}
const QByteArray WebSocketPackage::MakeRandomBytes(const int &size) {
    QByteArray data(size, Qt::Uninitialized);
        for(int i = 0; i < size; i++)
            data[i] = (char)qrand();
        return data;
}
