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
	CPlayer(int nPriority = 3);
	~CPlayer();

	static CPlayer* Create(void);

	void Set(D3DXVECTOR3 pos,CCharaBase::CHARACTOR_MOVE_TYPE type, D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,0.0f,0.0f));
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void DamageReaction(float fDamageValue) {};

	CCharaBase* GetCharaMover(void) { return m_pCharactorMove; };

	D3DXVECTOR3 GetPosition(void) { return GetCharaMover()->GetPosition(); };
	D3DXVECTOR3 GetRotation(void) { return GetCharaMover()->GetRotation(); };

	LPCSTR GetCameraName(void) { return m_ChildCameraName; };
	void SetCameraName(LPCSTR name) { m_ChildCameraName = name; };
private:
	C3DCharactor* m_pCharactorMove;			//�L�����N�^�[�̈ړ��Ǘ�

	CSceneX* m_pPlayerModel;				//�v���C���[�̃��f��(���A��Ł��̕ϐ��ɍ����ւ���)
	//std::vector<CCharaParts*> m_pVecPlayerParts;	//�L�����N�^�[�̍\���p�[�c

	LPCSTR m_ChildCameraName;		//���̃v���C���ɒǏ]����J�����̖��O
};
#endif // !_PLAYER_H_
