#pragma once
#include <Windows.h>
#include <conio.h>

// ----------------------------------------------------------------
// �ȴ����� "_getch" Ϊc++��׼�⺯��������int��������������
// 
// ����							KeyPress
// ������Ϣ						KeyPressToWindow
// �ȴ�����						_getch
// �жϰ���״̬					GetKeystatus
// ����_�����ȼ�_ע��				InstallKeyboardHook
// ����_�����ȼ�_ж��				UninstallKeyboardHook
// ��Ϣѭ��						LoopMessage
// ----------------------------------------------------------------

#define ����					KeyPress
#define ������Ϣ				KeyPressToWindow
#define �ȴ�����				_getch
#define �жϰ���״̬			GetKeystatus
#define ����_�����ȼ�_ע��	InstallKeyboardHook
#define ����_�����ȼ�_ж��	UninstallKeyboardHook
#define ��Ϣѭ��				LoopMessage

#define ����		256
#define �ſ�		257
#define ALT����	260
#define ������	kbStruct->vkCode

// �ȴ�����
// C++��׼�⺯��������ĳ�����󷵻ؼ�����
int __cdecl _getch(void);

class BF_Keyboard
{
public:
	// ����
	// keyCode: ��ĸ��ASCII�룬���ܼ���꣬��VK_F1
	// type: 1���� 2���� 3�ſ�
	static void KeyPress(int keyCode, int type);

	// ָ�����ڴ��ڷ���ģ�ⰴ����Ϣ
	// hWnd:	���ھ��
	// keyCode: ��ĸ��ASCII�룬���ܼ���꣬��VK_F1
	// type:	1���� 2���� 3�ſ�
	static void KeyPressToWindow(HWND hWnd, int keyCode, int type);

	// �жϰ���״̬
	// ���·����棬���𷵻ؼ�; �ú�����Ҫ������ѭ���в����𵽼������
	// keyCode �����룬 speed ����ٶ�(�ɺ��ԣ�Խ���ٶ�Խ�죬cpuԽ�ߣ�Ĭ��Ϊ10)
	// keyCode ����ĸʱ���ô�дASCII�룻��������ʱ���ñ�׼�꣨���磺F1: VK_F1)
	static BOOL GetKeystatus(int& keyCode, int speed = 10);

	// ����_�����ȼ�_ע��
	// callBack Ϊ�ص�����ָ��
	bool InstallKeyboardHook(HOOKPROC callBack);

	// ����_�����ȼ�_ж��
	bool UninstallKeyboardHook();

	// ��Ϣѭ��
	void LoopMessage();

private:
	static void SendKeyMessage(int& keyCode, bool type);
	static void SendKeyMessageToWindow1(HWND& hwnd, int& keyCode, bool keyDown);
	static void SendKeyMessageToWindow2(HWND& hwnd, int& keyCode, bool keyDown);

public:
	BF_Keyboard();
	~BF_Keyboard();

private:
	HHOOK hook;
	MSG msg;
};

BF_Keyboard::BF_Keyboard() { hook = NULL; }

BF_Keyboard::~BF_Keyboard() { if (hook != NULL) UninstallKeyboardHook(); }

void BF_Keyboard::KeyPress(int keyCode, int type)
{
	// 1 #����_ 2 #����_ 3 #�ſ�_

	if (type == 1)
	{
		SendKeyMessage(keyCode, true);
		SendKeyMessage(keyCode, false);
	}
	if (type == 2)
	{
		SendKeyMessage(keyCode, true);
	}
	if (type == 3)
	{
		SendKeyMessage(keyCode, false);
	}
}

void BF_Keyboard::SendKeyMessage(int& keyCode, bool type)
{
	INPUT input;

	// 1.���ýṹ��
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = 0;
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;

	// 2.���ü�����
	input.ki.wVk = keyCode;

	// 3.�жϼ�����
	if (type)
	{
		input.ki.dwFlags = 0;  // ����
	}
	else
	{
		input.ki.dwFlags = KEYEVENTF_KEYUP;  // ����
	}

	// 4.������Ϣ
	SendInput(1, &input, sizeof(INPUT));
}

void BF_Keyboard::SendKeyMessageToWindow1(HWND& hwnd, int& keyCode, bool keyDown)
{
	// ������̰�����Ϣ
	LPARAM lParam = 0;
	if (keyDown)
	{
		lParam |= (1 << 31);  // �� 31 λ��ʾ�����Ƿ�Ϊ����״̬
	}
	lParam |= (MapVirtualKey(keyCode, MAPVK_VK_TO_VSC) << 16);  // �� 16-23 λ��ʾɨ����
	if (keyDown == true)
	{

	}
	PostMessage(hwnd, WM_KEYDOWN, keyCode, lParam);  // ���Ͱ�����Ϣ
	PostMessage(hwnd, WM_KEYUP, keyCode, lParam | (1 << 30));  // ���͵�����Ϣ
}

void BF_Keyboard::KeyPressToWindow(HWND hWnd, int keyCode, int type)
{
	switch (type)
	{
	case 1: SendKeyMessageToWindow1(hWnd, keyCode, true); break;	// ����
	case 2: SendKeyMessageToWindow2(hWnd, keyCode, true); break;	// ����
	case 3: SendKeyMessageToWindow2(hWnd, keyCode, false); break;	// ����
	}

}

void BF_Keyboard::SendKeyMessageToWindow2(HWND& hwnd, int& keyCode, bool keyDown)
{
	LPARAM lParam = 0;
	if (keyDown)
	{
		lParam |= (1 << 31); // �� 31 λ��ʾ�����Ƿ�Ϊ����״̬
	}
	lParam |= (MapVirtualKey(keyCode, MAPVK_VK_TO_VSC) << 16); // �� 16-23 λ��ʾɨ����

	UINT message = keyDown ? WM_KEYDOWN : WM_KEYUP; // ���� keyDown �����ж��ǰ��»��ǵ������
	SendMessage(hwnd, message, keyCode, lParam);
}

// �жϰ���״̬
// ���·����棬���𷵻ؼ�; �ú�����Ҫ������ѭ���в����𵽼������
// keyCode �����룬 speed ����ٶ�(�ɺ��ԣ�Խ���ٶ�Խ�죬cpuԽ�ߣ�Ĭ��Ϊ10)
// keyCode ����ĸʱ���ô�дASCII�룻��������ʱ���ñ�׼�꣨���磺F1: VK_F1)
BOOL BF_Keyboard::GetKeystatus(int& keyCode, int speed)
{
	SHORT ret = GetAsyncKeyState(keyCode) & 0x8000;
	if (ret < 0)
	{
		if (speed == 0)
		{
			return true;
		}
		Sleep(speed);
		return true;
	}
	else
	{
		if (speed == 0)
		{
			return false;
		}
		Sleep(speed);
		return false;
	}
}

// ȫ�ֹ��ӻص�����ʾ��
/*
LRESULT CALLBACK KeyboardHookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT* kbStruct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
	// ���˴���д������

	if (wParam == ALT���� || ���� || �ſ�)	// ����
	{
		cout << "������" << ������ << endl;
	}

	// ���˴���д������
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

BF_Keyboard::LoopMessage();
*/
bool BF_Keyboard::InstallKeyboardHook(HOOKPROC callBack)
{
	this->hook = SetWindowsHookEx(WH_KEYBOARD_LL, callBack, NULL, 0);
	return (hook != NULL);
}

bool BF_Keyboard::UninstallKeyboardHook()
{
	BOOL result = UnhookWindowsHookEx(this->hook);
	hook = NULL;
	return (result != FALSE);
}

void BF_Keyboard::LoopMessage()
{
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


// ���Ӱ�װ����
//
//LRESULT CALLBACK KeyboardHookCallback(int nCode, WPARAM wParam, LPARAM lParam)
//{
//	KBDLLHOOKSTRUCT* kbStruct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
//	// ���˴���д������
//
//	if (wParam == ALT���� || ���� || �ſ�)	// ����
//	{
//		cout << "������" << ������ << endl;
//	}
//
//	// ���˴���д������
//	return CallNextHookEx(NULL, nCode, wParam, lParam);
//}
//int main()
//{
//	BF_Keyboard key;
//	key.InstallKeyboardHook(KeyboardHookCallback);
//	key.LoopMessage();
//	return 0;
//}
