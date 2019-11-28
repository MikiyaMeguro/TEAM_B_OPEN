//=============================================================================
//
// �������ԏ��� [time.h]
// Author : Shun Yokomichi
//
//=============================================================================
#ifndef _POINT_H_
#define _POINT_H_

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
#define MAX_POINT_NUM			(2)		// �^�C�}�[�̌���

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPoint : public CScene
{
public:
	typedef enum
	{
		TYPE_NONE = 0,	// �����Ȃ�
		TYPR_PLAYER,	// �v���C���[
		TYPE_CPU,		// �G
		TYPE_MAX
	}TYPE_CHARACTER;

	CPoint(int nPriority = 6, OBJTYPE objType = OBJTYPE_POINT);
	~CPoint();

	static CPoint *Create(int nID, int nNumPlayer, TYPE_CHARACTER type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void TexPoint(int nTexData);

	//============================
	// �ݒ�@�擾�@�̊֐�
	//============================
	int GetPoint(void) { return m_nTotalPoint; };

	//============================
	// ���Z�@���Z�@�̊֐�
	//============================
	void AddPoint(int nPoint);				// ���Z����
	void SubtractionPoint(int nPoint);		// ���Z����


private:
	void DebugKey(void);
	void TimeManagement(void);
	int PowerCalculation(int nData);
	void PointBGCreate(void);			// �|�C���g�̔w�i����
	void BGPosition(CScene2D *pBg);		// �w�i�̈ʒu�܂Ƃ�
	void UIPosition(void);				// UI�̈ʒu�܂Ƃ�
	void PointPostion(int nNumPlayer, int nID);			// �|�C���g�̈ʒu�܂Ƃ�
	void SizeChange(void);				// �������̃T�C�Y�ύX

	CNumber *m_apNumber[MAX_POINT_NUM];	// �i���o�[�ւ̃|�C���^
	int m_nTotalPoint;							// �g�[�^���̃|�C���g
	int						m_nPointNum;		// �|�C���g�̕\��������
	int						m_nNumPlayer;		// �l���ۊ�
	int						m_nID;				// �����̔ԍ�
	bool					m_bStart;
	bool					m_bSizeChange;		// �|�C���g�������̃T�C�Y�ύX
	D3DXVECTOR3				m_pos;				// �ʒu
	CScene2D				*m_pIcon;			// �v���C���[�A�C�R��
	TYPE_CHARACTER			m_type;				// ���
	D3DXCOLOR				m_ChangeCol;		// �|�C���g�������̐F
};
#endif
