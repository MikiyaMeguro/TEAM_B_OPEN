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
//=============================================================================
// �}�N����`
//=============================================================================
#define BULLET_PRIORITY (1)
#define BULLET_COLLISION_SIZE (30.0f)

//=============================================================================
// �O���錾
//=============================================================================
class CSceneX;
class CSceneBillBoard;

//=============================================================================
// �N���X�̒�`
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

	BULLET_TYPE GetType(void) { return m_Type; };
protected:
	BULLET_TYPE m_Type;
private:
	D3DXVECTOR3 m_pos;				//�ʒu
	D3DXVECTOR3 m_rot;				//�p�x
	float m_fMove;				//�ړ���

	int m_nLife;	//�̗�
	int m_nID;	//�N���ł�����

};

//���f���e�N���X
class CModelBullet : public C3DBullet
{
public:
	CModelBullet();
	CModelBullet(int nPriority = BULLET_PRIORITY);

	~CModelBullet();
	static CModelBullet* Create(void);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CLoad::MODEL model, float fSpeed, int nLife,int nID);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CSceneX* m_pModel;
};

//�����e�N���X
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
