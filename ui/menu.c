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
                {VOICE_ID_FREQUENCY_STEP, MENU_STEP,"\x4F\x73\x80\x56"
                },
                {VOICE_ID_POWER, MENU_TXP,"\x1F\x2F\x1A\x56"
                }, // was "TXP"
                { VOICE_ID_DCS, MENU_R_DCS,"\x3F\x43\x45\x2A\x0C\x7E"
                }, // was "R_DCS"
                {VOICE_ID_CTCSS, MENU_R_CTCS,"\x3F\x43\x4E\x3C\x0C\x7E"
                }, // was "R_CTCS"
                { VOICE_ID_DCS, MENU_T_DCS, "\x1F\x74\x45\x2A\x0C\x7E"},
                // was "T_DCS"
                { VOICE_ID_CTCSS, MENU_T_CTCS, "\x1F\x74\x4E\x3C\x0C\x7E"
                }, // was "T_CTCS"
                { VOICE_ID_TX_OFFSET_FREQUENCY_DIRECTION, MENU_SFT_D, "\x80\x32\x46\x21"
                }, // was "SFT_D"
                { VOICE_ID_TX_OFFSET_FREQUENCY, MENU_OFFSET, "\x80\x32\x80\x56"
                }, // was "OFFSET"
                { VOICE_ID_CHANNEL_BANDWIDTH, MENU_W_N, "\x2D\x5F\x78\x67"
                },
                { VOICE_ID_SCRAMBLER_ON, MENU_SCR, "\x1B\x2E\x75\x6D"
                }, // was "SCR"
                { VOICE_ID_BUSY_LOCKOUT, MENU_BCL, "\x76\x37\x5E\x1F"
                }, // was "BCL"
                {VOICE_ID_INVALID, MENU_COMPAND, "\x1E\x3A"
                },
                { VOICE_ID_INVALID, MENU_AM, "\x6E\x19\x4E\x36"
                }, // was "AM"
                { VOICE_ID_INVALID, MENU_S_ADD1, "\x42\x62\x16\x6B\x01"
                },
                {VOICE_ID_INVALID, MENU_S_ADD2, "\x42\x62\x16\x6B\x02"
                },
                { VOICE_ID_MEMORY_CHANNEL, MENU_MEM_CH, "\x2B\x13\x12\x77"
                }, // was "MEM-CH"
                {VOICE_ID_DELETE_CHANNEL, MENU_DEL_CH, "\x17\x7C\x12\x77"
                }, // was "DEL-CH"
                { VOICE_ID_INVALID, MENU_MEM_NAME, "\x23\x20\x12\x77"
                },

                { VOICE_ID_INVALID, MENU_S_LIST, "\x12\x77\x3B\x41\x16\x6B"
                },
                { VOICE_ID_INVALID, MENU_SLIST1, "\x3B\x41\x16\x6B\x01"
                },
                {VOICE_ID_INVALID, MENU_SLIST2, "\x3B\x41\x16\x6B\x02"
                },
                { VOICE_ID_INVALID, MENU_SC_REV, "\x42\x62\x38\x28\x4E\x36"
                },
#ifdef ENABLE_NOAA
                {"NOAA-S", VOICE_ID_INVALID,                       MENU_NOAA_S        },
#endif

                { VOICE_ID_INVALID, MENU_F1SHRT, "\x5B\x3E\x11\x7A\x01"
                },
                {VOICE_ID_INVALID, MENU_F1LONG, "\x7B\x3E\x11\x7A\x01"
                },
                {VOICE_ID_INVALID, MENU_F2SHRT, "\x5B\x3E\x11\x7A\x02"
                },
                { VOICE_ID_INVALID, MENU_F2LONG, "\x7B\x3E\x11\x7A\x02"
                },
                { VOICE_ID_INVALID, MENU_MLONG, "\x7B\x3E\x06\x7A"
                },

                {VOICE_ID_INVALID, MENU_AUTOLK, "\x7A\x59\x6A\x1C\x79\x2C"
                }, // was "AUTOLk"
                {VOICE_ID_TRANSMIT_OVER_TIME, MENU_TOT, "\x1F\x74\x6F\x47"
                }, // was "TOT"
                { VOICE_ID_SAVE_MODE, MENU_SAVE, "\x5A\x57\x4E\x36"
                }, // was "SAVE"
                { VOICE_ID_INVALID, MENU_MIC, "\x82\x15\x81\x55\x44\x34"
                },
#ifdef ENABLE_AUDIO_BAR
                {             VOICE_ID_INVALID,        MENU_MIC_BAR     ,"\x82\x15\x81\x3D\x5D\x4C"
  },
#endif
                {VOICE_ID_INVALID, MENU_MDF, "\x12\x77\x48\x5D\x4E\x36"
                }, // was "MDF"
                { VOICE_ID_INVALID, MENU_PONMSG, "\x35\x4A\x12\x39"
                },
                {VOICE_ID_INVALID, MENU_BAT_TXT, "\x57\x50\x4D\x60"
                },
                { VOICE_ID_INVALID, MENU_ABR, "\x6A\x1C\x69\x14"
                }, // was "ABR"
                { VOICE_ID_INVALID, MENU_ABR_MIN, "\x49\x30\x0D\x34"
                },
                {VOICE_ID_INVALID, MENU_ABR_MAX, "\x49\x29\x0D\x34"
                },
                {VOICE_ID_INVALID, MENU_ABR_ON_TX_RX, "\x69\x14\x54\x52"
                },
                {VOICE_ID_BEEP_PROMPT, MENU_BEEP, "\x7A\x59\x3E\x7A\x7E"
                },
#ifdef ENABLE_VOICE
                {"Voice",  VOICE_ID_VOICE_PROMPT,                  MENU_VOICE         },
#endif
                { VOICE_ID_INVALID, MENU_ROGER, "\x1F\x74\x65\x4B\x7E"
                },
                {VOICE_ID_INVALID, MENU_STE, "\x31\x7E\x53\x7C"
                },
                {VOICE_ID_INVALID, MENU_RP_STE, "\x72\x0B\x66\x31\x7E\x53\x7C"
                },
                {VOICE_ID_INVALID, MENU_1_CALL, "\x08\x7A\x1D\x22"
                },
#ifdef ENABLE_ALARM
                {"AlarmT", VOICE_ID_INVALID,                       MENU_AL_MOD        },
#endif
                {VOICE_ID_ANI_CODE, MENU_ANI_ID, "\x70\x0F\x5C"
                },
                { VOICE_ID_INVALID, MENU_UPCODE, "\x04\x07\x06\x05\x09\x64\x5C"
                },
                { VOICE_ID_INVALID, MENU_DWCODE, "\x04\x07\x06\x05\x0A\x64\x5C"
                },
                { VOICE_ID_INVALID, MENU_PTT_ID, "\x04\x07\x06\x05\x1F\x74"
                },
                {VOICE_ID_INVALID, MENU_D_ST, "\x04\x07\x06\x05\x11\x7E"
                },
                { VOICE_ID_INVALID, MENU_D_RSP, "\x04\x07\x06\x05\x24\x33"
                },
                { VOICE_ID_INVALID, MENU_D_HOLD, "\x04\x07\x06\x05\x28\x10"
                },
                {VOICE_ID_INVALID, MENU_D_PRE, "\x04\x07\x06\x05\x7F\x71\x51"
                },
                { VOICE_ID_INVALID, MENU_D_DCD, "\x04\x07\x06\x05\x6C\x5C"
                },
                { VOICE_ID_INVALID, MENU_D_LIST, "\x04\x07\x06\x05\x68\x61\x0E"
                },
                {VOICE_ID_INVALID, MENU_D_LIVE_DEC, "\x04\x07\x06\x05\x48\x5D"
                }, // live DTMF decoder
#ifdef ENABLE_AM_FIX
                { VOICE_ID_INVALID,                       MENU_AM_FIX     ,"\x03\x06\x6A\x1C\x26\x58"
   },
#endif
#ifdef ENABLE_AM_FIX_TEST1
                {"AM FT1", VOICE_ID_INVALID,                       MENU_AM_FIX_TEST1  },
#endif
#ifdef ENABLE_VOX
                {    VOICE_ID_VOX,                           MENU_VOX      ,"\x27\x40\x1F\x2F"
     },
#endif
                {VOICE_ID_INVALID, MENU_VOL, "\x57\x50\x57\x1E"
                }, // was "VOL"
                {VOICE_ID_DUAL_STANDBY, MENU_TDR, "\x43\x1F\x4E\x36"
                },
                {VOICE_ID_SQUELCH, MENU_SQL, "\x7D\x25\x63\x18"
                },

                // hidden menu items from here on
                // enabled if pressing both the PTT and upper side button at power-on
                {VOICE_ID_INVALID, MENU_F_LOCK, "\x80\x56\x78\x67"},
                {VOICE_ID_INVALID, MENU_200TX, "\x01\x85\x85\x06\x1f\x2f"}, // was "200TX"
                {VOICE_ID_INVALID, MENU_350TX, "\x83\x84\x85\x06\x1f\x2f"}, // was "350TX"
                { VOICE_ID_INVALID, MENU_500TX, "\x84\x85\x85\x06\x1f\x2f"}, // was "500TX"
                {VOICE_ID_INVALID, MENU_350EN, "\x83\x84\x85\x06\x3f\x43"}, // was "350EN"
                { VOICE_ID_INVALID, MENU_SCREN, "\x1b\x2e"}, // was "SCREN"
#ifdef ENABLE_F_CAL_MENU
                {"FrCali", VOICE_ID_INVALID,                       MENU_F_CALI        }, // reference xtal calibration
#endif
                {VOICE_ID_INVALID, MENU_BATCAL, "\x57\x50\x6e\x1e"}, // battery voltage calibration
                { VOICE_ID_INVALID, MENU_BATTYP, "\x57\x50\x29\x30"}, // battery type 1600/2200mAh
                {VOICE_ID_INITIALISATION,MENU_RESET, "\x28\x10"}, // might be better to move this to the hidden menu items ?

                {VOICE_ID_INVALID, 0xff, ""}  // end of list - DO NOT delete or move this this
        };

const uint8_t FIRST_HIDDEN_MENU_ITEM = MENU_F_LOCK;

const char gSubMenu_TXP[][5] =//5
        {
                "LOW",
                "MID",
                "HIGH"
        };

const char gSubMenu_SFT_D[][4] =//4
        {
                "OFF",
                "+",
                "-"
        };

const char gSubMenu_W_N[][7] =//7
        {
                "WIDE",
                "NARROW"
        };

const char gSubMenu_OFF_ON[][4] =//4
        {
                "OFF",
                "ON"
        };

const char gSubMenu_SAVE[][4] =//4
        {
                "OFF",
                "1:1",
                "1:2",
                "1:3",
                "1:4"
        };

const char gSubMenu_TOT[][7] =
        {
                "30 sec",
                "1 min",
                "2 min",
                "3 min",
                "4 min",
                "5 min",
                "6 min",
                "7 min",
                "8 min",
                "9 min",
                "15 min"
        };

const char *gSubMenu_RXMode[] =
        {
                "MAIN\nONLY",        // TX and RX on main only
                "DUAL RX\nRESPOND", // Watch both and respond
                "CROSS\nBAND",        // TX on main, RX on secondary
                "MAIN TX\nDUAL RX"    // always TX on main, but RX on both
        };

#ifdef ENABLE_VOICE
const char gSubMenu_VOICE[][4] =
{
    "OFF",
    "CHI",
    "ENG"
};
#endif

const char gSubMenu_SC_REV[][8] =
        {
                "TIMEOUT",
                "CARRIER",
                "STOP"
        };

const char *gSubMenu_MDF[] =
        {
                "FREQ",
                "CHANNEL\nNUMBER",
                "NAME",
                "NAME\n+\nFREQ"
        };

#ifdef ENABLE_ALARM
const char gSubMenu_AL_MOD[][5] =
{
    "SITE",
    "TONE"
};
#endif

const char gSubMenu_D_RSP[][11] =
        {
                "DO\nNOTHING",
                "RING",
                "REPLY",
                "BOTH"
        };

const char *gSubMenu_PTT_ID[] =
        {
                "OFF",
                "UP CODE",
                "DOWN CODE",
                "UP+DOWN\nCODE",
                "APOLLO\nQUINDAR"
        };

const char gSubMenu_PONMSG[][8] =
        {
                "FULL",
                "MESSAGE",
                "VOLTAGE",
                "NONE"
        };

const char gSubMenu_ROGER[][6] =
        {
                "OFF",
                "ROGER",
                "MDC"
        };

const char gSubMenu_RESET[][4] =
        {
                "VFO",
                "ALL"
        };

const char *gSubMenu_F_LOCK[] =
        {
                "DEFAULT+\n137-174\n400-470",
                "FCC HAM\n144-148\n420-450",
                "CE HAM\n144-146\n430-440",
                "GB HAM\n144-148\n430-440",
                "137-174\n400-430",
                "137-174\n400-438",
                "DISABLE\nALL",
                "UNLOCK\nALL",
        };

const char gSubMenu_BACKLIGHT[][7] =
        {
                "OFF",
                "5 sec",
                "10 sec",
                "20 sec",
                "1 min",
                "2 min",
                "4 min",
                "ON"
        };

const char gSubMenu_RX_TX[][6] =
        {
                "OFF",
                "TX",
                "RX",
                "TX/RX"
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

const char gSubMenu_BAT_TXT[][8] =
        {
                "NONE",
                "VOLTAGE",
                "PERCENT"
        };

const char gSubMenu_BATTYP[][9] =
        {
                "1600mAh",
                "2200mAh"
        };

const char gSubMenu_SCRAMBLER[][7] =
        {
                "OFF",
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
                {"NONE", ACTION_OPT_NONE},
                {"FLASH\nLIGHT", ACTION_OPT_FLASHLIGHT},
                {"POWER", ACTION_OPT_POWER},
                {"MONITOR", ACTION_OPT_MONITOR},
                {"SCAN", ACTION_OPT_SCAN},
#ifdef ENABLE_VOX
                {"VOX",				ACTION_OPT_VOX},
#endif
#ifdef ENABLE_ALARM
                {"ALARM",			ACTION_OPT_ALARM},
#endif
#ifdef ENABLE_FMRADIO
                {"FM RADIO",		ACTION_OPT_FM},
#endif
#ifdef ENABLE_TX1750
                {"1750HZ",			ACTION_OPT_1750},
#endif
                {"LOCK\nKEYPAD", ACTION_OPT_KEYLOCK},
                {"SWITCH\nVFO", ACTION_OPT_A_B},
                {"VFO/MR", ACTION_OPT_VFO_MR},
                {"SWITCH\nDEMODUL", ACTION_OPT_SWITCH_DEMODUL},
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

void change_bit(unsigned char *data, unsigned char local, unsigned char num) {
    *data = (*data & ~(1 << local)) | (num << local);
}

void UI_DisplayMenu(void) {
    const unsigned int menu_list_width = 6; // max no. of characters on the menu list (left side)
    const unsigned int menu_item_x1 = (8 * menu_list_width) + 2;
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
                strcpy(String, "OFF");
            else if (gSubMenuSelection < 105)
                sprintf(String, "D%03oN", DCS_Options[gSubMenuSelection - 1]);
            else
                sprintf(String, "D%03oI", DCS_Options[gSubMenuSelection - 105]);
            break;

        case MENU_R_CTCS:
        case MENU_T_CTCS: {
            if (gSubMenuSelection == 0)
                strcpy(String, "OFF");
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
            
            
            BACKLIGHT_SetBrightness(-1);
            break;

        case MENU_ABR_MIN:
        case MENU_ABR_MAX:
            sprintf(String, "%d", gSubMenuSelection);
            if (gIsInSubMenu)
                BACKLIGHT_SetBrightness(gSubMenuSelection);
            else
                BACKLIGHT_SetBrightness(-1);
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
            strcpy(String, (gSubMenuSelection == 0) ? "OFF" : "AUTO");
            
            
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
            strcpy(String, gSubMenu_SC_REV[gSubMenuSelection]);
            
            
            break;

        case MENU_MDF:
            strcpy(String, gSubMenu_MDF[gSubMenuSelection]);
            
            
            break;

        case MENU_RP_STE:
            if (gSubMenuSelection == 0)
                strcpy(String, "OFF");
            else
                sprintf(String, "%d*100ms", gSubMenuSelection);
            break;

        case MENU_S_LIST:
            if (gSubMenuSelection < 2)
                sprintf(String, "LIST%u", 1 + gSubMenuSelection);
            else
                strcpy(String, "ALL");
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
            if (!gIsInSubMenu && gUnlockAllTxConfCnt > 0 && gUnlockAllTxConfCnt < 10)
                strcpy(String, "READ\nMANUAL");
            
            else
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
                    lines++;
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
                while (i < len && String[i] >= 32)
                    i++;

                // hop over the null term char(s)
                while (i < len && String[i] < 32)
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
        UI_PrintStringSmall("SCAN", menu_item_x1, menu_item_x2, 5);


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
    uint8_t cnt_char = 0;

    uint8_t size_menu = 0;
    for (uint8_t i = 0; i < 7 && MenuList[gMenuCursor].name[i] != 0; i++) {
        cnt_char = MenuList[gMenuCursor].name[i];
        if (cnt_char <= 145)size_menu++;
        else break;

    }
    cnt_char = 0;
    if (size_menu < 4)cnt_char = (48 - size_menu * 10) / 2;

    for (uint8_t i = 0; i < size_menu; i++) {
        uint8_t now_char[2] = {0};
        now_char[0] = MenuList[gMenuCursor].name[i];
        if(now_char[0]<=7|| (now_char[0] > 130&&now_char[0] <= 133))//数字/字母
        {
            if(now_char[0]<3)now_char[0]+='0';
            else if(now_char[0]==3)now_char[0]='A';
            else if(now_char[0]==4)now_char[0]='D';
            else if(now_char[0]==5)now_char[0]='F';
            else if(now_char[0]==6)now_char[0]='M';
            else if(now_char[0]==7)now_char[0]='T';
            else if(now_char[0]==0x83)now_char[0]='3';
            else if(now_char[0]==0x84)now_char[0]='5';
            else if(now_char[0]==0x85)now_char[0]='0';

//            0x83 3
//            0x84 5
//            0x85 0

            UI_PrintStringSmall((const char *) now_char, (cnt_char), 0, 0);


            //UI_PrintChar(now_char, (cnt_char%48), );

            cnt_char += 8;
        } else if (now_char[0] <= 130) {


            UI_PrintChineseChar(now_char[0] - 8, (cnt_char), 0);

            cnt_char += 12;
        }

    }
//    UI_PrintChineseChar(0,  start, start_line);
//    UI_PrintChineseChar(1,  start+16, start_line);
//    UI_PrintChineseChar(2,  32, 0);
//    UI_PrintChineseChar(3,  0, 2);
}