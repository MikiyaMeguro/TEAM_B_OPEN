//=============================================================================
//
// ゲーム処理 [game.h]
// Author : 目黒 未来也
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"
#include "player.h"
#include "tube.h"
#include "meshField.h"
//前方宣言
class CPlayer;
class CTube;
class CPoint;

//=============================================================================
// マクロ定義
//=============================================================================
//********************************
// 1画面時の筒の位置
//********************************
#define WORD_TUBE001_POS_1P		(D3DXVECTOR3(50.0f, 590.0f, 0.0f))		// 2画面時(1P)の位置

//********************************
// 2画面時の筒の位置
//********************************
#define WORD_TUBE002_POS_1P		(D3DXVECTOR3(50.0f, 240.0f, 0.0f))		// 2画面時(1P)の位置
#define WORD_TUBE002_POS_2P		(D3DXVECTOR3(50.0f, 590.0f, 0.0f))		// 2画面時(2P)の位置
#define WORD_TUBE002_SIZE		(D3DXVECTOR2(60.0f, 160.0f))			// 2画面時のサイズ

//********************************
// 3画面時の筒の位置
//********************************
#define WORD_TUBE003_POS_1P		(D3DXVECTOR3(50.0f, 240.0f, 0.0f))		// 3画面時(1P)の位置
#define WORD_TUBE003_POS_2P		(D3DXVECTOR3(1220.0f, 240.0f, 0.0f))	// 3画面時(2P)の位置
#define WORD_TUBE003_POS_3P		(D3DXVECTOR3(50.0f, 590.0f, 0.0f))		// 3画面時(3P)の位置

//********************************
// 4画面時の筒の位置
//********************************
#define WORD_TUBE004_POS_1P		(D3DXVECTOR3(50.0f, 240.0f, 0.0f))		// 4画面時(1P)の位置
#define WORD_TUBE004_POS_2P		(D3DXVECTOR3(1220.0f, 240.0f, 0.0f))	// 4画面時(2P)の位置
#define WORD_TUBE004_POS_3P		(D3DXVECTOR3(50.0f, 590.0f, 0.0f))		// 4画面時(3P)の位置
#define WORD_TUBE004_POS_4P		(D3DXVECTOR3(1220.0f, 590.0f, 0.0f))	// 4画面時(4P)の位置

#define MAX_PLAYER (4)

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

	void WordCreate(void);	// 文字の生成の管理

	// 取得の関数
	static CPlayer *GetPlayer(int nNumPlayer = 0) { return (nNumPlayer < MAX_PLAYER && nNumPlayer >= 0) ? m_pPlayer[nNumPlayer] : m_pPlayer[0]; }		// プレイヤーの取得
	static CTube *GetTube(int nNum);		// 文字の可視化UIの取得
	static CMeshField *GetMeshField(void) { return m_pMeshField; }			// 文字の可視化UIの取得
	static CPoint *GetPoint(int nNum) { return m_pPoint[nNum]; }			// ポイントの取得
private:
	void CameraSetting(int nNum);		// 人数に応じたカメラ生成
	void PlayerSetting(int nNum);		// 人数に応じたプレイヤー生成
	void TubeSetting(int nNum);			// 人数に応じた筒の生成
	void SetPointFrame(int nNum);		// 人数に応じたポイントの生成
	static CPlayer *m_pPlayer[MAX_PLAYER];
	static CTube *m_apTube[MAX_PLAYER];
	static CPoint *m_pPoint[MAX_PLAYER];
	static CMeshField *m_pMeshField;

};
#endif