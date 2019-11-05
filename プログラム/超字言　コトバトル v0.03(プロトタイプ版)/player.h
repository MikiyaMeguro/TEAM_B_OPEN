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
#define MOTION_BLENDTIME (8)
#define MAX_KEY (20)
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
		TYPE_MAX
	}PLAYER_TYPE;	//�v���C���[�̑���^�C�v

	typedef enum
	{
		MOTION_NONE = 0,		//���[�V��������
		MOTION_NEUTRAL,			//�ҋ@(�e����)
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

	typedef enum
	{
		LOWER_BODY = 0,		//�����g
		UPPER_BODY,			//�㔼�g
	}BODY;

	typedef struct
	{
		int nFrame;							//�t���[����
		D3DXVECTOR3 Pos[PLAYER_MODELNUM];	//�ʒu
		D3DXVECTOR3 Rot[PLAYER_MODELNUM];	//����
		void operator()(void)
		{
			nFrame = 0;
			for (int nCntPlayer = 0; nCntPlayer < PLAYER_MODELNUM; nCntPlayer++)
			{
				Pos[nCntPlayer] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				Rot[nCntPlayer] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
	}KeyProperty;

	typedef struct
	{
		int	  nLoop;								//���[�v���邩�ǂ���	:1�Ȃ烋�[�v
		int   nKeyNum;								//�L�[��
		KeyProperty key[MAX_KEY];					//�L�[���

		//�������p
		void operator()(void)
		{
			nLoop = 0;
			nKeyNum = 0;
			for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
			{
				key[nCntKey].nFrame = 0;
				for (int nCntPlayer = 0; nCntPlayer < PLAYER_MODELNUM; nCntPlayer++)
				{
					key[nCntKey].Pos[nCntPlayer] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					key[nCntKey].Rot[nCntPlayer] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}
		}
	}MotionProperty;

	typedef struct
	{
		int nIndex;
		int nParent;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		char FileName[256];
	}PartsLoadInfo;

	typedef struct
	{
		PartsLoadInfo info[PLAYER_MODELNUM];
		MotionProperty prop[MOTION_MAX];
		int nPartsNum;
		bool bFlag;
	}PlayerLoadState;
	CPlayer(int nPriority = 3);
	~CPlayer();

	static CPlayer* Create(void);

	void Set(D3DXVECTOR3 pos,CCharaBase::CHARACTOR_MOVE_TYPE MoveType, int nPlayerID, PLAYER_TYPE PlayerType,D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,0.0f,0.0f));

	HRESULT ModelLoad(LPCSTR pFileName, PLAYER_TYPE type,bool bReLoad = false);
	void Unload(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CCharaBase*		GetCharaMover(void)				{ return m_pCharactorMove; };
	D3DXVECTOR3		GetPosition(void)				{ return GetCharaMover()->GetPosition(); };
	D3DXVECTOR3		GetRotation(void)				{ return GetCharaMover()->GetRotation(); };
	int				GetID(void)						{ return m_nID; };
	LPCSTR			GetCameraName(void)				{ return m_ChildCameraName; };
	void			SetCameraName(LPCSTR name)		{ m_ChildCameraName = name; };
	void			SetTransTime(int nTime)			{ m_nCntTransTime = nTime; };
	CWordManager*   GetWordManager(void)			{ return m_pWordManager; }				// ���t�Ǘ��N���X�̎擾
	void			SetbSetupBullet(bool bBullet)	{ m_bSetupBullet = bBullet; };
	bool			GetbSetupBullet(void)			{ return m_bSetupBullet; };	//�e�����Ă��Ԃ̔���p

	void			SetMotion(MOTION motion, BODY body = BODY::LOWER_BODY, MOTION_STATE state = STATE_BLEND);
	MOTION			GetMotion(void) { return m_motion; };
private:
	bool			CollisionBullet(void);
	void			DamageReaction(float fDamageValue,D3DXVECTOR3 HitRotation);	//fDamageValue = �_���[�W�� | HitRotation = �U�����󂯂�����
	bool			CollisonObject(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius);	// �����蔻��
	void			MotionUpdate(BODY body = BODY::LOWER_BODY);			//���[�V�����X�V
	int				GetNearPlayer(void);		//�߂��v���C���[���擾

	static PlayerLoadState m_PlayerLoadState[TYPE_MAX];	//�p�[�c���

	int m_nID;	//����ID(0�`3�̊�)
	PLAYER_TYPE m_PlayerType;
	LPCSTR m_ChildCameraName;		//���̃v���C���ɒǏ]����J�����̖��O
	C3DCharactor* m_pCharactorMove;			//�L�����N�^�[�̈ړ��Ǘ�
	CCharaParts* m_pPlayerParts[PLAYER_MODELNUM];	//�L�����N�^�[�̍\���p�[�c

	bool m_bLand;					// ���f���ɏ���Ă��邩�ǂ���
	D3DXVECTOR3 m_posOld;
	int m_nCntTransTime;			//���G����
	CSceneBillBoard *m_pPlayerNum;					// �v���C���[�ԍ�
	CWordManager *m_pWordManager;

	bool m_bSetupBullet;					//�e�����Ă��Ԃ̔���p

	C3DCharactor* m_pLockOnCharactor;

	/* Motion */
	MotionProperty m_propMotion[MOTION_MAX];
	MOTION m_motion;								//���݂̃��[�V����
	MOTION m_OldMotion;								//��O�̃��[�V����
	MOTION_STATE m_Mstate;							//���[�V�����̏��
	int m_nCntFlame;								//�t���[���p�J�E���^
	int m_nCntKey;									//�L�[�p�J�E���^
	int m_nCntBlendMotion;
};
#endif // !_PLAYER_H_
