#include "Menu.h"

struct Option_Class Menu_SettingOptionList[];

void Set_CursorStyle(void)
{
	if (Menu_Global.CursorStyle == reverse)
	{
		Menu_Global.CursorStyle = mouse;
		Menu_SettingOptionList[1].String = "Ani Style[mos]";
	}
	else if (Menu_Global.CursorStyle == mouse)
	{
		Menu_Global.CursorStyle = frame;
		Menu_SettingOptionList[1].String = "Ani Style[rec]";
	}
	else
	{
		Menu_Global.CursorStyle = reverse;
		Menu_SettingOptionList[1].String = "Ani Style[Inv]";
	}
}

void Set_animation_speed(void)
{
	static int8_t State = 0;

	if (State == 0)
	{
		Menu_Global.Cursor_ActSpeed = 0.2;
		Menu_Global.Slide_ActSpeed = 4;
		Menu_SettingOptionList[2].String = "Ani Speed[Fast]";
		State++;
	}
	else if (State == 1)
	{
		Menu_Global.Cursor_ActSpeed = 1;
		Menu_Global.Slide_ActSpeed = 16;
		Menu_SettingOptionList[2].String = "Ani Speed[Off]";
		State++;
	}
	else if (State == 2)
	{
		Menu_Global.Cursor_ActSpeed = 0.1;
		Menu_Global.Slide_ActSpeed = 1.26;
		Menu_SettingOptionList[2].String = "Ani Speed[Slow]";
		State++;
	}
	else
	{
		Menu_Global.Cursor_ActSpeed = 0.15;
		Menu_Global.Slide_ActSpeed = 2;
		Menu_SettingOptionList[2].String = "Ani Speed[Mid]";
		State = 0;
	}
}

void Menu_RunSettingMenu(void)
{
	Menu_RunMenu(Menu_SettingOptionList);
}

struct Option_Class Menu_SettingOptionList[] = {
	{"<<<"},
	{"Ani Style[Inv]", Set_CursorStyle},
	{"Ani Speed[Mid]", Set_animation_speed},
	{".."}
};
