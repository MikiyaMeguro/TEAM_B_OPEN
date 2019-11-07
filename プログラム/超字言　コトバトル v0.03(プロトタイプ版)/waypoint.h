//=============================================================================
//
// �o�H���̏��� [waypoint.h]
// Author :�@�ڍ� ������
//
//=============================================================================
#ifndef _WAYPOINT_H_
#define _WAYPOINT_H_

#include "sceneBillboard.h"
#include "game.h"

#define MAX_WAYPOINT	(SPLIT_WAYPOINT * SPLIT_WAYPOINT)	// �E�F�C�|�C���g�̍ő吔
#define SPLIT_WAYPOINT	(10)	// �E�F�C�|�C���g�̏c��������
#define WAYPOINT_HIT	(40)	// �E�F�C�|�C���g�͈̔�

//*********************************************************************
//�r���{�[�h�N���X�̒�`
//*********************************************************************
class CWaypoint : public CSceneBillBoard //�h���N���X
{
public:
	typedef struct
	{
		CSceneBillBoard *pWayPoint;
		D3DXVECTOR3 WayPointPos;
		int	nWayPointNum;
		bool bInPlayer;
	}WAYPOINT;

	CWaypoint();
	~CWaypoint();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CWaypoint *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, LPCSTR Tag);
	void InRange(D3DXVECTOR3 pos);
	D3DXVECTOR3 &ReturnPointMove(void);
	int CntWayPoint(void);

	// �֐�
private:
	D3DXVECTOR3 Move(D3DXVECTOR3 pos);
	void ScaleSize(void);

	WAYPOINT WayPoint[MAX_WAYPOINT];

	D3DXVECTOR3 m_size;		// �T�C�Y
	D3DXVECTOR3 m_sizeOld;	// �T�C�Y(�ߋ�)
	bool m_bFlagUninit;		// �I�����邽�߂̃t���O
	bool m_bMoveFlag;		// �㉺�ړ��̃t���O
	bool m_bScaleFlag;		// �g��k������t���O
	int m_nWaypointNum;		// �o�H���̔ԍ�

	D3DXVECTOR3 m_pWayPointPos[8];		// �|�C���^
	int nNumWayPoint;					// �s���\�Ȑ�

#ifdef _DEBUG
	int nNum2Cnt;
#endif

};

#endif