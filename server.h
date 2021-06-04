#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QNetworkInterface>
#include <QDataStream>
#include <QString>
#include <QVariant>

enum COMMAND { PING = 1, MESSAGE = 2 };

struct Client
{
    QTcpSocket *pSocket;
    bool statusConnection = false;
};

struct Host
{
    QHostAddress ip;
    int port;
};

class Server : public QObject
{
    Q_OBJECT

    Host host;

    QTcpServer* pServer;
    quint16 nNextBlockSize;

    Client client;

public:
    explicit Server(QObject *parent = nullptr);

    Host getHost() { return host; }

signals:
    void startServerError(QString message);
    void startServerSuccessful();
    void inputMessage(QString message);
    void serverStop();
    void clientDisconnected();
    void clientConnected();

public slots:
    void slotStart();
    void slotStop();
    void slotClientDisconnected();
    void slotReadClient();
    void slotNewConnection();
};

#endif // SERVER_H
