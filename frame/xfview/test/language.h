#ifndef __LANGUAGE_H__
#define __LANGUAGE_H__

#define STRING_NULL                    ""
#define STRING_NULL_LINE               "                "
#define STRING_INPUT_FP                "������ָ��"
#define STRING_INPUT_PASSWD            "����������"
#define STRING_INPUT_IC                "������IC��"
#define STRING_INPUT                   "������"
#define STRING_INPUT_AGAIN             "��������һ��"
#define STRING_INPUT_TIME              "������ʱ��"
#define STRING_INPUT_ADMIN             "���������Ա"

#define STRING_INPUT_SUCCESS           "����ɹ�"
#define STRING_INPUT_FAIL              "����ʧ��"
#define STRING_INPUT_OK                "������ȷ"
#define STRING_INPUT_ERR               "�������"
#define STRING_INPUT_INVALID           "������Ч"
#define STRING_EXEC_SUCCESS            "ɾ���ɹ�"
#define STRING_EXEC_FAIL               "ɾ��ʧ��"
#define STRING_SET_SUCCESS             "���óɹ�"
#define STRING_SET_FAIL                "����ʧ��"


#define STRING_EXIST_INFO              "�Ѵ�����Ϣ"
#define STRING_NULL_INFO               "����Ϣ"
#define STRING_FULL_INFO               "��Ϣ����"
#define STRING_STORED                  "�Ѵ洢"
#define STRING_STORE_FULL              "�洢����"

#define STRING_TIME_VALID              "ʱ��ʧЧ"

#define STRING_UNLOCKED                "�ѿ���"

#define STRING_TIME_START              "��ʼʱ��"
#define STRING_TIME_END                "����ʱ��"

#define STRING_UNLOCK_TYPE_SINGLE      "ָ��/����/IC��"  //"ָ��/����/IC��"
#define STRING_UNLOCK_TYPE_FP_NUM      "ָ��+����"
#define STRING_UNLOCK_TYPE_FP_FP       "ָ��+ָ��"
#define STRING_UNLOCK_TYPE_NUM_NUM     "����+����"
#define STRING_PWD_TYPE_FP             "ָ��"
#define STRING_PWD_TYPE_TEXT           "����"
#define STRING_PWD_TYPE_IC             "IC��"
#define STRING_USER_GROUP_ADMIN        "����"
#define STRING_USER_GROUP_GUSET        "�û�"

#define STRING_BATTERY_POWER_LOW       "������!"
#define STRING_WARNING_SYS_LOCK        "ϵͳ����"



#define STRING_UNLOCK_TYPE             "��������"

#define STRING_RESET_SYSTEM            "�ָ���������"
#define STRING_SET_ADMIN               "���ù���Ա"
#define STRING_MANAGE                  "��������"

//����
#define STRING_ADMIN                   "����Ա"
#define STRING_GUEST                   "��Ա"

//�˵�
#define STRING_ADD_USER                "¼���û�"
#define STRING_REMOVE_USER             "ɾ���û�"
#define STRING_SETTINGS                "ϵͳ����"
#define STRING_STORAGE                 "�洢ͳ��"
#define STRING_ADD_ADMIN               "¼�����Ա"
#define STRING_ADD_GUEST               "¼���Ա"
#define STRING_ADD_PWD                 "¼������"
#define STRING_ADD_ADMIN_PASSWD        "¼���������"
#define STRING_ADD_ADMIN_FP            "¼�����ָ��"
#define STRING_ADD_GUEST_PASSWD        "¼���Ա����"
#define STRING_ADD_GUEST_FP            "¼���Աָ��"
#define STRING_REMOVE_ADMIN            "ɾ������Ա"
#define STRING_REMOVE_GUEST            "ɾ����Ա"
#define STRING_SET_TIME                "ʱ������"
#define STRING_SET_TYPE_UNLOCK         "��������"
#define STRING_SYS_VERSION             "ϵͳ�汾"
#define STRING_RESET_FACTORY           "�ָ����ó���"
#define STRING_QUERY_TRACE             "��¼��ѯ"


//����
#define STRING_PLEASE_INPUT_PASSWD     "��¼������:"
#define STRING_TYPE_UNLOCK_FP          "ָ��"
#define STRING_TYPE_UNLOCK_ANY         "ָ��/����/IC��"
#define STRING_TYPE_UNLOCK_FP_FP       "ָ��+ָ��"
#define STRING_TYPE_UNLOCK_FP_CH       "ָ��+����"
#define STRING_TYPE_UNLOCK_CH_CH       "����+����"

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
