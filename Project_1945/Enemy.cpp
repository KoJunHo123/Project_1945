#include "pch.h"
#include "Enemy.h"

void		CEnemy::Initialize()
{
}

int			CEnemy::Update()
{	
	return 0;
}

void		CEnemy::Late_Update()
{
	// �Ʒ��� ���������� ����
	if (m_tRect.top > WINCY)
	{
		m_bDead = true;
	}

	if (m_iHp <= 0)
	{
		m_Score = m_iMaxHp * 10;
		m_bDead = true;
	}
}

void		CEnemy::Render(HDC hDC)
{
	HBRUSH hNewBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);

	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	SelectObject(hDC, hOldBrush); // ������ ����ϴ���(Newpen)�� ������  
	DeleteObject(hNewBrush);
}

void		CEnemy::Release()
{
}

void		CEnemy::Create_Bullet_Normal() {

	if (dwTime + 1500 < GetTickCount()) {
		m_pBulletList->push_back(CAbstractFactory<CBullet>::CreateObj(m_tObjInfo.fX, m_tObjInfo.fY)); // ���� ��ġ�� ����
		static_cast<CBullet*>(m_pBulletList->back())->SetEnemyBullet(); // �Ϲ� �Ѿ˷� ����
		dwTime = GetTickCount();
	}
}

void		CEnemy::Create_Bullet_Follow() {

	if (dwTime + 1500 < GetTickCount()) {
		m_pBulletList->push_back(CAbstractFactory<CBullet>::CreateObj(m_tObjInfo.fX, m_tObjInfo.fY)); // ���� ��ġ�� ����
		static_cast<CBullet*>(m_pBulletList->back())->SetTarget(m_pTarget); // �÷��̾� ��ġ ��������
		static_cast<CBullet*>(m_pBulletList->back())->Set_Identity(false);
		static_cast<CBullet*>(m_pBulletList->back())->SetFollowBullet(); // �Ϲ� �Ѿ˷� ����
		dwTime = GetTickCount();
	}
}

void		CEnemy::Create_Bullet_Boss()
{
	DWORD bossBulletTime = GetTickCount();

	if (dwTime + 400 < GetTickCount()) {
	
		int r = rand() % 8 + 1;
		for (int i = 270; i <= 360; i += r)
		{
			m_pBulletList->push_back(CAbstractFactory<CBullet>::CreateObj(m_tObjInfo.fX, m_tObjInfo.fY)); // ���� ��ġ�� ����
			static_cast<CBullet*>(m_pBulletList->back())->SetBossBullet((float)i);
			dwTime = GetTickCount();
		}
		
	}
}
