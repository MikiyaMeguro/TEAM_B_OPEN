//=============================================================================
//
// 爆発クラス [explosion.h]
// Author : Kodama Yuto
//
//	クラスの概要:
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "meshSphere.h"

class CExplosion3D : public CMeshSphere
{
public:
	CExplosion3D();
	CExplosion3D(int pri = 1, OBJTYPE type = OBJTYPE_SCENE3D);
	~CExplosion3D();

	static CExplosion3D* Create(void);

	void Set(D3DXVECTOR3 pos,float fStartSize,float fDestSize,int nLife,float fAnimSpeed = 0.01f);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	bool Collision(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld);
private:
	float m_fSize;
	float m_fDestSize;
	int m_nLife;
};

#endif // !_EXPLOSION_H_
