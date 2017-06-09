#ifndef __LANGUAGE_H__
#define __LANGUAGE_H__

#define STRING_NULL                    ""
#define STRING_NULL_LINE               "                "
#define STRING_INPUT_FP                "请输入指纹"
#define STRING_INPUT_PASSWD            "请输入密码"
#define STRING_INPUT_IC                "请输入IC卡"
#define STRING_INPUT                   "请输入"
#define STRING_INPUT_AGAIN             "请再输入一次"
#define STRING_INPUT_TIME              "请输入时间"
#define STRING_INPUT_ADMIN             "请输入管理员"

#define STRING_INPUT_SUCCESS           "输入成功"
#define STRING_INPUT_FAIL              "输入失败"
#define STRING_INPUT_OK                "输入正确"
#define STRING_INPUT_ERR               "输入错误"
#define STRING_INPUT_INVALID           "输入无效"
#define STRING_EXEC_SUCCESS            "删除成功"
#define STRING_EXEC_FAIL               "删除失败"
#define STRING_SET_SUCCESS             "设置成功"
#define STRING_SET_FAIL                "设置失败"


#define STRING_EXIST_INFO              "已存在信息"
#define STRING_NULL_INFO               "无信息"
#define STRING_FULL_INFO               "信息已满"
#define STRING_STORED                  "已存储"
#define STRING_STORE_FULL              "存储已满"

#define STRING_TIME_VALID              "时间失效"

#define STRING_UNLOCKED                "已开锁"

#define STRING_TIME_START              "开始时间"
#define STRING_TIME_END                "结束时间"

#define STRING_UNLOCK_TYPE_SINGLE      "指纹/密码/IC卡"  //"指纹/密码/IC卡"
#define STRING_UNLOCK_TYPE_FP_NUM      "指纹+密码"
#define STRING_UNLOCK_TYPE_FP_FP       "指纹+指纹"
#define STRING_UNLOCK_TYPE_NUM_NUM     "密码+密码"
#define STRING_PWD_TYPE_FP             "指纹"
#define STRING_PWD_TYPE_TEXT           "密码"
#define STRING_PWD_TYPE_IC             "IC卡"
#define STRING_USER_GROUP_ADMIN        "管理"
#define STRING_USER_GROUP_GUSET        "用户"

#define STRING_BATTERY_POWER_LOW       "电量低!"
#define STRING_WARNING_SYS_LOCK        "系统已锁"



#define STRING_UNLOCK_TYPE             "开锁类型"

#define STRING_RESET_SYSTEM            "恢复出厂设置"
#define STRING_SET_ADMIN               "设置管理员"
#define STRING_MANAGE                  "管理设置"

//单词
#define STRING_ADMIN                   "管理员"
#define STRING_GUEST                   "成员"

//菜单
#define STRING_ADD_USER                "录入用户"
#define STRING_REMOVE_USER             "删除用户"
#define STRING_SETTINGS                "系统设置"
#define STRING_STORAGE                 "存储统计"
#define STRING_ADD_ADMIN               "录入管理员"
#define STRING_ADD_GUEST               "录入成员"
#define STRING_ADD_PWD                 "录入密码"
#define STRING_ADD_ADMIN_PASSWD        "录入管理密码"
#define STRING_ADD_ADMIN_FP            "录入管理指纹"
#define STRING_ADD_GUEST_PASSWD        "录入成员密码"
#define STRING_ADD_GUEST_FP            "录入成员指纹"
#define STRING_REMOVE_ADMIN            "删除管理员"
#define STRING_REMOVE_GUEST            "删除成员"
#define STRING_SET_TIME                "时间设置"
#define STRING_SET_TYPE_UNLOCK         "开锁设置"
#define STRING_SYS_VERSION             "系统版本"
#define STRING_RESET_FACTORY           "恢复设置出厂"
#define STRING_QUERY_TRACE             "记录查询"


//界面
#define STRING_PLEASE_INPUT_PASSWD     "请录入密码:"
#define STRING_TYPE_UNLOCK_FP          "指纹"
#define STRING_TYPE_UNLOCK_ANY         "指纹/密码/IC卡"
#define STRING_TYPE_UNLOCK_FP_FP       "指纹+指纹"
#define STRING_TYPE_UNLOCK_FP_CH       "指纹+密码"
#define STRING_TYPE_UNLOCK_CH_CH       "密码+密码"

//#define STRING_MENU_


extern char DISPLAY_STRING_NULL[sizeof(STRING_NULL)];
extern char DISPLAY_STRING_ADD_PWD[sizeof(STRING_ADD_PWD)];
extern char DISPLAY_STRING_INPUT_PWD[sizeof(STRING_INPUT_PASSWD)];
extern char DISPLAY_STRING_INPUT_AGAIN[sizeof(STRING_INPUT_AGAIN)];
extern char DISPLAY_STRING_INPUT_SUCCESS[sizeof(STRING_INPUT_SUCCESS)];
extern char DISPLAY_STRING_INPUT_FAIL[sizeof(STRING_INPUT_FAIL)];
extern char DISPLAY_STRING_INPUT_OK[sizeof(STRING_INPUT_OK)];
extern char DISPLAY_STRING_INPUT_ERR[sizeof(STRING_INPUT_ERR)];
extern char DISPLAY_STRING_EXIST_INFO[sizeof(STRING_EXIST_INFO)];
extern char DISPLAY_STRING_STORE_FULL[sizeof(STRING_STORE_FULL)];




#endif
