#ifndef __MODEL_H__
#define __MODEL_H__

typedef struct {
    void start();
    void sleep();
    void wakeup();
    int unlock(FP_Pwd *pwd);

    int addUser(FP_User *user);
    int removeUser(FP_User *user);
    int findUsers(FP_User *users[], int size, FP_User *user, int startId, int endId);

    int addRule(FP_Rule *rule);
    int removeRule(FP_Rule *rule);

    int addDetails(FP_Detail *detail);
    int findDetails(FP_Detail *Details[], int size, FP_Detail *detail, int startId, int endId);

    //×Ó¹¦ÄÜ
    int setTime(FP_Time *time);
    int setUnlockType(uint8_t type);
    int getUnlockType(uint8_t *pType);
    int resetFactory(uint8_t mode);
    int getUsedStorage();
    int getEvent();
} MODEL_FPlock;

#endif
