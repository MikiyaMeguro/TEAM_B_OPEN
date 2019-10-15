//=============================================================================
//
// シーン処理 [scene.h]
// Author : 目黒 未来也
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_OBJECT		(256)	// テクスチャの数
#define NUM_PRIORITY	(8)		// 優先順位の数
#define SCENEX_PRIORITY	(3)
#define ENEMY_PRIORITY	(2)
#define PLAYER_PRIORITY	(2)
#define CPU_PRIORITY	(2)
#define SELECT_PRIORITY	(3)
#define SHADOW_PRIORITY	(6)

//========================================
// クラスの定義
//========================================
//=====================
// オブジェクトクラス
//=====================
class CScene
{
public:
	typedef enum
	{// オブジェクトの種類
		OBJTYPE_NONE = 0,
		OBJTYPE_SCENE2D,	// 2Dポリゴン
		OBJTYPE_SCENE3D,	// 3Dポリゴン
		OBJTYPE_SCENEX,		// モデル
		OBJTYPE_BILLBOARD,	// ビルボード
		OBJTYPE_MESHFIELD,	// メッシュフィールド
		OBJTYPE_PLAYER,
		OBJTYPE_ENEMY,
		OBJTYPE_SHADOW,
		OBJTYPE_UI,
		OBJTYPE_EFFECT,
		OBJTYPE_ANIM,
		OBJTYPE_WALL,
		OBJTYPE_FIELD,
		OBJTYPE_PARTICLE,
		OBJTYPE_PAUSE,
		OBJTYPE_MODESELECT,
		OBJTYPE_TIME,		// 時間
		OBJTYPE_MAX			// 総数
	} OBJTYPE;

	CScene(int nPriority = 3, OBJTYPE objType = OBJTYPE_NONE);	// コンストラクタ
	virtual ~CScene();											// デストラクタ

	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	//virtual void SetScene(D3DXVECTOR3 pos) = 0;

	static void ReleseAll(void);								// 全てのオブジェクトの解放
	static void UpdeteAll(void);								// 全てのオブジェクトの更新
	static void DrawAll(void);									// 全てのオブジェクトの描画
	static CScene *GetTop(int nPriority);						// 先頭のオブジェクトを取得
	CScene *GetNext(void);										// 次のオブジェクトのポインタを取得
	bool GetDeath(void);										// 死亡フラグを取得
	OBJTYPE GetObjType(void);									// オブジェクトの種類の取得
	void SetObjType(OBJTYPE objType);							// オブジェクトの種類の設定
	int GetPriority(void);
	static void SetbPause(bool bPause) { m_bPause = bPause; };
	static bool GetbPause(void) { return m_bPause; };

protected:
	void Release(void);											// 死亡フラグを立てる

private:
	void DeleteAll(void);										// 死亡フラグが立ったオブジェクトを消す

	static CScene *m_apTop[NUM_PRIORITY];						// 先頭オブジェクトへのポインタ
	static CScene *m_apCur[NUM_PRIORITY];						// 現在（最後尾）のオブジェクトへのポインタ
	CScene *m_pPrev;											// 前のオブジェクトへのポインタ
	CScene *m_pNext;											// 次のオブジェクトへのポインタ
	bool m_bDeath;												// 死亡フラグ
	static int m_nNumAll;										// 敵の総数 『静的メンバ変数』
	int m_nID;													// 自分自身のID
	int m_nPriority;											// 優先順位の番号
	static int m_nNumPriority[NUM_PRIORITY];					// その優先順位にあるオブジェクトの数
	OBJTYPE m_objType;											// オブジェクトの種類
	static bool	m_bPause;										// ポーズ

};

#endif