//
// Created by RUPC on 2023/11/17.
//
#include "bits/stdc++.h"

unsigned char chn_font[159][14] = {
        {0x77, 0xb7, 0xd1, 0xf7, 0xf7, 0x80, 0x75, 0xb5, 0xd5, 0xf7, 0xff, 0x57, 0xf9, 0xff},/*步*/
        {0xf6, 0x05, 0xff, 0x6b, 0xab, 0xc0, 0xeb, 0x00, 0xeb, 0xeb, 0xff, 0x59, 0x55, 0x75},/*进*/
        {0xb1, 0xd7, 0x80, 0x75, 0x95, 0xff, 0x82, 0xf8, 0x02, 0xfa, 0x82, 0xe5, 0x9f, 0x9b},/*频*/
        {0x7d, 0x55, 0x6d, 0x3d, 0x0c, 0x0d, 0x3d, 0x6d, 0x55, 0x7d, 0xff, 0xff, 0xfc, 0xff},/*率*/
        {0xfb, 0x78, 0x9b, 0xe3, 0xf8, 0xcb, 0x2b, 0xaa, 0xca, 0xfd, 0xfb, 0x79, 0xa9, 0x96},/*发*/
        {0xbf, 0x81, 0x34, 0xad, 0x01, 0xff, 0xfb, 0x9b, 0xfb, 0x00, 0xfb, 0x79, 0x7c, 0x71},/*射*/
        {0x7d, 0x01, 0x7d, 0x7d, 0xff, 0xfb, 0xfb, 0x3b, 0xc0, 0xfb, 0x03, 0xff, 0xe5, 0xe7},/*功*/
        {0xdb, 0x00, 0xeb, 0xff, 0xd5, 0x11, 0xc4, 0x55, 0x91, 0xd5, 0xff, 0x71, 0xa5, 0xb5},/*接*/
        {0x01, 0x7f, 0xbf, 0x00, 0xff, 0xf7, 0xfb, 0xc4, 0x3d, 0x81, 0xfd, 0x3f, 0x5f, 0x5a},/*收*/
        {0xaa, 0x31, 0x93, 0xa0, 0xb1, 0x2a, 0xf7, 0x80, 0x7b, 0x83, 0xfb, 0xa5, 0x96, 0x9b},/*数*/
        {0xb1, 0xbd, 0xb5, 0xb5, 0xb5, 0x14, 0xa5, 0xbd, 0xbd, 0xb1, 0xff, 0x7f, 0xf1, 0xff},/*字*/
        {0xe6, 0x9e, 0xfe, 0x00, 0xfe, 0xfe, 0x00, 0xfe, 0x9e, 0xe6, 0xff, 0x15, 0x45, 0x75},/*亚*/
        {0xf7, 0xf5, 0x11, 0x51, 0x54, 0x55, 0x51, 0x11, 0xf5, 0xf7, 0xff, 0x4f, 0x15, 0x3f},/*音*/
        {0xbb, 0xcb, 0x00, 0xeb, 0xbf, 0x85, 0xa0, 0x25, 0x90, 0x85, 0xbf, 0xcf, 0xe5, 0xd6},/*模*/
        {0xdb, 0x00, 0xeb, 0xff, 0x01, 0xbf, 0xdd, 0x73, 0x3f, 0xc0, 0xff, 0xf1, 0xe7, 0xdb},/*拟*/
        {0xf6, 0x05, 0xff, 0x6b, 0x6a, 0x81, 0xa9, 0x6a, 0x6b, 0xff, 0xff, 0x59, 0x55, 0x75},/*送*/
        {0xed, 0x65, 0x85, 0xe4, 0xa1, 0xa5, 0x24, 0xa5, 0xa5, 0xed, 0xed, 0x5e, 0x45, 0x75},/*差*/
        {0xfb, 0xfb, 0xfb, 0x7b, 0x82, 0xeb, 0xeb, 0xeb, 0xeb, 0x0b, 0xfb, 0xe5, 0x5f, 0x79},/*方*/
        {0x01, 0xfd, 0xfd, 0x05, 0x74, 0x75, 0x05, 0xfd, 0xfd, 0x01, 0xff, 0xfc, 0x7f, 0x71},/*向*/
        {0xf9, 0xf5, 0x05, 0xe1, 0xe5, 0x24, 0xe5, 0x01, 0xf5, 0xf9, 0xff, 0x55, 0x4e, 0x71},/*宽*/
        {0xb9, 0xb5, 0xd5, 0xe9, 0x0d, 0xac, 0xa9, 0xa5, 0xa5, 0xe9, 0xff, 0xff, 0xa8, 0xbe},/*窄*/
        {0xed, 0x0d, 0xc8, 0xcd, 0xcd, 0x08, 0xcd, 0xcd, 0xc8, 0x0d, 0xed, 0xfb, 0xb3, 0xba},/*带*/
        {0x02, 0x50, 0x62, 0x50, 0x02, 0xff, 0x0e, 0xee, 0xee, 0x60, 0xff, 0x54, 0x4c, 0x71},/*配*/
        {0xf4, 0xf2, 0x12, 0x94, 0x02, 0x52, 0xd4, 0x12, 0xf2, 0xf4, 0xff, 0x45, 0x01, 0x35},/*置*/
        {0xfb, 0x7b, 0x80, 0xfb, 0xfb, 0x03, 0xff, 0x01, 0xfd, 0xfd, 0x01, 0x79, 0xb9, 0xaa},/*加*/
        {0xc9, 0x55, 0xed, 0xc5, 0xc9, 0x44, 0xd9, 0xcd, 0x75, 0xe9, 0xff, 0x53, 0x51, 0x7c},/*密*/
        {0xee, 0x0d, 0xff, 0x07, 0x56, 0x54, 0x02, 0x54, 0x56, 0x07, 0xff, 0x19, 0x45, 0x51},/*通*/
        {0xf6, 0x05, 0xff, 0xff, 0xf7, 0x35, 0xb5, 0x81, 0xb6, 0x36, 0xf7, 0x93, 0x53, 0x71},/*话*/
        {0xf6, 0x05, 0xff, 0x10, 0xd2, 0x52, 0x00, 0x52, 0xd2, 0x10, 0xff, 0x59, 0x55, 0x75},/*遇*/
        {0xe3, 0xff, 0x00, 0xf7, 0xff, 0xfb, 0x03, 0xf8, 0xfb, 0xfb, 0xfb, 0xcf, 0x4f, 0x55},/*忙*/
        {0xb5, 0xa9, 0xa0, 0xa9, 0xa5, 0x2f, 0xa5, 0xa9, 0xa0, 0xa9, 0xb5, 0xe5, 0xf1, 0xd6},/*禁*/
        {0xff, 0x00, 0xfe, 0xee, 0xee, 0x02, 0xee, 0xae, 0x6e, 0xfe, 0xff, 0x59, 0x51, 0x75},/*压*/
        {0xed, 0x00, 0xf5, 0xff, 0x07, 0xfb, 0xfb, 0xfa, 0xfb, 0xfb, 0xff, 0x73, 0xfe, 0xff},/*扩*/
        {0xf6, 0x05, 0xff, 0xff, 0x00, 0xfe, 0x1a, 0x40, 0x1a, 0xfe, 0x00, 0x93, 0xfe, 0xc5},/*调*/
        {0x1b, 0xd4, 0xd5, 0x00, 0xd5, 0xd5, 0x1f, 0xff, 0x81, 0xff, 0x00, 0x3e, 0xeb, 0xc5},/*制*/
        {0xeb, 0xeb, 0x0b, 0xeb, 0xeb, 0xeb, 0xfb, 0xc0, 0x3b, 0xfa, 0x79, 0x45, 0xfa, 0xcb},/*式*/
        {0xdb, 0x00, 0xeb, 0xff, 0xe1, 0xa5, 0x2f, 0x80, 0xaf, 0x25, 0xa1, 0xf1, 0x85, 0x96},/*搜*/
        {0xe7, 0x75, 0x55, 0x55, 0x25, 0x20, 0x55, 0x65, 0x75, 0xf5, 0xe7, 0xe5, 0xbc, 0xb5},/*索*/
        {0xde, 0xe6, 0xf0, 0xd6, 0x06, 0xff, 0x83, 0xff, 0xff, 0x00, 0xff, 0x97, 0x7f, 0x71},/*列*/
        {0xdf, 0xd5, 0x55, 0x55, 0x95, 0xc0, 0x95, 0x55, 0xd5, 0x55, 0xdf, 0x3b, 0xf9, 0xd6},/*表*/
        {0xdd, 0xed, 0x05, 0xf9, 0xbc, 0xb5, 0xb5, 0x15, 0xa5, 0xbd, 0xfd, 0xcf, 0x1f, 0x3f},/*存*/
        {0xf7, 0x03, 0xfc, 0xff, 0x7d, 0x55, 0x54, 0x55, 0x55, 0x7d, 0xff, 0xf3, 0x54, 0x71},/*信*/
        {0xf6, 0x05, 0xff, 0xfd, 0x05, 0x24, 0xa9, 0x24, 0x05, 0xfd, 0xff, 0x59, 0x55, 0x75},/*道*/
        {0x00, 0xee, 0x00, 0xef, 0x00, 0xee, 0x00, 0xff, 0x81, 0xff, 0x00, 0xce, 0xce, 0xc7},/*删*/
        {0x00, 0x7e, 0x00, 0xff, 0xfb, 0x5d, 0xd6, 0x06, 0xd6, 0x55, 0xfb, 0xfc, 0x1e, 0x2f},/*除*/
        {0xf7, 0x17, 0xdb, 0x15, 0xf5, 0x16, 0xd5, 0xd5, 0x1b, 0xf7, 0xf7, 0xab, 0xb3, 0xbe},/*命*/
        {0xff, 0x7b, 0x2b, 0xdd, 0x0c, 0xc5, 0xd5, 0xd5, 0xd9, 0xdf, 0x1f, 0xfe, 0x54, 0x45},/*名*/
        {0xdb, 0x00, 0xeb, 0xff, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0x00, 0xf1, 0x55, 0x45},/*扫*/
        {0xdb, 0x00, 0xeb, 0xff, 0x05, 0xb5, 0xb0, 0x05, 0xb5, 0xb0, 0x05, 0xf1, 0x14, 0x05},/*描*/
        {0xf7, 0x03, 0xfc, 0xb3, 0xdf, 0xe5, 0x99, 0xbc, 0x05, 0xdd, 0xed, 0xf3, 0x97, 0x9b},/*恢*/
        {0x7b, 0x7c, 0xa1, 0x05, 0xa5, 0xa5, 0xa5, 0x25, 0xa1, 0xfd, 0xff, 0x55, 0x6a, 0x75},/*复*/
        {0xeb, 0x6c, 0x81, 0x6d, 0xff, 0xfe, 0x22, 0xea, 0xea, 0x22, 0xfe, 0x39, 0x17, 0x14},/*短*/
        {0xdb, 0x00, 0xeb, 0xff, 0xe9, 0xad, 0x44, 0x6d, 0x8d, 0xe9, 0xff, 0xf1, 0x95, 0x95},/*按*/
        {0x01, 0xfe, 0x81, 0xfd, 0x05, 0xfd, 0x81, 0xff, 0x81, 0xff, 0x00, 0x9c, 0xdb, 0xc5},/*侧*/
        {0xd3, 0x04, 0xd5, 0xfb, 0x06, 0xff, 0xd5, 0x55, 0x00, 0x55, 0xc1, 0xd3, 0x54, 54},/*键*/
        {0xef, 0xef, 0x00, 0xef, 0xe7, 0xab, 0x6d, 0xee, 0xef, 0xef, 0xff, 0x4f, 0xbe, 0xb5},/*长*/
        {0xef, 0xaf, 0x41, 0x6d, 0x65, 0x6c, 0x6d, 0x4d, 0x6d, 0x81, 0xef, 0x45, 0x44, 0x54},/*盘*/
        {0xff, 0x01, 0xad, 0xad, 0xad, 0xac, 0xad, 0xad, 0x01, 0xff, 0xff, 0x53, 0x55, 0x7c},/*自*/
        {0x77, 0x95, 0xe5, 0x75, 0x35, 0xff, 0xfb, 0x7b, 0x80, 0xfb, 0x03, 0xea, 0x9e, 0xa7},/*动*/
        {0xb3, 0x04, 0xb5, 0xff, 0x86, 0xf5, 0x77, 0x90, 0x77, 0xf5, 0x86, 0xe3, 0xf9, 0xdb},/*锁*/
        {0xf9, 0xf5, 0x15, 0xf5, 0xf5, 0x04, 0xb5, 0xb5, 0xb5, 0xf5, 0xf9, 0xb9, 0x5a, 0x55},/*定*/
        {0xf7, 0x15, 0xf5, 0x00, 0xb5, 0xb5, 0xff, 0x0c, 0x6e, 0x6a, 0x08, 0xac, 0x55, 0x55},/*超*/
        {0x01, 0xed, 0xed, 0x01, 0xff, 0xfb, 0xeb, 0x9b, 0xfb, 0x00, 0xfb, 0xaa, 0x7f, 0x71},/*时*/
        {0xeb, 0xed, 0x0e, 0x57, 0x57, 0x50, 0x57, 0x52, 0x05, 0xfb, 0xff, 0x4f, 0x55, 0x7c},/*省*/
        {0x81, 0xb5, 0xb5, 0xb5, 0x00, 0xb5, 0xb5, 0xb5, 0x81, 0xff, 0x7f, 0xff, 0x54, 0x45},/*电*/
        {0xef, 0x6d, 0x65, 0x25, 0x85, 0xa0, 0xa5, 0x25, 0xa5, 0xed, 0xef, 0x55, 0x6a, 0x55},/*麦*/
        {0xfd, 0xfd, 0xc5, 0xd5, 0x15, 0xd0, 0x15, 0xd5, 0xc5, 0xfd, 0x7d, 0x95, 0x6f, 0x45},/*克*/
        {0xff, 0x00, 0xfe, 0x7a, 0xb6, 0xce, 0xb6, 0x7a, 0xfe, 0x00, 0xff, 0xf9, 0xff, 0xcb},/*风*/
        {0x77, 0x01, 0x77, 0xff, 0xe1, 0x04, 0xad, 0x21, 0x4c, 0x05, 0xe1, 0xff, 0x43, 0x71},/*增*/
        {0xed, 0x2d, 0xb4, 0x35, 0xbd, 0xbd, 0x35, 0xb4, 0x2d, 0xed, 0xff, 0x11, 0x45, 0x74},/*益*/
        {0xdf, 0xa0, 0x6a, 0x0a, 0xea, 0xea, 0x0a, 0x6a, 0xa0, 0xdf, 0xff, 0x15, 0x45, 0x75},/*显*/
        {0xf7, 0x76, 0x96, 0xf6, 0xf6, 0x06, 0xf6, 0xf6, 0xd6, 0xb7, 0x77, 0x7e, 0xf1, 0xef},/*示*/
        {0xff, 0xdf, 0xdb, 0x29, 0xa4, 0x14, 0xab, 0x2d, 0xaf, 0xdf, 0xff, 0xeb, 0xf9, 0xfe},/*条*/
        {0xef, 0xee, 0x6e, 0x80, 0xee, 0xee, 0xee, 0x00, 0xee, 0xee, 0xef, 0xe7, 0x3f, 0x3f},/*开*/
        {0xbb, 0xcb, 0x00, 0xdb, 0xff, 0x00, 0xfe, 0xfe, 0x00, 0xff, 0x7f, 0xcf, 0xf9, 0xc4},/*机*/
        {0xff, 0x7f, 0x81, 0x2d, 0xa4, 0x25, 0xb5, 0x81, 0x7f, 0xff, 0xff, 0xb9, 0x05, 0x33},/*息*/
        {0xf7, 0x2e, 0xfd, 0xff, 0xef, 0x01, 0xf7, 0x80, 0xf7, 0xdb, 0x43, 0xfc, 0x53, 0x45},/*池*/
        {0xed, 0xf5, 0xf0, 0x0f, 0xaf, 0xaf, 0xaf, 0x10, 0xed, 0xee, 0xf7, 0x3f, 0x2a, 0x3f},/*背*/
        {0xef, 0xed, 0xeb, 0x27, 0xcf, 0xe0, 0x0f, 0xe7, 0xeb, 0xed, 0x6f, 0xe5, 0x4f, 0x45},/*光*/
        {0xef, 0x20, 0x8a, 0x4a, 0x0a, 0xea, 0xaa, 0x4a, 0xc0, 0x4f, 0xaf, 0xea, 0x5c, 56},/*最*/
        {0xbf, 0xcf, 0xf3, 0xff, 0xff, 0x00, 0xff, 0xff, 0xfb, 0xe7, 0x9f, 0x7f, 0xf1, 0xff},/*小*/
        {0xcd, 0xed, 0xe9, 0x25, 0xe4, 0xe5, 0x25, 0xe9, 0xed, 0xcd, 0xff, 0xe5, 0x4f, 0x71},/*亮*/
        {0xff, 0x01, 0xf5, 0xb5, 0x21, 0xa4, 0xa5, 0x21, 0xb5, 0xfd, 0xff, 0x59, 0x69, 0x75},/*度*/
        {0xfb, 0xfb, 0x7b, 0x9b, 0xe0, 0xdb, 0xbb, 0x7b, 0xfb, 0xfb, 0xff, 0xe5, 0xbf, 0xb5},/*大*/
        {0xff, 0x7f, 0x81, 0x15, 0xd5, 0xd5, 0xd4, 0xd5, 0xd5, 0x11, 0xff, 0x39, 0x55, 0x71},/*启*/
        {0xb7, 0x93, 0xa4, 0xb7, 0xfb, 0x2b, 0xab, 0xa0, 0xab, 0x2b, 0xfb, 0xa5, 0x53, 0x71},/*结*/
        {0xfd, 0xc5, 0x55, 0x95, 0xd5, 0x00, 0x95, 0x55, 0xd5, 0xc5, 0xfd, 0xfa, 0xf3, 0xda},/*束*/
        {0xff, 0x00, 0xfa, 0x5a, 0x4a, 0x4a, 0x0a, 0xa2, 0xaa, 0xba, 0xb8, 0xf9, 0x4f, 0x45},/*尾*/
        {0xfb, 0x36, 0xfd, 0xff, 0x06, 0x55, 0x50, 0x57, 0x53, 0x05, 0xfe, 0xfc, 0xfc, 0xf1},/*消*/
        {0xf6, 0x05, 0xff, 0xfb, 0xeb, 0x4b, 0x7b, 0x00, 0xfb, 0xfb, 0xff, 0x59, 0x55, 0x55},/*过*/
        {0xc3, 0xdb, 0xdb, 0xdb, 0xdb, 0x00, 0xdb, 0xdb, 0xdb, 0xdb, 0xc3, 0xff, 0xf3, 0xff},/*中*/
        {0x93, 0xac, 0xb7, 0xff, 0x00, 0xff, 0x29, 0xc7, 0x01, 0xc7, 0x29, 0xe5, 0x54, 0x55},/*继*/
        {0xff, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0xff, 0xff, 0xff, 0xff},/*一*/
        {0x00, 0xea, 0xaa, 0x60, 0xff, 0xff, 0x00, 0xbe, 0x7e, 0x80, 0xff, 0xe4, 0xce, 0xff},/*即*/
        {0x01, 0x7d, 0x01, 0xff, 0xdb, 0xd9, 0xd5, 0x00, 0xde, 0xd6, 0xdb, 0xff, 0x1f, 0x3f},/*呼*/
        {0xbf, 0xbf, 0x81, 0xb5, 0xa4, 0x25, 0xad, 0x01, 0xdf, 0xef, 0xff, 0x95, 0x1e, 0x3f},/*身*/
        {0xf7, 0x03, 0xfc, 0xf7, 0x6b, 0x8c, 0xef, 0xec, 0x0b, 0xf7, 0xff, 0x73, 0x5e, 0x7e},/*份*/
        {0xf6, 0x02, 0xf4, 0x06, 0xff, 0x7e, 0x60, 0x6e, 0xe0, 0x0f, 0xff, 0xab, 0x5f, 0x79},/*码*/
        {0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0xf7, 0xf7, 0xf7, 0xff, 0xff, 0x55, 0x51, 0x55},/*上*/
        {0xa7, 0x8b, 0xac, 0xb7, 0xff, 0xd7, 0xd7, 0x80, 0x6b, 0x6a, 0xa9, 0xa5, 0x97, 0x86},/*线*/
        {0xfe, 0xfe, 0xfe, 0xfe, 0x00, 0xfe, 0xf6, 0xee, 0xde, 0xfe, 0xff, 0xff, 0xfc, 0xff},/*下*/
        {0x01, 0x7d, 0x01, 0xff, 0x03, 0xfb, 0x09, 0x6a, 0x0b, 0xfb, 0x03, 0xff, 0xfc, 0xc7},/*响*/
        {0xff, 0x01, 0xfd, 0xed, 0x9d, 0xf5, 0xcc, 0x3d, 0xc5, 0xfd, 0xff, 0x59, 0x15, 0x35},/*应*/
        {0xf7, 0x03, 0xfc, 0xfb, 0xc3, 0x3b, 0xfa, 0xf9, 0x3b, 0xc3, 0xfb, 0x73, 0x15, 0x15},/*位*/
        {0xf6, 0xf2, 0x02, 0xb4, 0xc6, 0xff, 0x82, 0xfa, 0x00, 0xfa, 0x82, 0xc6, 0x9f, 0x9b},/*预*/
        {0xd7, 0x85, 0xa5, 0x00, 0xa5, 0x95, 0xf7, 0xc0, 0x37, 0xd6, 0x65, 0x2a, 0x9a, 0x8b},/*载*/
        {0xff, 0x36, 0xed, 0xff, 0x03, 0xf9, 0xcd, 0xad, 0x60, 0xad, 0xc9, 0x7c, 0x9e, 0x9b},/*波*/
        {0x0b, 0x55, 0x04, 0x55, 0x09, 0xff, 0xb6, 0x98, 0x0e, 0xb6, 0xf0, 0x6e, 0xac, 0xa8},/*解*/
        {0xfe, 0x00, 0x5a, 0x00, 0xbf, 0xff, 0xda, 0xd9, 0x03, 0xd9, 0xda, 0x3e, 0x9f, 0x9b},/*联*/
        {0xdf, 0xdd, 0x45, 0xc5, 0xc9, 0x0d, 0xd5, 0x5a, 0xee, 0xdf, 0xff, 0xfa, 0xf1, 0xfa},/*系*/
        {0xff, 0xff, 0x7f, 0x9f, 0xe7, 0xf8, 0xe7, 0x1f, 0xff, 0xff, 0xff, 0xf9, 0xff, 0xf6},/*人*/
        {0xfd, 0x15, 0x55, 0x15, 0x55, 0x50, 0x55, 0x15, 0x55, 0x15, 0xfd, 0xf9, 0xff, 0xff},/*声*/
        {0xdb, 0x00, 0xeb, 0xff, 0xe9, 0xcd, 0xd1, 0x1c, 0xd1, 0xcd, 0xe9, 0xf1, 0x15, 0x15},/*控*/
        {0xed, 0x09, 0xa0, 0xa9, 0x0d, 0xef, 0xab, 0xa8, 0x01, 0xab, 0x83, 0xa3, 0x7c, 0x7c},/*静*/
        {0x01, 0x7d, 0x01, 0xff, 0x63, 0x6b, 0x60, 0x3a, 0x60, 0x6b, 0x63, 0x7f, 0x39, 0x1b},/*噪*/
        {0xbb, 0xac, 0xa9, 0x25, 0xad, 0xab, 0xac, 0x85, 0x2d, 0xa9, 0xa5, 0xff, 0x5e, 0x7c},/*等*/
        {0x93, 0xa4, 0xbf, 0xff, 0xff, 0x7e, 0x80, 0xbe, 0x76, 0xb0, 0xc7, 0xe5, 0x99, 0x9b},/*级*/
        {0xd1, 0xdb, 0x00, 0xeb, 0xff, 0xd7, 0x95, 0x50, 0xd5, 0x05, 0xd7, 0xcf, 0xff, 0xf1},/*特*/
        {0xf7, 0x00, 0xb7, 0xff, 0xdf, 0x01, 0xef, 0x80, 0xd7, 0xb7, 0x87, 0xfe, 0x53, 0x45},/*地*/
        {0x00, 0xfe, 0xfe, 0x7a, 0xb6, 0xd6, 0xee, 0x96, 0x7a, 0xfe, 0xff, 0x54, 0x55, 0x75},/*区*/
        {0xff, 0x01, 0xd5, 0x7e, 0xf7, 0xd9, 0xae, 0x6e, 0xae, 0xd9, 0xf7, 0xe2, 0xe7, 0xf6},/*段*/
        {0xdf, 0xdb, 0xda, 0x59, 0x83, 0x9b, 0x59, 0xda, 0xdb, 0xdf, 0xff, 0xe5, 0xbf, 0xb5},/*关*/
        {0xaf, 0xab, 0x49, 0x6a, 0x43, 0x8b, 0xab, 0x4d, 0xab, 0xaf, 0xff, 0x57, 0xe9, 0xff},/*参*/
        {0xfb, 0x01, 0xfe, 0x06, 0xdb, 0xdd, 0xdd, 0x01, 0xdd, 0xde, 0xff, 0xb3, 0xd9, 0xe6},/*低*/
        {0x0d, 0xed, 0xe9, 0x25, 0xa5, 0xa4, 0x25, 0xe9, 0xed, 0x0d, 0xff, 0xbc, 0xea, 0xf1},/*高*/
        {0xf7, 0x03, 0xfc, 0xff, 0x01, 0x55, 0x15, 0x54, 0x15, 0x55, 0x11, 0x73, 0xcc, 0xcc},/*偏*/
        {0x6d, 0x8d, 0x01, 0xae, 0x7f, 0xab, 0x45, 0xcc, 0xcd, 0x55, 0x99, 0xcf, 0x95, 0xbe},/*移*/
        {0x06, 0xfd, 0x6f, 0x6e, 0xae, 0x02, 0xee, 0xee, 0xee, 0xfe, 0x00, 0xfc, 0xf1, 0xc7},/*闭*/
        {0xff, 0xfb, 0xdb, 0xdb, 0xda, 0x01, 0xdb, 0xdb, 0xdb, 0xfb, 0xff, 0x57, 0x51, 0x75},/*主*/
        {0xf8, 0x66, 0x9e, 0x66, 0xf8, 0xff, 0xf8, 0x66, 0x9e, 0x66, 0xf8, 0xb9, 0x9d, 0x9b},/*双*/
        {0xff, 0xff, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xff, 0xff, 0xab, 0xaa, 0xba},/*二*/
        {0xdf, 0xdf, 0xd0, 0x16, 0x56, 0x56, 0x56, 0x50, 0x5f, 0xdf, 0xff, 0xff, 0x57, 0x7e},/*号*/
        {0xff, 0x01, 0xf5, 0x15, 0xd5, 0xd5, 0xd6, 0xd6, 0x16, 0xf7, 0xff, 0x39, 0x55, 0x7c},/*后*/
        {0xb5, 0xa9, 0xa0, 0xa9, 0xa5, 0x2f, 0xa5, 0xa9, 0xa0, 0xa9, 0xb5, 0xe5, 0xf1, 0xd6},/*禁*/

     //   {0xcf, 0xd7, 0xd8, 0x5b, 0x9b, 0x80, 0x5b, 0xdb, 0xdb, 0xdf, 0xff, 0xe5, 0xbf, 0xb5},/*失*/
        {0xf7, 0x03, 0xfc, 0xff, 0xcd, 0xad, 0xa9, 0x28, 0xa9, 0xad, 0xcd, 0xf3, 0x17, 0x3f},/*停*/
        {0xff, 0xff, 0x07, 0xff, 0xff, 0x00, 0xf7, 0xf7, 0xf7, 0xff, 0xff, 0x45, 0x51, 0x55},/*止*/
        {0x75, 0x95, 0x01, 0xd6, 0x7e, 0x93, 0xfc, 0x01, 0xfd, 0xcd, 0x39, 0xcf, 0x1f, 0x3f},/*称*/
        {0xde, 0xde, 0xee, 0xf6, 0x02, 0xfc, 0xf6, 0xee, 0xde, 0xbe, 0xff, 0xff, 0xfc, 0xff},/*不*/
        {0x7b, 0xbb, 0x5b, 0x63, 0x7b, 0x00, 0x7b, 0x63, 0x5b, 0xbb, 0x7b, 0xff, 0xf3, 0xff},/*本*/
        {0xd3, 0x04, 0xd5, 0xff, 0xd7, 0x5b, 0x5d, 0x56, 0x5d, 0x5b, 0xd7, 0xd3, 0x5f, 0x7e},/*铃*/
        {0x00, 0xfe, 0xfe, 0x86, 0xb6, 0xb6, 0x86, 0xfe, 0xfe, 0x00, 0xff, 0x54, 0x55, 0x71},/*回*/
        {0xf7, 0xfb, 0xbb, 0xb5, 0xb5, 0x06, 0xb5, 0xb5, 0xbb, 0xfb, 0xf7, 0x57, 0x51, 0x75},/*全*/
        {0xef, 0x2d, 0xa5, 0xac, 0xa5, 0x2d, 0xef, 0x00, 0x76, 0x76, 0x88, 0x53, 0x31, 0x3f},/*部*/
        {0xc3, 0xdb, 0x00, 0xdb, 0x43, 0xff, 0xf7, 0xb5, 0x10, 0xb5, 0xf7, 0xa1, 0x5c, 0x54},/*蛙*/
        {0x01, 0x7d, 0x7d, 0x01, 0xff, 0x01, 0x7f, 0x7f, 0xbf, 0x00, 0xff, 0xff, 0xff, 0xf3},/*叫*/
        {0xff, 0x01, 0xd5, 0xd6, 0xc6, 0xff, 0x01, 0xed, 0xee, 0x0e, 0xef, 0xf9, 0xf9, 0xf3},/*所*/
        {0xdd, 0xed, 0x05, 0x51, 0x54, 0x55, 0x55, 0x55, 0x05, 0xfd, 0xff, 0xcf, 0x5f, 0x7c},/*有*/
        {0xff, 0x00, 0xb6, 0xb6, 0xb6, 0x00, 0xb6, 0xb6, 0xb6, 0x00, 0xff, 0xf9, 0xf3, 0xf1},/*用*/
        {0x00, 0xf7, 0xf7, 0xf7, 0x77, 0xff, 0x00, 0xf7, 0xf7, 0xfb, 0x7d, 0x94, 0x4f, 0x45},/*比*/
        {0xf7, 0x03, 0xfc, 0xdf, 0xee, 0xd0, 0x06, 0xff, 0x81, 0xff, 0x00, 0xf3, 0x79, 0x45},/*例*/
        {0xbf, 0xb5, 0xb5, 0xb5, 0x01, 0xb6, 0xb6, 0xb6, 0xb6, 0xbf, 0xff, 0x7f, 0xfc, 0xff},/*手*/
        {0xfb, 0x04, 0xf5, 0xf1, 0x15, 0xd7, 0xd3, 0x14, 0xf5, 0xf1, 0x05, 0xf3, 0xaa, 0x87},/*筒*/
        {0xee, 0x0d, 0xff, 0xff, 0x8f, 0x50, 0xde, 0xde, 0x50, 0x8f, 0xff, 0xe3, 0xa5, 0x95},/*设*/
        {0xff, 0x31, 0xbf, 0x20, 0xb7, 0xb8, 0x33, 0xab, 0x3b, 0xff, 0xff, 0x11, 0x45, 0x74},/*监*/
        {0x01, 0x7d, 0x01, 0xff, 0x01, 0xf5, 0xf5, 0x06, 0xf6, 0xf7, 0xff, 0x7f, 0x3e, 0x3f},/*听*/
        {0xf7, 0x01, 0x77, 0xb7, 0xff, 0x7d, 0x9d, 0xe1, 0xfd, 0xfd, 0x01, 0x7f, 0xf9, 0xc6},/*切*/
        {0xdb, 0x00, 0xeb, 0xbf, 0x87, 0xb3, 0x24, 0x15, 0xb1, 0x87, 0xbf, 0x71, 0xf9, 0xf6},/*换*/
        {0xef,0xf7,0xeb,0x6c,0x8f,0xef,0xec,0x0b,0xf7,0xef,0xff,0xe5,0x9f,0xbf},/*分*/
        {0x75,0x95,0x01,0xb6,0xff,0xe3,0xff,0xc0,0x7f,0xbb,0xd7,0xcf,0xa7,0xbf},/*秒*/

};