//=============================================================================
//
// ���C������ [main.h]
// Author : �R���֎j
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"
#include"word_manager.h"
#include "player.h"
#include "tube.h"

//�O���錾
class CWordManager;
class CPlayer;
class CTube;

//=============================================================================
// �}�N����`
//=============================================================================
#define WORD_TUBE_POS	(D3DXVECTOR3(50.0f, 240.0f, 0.0f))
#define WORD_TUBE_SIZE	(D3DXVECTOR2(60.0f, 160.0f))
#define MAX_PLAYER (4)

//�N���X�i�V�[��2D�̔h���N���X�j
class CGame
{
public:
	CGame();
	~CGame();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void LoadChara(void);
	static CGame *Create(void);

	void WordCreate(void);	// �����̐����̊Ǘ�

	// �擾�̊֐�
	static CWordManager *GetWordManager(void) { return m_pWordManager; }				// ���t�Ǘ��̎擾
	static CPlayer *GetPlayer(int nNumPlayer = 0) { return (nNumPlayer < MAX_PLAYER && nNumPlayer >= 0) ? m_pPlayer[nNumPlayer] : m_pPlayer[0]; }		// �v���C���[�̎擾
	static CTube *GetTube(void) { return m_pTube; }										// �����̉���UI�̎擾

private:
	void CameraSetting(int nNum);		// �l���ɉ������J��������
	void PlayerSetting(int nNum);		// �l���ɉ������v���C���[����
	static CWordManager *m_pWordManager;
	static CPlayer *m_pPlayer[MAX_PLAYER];
	static CTube *m_pTube;
};
#endif