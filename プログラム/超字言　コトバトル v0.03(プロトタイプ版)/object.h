//=============================================================================
//
// オブジェクト処理 [object.h]
// Author : 横道 駿
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "scenex.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//========================================
// クラスの定義
//========================================
//=====================
// オブジェクトクラス
//=====================
class CObject : public CSceneX
{
public:
	CObject();					// コンストラクタ
	~CObject();									// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos);				// 3Dオブジェクト初期化処理
	void Uninit(void);							// 3Dオブジェクト終了処理
	void Update(void);							// 3Dオブジェクト更新処理
	void Draw(void);							// 3Dオブジェクト描画処理

	// 移動床の処理
	void BeltConveyor(D3DXVECTOR3 *pMove);
	void KnockBack(D3DXVECTOR3 *pMove);
	static CObject *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Scale,CSceneX::COLLISIONTYPE type, CLoad::MODEL model);	// オブジェクトの生成
	static HRESULT Load(void);
	static void UnLoad(void);


private:
};

#endif