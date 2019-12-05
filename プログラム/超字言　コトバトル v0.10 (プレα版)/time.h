//=============================================================================
//
// �������ԏ��� [time.h]
// Author : Shun Yokomichi
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
//�@�O���錾
//*****************************************************************************
class CNumber;
class CBillNumber;
class CSceneBillBoard;
class CPlayer;
class CScene2D;
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TIME_MAX			(3)		// �^�C�}�[�̌���
#define PLAYER_MAX			(4)		// �v���C���[�ő吔

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTime : public CScene
{
public:
	CTime(int nPriority = 6, OBJTYPE objType = OBJTYPE_TIME);
	~CTime();

	static CTime *Create(int nNumPlayer);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void TexTime(int nTexData, int nTimeOne);

	//============================
	// �ݒ�@�擾�@�̊֐�
	//============================
	static int GetTime(void) { return m_nTime; };
	static void AddTime(int nTime);

	static bool GetTimeFlag(void) { return m_bCountFlag; };
	static void SetTimeFlag(bool bFlag) { m_bCountFlag = bFlag; };

	static int GetStageTime(void) { return m_nStageChange; }	// �X�e�[�W�ؑ֎��̎��Ԏ擾
private:
	void DebugKey(void);
	void TimeManagement(void);
	int PowerCalculation(int nData, int nOperation);
	CBillNumber *m_apNumber[TIME_MAX];	// �i���o�[�ւ̃|�C���^
	static int				m_nTime;			// ����
	static int				m_nTimeCount;		// ���Ԃ̃J�E���^
	static int				m_nTimeOld;
	static int				m_nStageChange;		// �X�e�[�W���؂�ւ�鎞��
	static int				m_nTimeOne;
	int						m_nTimeNum;			// ���Ԃ̕\��������
	int						m_nWaitTime;		// �Q�[���I�����̑҂�����
	int						m_nNumPlayer;		// �l���ۊ�
	bool					m_bStart;
	bool					m_bStageCreate;		// �X�e�[�W�������̐���
	D3DXVECTOR3				m_pos;				// �ʒu
	CSceneBillBoard			*m_pColon;			// �R����

	static bool m_bCountFlag;			//���Ԃ��J�E���g���邩



	//�J�E���g�_�E���p
	float						m_fWidth, m_fHeight;			// �� ����
	CScene2D					*m_pScene2D[PLAYER_MAX];		// 2D�|���S���ւ̃|�C���^
	int							m_nColorFlash;					// �_�ŃJ�E���g
	D3DXCOLOR					m_Col;							// �F
	bool						m_bCntDown;						// �����ꂽ���ǂ������
	int							m_nType;						// ���݂̃^�C�v
	float						m_fScale;						// �g��k����
	int							m_ScaleCounter;					// �g��k���̃J�E���^�[
	bool						m_bEndCntDown;					// �J�E���g�_�E�����I���������ǂ���
	int							m_StageCounter;					// Stage���������܂ł̎���

	CPlayer						*m_pPlayer[PLAYER_MAX];
};
#endif
