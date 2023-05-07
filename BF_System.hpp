#pragma once
#include <Windows.h>
#include <iostream>
#include <string>

// ---------------------------------------------------------------
// ʹ�ÿ���̨�������ͷ�ʱ�����붨��Ϊȫ�ֶ���
//
// ��������̨	AllocConsole
// �ͷſ���̨	FreeConsole
// �رտ���̨	CloseConsole
// ����			RunExe
// ȡ�������ı�	Getclipboard
// �ü������ı�	Setclipboard
// ���������	ClearClipboard
// ����			Beep
// ȡ����ʱ��	clock
// ��ʱ			Sleep
// ȡ��ǰĿ¼	GetNowDirectory
// ȡִ���ļ���	GetNowProcessName
// ---------------------------------------------------------------

#define ��������̨	AllocConsole
#define �ͷſ���̨	FreeConsole
#define �رտ���̨	CloseConsole
#define ����			RunExe
#define ȡ�������ı�	Getclipboard
#define �ü������ı�	Setclipboard
#define ���������	ClearClipboard
#define ����			Beep
#define ȡ����ʱ��	clock
#define ��ʱ			Sleep
#define ȡ��ǰĿ¼	GetNowDirectory
#define ȡִ���ļ���	GetNowProcessName

class BF_System
{
public:
	BOOL AllocConsole();	// ��������̨(MFC��)
	BOOL FreeConsole();		// �ͷſ���̨��ֹͣ���
	BOOL CloseConsole();	// �ͷſ���̨ + �رտ���̨����

	// ����
	// ����������ָ���Ŀ�ִ���ļ������ⲿ�������ɹ��������棬���򷵻ؼ١�������Ϊ�������
	// ����<1>������Ϊ�������е������С�������Ϊ���ı��ͣ�text������
	static bool RunExe(std::string directory/*Ŀ¼*/);

	// ȡ�������ı�
	// ���ش���ڵ�ǰ Windows ϵͳ�������е��ı��������ǰ�����������ı����ݣ������ؿ��ı���������Ϊ�������
	static std::string Getclipboard(); 

	// �ü������ı�
	// ��ָ���ı���ŵ���ǰ Windows ϵͳ��������ȥ���������е�ԭ�����ݱ����ǡ��ɹ������棬ʧ�ܷ��ؼ١�������Ϊ�������
	// ����<1>������Ϊ��׼�������������ı���������Ϊ���ı��ͣ�text������
	static bool Setclipboard(const std::string& text); 

	// ���������
	// �����ǰ Windows ϵͳ�������е��������ݡ�������Ϊ�������
	static bool ClearClipboard();		

	// ����--��ֱ�ӵ��ñ�׼�� Beep(int, int);
	// ͨ�������ý���豸�������ȷ���һ��������������Ϊ�������
	static BOOL Beep(DWORD frequent, DWORD time);		

	// ȡ����ʱ��	-- ���ñ�׼��clock(); // �������ĳ�δ����ִ��ʱ��
	// clock();		
	
	// ��ʱ			-- ���ñ�׼��Sleep();
	// Sleep();		
	
	// ȡ��ǰĿ¼
	// ȡ��ǰ��ִ�е�C�����ļ�������Ŀ¼��������Ϊ�������
	static std::string GetNowDirectory();

	// ȡִ���ļ���
	// ȡ��ǰ��ִ�е��׳����ļ������ơ�������Ϊ�������
	static std::string GetNowProcessName();		

public:
	BF_System();
	~BF_System();
private:
	bool console_exist;
	FILE* fp;
	HWND console_Hwnd;
	DWORD console_dwProcessId;
	HANDLE console_hProcess;
};

BF_System::BF_System()
{
	console_exist = false; // ��֤��һ�ο�������ɹ�
	fp = NULL;
	console_Hwnd = NULL;
	console_dwProcessId = NULL;
	console_hProcess = NULL;
}

BF_System::~BF_System()
{
	if (fp != nullptr)
	{
		FreeConsole();
	}
}

BOOL BF_System::AllocConsole()
{
	// ����ԭʼ�ı�׼�����  -- δ������ִ�к�original_stdout��Ϊ��
	// freopen_s(&original_stdout, "CONOUT$", "w", stdout);
	if (console_exist == true)
	{
		return false;
	}
	BOOL ret = ::AllocConsole();
	if (ret == false)
	{
		return false;
	}
	console_exist = true;
	// ��ȡ����̨���ھ��
	console_Hwnd = GetConsoleWindow();
	//// ��ȡ����̨���ڵĽ���ID
	//GetWindowThreadProcessId(console_Hwnd, &console_dwProcessId);
	//// ��ȡ����̨���ڵĽ��̾��
	//console_hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, console_dwProcessId);
	// �����ϲ���ʧ��
	if (console_Hwnd == NULL)
	{
		FreeConsole();
		return FALSE;
	}

	// �ض���
	freopen_s(&fp, "CONOUT$", "w", stdout);
	return true;
}

BOOL BF_System::FreeConsole()
{
	// �رտ���̨����
	BOOL ret = ::FreeConsole();
	if (ret == true)
	{
		console_exist = false;
	}
	// �ָ���׼����� -- δ���ļ�������ָ�
	//freopen_s(&fp, "CONOUT$", "w", original_stdout);
	return ret;
}

BOOL BF_System::CloseConsole()
{
	auto ret = FreeConsole();
	Sleep(10);
	auto ret2 = PostMessage(console_Hwnd, WM_CLOSE, 0, 0);
	return ret2;
}

bool BF_System::RunExe(std::string commandLine)
{
	// �������������õ�����������û������
	bool waitForCompletion = false;
	int windowShowStyle = SW_SHOWNORMAL;

	STARTUPINFO startupInfo = { sizeof(startupInfo) };
	PROCESS_INFORMATION processInfo;
	bool success = false;

	if (CreateProcess(NULL, &commandLine[0], NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo)) {
		if (waitForCompletion) {
			WaitForSingleObject(processInfo.hProcess, INFINITE);
		}
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
		success = true;
	}
	return success;
}

std::string BF_System::Getclipboard() {
	std::string clipboardText = "";

	if (OpenClipboard(NULL)) {
		HANDLE clipboardData = GetClipboardData(CF_TEXT);
		if (clipboardData != NULL) {
			char* clipboardTextPtr = (char*)GlobalLock(clipboardData);
			if (clipboardTextPtr != NULL) {
				clipboardText = clipboardTextPtr;
				GlobalUnlock(clipboardData);
			}
		}
		CloseClipboard();
	}

	return clipboardText;
}

bool BF_System::Setclipboard(const std::string& text) {
	bool result = false;

	if (OpenClipboard(NULL)) {
		EmptyClipboard();
		HGLOBAL clipboardData = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
		if (clipboardData != NULL) {
			char* clipboardDataPtr = (char*)GlobalLock(clipboardData);
			if (clipboardDataPtr != NULL) {
				memcpy(clipboardDataPtr, text.c_str(), text.size() + 1);
				GlobalUnlock(clipboardData);
				SetClipboardData(CF_TEXT, clipboardData);
				result = true;
			}
		}
		CloseClipboard();
	}

	return result;
}

bool BF_System::ClearClipboard()
{
	if (!OpenClipboard(NULL))
	{
		return false;
	}

	if (!EmptyClipboard())
	{
		CloseClipboard();
		return false;
	}

	CloseClipboard();
	return true;
}

BOOL BF_System::Beep(DWORD frequent, DWORD time)
{
	auto ret = ::Beep(frequent, time);
	return ret;
}

std::string BF_System::GetNowDirectory()
{
	char buffer[MAX_PATH];
	::GetModuleFileNameA(nullptr, buffer, MAX_PATH);
	std::string path(buffer);
	size_t pos = path.find_last_of("\\/");
	return (pos == std::string::npos) ? "" : path.substr(0, pos);
}

std::string BF_System::GetNowProcessName() {
	char filename[MAX_PATH];
	GetModuleFileName(NULL, filename, MAX_PATH);
	return std::string(filename);
}

