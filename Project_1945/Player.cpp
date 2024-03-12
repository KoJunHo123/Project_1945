#include "pch.h"
#include "Player.h"


CPlayer::CPlayer() :m_fStartY(500.f), m_BlinkTick(0), m_DestroyTick(0), m_InvincibleTick(0), m_iBombCount(0), m_BulletTick(0),
					m_fEffectsize(0.f), m_bulletList(nullptr), m_BombTick(0), m_bIsBomb(false), m_bIsShoot(true), m_GuidedTick(0)
{
	ZeroMemory(&m_tPlayerInfo, sizeof(PLAYERINFO));
	ZeroMemory(&m_tBombInfo, sizeof(OBJINFO));
	
}

CPlayer::~CPlayer()
{
	Release();
}

void		CPlayer::Initialize()
{
	m_fSpeed = 5.f;
	Set_Pos(250, 650);
	Set_Size(20, 60);
	m_tPlayerInfo = { 3,1, false, APPEAR };	//hp, �Ѿ˼�, �������� �ʱ�ȭ

	m_tBombInfo.fCX = 200;
	m_tBombInfo.fCY = 200;

	m_eObjId = OBJ_PLAYER;
}

int			CPlayer::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	//������ �� �ִ� ���¶��
	if (m_tPlayerInfo.eState == PLAYING)
	{
		Move_Player();
		if(m_bIsShoot)
			Create_Bullet();
		Use_Bomb();
	}
	__super::Update_Pos();

	return OBJ_NOEVENT;
}

void		CPlayer::Late_Update()
{
#pragma region ����� �ӽ� Ű �Է¿�
	//�ӽ� �������� ���
	if (GetAsyncKeyState('I'))
	{
		m_tPlayerInfo.bIsInvincible = true;
		m_InvincibleTick = GetTickCount();
		m_BlinkTick = GetTickCount();
	}
#pragma endregion ����� �ӽ� Ű �Է¿�

	if (m_tPlayerInfo.bIsInvincible)
	{
		Invincible_Time();
	}

	if (m_tPlayerInfo.eState == DESTROY)
	{
		Destroy_Player();
		if (m_fEffectsize <= 50)
			m_fEffectsize += 1.5f;
	}

	if (m_tPlayerInfo.eState == APPEAR)
	{
		Appear_Player();
	}

}

void		CPlayer::Render(HDC hDC)
{
	//hp�� 0 �̻��� ���� ����
	if (m_tPlayerInfo.iHp > 0)
	{
		//��ź ������ ����Ʈ ����
		if (m_bIsBomb)
		{
			Ellipse(hDC, (int)(m_tBombInfo.fX - m_fEffectsize), (int)(m_tBombInfo.fY - m_fEffectsize), (int)(m_tBombInfo.fX + m_fEffectsize), (int)(m_tBombInfo.fY + m_fEffectsize));
		}

		//���� ���� ���
		if (m_tPlayerInfo.bIsInvincible)
		{
			if (m_BlinkTick +300 < GetTickCount())
			{
				Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
				m_BlinkTick = GetTickCount();
			}
		}
		
		if (!m_tPlayerInfo.bIsInvincible && m_tPlayerInfo.eState != DESTROY)
			Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

		//�ı� ����Ʈ ����
		if (m_tPlayerInfo.eState == DESTROY)
		{
			m_fEffectsize += 0.2f;
			Ellipse(hDC, (int)(m_tObjInfo.fX - m_fEffectsize), (int)(m_tObjInfo.fY - m_fEffectsize), (int)(m_tObjInfo.fX + m_fEffectsize), (int)(m_tObjInfo.fY + m_fEffectsize));
		}
	}

	//hp ���� �׷��ֱ�
	for (int i = 0; i < m_tPlayerInfo.iHp; ++i)
	{
		Ellipse(hDC, 0 + i*20, 30, 20 +i*20, 50);
	}

	//��ź ������ ���� �׷��ֱ�
	for (int i = 0; i < m_iBombCount; ++i)
	{
		Ellipse(hDC, 0 + i * 20, WINCY-50, i * 20+20, WINCY-20);
	}
}

void		CPlayer::Release()
{
}

//������
void		CPlayer::Move_Player()
{

	if (GetAsyncKeyState(VK_RIGHT) && m_tObjInfo.fX + (m_tObjInfo.fCX * 0.5) < WINCX)
	{
		if (GetAsyncKeyState(VK_UP) && m_tObjInfo.fY - (m_tObjInfo.fCY * 0.5) > 0)
		{
			m_tObjInfo.fX += (float)(m_fSpeed / sqrt(2.f));
			m_tObjInfo.fY -= (float)(m_fSpeed / sqrt(2.f));
		}
		else if (GetAsyncKeyState(VK_DOWN) && m_tObjInfo.fY + (m_tObjInfo.fCY * 0.5) < WINCY)
		{
			m_tObjInfo.fX += (float)(m_fSpeed / sqrt(2.f));
			m_tObjInfo.fY += (float)(m_fSpeed / sqrt(2.f));
		}
		else
			m_tObjInfo.fX += m_fSpeed;
	}

	else if (GetAsyncKeyState(VK_LEFT) && m_tObjInfo.fX - (m_tObjInfo.fCX * 0.5) > 0)
	{
		if (GetAsyncKeyState(VK_UP) && m_tObjInfo.fY - (m_tObjInfo.fCY * 0.5) > 0)
		{
			m_tObjInfo.fX -= (float)m_fSpeed / sqrt(2.f);
			m_tObjInfo.fY -= (float)m_fSpeed / sqrt(2.f);
		}
		else if (GetAsyncKeyState(VK_DOWN) && m_tObjInfo.fY + (m_tObjInfo.fCY * 0.5) < WINCY)
		{
			m_tObjInfo.fX -= (float)(m_fSpeed / sqrt(2.f));
			m_tObjInfo.fY += (float)(m_fSpeed / sqrt(2.f));
		}
		else
			m_tObjInfo.fX -= m_fSpeed;

	}
	else if (GetAsyncKeyState(VK_UP) && m_tObjInfo.fY - (m_tObjInfo.fCY * 0.5) > 0)
	{
		m_tObjInfo.fY -= m_fSpeed;
	}
	else if (GetAsyncKeyState(VK_DOWN) && m_tObjInfo.fY + (m_tObjInfo.fCY * 0.5) < WINCY)
	{
		m_tObjInfo.fY += m_fSpeed;
	}

}

//�÷��̾ �� �Ѿ��� ������ ȣ��
void		CPlayer::Damaged_Player()
{
	if (!m_tPlayerInfo.bIsInvincible&& m_tPlayerInfo.eState == PLAYING)
	{
		m_tPlayerInfo.eState = DESTROY;
		m_DestroyTick = GetTickCount();
		m_fEffectsize = 0.5f;
		m_tPlayerInfo.bIsInvincible = true;
	}
}

void		CPlayer::Destroy_Player()
{
	if (m_DestroyTick + 1500 < GetTickCount())
	{
		Set_Pos(250, 650);
		m_tPlayerInfo.eState = APPEAR;
		--m_tPlayerInfo.iHp;
		
		if (m_tPlayerInfo.iHp <= 0)
		{
			m_tPlayerInfo.eState = DEAD;
			m_bDead = true;
		}

	}
}

//�÷��̾� ���� �Լ�
void		CPlayer::Appear_Player()
{
	if (m_fStartY >= m_tObjInfo.fY)
	{
		m_tPlayerInfo.eState = PLAYING;
		Set_Invincible();
	}

		m_tObjInfo.fY -= 5.0f;
	
}

void		CPlayer::Invincible_Time()
{
	if (m_InvincibleTick + 2500 < GetTickCount())
	{
		m_tPlayerInfo.bIsInvincible = false;
	}
}

void		CPlayer::Create_Bullet()
{
	int gap = 10;

	//�Ѿ� ����
	if (m_BulletTick + 200 < GetTickCount())
	{
		switch (m_tPlayerInfo.iBulletLevel)
		{
		case 1:
		case 2:
			m_bulletList->push_back(CAbstractFactory<CBullet>::CreateObj());
			m_bulletList->back()->Set_Pos(m_tObjInfo.fX - gap, m_tObjInfo.fY);	// �߾��� �������� ��, ��� gapĭ �������� ��ġ ����.
			static_cast<CBullet*>(m_bulletList->back())->SetBulletData(m_tPlayerInfo.iBulletLevel, TOP);			// �Ѿ��� ��ũ, ���� ����

			m_bulletList->push_back(CAbstractFactory<CBullet>::CreateObj());
			m_bulletList->back()->Set_Pos(m_tObjInfo.fX + gap, m_tObjInfo.fY);
			static_cast<CBullet*>(m_bulletList->back())->SetBulletData(m_tPlayerInfo.iBulletLevel, TOP);
			break;

		case 3:
			m_bulletList->push_back(CAbstractFactory<CBullet>::CreateObj());
			m_bulletList->back()->Set_Pos(m_tObjInfo.fX - gap, m_tObjInfo.fY);	// �߾��� �������� ��, ��� gapĭ �������� ��ġ ����.
			static_cast<CBullet*>(m_bulletList->back())->SetBulletData(m_tPlayerInfo.iBulletLevel - 1, TOP);			// �Ѿ��� ��ũ, ���� ����

			m_bulletList->push_back(CAbstractFactory<CBullet>::CreateObj());
			m_bulletList->back()->Set_Pos(m_tObjInfo.fX + gap, m_tObjInfo.fY);
			static_cast<CBullet*>(m_bulletList->back())->SetBulletData(m_tPlayerInfo.iBulletLevel - 1, TOP);

			m_bulletList->push_back(CAbstractFactory<CBullet>::CreateObj());
			m_bulletList->back()->Set_Pos(m_tObjInfo.fX - (gap + 5), m_tObjInfo.fY);
			static_cast<CBullet*>(m_bulletList->back())->SetBulletData(m_tPlayerInfo.iBulletLevel, LT);

			m_bulletList->push_back(CAbstractFactory<CBullet>::CreateObj());
			m_bulletList->back()->Set_Pos(m_tObjInfo.fX + (gap + 5), m_tObjInfo.fY);
			static_cast<CBullet*>(m_bulletList->back())->SetBulletData(m_tPlayerInfo.iBulletLevel, RT);
			break;

		case 4:
			m_bulletList->push_back(CAbstractFactory<CBullet>::CreateObj());
			m_bulletList->back()->Set_Pos(m_tObjInfo.fX - gap, m_tObjInfo.fY);	// �߾��� �������� ��, ��� gapĭ �������� ��ġ ����.
			static_cast<CBullet*>(m_bulletList->back())->SetBulletData(m_tPlayerInfo.iBulletLevel - 2, TOP);			// �Ѿ��� ��ũ, ���� ����

			m_bulletList->push_back(CAbstractFactory<CBullet>::CreateObj());
			m_bulletList->back()->Set_Pos(m_tObjInfo.fX + gap, m_tObjInfo.fY);
			static_cast<CBullet*>(m_bulletList->back())->SetBulletData(m_tPlayerInfo.iBulletLevel - 2, TOP);

			m_bulletList->push_back(CAbstractFactory<CBullet>::CreateObj());
			m_bulletList->back()->Set_Pos(m_tObjInfo.fX - (gap + 5), m_tObjInfo.fY);
			static_cast<CBullet*>(m_bulletList->back())->SetBulletData(m_tPlayerInfo.iBulletLevel - 1, LT);

			m_bulletList->push_back(CAbstractFactory<CBullet>::CreateObj());
			m_bulletList->back()->Set_Pos(m_tObjInfo.fX + (gap + 5), m_tObjInfo.fY);
			static_cast<CBullet*>(m_bulletList->back())->SetBulletData(m_tPlayerInfo.iBulletLevel - 1, RT);

			m_bulletList->push_back(CAbstractFactory<CBullet>::CreateObj());
			m_bulletList->back()->Set_Pos(m_tObjInfo.fX - (gap + 8), m_tObjInfo.fY);
			static_cast<CBullet*>(m_bulletList->back())->SetBulletData(m_tPlayerInfo.iBulletLevel, LT);

			m_bulletList->push_back(CAbstractFactory<CBullet>::CreateObj());
			m_bulletList->back()->Set_Pos(m_tObjInfo.fX + (gap + 8), m_tObjInfo.fY);
			static_cast<CBullet*>(m_bulletList->back())->SetBulletData(m_tPlayerInfo.iBulletLevel, RT);
			break;

		default:
			break;
		}

		if (m_GuidedTick + 1000 < GetTickCount())
		{
			m_bulletList->push_back(CAbstractFactory<CBullet>::CreateObj());
			m_bulletList->back()->Set_Pos(m_tObjInfo.fX, m_tObjInfo.fY);
			static_cast<CBullet*>(m_bulletList->back())->Set_Identity(true);	// �ʱ�ȭ�� true�̱� ������ ���̸� false��.
			// �� ����Ʈ �� �ִ� �Ÿ� Ȯ��.
			if (m_bossList->begin() != m_bossList->end())
				static_cast<CBullet*>(m_bulletList->back())->SetTarget(m_bossList->back());
			else
				static_cast<CBullet*>(m_bulletList->back())->SetTarget(static_cast<CBullet*>(m_bulletList->back())->CheckShortestDistance(*m_enemyList));
			static_cast<CBullet*>(m_bulletList->back())->SetFollowBullet();	// Ÿ�� �����ؼ� Ÿ�� ��ġ�� �߻�
			m_GuidedTick = GetTickCount();
		}


		m_BulletTick = GetTickCount();
	}
}

void		CPlayer::Use_Bomb()
{
	if (GetAsyncKeyState(VK_SPACE) && m_tPlayerInfo.eState == PLAYING && m_iBombCount > 0 && !m_bIsBomb)
	{
		if (WM_KEYDOWN)
		{
			--m_iBombCount;
			m_fEffectsize = 0.f;
			m_bIsBomb = true;
			m_tBombInfo.fX = m_tObjInfo.fX;
			m_tBombInfo.fY = m_tObjInfo.fY;
			m_BombTick = GetTickCount();
		}
	}


	if (m_bIsBomb)
	{
		if (m_BombTick + 2000 > GetTickCount()) 
		{
			//m_tPlayerInfo.bIsInvincible = true;
			if(m_tBombInfo.fCX*0.5 >= m_fEffectsize)
				m_fEffectsize += 3.0f;
		}
		else
		{
			//m_tPlayerInfo.bIsInvincible = false;
			m_bIsBomb = false;
		}
	}
}