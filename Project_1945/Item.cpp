#include "pch.h"
#include "Item.h"

CItem::CItem()
	: m_pEnemy(nullptr)
	, m_pPlayer(nullptr)
	, m_bExpired(false)
	, m_dwCreatedTickCount(GetTickCount())
{
}

CItem::~CItem()
{
	Release();
}

void CItem::Initialize()
{
	m_fXSpeed = -3.f; // ó�� ���� �� ���� �밢������ �̵�
	m_fYSpeed = -3.f; // ó�� ���� �� ���� �밢������ �̵�

	Set_Pos(100, 100); // Initialize() ����, �ܺ�(Enemy)���� �ڽ��� ��ǥ ������ ȣ������� ��
	Set_Size(10, 30);  // ��� �������̴� ���Ⱑ �³�..?

	m_eObjId = OBJ_ITEM;
}

int CItem::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}
	
	DWORD dwElapsedTickCount = GetTickCount() - m_dwCreatedTickCount;

	if (dwElapsedTickCount > MAX_TICK_COUNT)
	{
		m_bExpired = true;
	}

	m_tObjInfo.fX += m_fXSpeed;
	m_tObjInfo.fY += m_fYSpeed;

	// ����ٰ� �����ð��� ��� �밢�� �̵� �ӵ����� �����ؾ� �� ��..?

	__super::Update_Pos();

	return OBJ_NOEVENT;
}

void CItem::Late_Update()
{
	bool bCollision = false;
	                                  
	if (m_tRect.left <= 0
		|| m_tRect.right >= WINCX)
	{
		m_fXSpeed *= -1.f;
		bCollision = true;
	}
	
	if (m_tRect.top <= 0
		|| m_tRect.bottom >= WINCY)
	{
		m_fYSpeed *= -1.f;
		bCollision = true;
	}
	
	if (m_bExpired && bCollision) // ��� Tick�� MAX_TICK_COUNT �̻� && ������ �� �浹 �� �Ҹ�
	{
		m_bDead = true;
	}
}

void CItem::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CItem::Release()
{
}
