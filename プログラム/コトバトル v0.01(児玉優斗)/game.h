//=============================================================================
//
// メイン処理 [main.h]
// Author : 山下敦史
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"
#include"word_manager.h"
#include "player.h"
#include "tube.h"

//前方宣言
class CWordManager;
class CPlayer;
class CTube;

//クラス（シーン2Dの派生クラス）
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

	// 取得の関数
	static CWordManager *GetWordManager(void) { return m_pWordManager; }		// 言葉管理の取得
	static CPlayer *GetPlayer(void) { return m_pPlayer; }					// プレイヤーの取得
	static CTube *GetTube(void) { return m_pTube; }							// 文字の可視化UIの取得

private:
	void CameraSetting(void);
	static CWordManager *m_pWordManager;
	static CPlayer *m_pPlayer;
	static CTube *m_pTube;
};
#endif