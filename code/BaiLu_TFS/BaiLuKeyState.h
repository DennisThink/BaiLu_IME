#ifndef _BAI_LU_KEY_STATE_H_
#define _BAI_LU_KEY_STATE_H_
enum class Combine_Key_State
{
	None,
	Control,//Ctrl
	Shift,
	Control_S,//Ctrl+S
	Control_Shift,//Ctrl+Shift
};

class CBaiLuKeyState
{
public:
	static CBaiLuKeyState* GetInstance();
	Combine_Key_State GetState();
private:
	bool IsKeyPressed(const short value);
	bool IsKeyToggled(const short value);
	CBaiLuKeyState();
	virtual ~CBaiLuKeyState();

};
#endif