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
class CScene2D;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TIME_MAX			(3)		// �^�C�}�[�̌���

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
	void TexTime(int nTexData);

	//============================
	// �ݒ�@�擾�@�̊֐�
	//============================
	static int GetTime(void) { return m_nTime; };
	static void AddTime(int nTime);

private:
	void DebugKey(void);
	void TimeManagement(void);
	int PowerCalculation(int nData, int nOperation);
	CNumber *m_apNumber[TIME_MAX];	// �i���o�[�ւ̃|�C���^
	static int				m_nTime;			// ����
	static int				m_nTimeNumCount;	// ���Ԃ̕\����
	static int				m_nTimeCount;		// ���Ԃ̃J�E���^
	int						m_nTimeNum;			// ���Ԃ̕\��������
	int						m_nWaitTime;		// �Q�[���I�����̑҂�����
	int						m_nNumPlayer;		// �l���ۊ�
	bool					m_bStart;
	D3DXVECTOR3				m_pos;				// �ʒu
	CScene2D				*m_pColon;			// �R����
};
#endif
