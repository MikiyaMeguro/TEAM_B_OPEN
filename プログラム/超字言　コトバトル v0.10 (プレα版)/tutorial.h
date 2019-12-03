//=============================================================================
//
// チュートリアルの処理 [tutorial.h]
// Author : 目黒未来也
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "scene.h"
#include "scene.h"
#include "player.h"
#include "tube.h"
#include "meshField.h"
//=============================================================================
// 前方宣言
//=============================================================================
class CPlayer;
class CTube;
class CPoint;
class CSetWord;
class CWall;
class CStageSelect;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_TUTORIAL			(3)
#define CAMERA_LENGTH_1P_PLAY (250.0f)				//カメラの距離(1pプレイ用)
#define CAMERA_LENGTH_2P_PLAY (250.0f)				//カメラの距離(2pプレイ用)
#define CAMERA_LENGTH_3P4P_PLAY (200.0f)			//カメラの距離(3p4pプレイ用)
#define CAMERA_LENGTH_TOPVIEW_PLAY (650.0f)			//カメラの距離(3pプレイ時のトップビューカメラ用)

#define CAMERA_ROTX (-1.57f)		//カメラのデフォルト角度(X)

#define PLAYER_INITPOSX (200.0f)
#define PLAYER_INITPOSZ (200.0f)

#define MAX_PLAYER (4)
#define MAX_STAGE	(2)			// ステージの最大数
#define MAX_STAGECOUNT	(3)		// 各ステージの数

class CTutorial
{
public:
	CTutorial();
	~CTutorial();

	void Init(void);
	void Uninit(void);
	void Update(void);
	static CMeshField *GetMeshField(void) { return m_pMeshField; }			// 地面の取得
	void Draw(void);
	void SetStage(int nNumState, int nCntState);	// ステージの生成
	void SetCreateWord(void);
	static CPlayer *GetPlayer(int nNumPlayer = 0) { return (nNumPlayer < MAX_PLAYER && nNumPlayer >= 0) ? m_pPlayer[nNumPlayer] : m_pPlayer[0]; }		// プレイヤーの取得
	static CTube *GetTube(int nNum);		// 文字の可視化UIの取得
	static CSetWord *GetWordCreate(void) { return m_pWordCreate; }			// 文字出現の取得
	static CPoint *GetPoint(int nNum) { return m_pPoint[nNum]; }			// ポイントの取得
private:
	void CameraSetting(int nNum);		// 人数に応じたカメラ生成
	void PlayerSetting(int nNum);		// 人数に応じたプレイヤー生成
	void TubeSetting(int nNum);			// 人数に応じた筒の生成
	void SetPointFrame(int nNum);		// 人数に応じたポイントの生成
	static CPlayer *m_pPlayer[MAX_PLAYER];
	static CTube *m_apTube[MAX_PLAYER];
	static CPlayer::PLAYER_TYPE m_type[MAX_PLAYER];
	static CMeshField *m_pMeshField;
	static CWall *m_pWall;
	static CSetWord *m_pWordCreate;
	char *m_pcStageName[MAX_STAGE][MAX_STAGECOUNT];		// ステージの名前保管
	char *m_pcStageNameWord[MAX_STAGE][MAX_STAGECOUNT];	// ステージの名前保管
	int m_nChangeNum;
	static int m_nNumStage;
	static CPoint *m_pPoint[MAX_PLAYER];
};
#endif