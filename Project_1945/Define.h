#pragma once

#define WINCX 500
#define WINCY 600

#define PURE = 0

#define			OBJ_NOEVENT		0
#define			OBJ_DEAD		1

extern HWND g_hWnd;

enum OBJID { OBJ_PLAYER, OBJ_ENEMY, OBJ_MOUSE, OBJ_SHIELD, OBJ_ITEM, OBJ_BULLET, OBJ_BOSS, OBJ_END };

enum ITEMTYPE
{
	ITEM_POWER = 0,
	ITEM_LIFE,
	ITEM_INVINCIBLE,
	ITEM_BOMB,
	ITEM_END
};

enum PLAYERSTATE
{
	APPEAR,
	PLAYING,
	DESTROY,
	DEAD,
	PLAYERSTATE_END
};

typedef struct tagObj
{
	float	fX;
	float	fY;

	float	fCX;
	float	fCY;
}OBJINFO;

typedef struct tagPlayerInfo
{
	int iHp;			//ü��
	int	iBulletLevel;	//�߻��� �Ѿ� ����
	bool bIsInvincible;	//���� ����

	PLAYERSTATE eState;	//�÷��̾� ����

}PLAYERINFO;


#pragma region �Ѿ� �߰�
// �Ѿ� ������ ����
enum DIRECTION
{
	TOP,
	LT,
	RT,
	FOLLOW,
	ENEMYFOLLOW,
	BOTTOM,
	BOSS,
	DIRECTION_END
};

#pragma endregion

template <typename T>
void Safe_Delete(T& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}

template <typename T>
void Safe_Delete_Array(T& p)
{
	if (p)
	{
		delete[] p;
		p = nullptr;
	}
}