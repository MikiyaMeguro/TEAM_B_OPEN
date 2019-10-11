//=============================================================================
//
// �L�����N�^�[���� [charactor.h]
// Author : Kodama Yuto
//
//	�N���X�̊T�v
//	�EPosition��Rotation�ȂǁA�p������Ɏg���ϐ����������N���X�Q
//	�E�N���X���Ŏp��������s���AGet�֐��ł������擾����
//
//	C2DCharactor
//	�E2D�̃L�����N�^�[�p�̃N���X
//	�E�}�g���b�N�X���������APosition��Rotation�Ő��䂷��
//
//	C3DCharactor
//	�E3D�̃L�����N�^�[�p�̃N���X
//	�EPosition��Rotation�ɉ�����,�}�g���b�N�X���g���Ďp��������s��
//
//=============================================================================
#ifndef _CHARACTOR_H_
#define _CHARACTOR_H_

#include "scene.h"
class CPlayer;

class CCharaBase
{
public:
	typedef enum
	{
		MOVETYPE_PLAYER_INPUT,		//�v���C���[�̑���
		MOVETYPE_NPC_AI,			//NPC��AI�̑���
		MOVETYPE_MAX
	}CHARACTOR_MOVE_TYPE;

	CCharaBase() {};
	~CCharaBase() {};

	virtual void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CHARACTOR_MOVE_TYPE type, CPlayer* pThis);

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;

	D3DXVECTOR3& GetPosition(void) { return m_pos; };
	D3DXVECTOR3& GetRotation(void) { return m_rot; };
	D3DXVECTOR3& GetMove(void) { return m_Move; };
	D3DXVECTOR3& GetSpin(void) { return m_Spin; };
	float&		 GetSpeed(void) { return m_fSpeed; };

	CHARACTOR_MOVE_TYPE GetMoveType(void) { return m_type; };

	void SetThisCharactor(CPlayer* pThis) { m_pThisCharactor = pThis; };

protected:
	CPlayer* GetThisCharactor(void) { return m_pThisCharactor; };
	int m_nCntStepCoolTime;		//�X�e�b�v�ړ��̃N�[���_�E�����ԑ���p
private:
	D3DXVECTOR3 m_pos;				//�ʒu
	D3DXVECTOR3 m_rot;				//�p�x
	D3DXVECTOR3 m_Move;				//�ړ���
	D3DXVECTOR3 m_Spin;				//��]��
	float m_fSpeed;					//�ړ����x

	CHARACTOR_MOVE_TYPE m_type;		//�ړ��^�C�v

	CPlayer* m_pThisCharactor;		//���̃C���X�^���X���������Ă���v���C���[

};

class C2DCharactor : public CCharaBase
{
public:
	C2DCharactor() {};
	~C2DCharactor() {};

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CHARACTOR_MOVE_TYPE type, CPlayer* pThis) { CCharaBase::Set(pos, rot, type, pThis); };

	HRESULT Init(void);
	void Uninit(void) {};
	void Update(void);
private:
};

class C3DCharactor : public CCharaBase
{
public:
	C3DCharactor() {};
	~C3DCharactor() {};

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CHARACTOR_MOVE_TYPE type, CPlayer* pThis) { CCharaBase::Set(pos, rot, type, pThis); };

	HRESULT Init(void);
	void Uninit(void) {};
	void Update(void);

	D3DXVECTOR3 GetCameraPosR(void) { return m_CameraPosR; };
	D3DXMATRIX* GetMatrix(void) { return &m_mtxWorld; };
private:
	void CharaMove_Input(void);

	D3DXVECTOR3 m_CameraPosR;
	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���b�N�X
};

#endif // !_CHARACTOR_H_
