//=============================================================================
//
// �`���[�g���A���̏��� [tutorial.h]
// Author : �ڍ�������
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "scene.h"
#include "scene.h"
#include "player.h"
#include "tube.h"
#include "meshField.h"
//=============================================================================
// �O���錾
//=============================================================================
class CPlayer;
class CTube;
class CPoint;
class CSetWord;
class CWall;
class CStageSelect;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_TUTORIAL			(3)
#define CAMERA_LENGTH_1P_PLAY (100.0f)				//�J�����̋���(1p�v���C�p)
#define CAMERA_LENGTH_2P_PLAY (120.0f)				//�J�����̋���(2p�v���C�p)
#define CAMERA_LENGTH_3P4P_PLAY (140.0f)			//�J�����̋���(3p4p�v���C�p)
#define CAMERA_LENGTH_TOPVIEW_PLAY (140.0f)			//�J�����̋���(3p�v���C���̃g�b�v�r���[�J�����p)

#define CAMERA_ROTX (-0.05f)		//�J�����̃f�t�H���g�p�x(X)

#define PLAYER_INITPOS (200.0f)
#define MAX_PLAYER (4)
#define MAX_STAGE	(3)			// �X�e�[�W�̍ő吔
#define MAX_STAGECOUNT	(3)		// �e�X�e�[�W�̐�

class CTutorial
{
public:
	CTutorial();
	~CTutorial();

	void Init(void);
	void Uninit(void);
	void Update(void);
	static CMeshField *GetMeshField(void) { return m_pMeshField; }			// �n�ʂ̎擾
	void Draw(void);
	void SetStage(int nNumState, int nCntState);	// �X�e�[�W�̐���
	void SetCreateWord(void);

private:
	void CameraSetting(int nNum);		// �l���ɉ������J��������
	void PlayerSetting(int nNum);		// �l���ɉ������v���C���[����
	void TubeSetting(int nNum);			// �l���ɉ��������̐���
	static CPlayer *m_pPlayer[MAX_PLAYER];
	static CTube *m_apTube[MAX_PLAYER];
	static CPlayer::PLAYER_TYPE m_type[MAX_PLAYER];
	static CMeshField *m_pMeshField;
	static CWall *m_pWall;
	static CSetWord *m_pWordCreate;
	char *m_pcStageName[MAX_STAGE][MAX_STAGECOUNT];		// �X�e�[�W�̖��O�ۊ�
	char *m_pcStageNameWord[MAX_STAGE][MAX_STAGECOUNT];	// �X�e�[�W�̖��O�ۊ�
	int m_nChangeNum;
	static int m_nNumStage;
};
#endif