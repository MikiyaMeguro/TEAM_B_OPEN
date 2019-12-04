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

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_PLAYER (4)
#define MAX_POINT (2)
#define MAX_RESULT_TEX (1)

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
	static CPlayer *GetPlayer(int nNumPlayer = 0) { return (nNumPlayer < MAX_PLAYER && nNumPlayer >= 0) ? m_pPlayer[nNumPlayer] : m_pPlayer[0]; }		// �v���C���[�̎擾

private:
	/* �|���S���̎�� */
	typedef enum
	{
		RESULTTYPE_WINDOW = 0,	//�E�B���h�E
		RESULTTYPE_MAX			//�ő吔
	}STAGESELECTTYPE;

	void InitPointer(void);
	void SetPolygon(void);
	void SetAlpha(void);

	static CPlayer *m_pPlayer[MAX_PLAYER];
	static CPlayer::PLAYER_TYPE m_type[MAX_PLAYER];
	static CharaSet m_ResultChara[MAX_PLAYER];
	static CMeshField *m_pMeshField;
	CSelectMenu *m_pSeletMenu;
	CNumber *m_apNumber[MAX_PLAYER][MAX_POINT];	// �i���o�[�ւ̃|�C���^
	CScene2D *m_apScene2D[MAX_RESULT_TEX];		//���o�n2D�|���S��
	CScene2D *m_apPlayerIcon[MAX_PLAYER];		//�v���C���[�̃A�C�R��
	CScene2D *m_apRanking[MAX_PLAYER];			//����
	CScene2D *m_apPlayerNum[MAX_PLAYER];		//�v���C���[�ԍ�

	bool m_bMenu;
	bool m_bMenuCreate;							//���j���[�𐶐��������̃t���O

};
#endif