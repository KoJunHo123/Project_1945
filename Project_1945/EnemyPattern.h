#pragma once
#include "MainGame.h"

// ����� �߰�
class CEnemyPattern
{
	//private:
	//	static DWORD m_dwTime;

public:
	CEnemyPattern();
	~CEnemyPattern();

public:
	static void				SetTarget(CObj* _target) { m_pTarget = _target; }

public:
	// ����Ʈ�� ���� �����߰��ϴ� ���̹Ƿ� ������ �����ؾ��Ѵ�

		// ���������
	static void EnemyA1(list<CObj*>& _Enemy, list<CObj*>& _Bullet); // ��� �ϳ�
	static void EnemyA2(list<CObj*>& _Enemy, list<CObj*>& _Bullet); // ��
	static void EnemyA3(list<CObj*>& _Enemy, list<CObj*>& _Bullet); // ��
	// ��ź
	static void EnemyB1(list<CObj*>& _Enemy, list<CObj*>& _Bullet); // ���� �ϳ�
	static void EnemyB2(list<CObj*>& _Enemy, list<CObj*>& _Bullet); // ������ �ϳ�
	static void EnemyB3(list<CObj*>& _Enemy, list<CObj*>& _Bullet); // ��
	// ���� �����
	static void EnemyC1(list<CObj*>& _Enemy, list<CObj*>& _Bullet); // ��� �ϳ�
	static void EnemyC2(list<CObj*>& _Enemy, list<CObj*>& _Bullet); // ��
	// �︮����
	static void EnemyD1(list<CObj*>& _Enemy, list<CObj*>& _Bullet, list<CObj*>& _Player); // ���ϴ�
	static void EnemyD2(list<CObj*>& _Enemy, list<CObj*>& _Bullet, list<CObj*>& _Player); // ���ϴ�
	// ���������
	static void EnemyE1(list<CObj*>& _Enemy, list<CObj*>& _Bullet); // �¹ݿ�
	// ����
	static void Boss(list<CObj*>& _Enemy, list<CObj*>& _Bullet); // T�� ���

private :
	static CObj* m_pTarget;
};