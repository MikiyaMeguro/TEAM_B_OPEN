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
		//--------------------------------------
		// 背景モデル
		//--------------------------------------
		MODE_WALL_SMALL = 0,// 小さい壁
		MODE_WALL_BIG,		// 大きい壁
		MODE_GEAR,			// 歯車
		MODEL_BOX,			// 箱
		MODEL_DODAI,		// 土台
		MODE_DUST,			// ゴミ
		MODEL_SAMPLE_PLAYER,// プレイヤー(Sample)
		MODEL_PROPELLER,	// プロペラ
		MODEL_DRAWN_X,		// ドローンX
		MODEL_DRAWN_Z,		// ドローンZ
		MODEL_BGFROOR,		// 床
		MODEL_SWITCH,		// スイッチ
		MODEL_PODIUM1,		// 表彰台1
		MODEL_PODIUM2,		// 表彰台2
		MODEL_PODIUM3,		// 表彰台3
		MODEL_PAUL,			// 電気ポール
		MODEL_ALPHAMODEL00,	// 雷の見えない判定ver1
		MODEL_ALPHAMODEL01,	// 雷の見えない判定ver2
		MODEL_Seesaw,		// シーソー
		MODEL_Bench,		// ベンチ
		MODEL_House,		// 家
		MODEL_bridge,		// 橋(木)
		MODEL_Grren,		// 芝生
		MODEL_FSymbol,		// 噴水 シンボル
		MODEL_FWall,		// 噴水 囲い
		MODEL_Wood,			// 木
		MODEL_Snowfall,		// 落屑
		MODEL_SnowWalldistortion,		// 雪壁
		MODEL_Telephonepole,		// 電柱
		MODEL_KANBAN,		// 看板(商店街)
		MODEL_GATE,			// 広場門
		MODEL_ORI,			// 檻
		MODEL_HASUICO,		// 排水溝
		MODEL_ICEFLOOR,		// 氷床
		MODEL_FLOOR,		// 第三地形
		MODEL_ORI2,			// 檻2
		MODEL_BUSH,			// 草むら
		MODEL_ITA,			// 板柵
		MODEL_ITA2,			// 板柵
		MODEL_KUSA,			// 草
		MODEL_ROCK,			// 石
		MODEL_SNOW,			// 雪

		MODEL_STAGEFLOOR,		// 各ステージの床
		MODEL_STAGEFLOOR001,	// 各ステージの床
		MODEL_STAGEFLOOR002,	// 各ステージの床

		MODEL_STAGEOUT,			// 各ステージ周り

		MODEL_RANKINGSTADIUM,	//ランキングのスタジアム背景

		MODEL_SNOWBUSH,			// 雪草むら
		MODEL_POLE2,		    // ポール
		MODEL_POLE3,		    // ポール
		MODEL_SnowMan,		    // オラフスキー
		//--------------------------------------
		// 文字モデル
		//--------------------------------------
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
		MODEL_LOG,	// まるた
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
		MODEL_RING,		// リング
		MODEL_KUSAYA,	// くさや
		MODEL_SAZAE,	// サザエ
		MODEL_TILE,		// タイル
		MODEL_RICE,		// ライス
		MODEL_COMIC,	// マンガ
		MODEL_FUIGO,	// ふいご
		MODEL_NAMAKO,	// ナマコ
		MODEL_SEAWEED,	// コンブ
		MODEL_LAITC,	// らいち
		MODEL_MASK,		// マスク
		MODEL_MEKABU,	// めかぶ
		MODEL_MEDIC,	// くすり
		MODEL_KAIGA,	// かいが
		MODEL_ikura,	// いくら
		MODEL_menko,	// めんこ
		MODEL_Mace,		// めいす
		MODEL_Sarai,	// さらい
		MODEL_INK,		// インク
		MODEL_Zail,		// ざいる
		MODEL_Inari,	// いなり
		MODE_gakuhu,	// 楽譜
		MODEL_TAITU,	// タイツ
		MODEL_FLAG,		// カエル
		MODEL_PLUG,		// プラグ
		MODEL_SING,		// サイン
		MODEL_TAIMA,	// 大麻
		MODEL_SAKURA,	// サクラ
		MODEL_KAYAKU,	// 火薬

		MODEL_IRUI,		// いるい : いふく
		MODEL_KOTATU,	// こたつ
		MODEL_KUKUI,	// くくい
		MODEL_TAKOSU,	// タコス
		MODEL_SARADA,	// サラダ
		MODEL_MENMA,	// メンマ
		MODEL_TARAKO,	// たらこ


		MODEL_HUSUMA,	// ふすま
		MODEL_TANCE,	// たんす
		MODEL_NAMEKO,	// なめこ
		MODEL_DOLPHIN,	// いるか
		MODEL_ICHII,	// いちい
		MODEL_KANNA,	// かんな
		MODEL_IEI,		// いえい
		MODEL_EYE,		// めだま

		MODEL_SUDATI,	// すだち
		MODEL_RINSE,	// りんす
		MODEL_LAMP,		// らんぷ
		MODEL_SANGO,	// さんご
		MODEL_SUMAI,	// すまい
		MODEL_KUKURI,	// くくり
		MODEL_CORK,		// こるく

						// なふだ
						// サンゴ
						
						// するめ
						// すずめ
						// コアラ

		MODEL_MAX
	} MODEL;

	CLoad();		// コンストラクタ
	~CLoad();    	// デストラクタ

	static HRESULT LoadModel(void);
	static void UnloadModel(void);

	static LPD3DXMESH GetMesh(int nIdx);
	static LPD3DXBUFFER GetBuffMat(int nIdx);
	static DWORD GetNumMat(int nIdx);
	static void TextureSetting(int nModel);
	static LPDIRECT3DTEXTURE9 *GetTexture(MODEL Model);

	static void LoadFile(char *pFileName);
	static char *ReadLine(FILE *pFile, char *pDst);	//1行読み込み
	static char *GetLineTop(char *pStr);			//行の先頭を取得
	static int  PopString(char *pStr, char *pDest);	//行の最後を切り捨て

private:
	static LPD3DXMESH		*m_pMesh;			// メッシュ情報（頂点情報）へのポインタ
	static LPD3DXBUFFER		*m_pBuffMat;		// マテリアル情報へのポインタ
	static DWORD			*m_nNumMat;			// マテリアル情報の数
	static char m_apModelName[MODEL_MAX][256];
	static const char *m_apModelFilename[];
	static int m_nCntModel;
	static int m_nMaxModel;

	static LPDIRECT3DTEXTURE9	*m_pTexture[MODEL_MAX];			// テクスチャへのポインタ
};

#endif