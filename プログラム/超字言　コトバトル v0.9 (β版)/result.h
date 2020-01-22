//=============================================================================
//
// リザルト処理 [result.h]
// Author : 目黒未来也/後閑茜
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "scene.h"
#include "player.h"
#include "meshField.h"
#include "SelectMenu.h"
//=============================================================================
// 前方宣言
//=============================================================================
class CPlayer;
class CNumber;
class CScene2D;
class CCharaBase;
class CSpotLight;
//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_PLAYER (4)
#define MAX_POINT (2)
#define MAX_MODEL (4)			//観客席の数
#define MAX_AUDIENCE (27)		//観客全体の数
#define MAX_STADIUMSTEP (3)		//観客席の段数
#define MAX_CURTAIN		(2)		// カーテン
//========================================
// クラスの定義
//========================================
class CResult : public CScene
{
public:

	typedef struct
	{
		int nId;
		int nNumRank;
		int nPoint;
		CPlayer::PLAYER_TYPE type;
		CCharaBase::CHARACTOR_MOVE_TYPE Movetype;
	}CharaSet;

	CResult();
	~CResult();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMeshField *GetMeshField(void) { return m_pMeshField; }			// 地面の取得
	static void SetRanking(int nNumPlayer, int nId,CPlayer::PLAYER_TYPE type, CCharaBase::CHARACTOR_MOVE_TYPE typeM, int nPoint);
	static void SetCharaSelect(int PlNum, CPlayer::PLAYER_TYPE type) { m_type[PlNum] = type; }
	void TexPoint(int nPlayer, int nPoint);
	static CPlayer *GetPlayer(int nNumPlayer = 0) { return (nNumPlayer < MAX_PLAYER && nNumPlayer >= 0) ? m_pPlayer[nNumPlayer] : m_pPlayer[0]; }		// プレイヤーの取得

private:
	/* ポリゴンの種類 */
	typedef enum
	{
		RESULTTYPE_WINDOW = 0,	//ウィンドウ
		RESULTTYPE_CALLOUT_1,	//吹き出し：1位
		RESULTTYPE_CALLOUT_2,	//吹き出し：2位
		RESULTTYPE_CALLOUT_3,	//吹き出し：3位
		RESULTTYPE_CALLOUT_4,	//吹き出し：4位
		RESULTTYPE_MAX			//最大数
	}STAGESELECTTYPE;

	/* エフェクトのフェード */
	typedef enum
	{
		EFFECTPRO_NONE = 0,
		EFFECTPRO_PATTURN1,
		EFFECTPRO_PATTURN2,
		EFFECTPRO_MAX
	}EFFECTPRO_STATE;

	/* 2Dの演出 */
	typedef enum
	{
		PRODUCTION_NONE = 0,
		PRODUCTION_START,				// 開始
		PRODUCTION_FALL_WINDOW,			// 枠降下
		PRODUCTION_FADERANK,			// 順位フェードイン
		PRODUCTION_FALL_ICON,			// アイコン降下
		PRODUCTION_TURN_STAND,			// アイコン回転(裏→立てる)
		PRODUCTION_TURN,				// アイコン回転（立った状態→表）
		PRODUCTION_TURN_TABLE,			// アイコン回転(表完全開示)
		PRODUCTION_TURN_FADEPLNUM,		// プレイヤーナンバーフェード
		PRODUCTION_COLLOUT_EXPANSION,	// ポイント枠を表示
		PRODUCTION_FADEPOINT,			// ポイントを表示
		PRODUCTION_FINISH,				// 終了
		PRODUCTION_MAX					// 最大値
	}PRODUCTION;

	/* マスクの演出 */
	typedef enum
	{
		MASKPRODUCION_NONE = 0,
		MASKPRODUCION_OPEN,
		MASKPRODUCION_CLOSE,
		MASKPRODUCION_MAX
	}MASKPRODUCION;

	void InitPointer(void);
	void SetPolygon(void);
	void SetModel(void);
	void Set2DUI(int nNum,int nPosNum);
	void RankTex(int nNum, int nRank);
	void PLNumTex(int nNum, int nRank,int nChara, CCharaBase::CHARACTOR_MOVE_TYPE type);
	void SetNumCallout(int nNum, int nIconPos, CCharaBase::CHARACTOR_MOVE_TYPE type);
	void EffectPro(void);
	void SetAudience(void);
	void Production(void);
	void MaskPro(void);

	static CPlayer *m_pPlayer[MAX_PLAYER];
	static CPlayer::PLAYER_TYPE m_type[MAX_PLAYER];
	static CharaSet m_ResultChara[MAX_PLAYER];
	static CMeshField *m_pMeshField;
	static CScene3D *m_apAudience[MAX_AUDIENCE];								//観客
	CScene3D *m_apMask[MAX_CURTAIN];											//マスク
	CSelectMenu *m_pSeletMenu;
	CNumber *m_apNumber[MAX_PLAYER][MAX_POINT];									// ナンバーへのポインタ
	CScene2D *m_apScene2D[RESULTTYPE_MAX];										//演出系2Dポリゴン
	CScene2D *m_apPlayerIcon[MAX_PLAYER];										//プレイヤーのアイコン
	CScene2D *m_apRanking[MAX_PLAYER];											//順位
	CScene2D *m_apPlayerNum[MAX_PLAYER];										//プレイヤー番号
	CScene2D *m_apEffect[MAX_PLAYER][2];										//エフェクト[プレイヤー人数][エフェクト出す数]
	CSceneX *m_apStadium[MAX_MODEL];											//モデルの配置
	CSpotLight *m_pSpotLight[MAX_PLAYER];										//スポットライト
	bool m_bMenu;
	bool m_bMenuCreate;							//メニューを生成したかのフラグ
	bool m_bEffectPro;							//エフェクト演出が始まってるかどうかフラグ
	bool m_bProductin;							//演出のフラグ
	bool m_bCurtain;
	D3DXVECTOR3 m_RankPos[MAX_PLAYER];			//順位の位置を保存
	D3DXVECTOR3 m_PlayerNumPos[MAX_PLAYER];		//プレイヤーナンバーの位置を保存
	D3DXVECTOR3 m_PlayerIconPos[MAX_PLAYER];	//アイコンの位置を保存
	D3DXVECTOR2 m_RankIconSize[MAX_PLAYER];		//順位のサイズを保存(X:幅,Y:高さ)
	D3DXVECTOR2 m_PlayerNumSize[MAX_PLAYER];	//プレイヤーナンバーのサイズを保存(X:幅,Y:高さ)
	D3DXVECTOR2 m_PlayerIconSize[MAX_PLAYER];	//プレイヤーナンバーのサイズを保存(X:幅,Y:高さ)
	D3DXVECTOR3 m_RankEffect[MAX_PLAYER][2];	//プレイヤーナンバーの位置を保存
	D3DXVECTOR2 m_EffectAlpha;					//エフェクトのalpha値管理（X:エフェクト番号0　Y:エフェクト番号1）
	EFFECTPRO_STATE m_EffectState;				//エフェクトの状態管理
	PRODUCTION m_Production;					//演出
	MASKPRODUCION m_MaskPro;					//カーテンの演出
	bool		m_bCurtainSound;

	int nCntFadeTime = 0;
};
#endif