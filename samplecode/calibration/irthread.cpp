#include <QDebug>
#include <QPainter>
#include <qevent.h>
#include <cmath>

#include "irthread.h"
#include "calibrationwindow.h"
// TODO this class should be renamed to InputReceiver


IRThread::IRThread()
{
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

    // TODO bunu loop içinde tekrarlayalım, ta ki wiimote bulunana kadar, ama uygun arabirimi de olsun
    // (press and hold 1 and 2 on the wiimote

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

    previous.setX(0);
    previous.setY(0);
    counter = 0;
    startRelease = false;

}

void IRThread::releasedChecking() {
    printf("startRelease: %d\n",startRelease);
    startRelease = true;
}

IRThread::~IRThread()
    {
    }

// TODO aslında şu anda tek tür event gönderimi yapıyoruz, sadece IR point görünüyorken.
// onun yerine şu yaklaşımı izlesek faydalı olacak aslında:
// - daha önce görünmeyen bir yerde (prevX ve prevY ye bakarak anlaşılır) IR point çıktıysa TouchBegin
// - daha önce görünen bi yerin yakınlarında tekrar IR point oluştuysa TouchMove
// - daha önce görünen bi yerde artık IR point görünmüyorsa TouchEnd
// bunu EventGenerator içinde halletmek mantıklı.

void IRThread::run()
{
    while(1) {
        //printf("startRls: %d\n",startRelease);
        if(startRelease) {
            if(current == previous && previous != QPoint(0,0)) {
                counter++;
                printf("AAA: %d %d %d %d\n",current.x(), current.y(), previous.x() , previous.y());
            }
            if(counter >= 1000) {
                counter = 0;
                printf("counter 250 gecti!\n");
                startRelease = false;
                emit mouseReleased();
            }
            previous.setX(current.x());
            previous.setY(current.y());
            //printf("counter: %d\n",counter);
        }
        if (wiiuse_poll(wiimotes, MAX_WIIMOTES)) {
            if(wiimotes[0]->event == WIIUSE_EVENT) {
                if (WIIUSE_USING_IR(wiimotes[0])) {
                    int i = 0;                    
                    /* go through each of the 4 possible IR sources */
                    for (; i < 4; ++i) {
                        /* check if the source is visible */                        
                        if (wiimotes[0]->ir.dot[i].visible) {
                                printf("yeni aldım!\n");
                                current = QPoint(wiimotes[0]->ir.dot[i].x,(wiimotes[0]->ir.dot[i].y));
                                counter = 0;
                                emit IRInputReceived(wiimotes[0]->ir.dot[i].x, wiimotes[0]->ir.dot[i].y, i);                                
                        }                        
                    }
                }
            }
        }
    }
    exec();
}

