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
#include "sceneBillboard.h"
#include "CharaParts.h"


#define PLAYER_MODELNUM (20)

//class CScene3D;
class CSceneX;
class CWordManager;

class CPlayer : public CScene
{
public:
	typedef enum
	{
		TYPE_NORMAL = 0,			//�m�[�}��
		TYPE_POWER,					//�p���[
		TYPE_SPEED,					//�X�s�[�h
		TYPE_REACH,					//���[�`
	}PLAYER_TYPE;	//�v���C���[�̑���^�C�v

	typedef enum
	{
		MOTION_NEUTRAL = 0,		//�ҋ@(�e����)
		MOTION_WALK,			//���s(�e����)
		MOTION_SETUP_NEUTRAL,	//�ҋ@(�e�L��)
		MOTION_SETUP_WALK,		//���s(�e�L��)
		MOTION_STEP,			//�X�e�b�v���
		MOTION_SHOT,			//�e��ł�
		MOTION_DAMAGE,			//�_���[�W���󂯂�
		MOTION_WINNER,			//��ʂ̎�
		MOTION_LOSER,			//�ŉ��ʂ̎�
		MOTION_MAX
	}MOTION;
	typedef enum
	{
		STATE_NORMAL,		//���[�V�����Đ����
		STATE_BLEND,		//���[�V�����u�����h���
	}MOTION_STATE;

	typedef struct
	{
		int nFrame;							//�t���[����
		D3DXVECTOR3 Pos[PLAYER_MODELNUM];	//�ʒu
		D3DXVECTOR3 Rot[PLAYER_MODELNUM];	//����
	}KeyProperty;

	typedef struct
	{
		LPCSTR MotionName;							//���[�V������
		int	  nLoop;								//���[�v���邩�ǂ��� : -1 �������[�v | 0 ���[�v�Ȃ�
		int   nKeyNum;								//�L�[��
		std::vector<KeyProperty> vecKey;			//�L�[���
	}MotionProperty;

	typedef struct
	{
		int nIndex;
		int nParent;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		char FileName[256];
	}PartsLoadInfo;

	CPlayer(int nPriority = 3);
	~CPlayer();

	static CPlayer* Create(void);

	void Set(D3DXVECTOR3 pos,CCharaBase::CHARACTOR_MOVE_TYPE type, int nPlayerID,D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,0.0f,0.0f));

	HRESULT ModelLoad(LPCSTR pFileName);
	void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);


	CCharaBase* GetCharaMover(void) { return m_pCharactorMove; };

	D3DXVECTOR3 GetPosition(void) { return GetCharaMover()->GetPosition(); };
	D3DXVECTOR3 GetRotation(void) { return GetCharaMover()->GetRotation(); };
	int GetID(void) { return m_nID; };
	LPCSTR GetCameraName(void) { return m_ChildCameraName; };
	void SetCameraName(LPCSTR name) { m_ChildCameraName = name; };

	void SetTransTime(int nTime) { m_nCntTransTime = nTime; };
	CWordManager *GetWordManager(void) { return m_pWordManager; }				// ���t�Ǘ��N���X�̎擾


	void SetbSetupBullet(bool bBullet) { m_bSetupBullet = bBullet; };
	bool GetbSetupBullet(void) { return m_bSetupBullet; };	//�e�����Ă��Ԃ̔���p
private:
	bool CollisionBullet(void);
	void DamageReaction(float fDamageValue,D3DXVECTOR3 HitRotation);	//fDamageValue = �_���[�W�� | HitRotation = �U�����󂯂�����
	bool CollisonObject(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius);	// �����蔻��


	C3DCharactor* m_pCharactorMove;			//�L�����N�^�[�̈ړ��Ǘ�
	int m_nID;	//����ID(0�`3�̊�)
	PLAYER_TYPE m_PlayerType;
	LPCSTR m_ChildCameraName;		//���̃v���C���ɒǏ]����J�����̖��O
	bool m_bLand;					// ���f���ɏ���Ă��邩�ǂ���
	D3DXVECTOR3 m_posOld;
	int m_nCntTransTime;			//���G����

	CSceneX* m_pPlayerModel;							//�v���C���[�̃��f��(���A��Ł��̕ϐ��ɍ����ւ���)

	CCharaParts* m_pPlayerParts[PLAYER_MODELNUM];	//�L�����N�^�[�̍\���p�[�c
	CWordManager *m_pWordManager;
	CSceneBillBoard *m_pPlayerNum;					// �v���C���[�ԍ�

	bool m_bSetupBullet;					//�e�����Ă��Ԃ̔���p
};
#endif // !_PLAYER_H_
