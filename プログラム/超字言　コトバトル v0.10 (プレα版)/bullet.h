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
#include "manager.h"

#include "charactor.h"
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
class CLineOrbit;
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
	float& GetKnockBackPower(void) { return m_fKnockBack; };
	BULLET_TYPE GetType(void) { return m_Type; };
	bool CollisionObject(CManager::DIRECTION* dir);
	bool SimpleCollision(void);// { CManager::DIRECTION dir; return C3DBullet::CollisionObject(&dir); }

	void Homing(D3DXVECTOR3 HomingPos);
protected:
	BULLET_TYPE m_Type;
	float m_fCollisionRadius;
	float m_fKnockBack;	//�m�b�N�o�b�N����l
	D3DXMATRIX m_mtxTrans;
private:
	D3DXVECTOR3 m_pos;				//�ʒu
	D3DXVECTOR3 m_posOld;			//�O��̈ʒu
	D3DXVECTOR3 m_rot;				//�p�x
	D3DXMATRIX m_mtxRotate;			//��]�}�g���b�N�X
	float m_fMove;					//�ړ���
	D3DXVECTOR3 m_MoveResult;		//�O��Ƃ̈ړ�����

	int m_nLife;	//�̗�
	int m_nID;	//�N���ł�����
};

//���f���e�N���X
class CModelBullet : public C3DBullet
{
public:
	typedef enum
	{
		TYPE_NORMAL = 0,		//�ʏ�(�m�b�N�o�b�N��)
		TYPE_KNOCKBACK,			//�m�b�N�o�b�N��
		TYPE_HIGHSPEED,			//���x����
		TYPE_STINGER,			//�I�u�W�F�N�g�ђ�
		TYPE_REFLECT,			//����
		TYPE_MISSILE,			//�~�T�C��
		TYPE_BOMB,				//�������e
	}BULLET_PROPERTY;

	CModelBullet();
	CModelBullet(int nPriority = BULLET_PRIORITY);

	~CModelBullet();
	static CModelBullet* Create(void);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CLoad::MODEL model, BULLET_PROPERTY type,int nID,
		D3DXVECTOR3 RotateOffset = D3DXVECTOR3(0.0f,0.0f,0.0f));

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetModelScale(const D3DXVECTOR3& scale);
	void SetModelRot(const D3DXVECTOR3& rot);

	void SetHomingChara(C3DCharactor* pChara) { m_pHomingChara = pChara; };

private:

	void Reflect(CManager::DIRECTION dir);
	CSceneX* m_pModel;
	BULLET_PROPERTY m_Prop;
	D3DXVECTOR3 m_modelRotateOffSet;

	C3DCharactor* m_pHomingChara;


	CLineOrbit* m_pOrbit;

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
