#include "collaborativedrawingwidget.h"

CollaborativeDrawingWidget::CollaborativeDrawingWidget(QWidget *parent) :
    BaseDrawingWidget(parent)
{
    serverSocket = NULL;
    connect(&server, SIGNAL(newConnection()), this, SLOT(gotNewConnection()));
}

void CollaborativeDrawingWidget::commitDrawing(QPicture drawingPictureData)
{
    // TODO the actual data sending shouldn't take place here
    // TODO implement a proper protocol with error checking!

    qWarning() << "Collab commitDrawing size" << drawingPictureData.size();

    BaseDrawingWidget::commitDrawing(drawingPictureData);
    QByteArray picdata(drawingPictureData.data(), drawingPictureData.size());
    qWarning() << "written bytes #" << clientSocket.write(picdata);
}

void CollaborativeDrawingWidget::startListening(int portNumber)
{
    qWarning() << "server starting to listen";
    server.listen(QHostAddress::Any, portNumber);
}


void CollaborativeDrawingWidget::gotNewConnection()
{
    qWarning() << "server got new connection!";

    serverSocket = server.nextPendingConnection();
    connect(serverSocket, SIGNAL(readyRead()), this, SLOT(dataArrived()));
}


void CollaborativeDrawingWidget::dataArrived()
{
    qWarning() << "new data arrived to server!";
    QByteArray newdata = serverSocket->readAll();
    qWarning() << "size of arrived data" << newdata.size();
    QPicture pic;
    pic.setData(newdata.constData(), newdata.size());
    BaseDrawingWidget::commitDrawing(pic);
}
