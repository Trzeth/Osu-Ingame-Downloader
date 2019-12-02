#pragma once
#ifndef __CLOG__
#define __CLOG__
#include <string>
#include <fstream>
#include <tchar.h>
#include "rw_lock.h"
class logger {
public:
	logger();
	~logger();
	template <class T>
	static void WriteLog(T x);
	//֧�ָ�ʽ�������������
	static void WriteLogFormat(const char* format, ...);
	static std::string GetSystemTimes();
private:
	static std::string GetFilePath();
	std::string m_LogFilePath;
	static bool IsPathExist(const std::string FilePath);
};

//֧�����int double �ı� 
template <class T> void logger::WriteLog(T x) {
	std::fstream of(GetFilePath(), std::ios::app);
	if (!of.is_open()) {
		return;
	}
	of.seekp(std::ios::end);  //�����ļ�ָ�뵽�ļ�β��
	of << GetSystemTimes() << ": " << x << std::endl;
	of.close();  //�ر��ļ���
}
#endif