//=============================================================================
//
// チュートリアル処理 [tutorial.cpp]
// Author : 目黒 未来也
//
//=============================================================================
#include "tutorial.h"
#include "game.h"
#include "manager.h"
#include "light.h"
#include "scene3D.h"
#include "sceneX.h"
#include "meshField.h"
#include "game.h"
#include "debugProc.h"
#include "scene.h"
#include "fade.h"
#include "input.h"
#include "InputKeyboard.h"
#include "CameraManager.h"
#include "word_manager.h"
#include "word.h"
#include "tube.h"
#include "time.h"
#include "PlayerNumSelect.h"
#include "object.h"
#include "point.h"
#include "SetWord.h"
#include"StageSelect.h"

#include "PlayerNumSelect.h"

#include "player.h"
#include "charactor.h"
#include "SetObject.h"
#include "loadText.h"
#include "wall.h"

#include "result.h"
#include "effect.h"

//============================================================================
//	マクロ定義
//============================================================================
#define SIZE_X (SCREEN_WIDTH)
#define SIZE_Y (SCREEN_HEIGHT)
#define COLISIONSIZE (20.0f)
#define TIME_INI		(60)

//--------------------------
// 機械ステージ
//--------------------------
#define MACHINE_STAGE_00	("data\\TEXT\\チュートリアルステージ\\Machine_Stage_0.txt")
#define MACHINE_STAGE_01	("data\\TEXT\\チュートリアルステージ\\Machine_Stage_1.txt")
#define MACHINE_STAGE_02	("data\\TEXT\\チュートリアルステージ\\Machine_Stage_2.txt")
#define FILE_NAME00		("data\\TEXT\\チュートリアルステージ\\文字出現位置\\Machine_Word_0.txt")
#define FILE_NAME01		("data\\TEXT\\チュートリアルステージ\\文字出現位置\\Machine_Word_1.txt")
#define FILE_NAME02		("data\\TEXT\\チュートリアルステージ\\文字出現位置\\Machine_Word_2.txt")

//============================================================================
//静的メンバ変数宣言
//============================================================================
CPlayer *CTutorial::m_pPlayer[MAX_PLAYER] = {};
CTube *CTutorial::m_apTube[MAX_PLAYER] = {};
CWall *CTutorial::m_pWall = {};
CMeshField *CTutorial::m_pMeshField = NULL;
CPlayer::PLAYER_TYPE CTutorial::m_type[MAX_PLAYER] = {};
CSetWord *CTutorial::m_pWordCreate = NULL;
int CTutorial::m_nNumStage = NULL;
CPoint *CTutorial::m_pPoint[MAX_PLAYER] = {};

//=============================================================================
//	コンストラクタ
//=============================================================================
CTutorial::CTutorial()
{

}

//=============================================================================
//デストラクタ
//=============================================================================
CTutorial::~CTutorial()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
void CTutorial::Init(void)
{

	//	エフェクトのテキストの名前の読み込み
	CEffect::LoadNameEffect();			//	エフェクトのテキスト読み込み
	CEffect::LoadDataEffect();			//	エフェクトのデータ読み込み
	CEffect::Load();					//	エフェクトの読み込み
	//カメラのクリエイト
	CCameraManager *pCameraManager = CManager::GetCameraManager();
	CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();
	CameraSetting((int)NumPlayer);

	m_nChangeNum = 0;
	m_nNumStage = 0;

	//	チュートリアル
	m_pcStageName[0][0] = { MACHINE_STAGE_00 };
	m_pcStageName[0][1] = { MACHINE_STAGE_01 };
	m_pcStageName[0][2] = { MACHINE_STAGE_02 };
	m_pcStageNameWord[0][0] = { FILE_NAME00 };
	m_pcStageNameWord[0][1] = { FILE_NAME01 };
	m_pcStageNameWord[0][2] = { FILE_NAME02 };

	if (m_pMeshField == NULL)
	{
		m_pMeshField = m_pMeshField->Create(D3DXVECTOR3(0.0f, 0.0f, 2000.0f),20,60,40);
	}

	if (m_pWall == NULL)
	{
		//	チュートリアル
		m_pWall->Create(D3DXVECTOR3(0.0f, -1.5f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(1200.0f, 600.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 0, 11);
		//	チュートリアル
		m_pWall->Create(D3DXVECTOR3(0.0f, -1.5f, 1200.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(1200.0f, 600.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 0, 11);
		//	チュートリアル
		m_pWall->Create(D3DXVECTOR3(0.0f, -1.5f, 2200.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(1200.0f, 600.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 0, 11);
		//	相手に当てよう
		m_pWall->Create(D3DXVECTOR3(-280.0f, 0.5f, 740.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(140.0f, 160.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 0, 8);
		m_pWall->Create(D3DXVECTOR3(280.0f, 0.5f, 740.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(140.0f, 160.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 0, 8);
		//	相手に当てよう表記文字
		m_pWall->Create(D3DXVECTOR3(-280.0f, 12.0f, 860.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(80.0f, 20.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 14);
		m_pWall->Create(D3DXVECTOR3(280.0f, 12.0f, 860.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(80.0f, 20.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 14);
		//	相手に当てようモデル表記
		m_pWall->Create(D3DXVECTOR3(-267.0f, 14.0f, 712.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(28.0f, 28.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 15);
		m_pWall->Create(D3DXVECTOR3(275.0f, 14.0f,712.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(28.0f, 28.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 15);
		//	コトバを作って
		m_pWall->Create(D3DXVECTOR3(-280.0f, 0.5f, 420.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(140.0f, 160.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 0, 3);
		m_pWall->Create(D3DXVECTOR3(280.0f, 0.5f, 420.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(140.0f, 160.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 0, 3);
		//	コトバを作って表記文字
		m_pWall->Create(D3DXVECTOR3(-280.0f, 12.0f, 540.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(80.0f, 20.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 13);
		m_pWall->Create(D3DXVECTOR3(280.0f, 12.0f, 540.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(80.0f, 20.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 13);
		//	コトバを作ってモデル表記
		m_pWall->Create(D3DXVECTOR3(-276.0f, 17.0f, 410.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(45.0f, 45.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 15);
		m_pWall->Create(D3DXVECTOR3(280.0f, 17.0f, 410.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(45.0f, 45.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 15);
		//	文字を拾って
		m_pWall->Create(D3DXVECTOR3(-280.0f, 0.5f, 100.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(140.0f, 160.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 0, 2);
		m_pWall->Create(D3DXVECTOR3(280.0f, 0.5f, 100.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(140.0f, 160.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 0, 2);
		//	文字を拾って表記文字
		m_pWall->Create(D3DXVECTOR3(-280.0f, 12.0f, 220.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(80.0f, 20.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 12);
		m_pWall->Create(D3DXVECTOR3(280.0f, 12.0f, 220.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(80.0f, 20.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 12);
		//	文字を撃った
		m_pWall->Create(D3DXVECTOR3(250.0f, 19.0f, 1150.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(120.0f, 30.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 17);
		m_pWall->Create(D3DXVECTOR3(-250.0f, 19.0f, 1150.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(120.0f, 30.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 17);
		//	モデル表記
		m_pWall->Create(D3DXVECTOR3(-223.0f, 7.0, 1134.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(18.0f, 18.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 15);
		m_pWall->Create(D3DXVECTOR3(280.0f, 7.0f, 1134.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(18.0f, 18.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 15);
		//	4人で戦います
		m_pWall->Create(D3DXVECTOR3(240.0f, 19.0f, 1000.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(120.0f, 30.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 16);
		m_pWall->Create(D3DXVECTOR3(-240.0f, 19.0f, 1000.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(120.0f, 30.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 16);
		//	ポイントUP
		m_pWall->Create(D3DXVECTOR3(240.0f, 19.0f, 1300.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(120.0f, 30.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 18);
		m_pWall->Create(D3DXVECTOR3(-240.0f, 19.0f, 1300.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(120.0f, 30.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 18);
		//	ゲームルール
		m_pWall->Create(D3DXVECTOR3(0.0f, 0.2f, 900.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(120.0f, 30.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 0, 19);
		//	模擬戦へ
		m_pWall->Create(D3DXVECTOR3(0.0f, 0.2f, 1550), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 50.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 0, 21);
		//	勝利条件
		m_pWall->Create(D3DXVECTOR3(0.0f, 75.0f, 1300.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(140.0f, 40.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 20);

		//	文字一覧
		m_pWall->Create(D3DXVECTOR3(0.0f, 15.0f, 2350.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(270.0f, 30.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 22);
		m_pWall->Create(D3DXVECTOR3(0.0f, 15.0f, 2280.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(270.0f, 30.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 22);
		m_pWall->Create(D3DXVECTOR3(0.0f, 15.0f, 2210.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(270.0f, 30.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 22);
		m_pWall->Create(D3DXVECTOR3(0.0f, 15.0f, 2140.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(270.0f, 30.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 22);
		m_pWall->Create(D3DXVECTOR3(0.0f, 15.0f, 2070.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(270.0f, 30.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 22);
		m_pWall->Create(D3DXVECTOR3(0.0f, 15.0f, 2000.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(270.0f, 30.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 22);
		m_pWall->Create(D3DXVECTOR3(0.0f, 15.0f, 1930.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(270.0f, 30.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 22);
		m_pWall->Create(D3DXVECTOR3(0.0f, 15.0f, 1860.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(270.0f, 30.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 22);
		m_pWall->Create(D3DXVECTOR3(0.0f, 15.0f, 1790.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(270.0f, 30.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 22);
		m_pWall->Create(D3DXVECTOR3(0.0f, 15.0f, 1720.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(270.0f, 30.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 22);
		m_pWall->Create(D3DXVECTOR3(0.0f, 15.0f, 1650.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(270.0f, 30.0f, 0.0f),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f), 1, 22);

	}

	// プレイヤーの生成
	PlayerSetting((int)NumPlayer);
	// 文字のリソース読み込み
	CLoadText::LoadFile();

	// 文字の可視化UI(2D)の生成
	TubeSetting((int)NumPlayer);

	m_pWordCreate = NULL;
	if (m_pWordCreate == NULL) { m_pWordCreate = CSetWord::Create(); }
	SetCreateWord();

	CSetObject::Create();
	SetStage(m_nNumStage, m_nChangeNum);		// ステージ生成
												//カウントダウン生成
	for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
	{
		m_pScene2D[nCnt] = NULL;
	}

	if (NumPlayer == CPlayerSelect::SELECTPLAYER_1P)
	{
		m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(1160.0f,479.0f, 0), "TOP000");
		m_pScene2D[0]->SetWidthHeight(200.0f, 57.0f);
		m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(1160.0f, 547.0f, 0), "TOP003");
		m_pScene2D[1]->SetWidthHeight(200.0f, 57.0f);
		m_pScene2D[2] = CScene2D::Create(D3DXVECTOR3(1160.0f, 617.0f, 0), "TOP002");
		m_pScene2D[2]->SetWidthHeight(200.0f, 57.0f);
		m_pScene2D[3] = CScene2D::Create(D3DXVECTOR3(1140.0f, 685.0f, 0), "TOP001");
		m_pScene2D[3]->SetWidthHeight(230.0f, 57.0f);

		m_pScene2D[16] = CScene2D::Create(D3DXVECTOR3(153.0f, 50.0f, 0), "TUTOLOGO");
		m_pScene2D[16]->SetWidthHeight(280.0f, 100.0f);
		m_pScene2D[17] = CScene2D::Create(D3DXVECTOR3(1150.0f, 35.0f, 0), "TUTOSTART");
		m_pScene2D[17]->SetWidthHeight(200.0f, 50.0);
	}
	else if (NumPlayer == CPlayerSelect::SELECTPLAYER_2P)
	{
		// 1P 操作UI
		m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(1047.0f, 207.0f, 0), "TOP000");
		m_pScene2D[0]->SetWidthHeight(140.0f, 35.0f);
		m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(1047.0f, 248.0f, 0), "TOP003");
		m_pScene2D[1]->SetWidthHeight(140.0f, 35.0f);
		m_pScene2D[2] = CScene2D::Create(D3DXVECTOR3(1047.0f, 290.0f, 0), "TOP002");
		m_pScene2D[2]->SetWidthHeight(140.0f, 35.0f);
		m_pScene2D[3] = CScene2D::Create(D3DXVECTOR3(1045.0f, 332.0f, 0), "TOP001");
		m_pScene2D[3]->SetWidthHeight(160.0f, 36.0f);
		// 2P 操作UI
		m_pScene2D[4] = CScene2D::Create(D3DXVECTOR3(1047.0f, 572.0f, 0), "TOP000");
		m_pScene2D[4]->SetWidthHeight(140.0f, 35.0f);
		m_pScene2D[5] = CScene2D::Create(D3DXVECTOR3(1047.0f, 613.0f, 0), "TOP003");
		m_pScene2D[5]->SetWidthHeight(140.0f, 35.0f);
		m_pScene2D[6] = CScene2D::Create(D3DXVECTOR3(1047.0f, 654.0f, 0), "TOP002");
		m_pScene2D[6]->SetWidthHeight(140.0f, 35.0f);
		m_pScene2D[7] = CScene2D::Create(D3DXVECTOR3(1045.0f, 696.0f, 0), "TOP001");
		m_pScene2D[7]->SetWidthHeight(160.0f, 36.0f);

		m_pScene2D[16] = CScene2D::Create(D3DXVECTOR3(250.0f, 30.0f, 0), "TUTOLOGO");
		m_pScene2D[16]->SetWidthHeight(170.0f, 50.0);
		m_pScene2D[17] = CScene2D::Create(D3DXVECTOR3(1025.0f, 30.0f, 0), "TUTOSTART");
		m_pScene2D[17]->SetWidthHeight(170.0f, 40.0);
		m_pScene2D[18] = CScene2D::Create(D3DXVECTOR3(250.0f, 390.0f, 0), "TUTOLOGO");
		m_pScene2D[18]->SetWidthHeight(170.0f, 50.0);
		m_pScene2D[19] = CScene2D::Create(D3DXVECTOR3(1025.0f, 390.0f, 0), "TUTOSTART");
		m_pScene2D[19]->SetWidthHeight(170.0f, 40.0);
	}
	else if (NumPlayer == CPlayerSelect::SELECTPLAYER_3P )
	{
		// 1P 操作UI
		m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(575.0f, 230.0f, 0), "TOP000");
		m_pScene2D[0]->SetWidthHeight(90.0f, 25.0f);
		m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(575.0f, 265.0f, 0), "TOP003");
		m_pScene2D[1]->SetWidthHeight(90.0f, 25.0f);
		m_pScene2D[2] = CScene2D::Create(D3DXVECTOR3(575.0f, 300.0f, 0), "TOP002");
		m_pScene2D[2]->SetWidthHeight(90.0f, 25.0f);
		m_pScene2D[3] = CScene2D::Create(D3DXVECTOR3(567.0f, 335.0f, 0), "TOP001");
		m_pScene2D[3]->SetWidthHeight(110.0f, 26.0f);
		// 3P 操作UI
		m_pScene2D[4] = CScene2D::Create(D3DXVECTOR3(575.0f, 594.0f, 0), "TOP000");
		m_pScene2D[4]->SetWidthHeight(90.0f, 25.0f);
		m_pScene2D[5] = CScene2D::Create(D3DXVECTOR3(575.0f, 629.0f, 0), "TOP003");
		m_pScene2D[5]->SetWidthHeight(90.0f, 25.0f);
		m_pScene2D[6] = CScene2D::Create(D3DXVECTOR3(575.0f, 664.0f, 0), "TOP002");
		m_pScene2D[6]->SetWidthHeight(90.0f, 25.0f);
		m_pScene2D[7] = CScene2D::Create(D3DXVECTOR3(567.0f, 699.0f, 0), "TOP001");
		m_pScene2D[7]->SetWidthHeight(110.0f, 26.0f);
		// 2P 操作UI
		m_pScene2D[8] = CScene2D::Create(D3DXVECTOR3(1219.0f, 230.0f, 0), "TOP000");
		m_pScene2D[8]->SetWidthHeight(90.0f, 25.0f);
		m_pScene2D[9] = CScene2D::Create(D3DXVECTOR3(1219.0f, 265.0f, 0), "TOP003");
		m_pScene2D[9]->SetWidthHeight(90.0f, 25.0f);
		m_pScene2D[10] = CScene2D::Create(D3DXVECTOR3(1219.0f, 300.0f, 0), "TOP002");
		m_pScene2D[10]->SetWidthHeight(90.0f, 25.0f);
		m_pScene2D[11] = CScene2D::Create(D3DXVECTOR3(1214.0f, 335.0f, 0), "TOP001");
		m_pScene2D[11]->SetWidthHeight(110.0f, 26.0f);

		m_pScene2D[16] = CScene2D::Create(D3DXVECTOR3(90.0f, 25.0f, 0), "TUTOLOGO");
		m_pScene2D[16]->SetWidthHeight(140.0f, 40.0);
		m_pScene2D[17] = CScene2D::Create(D3DXVECTOR3(540.0f, 28.0f, 0), "TUTOSTART");
		m_pScene2D[17]->SetWidthHeight(140.0f, 40.0);
		m_pScene2D[18] = CScene2D::Create(D3DXVECTOR3(730.0f, 25.0f, 0), "TUTOLOGO");
		m_pScene2D[18]->SetWidthHeight(140.0f, 40.0);
		m_pScene2D[19] = CScene2D::Create(D3DXVECTOR3(1180.0f, 28.0f, 0), "TUTOSTART");
		m_pScene2D[19]->SetWidthHeight(140.0f, 40.0);
		m_pScene2D[20] = CScene2D::Create(D3DXVECTOR3(90.0f, 385.0f, 0), "TUTOLOGO");
		m_pScene2D[20]->SetWidthHeight(140.0f, 40.0);
		m_pScene2D[21] = CScene2D::Create(D3DXVECTOR3(540.0f,393.0f, 0), "TUTOSTART");
		m_pScene2D[21]->SetWidthHeight(140.0f, 40.0);
	}
	else if (NumPlayer == CPlayerSelect::SELECTPLAYER_4P)
	{
		// 1P 操作UI
		m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(575.0f, 230.0f, 0), "TOP000");
		m_pScene2D[0]->SetWidthHeight(90.0f, 25.0f);
		m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(575.0f, 265.0f, 0), "TOP003");
		m_pScene2D[1]->SetWidthHeight(90.0f, 25.0f);
		m_pScene2D[2] = CScene2D::Create(D3DXVECTOR3(575.0f, 300.0f, 0), "TOP002");
		m_pScene2D[2]->SetWidthHeight(90.0f, 25.0f);
		m_pScene2D[3] = CScene2D::Create(D3DXVECTOR3(567.0f, 335.0f, 0), "TOP001");
		m_pScene2D[3]->SetWidthHeight(110.0f, 26.0f);
		// 3P 操作UI
		m_pScene2D[4] = CScene2D::Create(D3DXVECTOR3(575.0f, 594.0f, 0), "TOP000");
		m_pScene2D[4]->SetWidthHeight(90.0f, 25.0f);
		m_pScene2D[5] = CScene2D::Create(D3DXVECTOR3(575.0f, 629.0f, 0), "TOP003");
		m_pScene2D[5]->SetWidthHeight(90.0f, 25.0f);
		m_pScene2D[6] = CScene2D::Create(D3DXVECTOR3(575.0f, 664.0f, 0), "TOP002");
		m_pScene2D[6]->SetWidthHeight(90.0f, 25.0f);
		m_pScene2D[7] = CScene2D::Create(D3DXVECTOR3(567.0f,699.0f, 0), "TOP001");
		m_pScene2D[7]->SetWidthHeight(110.0f, 26.0f);
		// 2P 操作UI
		m_pScene2D[8] = CScene2D::Create(D3DXVECTOR3(1219.0f, 230.0f, 0), "TOP000");
		m_pScene2D[8]->SetWidthHeight(90.0f, 25.0f);
		m_pScene2D[9] = CScene2D::Create(D3DXVECTOR3(1219.0f, 265.0f, 0), "TOP003");
		m_pScene2D[9]->SetWidthHeight(90.0f, 25.0f);
		m_pScene2D[10] = CScene2D::Create(D3DXVECTOR3(1219.0f, 300.0f, 0), "TOP002");
		m_pScene2D[10]->SetWidthHeight(90.0f, 25.0f);
		m_pScene2D[11] = CScene2D::Create(D3DXVECTOR3(1214.0f, 335.0f, 0), "TOP001");
		m_pScene2D[11]->SetWidthHeight(110.0f, 26.0f);
		// 4P 操作UI
		m_pScene2D[12] = CScene2D::Create(D3DXVECTOR3(1219.0f, 594.0f, 0), "TOP000");
		m_pScene2D[12]->SetWidthHeight(90.0f, 25.0f);
		m_pScene2D[13] = CScene2D::Create(D3DXVECTOR3(1219.0f, 629.0f, 0), "TOP003");
		m_pScene2D[13]->SetWidthHeight(90.0f, 25.0f);
		m_pScene2D[14] = CScene2D::Create(D3DXVECTOR3(1219.0f, 664.0f, 0), "TOP002");
		m_pScene2D[14]->SetWidthHeight(90.0f, 25.0f);
		m_pScene2D[15] = CScene2D::Create(D3DXVECTOR3(1214.0f, 699.0f, 0), "TOP001");
		m_pScene2D[15]->SetWidthHeight(110.0f, 26.0f);

		m_pScene2D[16] = CScene2D::Create(D3DXVECTOR3(90.0f, 25.0f, 0), "TUTOLOGO");
		m_pScene2D[16]->SetWidthHeight(140.0f, 40.0);
		m_pScene2D[17] = CScene2D::Create(D3DXVECTOR3(540.0f, 28.0f, 0), "TUTOSTART");
		m_pScene2D[17]->SetWidthHeight(140.0f, 40.0);
		m_pScene2D[18] = CScene2D::Create(D3DXVECTOR3(730.0f, 25.0f, 0), "TUTOLOGO");
		m_pScene2D[18]->SetWidthHeight(140.0f, 40.0);
		m_pScene2D[19] = CScene2D::Create(D3DXVECTOR3(1180.0f, 28.0f, 0), "TUTOSTART");
		m_pScene2D[19]->SetWidthHeight(140.0f, 40.0);
		m_pScene2D[20] = CScene2D::Create(D3DXVECTOR3(90.0f, 385.0f, 0), "TUTOLOGO");
		m_pScene2D[20]->SetWidthHeight(140.0f, 40.0);
		m_pScene2D[21] = CScene2D::Create(D3DXVECTOR3(540.0f, 393.0f, 0), "TUTOSTART");
		m_pScene2D[21]->SetWidthHeight(140.0f, 40.0);
		m_pScene2D[22] = CScene2D::Create(D3DXVECTOR3(730.0f, 385.0f, 0), "TUTOLOGO");
		m_pScene2D[22]->SetWidthHeight(140.0f, 40.0);
		m_pScene2D[23] = CScene2D::Create(D3DXVECTOR3(1180.0f, 393.0f, 0), "TUTOSTART");
		m_pScene2D[23]->SetWidthHeight(140.0f, 40.0);
	}


}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CTutorial::Uninit(void)
{
	//メッシュフィールドの破棄
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Uninit();
		m_pMeshField = NULL;
	}

	CEffect::Unload();			//	エフェクトの開放

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (m_pPlayer[nCntPlayer] != NULL)
		{	// プレイヤーの破棄
			m_pPlayer[nCntPlayer]->Uninit();
			m_pPlayer[nCntPlayer] = NULL;
		}
	}
	for (int nCntTube = 0; nCntTube < MAX_PLAYER; nCntTube++)
	{
		if (m_apTube[nCntTube] != NULL)
		{	// 文字の可視化UI(2D)の破棄
			m_apTube[nCntTube]->Uninit();
			m_apTube[nCntTube] = NULL;
		}
	}

	for (int nCntPoint = 0; nCntPoint < MAX_PLAYER; nCntPoint++)
	{
		if (m_pPoint[nCntPoint] != NULL)
		{	// ポイントの破棄
			m_pPoint[nCntPoint]->Uninit();
			m_pPoint[nCntPoint] = NULL;
		}
	}
	CEffect::Unload();			//	エフェクトの開放

	if (m_pWordCreate != NULL)
	{
		m_pWordCreate->Uninit();
		m_pWordCreate = NULL;
	}

	for (int nCnt = 0; nCnt < UI_MAX; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{
			m_pScene2D[nCnt]->Uninit();
			m_pScene2D[nCnt] = NULL;
		}
	}


	//不要なカメラを削除
	CCameraManager *pCameraManager = CManager::GetCameraManager();
	if (pCameraManager != NULL)
	{
		pCameraManager->DeleteCamera("1P_CAMERA");
		pCameraManager->DeleteCamera("2P_CAMERA");
		pCameraManager->DeleteCamera("3P_CAMERA");
		pCameraManager->DeleteCamera("4P_CAMERA");
		pCameraManager->DeleteCamera("TOPVIEW_CAMERA");
	}
	//全ての終了処理
	CScene::ReleseAll();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CTutorial::Update(void)
{
	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();

	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//カメラ操作（テスト）
	CCameraManager *pCameraManager = CManager::GetCameraManager();
	CCamera* pCam = pCameraManager->GetCamera("TOPVIEW_CAMERA");
	if (pCam != NULL)
	{
		pCam->SetRotation(pCam->GetRotation() + D3DXVECTOR3(0.0f, 0.001f, 0.0f));
	}

	//任意のキーENTER
	if (CCommand::GetCommand("PAUSE"))
	{
		pFade->SetFade(pManager->MODE_CHARASELECT, pFade->FADE_OUT);
	}

	if (pInputKeyboard->GetTrigger(DIK_BACKSPACE) == true)
	{
		CEffect::Create(D3DXVECTOR3(0.0f, 30.0f, 0.0f), 4, 4);
	}


#ifdef _DEBUG
	CDebugProc::Print("c", "チュートリアル");
#endif
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CTutorial::Draw(void)
{

}
//=============================================================================
// カメラセット処理
//=============================================================================
void CTutorial::CameraSetting(int nNumPlayer)
{
	//カメラのクリエイト
	CCameraManager *pCameraManager = CManager::GetCameraManager();
	if (pCameraManager != NULL)
	{
		switch (nNumPlayer)
		{
		case CPlayerSelect::SELECTPLAYER_1P:
			pCameraManager->CreateCamera("1P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, CAMERA_POSR, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_1P_PLAY);
			pCameraManager->SetCameraViewPort("1P_CAMERA", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			break;

		case CPlayerSelect::SELECTPLAYER_2P:
			pCameraManager->CreateCamera("1P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, CAMERA_POSR, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_2P_PLAY);
			pCameraManager->SetCameraViewPort("1P_CAMERA", 140, 0, 1000, 355);
			pCameraManager->CreateCamera("2P_CAMERA", CCamera::TYPE_TPS,D3DXVECTOR3(0.0f, CAMERA_POSR, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_2P_PLAY);
			pCameraManager->SetCameraViewPort("2P_CAMERA", 140, 365, 1000, 355);
			break;

		case CPlayerSelect::SELECTPLAYER_3P:
			pCameraManager->CreateCamera("1P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, CAMERA_POSR, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("1P_CAMERA", 0, 0, 635, 355);

			pCameraManager->CreateCamera("2P_CAMERA", CCamera::TYPE_TPS,D3DXVECTOR3(0.0f, CAMERA_POSR, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("2P_CAMERA", 645, 0, 635, 355);

			pCameraManager->CreateCamera("3P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, CAMERA_POSR, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);

			pCameraManager->SetCameraViewPort("3P_CAMERA", 0, 365, 635, 355);

			pCameraManager->CreateCamera("TOPVIEW_CAMERA", CCamera::TYPE_TOPVIEW,
				D3DXVECTOR3(0.0f, -100.0f, 0.0f), D3DXVECTOR3(-1.0f, D3DX_PI * -0.5f, 0.0f), CAMERA_LENGTH_TOPVIEW_PLAY);
			pCameraManager->SetCameraViewPort("TOPVIEW_CAMERA", 645, 365, 635, 355);
			break;

		case CPlayerSelect::SELECTPLAYER_4P:
			pCameraManager->CreateCamera("1P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, CAMERA_POSR, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("1P_CAMERA", 0, 0, 635, 355);

			pCameraManager->CreateCamera("2P_CAMERA", CCamera::TYPE_TPS,D3DXVECTOR3(0.0f, CAMERA_POSR, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("2P_CAMERA", 645, 0, 635, 355);

			pCameraManager->CreateCamera("3P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, CAMERA_POSR, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("3P_CAMERA", 0, 365, 635, 355);

			pCameraManager->CreateCamera("4P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, CAMERA_POSR, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("4P_CAMERA", 645, 365, 635, 355);
			break;

		default:
			pCameraManager->CreateCamera("1P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, CAMERA_POSR, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("1P_CAMERA", 0, 0, 635, 355);

			pCameraManager->CreateCamera("2P_CAMERA", CCamera::TYPE_TPS,D3DXVECTOR3(0.0f, CAMERA_POSR, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("2P_CAMERA", 645, 0, 635, 355);

			pCameraManager->CreateCamera("3P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, CAMERA_POSR, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("3P_CAMERA", 0, 365, 635, 355);

			pCameraManager->CreateCamera("4P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, CAMERA_POSR, 0.0f), D3DXVECTOR3(CAMERA_ROTX, 0.0f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("4P_CAMERA", 645, 365, 635, 355);
			break;
		}
	}
}

//=============================================================================
// 人数に応じてプレイヤー生成の処理
//=============================================================================
void CTutorial::PlayerSetting(int nNum)
{
	CCameraManager *pCameraManager = CManager::GetCameraManager();

	if (nNum == 1 || nNum == 2 || nNum == 3 || nNum == 4)
	{
		// 人数分を生成
		for (int nCntPlayer = 0; nCntPlayer < nNum; nCntPlayer++)
		{
			if (m_pPlayer[nCntPlayer] == NULL)
			{
				m_pPlayer[nCntPlayer] = CPlayer::Create();
			}
		}
		for (int nCntPlayer = 0; nCntPlayer < 4; nCntPlayer++)
		{
			if (m_pPlayer[nCntPlayer] == NULL)
			{
				//m_pPlayer[nCntPlayer] = CPlayer::Create();
			}
		}
		if (m_pPlayer[0] != NULL)
		{
			m_type[0] = CPlayer::TYPE_REACH;
			m_pPlayer[0]->Set(D3DXVECTOR3(-150, 0.0f, -150), CCharaBase::MOVETYPE_PLAYER_INPUT, 0, m_type[0], D3DXVECTOR3(0.0f, 1.57f, 0.0f));
			m_pPlayer[0]->SetCameraName("1P_CAMERA");
			pCameraManager->SetCameraHomingChara("1P_CAMERA", (C3DCharactor*)m_pPlayer[0]->GetCharaMover());
		}

		if (m_pPlayer[1] != NULL)
		{
			if (nNum > 1)
			{
				m_pPlayer[1]->Set(D3DXVECTOR3(PLAYER_INITPOSX+120, 0.0f, PLAYER_INITPOSZ), CCharaBase::MOVETYPE_PLAYER_INPUT, 1, m_type[1], D3DXVECTOR3(0.0f, 1.57f, 0.0f));
			}
			else
			{
				m_type[1] = (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_MAX);
				m_pPlayer[1]->Set(D3DXVECTOR3(PLAYER_INITPOSX + 120, 0.0f, PLAYER_INITPOSZ), CCharaBase::MOVETYPE_NPC_AI, 1, m_type[1], D3DXVECTOR3(0.0f, 1.57f, 0.0f));
			}
			m_pPlayer[1]->SetCameraName("2P_CAMERA");
			pCameraManager->SetCameraHomingChara("2P_CAMERA", (C3DCharactor*)m_pPlayer[1]->GetCharaMover());
		}

		if (m_pPlayer[2] != NULL)
		{
			if (nNum > 2)
			{
				m_pPlayer[2]->Set(D3DXVECTOR3(PLAYER_INITPOSX + 240, 0.0f, PLAYER_INITPOSZ), CCharaBase::MOVETYPE_PLAYER_INPUT, 2, m_type[2], D3DXVECTOR3(0.0f, 1.57f, 0.0f));
			}
			else
			{
				m_type[2] = (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_MAX);
				m_pPlayer[2]->Set(D3DXVECTOR3(PLAYER_INITPOSX + 240, 0.0f, 0.0f), CCharaBase::MOVETYPE_NPC_AI, 2, m_type[2], D3DXVECTOR3(0.0f, 1.57f, 0.0f));
			}
			m_pPlayer[2]->SetCameraName("3P_CAMERA");
			pCameraManager->SetCameraHomingChara("3P_CAMERA", (C3DCharactor*)m_pPlayer[2]->GetCharaMover());
		}

		if (m_pPlayer[3] != NULL)
		{
			if (nNum > 3)
			{
				m_pPlayer[3]->Set(D3DXVECTOR3(PLAYER_INITPOSX + 360, 0.0f, PLAYER_INITPOSZ), CCharaBase::MOVETYPE_PLAYER_INPUT, 3, m_type[3], D3DXVECTOR3(0.0f, 1.57f, 0.0f));
			}
			else
			{
				m_type[3] = (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_MAX);
				m_pPlayer[3]->Set(D3DXVECTOR3(PLAYER_INITPOSX + 360, 0.0f, 0.0f), CCharaBase::MOVETYPE_NPC_AI, 3, m_type[3], D3DXVECTOR3(0.0f, 1.57f, 0.0f));
			}
			m_pPlayer[3]->SetCameraName("4P_CAMERA");
			pCameraManager->SetCameraHomingChara("4P_CAMERA", (C3DCharactor*)m_pPlayer[3]->GetCharaMover());
		}
		//#endif
	}
	else
	{
		// 人数分を生成
		for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
		{
			if (m_pPlayer[nCntPlayer] == NULL)
			{
				m_pPlayer[nCntPlayer] = CPlayer::Create();
			}
		}

		if (m_pPlayer[0] != NULL)
		{
			m_pPlayer[0]->Set(D3DXVECTOR3(PLAYER_INITPOSX, 0.0f, PLAYER_INITPOSZ), CCharaBase::MOVETYPE_PLAYER_INPUT, 0, (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_MAX), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_pPlayer[0]->SetCameraName("1P_CAMERA");
			pCameraManager->SetCameraHomingChara("1P_CAMERA", (C3DCharactor*)m_pPlayer[0]->GetCharaMover());
		}

		if (m_pPlayer[1] != NULL)
		{
			m_pPlayer[1]->Set(D3DXVECTOR3(PLAYER_INITPOSX+50, 0.0f, PLAYER_INITPOSZ), CCharaBase::MOVETYPE_PLAYER_INPUT, 1, (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_MAX), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_pPlayer[1]->SetCameraName("2P_CAMERA");
			pCameraManager->SetCameraHomingChara("2P_CAMERA", (C3DCharactor*)m_pPlayer[1]->GetCharaMover());
		}

		if (m_pPlayer[2] != NULL)
		{
			m_pPlayer[2]->Set(D3DXVECTOR3(PLAYER_INITPOSX + 100, 0.0f, PLAYER_INITPOSZ), CCharaBase::MOVETYPE_PLAYER_INPUT, 2, (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_MAX), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_pPlayer[2]->SetCameraName("3P_CAMERA");
			pCameraManager->SetCameraHomingChara("3P_CAMERA", (C3DCharactor*)m_pPlayer[2]->GetCharaMover());
		}
		if (m_pPlayer[3] != NULL)
		{
			m_pPlayer[3]->Set(D3DXVECTOR3(PLAYER_INITPOSX + 150, 0.0f, PLAYER_INITPOSZ), CCharaBase::MOVETYPE_PLAYER_INPUT, 3, (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_MAX), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_pPlayer[3]->SetCameraName("4P_CAMERA");
			pCameraManager->SetCameraHomingChara("4P_CAMERA", (C3DCharactor*)m_pPlayer[3]->GetCharaMover());
		}
	}
}

//=============================================================================
// 人数に応じた筒の生成処理
//=============================================================================
void CTutorial::TubeSetting(int nNum)
{
	switch (nNum)
	{
	case 1:
		if (m_apTube[0] == NULL)
		{
			m_apTube[0] = CTube::Create(WORD_TUBE001_POS_1P, WORD_SIZE_001, "TUBE", 3);
			m_apTube[0]->SetID(0);
		}
		break;

	case 2:
		for (int nCntTube = 0; nCntTube < nNum; nCntTube++)
		{
			if (m_apTube[nCntTube] == NULL)
			{
				if (nCntTube == 0) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE002_POS_1P, WORD_SIZE_002, "TUBE", 3); m_apTube[0]->SetID(0); }
				if (nCntTube == 1) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE002_POS_2P, WORD_SIZE_002, "TUBE", 3); m_apTube[1]->SetID(1); }
			}
		}
		break;

	case 3:
		for (int nCntTube = 0; nCntTube < nNum; nCntTube++)
		{
			if (m_apTube[nCntTube] == NULL)
			{
				if (nCntTube == 0) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_1P, WORD_SIZE_002, "TUBE", 3); m_apTube[0]->SetID(0); }
				if (nCntTube == 1) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_2P, WORD_SIZE_002, "TUBE", 3); m_apTube[1]->SetID(1); }
				if (nCntTube == 2) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_3P, WORD_SIZE_002, "TUBE", 3); m_apTube[2]->SetID(2); }
			}
		}
		break;

	case 4:
		for (int nCntTube = 0; nCntTube < nNum; nCntTube++)
		{
			if (m_apTube[nCntTube] == NULL)
			{
				if (nCntTube == 0) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_1P, WORD_SIZE_002, "TUBE", 3); m_apTube[0]->SetID(0); }
				if (nCntTube == 1) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_2P, WORD_SIZE_002, "TUBE", 3); m_apTube[1]->SetID(1); }
				if (nCntTube == 2) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_3P, WORD_SIZE_002, "TUBE", 3); m_apTube[2]->SetID(2); }
				if (nCntTube == 3) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE004_POS_4P, WORD_SIZE_002, "TUBE", 3); m_apTube[3]->SetID(3); }
			}
		}
		break;

	default:
		for (int nCntTube = 0; nCntTube < MAX_PLAYER; nCntTube++)
		{
			if (m_apTube[nCntTube] == NULL)
			{
				if (nCntTube == 0) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_1P, WORD_SIZE_002, "TUBE", 3); m_apTube[0]->SetID(0); }
				if (nCntTube == 1) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_2P, WORD_SIZE_002, "TUBE", 3); m_apTube[1]->SetID(1); }
				if (nCntTube == 2) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_3P, WORD_SIZE_002, "TUBE", 3); m_apTube[2]->SetID(2); }
				if (nCntTube == 3) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE004_POS_4P, WORD_SIZE_002, "TUBE", 3); m_apTube[3]->SetID(3); }
			}
		}
		break;
	}
}

//=============================================================================
// ステージ生成の処理
//=============================================================================
void CTutorial::SetStage(int nNumState, int nCntState)
{
	if (nCntState < MAX_STAGE)
	{
		CSetObject::LoadFile(m_pcStageName[nNumState][nCntState]);
		m_nChangeNum = nCntState;
	}
}

//=============================================================================
// ステージ生成の処理
//=============================================================================
void CTutorial::SetCreateWord(void)
{
	if (m_pWordCreate != NULL) { m_pWordCreate->LoadFile(m_pcStageNameWord[m_nNumStage][m_nChangeNum]); }
}
//=============================================================================
// 文字2D可視化の取得処理
//=============================================================================
CTube *CTutorial::GetTube(int nNum)
{
	if (m_apTube[nNum] != NULL) { return m_apTube[nNum]; }
	return NULL;
}
//=============================================================================
// ポイントの生成処理
//=============================================================================
void CTutorial::SetPointFrame(int nNumPlayer)
{
	if (nNumPlayer <= MAX_PLAYER && nNumPlayer >= 0)
	{	// 指定人数の範囲内
		for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
		{
			if (m_pPoint[nCount] == NULL)
			{
				if (nNumPlayer > nCount)
				{	// プレイ人数分ポイント生成
					m_pPoint[nCount] = CPoint::Create(nCount, nNumPlayer, CPoint::TYPR_PLAYER);
				}
				else
				{	// CPUのポイント生成
					m_pPoint[nCount] = CPoint::Create(nCount, nNumPlayer, CPoint::TYPE_CPU);
				}
			}
		}
	}
}