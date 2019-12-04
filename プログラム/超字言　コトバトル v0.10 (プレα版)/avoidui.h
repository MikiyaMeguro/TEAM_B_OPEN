//=============================================================================
//
// 回避UI処理 [avoidui.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _AVOIDUI_H_
#define _AVOIDUI_H_

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "main.h"		// メイン
#include "scene3d.h"		// シーン
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
class CAvoidUi : public CScene3D
{// シーン3D（親：CScene）
public:

	CAvoidUi();															// コンストラクタ
	~CAvoidUi();														// デストラクタ
																		// 初期化処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV);
	void Uninit(void);													// 終了処理
	void Update(void);													// 更新処理
	void Draw(void);													// 描画処理
																		// 生成
	static CAvoidUi *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV);		// 当たり判定

	void SetDrawFlag(bool bDraw) { m_bDraw = bDraw; };
private:
	int m_nCounter;
	bool m_bDraw;
	D3DXVECTOR3 m_move;
};

#endif