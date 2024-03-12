#pragma once
#include "Obj.h"
#include "pch.h"
#include "Enemy.h"

//��������� --> �˵��� ���� ������, �ѹ��� 5����, �Ѿ� �߻� ����

class CEnemyE : public CEnemy {

private :
	// �̵���θ� ������������?
	float a; // ���� ������ x ��ǥ
	float b; // ���� ������ y ��ǥ
	float fDistance; // ���� ������
	float fAngle; // ���� ����
public:
	CEnemyE() : a(-100), b(300), fDistance(200), fAngle(180.f) { }
	virtual ~CEnemyE() { Release(); }

public:
	virtual void Initialize() override {
		m_eObjId = OBJ_ENEMY;
		m_iHp = 5;
 		m_iMaxHp = m_iHp;
		m_tObjInfo.fCX = 40.f; // ����� ũ��
		m_tObjInfo.fCY = 20.f; // ����� ũ��
		m_fSpeed = 2.f; // ����� �ӵ�(���ӵ�)
	}

	virtual int Update() override {
		if (m_bDead)
			return OBJ_DEAD;

		fAngle += m_fSpeed; // ������ �ӵ��� ����

		// ������ ������ ���� �߽����� �ﰢ�Լ��Ͽ� ���Ѵ�
		m_tObjInfo.fX = a + fDistance * cos(fAngle * (3.14 / 180.f));
		m_tObjInfo.fY = b - fDistance * sin(fAngle * (3.14 / 180.f));

		__super::Update_Pos();
		return OBJ_NOEVENT;
	}
	virtual void Late_Update() override { CEnemy::Late_Update(); }
	virtual void Release() override {}
};