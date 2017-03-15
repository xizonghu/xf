#ifndef __BGRAPH_H__
#define __BGRAPH_H__

#define STRING_NULL                    "                "
#define STRING_ADD_FP                  "请录入指纹"
#define STRING_ADD_PWD                 "请录入密码"
#define STRING_ADD_IC                  "请录入IC卡"
#define STRING_INPUT                   "请输入"
#define STRING_INPUT_PWD               "请输入密码"
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

//#define STRING_MENU


#define DISPLAY_PRINT_BUF_LENGTH       20  //
#define DISPLAY_CURSOR_POS_X		   120  //光标x位置
#define DISPLAY_PRINT_SIZE             16  //显示最大文本位置
#define DISPLAY_LINE_SIZE              3  //显示最大行数
#define DISPLAY_X_SIZE                 128  //显示最大x位置
#define DISPLAY_Y_SIZE                 8  //显示最大y位置
#define DISPLAY_CHAR_X_SIZE            8  //文本的x大小
#define DISPLAY_CHAR_Y_SIZE            2  //文本的y大小

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
    const char *name;  //字库名字
    char *encodeAddr;  //内码地址
    char *addr;  //字库地址
    int size;  //字数
    uint8_t fontWidth;  //字体宽
    uint8_t fontHeight;  //字体高
    uint8_t fontSize;  //单个字体所占存储空间，单位字节
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
