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
    Q_INVOKABLE bool sendTextMessage(QString message);
    Q_INVOKABLE bool close();

signals:
    void textMessageReceivedChanged(QString message);

public slots:

private Q_SLOTS:
    void onConnected();
    void onSslErrors(const QList<QSslError> &errors);
    void onDisconnected();
    void onTextMessageReceived(QString message);

private:
    QWebSocket m_webSocket;
};

#endif // SOCKET_H
