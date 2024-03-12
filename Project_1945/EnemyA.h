#pragma once
#include "pch.h"
#include "Windows.h"
#include "Enemy.h"

//��������� --> x ��ǥ ����, y ��ǥ ����, �����̵�, �Ѿ� 2�߾� �߻�
class CEnemyA : public CEnemy {

public:
	CEnemyA() { }
	virtual ~CEnemyA() { Release(); }

public:
	virtual void Initialize() override {
		m_eObjId = OBJ_ENEMY;
		m_iHp = 6;
		m_iMaxHp = m_iHp;
		m_tObjInfo.fCX = 20.f; // ����� ũ��
		m_tObjInfo.fCY = 40.f; // ����� ũ��
		m_fSpeed = 1.5f; // ����� �ӵ�
	}
	virtual int Update() override {
		if (m_bDead)
			return OBJ_DEAD;
		
		m_tObjInfo.fY += m_fSpeed; // �̵�
		Create_Bullet_Normal();

		__super::Update_Pos();
		return OBJ_NOEVENT; // 0
	}
	virtual void Late_Update() override { CEnemy::Late_Update(); }
	virtual void Release() override {}
};