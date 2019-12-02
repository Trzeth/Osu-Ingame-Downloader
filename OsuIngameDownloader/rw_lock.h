#pragma once
#ifndef _RWLockImpl_Header
#define _RWLockImpl_Header
#include <assert.h>
#include <iostream>
#include <Windows.h>
#include <process.h>

// from https://blog.csdn.net/meijia_tts/article/details/7225229

using namespace std;

// ��д������ǰ�Ķ�����û����ʱ�����Դ����ֻ����һ��д���߷��ʱ�����Դ
class RWLockImpl
{
protected:
	RWLockImpl();
	~RWLockImpl();
	void ReadLockImpl();
	bool TryReadLockImpl();
	void WriteLockImpl();
	bool TryWriteLockImpl();
	void UnlockImpl();

private:
	void AddWriter();
	void RemoveWriter();
	DWORD TryReadLockOnce();

	HANDLE   m_mutex;
	HANDLE   m_readEvent;
	HANDLE   m_writeEvent;
	unsigned m_readers;
	unsigned m_writersWaiting;
	unsigned m_writers;
};

class LK : private RWLockImpl
{
public:
	//������/д��
	LK() {};

	//���ٶ�/д��
	~LK() {};

	//��ȡ����
	//�������һ���߳�ռ��д������ǰ�̱߳���ȴ�д�����ͷţ����ܶԱ�����Դ���з���
	void ReadLock();

	//���Ի�ȡһ������
	//�����ȡ�ɹ�������������true��������һ���߳�ռ��д�����򷵻�false
	bool TryReadLock();

	//��ȡд��
	//���һ��������߳�ռ�ж����������ȴ����������ͷ�
	//�����ͬ��һ���߳��Ѿ�ռ��һ��������д�����򷵻ؽ����ȷ��
	void WriteLock();

	//���Ի�ȡһ��д��
	//�����ȡ�ɹ�������������true������һ������������߳�ռ�ж���������false
	//�����ͬ��һ���߳��Ѿ�ռ��һ��������д�����򷵻ؽ����ȷ��
	bool TryWriteLock();

	//�ͷ�һ��������д��
	void Unlock();

private:
	LK(const LK&);
};

inline void LK::ReadLock()
{
	ReadLockImpl();
}

inline bool LK::TryReadLock()
{
	return TryReadLockImpl();
}

inline void LK::WriteLock()
{
	WriteLockImpl();
}

inline bool LK::TryWriteLock()
{
	return TryWriteLockImpl();
}

inline void LK::Unlock()
{
	UnlockImpl();
}
#endif