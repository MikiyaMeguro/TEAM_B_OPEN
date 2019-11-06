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

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_MODELNUM (20)
#define MOTION_BLENDTIME (8)
#define MAX_KEY (20)

//class CScene3D;
class CSceneX;
class CWordManager;

class CPlayer : public CScene
{
public:
	//�L�����N�^�[�^�C�v
	typedef enum
	{
		TYPE_BARANCE = 0,			//�m�[�}��
		TYPE_POWER,					//�p���[
		TYPE_SPEED,					//�X�s�[�h
		TYPE_REACH,					//���[�`
		TYPE_MAX
	}PLAYER_TYPE;

	//�̏��
	typedef enum
	{
		LOWER_BODY = 0,		//�����g
		UPPER_BODY,			//�㔼�g
		BODY_MAX,
	}BODY;

	//���[�V������(�㔼�g)
	typedef enum
	{
		MOTION_UPPER_NONE = 0,				//���[�V��������
		MOTION_UPPER_NEUTRAL,				//�ҋ@(�e����)
		MOTION_UPPER_WALK,					//���s(�e����)
		MOTION_UPPER_SETUP_NEUTRAL,			//�ҋ@(�e�L��)
		MOTION_UPPER_SETUP_WALK,			//���s(�e�L��)
		MOTION_UPPER_STEP,					//�X�e�b�v���
		MOTION_UPPER_SHOT,					//�e��ł�
		MOTION_UPPER_DAMAGE,				//�_���[�W���󂯂�
		MOTION_UPPER_WINNER,				//��ʂ̎�
		MOTION_UPPER_LOSER,					//�ŉ��ʂ̎�
		MOTION_UPPER_MAX
	}MOTION_UPPER;

	//���[�V������(�����g)
	typedef enum
	{
		MOTION_LOWER_NONE = 0,				//���[�V��������
		MOTION_LOWER_NEUTRAL,				//�ҋ@(�e����)
		MOTION_LOWER_WALK_FRONT,			//���ʈړ�
		MOTION_LOWER_WALK_RIGHT,			//�E�ړ�
		MOTION_LOWER_WALK_LEFT,				//���ړ�
		MOTION_LOWER_STEP,					//�X�e�b�v���
		MOTION_LOWER_SHOT,					//�e��ł�
		MOTION_LOWER_DAMAGE,				//�_���[�W���󂯂�
		MOTION_LOWER_WINNER,				//��ʂ̎�
		MOTION_LOWER_LOSER,					//�ŉ��ʂ̎�
		MOTION_LOWER_MAX
	}MOTION_LOWER;

	//���[�V�����J�ڎ��̏��
	typedef enum
	{
		STATE_NORMAL,		//���[�V������ʏ�J�ڂ�����
		STATE_BLEND,		//���[�V�����u�����h��������
	}MOTION_STATE;

	//�L�[�t���[�����Ƃ̏��
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

	//���[�V�������(
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

	//�L�����p�[�c�̏��i�[�\����
	typedef struct
	{
		int nIndex;				//�p�[�c�C���f�b�N�X
		int nParent;			//�p�[�c�̐e�ԍ�
		D3DXVECTOR3 pos;		//�ʒu
		D3DXVECTOR3 rot;		//�p�x
		char FileName[256];		//�t�@�C����
	}PartsLoadInfo;

	//�v���C���[�̏��i�[�\����
	typedef struct
	{
		PartsLoadInfo info[PLAYER_MODELNUM];		//�p�[�c���
		MotionProperty prop[10];					//���[�V�������
		int nPartsNum;								//�p�[�c��
		bool bLoad;									//���[�h���ꂽ��
	}PlayerLoadState;

	CPlayer(int nPriority = 3);
	~CPlayer();

	static CPlayer* Create(void);

	void Set(D3DXVECTOR3 pos,CCharaBase::CHARACTOR_MOVE_TYPE MoveType, int nPlayerID, PLAYER_TYPE PlayerType,D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,0.0f,0.0f));

	HRESULT ModelLoad(LPCSTR pFileName, PLAYER_TYPE type, BODY body,bool bReLoad = false);
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

	void			SetMotion(int motion, BODY body, MOTION_STATE state = STATE_BLEND);
	int			GetMotion(BODY body = BODY::LOWER_BODY) { return m_motion[body]; };
private:
	bool			CollisionBullet(void);
	void			DamageReaction(float fDamageValue,D3DXVECTOR3 HitRotation);	//fDamageValue = �_���[�W�� | HitRotation = �U�����󂯂�����
	bool			CollisonObject(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius);	// �����蔻��
	void			MotionUpdate(BODY body = BODY::LOWER_BODY);			//���[�V�����X�V
	int				GetNearPlayer(void);		//�߂��v���C���[���擾

	static PlayerLoadState m_PlayerLoadState[TYPE_MAX][BODY_MAX];	//�p�[�c���

	int m_nID;	//����ID(0�`3�̊�)
	PLAYER_TYPE m_PlayerType;
	LPCSTR m_ChildCameraName;		//���̃v���C���ɒǏ]����J�����̖��O
	C3DCharactor* m_pCharactorMove;							//�L�����N�^�[�̈ړ��Ǘ�
	CCharaParts* m_pPlayerParts[PLAYER_MODELNUM][BODY_MAX];	//�L�����N�^�[�̍\���p�[�c

	bool m_bLand;									// ���f���ɏ���Ă��邩�ǂ���
	D3DXVECTOR3 m_posOld;
	int m_nCntTransTime;							//���G����
	CSceneBillBoard *m_pPlayerNum;					// �v���C���[�ԍ��\���p�r���{�[�h
	CWordManager *m_pWordManager;					//�����Ǘ��N���X�̃|�C���^

	bool m_bSetupBullet;							//�e�����Ă��Ԃ̔���p

	C3DCharactor* m_pLockOnCharactor;				//���b�N�I�����Ă���L�����N�^�[�̏��

	/* Motion */
	MotionProperty m_propMotion[MOTION_UPPER_MAX][BODY_MAX];
	int m_motion[BODY_MAX];											//���݂̃��[�V����
	int m_OldMotion[BODY_MAX];										//��O�̃��[�V����
	int m_Mstate[BODY_MAX];									//���[�V�����̏��
	int m_nCntFlame[BODY_MAX];											//�t���[���p�J�E���^
	int m_nCntKey[BODY_MAX];											//�L�[�p�J�E���^
	int m_nCntBlendMotion[BODY_MAX];
};

#endif // !_PLAYER_H_
