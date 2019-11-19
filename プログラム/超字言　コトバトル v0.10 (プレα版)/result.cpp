//=============================================================================
//
// リザルト処理 [result.cpp]
// Author : 目黒未来也
//
//=============================================================================
#include "result.h"
#include "debugProc.h"
#include "input.h"
#include "InputKeyboard.h"
#include "manager.h"
#include "fade.h"
#include "time.h"
#include "camera.h"
#include "SelectMenu.h"
#include "CameraManager.h"
#include "camera.h"
#include "meshField.h"
#include "sceneX.h"
#include "number.h"
//============================================================================
//	マクロ定義
//============================================================================
#define POS_1ST (D3DXVECTOR3(20.0f,100.0f,0.0f))
#define POS_2ND (D3DXVECTOR3(50.0f,100.0f,0.0f))
#define POS_3RD (D3DXVECTOR3(-10.0f,100.0f,0.0f))
#define POS_4TH (D3DXVECTOR3(-60.0f,100.0f,0.0f))

#define NUMBERPOS_1ST (D3DXVECTOR3(150.0f,100.0f,0.0f))
#define NUMBERPOS_2ND (D3DXVECTOR3(150.0f,200.0f,0.0f))
#define NUMBERPOS_3RD (D3DXVECTOR3(150.0f,300.0f,0.0f))
#define NUMBERPOS_4TH (D3DXVECTOR3(150.0f,400.0f,0.0f))


#define TIMER_SPACE			(40.0f)							// 数字と数字の間のサイズ(ゲーム時間)

//============================================================================
//静的メンバ変数宣言
//============================================================================
CPlayer *CResult::m_pPlayer[MAX_PLAYER] = {};
CResult::CharaSet CResult::m_ResultChara[MAX_PLAYER] = {};
CMeshField *CResult::m_pMeshField = NULL;

//=============================================================================
//	コンストラクタ
//=============================================================================
CResult::CResult()
{
}

//=============================================================================
//デストラクタ
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CResult::Init(void)
{
#if 1
	//メッシュフィールド生成
	m_pMeshField = NULL;
	if (m_pMeshField == NULL)
	{
		m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (m_pPlayer[nCntPlayer] == NULL)
		{
			m_pPlayer[nCntPlayer] = CPlayer::Create();
		}
	}

	CSceneX::Create(D3DXVECTOR3(20.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.7f, 0.7f, 0.5f), CLoad::MODEL_BOX, 1);
	CSceneX::Create(D3DXVECTOR3(50.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.7f, 0.5f, 0.5f), CLoad::MODEL_BOX, 1);
	CSceneX::Create(D3DXVECTOR3(-10.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.7f, 0.3f, 0.5f), CLoad::MODEL_BOX, 1);

	D3DXVECTOR3 RankPos;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		switch (nCntPlayer)
		{
		case 0:
			RankPos = POS_1ST;
			break;
		case 1:
			RankPos = POS_2ND;
			break;
		case 2:
			RankPos = POS_3RD;
			break;
		case 3:
			RankPos = POS_4TH;
			break;
		}

		if (m_pPlayer[nCntPlayer] != NULL)
		{
			m_pPlayer[nCntPlayer]->Set(RankPos, CCharaBase::MOVETYPE_RANKING_CHARA, nCntPlayer, m_ResultChara[nCntPlayer].type);
			m_pPlayer[nCntPlayer]->SetMotion(CPlayer::MOTION_UPPER_NEUTRAL, CPlayer::UPPER_BODY);
			m_pPlayer[nCntPlayer]->SetMotion(CPlayer::MOTION_LOWER_NEUTRAL, CPlayer::LOWER_BODY);
		}
	}


	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		switch (nCntPlayer)
		{
		case 0:
			RankPos = NUMBERPOS_1ST;
			break;
		case 1:
			RankPos = NUMBERPOS_2ND;
			break;
		case 2:
			RankPos = NUMBERPOS_3RD;
			break;
		case 3:
			RankPos = NUMBERPOS_4TH;
			break;
		}

		for (int nCntTime = 0; nCntTime < MAX_POINT; nCntTime++)
		{
			// タイマー初期設定
			m_apNumber[nCntPlayer][nCntTime] = new CNumber;
			if (nCntTime < 2)
			{	// ３桁まで
				m_apNumber[nCntPlayer][nCntTime]->Init(D3DXVECTOR3((RankPos.x - TIMER_SPACE * nCntTime), RankPos.y, RankPos.z), 0);
				m_apNumber[nCntPlayer][nCntTime]->SetSize(D3DXVECTOR2(30.0f, 30.0f), D3DXVECTOR2((RankPos.x - TIMER_SPACE * nCntTime), RankPos.y));
				m_apNumber[nCntPlayer][nCntTime]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (nCntTime == 2)
			{	// 3桁目
				m_apNumber[nCntPlayer][nCntTime]->Init(D3DXVECTOR3((RankPos.x - TIMER_SPACE * nCntTime), RankPos.y, RankPos.z), 0);
			}
		}
	}
	//数字のテクスチャ設定
	//TexTime(nTexData, m_nTimeOne);

#endif
	CCameraManager *pCameraManager = CManager::GetCameraManager();
	pCameraManager->CreateCamera("RESULT_CAMERA",CCamera::TYPE_SPECTOR,D3DXVECTOR3(0.0f, 60.0f, 135.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 135.0f);
	pCameraManager->SetCameraViewPort("RESULT_CAMERA", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	CCamera *pCamera = pCameraManager->GetCamera("RESULT_CAMERA");
	if (pCamera != NULL)
	{
		pCamera->SetPosR(D3DXVECTOR3(0.0f, 45.0f, 0.0f));
	}

	m_pSeletMenu = CSelectMenu::Create(D3DXVECTOR3(740, 100.0f, 0), 120, 180, CSelectMenu::MENU_TYPE::MENU_TYPE_RESULT);

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CResult::Uninit(void)
{
	//メッシュフィールドの破棄
	if (m_pSeletMenu != NULL)
	{
		m_pSeletMenu->Uninit();
		m_pSeletMenu = NULL;
	}

	//メッシュフィールドの破棄
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Uninit();
		m_pMeshField = NULL;
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		for (int nCntTime = 0; nCntTime < MAX_POINT; nCntTime++)
		{
			if (m_apNumber[nCntPlayer][nCntTime] != NULL)
			{
				m_apNumber[nCntPlayer][nCntTime]->Uninit();
				m_apNumber[nCntPlayer][nCntTime] = NULL;
			}
		}
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (m_pPlayer[nCntPlayer] != NULL)
		{	// プレイヤーの破棄
			m_pPlayer[nCntPlayer]->Uninit();
			m_pPlayer[nCntPlayer] = NULL;
		}
	}
	//全ての終了処理
	Release();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CResult::Update(void)
{
	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();

	//任意のキーENTER
	if (CCommand::GetCommand("DECISION"))
	{
	//	pFade->SetFade(pManager->MODE_TITLE, pFade->FADE_OUT);
	}
#ifdef _DEBUG
	CDebugProc::Print("c", "リザルト");

#endif
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CResult::Draw(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		for (int nCntTime = 0; nCntTime < MAX_POINT; nCntTime++)
		{
			if (m_apNumber[nCntPlayer][nCntTime] != NULL)
			{
				m_apNumber[nCntPlayer][nCntTime]->Draw();
			}
		}
	}
}

//=============================================================================
// キャラクター情報を設定
//=============================================================================
void CResult::SetRanking(int nNumPlayer, CPlayer::PLAYER_TYPE type, int nPoint)
{
	m_ResultChara[nNumPlayer].type = type;
	m_ResultChara[nNumPlayer].nPoint = nPoint;
}
