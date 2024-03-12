#pragma once
#include "Obj.h"
#include "pch.h"
#include "Enemy.h"

//�︮���� --> ������� �̵�, ���� �̻��� �߻�
class CEnemyD : public CEnemy {

private:
	float x; // ����� ���� x ��ǥ
	float y; // ����� ���� y ��ǥ
	float a; // ������ ��ǥ
	float b; // ������ ��ǥ
	float d; // ��������(�Ÿ�)
	float fAngle; // acos()���� ���� ����
	int num;

public:
	CEnemyD() : x(0), y(0), a(0), b(0), d(0), fAngle(0), num(1) { }
	virtual ~CEnemyD() { Release(); }

public:
	virtual void Initialize() override {
		m_eObjId = OBJ_ENEMY;
		m_iHp = 8;
		m_iMaxHp = m_iHp;
		m_tObjInfo.fCX = 30.f; // ����� ũ��
		m_tObjInfo.fCY = 30.f; // ����� ũ��
		m_fSpeed = 1.5f; // ����� �ӵ�
	}
	virtual int Update() override {
		if (m_bDead)
			return OBJ_DEAD;

		x = m_tObjInfo.fX;
		y = m_tObjInfo.fY;

		switch (num) {
		case 1: a = 50; b = 500; // (50, 500)����
			if (x <= 50 || y <= 500) { num = 2; }  break;
		case 2: a = 450; b = 400; // (450, 400)���� 
			if (x >= 450 && y <= 400) { num = 3; } break;
		case 3: a = 50; b = 100; // (50, 100)����
			if (x <= 50 && y <= 100) { num = 4; } break;
		case 4: a = 450; b = 200; // (450, 200)���� 
			if (x >= 450 && y >= 200) { num = 5; } break;
		case 5: a = 50; b = 500; // (50, 500)���� 
			if (x <= 50 && y >= 500) { num = 1; } break;
		}

		Create_Bullet_Follow();

		d = sqrt(((a - x) * (a - x)) + ((b - y) * (b - y)));
		fAngle = acosf((a - x) / d);
		m_tObjInfo.fX += (float)(m_fSpeed * cos(fAngle));
		if (b < y) { m_tObjInfo.fY -= m_fSpeed * sin(fAngle); }
		else { m_tObjInfo.fY -= -m_fSpeed * sin(fAngle); }

		__super::Update_Pos();
		return OBJ_NOEVENT;
	}
	virtual void Late_Update() override { CEnemy::Late_Update(); }
	virtual void Release() override {}
};