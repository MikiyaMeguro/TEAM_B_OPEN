//=============================================================================
//
// ���U���g���� [result.h]
// Author : �ڍ�������
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
	}CharaSet;

	CResult();
	~CResult();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMeshField *GetMeshField(void) { return m_pMeshField; }			// �n�ʂ̎擾
	static void SetRanking(int nNumPlayer, CPlayer::PLAYER_TYPE type, int nPoint);
	static void SetCharaSelect(int PlNum, CPlayer::PLAYER_TYPE type) { m_type[PlNum] = type; }
	void TexPoint(int nPlayer, int nPoint);

private:
	static CPlayer *m_pPlayer[MAX_PLAYER];
	static CPlayer::PLAYER_TYPE m_type[MAX_PLAYER];
	static CharaSet m_ResultChara[MAX_PLAYER];

	static CMeshField *m_pMeshField;
	CSelectMenu *m_pSeletMenu;
	CNumber *m_apNumber[MAX_PLAYER][MAX_POINT];	// �i���o�[�ւ̃|�C���^
	bool m_bMenu;
	int nCounterMenu;

};
#endif