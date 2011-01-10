#include "inputcalibration.h"

#include <QDesktopWidget>
#include <QApplication>
#include <QDebug>

// class constructor
// - get screen width/height and store them
InputCalibration::InputCalibration()
{
    QDesktopWidget * desktop = QApplication::desktop();
    QRect rect = desktop->screenGeometry(-1);
    screenWidth = rect.width();
    screenHeight = rect.height();

    isCalibrated = false;

    pointCounter = 0;
    sampleCounterForCurrentPoint = 0;
}

// specify a new set of calibration points
// resets sampled point adding!
void InputCalibration::setCalibrationPoints(QPoint *newPoints)
{
    pointCounter = 0;
    calibrationPoints[0] = newPoints[0];
    calibrationPoints[1] = newPoints[1];
    calibrationPoints[2] = newPoints[2];
    calibrationPoints[3] = newPoints[3];

    isCalibrated = true;
}

// have we received calibration info yet?
bool InputCalibration::calibrated()
{
    return isCalibrated;
}

// get the existing calibration points
QPoint * InputCalibration::getCalibrationPoints()
{
    return calibrationPoints;
}

// add a data point sample for calibration
// once we have NUM_SAMPLES_PER_POINT samples, get the new point
void InputCalibration::addCalibrationSample(QPoint newPoint)
{
    // TODO the following conditional ignores repeated press events during calibration
    // this should be handled with TouchBegin - TouchEnd instead
    // but we may want to keep the following for extra security...just in case
    qWarning() << "points:" << newPoint << prevSample << "samplecounter" << sampleCounterForCurrentPoint;
    if((prevSample-newPoint).manhattanLength() < CALIBRATION_POINT_THRESHOLD && prevSample != QPoint(0,0))
    {
        qWarning() << "ignoring repeated calibration sample";
        return;
    }
    else
        qWarning() << "actually received new calibration sample";


    // sum with existing values
    sampleAverage += sampleAverage + newPoint;
    sampleCounterForCurrentPoint++;
    prevSample = newPoint;

    if(sampleCounterForCurrentPoint == NUM_SAMPLES_PER_POINT) {
        // we have enough samples for this point now
        // get the average from the data sum
        sampleAverage /= NUM_SAMPLES_PER_POINT;
        // we have one more calibration point now
        calibrationPoints[pointCounter] = sampleAverage;
        emit calibrationPointReceived(sampleAverage);
        pointCounter++;
        // get ready for the new set of samples
        sampleAverage = QPoint(0,0);
        sampleCounterForCurrentPoint = 0;
    }

    if(pointCounter == NUM_CALIBRATION_POINTS) {
        // we have all the calibration points we need
        isCalibrated = true;
        pointCounter = 0;
    }
}

// map from Wiimote coordinates to screen coordinates
// according to current calibration information
QPoint InputCalibration::mapFromWiimoteToScreen(QPoint inputPoint)
{
    // if calibration was not performed, return the same point
    if(!isCalibrated)
        return inputPoint;

    int x = inputPoint.x(), y = inputPoint.y();

    x = ((x - calibrationPoints[3].x()) * screenWidth)  / (double)(calibrationPoints[2].x() - calibrationPoints[3].x()) ;
    y = (((y - calibrationPoints[0].y() )* screenHeight) / (double)( calibrationPoints[3].y() - calibrationPoints[0].y())) ;

    return QPoint(x,y);
}

void InputCalibration::processWiimotePoint(QPoint inputPoint)
{
    QPoint mappedPoint = mapFromWiimoteToScreen(inputPoint);

    // TOOD send point to event generator
}

void InputCalibration::recalibrate()
{
    // TODO here we will display the calibration UI and perform a new calibration
}
