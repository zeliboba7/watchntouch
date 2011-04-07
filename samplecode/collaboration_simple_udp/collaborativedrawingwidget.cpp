#include "collaborativedrawingwidget.h"

CollaborativeDrawingWidget::CollaborativeDrawingWidget(QWidget *parent) :
    BaseDrawingWidget(parent)
{
    //serverSocket = NULL;
    //connect(&server, SIGNAL(newConnection()), this, SLOT(gotNewConnection()));
}

void CollaborativeDrawingWidget::commitDrawing(QPicture drawingPictureData)
{
    // TODO the actual data sending shouldn't take place here
    // TODO implement a proper protocol with error checking!



    qWarning() << "Collab commitDrawing size" << drawingPictureData.size();

    BaseDrawingWidget::commitDrawing(drawingPictureData);
    QByteArray picdata(drawingPictureData.data(), drawingPictureData.size());
    int dsize = drawingPictureData.size();
    QByteArray datalen = QByteArray::fromRawData((const char*)&dsize, 4);

    QByteArray datagram;
    datagram.append(QString("DRAW").toAscii());
    datagram.append(datalen);
    datagram.append(picdata);

    /*qWarning() << "written header # " << clientSocket.write(QString("DRAW").toAscii());
    qWarning() << "written length # " << clientSocket.write(datalen) << datalen;
    qWarning() << "written bytes #" << clientSocket.write(picdata);*/

    server.writeDatagram(datagram.data(), datagram.size(), QHostAddress::Broadcast, 45454);
}

void CollaborativeDrawingWidget::startListening(int portNumber)
{
    //qWarning() << "server starting to listen";
    //server.listen(QHostAddress::Any, portNumber);
    client.bind(45454, QUdpSocket::ShareAddress);
    connect(&client, SIGNAL(readyRead()),
            this, SLOT(dataArrived()));
    /*void Receiver::processPendingDatagrams()
    {
    //! [2]
        while (udpSocket->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(udpSocket->pendingDatagramSize());
            udpSocket->readDatagram(datagram.data(), datagram.size());
            statusLabel->setText(tr("Received datagram: \"%1\"")
                                 .arg(datagram.data()));
        }
    //! [2]
    }*/
}


void CollaborativeDrawingWidget::gotNewConnection()
{
    qWarning() << "server got new connection!";

    /*serverSocket = server.nextPendingConnection();
    connect(serverSocket, SIGNAL(readyRead()), this, SLOT(dataArrived()));*/
}


void CollaborativeDrawingWidget::dataArrived()
{
    static int sizeOfPackage = -1;
    static QByteArray receivedData;

    while (client.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(client.pendingDatagramSize());
        client.readDatagram(datagram.data(), datagram.size());

        qWarning() << "new data arrived to server!";
        QByteArray newdata = datagram;
        qWarning() << "size of arrived data" << newdata.size();

        if(newdata.startsWith(QString("DRAW").toAscii())) {
            qWarning() << "raw data" << newdata.right(newdata.length() - 4).left(4).toHex();
            memcpy(&sizeOfPackage, newdata.right(newdata.length() - 4).left(4).constData(), 4);
            qWarning() << "got sizeofpackage " << sizeOfPackage;
            receivedData = newdata.right(newdata.length() - 8);
        } else {
            receivedData.append(newdata);
        }

        qWarning() << "sizeofpackage " << sizeOfPackage << "total recv data size" << receivedData.size();

        if(sizeOfPackage == receivedData.size()) {
            // done receiving data for this drawing step
            QPicture pic;
            pic.setData(receivedData.constData(), receivedData.size());
            BaseDrawingWidget::commitDrawing(pic);
            sizeOfPackage = -1;
            receivedData = QByteArray();
        }
    }
}
