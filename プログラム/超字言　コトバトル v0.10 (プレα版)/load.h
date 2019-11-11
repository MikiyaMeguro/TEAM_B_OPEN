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
		MODE_WALL_SMALL = 0,// 小さい壁
		MODE_WALL_BIG,	// 大きい壁
		MODE_GEAR,		// 歯車
		MODEL_BOX,		// 箱
		MODEL_DODAI,	// 土台
		MODE_DUST,		// ゴミ
		MODEL_SAMPLE_PLAYER,	//プレイヤー(Sample)
		MODEL_CAR0,		// 車0
		MODEL_MIC,		// マイク
		MODEL_DESK,		// 机
		MODEL_PULIN,	// プリン
		MODE_KNIFE,		// ナイフ
		MODE_APPLE,		// アップル
		MODE_PALLET,	// 絵具
		MODE_TAICO,		// タイヤ
		MODE_WHEEL,		// 太鼓
		MODE_COIN,		// コイン
		MODE_SUIKA,		// すいか
		MODE_TARAI,		// たらい
		MODE_POT,		// やかん
		MODE_IKARI,		// いかり
		MODE_IKADA,		// いかだ
		MODEL_SAIHU,	// 財布
		MODEL_KARUTA,	// かるた
		MODEL_CAMERA,	// カメラ
		MODEL_TWIG,		// こえだ
		MODEL_STRAWBERRY,// イチゴ
		MODEL_EGG,		// たまご
		MODEL_LANCE,	// ランス
		MODEL_KADANN,	// かだん
		MODEL_KATANA,	// 刀
		MODEL_LOG	,	// まるた
		MODEL_ICE,		// つらら
		MODEL_DANGO,	// だんご
		MODEL_MAKURA,	// まくら
		MODEL_KUNAI,	// くない
		MODEL_FISH,		// さかな
		MODEL_VOLCANO,	// かざん
		MODEL_NAZCA,	// なすか
		MODEL_TANK,		// たんく
		MODEL_YAGURA,	// やぐら
		MODEL_CHAIR,	// ざいす
		MODEL_CONGA,	// こんが
		MODEL_DICE,		// だいす
		MODEL_TREASURECHEST,	// たから
		MODEL_GRASS,	// ガラス
		MODEL_STRETCHER,	// たんか
		MODEL_RING,	// リング
		MODEL_KUSAYA,	// くさや
		MODEL_SAZAE,	// サザエ
		MODEL_TILE,	// タイル
		MODEL_Rice,	// ライス
		MODEL_Comic,	// マンガ
		MODEL_Fuigo,	// ふいご
		MODEL_Namako,	// ナマコ
		MODEL_Zugai,	// ずがい
		MODEL_Seaweed,	// コンブ
		MODEL_Laitc,	// らいち
		MODEL_Mekabu,	// めかぶ
		MODEL_Medic,	// くすり
		MODEL_Kaiga,	// かいが
		MODEL_MAX
	} MODEL;

	CLoad();		// コンストラクタ
	~CLoad();	// デストラクタ

	static HRESULT LoadModel(void);
	static void UnloadModel(void);

	static LPD3DXMESH GetMesh(int nIdx);
	static LPD3DXBUFFER GetBuffMat(int nIdx);
	static DWORD GetNumMat(int nIdx);
	static void TextureSetting(int nModel);
	static LPDIRECT3DTEXTURE9 *GetTexture(MODEL Model);

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

	static LPDIRECT3DTEXTURE9	*m_pTexture[MODEL_MAX];			// テクスチャへのポインタ
};

#endif