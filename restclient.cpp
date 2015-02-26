#include "restclient.h"

std::unique_ptr<QNetworkAccessManager> RestClient::customNetworkAccessManager(std::unique_ptr<QNetworkAccessManager>(new QNetworkAccessManager));

void RestClient::post(const QUrl &url, const QMap<QString, QString> data, QMap<QString, QString> headerData, std::function<void(QNetworkReply*)> callback)
{
    QNetworkRequest postRequest;
    postRequest.setUrl(url);
    QUrlQuery postQuery;
    setQueryItems(postQuery, data);
    setMultipleHeaders(postRequest, headerData);
    QNetworkReply *postReply = customNetworkAccessManager->post(postRequest, postQuery.toString().toUtf8());
    QObject::connect(postReply, &QNetworkReply::finished, [=]() { callback(postReply); postReply->deleteLater(); });
}

void RestClient::get(const QUrl &url, QMap<QString, QString> data, QMap<QString, QString> headerData, std::function<void (QNetworkReply *)> callback)
{
    QNetworkRequest getRequest;
    getRequest.setUrl(url);
    QUrlQuery getQuery;
    setQueryItems(getQuery, data);
    setMultipleHeaders(getRequest, headerData);
    QNetworkReply *getReply = customNetworkAccessManager->get(getRequest);
    QObject::connect(getReply, &QNetworkReply::finished, [=]() { callback(getReply); getReply->deleteLater(); });
}

void RestClient::setMultipleHeaders(QNetworkRequest &networkRequest, const QMap<QString, QString> &headers)
{
    if (!headers.empty()) {
        QMapIterator<QString, QString> mapItr(headers);
        while (mapItr.hasNext()) {
            mapItr.next();
            networkRequest.setRawHeader(mapItr.key().toUtf8(), mapItr.value().toUtf8());
        }
    }

}

void RestClient::setQueryItems(QUrlQuery &urlQuery, const QMap<QString, QString> &queryItems)
{
    if (!queryItems.empty()) {
        QMapIterator<QString, QString> mapItr(queryItems);
        while (mapItr.hasNext()) {
            mapItr.next();
            urlQuery.addQueryItem(mapItr.key(), mapItr.value());
        }
    }
}

void RestClient::defaultResponseHandler(QNetworkReply *reply)
{
    qDebug() << "Default Response Handler has been invoked for url: " << reply->url().toString();
    qDebug() << reply->readAll();
}
