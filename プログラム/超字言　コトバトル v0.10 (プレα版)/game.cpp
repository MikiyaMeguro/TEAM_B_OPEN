//=============================================================================
//
// メイン処理 [game.cpp]
// Author :
//
//=============================================================================
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
#define CAMERA_LENGTH_1P_PLAY (100.0f)				//カメラの距離(1pプレイ用)
#define CAMERA_LENGTH_2P_PLAY (120.0f)				//カメラの距離(2pプレイ用)
#define CAMERA_LENGTH_3P4P_PLAY (140.0f)			//カメラの距離(3p4pプレイ用)
#define CAMERA_LENGTH_TOPVIEW_PLAY (750.0f)			//カメラの距離(3pプレイ時のトップビューカメラ用)

#define CAMERA_ROTX (-0.05f)		//カメラのデフォルト角度(X)

#define PLAYER_INITPOS (50.0f)		//
//--------------------------
// 機械ステージ
//--------------------------
#define MACHINE_STAGE_00	("data\\TEXT\\機械ステージ\\Machine_Stage_0.txt")
#define MACHINE_STAGE_01	("data\\TEXT\\機械ステージ\\Machine_Stage_1.txt")
#define MACHINE_STAGE_02	("data\\TEXT\\機械ステージ\\Machine_Stage_2.txt")
#define FILE_NAME00		("data\\TEXT\\機械ステージ\\文字出現位置\\Machine_Word_0.txt")
#define FILE_NAME01		("data\\TEXT\\機械ステージ\\文字出現位置\\Machine_Word_1.txt")
#define FILE_NAME02		("data\\TEXT\\機械ステージ\\文字出現位置\\Machine_Word_2.txt")

//--------------------------
// 天候ステージ
//--------------------------
#define MACHINE_STAGE_10	("data\\TEXT\\天候ステージ\\Machine_Stage_0.txt")
#define MACHINE_STAGE_11	("data\\TEXT\\天候ステージ\\Machine_Stage_1.txt")
#define MACHINE_STAGE_12	("data\\TEXT\\天候ステージ\\Machine_Stage_2.txt")
#define FILE_NAME10		("data\\TEXT\\天候ステージ\\文字出現位置\\Machine_Word_0.txt")
#define FILE_NAME11		("data\\TEXT\\天候ステージ\\文字出現位置\\Machine_Word_1.txt")
#define FILE_NAME12		("data\\TEXT\\天候ステージ\\文字出現位置\\Machine_Word_2.txt")

//============================================================================
//静的メンバ変数宣言
//============================================================================
CPlayer *CGame::m_pPlayer[MAX_PLAYER] = {};
CTube *CGame::m_apTube[MAX_PLAYER] = {};
CMeshField *CGame::m_pMeshField = NULL;
CPoint *CGame::m_pPoint[MAX_PLAYER] = {};
CSetWord *CGame::m_pWordCreate = NULL;
CWall *CGame::m_pWall = NULL;
CPlayer::PLAYER_TYPE CGame::m_type[MAX_PLAYER] = {};
int CGame::m_nNumStage = NULL;
bool CGame::m_bStageSet = false;
//=============================================================================
//	コンストラクタ
//=============================================================================
CGame::CGame()
{
}

//=============================================================================
//デストラクタ
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
void CGame::Init(void)
{
	//	エフェクトのテキストの名前の読み込み
	CEffect::LoadNameEffect();			//	エフェクトのテキスト読み込み
	CEffect::LoadDataEffect();			//	エフェクトのデータ読み込み
	CEffect::Load();					//	エフェクトの読み込み
	m_nChangeNum = 0;
	m_nNumStage = 0;
	m_bStageSet = false;

	m_nNumStage = CStageSelect::GetStageState();
	if (m_nNumStage == NULL)
	{//	ステージ選択にNULLが入った場合
		m_nNumStage = 0;
	}
	//カメラのクリエイト
	CCameraManager *pCameraManager = CManager::GetCameraManager();
	CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();
	CameraSetting((int)NumPlayer);

	//メッシュフィールド生成
	m_pMeshField = NULL;
	if (m_pMeshField == NULL)
	{
		m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	switch (m_nNumStage)
	{
	case 0:
		//	機械
		m_pcStageName[0][0] = { MACHINE_STAGE_00 };
		m_pcStageName[0][1] = { MACHINE_STAGE_01 };
		m_pcStageName[0][2] = { MACHINE_STAGE_02 };
		m_pcStageNameWord[0][0] = { FILE_NAME00 };
		m_pcStageNameWord[0][1] = { FILE_NAME01 };
		m_pcStageNameWord[0][2] = { FILE_NAME02 };
		m_pWall = NULL;
		if (m_pWall == NULL)
		{
			//	下の壁
			m_pWall = CWall::Create(D3DXVECTOR3(0.0f, -100.0f, 400.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(5.0f, 5.0f), 0, 0);
			m_pWall = CWall::Create(D3DXVECTOR3(0.0f, -100.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(5.0f, 5.0f), 0, 0);
			m_pWall = CWall::Create(D3DXVECTOR3(400.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(5.0f, 5.0f), 0, 0);
			m_pWall = CWall::Create(D3DXVECTOR3(-400.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(5.0f, 5.0f), 0, 0);
		}
		break;
	case 1:
		//	天候
		m_pcStageName[1][0] = { MACHINE_STAGE_10 };
		m_pcStageName[1][1] = { MACHINE_STAGE_11 };
		m_pcStageName[1][2] = { MACHINE_STAGE_12 };
		m_pcStageNameWord[1][0] = { FILE_NAME10 };
		m_pcStageNameWord[1][1] = { FILE_NAME11 };
		m_pcStageNameWord[1][2] = { FILE_NAME12 };
		m_pWall = NULL;
		if (m_pWall == NULL)
		{
			//	下の壁
			m_pWall = CWall::Create(D3DXVECTOR3(0.0f, -100.0f, 400.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(5.0f, 5.0f), 0, 0);
			m_pWall = CWall::Create(D3DXVECTOR3(0.0f, -100.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(5.0f, 5.0f), 0, 0);
			m_pWall = CWall::Create(D3DXVECTOR3(400.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(5.0f, 5.0f), 0, 0);
			m_pWall = CWall::Create(D3DXVECTOR3(-400.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(5.0f, 5.0f), 0, 0);
			//	噴水の壁
			m_pWall = CWall::Create(D3DXVECTOR3(0.0f, 5.0f, 100.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f), D3DXVECTOR3(100.0f, 10.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f), D3DXVECTOR2(5.0f, 2.0f), 0, 5);
			m_pWall = CWall::Create(D3DXVECTOR3(0.0f, 5.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 10.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f), D3DXVECTOR2(5.0f, 2.0f), 0, 5);
			m_pWall = CWall::Create(D3DXVECTOR3(100.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(100.0f, 10.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f), D3DXVECTOR2(5.0f, 2.0f), 0, 5);
			m_pWall = CWall::Create(D3DXVECTOR3(-100.0f, 5.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(100.0f, 10.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f), D3DXVECTOR2(5.0f, 2.0f), 0, 5);
			//	噴水の上
			m_pWall = CWall::Create(D3DXVECTOR3(0.0f, 10.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f), D3DXVECTOR2(5.0f, 5.0f), 0, 5);
			m_pWall = CWall::Create(D3DXVECTOR3(0.0f, 15.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f), D3DXVECTOR2(5.0f, 5.0f), 0, 5);
			//	噴水からの水
			m_pWall = CWall::Create(D3DXVECTOR3(200.0f, 5.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(200.0f,20.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f), D3DXVECTOR2(5.0f, 5.0f), 0, 6);
			m_pWall = CWall::Create(D3DXVECTOR3(-200.0f, 5.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(200.0f, 20.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f), D3DXVECTOR2(5.0f, 5.0f), 0, 6);
			m_pWall = CWall::Create(D3DXVECTOR3(0.0f, 5.0f, 200.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 200.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f), D3DXVECTOR2(5.0f, 5.0f), 0, 6);
			m_pWall = CWall::Create(D3DXVECTOR3(0.0f, 5.0f, -200.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 200.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f), D3DXVECTOR2(5.0f, 5.0f), 0, 6);
		}
		break;
	}

	// プレイヤーの生成
	PlayerSetting((int)NumPlayer);

	CLoadText::LoadFile();		// 文字のリソース読み込み

	// 文字の可視化UI(2D)の生成
	TubeSetting((int)NumPlayer);

	SetPointFrame((int)NumPlayer);	// ポイントの設定

	//WordCreate();				// 文字の生成
	m_pWordCreate = NULL;
	if (m_pWordCreate == NULL)
	{
		m_pWordCreate = CSetWord::Create();
	}

	CSetObject::Create();
	SetStage(m_nNumStage, m_nChangeNum);		// ステージ生成

	if (NumPlayer == CPlayerSelect::SELECTPLAYER_2P)
	{
		CTime::Create((int)NumPlayer);
		CTime::Create((int)NumPlayer);
	}
	else if (NumPlayer != CPlayerSelect::SELECTPLAYER_2P) { CTime::Create((int)NumPlayer); }

	//デバック用
	//CTime::SetTimeFlag(false);
	CCommand::RegistCommand("TIMECOUNT_STOP",CCommand::INPUTTYPE_KEYBOARD,CCommand::INPUTSTATE_TRIGGER,DIK_M);

}
//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
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

	if (m_pWordCreate != NULL)
	{
		m_pWordCreate->Uninit();
		m_pWordCreate = NULL;
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
// 更新処理
//=============================================================================
void CGame::Update(void)
{
	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();
	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	CDebugProc::Print("c", "ゲームモード");
	//任意のキーENTER
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		for (int nCntPlayer = 0; nCntPlayer < 4; nCntPlayer++)
		{
			CResult::SetRanking(nCntPlayer, m_type[nCntPlayer], m_pPoint[nCntPlayer]->GetPoint());
		}

		pFade->SetFade(pManager->MODE_RESULT, pFade->FADE_OUT);
	}
	if (pInputKeyboard->GetTrigger(DIK_BACKSPACE) == true)
	{
		pFade->SetFade(pManager->MODE_GAME, pFade->FADE_OUT);

	}
	//カメラ操作（テスト）
	CCameraManager *pCameraManager = CManager::GetCameraManager();
	CCamera* pCam = pCameraManager->GetCamera("TOPVIEW_CAMERA");
	if (pCam != NULL)
	{
		pCam->SetRotation(pCam->GetRotation() + D3DXVECTOR3(0.0f,0.001f,0.0f));
	}

	//時間停止(デバック用)
	if (CCommand::GetCommand("TIMECOUNT_STOP"))
	{
		CTime::SetTimeFlag(!(CTime::GetTimeFlag()));	//現在のフラグを反転させる
	}

	if (m_bStageSet == true)
	{//	ステージが変わるタイミングで消す
		if (m_pWall != NULL)
		{//	噴水の水
			if (m_pWall->GetType() == 5 || m_pWall->GetType() == 6)
			{//	噴水の水
				m_pWall->Uninit();
				m_pWall = NULL;
			}
		}
	}
#ifdef _DEBUG

#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void CGame::Draw(void)
{

}

//=============================================================================
// カメラセット処理
//=============================================================================
void CGame::CameraSetting(int nNumPlayer)
{
	//CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();
	////CPlayerSelect::SELECTPLAYER NumPlayer = CPlayerSelect::SELECTPLAYER_3P;
	//カメラのクリエイト
	CCameraManager *pCameraManager = CManager::GetCameraManager();
	if (pCameraManager != NULL)
	{
		switch (nNumPlayer)
		{
		case CPlayerSelect::SELECTPLAYER_1P:
			pCameraManager->CreateCamera("1P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(-0.2f, 0.0f, 0.0f), CAMERA_LENGTH_1P_PLAY);
			pCameraManager->SetCameraViewPort("1P_CAMERA", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			break;

		case CPlayerSelect::SELECTPLAYER_2P:
			pCameraManager->CreateCamera("1P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(-0.2f, 0.0f, 0.0f), CAMERA_LENGTH_2P_PLAY);
			pCameraManager->SetCameraViewPort("1P_CAMERA", 0, 0, SCREEN_WIDTH, 355);
			pCameraManager->CreateCamera("2P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(-0.2f, D3DX_PI, 0.0f), CAMERA_LENGTH_2P_PLAY);
			pCameraManager->SetCameraViewPort("2P_CAMERA", 0, 365, SCREEN_WIDTH, 355);
			break;

		case CPlayerSelect::SELECTPLAYER_3P:
			pCameraManager->CreateCamera("1P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("1P_CAMERA", 0, 0, 635, 355);

			pCameraManager->CreateCamera("2P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("2P_CAMERA", 645, 0, 635, 355);

			pCameraManager->CreateCamera("3P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("3P_CAMERA", 0, 365, 635, 355);

			pCameraManager->CreateCamera("TOPVIEW_CAMERA", CCamera::TYPE_SPECTOR,
				D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(-1.75f, D3DX_PI * -0.5f, 0.0f), CAMERA_LENGTH_TOPVIEW_PLAY);
			pCameraManager->SetCameraViewPort("TOPVIEW_CAMERA", 645, 365, 635, 355);
			break;

		case CPlayerSelect::SELECTPLAYER_4P:
			pCameraManager->CreateCamera("1P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("1P_CAMERA", 0, 0, 635, 355);

			pCameraManager->CreateCamera("2P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("2P_CAMERA", 645, 0, 635, 355);

			pCameraManager->CreateCamera("3P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("3P_CAMERA", 0, 365, 635, 355);

			pCameraManager->CreateCamera("4P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(20.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("4P_CAMERA", 645, 365, 635, 355);
			break;

		default:
			pCameraManager->CreateCamera("1P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("1P_CAMERA", 0, 0, 635, 355);

			pCameraManager->CreateCamera("2P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("2P_CAMERA", 645, 0, 635, 355);

			pCameraManager->CreateCamera("3P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("3P_CAMERA", 0, 365, 635, 355);

			pCameraManager->CreateCamera("4P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(20.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), CAMERA_LENGTH_3P4P_PLAY);
			pCameraManager->SetCameraViewPort("4P_CAMERA", 645, 365, 635, 355);
			break;
		}
	}
}

//=============================================================================
// 人数に応じてプレイヤー生成の処理
//=============================================================================
void CGame::PlayerSetting(int nNum)
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
				m_pPlayer[nCntPlayer] = CPlayer::Create();
			}
		}
		switch (m_nNumStage)
		{
		case 0:
			if (m_pPlayer[0] != NULL)
			{
				m_pPlayer[0]->Set(D3DXVECTOR3(PLAYER_INITPOS, 0.0f, PLAYER_INITPOS), CCharaBase::MOVETYPE_PLAYER_INPUT, 0, m_type[0]);
				m_pPlayer[0]->SetCameraName("1P_CAMERA");
				pCameraManager->SetCameraHomingChara("1P_CAMERA", (C3DCharactor*)m_pPlayer[0]->GetCharaMover());
			}

			if (m_pPlayer[1] != NULL)
			{
				if (nNum > 1)
				{
					m_pPlayer[1]->Set(D3DXVECTOR3(-PLAYER_INITPOS, 0.0f, PLAYER_INITPOS), CCharaBase::MOVETYPE_PLAYER_INPUT, 1, m_type[1], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				else
				{
					m_type[1] = (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM);
					m_pPlayer[1]->Set(D3DXVECTOR3(-PLAYER_INITPOS, 0.0f, PLAYER_INITPOS), CCharaBase::MOVETYPE_NPC_AI, 1, m_type[1], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				m_pPlayer[1]->SetCameraName("2P_CAMERA");
				pCameraManager->SetCameraHomingChara("2P_CAMERA", (C3DCharactor*)m_pPlayer[1]->GetCharaMover());
			}

			if (m_pPlayer[2] != NULL)
			{
				if (nNum > 2)
				{
					m_pPlayer[2]->Set(D3DXVECTOR3(PLAYER_INITPOS, 0.0f, -PLAYER_INITPOS), CCharaBase::MOVETYPE_PLAYER_INPUT, 2, m_type[2], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				else
				{
					m_type[2] = (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM);
					m_pPlayer[2]->Set(D3DXVECTOR3(PLAYER_INITPOS, 0.0f, -PLAYER_INITPOS), CCharaBase::MOVETYPE_NPC_AI, 2, m_type[2], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				m_pPlayer[2]->SetCameraName("3P_CAMERA");
				pCameraManager->SetCameraHomingChara("3P_CAMERA", (C3DCharactor*)m_pPlayer[2]->GetCharaMover());
			}

			if (m_pPlayer[3] != NULL)
			{
				if (nNum > 3)
				{
					m_pPlayer[3]->Set(D3DXVECTOR3(-PLAYER_INITPOS, 0.0f, -PLAYER_INITPOS), CCharaBase::MOVETYPE_PLAYER_INPUT, 3, m_type[3], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				else
				{
					m_type[3] = (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM);
					m_pPlayer[3]->Set(D3DXVECTOR3(-PLAYER_INITPOS, 0.0f, -PLAYER_INITPOS), CCharaBase::MOVETYPE_NPC_AI, 3, m_type[3], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				m_pPlayer[3]->SetCameraName("4P_CAMERA");
				pCameraManager->SetCameraHomingChara("4P_CAMERA", (C3DCharactor*)m_pPlayer[3]->GetCharaMover());
			}
			break;
		case 1:
			if (m_pPlayer[0] != NULL)
			{
				m_pPlayer[0]->Set(D3DXVECTOR3(200, 0.0f, 200), CCharaBase::MOVETYPE_PLAYER_INPUT, 0, m_type[0]);
				m_pPlayer[0]->SetCameraName("1P_CAMERA");
				pCameraManager->SetCameraHomingChara("1P_CAMERA", (C3DCharactor*)m_pPlayer[0]->GetCharaMover());
			}

			if (m_pPlayer[1] != NULL)
			{
				if (nNum > 1)
				{
					m_pPlayer[1]->Set(D3DXVECTOR3(-200, 0.0f, 200), CCharaBase::MOVETYPE_PLAYER_INPUT, 1, m_type[1], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				else
				{
					m_type[1] = (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM);
					m_pPlayer[1]->Set(D3DXVECTOR3(-200, 0.0f, 200), CCharaBase::MOVETYPE_NPC_AI, 1, m_type[1], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				m_pPlayer[1]->SetCameraName("2P_CAMERA");
				pCameraManager->SetCameraHomingChara("2P_CAMERA", (C3DCharactor*)m_pPlayer[1]->GetCharaMover());
			}

			if (m_pPlayer[2] != NULL)
			{
				if (nNum > 2)
				{
					m_pPlayer[2]->Set(D3DXVECTOR3(200, 0.0f, -200), CCharaBase::MOVETYPE_PLAYER_INPUT, 2, m_type[2], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				else
				{
					m_type[2] = (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM);
					m_pPlayer[2]->Set(D3DXVECTOR3(200, 0.0f, -200), CCharaBase::MOVETYPE_NPC_AI, 2, m_type[2], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				m_pPlayer[2]->SetCameraName("3P_CAMERA");
				pCameraManager->SetCameraHomingChara("3P_CAMERA", (C3DCharactor*)m_pPlayer[2]->GetCharaMover());
			}

			if (m_pPlayer[3] != NULL)
			{
				if (nNum > 3)
				{
					m_pPlayer[3]->Set(D3DXVECTOR3(-200, 0.0f, -200), CCharaBase::MOVETYPE_PLAYER_INPUT, 3, m_type[3], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				else
				{
					m_type[3] = (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM);
					m_pPlayer[3]->Set(D3DXVECTOR3(-200, 0.0f, -200), CCharaBase::MOVETYPE_NPC_AI, 3, m_type[3], D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}
				m_pPlayer[3]->SetCameraName("4P_CAMERA");
				pCameraManager->SetCameraHomingChara("4P_CAMERA", (C3DCharactor*)m_pPlayer[3]->GetCharaMover());
			}
			break;
		}
//#endif
	}
	else
	{
		switch (m_nNumStage)
		{
		case 0:
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
				m_pPlayer[0]->Set(D3DXVECTOR3(PLAYER_INITPOS, 0.0f, PLAYER_INITPOS), CCharaBase::MOVETYPE_PLAYER_INPUT, 0, (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_pPlayer[0]->SetCameraName("1P_CAMERA");
				pCameraManager->SetCameraHomingChara("1P_CAMERA", (C3DCharactor*)m_pPlayer[0]->GetCharaMover());
			}

			if (m_pPlayer[1] != NULL)
			{
				m_pPlayer[1]->Set(D3DXVECTOR3(-PLAYER_INITPOS, 0.0f, PLAYER_INITPOS), CCharaBase::MOVETYPE_PLAYER_INPUT, 1, (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_pPlayer[1]->SetCameraName("2P_CAMERA");
				pCameraManager->SetCameraHomingChara("2P_CAMERA", (C3DCharactor*)m_pPlayer[1]->GetCharaMover());
			}

			if (m_pPlayer[2] != NULL)
			{
				m_pPlayer[2]->Set(D3DXVECTOR3(PLAYER_INITPOS, 0.0f, -PLAYER_INITPOS), CCharaBase::MOVETYPE_PLAYER_INPUT, 2, (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_pPlayer[2]->SetCameraName("3P_CAMERA");
				pCameraManager->SetCameraHomingChara("3P_CAMERA", (C3DCharactor*)m_pPlayer[2]->GetCharaMover());
			}
			if (m_pPlayer[3] != NULL)
			{
				m_pPlayer[3]->Set(D3DXVECTOR3(-PLAYER_INITPOS, 0.0f, -PLAYER_INITPOS), CCharaBase::MOVETYPE_PLAYER_INPUT, 3, (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_pPlayer[3]->SetCameraName("4P_CAMERA");
				pCameraManager->SetCameraHomingChara("4P_CAMERA", (C3DCharactor*)m_pPlayer[3]->GetCharaMover());
			}
			break;
		case 1:
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
				m_pPlayer[0]->Set(D3DXVECTOR3(200, 0.0f, 200), CCharaBase::MOVETYPE_PLAYER_INPUT, 0, (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_pPlayer[0]->SetCameraName("1P_CAMERA");
				pCameraManager->SetCameraHomingChara("1P_CAMERA", (C3DCharactor*)m_pPlayer[0]->GetCharaMover());
			}

			if (m_pPlayer[1] != NULL)
			{
				m_pPlayer[1]->Set(D3DXVECTOR3(-200, 0.0f, 200), CCharaBase::MOVETYPE_PLAYER_INPUT, 1, (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_pPlayer[1]->SetCameraName("2P_CAMERA");
				pCameraManager->SetCameraHomingChara("2P_CAMERA", (C3DCharactor*)m_pPlayer[1]->GetCharaMover());
			}

			if (m_pPlayer[2] != NULL)
			{
				m_pPlayer[2]->Set(D3DXVECTOR3(200, 0.0f, -200), CCharaBase::MOVETYPE_PLAYER_INPUT, 2, (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_pPlayer[2]->SetCameraName("3P_CAMERA");
				pCameraManager->SetCameraHomingChara("3P_CAMERA", (C3DCharactor*)m_pPlayer[2]->GetCharaMover());
			}
			if (m_pPlayer[3] != NULL)
			{
				m_pPlayer[3]->Set(D3DXVECTOR3(-200, 0.0f, -200), CCharaBase::MOVETYPE_PLAYER_INPUT, 3, (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_pPlayer[3]->SetCameraName("4P_CAMERA");
				pCameraManager->SetCameraHomingChara("4P_CAMERA", (C3DCharactor*)m_pPlayer[3]->GetCharaMover());
			}
			break;
		}
	}
}

//=============================================================================
// 人数に応じた筒の生成処理
//=============================================================================
void CGame::TubeSetting(int nNum)
{
	switch (nNum)
	{
	case 1:
		if (m_apTube[0] == NULL)
		{
			m_apTube[0] = CTube::Create(WORD_TUBE001_POS_1P, WORD_SIZE_001, "TUBE", 3);
		}
		break;

	case 2:
		for (int nCntTube = 0; nCntTube < nNum; nCntTube++)
		{
			if (m_apTube[nCntTube] == NULL)
			{
				if (nCntTube == 0) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE002_POS_1P, WORD_SIZE_002, "TUBE", 3); }
				if (nCntTube == 1) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE002_POS_2P, WORD_SIZE_002, "TUBE", 3); }
			}
		}
		break;

	case 3:
		for (int nCntTube = 0; nCntTube < nNum; nCntTube++)
		{
			if (m_apTube[nCntTube] == NULL)
			{
				if (nCntTube == 0) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_1P, WORD_SIZE_002, "TUBE", 3); }
				if (nCntTube == 1) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_2P, WORD_SIZE_002, "TUBE", 3); }
				if (nCntTube == 2) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_3P, WORD_SIZE_002, "TUBE", 3); }
			}
		}
		break;

	case 4:
		for (int nCntTube = 0; nCntTube < nNum; nCntTube++)
		{
			if (m_apTube[nCntTube] == NULL)
			{
				if (nCntTube == 0) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_1P, WORD_SIZE_002, "TUBE", 3); }
				if (nCntTube == 1) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_2P, WORD_SIZE_002, "TUBE", 3); }
				if (nCntTube == 2) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_3P, WORD_SIZE_002, "TUBE", 3); }
				if (nCntTube == 3) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE004_POS_4P, WORD_SIZE_002, "TUBE", 3); }
			}
		}
		break;

	default:
		for (int nCntTube = 0; nCntTube < MAX_PLAYER; nCntTube++)
		{
			if (m_apTube[nCntTube] == NULL)
			{
				if (nCntTube == 0) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_1P, WORD_SIZE_002, "TUBE", 3); }
				if (nCntTube == 1) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_2P, WORD_SIZE_002, "TUBE", 3); }
				if (nCntTube == 2) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_3P, WORD_SIZE_002, "TUBE", 3); }
				if (nCntTube == 3) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE004_POS_4P, WORD_SIZE_002, "TUBE", 3); }
			}
		}
		break;
	}
}

//=============================================================================
// ポイントの生成処理
//=============================================================================
void CGame::SetPointFrame(int nNumPlayer)
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

//=============================================================================
// ステージ生成の処理
//=============================================================================
void CGame::SetStage(int nNumState,int nCntState)
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
void CGame::SetCreateWord(void)
{
	if (m_pWordCreate != NULL) { m_pWordCreate->LoadFile(m_pcStageNameWord[m_nNumStage][m_nChangeNum]); }
}

//=============================================================================
// 文字2D可視化の取得処理
//=============================================================================
CTube *CGame::GetTube(int nNum)
{
	if (m_apTube[nNum] != NULL) { return m_apTube[nNum]; }
	return NULL;
}



#if 0
//=============================================================================
// ブロックとの当たり判定処理
//=============================================================================
bool CGame::Collision(D3DXVECTOR3 *pos0, float fRadius0, D3DXVECTOR3 *pos1, float fRadius1)
{
	bool bHit = false;	// 当たっていない状態

	// 中心と中心の差を求める
	D3DXVECTOR3 DiffLength = D3DXVECTOR3(pos0->x - pos1->x, pos0->y - pos1->y, pos0->z - pos1->z);

	// 中心から中心のベクトルの長さを算出
	float fLength = sqrtf((DiffLength.x * DiffLength.x) + (DiffLength.y * DiffLength.y) + (DiffLength.z * DiffLength.z));

	if (fLength < fRadius0 + fRadius1)
	{// 長さが半径の和より小さければ当たっている
		bHit = true;
	}

	return bHit;	// ブロックに当たっているかどうかを返す
}
#endif