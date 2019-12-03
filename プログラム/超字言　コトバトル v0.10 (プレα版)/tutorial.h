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
#define CAMERA_LENGTH_1P_PLAY (250.0f)				//�J�����̋���(1p�v���C�p)
#define CAMERA_LENGTH_2P_PLAY (250.0f)				//�J�����̋���(2p�v���C�p)
#define CAMERA_LENGTH_3P4P_PLAY (200.0f)			//�J�����̋���(3p4p�v���C�p)
#define CAMERA_LENGTH_TOPVIEW_PLAY (650.0f)			//�J�����̋���(3p�v���C���̃g�b�v�r���[�J�����p)

#define CAMERA_ROTX (-1.57f)		//�J�����̃f�t�H���g�p�x(X)

#define PLAYER_INITPOSX (200.0f)
#define PLAYER_INITPOSZ (200.0f)

#define MAX_PLAYER (4)
#define MAX_STAGE	(2)			// �X�e�[�W�̍ő吔
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
	static CPlayer *GetPlayer(int nNumPlayer = 0) { return (nNumPlayer < MAX_PLAYER && nNumPlayer >= 0) ? m_pPlayer[nNumPlayer] : m_pPlayer[0]; }		// �v���C���[�̎擾
	static CTube *GetTube(int nNum);		// �����̉���UI�̎擾
	static CSetWord *GetWordCreate(void) { return m_pWordCreate; }			// �����o���̎擾
	static CPoint *GetPoint(int nNum) { return m_pPoint[nNum]; }			// �|�C���g�̎擾
private:
	void CameraSetting(int nNum);		// �l���ɉ������J��������
	void PlayerSetting(int nNum);		// �l���ɉ������v���C���[����
	void TubeSetting(int nNum);			// �l���ɉ��������̐���
	void SetPointFrame(int nNum);		// �l���ɉ������|�C���g�̐���
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
	static CPoint *m_pPoint[MAX_PLAYER];
};
#endif