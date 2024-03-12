#pragma once
#include "pch.h"
#include "EnemyPattern.h"
#include "Boss.h"

CEnemyPattern::CEnemyPattern()
{
}
CEnemyPattern::	~CEnemyPattern() {}

// ���������
void CEnemyPattern::EnemyA1(list<CObj*>& _Enemy, list<CObj*>& _Bullet) // ��� �ϳ�
{
	CObj* pEnemy = CAbstractFactory<CEnemyA>::CreateObj(250, -50);
	static_cast<CEnemy*>(pEnemy)->Set_BulletList(&_Bullet);
	//m_pObjList[OBJ_ENEMY].push_back(pEnemy);
	_Enemy.push_back(pEnemy);
}
void CEnemyPattern::EnemyA2(list<CObj*>& _Enemy, list<CObj*>& _Bullet)  // ��
{
	CObj* pEnemy = CAbstractFactory<CEnemyA>::CreateObj(170, -50);
	static_cast<CEnemy*>(pEnemy)->Set_BulletList(&_Bullet);
	_Enemy.push_back(pEnemy);
}
void CEnemyPattern::EnemyA3(list<CObj*>& _Enemy, list<CObj*>& _Bullet) // ��
{
	CObj* pEnemy = CAbstractFactory<CEnemyA>::CreateObj(100, -50);
	static_cast<CEnemy*>(pEnemy)->Set_BulletList(&_Bullet);
	_Enemy.push_back(pEnemy);

	CObj* pEnemy1 = CAbstractFactory<CEnemyA>::CreateObj(250, -50);
	static_cast<CEnemy*>(pEnemy1)->Set_BulletList(&_Bullet);
	_Enemy.push_back(pEnemy1);

	CObj* pEnemy2 = CAbstractFactory<CEnemyA>::CreateObj(400, -50);
	static_cast<CEnemy*>(pEnemy2)->Set_BulletList(&_Bullet);
	_Enemy.push_back(pEnemy2);
}

// ��ź
void CEnemyPattern::EnemyB1(list<CObj*>& _Enemy, list<CObj*>& _Bullet) // ���� �ϳ�
{
	CObj* pEnemy = CAbstractFactory<CEnemyB>::CreateObj(100, -50);
	static_cast<CEnemy*>(pEnemy)->Set_BulletList(&_Bullet);
	_Enemy.push_back(pEnemy);
}
void CEnemyPattern::EnemyB2(list<CObj*>& _Enemy, list<CObj*>& _Bullet) // ������ �ϳ�
{
	CObj* pEnemy = CAbstractFactory<CEnemyB>::CreateObj(400, -50);
	static_cast<CEnemy*>(pEnemy)->Set_BulletList(&_Bullet);
	_Enemy.push_back(pEnemy);
}
void CEnemyPattern::EnemyB3(list<CObj*>& _Enemy, list<CObj*>& _Bullet)  // ��
{
	CObj* pEnemy = CAbstractFactory<CEnemyB>::CreateObj(100, -50);
	static_cast<CEnemy*>(pEnemy)->Set_BulletList(&_Bullet);
	_Enemy.push_back(pEnemy);

	CObj* pEnemy1 = CAbstractFactory<CEnemyB>::CreateObj(400, -50);
	static_cast<CEnemy*>(pEnemy1)->Set_BulletList(&_Bullet);
	_Enemy.push_back(pEnemy1);
}

// ���� �����
void CEnemyPattern::EnemyC1(list<CObj*>& _Enemy, list<CObj*>& _Bullet) // ��� �ϳ�
{
	CObj* pEnemy = CAbstractFactory<CEnemyC>::CreateObj(250, -50);
	static_cast<CEnemy*>(pEnemy)->Set_BulletList(&_Bullet);
	_Enemy.push_back(pEnemy);
}
void CEnemyPattern::EnemyC2(list<CObj*>& _Enemy, list<CObj*>& _Bullet) // ��
{
	CObj* pEnemy = CAbstractFactory<CEnemyC>::CreateObj(150, -50);
	static_cast<CEnemy*>(pEnemy)->Set_BulletList(&_Bullet);
	_Enemy.push_back(pEnemy);

	CObj* pEnemy1 = CAbstractFactory<CEnemyC>::CreateObj(350, -50);
	static_cast<CEnemy*>(pEnemy1)->Set_BulletList(&_Bullet);
	_Enemy.push_back(pEnemy1);
}

// �︮����
void CEnemyPattern::EnemyD1(list<CObj*>& _Enemy, list<CObj*>& _Bullet, list<CObj*>& _Player) // ���ϴ�
{
	CObj* pEnemy = CAbstractFactory<CEnemyD>::CreateObj(-50, 550);
	static_cast<CEnemy*>(pEnemy)->Set_CopyPlayer(&_Player);
	static_cast<CEnemy*>(pEnemy)->Set_BulletList(&_Bullet);
	_Enemy.push_back(pEnemy);
}
void CEnemyPattern::EnemyD2(list<CObj*>& _Enemy, list<CObj*>& _Bullet, list<CObj*>& _Player) // ���ϴ�
{
	CObj* pEnemy = CAbstractFactory<CEnemyD>::CreateObj(550, 550);
	static_cast<CEnemy*>(pEnemy)->Set_CopyPlayer(&_Player);
	static_cast<CEnemy*>(pEnemy)->Set_BulletList(&_Bullet);
	_Enemy.push_back(pEnemy);
}

// ���������
void CEnemyPattern::EnemyE1(list<CObj*>& _Enemy, list<CObj*>& _Bullet) // �¹ݿ�
{
	CObj* pEnemy = CAbstractFactory<CEnemyE>::CreateObj();
	static_cast<CEnemy*>(pEnemy)->Set_BulletList(&_Bullet);
	_Enemy.push_back(pEnemy);
}

// ����
void CEnemyPattern::Boss(list<CObj*>& _Enemy, list<CObj*>& _Bullet) // T�� ���
{
	CObj* pEnemy = CAbstractFactory<CBoss>::CreateObj(250, -50);
	static_cast<CEnemy*>(pEnemy)->Set_BulletList(&_Bullet);
	_Enemy.push_back(pEnemy);
}
