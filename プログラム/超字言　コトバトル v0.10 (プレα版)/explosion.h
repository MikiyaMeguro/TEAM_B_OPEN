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

//=============================================================================
// マクロ定義
//=============================================================================
#define TUBE_EFFECT_NUM (3)	//筒エフェクトの数

//=============================================================================
// クラスの定義
//=============================================================================
class CExplosion3D : public CMeshSphere
{
public:
	CExplosion3D();
	CExplosion3D(int pri = 1, OBJTYPE type = OBJTYPE_SCENE3D);
	~CExplosion3D();

	static CExplosion3D* Create(void);

	void Set(D3DXVECTOR3 pos,float fStartSize,float fDestSize,int nLife,float fAnimSpeed = 0.01f,
		D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXCOLOR col = D3DXCOLOR(0.90f, 0.55f, 0.1f, 0.5f),
		D3DXVECTOR3 scaleMag = D3DXVECTOR3(1.0f,1.0f,1.0f),LPCSTR Tag = "EXPLOSION",int nMesh = 40);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);



	bool Collision(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld);

private:
	void IsNotDup(bool bDup) { m_bNotDup = bDup; };
	float m_fSize;
	float m_fDestSize;
	int m_nLife;

	bool m_bNotDup;		//重ねて表示するか
	D3DXVECTOR3 m_ScaleMag;

};

#endif // !_EXPLOSION_H_
