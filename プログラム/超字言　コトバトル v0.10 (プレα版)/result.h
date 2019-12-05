//=============================================================================
//
// ���U���g���� [result.h]
// Author : �ڍ�������/��Ո�
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "scene.h"
#include "player.h"
#include "meshField.h"
#include "SelectMenu.h"
//=============================================================================
// �O���錾
//=============================================================================
class CPlayer;
class CNumber;
class CScene2D;
class CCharaBase;

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_PLAYER (4)
#define MAX_POINT (2)

//========================================
// �N���X�̒�`
//========================================
class CResult : public CScene
{
public:

	typedef struct
	{
		int nNumRank;
		int nPoint;
		CPlayer::PLAYER_TYPE type;
		CCharaBase::CHARACTOR_MOVE_TYPE Movetype;
	}CharaSet;

	CResult();
	~CResult();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMeshField *GetMeshField(void) { return m_pMeshField; }			// �n�ʂ̎擾
	static void SetRanking(int nNumPlayer, CPlayer::PLAYER_TYPE type, CCharaBase::CHARACTOR_MOVE_TYPE typeM, int nPoint);
	static void SetCharaSelect(int PlNum, CPlayer::PLAYER_TYPE type) { m_type[PlNum] = type; }
	void TexPoint(int nPlayer, int nPoint);
	static CPlayer *GetPlayer(int nNumPlayer = 0) { return (nNumPlayer < MAX_PLAYER && nNumPlayer >= 0) ? m_pPlayer[nNumPlayer] : m_pPlayer[0]; }		// �v���C���[�̎擾

private:
	/* �|���S���̎�� */
	typedef enum
	{
		RESULTTYPE_WINDOW = 0,	//�E�B���h�E
		RESULTTYPE_CALLOUT_1,	//�����o���F1��
		RESULTTYPE_CALLOUT_2,	//�����o���F2��
		RESULTTYPE_CALLOUT_3,	//�����o���F3��
		RESULTTYPE_CALLOUT_4,	//�����o���F4��
		RESULTTYPE_MAX			//�ő吔
	}STAGESELECTTYPE;

	void InitPointer(void);
	void SetPolygon(void);
	void SetAlpha(void);
	void Set2DUI(int nNum,int nPosNum);
	void RankTex(int nNum, int nRank);
	void PLNumTex(int nNum, int nChara, CCharaBase::CHARACTOR_MOVE_TYPE type);
	void SetNumCallout(int nNum, int Rank, CCharaBase::CHARACTOR_MOVE_TYPE type);

	static CPlayer *m_pPlayer[MAX_PLAYER];
	static CPlayer::PLAYER_TYPE m_type[MAX_PLAYER];
	static CharaSet m_ResultChara[MAX_PLAYER];
	static CMeshField *m_pMeshField;
	CSelectMenu *m_pSeletMenu;
	CNumber *m_apNumber[MAX_PLAYER][MAX_POINT];	// �i���o�[�ւ̃|�C���^
	CScene2D *m_apScene2D[RESULTTYPE_MAX];		//���o�n2D�|���S��
	CScene2D *m_apPlayerIcon[MAX_PLAYER];		//�v���C���[�̃A�C�R��
	CScene2D *m_apRanking[MAX_PLAYER];			//����
	CScene2D *m_apPlayerNum[MAX_PLAYER];		//�v���C���[�ԍ�

	bool m_bMenu;
	bool m_bMenuCreate;							//���j���[�𐶐��������̃t���O
	D3DXVECTOR3 m_RankPos[MAX_PLAYER];			//���ʂ̈ʒu��ۑ�
	D3DXVECTOR3 m_PlayerNumPos[MAX_PLAYER];		//�v���C���[�i���o�[�̈ʒu��ۑ�
	D3DXVECTOR3 m_PlayerIconPos[MAX_PLAYER];	//�A�C�R���̈ʒu��ۑ�
	D3DXVECTOR2 m_RankIconSize[MAX_PLAYER];		//���ʂ̃T�C�Y��ۑ�(X:��,Y:����)
	D3DXVECTOR2 m_PlayerNumSize[MAX_PLAYER];	//�v���C���[�i���o�[�̃T�C�Y��ۑ�(X:��,Y:����)
	D3DXVECTOR2 m_PlayerIconSize[MAX_PLAYER];	//�v���C���[�i���o�[�̃T�C�Y��ۑ�(X:��,Y:����)
};
#endif