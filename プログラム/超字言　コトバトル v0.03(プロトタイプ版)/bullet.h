//=============================================================================
//
// 弾処理 [bullet.h]
// Author : Kodama Yuto
//
//	クラスの概要
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "scene.h"
class CSceneX;
class CSceneBillBoard;

class CBulletBase
{
public:
	CBulletBase();
	~CBulletBase();

	virtual void Set(D3DXVECTOR3 pos,D3DXVECTOR3 rot);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3& GetPosition(void) { return m_pos;};
	D3DXVECTOR3& GetRotation(void) { return m_rot;};
	D3DXVECTOR3& GetMove(void) { return m_Move; };

	void SetID(int nID) { m_nID = nID; };
private:
	D3DXVECTOR3 m_pos;				//位置
	D3DXVECTOR3 m_rot;				//角度
	D3DXVECTOR3 m_Move;				//移動量

	int m_nID;
};

class CModelBullet : public CBulletBase
{
public:
	CModelBullet();
	~CModelBullet();

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

};
class CWordBullet : public CBulletBase
{
public:
	CWordBullet();
	~CWordBullet();

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
};

#endif // !_BULLET_H_
