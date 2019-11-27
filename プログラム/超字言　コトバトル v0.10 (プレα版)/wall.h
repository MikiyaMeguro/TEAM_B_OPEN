//=============================================================================
//
// 壁処理 [wall.h]
// Author : YUTARO ABE
//
//=============================================================================
#ifndef _WALL_H_
#define _WALL_H_

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
class CWall : public CScene3D
{// シーン3D（親：CScene）
public:

	CWall();															// コンストラクタ
	~CWall();															// デストラクタ
																		// 初期化処理
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, int nType,int nTexType);
	void Uninit(void);													// 終了処理
	void Update(void);													// 更新処理
	void Draw(void);													// 描画処理
																		// 生成
	static CWall *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, int nType, int nTexType);		// 当たり判定
	int GetType(void) { return m_nType; }
private:
	static LPDIRECT3DTEXTURE9		m_pTexture[MAX_WALL_TEX];			// テクスチャ情報へのポインタ
	int m_nType;
	int m_nAnimCounter;
	int m_nCounter;
	D3DXVECTOR3 m_move;

};

#endif