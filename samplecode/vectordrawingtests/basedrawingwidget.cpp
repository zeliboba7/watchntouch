#include "basedrawingwidget.h"

#include <QDebug>
#include <QMouseEvent>
#include <QGraphicsLineItem>

BaseDrawingWidget::BaseDrawingWidget(QWidget *parent) :
    QGraphicsView(parent)
{
    // set the default options for drawing
    drawingPen = DEFAULT_DRAWING_PEN;
    drawingBrush = DEFAULT_DRAWING_BRUSH;
    drawingMode = DRAWINGMODE_FREEHAND;
}

void BaseDrawingWidget::mouseMoveEvent (QMouseEvent * event)
{
    drawingUpdate(mapToScene(event->pos()));
}

void BaseDrawingWidget::mousePressEvent (QMouseEvent * event)
{
    drawingStart(mapToScene(event->pos()));
}

void BaseDrawingWidget::mouseReleaseEvent (QMouseEvent * event)
{
    drawingEnd(mapToScene(event->pos()));
}

void BaseDrawingWidget::drawLineAction(QPointF from, QPointF to)
{
    QGraphicsLineItem *newItem = new QGraphicsLineItem(QLineF(from, to));
    newItem->setPen(drawingPen);
    getDrawingData()->addItem(newItem);
}

void BaseDrawingWidget::setDrawingData(DrawingData * newData)
{
    drawingData = newData;
    setScene(drawingData);
}

DrawingData * BaseDrawingWidget::getDrawingData()
{
    return drawingData;
}

void BaseDrawingWidget::setDrawingPen(QPen pen)
{
    drawingPen = pen;
}

QPen BaseDrawingWidget::getDrawingPen()
{
    return drawingPen;
}

void BaseDrawingWidget::setDrawingBrush(QBrush brush)
{
    drawingBrush = brush;
}

QBrush BaseDrawingWidget::getDrawingBrush()
{
    return drawingBrush;
}

void BaseDrawingWidget::setDrawingMode(DrawingMode mode)
{
    drawingMode = mode;
}

DrawingMode BaseDrawingWidget::getDrawingMode()
{
    return drawingMode;
}

void BaseDrawingWidget::drawingStart(QPointF startPoint)
{
    mouseDownPoint = mousePrevPoint = startPoint;
}

void BaseDrawingWidget::drawingUpdate(QPointF updatePoint)
{
    drawLineAction(mousePrevPoint, updatePoint);
    mousePrevPoint = updatePoint;
}

void BaseDrawingWidget::drawingEnd(QPointF endPoint)
{
    drawLineAction(mousePrevPoint, endPoint);
    getDrawingData()->registerAction();
    mousePrevPoint = mouseUpPoint = endPoint;
}


void BaseDrawingWidget::resizeEvent(QResizeEvent * event)
{
    // TODO fix scene size problem - we still have scrollbars appearing
    if(scene() != NULL) {
        scene()->setSceneRect(0,0,width() - 50,height() - 50);
    }

    QGraphicsView::resizeEvent(event);
}
