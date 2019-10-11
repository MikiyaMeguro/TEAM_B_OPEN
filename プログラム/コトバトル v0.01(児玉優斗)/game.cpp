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

#include "PlayerNumSelect.h"

#include "player.h"
#include "charactor.h"
//============================================================================
//	マクロ定義
//============================================================================
#define SIZE_X (SCREEN_WIDTH)
#define SIZE_Y (SCREEN_HEIGHT)
#define COLISIONSIZE (20.0f)
#define TIME_INI		(60)
#define WORD_TUBE_POS	(D3DXVECTOR3(50.0f, 240.0f, 0.0f))
#define WORD_TUBE_SIZE	(D3DXVECTOR2(60.0f, 130.0f))
//============================================================================
//静的メンバ変数宣言
//============================================================================
CWordManager *CGame::m_pWordManager = NULL;
CPlayer *CGame::m_pPlayer[MAX_PLAYER] = {};
CTube *CGame::m_pTube = NULL;
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
	//カメラのクリエイト
	CCameraManager *pCameraManager = CManager::GetCameraManager();

	if (pCameraManager != NULL)
	{
		pCameraManager->CreateCamera("1P_CAMERA", CCamera::TYPE_TPS,
			D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(-0.2f, 0.0f, 0.0f), 150.0f);
		pCameraManager->SetCameraViewPort("1P_CAMERA", 0, 0, SCREEN_WIDTH, 355);
		pCameraManager->CreateCamera("2P_CAMERA", CCamera::TYPE_TPS,
			D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(-0.2f, D3DX_PI, 0.0f), 300.0f);
		pCameraManager->SetCameraViewPort("2P_CAMERA", 0, 365, SCREEN_WIDTH, 340);
		//pCameraManager->CreateCamera("3P_CAMERA", CCamera::TYPE_TPS,
		//	D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.2f, D3DX_PI * -0.5f, 0.0f), 200.0f);
		//pCameraManager->SetCameraViewPort("3P_CAMERA", 0, 380, 620, 340);

		//pCameraManager->CreateCamera("4P_CAMERA", CCamera::TYPE_TPS,
		//	D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.2f, D3DX_PI * 0.5f, 0.0f), 200.0f);
		//pCameraManager->SetCameraViewPort("4P_CAMERA", 660, 380, 620, 340);
	}

	CScene3D* p3D = NULL;
	p3D = CScene3D::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), "BLOCK");
	p3D = CScene3D::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f), "BLOCK");
	p3D->SetRot(D3DXVECTOR3(D3DX_PI,0.0f,0.0f));


	// プレイヤーの生成
	m_pPlayer[0] = CPlayer::Create();
	if (m_pPlayer[0] != NULL)
	{
		m_pPlayer[0]->Set(D3DXVECTOR3(100.0f, -20.0f, 100.0f), CCharaBase::MOVETYPE_PLAYER_INPUT);
		m_pPlayer[0]->SetCameraName("1P_CAMERA");
		pCameraManager->SetCameraHomingChara("1P_CAMERA", (C3DCharactor*)m_pPlayer[0]->GetCharaMover());

	}


	//pPlayer = CPlayer::Create();
	//if (pPlayer != NULL)
	//{
	//	pPlayer->Set(D3DXVECTOR3(-100.0f, -20.0f, 100.0f), CCharaBase::MOVETYPE_PLAYER_INPUT);
	//	pPlayer->SetCameraName("2P_CAMERA");
	//	pCameraManager->SetCameraHomingChara("2P_CAMERA", (C3DCharactor*)pPlayer->GetCharaMover());

	//}

	//pPlayer = CPlayer::Create();
	//if (pPlayer != NULL)
	//{
	//	pPlayer->Set(D3DXVECTOR3(100.0f, -20.0f, -100.0f), CCharaBase::MOVETYPE_PLAYER_INPUT);
	//	pPlayer->SetCameraName("3P_CAMERA");
	//	pCameraManager->SetCameraHomingChara("3P_CAMERA", (C3DCharactor*)pPlayer->GetCharaMover());

	//}

	//pPlayer = CPlayer::Create();
	//if (pPlayer != NULL)
	//{
	//	pPlayer->Set(D3DXVECTOR3(-100.0f, -20.0f, -100.0f), CCharaBase::MOVETYPE_PLAYER_INPUT);
	//	pPlayer->SetCameraName("4P_CAMERA");
	//	pCameraManager->SetCameraHomingChara("4P_CAMERA", (C3DCharactor*)pPlayer->GetCharaMover());

	//}

	// 文字管理の生成
	if (m_pWordManager == NULL)
	{
		m_pWordManager = new CWordManager;
		m_pWordManager->Init();
	}

	// 文字の可視化UI(2D)の生成
	if (m_pTube == NULL)
	{
		m_pTube = CTube::Create(WORD_TUBE_POS, WORD_TUBE_SIZE, "TUBE", 3);
	}

	// 机
	CWord::Create(D3DXVECTOR3(0.0f, -20.0f, 0.0f), 12.0f, 12.0f, "WORD", 17);
	CWord::Create(D3DXVECTOR3(-300.0f, -20.0f, 0.0f), 12.0f, 12.0f, "WORD", 7);
	CWord::Create(D3DXVECTOR3(-400.0f, -20.0f, 0.0f), 12.0f, 12.0f, "WORD", 3);

	// リンゴ
	CWord::Create(D3DXVECTOR3(-200.0f, -20.0f, 0.0f), 12.0f, 12.0f, "WORD", 39);
	CWord::Create(D3DXVECTOR3(-100.0f, -20.0f, 150.0f), 12.0f, 12.0f, "WORD", 45);
	CWord::Create(D3DXVECTOR3(-50.0f, -20.0f, 0.0f), 12.0f, 12.0f, "WORD", 9);

}
//=============================================================================
// 終了処理
//=============================================================================
void CGame::Uninit(void)
{
	if (m_pTube != NULL)
	{	// 文字の可視化UI(2D)の破棄
		m_pTube->Uninit();
		m_pTube = NULL;
	}
	//全ての終了処理
	CScene::ReleseAll();

	if (m_pWordManager != NULL)
	{// ライトクラスの破棄
	 // 終了処理
		m_pWordManager->Uninit();

		// メモリを開放
		delete m_pWordManager;
		m_pWordManager = NULL;
	}
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
	// ランダムな値を更新
	srand((unsigned int)time(NULL));

	CDebugProc::Print("c", "ゲームモード");


	//任意のキーENTER
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		pFade->SetFade(pManager->MODE_RESULT, pFade->FADE_OUT);
	}
	if (pInputKeyboard->GetTrigger(DIK_BACKSPACE) == true)
	{
		pFade->SetFade(pManager->MODE_GAME, pFade->FADE_OUT);

	}

	// 文字管理の更新
	if (m_pWordManager != NULL) { m_pWordManager->Update(); }


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
void CGame::CameraSetting(void)
{
	CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();
	//カメラのクリエイト
	CCameraManager *pCameraManager = CManager::GetCameraManager();
	if (pCameraManager != NULL)
	{
		switch (NumPlayer)
		{
		case CPlayerSelect::SELECTPLAYER_1P:
			break;
		case CPlayerSelect::SELECTPLAYER_2P:
			break;
		case CPlayerSelect::SELECTPLAYER_3P:
			break;
		case CPlayerSelect::SELECTPLAYER_4P:
			pCameraManager->CreateCamera("1P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f);
			pCameraManager->SetCameraViewPort("1P_CAMERA", 0, 0, 620, 340);

			pCameraManager->CreateCamera("2P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 100.0f);
			pCameraManager->SetCameraViewPort("2P_CAMERA", 660, 0, 620, 340);

			pCameraManager->CreateCamera("3P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), 100.0f);
			pCameraManager->SetCameraViewPort("3P_CAMERA", 0, 380, 620, 340);

			pCameraManager->CreateCamera("4P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), 100.0f);
			pCameraManager->SetCameraViewPort("4P_CAMERA", 660, 380, 620, 340);
			break;
		}
	}
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