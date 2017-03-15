#ifndef __BGRAPH_H__
#define __BGRAPH_H__

#define STRING_NULL                    "                "
#define STRING_ADD_FP                  "��¼��ָ��"
#define STRING_ADD_PWD                 "��¼������"
#define STRING_ADD_IC                  "��¼��IC��"
#define STRING_INPUT                   "������"
#define STRING_INPUT_PWD               "����������"
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

//#define STRING_MENU


#define DISPLAY_PRINT_BUF_LENGTH       20  //
#define DISPLAY_CURSOR_POS_X		   120  //���xλ��
#define DISPLAY_PRINT_SIZE             16  //��ʾ����ı�λ��
#define DISPLAY_LINE_SIZE              3  //��ʾ�������
#define DISPLAY_X_SIZE                 128  //��ʾ���xλ��
#define DISPLAY_Y_SIZE                 8  //��ʾ���yλ��
#define DISPLAY_CHAR_X_SIZE            8  //�ı���x��С
#define DISPLAY_CHAR_Y_SIZE            2  //�ı���y��С

#define BGRAPH_PIXEL_LENGHT            128
#define BGRAPH_PIXEL_HEIGHT            64
#define BGRAPH_PIXEL_CELL              32

#define BGRAPH_CELL_OFFSET             5  //log2(BGRAPH_PIXEL_CELL)
#define BGRAPH_CELL_SHIFT              0x1f  // 0xff << BGRAPH_CELL_OFFSET

//typedef uint32_t cell;

typedef enum {
    BGRAPH_COLOR_BLACK = (uint8_t)0,
    BGRAPH_COLOR_WHITE,
} BGRAPH_Color;

typedef struct {
    const char *name;  //�ֿ�����
    char *encodeAddr;  //�����ַ
    char *addr;  //�ֿ��ַ
    int size;  //����
    uint8_t fontWidth;  //�����
    uint8_t fontHeight;  //�����
    uint8_t fontSize;  //����������ռ�洢�ռ䣬��λ�ֽ�
} BGRAPH_Font;

typedef struct {
    void **fb;  //framebuffer
    void **fontEN;
    BGRAPH_Font *fontCN;
    uint8_t pixelLenght;
    uint8_t pixelHeight;
    uint8_t pixelOfCharX;
    uint8_t pixelOfCharY;
    uint8_t charLenght;
    uint8_t charHeight;
    uint8_t posX;
    uint8_t posY;
} BGRAPH;

extern int bgraph_set_pixel(BGRAPH *bg, uint8_t x, uint8_t y, BGRAPH_Color color);
extern int bgraph_set_text(BGRAPH *bg, uint8_t x, uint8_t y, char *str, BGRAPH_Color color);
extern int bgraph_refresh(BGRAPH *bg);
extern int bgraph_refresh_area(BGRAPH *bg, uint8_t x, uint8_t y, uint8_t lenght, uint8_t height, BGRAPH_Color color);
extern int bgraph_clear(BGRAPH *bg);

extern int bgraph_set_pos(BGRAPH *bg, uint8_t x, uint8_t y);
extern int bgraph_get_pos(BGRAPH *bg, uint8_t *x, uint8_t *y);
#endif
