#pragma once
#include "pch.h"
#include "Windows.h"
#include "Enemy.h"

//��������� --> x ��ǥ ����, y ��ǥ ����, ũ�⺯��
class CEnemyC : public CEnemy {

public:
	CEnemyC() { }
	virtual ~CEnemyC() { Release(); }

public:
	virtual void Initialize() override {
		m_eObjId = OBJ_ENEMY;
		m_iHp = 10;
		m_iMaxHp = m_iHp;
		m_tObjInfo.fCX = 30.f; // ����� ũ��
		m_tObjInfo.fCY = 40.f; // ����� ũ��
		m_fSpeed = 0.7f; // ����� �ӵ�
	}
	virtual int Update() override {
		if (m_bDead)
			return OBJ_DEAD;

		m_tObjInfo.fY += m_fSpeed; // �̵�

		if (m_tObjInfo.fY >= 80) { // Ư����ġ���� ũ�� Ŀ��
			if (m_tObjInfo.fCX < 60) {
				m_tObjInfo.fCX += 2;
				m_tObjInfo.fCY += 3;
			}
			else
			{
				Create_Bullet_Normal();
			}
		} 
		__super::Update_Pos();
		return OBJ_NOEVENT;
	}
	virtual void Late_Update() override { CEnemy::Late_Update(); }
	virtual void Release() override {}
};