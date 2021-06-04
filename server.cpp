#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
             host.ip = address;
    }

    host.port = 12012;
    nNextBlockSize = 0;
}

void Server::slotStart()
{
    pServer = new QTcpServer(this);

    if (!pServer->listen(host.ip, host.port)) {
        pServer->close();
        emit startServerError("Unable to start server!");
        qDebug() << "Unable to start server!";
        qDebug() << host.ip;
        return;
    }
    else
        emit startServerSuccessful();

    connect(pServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
}

void Server::slotNewConnection()
{
    if(!client.statusConnection)
    {
        client.pSocket = pServer->nextPendingConnection();
        client.statusConnection = true;

        connect(client.pSocket, SIGNAL(disconnected()), this, SLOT(slotClientDisconnected()));
        connect(client.pSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));

        emit clientConnected();
    }
}

void Server::slotReadClient()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_5_13);

    for (;;) {
        if (!nNextBlockSize) {
            if (pClientSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }

            in >> nNextBlockSize;
        }

        if (pClientSocket->bytesAvailable() < nNextBlockSize) {
            break;
        }

        int COMMAND;
        in >> COMMAND;

        switch (COMMAND)
        {
        case MESSAGE:
        {
            QString message;

                in >> message;

            emit inputMessage(message);

            break;
        }
        default:
        {
            break;
        }
        }

        nNextBlockSize = 0;
    }
}

void Server::slotStop()
{
    //client.pSocket->disconnect();
    client.statusConnection = false;

    pServer->disconnect();

    delete pServer;
    delete client.pSocket;
}

void Server::slotClientDisconnected()
{
    client.statusConnection = false;
    delete client.pSocket;

    emit clientDisconnected();
}
