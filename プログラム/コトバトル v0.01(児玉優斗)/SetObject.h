//=============================================================================
//
// オブジェクト配置処理 [SetObject.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _SETOBJECT_H_
#define _SETOBJECT_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
//　前方宣言
//*****************************************************************************
class CSceneX;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_MATTEX	(20)

//*********************************************************************
//プレイヤークラスの定義
//*********************************************************************
class CSetObject : public CScene //派生クラス
{
public:
	//モデルの種類
	typedef enum
	{
		MODELTYPE_BOX000 = 0,	//BOX
		MODELTYPE_MAX,			//最大数
	}MODELTYPE;

	CSetObject();
	~CSetObject();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static CSetObject *Create();
	D3DXVECTOR3 GetPos(void);

	static void LoadFile(void);

	static char *ReadLine(FILE *pFile, char *pDst);	//1行読み込み
	static char *GetLineTop(char *pStr);			//行の先頭を取得
	static int  PopString(char *pStr, char *pDest);	//行の最後を切り捨て


private:
	//メンバ変数
public:
};

#endif