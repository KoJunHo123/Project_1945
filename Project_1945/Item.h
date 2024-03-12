#pragma once

#include "Obj.h"

class CItem abstract
	: public CObj
{
public:
	CItem();
	virtual ~CItem()		override;

public:
	void Initialize()		override;
	int	 Update()			override;
	void Late_Update()		override;
	void Render(HDC hDC)	override;
	void Release()			override;
	virtual void Apply_Ability() PURE;

public:
	inline void Set_Player(CObj* _pPlayer) { m_pPlayer = _pPlayer; }
	inline void Set_Enemy(CObj* _pEnemy) { m_pEnemy = _pEnemy; }
	
protected:
	CObj* m_pEnemy;				// ��� ��� �� �� �����ѵ�..
	CObj* m_pPlayer;
	bool  m_bExpired;			// ������ ������ �������� ����
	DWORD m_dwCreatedTickCount; // ������ ���� �ñ�

private:
	static const int MAX_TICK_COUNT = 10000; // ������ ����
};

