#ifndef RESTCLIENT_H
#define RESTCLIENT_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QUrl>
#include <QMap>
#include <QJsonObject>
#include <QJsonDocument>

#include <memory>
#include <functional>

class RestClient
{
public:
    static void post(const QUrl &url, QMap<QString, QString> data, QMap<QString, QString> headerData = {{}}, std::function<void(QNetworkReply*)> callback = defaultResponseHandler);
    static void get(const QUrl &url, QMap<QString, QString> data = {{}}, QMap<QString, QString> headerData = {{}}, std::function<void(QNetworkReply*)> callback = defaultResponseHandler);

    static void setMultipleHeaders(QNetworkRequest &networkRequest, const QMap<QString, QString> &headers);
    static void setQueryItems(QUrlQuery &urlQuery, const QMap<QString, QString> &queryItems);

    static void defaultResponseHandler(QNetworkReply* reply);

private:
    static std::unique_ptr<QNetworkAccessManager> customNetworkAccessManager;
};

#endif // RESTCLIENT_H
