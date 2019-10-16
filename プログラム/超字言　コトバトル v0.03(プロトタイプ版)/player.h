//=============================================================================
//
// �v���C���[���� [player.h]
// Author : Kodama Yuto
//
//	�N���X�̊T�v
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "charactor.h"
#include "scene.h"

//class CScene3D;
class CSceneX;

class CPlayer : public CScene
{
public:
	typedef enum
	{
		TYPE_NORMAL = 0,
		TYPE_POWER,
		TYPE_SPEED,
		TYPE_REACH,
	}PLAYER_TYPE;
	CPlayer(int nPriority = 3);
	~CPlayer();

	static CPlayer* Create(void);

	void Set(D3DXVECTOR3 pos,CCharaBase::CHARACTOR_MOVE_TYPE type, int nPlayerID,D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,0.0f,0.0f));
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void DamageReaction(float fDamageValue) {};

	CCharaBase* GetCharaMover(void) { return m_pCharactorMove; };

	D3DXVECTOR3 GetPosition(void) { return GetCharaMover()->GetPosition(); };
	D3DXVECTOR3 GetRotation(void) { return GetCharaMover()->GetRotation(); };
	int GetID(void) { return m_nID; };
	LPCSTR GetCameraName(void) { return m_ChildCameraName; };
	void SetCameraName(LPCSTR name) { m_ChildCameraName = name; };

	bool CollisonObject(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius);	// �����蔻��

private:
	C3DCharactor* m_pCharactorMove;			//�L�����N�^�[�̈ړ��Ǘ�
	int m_nID;	//����ID(0�`3�̊�)
	CSceneX* m_pPlayerModel;				//�v���C���[�̃��f��(���A��Ł��̕ϐ��ɍ����ւ���)
	//std::vector<CCharaParts*> m_pVecPlayerParts;	//�L�����N�^�[�̍\���p�[�c
	PLAYER_TYPE m_PlayerType;
	LPCSTR m_ChildCameraName;		//���̃v���C���ɒǏ]����J�����̖��O
	bool m_bLand;		// ���f���ɏ���Ă��邩�ǂ���
	D3DXVECTOR3 m_posOld;
};
#endif // !_PLAYER_H_
