#include <QCoreApplication>
#include "restclient.h"

#include <QVariant>

#include <utility>

void handleReply(QNetworkReply *jsonReply)
{
    qDebug() << "Reply Received";
    qDebug() << jsonReply->url();
    qDebug() << jsonReply->errorString();
    qDebug() << jsonReply->readAll();
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    RestClient::get(QUrl("https://hacker-news.firebaseio.com/v0/item/8863.json"));
    return a.exec();
}
