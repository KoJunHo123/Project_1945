#pragma once
#include "pch.h"
#include "Windows.h"
#include "Enemy.h"

//��ź --> x ��ǥ ����, y ��ǥ ����, �����̵�, ������ ���� �������� ��ź �߻�

class CEnemyB : public CEnemy {

public:
	CEnemyB() { }
	virtual ~CEnemyB() { Release(); }

public:
	virtual void Initialize() override {
		m_eObjId = OBJ_ENEMY;
		m_iHp = 10;
		m_iMaxHp = m_iHp;
		m_tObjInfo.fCX = 20.f; // ����� ũ��
		m_tObjInfo.fCY = 40.f; // ����� ũ��
		m_fSpeed = 1.f; // ����� �ӵ�
	}
	virtual int Update() override {
		if (m_bDead)
			return OBJ_DEAD;

		m_tObjInfo.fY += m_fSpeed; // �̵�
		Create_Bullet_Normal();

		__super::Update_Pos();
		return OBJ_NOEVENT;
	}
	virtual void Late_Update() override { CEnemy::Late_Update(); }
	virtual void Render(HDC hDC) override
	{
		HBRUSH hNewBrush = CreateSolidBrush(RGB(0, 0, 0));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);

		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

		SelectObject(hDC, hOldBrush); // ������ ����ϴ���(Newpen)�� ������  
		DeleteObject(hNewBrush);
	}
	virtual void Release() override {}
};