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

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_PLAYER (4)
#define MAX_POINT (2)
#define MAX_RESULT_TEX (1)

//========================================
// クラスの定義
//========================================
class CResult : public CScene
{
public:
	typedef struct
	{
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
	static void SetRanking(int nNumPlayer, CPlayer::PLAYER_TYPE type, CCharaBase::CHARACTOR_MOVE_TYPE typeM, int nPoint);
	static void SetCharaSelect(int PlNum, CPlayer::PLAYER_TYPE type) { m_type[PlNum] = type; }
	void TexPoint(int nPlayer, int nPoint);

private:
	/* ポリゴンの種類 */
	typedef enum
	{
		RESULTTYPE_WINDOW = 0,	//ウィンドウ
		RESULTTYPE_MAX			//最大数
	}STAGESELECTTYPE;
	
	void InitPointer(void);
	void SetPolygon(void);
	void SetAlpha(void);
	void Set2DUI(int nNum,int nPosNum);
	void RankTex(int nNum,int nRank);
	void PLNumTex(int nNum, int nChara, CCharaBase::CHARACTOR_MOVE_TYPE type);

	static CPlayer *m_pPlayer[MAX_PLAYER];
	static CPlayer::PLAYER_TYPE m_type[MAX_PLAYER];
	static CharaSet m_ResultChara[MAX_PLAYER];
	static CMeshField *m_pMeshField;
	CSelectMenu *m_pSeletMenu;
	CNumber *m_apNumber[MAX_PLAYER][MAX_POINT];	// ナンバーへのポインタ
	CScene2D *m_apScene2D[MAX_RESULT_TEX];		//演出系2Dポリゴン
	CScene2D *m_apPlayerIcon[MAX_PLAYER];		//プレイヤーのアイコン
	CScene2D *m_apRanking[MAX_PLAYER];			//順位
	CScene2D *m_apPlayerNum[MAX_PLAYER];		//プレイヤー番号

	bool m_bMenu;
	bool m_bMenuCreate;							//メニューを生成したかのフラグ
	D3DXVECTOR3 m_RankPos[MAX_PLAYER];			//順位の位置を保存
	D3DXVECTOR3 m_PlayerNumPos[MAX_PLAYER];		//プレイヤーナンバーの位置を保存
	D3DXVECTOR3 m_PlayerIconPos[MAX_PLAYER];	//アイコンの位置を保存
	D3DXVECTOR2 m_RankIconSize[MAX_PLAYER];		//順位のサイズを保存(X:幅,Y:高さ)
	D3DXVECTOR2 m_PlayerNumSize[MAX_PLAYER];	//プレイヤーナンバーのサイズを保存(X:幅,Y:高さ)
	D3DXVECTOR2 m_PlayerIconSize[MAX_PLAYER];	//プレイヤーナンバーのサイズを保存(X:幅,Y:高さ)

};
#endif