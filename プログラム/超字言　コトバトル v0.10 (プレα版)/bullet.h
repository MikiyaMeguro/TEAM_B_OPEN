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
#include "load.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define BULLET_PRIORITY (1)
#define BULLET_COLLISION_SIZE (30.0f)

//=============================================================================
// 前方宣言
//=============================================================================
class CSceneX;
class CSceneBillBoard;

//=============================================================================
// クラスの定義
//=============================================================================
class C3DBullet : public CScene
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		TYPE_WORD,
		TYPE_MODEL,
		TYPE_MAX
	}BULLET_TYPE;

	C3DBullet() {};
	C3DBullet(int nPriority = BULLET_PRIORITY);
	~C3DBullet();

	void Set(D3DXVECTOR3 pos,D3DXVECTOR3 rot,float fSpeed,int nLife, int nID);

	virtual HRESULT Init(void);
	virtual void	Uninit(void);
	virtual void	Update(void);
	virtual void	Draw(void);

	D3DXVECTOR3& GetPosition(void) { return m_pos;};
	D3DXVECTOR3& GetRotation(void) { return m_rot;};
	float& GetMove(void) { return m_fMove; };
	int& GetLife(void) { return m_nLife; };
	int GetID(void) { return m_nID; };
	float& GetKnockBackPower(void) { return m_fKnockBack; };
	BULLET_TYPE GetType(void) { return m_Type; };
protected:
	BULLET_TYPE m_Type;
	float m_fKnockBack;	//ノックバックする値
private:
	D3DXVECTOR3 m_pos;				//位置
	D3DXVECTOR3 m_rot;				//角度
	float m_fMove;				//移動量

	int m_nLife;	//体力
	int m_nID;	//誰が打ったか

};

//モデル弾クラス
class CModelBullet : public C3DBullet
{
public:
	typedef enum
	{
		TYPE_NORMAL = 0,		//通常(ノックバック小)
		TYPE_KNOCKBACK,			//ノックバック大
		TYPE_HIGHSPEED,			//速度早い
		TYPE_STINGER,			//オブジェクト貫通
		TYPE_REFLECT,			//反射
	}BULLET_PROPERTY;

	CModelBullet();
	CModelBullet(int nPriority = BULLET_PRIORITY);

	~CModelBullet();
	static CModelBullet* Create(void);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CLoad::MODEL model, BULLET_PROPERTY type,int nID,D3DXVECTOR3 RotateOffset = D3DXVECTOR3(0.0f,0.0f,0.0f));

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetModelScale(const D3DXVECTOR3& scale);
	void SetModelRot(const D3DXVECTOR3& rot);

private:
	void Reflect(void);
	CSceneX* m_pModel;
	BULLET_PROPERTY m_Prop;
	D3DXVECTOR3 m_modelRotateOffSet;
};

//文字弾クラス
class CWordBullet : public C3DBullet
{
public:
	CWordBullet();
	CWordBullet(int nPriority = BULLET_PRIORITY);
	~CWordBullet();

	static CWordBullet* Create(void);
	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fSpeed, int nLife,int nWordNum, int nID);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CSceneBillBoard* m_pWord;
};

#endif // !_BULLET_H_
