//=============================================================================
//
// 管理クラス処理 [Manager.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "Manager.h"
#include "scene2D.h"
#include "scene3D.h"
#include "sceneX.h"
#include "sceneBillboard.h"

#include "pause.h"
#include "fade.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
//==================================================================
// 静的メンバ変数
//==================================================================
CRenderer* CManager::m_pRenderer = NULL;
CInputKeyboard* CManager::m_pInputKeyboard = NULL;
CCameraManager* CManager::m_pCameraManager = NULL;
CLight* CManager::m_pLight = NULL;
CDebugProc* CManager::m_pDebugProc = NULL;

CFade*			CManager::m_pFade = NULL;
CPause*			CManager::m_pPause = NULL;
CSound*				CManager::m_pSound = NULL;

//状態遷移用のポインタ
CTitle* CManager::m_pTitle = NULL;							//タイトル
CTutorial* CManager::m_pTutorial = NULL;					//チュートリアル
CGame* CManager::m_pGame = NULL;							//ゲーム
CResult* CManager::m_pResult = NULL;						//リザルト
CRanking* CManager::m_pRanking = NULL;						//ゲーム

CManager::MODE CManager::m_Mode = CManager::MODE_TITLE;		//現在の画面状態
CManager::MODE CManager::m_OrgMode = CManager::MODE_NONE;	//一つ前の画面状態
bool CManager::m_bPauseFlag = false;

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CManager::CManager()
{

}
CManager::~CManager()
{

}

//==================================================================
// 初期化処理
//==================================================================
HRESULT CManager::Init(HINSTANCE hInstance,HWND hWnd)
{
	srand((unsigned int)time(0));

	//レンダラの生成
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;
	}

	if (m_pRenderer != NULL)
	{
		// 初期化処理(ウィンドウを作成してから行う)
		if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
		{
			// 終了処理
			m_pRenderer->Uninit();

			delete m_pRenderer;
			m_pRenderer = NULL;
			return -1;
		}
	}
	m_pSound = CSound::Create(hWnd);

	CTexture::Load();

	//デバック管理クラスの生成
	Create(m_pDebugProc);

	//ポーズ画面の生成
	Create(m_pPause);

	//カメラ・ライトの生成
	if (Create(m_pCameraManager))
	{
		m_pCameraManager->CreateCamera("1P_CAMERA",CCamera::TYPE_TPS,
			D3DXVECTOR3(0.0f,0.0f,-100.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),100.0f);

		m_pCameraManager->SetCameraViewPort("1P_CAMERA",0,0,620,340);

		m_pCameraManager->CreateCamera("2P_CAMERA", CCamera::TYPE_TPS,
			D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 100.0f);

		m_pCameraManager->SetCameraViewPort("2P_CAMERA", 660, 0, 620, 340);

		m_pCameraManager->CreateCamera("3P_CAMERA", CCamera::TYPE_TPS,
			D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), 100.0f);
		m_pCameraManager->SetCameraViewPort("3P_CAMERA", 0, 380, 620, 340);

		m_pCameraManager->CreateCamera("4P_CAMERA", CCamera::TYPE_TPS,
			D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), 100.0f);

		m_pCameraManager->SetCameraViewPort("4P_CAMERA", 660, 380, 620, 340);
	}

	Create(m_pLight);

	//入力デバイスの生成
	m_pInputKeyboard = new CInputKeyboard;

	if (m_pInputKeyboard != NULL)
	{
		// 初期化処理(ウィンドウを作成してから行う)
		if (FAILED(m_pInputKeyboard->Init(hInstance,hWnd)))
		{
			// 終了処理
			m_pInputKeyboard->Uninit();

			delete m_pInputKeyboard;
			m_pInputKeyboard = NULL;
			return -1;
		}
	}
	//フェードの生成
	m_pFade = CFade::Create(CManager::MODE_TITLE);

	//モードの設定
	SetMode(m_Mode);

	//コマンド登録
	CCommand::RegistCommand("ENTER", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_RETURN);

	CCommand::RegistCommand("PAUSE", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_P);

	CCommand::RegistCommand("PAUSE_MENU_UP", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_UP);
	CCommand::RegistCommand("PAUSE_MENU_UP", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_W);
	CCommand::RegistCommand("PAUSE_MENU_DOWN", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_DOWN);
	CCommand::RegistCommand("PAUSE_MENU_DOWN", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_S);

	return S_OK;
}

//==================================================================
// 終了処理
//==================================================================
void CManager::Uninit(void)
{
	//オブジェクト全破棄
	CScene::ReleaseAll(true);

	//フェード破棄
	Release(m_pFade);

	//Uninit
	switch (m_Mode)
	{
	case CManager::MODE_LOGO:
		break;
	case CManager::MODE_TITLE:
		Release(m_pTitle);
		break;
	case CManager::MODE_SELECT:
		break;
	case CManager::MODE_TUTORIAL:
		Release(m_pTutorial);
		break;
	case CManager::MODE_GAME:
		Release(m_pGame);
		break;
	case CManager::MODE_RESULT:
		Release(m_pResult);
		break;
	case CManager::MODE_RANKING:
		Release(m_pRanking);
		break;
	case CManager::MODE_OPTION:
		break;
	}

	if (m_pSound != NULL)
	{
		m_pSound->StopAll();
		Release(m_pSound);
	}

	//キーボード
	Release(m_pInputKeyboard);

	//テクスチャ破棄
	CTexture::Unload();

	//ポーズ画面の生成
	Release(m_pPause);

	//カメラ
	Release(m_pCameraManager);

	//ライト
	Release(m_pLight);

	//デバック
	Release(m_pDebugProc);

	//レンダラの削除
	Release(m_pRenderer);

}

//==================================================================
// 更新処理
//==================================================================
void CManager::Update(void)
{
	//Update
	switch (m_Mode)
	{
	case CManager::MODE_LOGO:
		break;
	case CManager::MODE_TITLE:
		if (m_pTitle != NULL) { m_pTitle->Update(); }
		break;
	case CManager::MODE_SELECT:
		break;
	case CManager::MODE_TUTORIAL:
		if (m_pTutorial != NULL) { m_pTutorial->Update(); }
		break;
	case CManager::MODE_GAME:
		if (m_pGame != NULL) { m_pGame->Update(); }
		break;
	case CManager::MODE_RESULT:
		if (m_pResult != NULL) { m_pResult->Update(); }
		break;
	case CManager::MODE_RANKING:
		if (m_pRanking != NULL) { m_pRanking->Update(); }
		break;
	case CManager::MODE_OPTION:
		break;
	}


	if (m_pInputKeyboard != NULL)
	{
		// 更新処理
		m_pInputKeyboard->Update();
	}

	//カメラ
	if (m_pCameraManager != NULL)
	{
		m_pCameraManager->Update();
	}

	if (m_pLight != NULL)
	{
		// 更新処理
		m_pLight->Update();
	}

	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}

	if (m_bPauseFlag == false)
	{	//レンダラの更新
		if (m_pRenderer != NULL)
		{
			m_pRenderer->Update();
		}
	}
	else
	{//ポーズの更新
		if (m_pPause != NULL)
		{
			m_pPause->Update();
		}
	}

	if (m_pInputKeyboard->GetPress(DIK_Q) == true &&
		m_pInputKeyboard->GetTrigger(DIK_P) == true)
	{
		//オブジェクト全破棄
		CScene::ReleaseAll(false);
	}

	CDebugProc::Print("TEXNUM = %d\n",CTexture::GetTexNum(true));
	CDebugProc::Print("MODE = %s\n",GetModeName());
}

//==================================================================
// 描画処理
//==================================================================
void CManager::Draw(void)
{
	//Draw
	switch (m_Mode)
	{
	case CManager::MODE_LOGO:
		break;
	case CManager::MODE_TITLE:
		if (m_pTitle != NULL) { m_pTitle->Draw(); }
		break;
	case CManager::MODE_SELECT:
		break;
	case CManager::MODE_TUTORIAL:
		if (m_pTutorial != NULL) { m_pTutorial->Draw(); }
		break;
	case CManager::MODE_GAME:
		if (m_pGame != NULL) { m_pGame->Draw(); }
		break;
	case CManager::MODE_RESULT:
		if (m_pResult != NULL) { m_pResult->Draw(); }
		break;
	case CManager::MODE_RANKING:
		if (m_pRanking != NULL) { m_pRanking->Draw(); }
		break;
	case CManager::MODE_OPTION:
		break;
	}

	if (m_pRenderer != NULL)
	{
		// 描画処理
		m_pRenderer->Draw();
	}
}

//==================================================================
// モード設定処理
//==================================================================
HRESULT CManager::SetMode(MODE mode)
{
	//Uninit
	switch (m_Mode)
	{
	case CManager::MODE_LOGO:
		break;
	case CManager::MODE_TITLE:
		Release(m_pTitle);//解放
		break;
	case CManager::MODE_SELECT:
		break;
	case CManager::MODE_TUTORIAL:
		Release(m_pTutorial);
		break;
	case CManager::MODE_GAME:
		Release(m_pGame);
		break;
	case CManager::MODE_RESULT:
		Release(m_pResult);
		break;
	case CManager::MODE_RANKING:
		Release(m_pRanking);
		break;
	case CManager::MODE_OPTION:
		break;
	}

	switch (mode)
	{
	case CManager::MODE_LOGO:
		break;
	case CManager::MODE_TITLE:
		Create(m_pTitle); //生成
		break;
	case CManager::MODE_SELECT:
		break;
	case CManager::MODE_TUTORIAL:
		Create(m_pTutorial);
		break;
	case CManager::MODE_GAME:
		Create(m_pGame);
		break;
	case CManager::MODE_RESULT:
		Create(m_pResult);
		break;
	case CManager::MODE_RANKING:
		Create(m_pRanking);
		break;
	case CManager::MODE_OPTION:
		break;
	}
	m_OrgMode = m_Mode;	//遷移前のモードを格納
	m_Mode = mode;		//現在のモードを変更
	return S_OK;
}


//==================================================================
// モード名取得処理
//==================================================================
LPCSTR CManager::GetModeName(void)
{
	LPCSTR name = "";

	switch (m_Mode)
	{
	case CManager::MODE_LOGO:		name = "LOGO";
		break;
	case CManager::MODE_TITLE:		name = "TITLE";
		break;
	case CManager::MODE_SELECT:		name = "SELECT";
		break;
	case CManager::MODE_TUTORIAL:	name = "TUTORIAL";
		break;
	case CManager::MODE_GAME:		name = "GAME";
		break;
	case CManager::MODE_RESULT:		name = "RESULT";
		break;
	case CManager::MODE_RANKING:	name = "RANKING";
		break;
	case CManager::MODE_OPTION:		name = "OPTION";
		break;
	}

	return name;
}