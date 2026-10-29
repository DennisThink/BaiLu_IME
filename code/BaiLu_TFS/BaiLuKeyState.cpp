#include "BaiLuKeyState.h"
#include <Windows.h>
CBaiLuKeyState* CBaiLuKeyState::GetInstance()
{
	static CBaiLuKeyState gInstance;
	return &gInstance;
}

Combine_Key_State CBaiLuKeyState::GetState()
{
	Combine_Key_State result = Combine_Key_State::None;

	bool bControl = false;
	bool bShift = false;
	bool bCharS = false;
	{
		int control = GetKeyState(VK_CONTROL);
		if (IsKeyPressed(control))
		{
			bControl = true;
		}
	}
	{
		int control = GetKeyState(VK_SHIFT);
		if (IsKeyPressed(control))
		{
			bShift = true;
		}	
	}
	if (bControl && !bShift)
	{
		result = Combine_Key_State::Control;
	}

	else if (!bControl && bShift)
	{
		result = Combine_Key_State::Shift;
	}

	if (bControl && bShift)
	{
		result = Combine_Key_State::Control_Shift;
	}
	return result;
}


CBaiLuKeyState::CBaiLuKeyState()
{

}

CBaiLuKeyState::~CBaiLuKeyState()
{

}

bool CBaiLuKeyState::IsKeyPressed(const short value)
{
	const short mask = 0xF0;
	if ((value & mask) > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool CBaiLuKeyState::IsKeyToggled(const short value)
{
	const short mask = 0x0F;
	if ((value & mask) > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}