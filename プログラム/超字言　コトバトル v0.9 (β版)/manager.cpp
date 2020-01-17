//=============================================================================
//
// マネージャ処理 [manager.cpp]
// Author : 目黒 未来也
//
//=============================================================================
#include "manager.h"
#include "main.h"

#include "scene2D.h"
#include "scene3D.h"
#include "sceneX.h"
#include "renderer.h"
#include "input.h"
#include "InputKeyboard.h"
#include "camera.h"
#include "light.h"
#include "debugProc.h"
#include "fade.h"
#include "game.h"
#include "sound.h"
#include "title.h"
#include "result.h"
#include "tutorial.h"
#include "select.h"
#include "CharaSelect.h"
#include "StageSelect.h"
#include "mask.h"
#include "Command.h"
#include "CameraManager.h"

#include "player.h"
#include "tube.h"
#include "SetWord.h"
#include "meshField.h"
#include "point.h"
//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
//CCamera *CManager::m_pCamera = NULL;
CCameraManager* CManager::m_pCameraManager = NULL;
CLight *CManager::m_pLight = NULL;
CDebugProc *CManager::m_pDebugProc = NULL;
CMask *CManager::m_pMask = NULL;
CGame *CManager::m_pGame = NULL;
CTitle *CManager::m_pTitle = NULL;
CSelect *CManager::m_pSelect = NULL;
CCharaSelect *CManager::m_pCharaSelect = NULL;
CStageSelect *CManager::m_pStageSelect = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CResult *CManager::m_pResult = NULL;
CFade *CManager::m_pFade = NULL;
CCharacterMove *CManager::m_pCharacterMove = NULL;
CInputXPad *CManager::m_pXInput[MAX_PLAYER] = {};
CManager::MODE CManager::m_mode = CManager::MODE_TITLE;	//ゲーム起動時のモード
CSound	*CManager::m_pSound[MAX_SOUND] = {};

#ifdef _DEBUG
//回数カウント用 trueならリピートモード
bool CManager::bRepeatGame = false;

int CManager::nTitleCnt    = 0;
int CManager::nSelectCnt   = 0;
int CManager::nTutoCnt     = 0;
int CManager::nCharaSelCnt = 0;
int CManager::nStaSelCnt   = 0;
int CManager::nGameCnt     = 0;
int CManager::nResultCnt   = 0;
#endif

//=============================================================================
// マネージャクラスのコンストラクタ
//=============================================================================
CManager::CManager()
{
}

//==================================================6===========================
// デストラクタ
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// マネージャ初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	if (m_pRenderer == NULL)
	{
		// レンダリングクラスの生成
		m_pRenderer = new CRenderer;

		if (m_pRenderer != NULL)
		{
			// 初期化処理
			if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
			{
				return -1;
			}
		}
	}

	//カメラ・ライトの生成
	if (ObjCreate(m_pCameraManager))
	{
		m_pCameraManager->CreateCamera("DEFAULT_CAMERA", CCamera::TYPE_TPS,
			D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f);
		m_pCameraManager->SetCameraViewPort("DEFAULT_CAMERA", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}


	if (m_pLight == NULL)
	{
		// ライトクラスの生成
		m_pLight = new CLight;

		if (m_pLight != NULL)
		{
			m_pLight->Init();
		}
	}

	if (m_pInputKeyboard == NULL)
	{
		// 入力クラス(キーボード)の生成
		m_pInputKeyboard = new CInputKeyboard;

		if (m_pInputKeyboard != NULL)
		{
			m_pInputKeyboard->Init(hInstance, hWnd);
		}
	}
	for (int nCntXPad = 0; nCntXPad < MAX_PLAYER; nCntXPad++)
	{
		//入力クラス(XInputコントローラー)の生成
		if (m_pXInput[nCntXPad] == NULL)
		{
			m_pXInput[nCntXPad] = new CInputXPad;
			if (m_pXInput[nCntXPad] != NULL)
			{
				m_pXInput[nCntXPad]->Init(hInstance, hWnd);
			}
		}
	}

	if (m_pMask == NULL)
	{
		m_pMask = CMask::Create();
	}

	//サウンド
	for (int nCnt = 0; nCnt < MAX_SOUND; nCnt++)
	{
		m_pSound[nCnt] = new CSound;
		if (m_pSound[nCnt] != NULL)
		{
			m_pSound[nCnt]->InitSound(hWnd);
		}
	}
#ifdef _DEBUG
	if (m_pDebugProc == NULL)
	{
		// デバック表示クラスの生成
		m_pDebugProc = new CDebugProc;

		if (m_pDebugProc != NULL)
		{
			m_pDebugProc->Init();
		}
	}
#endif

	//テクスチャロード
	CTexture::Load();
	//モデルロード
	CLoad::LoadModel();

	if (m_pFade == NULL)
	{
		//フェードの生成
		m_pFade = CFade::Create();

		if (m_pFade != NULL)
		{
			m_pFade->SetFade(m_mode, m_pFade->FADE_IN);
		}
	}

	// モード切替
	//SetMode(m_mode);

	//ゲームスタート
	CCommand::RegistCommand("ENTER", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_RETURN);
	CCommand::RegistCommand("ENTER", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_TRIGGER, CInputXPad::XPAD_START);

	//決定
	CCommand::RegistCommand("DECISION", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_RETURN);
	CCommand::RegistCommand("DECISION", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_TRIGGER, CInputXPad::XPAD_A);
	CCommand::RegistCommand("DECISION", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_TRIGGER, CInputXPad::XPAD_RIGHT_SHOULDER);

	CCommand::RegistCommand("RIGHT", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_D);
	CCommand::RegistCommand("RIGHT", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_TRIGGER, CInputXPad::XPAD_RIGHT);

	CCommand::RegistCommand("LEFT", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_A);
	CCommand::RegistCommand("LEFT", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_TRIGGER, CInputXPad::XPAD_LEFT);

	CCommand::RegistCommand("UP", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_W);
	CCommand::RegistCommand("UP", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_TRIGGER, CInputXPad::XPAD_UP);

	CCommand::RegistCommand("DOWN", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_S);
	CCommand::RegistCommand("DOWN", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_TRIGGER, CInputXPad::XPAD_DOWN);

	CCommand::RegistCommand("PAUSE", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_P);
	CCommand::RegistCommand("PAUSE", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_TRIGGER, CInputXPad::XPAD_START);

	CCommand::RegistCommand("DELETE", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_BACKSPACE);
	CCommand::RegistCommand("DELETE", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_X);
	CCommand::RegistCommand("DELETE", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_LEFT_SHOULDER);

	CCommand::RegistCommand("DEBUG2D", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_O);

	return S_OK;
}

//=============================================================================
// マネージャ終了処理
//=============================================================================
void CManager::Uninit(void)
{
	if (m_pMask != NULL)
	{// フェードの終了
		m_pMask->Uninit();
		delete m_pMask;
		m_pMask = NULL;
	}

	if (m_pRenderer != NULL)
	{// レンダリングクラスの破棄
		// 終了処理
		m_pRenderer->Uninit();

		// メモリを開放
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//カメラ
	ObjRelease(m_pCameraManager);


	if (m_pLight != NULL)
	{// ライトクラスの破棄
	 // 終了処理
		m_pLight->Uninit();

		// メモリを開放
		delete m_pLight;
		m_pLight = NULL;
	}

	if (m_pInputKeyboard != NULL)
	{// レンダリングクラスの破棄
		 // 終了処理
		m_pInputKeyboard->Uninit();

		// メモリを開放
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}
	for (int nCntXPad = 0; nCntXPad < MAX_PLAYER; nCntXPad++)
	{
		if (m_pXInput[nCntXPad] != NULL)
		{
			// 終了処理
			m_pXInput[nCntXPad]->Uninit();

			// メモリを開放
			delete m_pXInput[nCntXPad];
			m_pXInput[nCntXPad] = NULL;
		}

	}

	//テクスチャの破棄
	CTexture::Unload();
	//モデルの破棄
	CLoad::UnloadModel();
	//フェードクラスの破棄
	if (m_pFade != NULL)
	{
		// 終了処理
		m_pFade->Uninit();

		//メモリの開放
		delete m_pFade;

		//NULLにする
		m_pFade = NULL;
	}

#ifdef _DEBUG
	if (m_pDebugProc != NULL)
	{// デバック表示クラスの破棄
		// 終了処理
		m_pDebugProc->Uninit();

		// メモリを開放
		delete m_pDebugProc;
		m_pDebugProc = NULL;
	}
#endif

	switch (m_mode)
	{
		//タイトルモードの終了処理
	case CManager::MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;

			//タイトルのBGMを止める
			m_pSound[0]->StopSound(CSound::SOUND_LABEL_BGM_TITLE);
		}
		break;

	case CManager::MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			delete m_pTutorial;
			m_pTutorial = NULL;
		}
		break;

		//ゲームモードの終了処理
	case CManager::MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		break;

		//リザルトモードの終了処理
	case CManager::MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
			//タイトルのBGMを止める
		//	m_pSound[0]->StopSound(CSound::SOUND_LABEL_BGM_RESULT);
		}
		break;

		//セレクトモードの終了処理
	case CManager::MODE_SELECT:
		if (m_pSelect != NULL)
		{
			m_pSelect->Uninit();
			delete m_pSelect;
			m_pSelect = NULL;

			//タイトルのBGMを止める
			//	m_pSound[0]->StopSound(CSound::SOUND_LABEL_BGM_RESULT);
		}
		break;
		//キャラセレクトモードの終了処理
	case CManager::MODE_CHARASELECT:
		if (m_pCharaSelect != NULL)
		{
			m_pCharaSelect->Uninit();
			delete m_pCharaSelect;
			m_pCharaSelect = NULL;
		}
		break;
		//ステージセレクトモードの終了処理
	case CManager::MODE_STAGESELECT:
		if (m_pStageSelect != NULL)
		{
			m_pStageSelect->Uninit();
			delete m_pStageSelect;
			m_pStageSelect = NULL;
		}
		break;
	}

	//サウンド
	for (int nCnt = 0; nCnt < MAX_SOUND; nCnt++)
	{
		if (m_pSound[nCnt] != NULL)
		{
			m_pSound[nCnt]->UninitSound();
			delete m_pSound[nCnt];
			m_pSound[nCnt] = NULL;
		}
	}

	CCommand::ResetCommandAll();
	// 全てのオブジェクトを解放
	CScene::ReleseAll();
}

//=============================================================================
// マネージャ更新処理
//=============================================================================
void CManager::Update(void)
{
#ifdef _DEBUG
	// デバック表示を消す
	CDebugProc::ReleseStr();
	//回数カウント用
	CDebugProc::Print("cn", "nTitleCnt    = ", nTitleCnt);
	CDebugProc::Print("cn", "nSelectCnt   = ", nSelectCnt);
	CDebugProc::Print("cn", "nTutoCnt     = ", nTutoCnt);
	CDebugProc::Print("cn", "nCharaSelCnt = ", nCharaSelCnt);
	CDebugProc::Print("cn", "nStaSelCnt   = ", nStaSelCnt);
	CDebugProc::Print("cn", "nGameCnt     = ", nGameCnt);
	CDebugProc::Print("cn", "nResultCnt   = ", nResultCnt);

	CDebugProc::Print("cn", "FADESTATE = ", (int)m_pFade->GetFade());
#endif

	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	if (m_pRenderer != NULL)
	{// レンダラー更新処理
		m_pRenderer->Update();
	}

	//カメラ
	if (m_pCameraManager != NULL)
	{
		m_pCameraManager->Update();
	}

	if (m_pLight != NULL)
	{// ライト更新処理
		m_pLight->Update();
	}

	if (m_pInputKeyboard != NULL)
	{// キーボード入力更新処理
		m_pInputKeyboard->Update();
	}

	bool bConnect = false;
	for (int nCntXPad = 0; nCntXPad < MAX_PLAYER; nCntXPad++)
	{
		if (m_pXInput[nCntXPad] != NULL)
		{
			// XInputコントローラ更新処理
			m_pXInput[nCntXPad]->Update();
			bConnect = m_pXInput[nCntXPad]->GetConnect();
		}
		m_pDebugProc->Print("cn", "XINPUT_CONNECT ::", (bConnect == true) ? 1 : 0);
	}
	if (m_pMask != NULL)
	{// フェード更新処理
		m_pMask->Update();
	}

	if (m_pFade != NULL)
	{//フェードの更新処理
		m_pFade->Update();
	}

	switch (m_mode)
	{
		//タイトルモードの更新処理
	case CManager::MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Update();
		}
		break;

	case CManager::MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Update();
		}
		break;

		//ゲームモードの更新処理
	case CManager::MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pSound[0]->SetVolume(CSound::SOUND_LABEL_BGM_GAME000, 0.2f);
			m_pGame->Update();
		}
		break;

		//リザルトモードの更新処理
	case CManager::MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Update();
		}
		break;

		//セレクトモードの更新処理
	case CManager::MODE_SELECT:
		if (m_pSelect != NULL)
		{
			m_pSelect->Update();
		}
		//キャラセレクトモード更新処理
	case CManager::MODE_CHARASELECT:
		if (m_pCharaSelect != NULL)
		{
			m_pCharaSelect->Update();
		}
		break;
		//ステージセレクトモードの更新処理
	case CManager::MODE_STAGESELECT:
		if (m_pStageSelect != NULL)
		{
			m_pStageSelect->Update();
		}
		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{// レンダラー描画処理
		m_pRenderer->Draw();
	}

	switch (m_mode)
	{
		//リザルトモードの更新処理
	case CManager::MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Draw();
		}
		break;
	}
}

//=============================================================================
// レンダラーの取得
//=============================================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
// 入力情報の取得
//=============================================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
// マスクの取得
//=============================================================================
CCharacterMove *CManager::GetCharacterMove(void)
{
	return m_pCharacterMove;
}

//=============================================================================
// マスクの取得
//=============================================================================
CMask *CManager::GetMask(void)
{
	return m_pMask;
}

//=============================================================================
// マネージャークラス サウンドを取得
//=============================================================================
CSound *CManager::GetSound(int nNum)
{
	return m_pSound[nNum];
}

//=============================================================================
// モードの設定
//=============================================================================
void CManager::SetMode(MODE mode)
{
	switch (m_mode)
	{
	case CManager::MODE_TITLE:
		//タイトルクラスの破棄
		if (m_pTitle != NULL)
		{
			// 終了処理
			m_pTitle->Uninit();

			//メモリの開放
			delete m_pTitle;

			//NULLにする
			m_pTitle = NULL;

			//タイトルのBGMを止める
			m_pSound[0]->StopSound(CSound::SOUND_LABEL_BGM_TITLE);
		}
		break;
	case CManager::MODE_SELECT:
		//リザルトクラスの破棄
		if (m_pSelect != NULL)
		{
			// 終了処理
			m_pSelect->Uninit();

			//メモリの開放
			delete m_pSelect;

			//NULLにする
			m_pSelect = NULL;

			//リザルトのBGMを止める
			m_pSound[0]->StopSound(CSound::SOUND_LABEL_BGM_SELECT);
		}
		break;
	case CManager::MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();
			delete m_pTutorial;
			m_pTutorial = NULL;
			//ゲームのBGMを止める
			m_pSound[0]->StopSound(CSound::SOUND_LABEL_BGM_TUTORIAL);
		}
		break;
	case CManager::MODE_CHARASELECT:
		//キャラセレクトモード破棄
		if (m_pCharaSelect != NULL)
		{
			// 終了処理
			m_pCharaSelect->Uninit();
			//メモリの開放
			delete m_pCharaSelect;
			//NULLにする
			m_pCharaSelect = NULL;
			//ゲームのBGMを止める
			m_pSound[0]->StopSound(CSound::SOUND_LABEL_BGM_CHARACTERSELECT);
		}
		break;
	case CManager::MODE_STAGESELECT:
		//ステージセレクトモードの破棄
		if (m_pStageSelect != NULL)
		{
			// 終了処理
			m_pStageSelect->Uninit();
			//メモリの開放
			delete m_pStageSelect;
			//NULLにする
			m_pStageSelect = NULL;
			//ゲームのBGMを止める
			m_pSound[0]->StopSound(CSound::SOUND_LABEL_BGM_STAGESELECT);
		}
		break;
	case CManager::MODE_GAME:
		//ゲームクラスの破棄
		if (m_pGame != NULL)
		{
			// 終了処理
			m_pGame->Uninit();

			delete m_pGame;

			m_pGame = NULL;

			//ゲームのBGMを止める
			m_pSound[0]->StopSound(CSound::SOUND_LABEL_BGM_GAME000);
		}
		break;

	case CManager::MODE_RESULT:
		//リザルトクラスの破棄
		if (m_pResult != NULL)
		{
			// 終了処理
			m_pResult->Uninit();
			//NULLにする
			m_pResult = NULL;
			CScene::ReleseAll();
			//リザルトのBGMを止める
			m_pSound[0]->StopSound(CSound::SOUND_LABEL_BGM_RANKING);
		}
		break;
	}
	m_mode = mode;

	//使われていたテクスチャを解放
	CTexture::ReleaseAll();

	switch (mode)
	{
	case CManager::MODE_TITLE:
		//タイトルの初期化
		if (m_pTitle == NULL)
		{//キーボードのメモリを動的確保
			m_pTitle = new CTitle;
			if (m_pTitle != NULL)
			{//タイトルのBGMを再生
				m_pSound[0]->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);
				// 初期化処理
				m_pTitle->Init();
#ifdef _DEBUG
				//回数カウント用
				nTitleCnt++;
#endif

			}
			else
			{
				MessageBox(0, "NULLじゃないです", "警告", MB_OK);
			}
		}
		else
		{
			MessageBox(0, "aaaNULLでした", "警告", MB_OK);
		}

		break;
	case CManager::MODE_CHARASELECT:
		//キャラセレクトモード初期化
		if (m_pCharaSelect == NULL)
		{//キャラセレクトモードメモリを動的確保
			m_pCharaSelect = new CCharaSelect;
			if (m_pCharaSelect != NULL)
			{//キャラセレクトのBGMを再生
				m_pSound[0]->PlaySound(CSound::SOUND_LABEL_BGM_CHARACTERSELECT);
				// 初期化処理
				m_pCharaSelect->Init();
#ifdef _DEBUG
				//回数カウント用
				nCharaSelCnt++;
#endif
			}
			else
			{
				MessageBox(0, "NULLじゃないです", "警告", MB_OK);
			}
		}
		else
		{
			MessageBox(0, "NULLでした", "警告", MB_OK);
		}
		break;
	case CManager::MODE_STAGESELECT:
		//ステージセレクトモードの初期化
		if (m_pStageSelect == NULL)
		{//ステージセレクトモードのメモリを動的確保
			m_pStageSelect = new CStageSelect;
			if (m_pStageSelect != NULL)
			{//ステージセレクトモードのBGMを再生
				m_pSound[0]->PlaySound(CSound::SOUND_LABEL_BGM_STAGESELECT);
				// 初期化処理
				m_pStageSelect->Init();
#ifdef _DEBUG
				//回数カウント用
				nStaSelCnt++;
#endif
			}
			else
			{
				MessageBox(0, "NULLじゃないです", "警告", MB_OK);
			}
		}
		else
		{
			MessageBox(0, "NULLでした", "警告", MB_OK);
		}
		break;
	case CManager::MODE_GAME:
		//ゲームの初期化
		if (m_pGame == NULL)
		{//ゲームのメモリを動的確保
			m_pGame = new CGame;
			if (m_pGame != NULL)
			{
				m_pSound[0]->PlaySound(m_pSound[0]->SOUND_LABEL_BGM_GAME000);
				// 初期化処理
				m_pGame->Init();
#ifdef _DEBUG
				//回数カウント用
				nGameCnt++;
#endif
			}
			else
			{
				MessageBox(0, "NULLじゃないです", "警告", MB_OK);
			}
		}
		else
		{
			MessageBox(0, "NULLでした", "警告", MB_OK);
		}
		break;

	case CManager::MODE_RESULT:
		//リザルトの初期化
		if (m_pResult == NULL)
		{//リザルトのメモリを動的確保
			m_pResult = new CResult;
			if (m_pResult != NULL)
			{
				//リザルトのBGMを再生
				m_pSound[0]->PlaySound(CSound::SOUND_LABEL_BGM_RANKING);
				// 初期化処理
				m_pResult->Init();
#ifdef _DEBUG
				//回数カウント用
				nResultCnt++;
#endif
			}
			else
			{
				MessageBox(0, "NULLじゃないです", "警告", MB_OK);
			}
		}
		else
		{
			MessageBox(0, "NULLでした", "警告", MB_OK);
		}
		break;

	case CManager::MODE_TUTORIAL:
		if (m_pTutorial == NULL)
		{
			m_pTutorial = new CTutorial;
			if (m_pTutorial != NULL)
			{
				//リザルトのBGMを再生
				m_pSound[0]->PlaySound(CSound::SOUND_LABEL_BGM_TUTORIAL);
				m_pTutorial->Init();
#ifdef _DEBUG
				//回数カウント用
				nTutoCnt++;
#endif
			}
			else
			{
				MessageBox(0, "NULLじゃないです", "警告", MB_OK);
			}
		}
		else
		{
			MessageBox(0, "NULLでした", "警告", MB_OK);
		}
		break;
	case CManager::MODE_SELECT:
		//リザルトの初期化
		if (m_pSelect == NULL)
		{
			//リザルトのメモリを動的確保
			m_pSelect = new CSelect;

			if (m_pSelect != NULL)
			{//リザルトのBGMを再生
				m_pSound[0]->PlaySound(CSound::SOUND_LABEL_BGM_SELECT);
				// 初期化処理
				m_pSelect->Init();
#ifdef _DEBUG
				//回数カウント用
				nSelectCnt++;
#endif
			}
			else
			{
				MessageBox(0, "NULLじゃないです", "警告", MB_OK);
			}
		}
		else
		{
			MessageBox(0, "NULLでした", "警告", MB_OK);
		}
		break;
	}

}

//=============================================================================
// プレイヤーの取得
//=============================================================================
CPlayer* CManager::GetPlayer(int nID)
{
	switch (m_mode)
	{
	case MODE_GAME:
		return CGame::GetPlayer(nID);
		break;
	case MODE_TUTORIAL:
		return CTutorial::GetPlayer(nID);
		break;
	case MODE_RESULT:
		return CResult::GetPlayer(nID);
		break;
	}

	return NULL;
}

//=============================================================================
// 筒の取得
//=============================================================================
CTube* CManager::GetTube(int nID)
{
	switch (m_mode)
	{
	case MODE_GAME:
		return CGame::GetTube(nID);
		break;
	case MODE_TUTORIAL:
		return CTutorial::GetTube(nID);
		break;
	}

	return NULL;
}

//=============================================================================
// 文字配置オブジェクトの取得
//=============================================================================
CSetWord* CManager::GetWordCreate(void)
{
	switch (m_mode)
	{
	case MODE_GAME:
		return CGame::GetWordCreate();
		break;
	case MODE_TUTORIAL:
		return CTutorial::GetWordCreate();
		break;
	}
	return NULL;
}

//=============================================================================
//	床オブジェクトの取得
//=============================================================================
CMeshField* CManager::GetMeshField(void)
{
	switch (m_mode)
	{
	case MODE_GAME:
		return CGame::GetMeshField();
		break;
	case MODE_TUTORIAL:
		return CTutorial::GetMeshField();
		break;
	}

	return NULL;
}

CPoint* CManager::GetPoint(int nNum)
{
	switch (m_mode)
	{
	case MODE_GAME:
		return CGame::GetPoint(nNum);
		break;
	case MODE_TUTORIAL:
		return CTutorial::GetPoint(nNum);
		break;
	}

	return NULL;

}