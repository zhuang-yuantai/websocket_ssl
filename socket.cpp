#include "socket.h"
#include <QtCore/QDebug>
#include <QtWebSockets/QWebSocket>
#include <QCoreApplication>
#include <QSslConfiguration>
#include <QSslSocket>
#include <QTextCodec>

Socket::Socket(QObject *parent) : QObject(parent)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    connect(&m_webSocket, &QWebSocket::connected, this, &Socket::onConnected);
    connect(&m_webSocket, QOverload<const QList<QSslError>&>::of(&QWebSocket::sslErrors),
            this, &Socket::onSslErrors);
    QSslConfiguration config = m_webSocket.sslConfiguration();
    config.setPeerVerifyMode(QSslSocket::QueryPeer);
    //config.setProtocol(QSsl::TlsV1SslV3);
    config.setProtocol(QSsl::AnyProtocol);
    m_webSocket.setSslConfiguration(config);
    m_webSocket.open(QUrl(QStringLiteral("wss://webSocket.nctu.me:4433")));

}

void Socket::onConnected()
{
    qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &Socket::onTextMessageReceived);
    connect(&m_webSocket, &QWebSocket::disconnected , this, &Socket::onDisconnected);
}

void Socket::onTextMessageReceived(QString message)
{
    emit textMessageReceivedChanged(message);
}

void Socket::onSslErrors(const QList<QSslError> &errors)
{
    Q_UNUSED(errors)
//    // WARNING: Never ignore SSL errors in production code.
//    // The proper way to handle self-signed certificates is to add a custom root
//    // to the CA store.
//    m_webSocket.ignoreSslErrors();
}

void Socket::onDisconnected()
{
    qDebug() << "        log closeReason:" << m_webSocket.closeReason() ;
    qDebug() << "        log closeCode:" << m_webSocket.closeCode() ;
}
bool Socket::sendTextMessage(QString message){
    qDebug() << "        log message:" << message;
    m_webSocket.sendTextMessage(message.toUtf8());
    emit textMessageReceivedChanged("{\"action\":\"System echo\", \"data\":\""+message+"\"}");
    emit textMessageReceivedChanged("{\"action\":\"System echo toUtf8\", \"data\":\""+message.toUtf8()+"\"}");
    return 0;
}
bool Socket::close(){
    m_webSocket.close();
    emit textMessageReceivedChanged("{\"action\":\"System\", \"data\":\"Socket close\"}");
    return 0;
}

bool Socket::connectionSocket(){
    qDebug() <<"      log start connection";
    m_webSocket.open(QUrl(QStringLiteral("wss://webSocket.nctu.me:4433")));
    emit textMessageReceivedChanged("{\"action\":\"System\", \"data\":\"Socket connection\"}");
    qDebug() <<"        log connection end";
    return 0;
}
