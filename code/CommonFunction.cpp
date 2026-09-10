#include "CommonFunction.hpp"
std::string VirtualKeyCodeToString(UINT vkCode)
{
	// 用于存储键名的缓冲区
	char keyName[256] = { 0 };

	// 将虚拟键码转换为扫描码
	UINT scanCode = MapVirtualKey(vkCode, MAPVK_VK_TO_VSC);

	// 构造lParam用于GetKeyNameText函数
	// 高16位放扫描码，低16位中的第25位（bit24）用于指示扩展键
	LONG lParam = (scanCode << 16);

	// 获取键名
	if (GetKeyNameTextA(lParam, keyName, sizeof(keyName)) > 0) {
		return std::string(keyName);
	}

	return "Unknown Key";
}