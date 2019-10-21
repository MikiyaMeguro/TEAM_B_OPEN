//=============================================================================
//
// プレイヤーの体パーツ処理 [CharaParts.h]
// Author : Kodama Yuto
//
//	クラスの概要
//
//=============================================================================
#ifndef _CHARA_PARTS_H_
#define _CHARA_PARTS_H_

#include "main.h"
#include "sceneX.h"
//=============================================================================
//	クラス定義
//=============================================================================
class CCharaParts : public CSceneX
{
public:
	CCharaParts();
	~CCharaParts();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
};
#endif // !_CHARA_PARTS_H_
