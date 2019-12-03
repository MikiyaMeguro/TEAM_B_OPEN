//=============================================================================
//
// キャラセレクトのカーソル処理 [CharaSelect_Cursol.h]
// Author : 目黒未来也/後閑茜
//
//=============================================================================
#ifndef _CHARASELECT_CURSOL_H_
#define _CHARASELECT_CURSOL_H_

#include "scene2D.h"
#include "CharaSelect.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CScene2D;
class CPlayer;
class CFade;
class CManager;
class CCharaSelect;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCharaSelCursol : public CScene2D
{
public:
	CCharaSelCursol();
	~CCharaSelCursol();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CCharaSelCursol *Create(int nId);

	CCharaSelect::SELECT_STATE GetSelectState() { return m_SelectState; }
	CPlayer::PLAYER_TYPE GetPlayerType() { return m_CharaType; }
	CPlayer::PLAYER_TYPE GetPlayerTypeOld() { return m_CharaTypeOld; }
	bool GetSelMove(void) { return m_bPCSelMove; }
	CScene2D *GetpBadge(void) { return this->m_apBadge2D; }
	CScene2D *GetpCursor(void) { return this->m_apCursor2D; }

private:
	void Initpointer(void);																						//ポインタの初期化
	void InitCharaSelectPoly(void);																				//ポインタの初期化
	void PressGauge(CFade *pFade, CManager *pManager, int operation);											//戻るボタン押してる時のゲージ
	void SetCommand(void);																						//コマンド設定
	void Move(CFade *pFade, CManager *pManager, int nControllNum);												//移動/選択処理
	D3DXVECTOR3 MoveRestriction(D3DXVECTOR3 pos);																//移動制限
	void Set(int nId);

	CScene2D *m_apCursor2D;		//カーソル
	CScene2D *m_apBadge2D;		//バッジ
	CScene2D *m_apGauge2D;		//戻る時のゲージ
	CPlayerSelect::SELECTPLAYER *m_PlayerNum;						//プレイヤーの人数
	float m_fGaugeSizeX;								//戻るゲージの長さを保管
	float m_fMaxGaugeX;									//ゲージの最大の長さ
	int m_nCntGauge;									//ゲージ長押し時間を管理
	int m_nId = 0;				//ID
	CPlayer::PLAYER_TYPE m_CharaType;		//選ばれたキャラの種類
	CPlayer::PLAYER_TYPE m_CharaTypeOld;	//前回選ばれたキャラの種類
	CCharaSelect::SELECT_STATE m_SelectState;							//演出の状態
	CCharaSelect::SELECT_STATE m_SelectStateold;						//前回の演出状態を記録
	D3DXVECTOR3 m_move;						//移動量
	D3DXVECTOR3 m_pos;						//移動量
	bool m_bPCSelMove;						//選ばれていない時のみ移動できる
	bool m_bPlayer;							//プレイヤーかどうか見る
};
#endif