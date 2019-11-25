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
#define CAMERA_LENGTH_1P_PLAY (100.0f)				//カメラの距離(1pプレイ用)
#define CAMERA_LENGTH_2P_PLAY (120.0f)				//カメラの距離(2pプレイ用)
#define CAMERA_LENGTH_3P4P_PLAY (140.0f)			//カメラの距離(3p4pプレイ用)
#define CAMERA_LENGTH_TOPVIEW_PLAY (140.0f)			//カメラの距離(3pプレイ時のトップビューカメラ用)

#define CAMERA_ROTX (-0.05f)		//カメラのデフォルト角度(X)

#define PLAYER_INITPOS (200.0f)
#define MAX_PLAYER (4)
#define MAX_STAGE	(3)			// ステージの最大数
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

private:
	void CameraSetting(int nNum);		// 人数に応じたカメラ生成
	void PlayerSetting(int nNum);		// 人数に応じたプレイヤー生成
	void TubeSetting(int nNum);			// 人数に応じた筒の生成
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
};
#endif