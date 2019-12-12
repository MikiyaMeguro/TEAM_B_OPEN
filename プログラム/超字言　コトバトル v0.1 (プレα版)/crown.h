//=============================================================================
//
// 王冠処理 [crown.h]
// Author : Shun Yokomichi
//
//=============================================================================
#ifndef _CROWN_H_
#define _CROWN_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"		// メイン
#include "sceneBillboard.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_WALL_TEX (1)

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCrown : public CSceneBillBoard
{// シーン3D（親：CScene）
public:

	CCrown();															// コンストラクタ
	~CCrown();														// デストラクタ
																		// 初期化処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, char *cpName);
	void Uninit(void);													// 終了処理
	void Update(void);													// 更新処理
	void Draw(void);													// 描画処理
																		// 生成
	static CCrown *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, char *cpName);		// 当たり判定

	void SetDrawFlag(bool bDraw) { m_bDraw = bDraw; };
	void SetCameraNum(int nCamera) { m_nCamera = nCamera; };
	bool GetVision(int nPlayer) { return m_bVision[nPlayer]; };
	void SetVision(int nPlayer, bool Vision) { m_bVision[nPlayer] = Vision; };

private:
	int m_nCounter;
	bool m_bDraw;
	D3DXVECTOR3 m_move;
	int	m_nCamera;			//カメラの番号
	bool m_bVision[4];		//見えているかどうか
};

#endif