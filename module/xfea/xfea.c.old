#include "xftypedef.h"
#include "xfea.h"

static int8 indexOf(XF_Event *evt, XF_Action *act) {
    uint8 i = 0;
    for(i = 0; i < evt->sizeActions; i++) {
        XF_Action *p;
		p = evt->actions[i];
		if(0 == p) continue;
        if(0 == strcmp(p->name, act->name)) {
            return (int8)i;
        }
    }
    return -1;
}

void XF_EventCreate(XF_Event *evt, XF_EventType type, XF_event_query_callback query, XF_Info infos[], XF_Memory dataInfos[], uint8 sizeInfos, XF_Action *actions[], uint8 sizeActions) {
    uint8 i = 0;

    evt->type = type;
    evt->query = query;

    evt->infos = infos;
    evt->sizeInfos = sizeInfos;
    evt->posInfos = 0;
    for(i = 0; i < evt->sizeInfos; i++) {
        evt->infos[i].data = (void *)&dataInfos[i];
        evt->infos[i].size = 0;
    }

    evt->actions = actions;
    evt->sizeActions = sizeActions;
    for(i = 0; i < evt->sizeActions; i++) {
        evt->actions[i] = 0;
    }
}

int8 XF_EventAddAct(XF_Event *evt, XF_Action *act) {
    uint8 i = 0;
    if(0 <= indexOf(evt, act)) {
        return -1;
    }

    for(i = 0; i < evt->sizeActions; i++) {
        if(0 == evt->actions[i]) {
            evt->actions[i] = act;
            return 0;
        }
    }

    return -2;
}

int8 XF_EventRemoveAct(XF_Event *evt, XF_Action *act) {
    int8 i = 0;
    if(0 > (i = indexOf(evt, act))) return -1;
    evt->actions[i] = 0;

    return 0;
}

void XF_EventNotifyAct(XF_Event *evt, XF_Info *info) {
    uint8 i = 0;

    for(i = 0; i < evt->sizeActions; i++) {
        XF_Action *act;
        act = evt->actions[i];
        if(0 == act) continue;
        if(0 == act->handler) continue;
        act->handler(info);
    }
}

void XF_EventNotifyActSync(XF_Event *evt, XF_Info *info) {
    uint8 i = 0;

    for(i = 0; i < evt->sizeActions; i++) {
        XF_Action *act;
        act = evt->actions[i];
        if(0 == act) continue;
        if(0 == act->handler) continue;
        act->handler(info);
    }
}

void XF_EventNotifyActAsyn(XF_Event *evt, XF_Info *info) {
    if(evt->posInfos >= evt->sizeInfos) return;
    evt->infos[evt->posInfos].size = info->size;
    memcpy(evt->infos[evt->posInfos].data, info->data, info->size);
    evt->posInfos++;
}

uint8 XF_EventExecuteAct(XF_Event *evt) {
    uint8 cnt = 0;
    uint8 i = 0, j = 0;

    for(j = 0; j < evt->posInfos; j++) {
        for(i = 0; i < evt->sizeActions; i++) {
            XF_Action *act;
            act = evt->actions[i];
            if(0 == act) continue;
            if(0 == act->handler) continue;
            act->handler(&evt->infos[j]);
            cnt++;
        }
    }
    evt->posInfos = 0;
    return cnt;
}

uint8 XF_EventPackageDispatch(XF_EventPackage evtPkg) {
    uint8 cnt = 0;

    uint8 i = 0;
    for(i = 0; i < evtPkg.size; i++) {
        XF_Event *evt = evtPkg.events[i];
        if(0 == evt->posInfos) continue;
        cnt += XF_EventExecuteAct(evt);
    }
    return cnt;
}

void XF_EventPackageQuery(XF_EventPackage evtPkg) {
    uint8 i = 0;
    for(i = 0; i < evtPkg.size; i++) {
        XF_Event *evt = evtPkg.events[i];
        if(0 == evt->query) continue;
        evt->query();
    }
}

void XF_EventPackageLoopRun(XF_EventPackage evtPkg) {
    while(1) {
        if(XF_EventPackageDispatch(evtPkg)) continue;
        XF_EventPackageQuery(evtPkg);
    }
}