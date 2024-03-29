﻿#pragma once

enum class VirtualKey : unsigned char {
    CONTROL = 0x11,
	
    KEY_0 = 0x30,
    KEY_1 = 0x31,
    KEY_2 = 0x32,
    KEY_3 = 0x33,
    KEY_4 = 0x34,
    KEY_5 = 0x35,
    KEY_6 = 0x36,
    KEY_7 = 0x37,
    KEY_8 = 0x38,
    KEY_9 = 0x39,
    KEY_A = 0x41,
    KEY_B = 0x42,
    KEY_C = 0x43,
    KEY_D = 0x44,
    KEY_E = 0x45,
    KEY_F = 0x46,
    KEY_G = 0x47,
    KEY_H = 0x48,
    KEY_I = 0x49,
    KEY_J = 0x4A,
    KEY_K = 0x4B,
    KEY_L = 0x4C,
    KEY_M = 0x4D,
    KEY_N = 0x4E,
    KEY_O = 0x4F,
    KEY_P = 0x50,
    KEY_Q = 0x51,
    KEY_R = 0x52,
    KEY_S = 0x53,
    KEY_T = 0x54,
    KEY_U = 0x55,
    KEY_V = 0x56,
    KEY_W = 0x57,
    KEY_X = 0x58,
    KEY_Y = 0x59,
    KEY_Z = 0x5A,

    NUMPAD_0 = 0x60,
    NUMPAD_1 = 0x61,
    NUMPAD_2 = 0x62,
    NUMPAD_3 = 0x63,
    NUMPAD_4 = 0x64,
    NUMPAD_5 = 0x65,
    NUMPAD_6 = 0x66,
    NUMPAD_7 = 0x67,
    NUMPAD_8 = 0x68,
    NUMPAD_9 = 0x69,

    OEM_1 = 0xBA,//	OEM_1(: ,)
    OEM_102 = 0xE2,//	OEM_102(> <)
    OEM_2 = 0xBF,//	OEM_2(? /)
    OEM_3 = 0xC0,//	OEM_3(~ `)
    OEM_4 = 0xDB,//	OEM_4({ [)
    OEM_5 = 0xDC,//	OEM_5(\| \)
    OEM_6 = 0xDD,//	OEM_6(} ])
    OEM_7 = 0xDE,//	OEM_7(" ')
    OEM_8 = 0xDF,//	OEM_8 (§ !)
    OEM_ATTN = 0xF0,//	Oem Attn
    OEM_AUTO = 0xF3,//	Auto
    OEM_AX = 0xE1,//	Ax
    OEM_BACKTAB = 0xF5,//	Back Tab
    OEM_CLEAR = 0xFE,//	OemClr
    OEM_COMMA = 0xBC,//	OEM_COMMA(< ,)
    OEM_COPY = 0xF2,//	Copy
    OEM_CUSEL = 0xEF,//	Cu Sel
    OEM_ENLW = 0xF4,//	Enlw
    OEM_FINISH = 0xF1,//	Finish
    OEM_FJ_LOYA = 0x95,//	Loya
    OEM_FJ_MASSHOU = 0x93,//	Mashu
    OEM_FJ_ROYA = 0x96,//	Roya
    OEM_FJ_TOUROKU = 0x94,//	Touroku
    OEM_JUMP = 0xEA,//	Jump
    OEM_MINUS = 0xBD,//	OEM_MINUS(_ -)
    OEM_PA1 = 0xEB,//	OemPa1
    OEM_PA2 = 0xEC,//	OemPa2
    OEM_PA3 = 0xED,//	OemPa3
    OEM_PERIOD = 0xBE,//	OEM_PERIOD(> .)
    OEM_PLUS = 0xBB,//	OEM_PLUS(+ =)
    OEM_RESET = 0xE9,//	Reset
    OEM_WSCTRL = 0xEE,//	WsCtrl
    PA1 = 0xFD,//	Pa1
    PACKET = 0xE7,//	Packet
    PLAY = 0xFA,//	Play
    PROCESSKEY = 0xE5,//	Process
    RETURN = 0x0D,//	Enter
    SELECT = 0x29,//	Select
    SEPARATOR = 0x6C,//	Separator
    SPACE = 0x20,//	Space
    SUBTRACT = 0x6D,//	Num -
    TAB = 0x09,//	Tab
    ZOOM = 0xFB,//	Zoom

    _none_ = 0xFF,//	no VK mapping
    ACCEPT = 0x1E,//	Accept
    APPS = 0x5D,//	Context Menu
    BROWSER_BACK = 0xA6,//	Browser Back
    BROWSER_FAVORITES = 0xAB,//	Browser Favorites
    BROWSER_FORWARD = 0xA7,//	Browser Forward
    BROWSER_HOME = 0xAC,//	Browser Home
    BROWSER_REFRESH = 0xA8,//	Browser Refresh
    BROWSER_SEARCH = 0xAA,//	Browser Search
    BROWSER_STOP = 0xA9,//	Browser Stop
    CAPITAL = 0x14,//	Caps Lock
    CONVERT = 0x1C,//	Convert
    DELETEKEY = 0x2E,//	Delete
    DOWN = 0x28,//	Arrow Down
    END = 0x23,//	End

    F1 = 0x70,//	F1
    F10 = 0x79,//	F10
    F11 = 0x7A,//	F11
    F12 = 0x7B,//	F12
    F13 = 0x7C,//	F13
    F14 = 0x7D,//	F14
    F15 = 0x7E,//	F15
    F16 = 0x7F,//	F16
    F17 = 0x80,//	F17
    F18 = 0x81,//	F18
    F19 = 0x82,//	F19
    F2 = 0x71,//	F2
    F20 = 0x83,//	F20
    F21 = 0x84,//	F21
    F22 = 0x85,//	F22
    F23 = 0x86,//	F23
    F24 = 0x87,//	F24
    F3 = 0x72,//	F3
    F4 = 0x73,//	F4
    F5 = 0x74,//	F5
    F6 = 0x75,//	F6
    F7 = 0x76,//	F7
    F8 = 0x77,//	F8
    F9 = 0x78,//	F9

    FINAL = 0x18,//	Final
    HELP = 0x2F,//	Help
    HOME = 0x24,//	Home
    ICO_00 = 0xE4,//	Ico00*
    INSERT = 0x2D,//	Insert
    JUNJA = 0x17,//	Junja
    KANA = 0x15,//	Kana
    KANJI = 0x19,//	Kanji
    LAUNCH_APP1 = 0xB6,//	App1
    LAUNCH_APP2 = 0xB7,//	App2
    LAUNCH_MAIL = 0xB4,//	Mail
    LAUNCH_MEDIA_SELECT = 0xB5,//	Media
    LBUTTON = 0x01,//	Left Button **
    LCONTROL = 0xA2,//	Left Ctrl
    LEFT = 0x25,//	Arrow Left
    LMENU = 0xA4,//	Left Alt
    LSHIFT = 0xA0,//	Left Shift
    LWIN = 0x5B,//	Left Win
    MBUTTON = 0x04,//	Middle Button **
    MEDIA_NEXT_TRACK = 0xB0,//	Next Track
    MEDIA_PLAY_PAUSE = 0xB3,//	Play / Pause
    MEDIA_PREV_TRACK = 0xB1,//	Previous Track
    MEDIA_STOP = 0xB2,//	Stop
    MODECHANGE = 0x1F,//	Mode Change
    NEXT = 0x22,//	Page Down
    NONCONVERT = 0x1D,//	Non Convert
    NUMLOCK = 0x90,//	Num Lock
    OEM_FJ_JISHO = 0x92,//	Jisho
    PAUSE = 0x13,//	Pause
    PRINT = 0x2A,//	Print
    PRIOR = 0x21,//	Page Up
    RBUTTON = 0x02,//	Right Button **
    RCONTROL = 0xA3,//	Right Ctrl
    RIGHT = 0x27,//	Arrow Right
    RMENU = 0xA5,//	Right Alt
    RSHIFT = 0xA1,//	Right Shift
    RWIN = 0x5C,//	Right Win
    SCROLL = 0x91,//	Scrol Lock
    SLEEP = 0x5F,//	Sleep
    SNAPSHOT = 0x2C,//	Print Screen
    UP = 0x26,//	Arrow Up
    VOLUME_DOWN = 0xAE,//	Volume Down
    VOLUME_MUTE = 0xAD,//	Volume Mute
    VOLUME_UP = 0xAF,//	Volume Up
    XBUTTON_1 = 0x05,//	X Button 1 **
    XBUTTON_2 = 0x06,//	X Button 2 **
};

class __declspec(dllexport) Keyboard
{
    bool virtual_keys[0XFE]{};
public:
	bool pressed(VirtualKey key) const;
	void set(VirtualKey key, bool active);
};
