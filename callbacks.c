#include <pspkernel.h>

#include "oslua.h"

extern lua_State *globalL;

/* Exit callback */
int ExitCallback(int arg1, int arg2, void *common) {
    oslQuit();
    sceKernelExitGame();
    return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp) {
    int cbid;

    cbid = sceKernelCreateCallback("ExitCallback", ExitCallback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();

    return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void) {
    int thid = 0;

    thid = sceKernelCreateThread("CallbackThread", CallbackThread, 0x11, 0xFA0, PSP_THREAD_ATTR_USER, 0);
    if(thid >= 0) {
        sceKernelStartThread(thid, 0, 0);
    }

    return thid;
}
