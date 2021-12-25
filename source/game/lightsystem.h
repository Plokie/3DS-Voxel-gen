#ifndef LIGHTSYSTEM_H
#define LIGHTSYSTEM_H

#define STACKSIZE (4 * 1024)

#include <string.h>
#include <stdio.h>
#include <3ds.h>
#include <time.h>

volatile bool runLightThread=true;

Thread lightThread;
Handle lightHandle;
time_t timer;

void lightThreadFunc(void *arg)
{
    while(runLightThread)
    {
        svcWaitSynchronization(lightHandle, U64_MAX);
        svcClearEvent(lightHandle);
        
        fflush(stdout);
        printf("\x1b[16;2HChunk size: %lli", time(&timer));
        fflush(stdout);
    }
}

void initLightThread()
{
    svcCreateEvent(&lightHandle, (ResetType)0);
    lightThread = threadCreate(lightThreadFunc, 0, STACKSIZE, 0x3f, -2, true);
}

void killLightThread()
{
    runLightThread=false;
    svcSignalEvent(lightHandle);
    threadJoin(lightThread, U64_MAX);
	threadFree(lightThread);
    svcCloseHandle(lightHandle);
}



#endif