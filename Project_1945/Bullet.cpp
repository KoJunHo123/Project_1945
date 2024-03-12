#include "pch.h"
#include "Bullet.h"

CBullet::CBullet() : m_bIdentity(true), m_crash(false), m_damage(0), m_dr(DIRECTION_END), m_iBulletLevel(0), m_fAngle_1(0.f), m_bJusin(false)

{	 

}

CBullet::~CBullet()
{

}

void		CBullet::Initialize()
{
	m_eObjId = OBJ_BULLET;
}

int			CBullet::Update()
{
	if (m_bDead)	// �浹 ��
		return OBJ_DEAD;

	// �Ѿ� ���⿡ ���� �̵�
	switch (m_dr)
	{
	case TOP:
	{
		m_tObjInfo.fY -= m_fSpeed;
	}
	break;

	case LT:
	{
		switch (m_iBulletLevel)
		{
		case 3:
			m_tObjInfo.fX -= 0.5f;
			m_tObjInfo.fY -= sqrt(99.75);
			break;

		case 4:
			m_tObjInfo.fX -= 1.f;
			m_tObjInfo.fY -= sqrt(99);
			break;
		}

	}
	break;

	case RT:
	{
		switch (m_iBulletLevel)
		{
		case 3:
			m_tObjInfo.fX += 0.5f;
			m_tObjInfo.fY -= sqrt(99.75);
			break;

		case 4:
			m_tObjInfo.fX += 1.f;
			m_tObjInfo.fY -= sqrt(99);
			break;
		}
	}
	break;

	case BOTTOM:
	{
		m_tObjInfo.fY += m_fSpeed;
	}
	break;

	case FOLLOW:
	{
		if (m_bIdentity) // �÷��̾��� �Ѿ��̸�
		{
			if (m_pTarget->Get_IsDead() == false)
			{
				float hype = sqrtf(pow(m_tObjInfo.fX - m_pTarget->Get_Info().fX, 2) + pow(m_tObjInfo.fY - m_pTarget->Get_Info().fY, 2));
				m_fAngle_1 = acos((m_pTarget->Get_Info().fX - m_tObjInfo.fX) / hype);

				if (m_pTarget->Get_Info().fY - m_tObjInfo.fY < 0)
					m_fAngle_1 *= -1;
			}
			m_tObjInfo.fX += m_fSpeed * cos(m_fAngle_1);
			m_tObjInfo.fY += m_fSpeed * sin(m_fAngle_1);
		}
		else
		{
			m_tObjInfo.fX += m_fSpeed * cos(m_fAngle_1);
			m_tObjInfo.fY += m_fSpeed * sin(m_fAngle_1);
		}
	}
	break;

	case BOSS:
		float x = cos(m_fCeta);
		float y = sin(m_fCeta);

		m_tObjInfo.fX += m_fSpeed * x;
		m_tObjInfo.fY += m_fSpeed * y;
		break;

	break;
	}

	__super::Update_Pos();

	return OBJ_NOEVENT;
}

void		CBullet::Late_Update()
{
	if (m_bJusin)
	{
		if (m_tRect.top > WINCY)
			m_bDead = true;
	}
	else
	{
		if (m_tRect.left <0 || m_tRect.top<0 || m_tRect.right > WINCX || m_tRect.bottom > WINCY)
		{
			m_bDead = true;
		}
	}

}

void		CBullet::Render(HDC hDC)
{
	HBRUSH hNewBrush = CreateSolidBrush(RGB(0xff, 0, 0));
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);

	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	SelectObject(hDC, hOldBrush); // ������ ����ϴ���(Newpen)�� ������  
	DeleteObject(hNewBrush);
}

void		CBullet::Release()
{

}

// ����� �Ѿ��� ��ũ�� ���� �Ѿ� ������ ����
// ex) 3�ܰ��� ��� 2�ܰ� �Ѿ� 2��, 3�ܰ� �Ѿ� 2���� �Ҵ��ؾ� ��.
void		CBullet::SetBulletData(int _bulletRank, DIRECTION _dr)
{
	m_iBulletLevel = _bulletRank;
	m_fSpeed = 10.f;
	m_dr = _dr;
	m_bIdentity = true;
	switch (m_iBulletLevel)
	{
	case 1:
	{
		m_damage = 1;
		m_tObjInfo.fCX = 5.f;
		m_tObjInfo.fCY = 5.f;

	}
		break;

	case 2:
	{
		m_damage = 2;
		m_tObjInfo.fCX = 10.f;
		m_tObjInfo.fCY = 10.f;
	}
		break;

	case 3:
	{
		m_damage = 1;
		m_tObjInfo.fCX = 5.f;
		m_tObjInfo.fCY = 5.f;
	}
		break;

	case 4:
	{
		m_damage = 1;
		m_tObjInfo.fCX = 5.f;
		m_tObjInfo.fCY = 5.f;
	}
		break;
	}

}

// �� �⺻ �Ѿ� ����(������)
void		CBullet::SetEnemyBullet()
{
	m_fSpeed = 5.f;
	m_dr = BOTTOM;
	m_bIdentity = false;
	m_damage = 1;
	m_tObjInfo.fCX = 8.f;
	m_tObjInfo.fCY = 8.f;
}

// �� ���� �Ѿ� ����(���� �� �÷��̾��� ��ġ)
void		CBullet::SetFollowBullet()
{
	m_fSpeed = 5.f;
	m_damage = 1;
	m_tObjInfo.fCX = 10.f;
	m_tObjInfo.fCY = 10.f;

	// �� ó�� ���� �� Ÿ���� ��ġ.
	if (m_pTarget != nullptr)
	{
		m_dr = FOLLOW;
		float hype = sqrtf(pow(m_tObjInfo.fX - m_pTarget->Get_Info().fX, 2) + pow(m_tObjInfo.fY - m_pTarget->Get_Info().fY, 2));
		m_fAngle_1 = acos((m_pTarget->Get_Info().fX - m_tObjInfo.fX) / hype);
		if (m_pTarget->Get_Info().fY - m_tObjInfo.fY < 0)
		{
			m_fAngle_1 *= -1;
		}
	}
	else
	{
		if (m_bIdentity)
			m_dr = TOP;
		else
			m_dr = BOTTOM;
	}

}

void		CBullet::SetBossBullet(float _fCeta)
{
	m_fSpeed = 3.f;
	m_dr = BOSS;
	m_bIdentity = false;
	m_damage = 1;
	m_tObjInfo.fCX = 10.f;
	m_tObjInfo.fCY = 10.f;
	m_fCeta = _fCeta;
}


void CBullet::SetJusinBullet()
{
	m_fSpeed = 1.f;
	m_dr = BOTTOM;
	m_bIdentity = false;
	m_bJusin = true;
	m_damage = 1;
	m_tObjInfo.fCX = 8.f;
	m_tObjInfo.fCY = 8.f;

}

// �ִ� �Ÿ� Ȯ��
CObj* CBullet::CheckShortestDistance(list<CObj*> _targetList)
{
	CObj* returnTarget = nullptr;
	for (auto& elem : _targetList)
	{
		if (nullptr != elem)
		{
			// ���� Ȯ���ϴ� ����
			float ver = elem->Get_Info().fX - m_tObjInfo.fX;
			float hor = elem->Get_Info().fY - m_tObjInfo.fY;

			float hypo = sqrt(pow(ver, 2) + pow(hor, 2));
			if (nullptr != returnTarget)
			{
				// ���� ������ ����
				float nowVer = returnTarget->Get_Info().fX - m_tObjInfo.fX;
				float nowHor = returnTarget->Get_Info().fY - m_tObjInfo.fY;

				// ���� Ȯ���ϴ� ������ ���̰� ���� ������ ���̺��� ��� ��ü.
				if (hypo < sqrt(pow(nowVer, 2) + pow(nowHor, 2)))
				{
					returnTarget = elem;
				}
			}
			else
			{
				// ������ �� ������ ����.
				returnTarget = elem;
			}
		}
	}
	return returnTarget;
}

