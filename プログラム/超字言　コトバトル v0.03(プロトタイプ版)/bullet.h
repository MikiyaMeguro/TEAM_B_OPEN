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

//弾基本クラス
class CBulletBase : public CScene
{
public:
	CBulletBase() {};
	CBulletBase(int nPriority = 1);
	~CBulletBase();

	void Set(D3DXVECTOR3 pos,D3DXVECTOR3 rot);

	virtual HRESULT Init(void);
	virtual void	Uninit(void);
	virtual void	Update(void);
	virtual void	Draw(void);

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

//モデル弾クラス
class CModelBullet : public CBulletBase
{
public:
	CModelBullet();
	CModelBullet(int nPriority = 1);

	~CModelBullet();

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CSceneX* m_pModel;
};

//文字弾クラス
class CWordBullet : public CBulletBase
{
public:
	CWordBullet();
	CWordBullet(int nPriority = 1);
	~CWordBullet();

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nWordNum);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CSceneBillBoard* m_pWord;
};

#endif // !_BULLET_H_
