//=============================================================================
//
// �e���� [bullet.h]
// Author : Kodama Yuto
//
//	�N���X�̊T�v
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "scene.h"
#include "load.h"
class CSceneX;
class CSceneBillBoard;

//�e��{�N���X
class CBulletBase : public CScene
{
public:
	CBulletBase() {};
	CBulletBase(int nPriority = 1);
	~CBulletBase();


	void Set(D3DXVECTOR3 pos,D3DXVECTOR3 rot,float fSpeed,int nLife);

	virtual HRESULT Init(void);
	virtual void	Uninit(void);
	virtual void	Update(void);
	virtual void	Draw(void);

	D3DXVECTOR3& GetPosition(void) { return m_pos;};
	D3DXVECTOR3& GetRotation(void) { return m_rot;};
	float& GetMove(void) { return m_fMove; };
	int& GetLife(void) { return m_nLife; };
private:
	D3DXVECTOR3 m_pos;				//�ʒu
	D3DXVECTOR3 m_rot;				//�p�x
	float m_fMove;				//�ړ���

	int m_nLife;	//�̗�
};

//���f���e�N���X
class CModelBullet : public CBulletBase
{
public:
	CModelBullet();
	CModelBullet(int nPriority = 1);

	~CModelBullet();
	static CModelBullet* Create(void);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CLoad::MODEL model, float fSpeed, int nLife);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CSceneX* m_pModel;
};

//�����e�N���X
class CWordBullet : public CBulletBase
{
public:
	CWordBullet();
	CWordBullet(int nPriority = 1);
	~CWordBullet();

	static CWordBullet* Create(void);
	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fSpeed, int nLife,int nWordNum);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CSceneBillBoard* m_pWord;
};

#endif // !_BULLET_H_
