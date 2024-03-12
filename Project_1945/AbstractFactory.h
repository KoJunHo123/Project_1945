#pragma once


template<typename T>
class CAbstractFactory
{
public:
	static CObj* CreateObj()
	{
		CObj* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	// ����� �߰�
	static CObj* CreateObj(float _fX, float _fY)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_fX, _fY);
		return pObj;
	}

public:
	CAbstractFactory() {}
	~CAbstractFactory() {}
};