/* Copyright 2023 Dual Tachyon
 * https://github.com/DualTachyon
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 */

#include <string.h>
#include <stdlib.h>  // abs()
#include "bitmaps.h"

#include "app/dtmf.h"
#include "app/menu.h"
#include "board.h"
#include "dcs.h"
#include "driver/backlight.h"
#include "driver/bk4819.h"
#include "driver/st7565.h"
#include "external/printf/printf.h"
#include "frequencies.h"
#include "helper/battery.h"
#include "misc.h"
#include "settings.h"
#include "ui/helper.h"
#include "ui/inputbox.h"
#include "ui/menu.h"
#include "ui/ui.h"


const t_menu_item MenuList[] =
        {
//   text,     voice ID,                               menu ID
                {/*"Step",*/   VOICE_ID_FREQUENCY_STEP,                MENU_STEP          ,"\x01\x02\x03\x04"},
                {/*"TxPwr",*/  VOICE_ID_POWER,                         MENU_TXP           ,"\x05\x06\x07\x04"}, // was "TXP"
                {/*"RxDCS",*/  VOICE_ID_DCS,                           MENU_R_DCS         ,"\x08\x09\x0B\x0C\x0D\x0E"}, // was "R_DCS"
                {/*"RxCTCS",*/ VOICE_ID_CTCSS,                         MENU_R_CTCS        ,"\x08\x09\x0F\x10\x0D\x0E"}, // was "R_CTCS"
                {/*"TxDCS",*/  VOICE_ID_DCS,                           MENU_T_DCS         ,"\x05\x11\x0B\x0C\x0D\x0E"}, // was "T_DCS"
                {/*"TxCTCS",*/ VOICE_ID_CTCSS,                         MENU_T_CTCS        ,"\x05\x11\x0F\x10\x0D\x0E"}, // was "T_CTCS"
                {/*"TxODir",*/ VOICE_ID_TX_OFFSET_FREQUENCY_DIRECTION, MENU_SFT_D         ,"\x03\x12\x13\x14"}, // was "SFT_D"
                {/*"TxOffs",*/ VOICE_ID_TX_OFFSET_FREQUENCY,           MENU_OFFSET        ,"\x03\x12\x03\x04"}, // was "OFFSET"
                {/*"W/N",*/    VOICE_ID_CHANNEL_BANDWIDTH,             MENU_W_N           ,"\x15\x16\x17\x18\x19"},
                {/*"Scramb",*/ VOICE_ID_SCRAMBLER_ON,                  MENU_SCR           ,"\x1A\x1B\x1C\x1D"}, // was "SCR"
                {/*"BusyCL",*/ VOICE_ID_BUSY_LOCKOUT,                  MENU_BCL           ,"\x1E\x1F\xE5\x05"}, // was "BCL"
                {/*"Compnd",*/ VOICE_ID_INVALID,                       MENU_COMPAND       ,"\x7F\x80"},
                {/*"Demodu",*/ VOICE_ID_INVALID,                       MENU_AM            ,"\x81\x82\x0F\x83"}, // was "AM"
                {/*"ScAdd1",*/ VOICE_ID_INVALID,                       MENU_S_ADD1        ,"\x84\x85\x86\x87\x31"},
                {/*"ScAdd2",*/ VOICE_ID_INVALID,                       MENU_S_ADD2        ,"\x84\x85\x86\x87\x32"},
                {/*"ChSave",*/ VOICE_ID_MEMORY_CHANNEL,                MENU_MEM_CH        ,"\x88\x19\x89\x8A"}, // was "MEM-CH"
                {/*"ChDele",*/ VOICE_ID_DELETE_CHANNEL,                MENU_DEL_CH        ,"\x8B\x8C\x89\x8A"}, // was "DEL-CH"
                {/*"ChName",*/ VOICE_ID_INVALID,                       MENU_MEM_NAME      ,"\x8D\x8E\x89\x8A"},

                {/*"SList",*/  VOICE_ID_INVALID,                       MENU_S_LIST        ,"\x89\x8A\x8F\x90\x86\x87"},
                {/*"SList1",*/ VOICE_ID_INVALID,                       MENU_SLIST1        ,"\x8F\x90\x86\x87\x31"},
                {/*"SList2",*/ VOICE_ID_INVALID,                       MENU_SLIST2        ,"\x8F\x90\x86\x87\x32"},
                {/*"ScnRev",*/ VOICE_ID_INVALID,                       MENU_SC_REV        ,"\x84\x85\x91\x92\x0F\x83"},
#ifdef ENABLE_NOAA//0
                {/*"NOAA-S",*/ VOICE_ID_INVALID,                       MENU_NOAA_S        ,""},
#endif

                {/*"F1Shrt",*/    VOICE_ID_INVALID,                    MENU_F1SHRT        ,"\x93\x94\x95\x96\x31"},
                {/*"F1Long",*/    VOICE_ID_INVALID,                    MENU_F1LONG        ,"\x97\x94\x95\x96\x31"},
                {/*"F2Shrt",*/    VOICE_ID_INVALID,                    MENU_F2SHRT        ,"\x93\x94\x95\x96\x32"},
                {/*"F2Long",*/    VOICE_ID_INVALID,                    MENU_F2LONG        ,"\x97\x94\x95\x96\x32"},
                {/*"M Long",*/    VOICE_ID_INVALID,                    MENU_MLONG         ,"\x97\x94\x4D\x96"},

                {/*"KeyLck",*/ VOICE_ID_INVALID,                       MENU_AUTOLK        ,"\x96\x98\x99\x9A\x9B\x9C"}, // was "AUTOLk"
                {/*"TxTOut",*/ VOICE_ID_TRANSMIT_OVER_TIME,            MENU_TOT           ,"\x05\x11\x9D\x9E"}, // was "TOT"
                {/*"BatSav",*/ VOICE_ID_SAVE_MODE,                     MENU_SAVE          ,"\x9F\xA0\x0F\x83"}, // was "SAVE"
                {/*"Mic",*/    VOICE_ID_INVALID,                       MENU_MIC           ,"\xA1\xA2\xA3\xA4\xA5"},
#ifdef ENABLE_AUDIO_BAR//1
                {/*"MicBar",*/ VOICE_ID_INVALID,                       MENU_MIC_BAR       ,"\xA1\xA2\xA3\xA6\xA7\xA8"},

#endif
                {/*"ChDisp",*/ VOICE_ID_INVALID,                       MENU_MDF           ,"\x89\x8A\xA6\xA7\x0F\x83"}, // was "MDF"
                {/*"POnMsg",*/ VOICE_ID_INVALID,                       MENU_PONMSG        ,"\xA9\xAA\x89\xAB"},
                {/*"BatTxt",*/ VOICE_ID_INVALID,                       MENU_BAT_TXT       ,"\xA0\xAC\xA6\xA7"},
                {/*"BackLt",*/ VOICE_ID_INVALID,                       MENU_ABR           ,"\x99\x9A\xAD\xAE"}, // was "ABR"
                {/*"BLMin",*/  VOICE_ID_INVALID,                       MENU_ABR_MIN       ,"\xAF\xB0\xB1\xB2"},
                {/*"BLMax",*/  VOICE_ID_INVALID,                       MENU_ABR_MAX       ,"\xAF\xB3\xB1\xB2"},
                {/*"BltTRX",*/ VOICE_ID_INVALID,                       MENU_ABR_ON_TX_RX  ,"\xAD\xAE\xA9\xB4"},
                {/*"Beep",*/   VOICE_ID_BEEP_PROMPT,                   MENU_BEEP          ,"\x96\x98\x94\x96\x0E"},
#ifdef ENABLE_VOICE//0
                {/*"Voice",*/  VOICE_ID_VOICE_PROMPT,                  MENU_VOICE         ,""},
#endif
                {/*"Roger",*/  VOICE_ID_INVALID,                       MENU_ROGER         ,"\x05\x11\xB5\xB6\x0E"},
                {/*"STE",*/    VOICE_ID_INVALID,                       MENU_STE           ,"\xB7\x0E\xB8\x8C"},
                {/*"RP STE",*/ VOICE_ID_INVALID,                       MENU_RP_STE        ,"\xB9\xBA\xBB\xB7\x0E\xB8\x8C"},
                {/*"1 Call",*/ VOICE_ID_INVALID,                       MENU_1_CALL        ,"\xBC\x96\xBD\xBE"},
#ifdef ENABLE_ALARM//0
                {/*"AlarmT",*/ VOICE_ID_INVALID,                       MENU_AL_MOD        ,""},
#endif
                {/*"ANI ID",*/ VOICE_ID_ANI_CODE,                      MENU_ANI_ID        ,"\xBF\xC0\xC1"},
                {/*"UPCode",*/ VOICE_ID_INVALID,                       MENU_UPCODE        ,"\x44\x54\x4D\x46\xC2\xC3\xC1"},
                {/*"DWCode",*/ VOICE_ID_INVALID,                       MENU_DWCODE        ,"\x44\x54\x4D\x46\xC4\xC3\xC1"},
                {/*"PTT ID",*/ VOICE_ID_INVALID,                       MENU_PTT_ID        ,"\x44\x54\x4D\x46\x05\x11"},
                {/*"D ST",*/   VOICE_ID_INVALID,                       MENU_D_ST          ,"\x44\x54\x4D\x46\x95\x0E"},
                {/*"D Resp",*/ VOICE_ID_INVALID,                       MENU_D_RSP         ,"\x44\x54\x4D\x46\xC5\xC6"},
                {/*"D Hold",*/ VOICE_ID_INVALID,                       MENU_D_HOLD        ,"\x44\x54\x4D\x46\x92\xC7"},
                {/*"D Prel",*/ VOICE_ID_INVALID,                       MENU_D_PRE         ,"\x44\x54\x4D\x46\xC8\xC9\xCA"},
                {/*"D Decd",*/ VOICE_ID_INVALID,                       MENU_D_DCD         ,"\x44\x54\x4D\x46\xCB\xC1"},
                {/*"D List",*/ VOICE_ID_INVALID,                       MENU_D_LIST        ,"\x44\x54\x4D\x46\xCC\xCD\xCE"},
                {/*"D Live",*/ VOICE_ID_INVALID,                       MENU_D_LIVE_DEC    ,"\x44\x54\x4D\x46\xA6\xA7"}, // live DTMF decoder
#ifdef ENABLE_AM_FIX//1
                {/*"AM Fix",*/ VOICE_ID_INVALID,                       MENU_AM_FIX        ,"\x41\x4D\x99\x9A\xA4\xA5"},
#endif
#ifdef ENABLE_AM_FIX_TEST1//0
                {/*"AM FT1",*/ VOICE_ID_INVALID,                       MENU_AM_FIX_TEST1  ,""},
#endif
#ifdef ENABLE_VOX//1
                {/*"VOX",*/    VOICE_ID_VOX,                           MENU_VOX           ,"\xCF\xD0\x05\x06"},
#endif
                {/*"BatVol",*/ VOICE_ID_INVALID,                       MENU_VOL           ,"\xA0\xAC\xA0\x7F"}, // was "VOL"
                {/*"RxMode",*/ VOICE_ID_DUAL_STANDBY,                  MENU_TDR           ,"\x09\x05\x0F\x83"},
                {/*"Sql",*/    VOICE_ID_SQUELCH,                       MENU_SQL           ,"\xD1\xD2\xD3\xD4"},

                // hidden menu items from here on
                // enabled if pressing both the PTT and upper side button at power-on
                {/*"F Lock",*/ VOICE_ID_INVALID,                       MENU_F_LOCK        ,"\xD5\x9C\xD6\xD7\x03\xD8"},
                {/*"Tx 200",*/ VOICE_ID_INVALID,                       MENU_200TX         ,"\x32\x30\x30\x4D\x05\x06"}, // was "200TX"
                {/*"Tx 350",*/ VOICE_ID_INVALID,                       MENU_350TX         ,"\x33\x35\x30\x4D\x05\x06"}, // was "350TX"
                {/*"Tx 500",*/ VOICE_ID_INVALID,                       MENU_500TX         ,"\x35\x30\x30\x4D\x05\x06"}, // was "500TX"
                {/*"350 En",*/ VOICE_ID_INVALID,                       MENU_350EN         ,"\x33\x35\x30\x4D\x08\x09"}, // was "350EN"
                {/*"ScraEn",*/ VOICE_ID_INVALID,                       MENU_SCREN         ,"\x1A\x1B\xA9\xD9"}, // was "SCREN"
#ifdef ENABLE_F_CAL_MENU//0
                {/*"FrCali",*/ VOICE_ID_INVALID,                       MENU_F_CALI        ,""}, // reference xtal calibration
#endif
                {/*"BatCal",*/ VOICE_ID_INVALID,                       MENU_BATCAL        ,"\xA0\xAC\x81\x7F"}, // battery voltage calibration
                {/*"BatTyp",*/ VOICE_ID_INVALID,                       MENU_BATTYP        ,"\xA0\xAC\xB3\xB0"}, // battery type 1600/2200mAh
                {/*"Reset",*/  VOICE_ID_INITIALISATION,                MENU_RESET         ,"\xDA\x0B\x92\xC7"}, // might be better to move this to the hidden menu items ?

                {/*"",*/       VOICE_ID_INVALID,                       0xff               ,"\x00"}  // end of list - DO NOT delete or move this this
        };


const uint8_t FIRST_HIDDEN_MENU_ITEM = MENU_F_LOCK;

const char gSubMenu_TXP[][2] =//5
        {
//                "LOW",
//                "MID",
//                "HIGH"
"\xDB","\xBA","\xDC"
        };

const char gSubMenu_SFT_D[][11] =//4
        {
//                "OFF",
//                "+",
//                "-"
                "\x05\x11=\x08\x09",
                "\x05\x11=\x0a\x08\x09+\xDD\xDE",
                "\x05\x11=\x0a\x08\x09-\xDD\xDE"

        };

const char gSubMenu_W_N[][3] =//7
        {
//                "WIDE",
//                "NARROW"
                "\x15\x03",
                "\x16\x03"
        };

const char gSubMenu_OFF_ON[][3] =//4
        {
//                "OFF",
//                "ON"
                "\xD9\xDF",
                "\xA9\xB4"
        };

const char gSubMenu_SAVE[][4] =//4
        {
//                "OFF",
//                "1:1",
//                "1:2",
//                "1:3",
//                "1:4"

                "\xD9\xDF",
                "1 \xD4",
                "2 \xD4",
                "3 \xD4",
                "4 \xD4"

        };

const char gSubMenu_TOT[][5] = //7
        {
//                "30 sec",
//                "1 min",
//                "2 min",
//                "3 min",
//                "4 min",
//                "5 min",
//                "6 min",
//                "7 min",
//                "8 min",
//                "9 min",
//                "15 min"

                    "30 \xFE",
                            "1 \xFD",
                            "2 \xFD",
                            "3 \xFD",
                            "4 \xFD",
                            "5 \xFD",
                            "6 \xFD",
                            "7 \xFD",
                            "8 \xFD",
                            "9 \xFD",
                            "15 \xFD"

        };

const char *gSubMenu_RXMode[] =
        {

//                "MAIN\nONLY",        // TX and RX on main only
//                "DUAL RX\nRESPOND", // Watch both and respond
//                "CROSS\nBAND",        // TX on main, RX on secondary
//                "MAIN TX\nDUAL RX"    // always TX on main, but RX on both
                "\xE0\x89\x8A\n\x08\x09\x05\x06",        // TX and RX on main only
                "\xE1\x89\x8A\n\x08\x09", // Watch both and respond
                "\xE0\x89\x8A\x05\x06\n\xE2\x89\x8A\x08\x09",        // TX on main, RX on secondary
                "\xE0\x89\x8A\x05\x06\n\xE1\x89\x8A\x08\x09"    // always TX on main, but RX on both

        };

#ifdef ENABLE_VOICE
const char gSubMenu_VOICE[][4] =
{
    "OFF",
    "CHI",
    "ENG"
};
#endif

const char gSubMenu_SC_REV[][10] =//8
        {
//                "TIMEOUT",
//                "CARRIER",
//                "STOP"
                "\x1E\x89\xE3\n\x35\xFE\xE4\x84\x85",//遇信号  \n5秒后搜索

                "\x89\xE3\xE6\xE7\xE4\x0a\x84\x85", //信号停止后搜索

                "\x1E\x89\xE3\xE4\x0a\xE6\xE7\x84\x85"//遇信号后停止搜索
//                "\xEA\xD6\xC5\xEB",
//                "\xEC\x92\xC5\xC6",
//                "\xEA\xD6\xC5\xEB\n\xEC\x92\xC5\xC6"
        };

const char *gSubMenu_MDF[] =
        {
//                "FREQ",
//                "CHANNEL\nNUMBER",
//                "NAME",
//                "NAME\n+\nFREQ"
                "\x03\x04",
                "\x89\x8A\xE3",
                "\x8E\xE8",
                "\x8E\xE8\n+\x03\x04"
        };

#ifdef ENABLE_ALARM
const char gSubMenu_AL_MOD[][5] =
{
    "SITE",
    "TONE"
};
#endif

const char gSubMenu_D_RSP[][10] =//11
        {
//                "DO\nNOTHING",
//                "RING",
//                "REPLY",
//                "BOTH"
                "\xE9\xC5\xC6",
                "\xEA\xD6\xC5\xEB",
                "\xEC\x92\xC5\xC6",
                "\xEA\xD6\xC5\xEB\n\xEC\x92\xC5\xC6"
        };

const char *gSubMenu_PTT_ID[] =
        {
//                "OFF",
//                "UP CODE",
//                "DOWN CODE",
//                "UP+DOWN\nCODE",
//                "APOLLO\nQUINDAR"
                "\xE9\x05\x11",
                "\xC2\xC3\xC1",
                "\xC4\xC3\xC1",
                "\xC2\xC3\x2B\xC4\xC3\xC1",
                "\x51\x75\x69\x6E\x64\x61\x72\xC1"
        };

const char gSubMenu_PONMSG[][5] =//8
        {
//                "FULL",
//                "MESSAGE",
//                "VOLTAGE",
//                "NONE"
                "\xED\xEE\xA6\xA7",
                "\x89\xAB\xA6\xA7",
                "\xA0\x7F\xA6\xA7",
                "\xE9\xA6\xA7"
        };

const char gSubMenu_ROGER[][9] =
        {
//                "OFF",
//                "ROGER",
//                "MDC"

                "\xD9\xDF\xB5\xB6\x0E",
                "ROGER\xB5\xB6\x0E",
                "\x4D\x44\x43\xEF\xF0"
        };

const char gSubMenu_RESET[][6] =//4
        {
//                "VFO",
//                "ALL"
                "\x8C\x89\x8A\xDA\x0B",
                "\xF1\xF2\xDA\x0B"
        };

const char *gSubMenu_F_LOCK[] =
        {
                "DEFAULT+\n137-174\n400-470",
                "FCC HAM\n144-148\n420-450",
                "CE HAM\n144-146\n430-440",
                "GB HAM\n144-148\n430-440",
                "137-174\n400-430",
                "137-174\n400-438",
//                "DISABLE\nALL",
//                "UNLOCK\nALL",
                "\xE5\xF3\xED\xEE",
                "\xCB\x9B\xED\xEE",
        };

const char gSubMenu_BACKLIGHT[][5] =//7
        {
//                "OFF",
//                "5 sec",
//                "10 sec",
//                "20 sec",
//                "1 min",
//                "2 min",
//                "4 min",
//                "ON"
                "\xD9\xDF",
                "5 \xFE",
                "10 \xFE",
                "20 \xFE",
                "1 \xFD",
                "2 \xFD",
                "4 \xFD",
                "\xD9\xDF"

        };

const char gSubMenu_RX_TX[][7] =//6
        {
//                "OFF",
//                "TX",
//                "RX",
//                "TX/RX"
                "\xD9\xDF",
                "\x05\x11\x9E",
                "\x08\x09\x9E",
                "\x05\x11\x2F\x08\x09\x9E"
        };

#ifdef ENABLE_AM_FIX_TEST1
const char gSubMenu_AM_fix_test1[][8] =
{
    "LNA-S 0",
    "LNA-S 1",
    "LNA-S 2",
    "LNA-S 3"
};
#endif

const char gSubMenu_BAT_TXT[][3] =//8
        {
//                "NONE",
//                "VOLTAGE",
//                "PERCENT"
                "\xD9\xDF",
                "\xA0\x7F",
                "\xF4\xF5"
        };

const char gSubMenu_BATTYP[][9] =
        {
                "1600mAh",
                "2200mAh"
        };

const char gSubMenu_SCRAMBLER[][7] =
        {
//                "OFF",
                "\xD9\xDF",

                "2600Hz",
                "2700Hz",
                "2800Hz",
                "2900Hz",
                "3000Hz",
                "3100Hz",
                "3200Hz",
                "3300Hz",
                "3400Hz",
                "3500Hz"
        };

const t_sidefunction SIDEFUNCTIONS[] =
        {
//                {"NONE", ACTION_OPT_NONE},
//                {"FLASH\nLIGHT", ACTION_OPT_FLASHLIGHT},
//                {"POWER", ACTION_OPT_POWER},
//                {"MONITOR", ACTION_OPT_MONITOR},
//                {"SCAN", ACTION_OPT_SCAN},
                {"\xE5\xF3", ACTION_OPT_NONE},
                {"\xF6\xA0\xF7", ACTION_OPT_FLASHLIGHT},
                {"\xF8\x19\x05\x06\x07\x04", ACTION_OPT_POWER},
                {"\xF9\xFA", ACTION_OPT_MONITOR},
                {"\x8F\x90", ACTION_OPT_SCAN},
#ifdef ENABLE_VOX
//                {"VOX",				ACTION_OPT_VOX},
  {"\xCF\xD0\x05\x06\xA9\xD9",				ACTION_OPT_VOX},
#endif
#ifdef ENABLE_ALARM
                {"ALARM",			ACTION_OPT_ALARM},
#endif
#ifdef ENABLE_FMRADIO
//                {"FM RADIO",		ACTION_OPT_FM},
                                {"\x46\x4D\x09\x0E\xAA",		ACTION_OPT_FM},

#endif
#ifdef ENABLE_TX1750
                {"1750HZ",			ACTION_OPT_1750},
#endif
//                {"LOCK\nKEYPAD", ACTION_OPT_KEYLOCK},
//                {"SWITCH\nVFO", ACTION_OPT_A_B},
//                {"VFO/MR", ACTION_OPT_VFO_MR},
//                {"SWITCH\nDEMODUL", ACTION_OPT_SWITCH_DEMODUL},
                {"\x9B\x9C\x96\x98", ACTION_OPT_KEYLOCK},
                {"\xFB\xFC\x89\x8A", ACTION_OPT_A_B},
                {"\x03\x04\x2F\x89\x8A\x0F\x83", ACTION_OPT_VFO_MR},
                {"\xFB\xFC\x81\x82\x0F\x83", ACTION_OPT_SWITCH_DEMODUL},
#ifdef ENABLE_BLMIN_TMP_OFF
                {"BLMIN\nTMP OFF",  ACTION_OPT_BLMIN_TMP_OFF}, 		//BackLight Minimum Temporay OFF
#endif
        };
const t_sidefunction *gSubMenu_SIDEFUNCTIONS = SIDEFUNCTIONS;
const uint8_t gSubMenu_SIDEFUNCTIONS_size = ARRAY_SIZE(SIDEFUNCTIONS);

bool gIsInSubMenu;
uint8_t gMenuCursor;

int UI_MENU_GetCurrentMenuId() {
    if (gMenuCursor < ARRAY_SIZE(MenuList))
        return MenuList[gMenuCursor].menu_id;
    else
        return MenuList[ARRAY_SIZE(MenuList) - 1].menu_id;
}

uint8_t UI_MENU_GetMenuIdx(uint8_t id) {
    for (uint8_t i = 0; i < ARRAY_SIZE(MenuList); i++)
        if (MenuList[i].menu_id == id)
            return i;
    return 0;
}

int32_t gSubMenuSelection;

// edit box
char edit_original[17]; // a copy of the text before editing so that we can easily test for changes/difference
char edit[17];
int edit_index;


void UI_DisplayMenu(void) {
    const unsigned int menu_list_width = 6; // max no. of characters on the menu list (left side)
    const unsigned int menu_item_x1 = (8 * menu_list_width) ;//+ 2;
    const unsigned int menu_item_x2 = LCD_WIDTH - 1;
    unsigned int i;
    char String[64];  // bigger cuz we can now do multi-line in one string (use '\n' char)
    char Contact[16];

    // clear the screen buffer
    memset(gFrameBuffer, 0, sizeof(gFrameBuffer));

#if 1
    // original menu layout



    // invert the current menu list item pixels反转当前菜单项的像素值 ：


    // draw vertical separating dotted line绘制垂直分隔的点线 ：
//    for (i = 0; i < 7; i++)
//        gFrameBuffer[i][(8 * menu_list_width) + 1] = 0xAA;


    // draw the little sub-menu triangle marker绘制子菜单三角标志：
    //const void *BITMAP_CurrentIndicator = BITMAP_MARKER;

    if (gIsInSubMenu)
        memmove(gFrameBuffer[2] + 40, BITMAP_MARKER, sizeof(BITMAP_MARKER));

    // draw the menu index number/count绘制菜单索引号/总数 ：
    sprintf(String, "%2u/%u", 1 + gMenuCursor, gMenuListCount);
    UI_PrintStringSmall(String, 2, 0, 6);
//    UI_ShowChineseMenu();
    UI_ShowChineseMenu();

#else
    {	// new menu layout .. experimental & unfinished

        const int menu_index = gMenuCursor;  // current selected menu item
        i = 1;

        if (!gIsInSubMenu)
        {
            while (i < 2)
            {	// leading menu items - small text
                const int k = menu_index + i - 2;
                if (k < 0)
                    UI_PrintStringSmall(MenuList[gMenuListCount + k].name, 0, 0, i);  // wrap-a-round
                else
                if (k >= 0 && k < (int)gMenuListCount)
                    UI_PrintStringSmall(MenuList[k].name, 0, 0, i);
                i++;
            }

            // current menu item - keep big n fat
            if (menu_index >= 0 && menu_index < (int)gMenuListCount)
                UI_PrintStringSmall(MenuList[menu_index].name, 0, 0, 2);
            i++;

            while (i < 4)
            {	// trailing menu item - small text
                const int k = menu_index + i - 2;
                if (k >= 0 && k < (int)gMenuListCount)
                    UI_PrintStringSmall(MenuList[k].name, 0, 0, 1 + i);
                else
                if (k >= (int)gMenuListCount)
                    UI_PrintStringSmall(MenuList[gMenuListCount - k].name, 0, 0, 1 + i);  // wrap-a-round
                i++;
            }

            // draw the menu index number/count
            sprintf(String, "%2u.%u", 1 + gMenuCursor, gMenuListCount);
            UI_PrintStringSmall(String, 2, 0, 6);
        }
        else
        if (menu_index >= 0 && menu_index < (int)gMenuListCount)
        {	// current menu item
            strcpy(String, MenuList[menu_index].name);
//			strcat(String, ":");
            UI_PrintStringSmall(String, 0, 0, 0);
//			UI_PrintStringSmall(String, 0, 0, 0);
        }
    }
#endif

    // **************

    memset(String, 0, sizeof(String));

    bool already_printed = false;

    switch (UI_MENU_GetCurrentMenuId()) {
        case MENU_SQL:
            sprintf(String, "%d", gSubMenuSelection);
            break;

        case MENU_MIC: {    // display the mic gain in actual dB rather than just an index number
            const uint8_t mic = gMicGain_dB2[gSubMenuSelection];
            sprintf(String, "+%u.%01udB", mic / 2, mic % 2);
        }
            break;

#ifdef ENABLE_AUDIO_BAR
            case MENU_MIC_BAR:
                strcpy(String, gSubMenu_OFF_ON[gSubMenuSelection]);
                break;
#endif

        case MENU_STEP: {
            uint16_t step = gStepFrequencyTable[FREQUENCY_GetStepIdxFromSortedIdx(gSubMenuSelection)];
            sprintf(String, "%d.%02ukHz", step / 100, step % 100);
            break;
        }

        case MENU_TXP:
            strncpy(String, gSubMenu_TXP[gSubMenuSelection], sizeof(gSubMenu_TXP[gSubMenuSelection]));
            String[sizeof(gSubMenu_TXP[gSubMenuSelection])] = '\0';


            break;

        case MENU_R_DCS:
        case MENU_T_DCS:
            if (gSubMenuSelection == 0)
                //translate
#ifdef test
                  strcpy(String, "OFF");

#else
                strcpy(String, "\xD9\xDF");

#endif

            else if (gSubMenuSelection < 105)
                sprintf(String, "D%03oN", DCS_Options[gSubMenuSelection - 1]);
            else
                sprintf(String, "D%03oI", DCS_Options[gSubMenuSelection - 105]);
            break;

        case MENU_R_CTCS:
        case MENU_T_CTCS: {
            if (gSubMenuSelection == 0)
               // translate
#ifdef test
                    strcpy(String, "OFF");

#else
                strcpy(String, "\xD9\xDF");

#endif

            else
                sprintf(String, "%u.%uHz", CTCSS_Options[gSubMenuSelection - 1] / 10,
                        CTCSS_Options[gSubMenuSelection - 1] % 10);
            break;
        }

        case MENU_SFT_D:
            strncpy(String, gSubMenu_SFT_D[gSubMenuSelection] , sizeof( gSubMenu_SFT_D[gSubMenuSelection] ));
            String[sizeof( gSubMenu_SFT_D[gSubMenuSelection])] = '\0';
            break;

        case MENU_OFFSET:
            if (!gIsInSubMenu || gInputBoxIndex == 0) {
                sprintf(String, "%3d.%05u", gSubMenuSelection / 100000, abs(gSubMenuSelection) % 100000);
                UI_PrintStringSmall(String, menu_item_x1, menu_item_x2, 2);
            } else {
                const char *ascii = INPUTBOX_GetAscii();
                sprintf(String, "%.3s.%.3s  ", ascii, ascii + 3);
                UI_PrintStringSmall(String, menu_item_x1, menu_item_x2, 2);
            }

            UI_PrintStringSmall("MHz", menu_item_x1, menu_item_x2, 4);

            already_printed = true;
            break;

        case MENU_W_N:
        
            strcpy(String, gSubMenu_W_N[gSubMenuSelection]);
            break;
   
        case MENU_SCR:
            strcpy(String, gSubMenu_SCRAMBLER[gSubMenuSelection]);
       
#if 1
            if (gSubMenuSelection > 0 && gSetting_ScrambleEnable)
                BK4819_EnableScramble(gSubMenuSelection - 1);
            else
                BK4819_DisableScramble();
#endif
            break;

#ifdef ENABLE_VOX
            case MENU_VOX:
                if (gSubMenuSelection == 0)
                    strcpy(String, "OFF");
                else
                    sprintf(String, "%d", gSubMenuSelection);
                break;
#endif

        case MENU_ABR:
            strcpy(String, gSubMenu_BACKLIGHT[gSubMenuSelection]);
            
            
//            BACKLIGHT_SetBrightness(-1);
            break;

        case MENU_ABR_MIN:
        case MENU_ABR_MAX:
            sprintf(String, "%d", gSubMenuSelection);
            if (gIsInSubMenu)
                BACKLIGHT_SetBrightness(gSubMenuSelection);
//            else
//                BACKLIGHT_SetBrightness(-1);
            break;

        case MENU_AM:
            strcpy(String, gModulationStr[gSubMenuSelection]);
            
            
            break;

#ifdef ENABLE_AM_FIX_TEST1
            case MENU_AM_FIX_TEST1:
                strcpy(String, gSubMenu_AM_fix_test1[gSubMenuSelection]);
//				gSetting_AM_fix = gSubMenuSelection;
                break;
#endif

        case MENU_AUTOLK:
            //translate
#ifdef test
                  strcpy(String, (gSubMenuSelection == 0) ? "OFF" : "AUTO");

#else
            strcpy(String, (gSubMenuSelection == 0) ? "\xD9\xDF" : "\x99\x9A");

#endif


            break;

        case MENU_COMPAND:
        case MENU_ABR_ON_TX_RX:
            strcpy(String, gSubMenu_RX_TX[gSubMenuSelection]);
            
            
            break;

#ifdef ENABLE_AM_FIX
            case MENU_AM_FIX:
#endif
        case MENU_BCL:
        case MENU_BEEP:
        case MENU_S_ADD1:
        case MENU_S_ADD2:
        case MENU_STE:
        case MENU_D_ST:
        case MENU_D_DCD:
        case MENU_D_LIVE_DEC:
#ifdef ENABLE_NOAA
            case MENU_NOAA_S:
#endif
        case MENU_350TX:
        case MENU_200TX:
        case MENU_500TX:
        case MENU_350EN:
        case MENU_SCREN:
            strcpy(String, gSubMenu_OFF_ON[gSubMenuSelection]);
            
            
            break;

        case MENU_MEM_CH:
        case MENU_1_CALL:
        case MENU_DEL_CH: {
            const bool valid = RADIO_CheckValidChannel(gSubMenuSelection, false, 1);

            UI_GenerateChannelStringEx(String, valid, gSubMenuSelection);
            UI_PrintStringSmall(String, menu_item_x1, menu_item_x2, 2);

            if (valid && !gAskForConfirmation) {    // show the frequency so that the user knows the channels frequency
                const uint32_t frequency = BOARD_fetchChannelFrequency(gSubMenuSelection);
                sprintf(String, "%u.%05u", frequency / 100000, frequency % 100000);
                UI_PrintStringSmall(String, menu_item_x1, menu_item_x2, 5);
            }

            already_printed = true;
            break;
        }

        case MENU_MEM_NAME: {
            const bool valid = RADIO_CheckValidChannel(gSubMenuSelection, false, 1);

            UI_GenerateChannelStringEx(String, valid, gSubMenuSelection);
            UI_PrintStringSmall(String, menu_item_x1, menu_item_x2, 2);

            if (valid) {
                const uint32_t frequency = BOARD_fetchChannelFrequency(gSubMenuSelection);

                if (!gIsInSubMenu || edit_index < 0) {    // show the channel name
                    BOARD_fetchChannelName(String, gSubMenuSelection);
                    if (String[0] == 0)
                        strcpy(String, "--");
                    
                    UI_PrintStringSmall(String, menu_item_x1, menu_item_x2, 3);//4
                } else {    // show the channel name being edited
                    UI_PrintStringSmall(edit, menu_item_x1, 0, 3);
                    if (edit_index < 10)
                        UI_PrintStringSmall("^", menu_item_x1 + (8 * edit_index), 0, 4);  // show the cursor
                }

                if (!gAskForConfirmation) {    // show the frequency so that the user knows the channels frequency
                    sprintf(String, "%u.%05u", frequency / 100000, frequency % 100000);
                    if (!gIsInSubMenu || edit_index < 0)
                        UI_PrintStringSmall(String, menu_item_x1, menu_item_x2, 5);
                    else
                        UI_PrintStringSmall(String, menu_item_x1, menu_item_x2, 5);
                }
            }

            already_printed = true;
            break;
        }

        case MENU_SAVE:
            strcpy(String, gSubMenu_SAVE[gSubMenuSelection]);
            
            
            break;

        case MENU_TDR:
            strcpy(String, gSubMenu_RXMode[gSubMenuSelection]);
            
            
            break;

        case MENU_TOT:
            strcpy(String, gSubMenu_TOT[gSubMenuSelection]);
            
            
            break;

#ifdef ENABLE_VOICE
            case MENU_VOICE:
                strcpy(String, gSubMenu_VOICE[gSubMenuSelection]);
                break;
#endif

        case MENU_SC_REV:
//            if(gSubMenuSelection==0)            strcpy(String, "\x1E\x89\xE3\x35\x0a\xFE\xE4\x84\x85\x00");
//
//            else if(gSubMenuSelection==1)             strcpy(String, "\x89\xE3\xE6\xE7\xE4\x0a\x84\x85\x00");
//
//            else             strcpy(String, "\x1E\x89\xE3\x0a\xE4\xE6\xE7\x84\x85\x00");

            strcpy(String, gSubMenu_SC_REV[gSubMenuSelection]);

//            strncpy(String, gSubMenu_SC_REV[gSubMenuSelection] , sizeof( gSubMenu_SC_REV[gSubMenuSelection] ));
//            String[sizeof( gSubMenu_SC_REV[gSubMenuSelection])] = '\0';
            break;

        case MENU_MDF:


    strcpy(String, gSubMenu_MDF[gSubMenuSelection]);
            
            
            break;

        case MENU_RP_STE:
            if (gSubMenuSelection == 0)
//translate
#ifdef test
                   strcpy(String, "OFF");

#else
                strcpy(String, "\xD9\xDF");

#endif


            else
                sprintf(String, "%d*100ms", gSubMenuSelection);
            break;

        case MENU_S_LIST:
            if (gSubMenuSelection < 2)

         //translate

#ifdef test
                   sprintf(String, "list %u", 1 + gSubMenuSelection);

#else
                sprintf(String, "\x86\x87 %u", 1 + gSubMenuSelection);

#endif

            else

#ifdef test
                  strcpy(String, "ALL");

#else
            strcpy(String, "\xED\xEE");

#endif
            break;

#ifdef ENABLE_ALARM
            case MENU_AL_MOD:
                sprintf(String, gSubMenu_AL_MOD[gSubMenuSelection]);
                break;
#endif

        case MENU_ANI_ID:
            strcpy(String, gEeprom.ANI_DTMF_ID);
            break;

        case MENU_UPCODE:
            strcpy(String, gEeprom.DTMF_UP_CODE);
            break;

        case MENU_DWCODE:
            strcpy(String, gEeprom.DTMF_DOWN_CODE);
            break;

        case MENU_D_RSP:
            strcpy(String, gSubMenu_D_RSP[gSubMenuSelection]);
            
            
            break;

        case MENU_D_HOLD:
            sprintf(String, "%ds", gSubMenuSelection);
            break;

        case MENU_D_PRE:
            sprintf(String, "%d*10ms", gSubMenuSelection);
            break;

        case MENU_PTT_ID:
            strcpy(String, gSubMenu_PTT_ID[gSubMenuSelection]);
            
            
            break;

        case MENU_BAT_TXT:
            strcpy(String, gSubMenu_BAT_TXT[gSubMenuSelection]);
            
            
            break;

        case MENU_D_LIST:
            gIsDtmfContactValid = DTMF_GetContact((int) gSubMenuSelection - 1, Contact);
            if (!gIsDtmfContactValid)
                strcpy(String, "NULL");
            else
                memmove(String, Contact, 8);
            break;

        case MENU_PONMSG:
            strcpy(String, gSubMenu_PONMSG[gSubMenuSelection]);
            
            
            break;

        case MENU_ROGER:
            strcpy(String, gSubMenu_ROGER[gSubMenuSelection]);
            
            
            break;

        case MENU_VOL:
            sprintf(String, "%u.%02uV\n%u%%",
                    gBatteryVoltageAverage / 100, gBatteryVoltageAverage % 100,
                    BATTERY_VoltsToPercent(gBatteryVoltageAverage));
            break;

        case MENU_RESET:
            strcpy(String, gSubMenu_RESET[gSubMenuSelection]);
            
            
            break;

        case MENU_F_LOCK:
//            if (!gIsInSubMenu && gUnlockAllTxConfCnt > 0&& gUnlockAllTxConfCnt < 10)
//                strcpy(String, "READ\nMANUAL");
//
//            else
                strcpy(String, gSubMenu_F_LOCK[gSubMenuSelection]);
            
            
            break;

#ifdef ENABLE_F_CAL_MENU
            case MENU_F_CALI:
                {
                    const uint32_t value   = 22656 + gSubMenuSelection;
                    const uint32_t xtal_Hz = (0x4f0000u + value) * 5;

                    writeXtalFreqCal(gSubMenuSelection, false);

                    sprintf(String, "%d\n%u.%06u\nMHz",
                        gSubMenuSelection,
                        xtal_Hz / 1000000, xtal_Hz % 1000000);
                }
                break;
#endif

        case MENU_BATCAL: {
            const uint16_t vol = (uint32_t) gBatteryVoltageAverage * gBatteryCalibration[3] / gSubMenuSelection;
            sprintf(String, "%u.%02uV\n%u", vol / 100, vol % 100, gSubMenuSelection);
            break;
        }

        case MENU_BATTYP:
            strcpy(String, gSubMenu_BATTYP[gSubMenuSelection]);
 
            break;

        case MENU_F1SHRT:
        case MENU_F1LONG:
        case MENU_F2SHRT:
        case MENU_F2LONG:
        case MENU_MLONG:
            strcpy(String, gSubMenu_SIDEFUNCTIONS[gSubMenuSelection].name);
            break;

    }

    if (!already_printed) {    // we now do multi-line text in a single string

        unsigned int y;
        unsigned int lines = 1;
        unsigned int len = strlen(String);
        bool small = false;

        if (len > 0) {
            // count number of lines
            for (i = 0; i < len; i++) {
                if (String[i] == '\n' && i < (len - 1)) {    // found new line char
                    lines+=1;
                    String[i] = 0;  // null terminate the line
                }
            }

            if (lines > 3) {    // use small text
                small = true;
                if (lines > 7)
                    lines = 7;
            }

            // center vertically'ish
            if (small)
                y = 3 - ((lines + 0) / 2);  // untested
            else
                y = 2 - ((lines + 0) / 2);

            // draw the text lines
            for (i = 0; i < len && lines > 0; lines--) {
                if (small)
                    UI_PrintStringSmall(String + i, menu_item_x1, menu_item_x2, y + 1);
                else
                    UI_PrintStringSmall(String + i, menu_item_x1, menu_item_x2, y + 1);

                // look for start of next line
                while (i < len && String[i] !=0&&String[i] !='\n')
                    i++;

                // hop over the null term char(s)
                while (i < len && (String[i] ==0||String[i] =='\n'))
                    i++;

                y += small ? 1 : 2;
            }
        }
    }

    if (UI_MENU_GetCurrentMenuId() == MENU_SLIST1 || UI_MENU_GetCurrentMenuId() == MENU_SLIST2) {
        i = (UI_MENU_GetCurrentMenuId() == MENU_SLIST1) ? 0 : 1;

//		if (gSubMenuSelection == 0xFF)
        if (gSubMenuSelection < 0)
            strcpy(String, "NULL");
        else
            UI_GenerateChannelStringEx(String, true, gSubMenuSelection);

//		if (gSubMenuSelection == 0xFF || !gEeprom.SCAN_LIST_ENABLED[i])
        if (gSubMenuSelection < 0 || !gEeprom.SCAN_LIST_ENABLED[i]) {
            // channel number
            UI_PrintStringSmall(String, menu_item_x1, menu_item_x2, 2);

            // channel name
            BOARD_fetchChannelName(String, gSubMenuSelection);
            if (String[0] == 0)
                strcpy(String, "--");
            UI_PrintStringSmall(String, menu_item_x1, menu_item_x2, 4);
        } else {
            // channel number
            UI_PrintStringSmall(String, menu_item_x1, menu_item_x2, 2);

            // channel name
            BOARD_fetchChannelName(String, gSubMenuSelection);
            if (String[0] == 0)
                strcpy(String, "--");
            UI_PrintStringSmall(String, menu_item_x1, menu_item_x2, 4);

            if (IS_MR_CHANNEL(gEeprom.SCANLIST_PRIORITY_CH1[i])) {
                sprintf(String, "PRI1:%u", gEeprom.SCANLIST_PRIORITY_CH1[i] + 1);
                UI_PrintStringSmall(String, menu_item_x1, menu_item_x2, 4);
            }

            if (IS_MR_CHANNEL(gEeprom.SCANLIST_PRIORITY_CH2[i])) {
                sprintf(String, "PRI2:%u", gEeprom.SCANLIST_PRIORITY_CH2[i] + 1);
                UI_PrintStringSmall(String, menu_item_x1, menu_item_x2, 5);
            }
        }
    }

    if (UI_MENU_GetCurrentMenuId() == MENU_MEM_CH ||
        UI_MENU_GetCurrentMenuId() == MENU_DEL_CH ||
        UI_MENU_GetCurrentMenuId() == MENU_1_CALL) {    // display the channel name
        char s[11];
        BOARD_fetchChannelName(s, gSubMenuSelection);
        if (s[0] == 0)
            strcpy(s, "--");
        UI_PrintStringSmall(s, menu_item_x1, menu_item_x2, 3);
    }

    if ((UI_MENU_GetCurrentMenuId() == MENU_R_CTCS || UI_MENU_GetCurrentMenuId() == MENU_R_DCS) && gCssBackgroundScan)
        UI_PrintStringSmall("\x8F\x90", menu_item_x1, menu_item_x2, 5);


    if (UI_MENU_GetCurrentMenuId() == MENU_UPCODE)
        if (strlen(gEeprom.DTMF_UP_CODE) > 8)
            UI_PrintStringSmall(gEeprom.DTMF_UP_CODE + 8, menu_item_x1, menu_item_x2, 5);

    if (UI_MENU_GetCurrentMenuId() == MENU_DWCODE)
        if (strlen(gEeprom.DTMF_DOWN_CODE) > 8)
            UI_PrintStringSmall(gEeprom.DTMF_DOWN_CODE + 8, menu_item_x1, menu_item_x2, 5);

    if (UI_MENU_GetCurrentMenuId() == MENU_D_LIST && gIsDtmfContactValid) {
        Contact[11] = 0;
        memmove(&gDTMF_ID, Contact + 8, 4);
        sprintf(String, "ID:%s", Contact + 8);
        UI_PrintStringSmall(String, menu_item_x1, menu_item_x2, 5);
    }

    if (UI_MENU_GetCurrentMenuId() == MENU_R_CTCS ||
        UI_MENU_GetCurrentMenuId() == MENU_T_CTCS ||
        UI_MENU_GetCurrentMenuId() == MENU_R_DCS ||
        UI_MENU_GetCurrentMenuId() == MENU_T_DCS ||
        UI_MENU_GetCurrentMenuId() == MENU_D_LIST) {
        sprintf(String, "%2d", gSubMenuSelection);
        UI_PrintStringSmall(String, 105, 0, 1);//small
    }

    if ((UI_MENU_GetCurrentMenuId() == MENU_RESET ||
         UI_MENU_GetCurrentMenuId() == MENU_MEM_CH ||
         UI_MENU_GetCurrentMenuId() == MENU_MEM_NAME ||
         UI_MENU_GetCurrentMenuId() == MENU_DEL_CH) && gAskForConfirmation) {    // display confirmation
        strcpy(String, (gAskForConfirmation == 1) ? "SURE?" : "WAIT!");
        UI_PrintStringSmall(String, menu_item_x1, menu_item_x2, 5);
    }
//    for (int i = 0; i < 128; i++) {
//        // Set the 7th and 8th positions to 1, keep others unchanged
//        gFrameBuffer[1][i] |= (1 << 7)|(1<<6) ;
//
//    }

    ST7565_BlitFullScreen();
}

//


void UI_ShowChineseMenu() {
  //  return;
    uint8_t cnt_char = 0;

    uint8_t size_menu = 0;
    uint8_t cnt_menu=0;
    for ( cnt_menu = 0; cnt_menu < 7 && MenuList[gMenuCursor].name[cnt_menu] != 0; cnt_menu++) {

            if(is_chn(MenuList[gMenuCursor].name[cnt_menu])!=255)//中文
                size_menu+=12;
            else//英文
                size_menu+=7;

    }
    cnt_char = 0;
    if (size_menu < 48)cnt_char = (48 - size_menu ) / 2;
    menu_set_flag=1;
    UI_PrintStringSmall(MenuList[gMenuCursor].name, (cnt_char), 0, 0);
//
//    for (uint8_t i = 0; i < cnt_menu; i++) {
//        uint8_t num_solve=is_chn(MenuList[gMenuCursor].name[i]);
//        if(num_solve==255)//数字/字母
//        {
//            char tmp[2]={0};
//            tmp[0]=MenuList[gMenuCursor].name[i];
//            UI_PrintStringSmall((const char *)tmp, (cnt_char), 0, 0);
//            cnt_char += 7;
//        } else  {
//
//
//            UI_PrintChineseChar(num_solve, cnt_char, 0);
//
//            cnt_char += 13;
//        }
//
//    }

}