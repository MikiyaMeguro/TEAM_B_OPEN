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

	// �擾�̊֐�
	static CWordManager *GetWordManager(void) { return m_pWordManager; }		// ���t�Ǘ��̎擾
	static CPlayer *GetPlayer(void) { return m_pPlayer; }					// �v���C���[�̎擾
	static CTube *GetTube(void) { return m_pTube; }							// �����̉���UI�̎擾

private:
	void CameraSetting(void);
	static CWordManager *m_pWordManager;
	static CPlayer *m_pPlayer;
	static CTube *m_pTube;
};
#endif