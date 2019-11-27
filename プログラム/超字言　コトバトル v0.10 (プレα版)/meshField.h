//=============================================================================
//
// メッシュフィールドの処理 [meshFiled.h]
// Author :
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MESHFIELD_TEXTURE_NAME	"data\\TEXTURE\\field001.jpg"	// 地面のテクスチャ名
#define	TOUL_FILENAME			"toul.bin"					// ツールのテキスト
#define POLYGON_X				(20)						// ポリゴンの数（X）
#define POLYGON_Z				(20)						// ポリゴンの数（Z）
#define MESHFIELD_SIZE			(40.0f)						// メッシュフィールドの大きさ
#define NUM_POLYGON				(10000)						// メッシュフィールドの大きさ
#define MESH_CENTER				((POLYGON_X / 2) * -MESHFIELD_SIZE + (MESHFIELD_SIZE))	//中央値

//========================================
// クラスの定義
//========================================
//=========================
// メッシュフィールドクラス
//=========================
class CMeshField : public CScene
{
public:
	CMeshField(int nPriority = 3, OBJTYPE objType = OBJTYPE_MESH_FIELD);	// コンストラクタ
	~CMeshField();														// デストラクタ

	static CMeshField *Create(D3DXVECTOR3 pos);							// オブジェクトの生成

	HRESULT Init(void);										// メッシュフィールド初期化処理
	void Uninit(void);													// メッシュフィールド終了処理
	void Update(void);													// メッシュフィールド更新処理
	void Draw(void);													// メッシュフィールド描画処理

	float GetHeight(D3DXVECTOR3 pos);									// 高さの取得
	bool GetHeightbool(D3DXVECTOR3 &pos);								//地面との当たり判定
	void SetHeight(D3DXVECTOR3 pos, float fValue, float fRange);		// 高さの設定

	void SaveHeight(void);												// 高さのセーブ
	void LoadHeight(void);												// 高さのロード

private:
	LPDIRECT3DTEXTURE9		m_pTexture;									// テクスチャへのポインタ
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;									// インデックスバッファへのポインタ
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;									// 頂点バッファへのポインタ
	D3DXMATRIX				m_mtxWorld;									// ワールドマトリックス
	D3DXVECTOR3				m_pos;										// ポリゴンの位置
	D3DXVECTOR3				m_rot;										// ポリゴンの向き
	D3DXVECTOR3				m_aNor[NUM_POLYGON];
	int						m_nNumVerTex;								// 頂点数
	int						m_nNumIndex;								// インデックス数
	int						m_nNumPolygon;								// ポリゴン数
	bool					m_bRand;									// ポリゴンに乗っている
};

#endif