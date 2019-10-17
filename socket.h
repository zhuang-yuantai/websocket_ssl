#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QtWebSockets/QWebSocket>
#include <QtNetwork/QSslError>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QUrl>
#include <QSslSocket>
class Socket : public QObject
{
    Q_OBJECT
public:
    explicit Socket(QObject *parent = nullptr);
    Q_INVOKABLE bool TextMessageReceived(QString message);



signals:
    void TextMessageReceivedChanged();
public slots:

private Q_SLOTS:
    void onConnected();
    void onSslErrors(const QList<QSslError> &errors);
    void onDisconnected();
    void onTextMessageReceived(QString message);

private:

    QSslConfiguration sslConfiguration;
    QSslSocket sslSocke;
    QWebSocket m_webSocket;
};

#endif // SOCKET_H
