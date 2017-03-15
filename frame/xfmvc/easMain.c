#include "xfconf.h"
#include "xfea.h"

#include "bgraph.h"
#include "view.h"

#include "mvcMain.h"

extern VIEW_Layout vStorage;

void StateInitEntry(void);
void StateSleepEntry(void);
void ModeLockEntry(void);
void ModeManageEntry(void);
void ModeFactoryEntry(void);
void ModeVendorEntry(void);
int ModeLockProcessMsg(XF_Message *msg);
int ModeManageProcessMsg(XF_Message *msg);
int ModeFactoryProcessMsg(XF_Message *msg);
int ModeVendorProcessMsg(XF_Message *msg);


XF_Event EventKB = {
    0,
};

XF_Event EventFP = {
    0,
};

XF_Event EventTR = {
    0,
};

XF_State StateInit = {
    StateInitEntry,
    0,
    0,
};

XF_State StateSleep = {
    StateSleepEntry,
    0,
    0,
};

XF_State ModeLock = {
    ModeLockEntry,
	0,
    ModeLockProcessMsg,
};

XF_State ModeManage = {
    ModeManageEntry,
	0,
    ModeManageProcessMsg,
};

XF_State ModeFactory = {
    ModeFactoryEntry,
	0,
    ModeFactoryProcessMsg,
};

XF_State ModeVendor = {
    ModeVendorEntry,
	0,
    ModeVendorProcessMsg,
};

static XF_State *states[] = {&StateInit, &StateSleep, &ModeLock, &ModeManage, &ModeFactory, &ModeVendor};

XF_StateMachine MachLock = {
    states,
    sizeof(states)/sizeof(states[0]),
    &StateInit,
};

#define EVENTKB_INFO_SIZE          2
#define EVENTKB_ACTION_SIZE        3

#define EVENTFP_INFO_SIZE          1
#define EVENTFP_ACTION_SIZE        1

#define EVENTTR_INFO_SIZE          1
#define EVENTTR_ACTION_SIZE        5

void easMain() {
    XF_Info infoKB[EVENTKB_INFO_SIZE] = {0}, infoTR[EVENTTR_INFO_SIZE] = {0};
    char dataInfoKB[EVENTKB_INFO_SIZE] = {0}, dataInfoTR[EVENTTR_INFO_SIZE] = {0};
	XF_Action *actionKB[EVENTKB_ACTION_SIZE] = {0}, *actionTR[EVENTTR_ACTION_SIZE] = {0};
    XF_Event *events[] = {&EventKB, &EventTR};
    XF_EventPackage evtPkg = {
        events,
        sizeof(events) / sizeof(events[0]),
    };
    XF_EventCreate(&EventKB, XF_EVENY_TYPE_INTERRUPT, 0, infoKB, dataInfoKB, EVENTKB_INFO_SIZE, actionKB, EVENTKB_ACTION_SIZE);
    XF_EventCreate(&EventTR, XF_EVENY_TYPE_INTERRUPT, 0, infoTR, dataInfoTR, EVENTTR_INFO_SIZE, actionTR, EVENTTR_ACTION_SIZE);

    XF_EventAddAct(&EventKB, &ViewAction);

    XF_SMachInitState(&MachLock, &ModeManage);
    XF_EventPackageLoopRun(evtPkg);
}

static void StateInitEntry() {
}

static void StateSleepEntry() {
}

static void ModeLockEntry() {
    //ViewCreate(&vMain, &cMain);
}

static void ModeManageEntry() {
    ViewCreate(0,&vManage);
}

static void ModeFactoryEntry() {
    //ViewStart(&vFactory, &cFactory);
}

static void ModeVendorEntry() {
    //ViewStart(&vVendor, &cVendor);
}

static int ModeLockProcessMsg(XF_Message *msg) {
    return 0;
}
static int ModeManageProcessMsg(XF_Message *msg) {
    return 0;
}
static int ModeFactoryProcessMsg(XF_Message *msg) {
    return 0;
}
static int ModeVendorProcessMsg(XF_Message *msg) {
    return 0;
}