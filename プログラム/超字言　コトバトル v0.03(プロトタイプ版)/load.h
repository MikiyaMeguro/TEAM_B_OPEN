//=============================================================================
//
// モデルの読み込み処理 [load.h]
// Author : 目黒 未来也
//
//=============================================================================
#ifndef _LOAD_H_
#define _LOAD_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//========================================
// クラスの定義
//========================================
//=====================
// オブジェクトクラス
//=====================
class CLoad
{
public:
	typedef enum // cppのやつと数と並びを揃える
	{
		MODEL_CAR0 = 0,	// 車0
		MODEL_CAR1,		// 車1
		MODEL_DESK,		// 机
		MODEL_PULIN,	// プリン
		MODE_KNIFE,		// ナイフ
		MODE_APPLE,		// アップル
		MODE_PALLET,	// 絵具
		MODE_TAICO,		// タイヤ
		MODE_WHEEL,		// 太鼓
		MODE_COIN,		// コイン
		MODEL_BOX,		// 箱
		MODEL_SAMPLE_PLAYER,	//プレイヤー(Sample)
		MODEL_MAX,
	} MODEL;

	CLoad();		// コンストラクタ
	~CLoad();	// デストラクタ

	static HRESULT LoadModel(void);
	static void UnloadModel(void);

	static LPD3DXMESH GetMesh(int nIdx);
	static LPD3DXBUFFER GetBuffMat(int nIdx);
	static DWORD GetNumMat(int nIdx);


	static void LoadFile(void);
	static char *ReadLine(FILE *pFile, char *pDst);	//1行読み込み
	static char *GetLineTop(char *pStr);			//行の先頭を取得
	static int  PopString(char *pStr, char *pDest);	//行の最後を切り捨て

private:
	static LPD3DXMESH		*m_pMesh;		// メッシュ情報（頂点情報）へのポインタ
	static LPD3DXBUFFER		*m_pBuffMat;		// マテリアル情報へのポインタ
	static DWORD			*m_nNumMat;		// マテリアル情報の数
	static char m_apModelName[MODEL_MAX][256];
	static const char *m_apModelFilename[];
	static int m_nCntModel;
	static int m_nMaxModel;
};

#endif