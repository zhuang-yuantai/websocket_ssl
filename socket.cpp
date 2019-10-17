#include "socket.h"
#include <QtCore/QDebug>
#include <QtWebSockets/QWebSocket>
#include <QCoreApplication>
#include <QSslConfiguration>
#include <QSslSocket>

Socket::Socket(QObject *parent) : QObject(parent)
{

    connect(&m_webSocket, &QWebSocket::connected, this, &Socket::onConnected);
    connect(&m_webSocket, QOverload<const QList<QSslError>&>::of(&QWebSocket::sslErrors),
            this, &Socket::onSslErrors);
    connect(&m_webSocket, &QWebSocket::disconnected , this, &Socket::onDisconnected);
    QSslConfiguration config = m_webSocket.sslConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1SslV3);
    m_webSocket.setSslConfiguration(config);
    m_webSocket.open(QUrl(QStringLiteral("wss://webSocket.nctu.me:4433")));

}

void Socket::onConnected()
{
    qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &Socket::onTextMessageReceived);
}

void Socket::onTextMessageReceived(QString message)
{
    qDebug() << "Message received:" << message;
}

void Socket::onSslErrors(const QList<QSslError> &errors)
{

    Q_UNUSED(errors);

    // WARNING: Never ignore SSL errors in production code.
    // The proper way to handle self-signed certificates is to add a custom root
    // to the CA store.

   // m_webSocket.ignoreSslErrors();
}

void Socket::onDisconnected()
{
    qDebug() << "        log closeReason:" << m_webSocket.closeReason() ;
    qDebug() << "        log closeCode:" << m_webSocket.closeCode() ;
}
bool Socket::TextMessageReceived(QString message){
    qDebug() << "        log message:" << message;
    m_webSocket.sendTextMessage(message);
    return 0;
}
