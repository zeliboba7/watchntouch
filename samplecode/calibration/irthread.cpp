#include "irthread.h"

#include <QDebug>
#include <QPainter>
#include <qevent.h>
#include <cmath>




IRThread::IRThread(CalibrationWindow * w) : QThread(w)
{

    prevX = 0;
    prevY = 0;
    cw = w;
    // wiiuse setup
    /*
    *	Initialize an array of wiimote objects.
    *
    *	The parameter is the number of wiimotes I want to create.
    */

    wiimotes =  wiiuse_init(MAX_WIIMOTES);

    /*
    *	Find wiimote devices
    *
    *	Now we need to find some wiimotes.
    *	Give the function the wiimote array we created, and tell it there
    *	are MAX_WIIMOTES wiimotes we are interested in.
    *
    *	Set the timeout to be 5 seconds.
    *
    *	This will return the number of actual wiimotes that are in discovery mode.
    */

    found = wiiuse_find(wiimotes, MAX_WIIMOTES, 5);
    if (!found) {
            printf ("No wiimotes found.");
            exit(-1);
    }
    /*
    *	Connect to the wiimotes
    *
    *	Now that we found some wiimotes, connect to them.
    *	Give the function the wiimote array and the number
    *	of wiimote devices we found.
    *
    *	This will return the number of established connections to the found wiimotes.
    */

    connected = wiiuse_connect(wiimotes, MAX_WIIMOTES);
    if (connected)
            printf("Connected to %i wiimotes (of %i found).\n", connected, found);
    else {
            printf("Failed to connect to any wiimote.\n");
            exit(-1);
    }

    /*
    *	Now set the LEDs and rumble for a second so it's easy
    *	to tell which wiimotes are connected (just like the wii does).
    */

    wiiuse_set_leds(wiimotes[0], WIIMOTE_LED_1);
    wiiuse_rumble(wiimotes[0], 1);

    #ifndef WIN32
            usleep(200000);
    #else
            Sleep(200);
    #endif

    wiiuse_rumble(wiimotes[0], 0);
    wiiuse_set_ir(wiimotes[0], 1);

    QObject::connect(this,SIGNAL(IRReleased(int,int)),cw,SLOT(calibrationDataReceived(int,int)));

}

IRThread::~IRThread()
    {
    }


void IRThread::run()
{
    // TODO: there you can run some part of your code in
    // different thread that rest of the application

    // You can create needed classes here or also in IRThread construction.

    // Thread enters the event loop and waits until exit() is called

    while(1) {
        if (wiiuse_poll(wiimotes, MAX_WIIMOTES)) {
            if(wiimotes[0]->event == WIIUSE_EVENT) {
                if (WIIUSE_USING_IR(wiimotes[0])) {
                    int i = 0;
                    /* go through each of the 4 possible IR sources */
                    for (; i < 4; ++i) {
                        /* check if the source is visible */
                        if (wiimotes[0]->ir.dot[i].visible) {
                            //printf("IR source %i: (%u, %u)\n", i, wiimotes[0]->ir.dot[i].x, wiimotes[0]->ir.dot[i].y);
                            if(cw->calibrationPointTouchCount < 4) {
                                int x = wiimotes[0]->ir.dot[i].x;
                                int y = wiimotes[0]->ir.dot[i].y;
                                if(abs((double)prevX - x) > 200 || abs((double)prevY - y) > 200) {
                                    emit IRReleased(x, y);
                                    printf("calibrated points 1 : %d %d %d %d %d\n",x,y, prevX, prevY,abs((double)prevX - x));
                                    cw->wc.wait(&(cw->mutex),2000);
                                    prevX = x;
                                    prevY = y;
                                }
                                //else {
                                  //  prevX = wiimotes[0]->ir.dot[i].x;
                                  //  prevY = wiimotes[0]->ir.dot[i].y;
                                //}
                            }
                            else
                                emit IRReleased(wiimotes[0]->ir.dot[i].x, wiimotes[0]->ir.dot[i].y);

                        }
                    }
                    printf("polling...\n");
                }
            }
        }
    }
    exec();
}

