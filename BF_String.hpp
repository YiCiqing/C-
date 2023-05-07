#pragma once
#include <string>
#include <Windows.h>
#include <cctype>		// std::tolower
#include <algorithm>	// std::search
#include <iterator>
#include <vector>

// --------------------------------------
// ��std::string����Ϊ�ַ�������
// 
// ȡ�ı����		GetStrLeft
// ȡ�ı��ұ�		GetStrRight
// ȡ�ı�����		GetStrLength
// ȡ�ı��м�		GetStrMiddle
// ȡ�ֽ�����		GetStrBytes
// Ѱ���ı�			FindString
// ��Сд			GetStrLower
// ����д			GetStrHigher
// ���ı�			ToString
// ɾ�׿�			DeleteFrontSpaces
// ɾβ��			DeleteLastSpaces
// �ָ��ı�			SplitStr
// �ı��滻			ReplaceSubString
// �ı��Ƚ�			CompareStr
// --------------------------------------

#define ȡ�ı����	GetStrLeft
#define ȡ�ı��ұ�	GetStrRight
#define ȡ�ı�����	GetStrLength
#define ȡ�ı��м�	GetStrMiddle
#define ȡ�ֽ�����	GetStrBytes
#define Ѱ���ı�		GetStrBytes
#define ��Сд		GetStrLower
#define ����д		GetStrHigher
#define ���ı�		ToString
#define ɾ�׿�		DeleteFrontSpaces
#define ɾβ��		DeleteLastSpaces
#define �ָ��ı�		SplitStr
#define �ı��滻		ReplaceSubString
#define �ı��Ƚ�		CompareStr

class BF_String
{
public:
	// ȡ�ı����
	// ����һ���ı������а���ָ���ı��д��������ָ���������ַ���������Ϊ�������
	// ����<1>������Ϊ����ȡ�䲿�ֵ��ı���������Ϊ���ı��ͣ�text������
	// ����<2>������Ϊ����ȡ���ַ�����Ŀ��������Ϊ�������ͣ�int������
	std::string GetStrLeft(std::string source, int length);
	// ȡ�ı��ұ�
	// ����һ���ı������а���ָ���ı��д��ұ�����ָ���������ַ���������Ϊ�������
	// ����<1>������Ϊ����ȡ�䲿�ֵ��ı���������Ϊ���ı��ͣ�text������
	// ����<2>������Ϊ����ȡ���ַ�����Ŀ��������Ϊ�������ͣ�int������
	std::string GetStrRight(std::string source, int length);
	// ȡ�ı�����
	// ����<1>������Ϊ���ı����ݡ�������Ϊ���ı��ͣ�text����������ֵָ��������䳤�ȵ��ı����ݡ�
	int GetStrLength(std::string source);
	// ȡ�ı��м�
	// ����һ���ı������а���ָ���ı��д�ָ��λ������ָ���������ַ���������Ϊ�������
	// ����<1>������Ϊ����ȡ�䲿�ֵ��ı���������Ϊ���ı��ͣ�text������
	// ����<2>������Ϊ����ʼȡ��λ�á�������Ϊ�������ͣ�int������1Ϊ��λ�ã�2Ϊ��2��λ�ã�������ơ�
	// ����<3>������Ϊ����ȡ���ַ�����Ŀ��������Ϊ�������ͣ�int������
	std::string GetStrMiddle(std::string source, int start, int length);
	// ȡ�ı��ֽ�����
	// ����char[]���ֽ�����
	const char* GetStrBytes(std::string& source);
	// Ѱ���ı�
	// ����һ������ֵ��ָ��һ�ı�����һ�ı������ȳ��ֵ�λ�ã�λ��ֵ��  ��ʼ�����δ�ҵ������� - 1��������Ϊ�������
	// ����<1>������Ϊ������Ѱ���ı���������Ϊ���ı��ͣ�text������
	// ����<2>������Ϊ����Ѱ�ҵ��ı���������Ϊ���ı��ͣ�text������
	// ����<3>������Ϊ���Ƿ����ִ�Сд��������Ϊ���߼��ͣ�bool��������ʼֵΪ���١���Ϊ�治���ִ�Сд��Ϊ�����֡�
	std::size_t FindString(const std::string& source, const std::string& subStr, bool judge);	// judgeΪtrue���Դ�Сд false������  // ʧ�ܷ���4294967295
	// ��Сд
	// ����<1>������Ϊ�����任���ı���������Ϊ���ı��ͣ�text������
	// ����<1>������Ϊ�����任���ı���������Ϊ���ı��ͣ�text������
	std::string GetStrLower(std::string source);
	// ����д
	// ���ı��е�СдӢ����ĸ�任Ϊ��д�����ر任��Ľ���ı���������Ϊ�������
	// ����<1>������Ϊ�����任���ı���������Ϊ���ı��ͣ�text������
	std::string GetStrHigher(std::string source);
	// ���ı� ֧�� �������������������������������߼��͡��ֽ��͡��ֽڼ���˫���ȸ��㡢�޷����������������������������ڣ� -- �����ͻ�û��������������
	// ����һ���ı�������ָ����ֵ���߼�ֵ������ʱ�䱻ת����Ľ�������Ϊ�ı����ݣ�����ֱ�ӷ��ء�������Ϊ�������
	// ����<1>������Ϊ����ת�������ݡ�������Ϊ��ͨ���ͣ�all�������ṩ��������ʱ����ͬʱ�ṩ�������������ݡ�����ֵֻ��Ϊ��ֵ���߼�ֵ���ֽڼ�������ʱ�����ֵ�����顣
	std::string ToString(int source);
	std::string ToString(long long source);
	std::string ToString(short source);
	std::string ToString(float source);
	std::string ToString(bool source);
	std::string ToString(char source);
	std::string ToString(char& source);
	std::string ToString(long double source);
	std::string ToString(unsigned int source);
	std::string ToString(unsigned long long source);
	// ɾ�׿�
	// ����һ���ı������а�����ɾ�����ײ�ȫ�ǻ��ǿո��ָ���ı���������Ϊ�������
	// ����<1>������Ϊ����ɾ���ո���ı���������Ϊ���ı��ͣ�text������
	std::string DeleteFrontSpaces(std::string source);
	// ɾβ��
	// ����һ���ı������а�����ɾ����β��ȫ�ǻ��ǿո��ָ���ı���������Ϊ�������
	// ����<1>������Ϊ����ɾ���ո���ı���������Ϊ���ı��ͣ�text������
	std::string DeleteLastSpaces(std::string str);
	// �ָ��ı�
	//��ָ���ı����зָ���طָ���һά�ı����顣������Ϊ�������
	// ����<1>������Ϊ�����ָ��ı���������Ϊ���ı��ͣ�text�������������ֵ��һ������Ϊ����ı����򷵻�һ�������飬��û���κγ�Ա�����顣
	// ����<2>������Ϊ�������ָ���ı���������Ϊ���ı��ͣ�text���������Ա�ʡ�ԡ�����ֵ���ڱ�ʶ���ı��߽硣�����ʡ�ԣ���Ĭ��ʹ�ð�Ƕ����ַ���Ϊ�ָ����������һ������Ϊ����ı����򷵻ص����������һ����Ա���������ġ����ָ��ı�����
	// ����<3>������Ϊ��Ҫ���ص����ı���Ŀ��������Ϊ�������ͣ�int���������Ա�ʡ�ԡ������ʡ�ԣ���Ĭ�Ϸ������е����ı���
	std::vector<std::string> SplitStr(const std::string& source, const std::string& splitStr);
	// �ı��滻
	// ��ָ���ı���ĳһ�������������ı��滻��������Ϊ�������
	// ����<1>������Ϊ�������滻���ı���������Ϊ���ı��ͣ�text������
	// ����<2>������Ϊ����ʼ�滻λ�á�������Ϊ�������ͣ�int�������滻����ʼλ�ã�1Ϊ��λ�ã�2Ϊ��2��λ�ã�������ơ�
	// ����<3>������Ϊ���滻���ȡ�������Ϊ�������ͣ�int������
	// ����<4>������Ϊ�������滻���ı���������Ϊ���ı��ͣ�text���������Ա�ʡ�ԡ������������ʡ�ԣ���ɾ���ı��е�ָ�����֡�
	std::string ReplaceSubString(std::string source, int start, int length, std::string subString);
	// �ı��Ƚ�
	//�������ֵС��0����ʾ�ı�һС���ı������������0����ʾ�ı�һ�����ı������������0����ʾ�ı�һ�����ı���������Ƚ�ʱ���ִ�Сд��Ҳ����ʹ�ñȽ����������ͬ���Ĳ�����������Ϊ�������
	// ����<1>������Ϊ�����Ƚ��ı�һ��������Ϊ���ı��ͣ�text������
	// ����<2>������Ϊ�����Ƚ��ı�����������Ϊ���ı��ͣ�text������
	// ����<3>������Ϊ���Ƿ����ִ�Сд��������Ϊ���߼��ͣ�bool��������ʼֵΪ���桱��Ϊ�����ִ�Сд��Ϊ�ٲ����֡�
	bool CompareStr(std::string string1, std::string string2, bool judge);

public:
	BF_String();
	~BF_String();
};

BF_String::BF_String() {}
BF_String::~BF_String() {}

std::string BF_String::GetStrLeft(std::string source, int length)
{
	std::string retStr = source.substr(0, length);
	return retStr;
}

std::string BF_String::GetStrRight(std::string source, int length)
{
	int sourceLength = source.length();
	std::string retStr = source.substr(sourceLength - length, length);
	return retStr;
}

int BF_String::GetStrLength(std::string source)
{
	int length = source.length();
	return length;
}

std::string BF_String::GetStrMiddle(std::string source, int start, int length)
{
	std::string ret = source.substr(start, length);
	return ret;
}

const char* BF_String::GetStrBytes(std::string& source)
{
	const char* ret = source.data();
	return ret;
}

std::size_t BF_String::FindString(const std::string& source, const std::string& subStr, bool judge)
{
	if (judge == true)
	{
		std::string sourceLower, subStrLower;
		// ��������תΪСд
		std::transform(source.begin(), source.end(), back_inserter(sourceLower), [](char c) { return std::tolower(c); });
		std::transform(subStr.begin(), subStr.end(), back_inserter(subStrLower), [](char c) { return std::tolower(c); });

		// �����ִ� �����ִ�Сд
		auto it = std::search(sourceLower.begin(), sourceLower.end(), subStrLower.begin(), subStrLower.end());

		if (it != sourceLower.end()) {
			return std::distance(sourceLower.begin(), it);
		}
		else {
			return std::string::npos;
		}
	}
	else
	{
		// �����ִ� ���ִ�Сд
		auto it = std::search(source.begin(), source.end(), subStr.begin(), subStr.end());

		if (it != source.end()) {
			return std::distance(source.begin(), it);
		}
		else {
			return std::string::npos;
		}
	}
}

std::string BF_String::GetStrLower(std::string source)
{
	std::string sourceLower;
	// תΪСд
	std::transform(source.begin(), source.end(), back_inserter(sourceLower), [](char c) { return std::tolower(c); });
	return sourceLower;
}

std::string BF_String::GetStrHigher(std::string source)
{
	std::string sourceHigher;
	// תΪСд
	std::transform(source.begin(), source.end(), back_inserter(sourceHigher), [](char c) { return std::toupper(c); });
	return sourceHigher;
}

std::string BF_String::ToString(int source)
{
	std::string ret = std::to_string(source);
	return ret;
}

std::string BF_String::ToString(long long source)
{
	std::string ret = std::to_string(source);
	return ret;
}

std::string BF_String::ToString(short source)
{
	std::string ret = std::to_string(source);
	return ret;
}

std::string BF_String::ToString(float source)
{
	std::string ret = std::to_string(source);
	return ret;
}

std::string BF_String::ToString(bool source)
{
	std::string ret;
	if (source == true)
	{
		ret = "true";
	}
	else
	{
		ret = "false";
	}
	return ret;
}

std::string BF_String::ToString(char source)
{
	char arr[2] = { source, 0 };
	std::string ret(arr);
	return ret;
}

std::string BF_String::ToString(char& source)
{
	std::string ret = std::to_string(source);
	return ret;
}

std::string BF_String::ToString(long double source)
{
	std::string ret = std::to_string(source);
	return ret;
}

std::string BF_String::ToString(unsigned int source)
{
	std::string ret = std::to_string(source);
	return ret;
}

std::string BF_String::ToString(unsigned long long source)
{
	std::string ret = std::to_string(source);
	return ret;
}

std::string BF_String::DeleteFrontSpaces(std::string source)
{
	// ���ҵ�һ���ǿո��ַ���λ��
	size_t pos = source.find_first_not_of(' ');

	if (pos == std::string::npos) {
		// ���û�зǿո��ַ����򷵻ؿ��ַ���
		return "";
	}
	else {
		// ɾ��ǰ��Ŀո�
		source.erase(0, pos);
		return source;
	}
}

std::string BF_String::DeleteLastSpaces(std::string str) {
	// �ҵ����һ���ǿո��ַ���λ��
	std::size_t pos = str.find_last_not_of(' ');
	if (pos != std::string::npos) {
		// ɾ�����λ��֮��������ַ�
		str.erase(pos + 1);
	}
	else {
		// ����ַ���ȫ�ǿո���ɾ�������ַ���
		str.clear();
	}
	return str;
}

std::vector<std::string> BF_String::SplitStr(const std::string& source, const std::string& splitStr) {
	std::vector<std::string> result;
	size_t pos = 0, last_pos = 0;
	while ((pos = source.find(splitStr, last_pos)) != std::string::npos) {
		if (pos != last_pos) {
			result.push_back(source.substr(last_pos, pos - last_pos));
		}
		last_pos = pos + splitStr.length();
	}
	if (last_pos < source.length()) {
		result.push_back(source.substr(last_pos));
	}
	return result;
}

std::string BF_String::ReplaceSubString(std::string source, int start, int length, std::string subString)
{
	// �ж��滻�����Ƿ�С�ڵ����滻�ı��ĳ���
	if (length <= subString.length()) {
		// ʹ���滻�ı���ǰ b ���ַ���Ϊ�滻�ı�
		subString = subString.substr(0, length);
	}
	else {
		// ʹ�ÿո�������ĳ���
		subString.append(length - subString.length(), ' ');
	}

	// �滻�ı�
	source.replace(start, length, subString);

	return source;
}

bool BF_String::CompareStr(std::string string1, std::string string2, bool judge) {
	if (judge) {
		// ���Դ�Сд
		std::transform(string1.begin(), string1.end(), string1.begin(), ::tolower);
		std::transform(string2.begin(), string2.end(), string2.begin(), ::tolower);
	}
	// �Ƚϴ��Ƿ����
	return string1.compare(string2) == 0;
}
