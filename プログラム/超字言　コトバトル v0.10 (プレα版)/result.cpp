//=============================================================================
//
// リザルト処理 [result.cpp]
// Author : 目黒未来也/後閑茜
//
//=============================================================================
#include "result.h"
#include "debugProc.h"
#include "input.h"
#include "InputKeyboard.h"
#include "manager.h"
#include "fade.h"
#include "camera.h"
#include "CameraManager.h"
#include "sceneX.h"
#include "scene3D.h"
#include "number.h"
#include "SpotLight.h"

//============================================================================
//	マクロ定義
//============================================================================
#define POS_4TH (D3DXVECTOR3(-52.0f,0.0f,0.0f))							// 四位のプレイヤーの位置
#define TIMER_SPACE			(40.0f)										// 数字と数字の間のサイズ(ゲーム時間)
#define SIZE_X (SCREEN_WIDTH/2)											// 横幅
#define SIZE_Y (SCREEN_HEIGHT/2)										// 縦幅
#define DEFAULT_SIZE (150.0f)											// ポリゴンサイズの基本の大きさ
#define DEFAULT_SCALE (D3DXVECTOR3(1.0f,1.0f,1.0f))						// ポリゴンサイズの基本の大きさ
#define DEFAULT_POS	(D3DXVECTOR3(0.0f,0.0f,0.0f))						// ポリゴンの初期位置
#define DEFAULT_ROT (D3DXVECTOR3(0.0f,0.0f,0.0f))						// 初期化回転
#define DEFAULT_COL_WHITE (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))				// 初期化色_白
#define DEFAULT_COL_PL1	 (D3DXCOLOR(0.8f,0.2f,0.2f,1.0f))				// 色_赤
#define DEFAULT_COL_PL2 (D3DXCOLOR(0.2f,0.2f,0.8f,1.0f))				// 色_青
#define DEFAULT_COL_PL3 (D3DXCOLOR(0.2f,0.8f,0.2f,1.0f))				// 色_緑
#define DEFAULT_COL_PL4 (D3DXCOLOR(0.8f,0.7f,0.2f,1.0f))				// 色_橙
#define DEFAULT_COL_COM (D3DXCOLOR(0.7f,0.7f,0.7f,1.0f))				// 色_灰
#define DEFAULT_COL_WHITE_ALPHA_HARF (D3DXCOLOR(0.8f,0.8f,0.8f,0.5f))	// 初期化色_白（半透明）
#define DEFAULT_SIZE2D (D3DXVECTOR2(0.0f,0.0f))							// Vectro2を用いたサイズ初期化
#define DEFAULT_EFFECT (D3DXVECTOR2(1.0f,0.0f))							// エフェクトの初期設定
#define CHARAICON_POS (D3DXVECTOR3(140.0f,150.0f,0.0f))					// アイコンの位置
#define CHARAICON_INTERVAL (300.0f)										// アイコンの間隔
#define NUMCALLOUT_CORRECTION (10.0f)									// 数字吹き出しのX位置微調整
#define AUDIENCE_INTERVAL (28.0f)
//============================================================================
//静的メンバ変数宣言
//============================================================================
CPlayer *CResult::m_pPlayer[MAX_PLAYER] = {};
CResult::CharaSet CResult::m_ResultChara[MAX_PLAYER] = {};
CMeshField *CResult::m_pMeshField = NULL;
CScene3D *CResult::m_apAudience[MAX_AUDIENCE] = {};

//=============================================================================
//	コンストラクタ
//=============================================================================
CResult::CResult()
{
	m_pSeletMenu = NULL;
	m_bMenu = false;
	m_bMenuCreate = false;
	m_bEffectPro = false;
	m_EffectAlpha = DEFAULT_SIZE2D;
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		m_RankPos[nCnt] = DEFAULT_POS;
		m_PlayerNumPos[nCnt] = DEFAULT_POS;
		m_PlayerIconPos[nCnt] = DEFAULT_POS;
		m_RankIconSize[nCnt] = DEFAULT_SIZE2D;
		m_PlayerNumSize[nCnt] = DEFAULT_SIZE2D;
		m_PlayerIconSize[nCnt] = DEFAULT_SIZE2D;
		m_EffectState = EFFECTPRO_NONE;
		for (int nCntEffe = 0; nCntEffe < 2; nCntEffe++)
		{
			m_RankEffect[nCnt][nCntEffe] = DEFAULT_POS;
		}
	}
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
	int nCntWinScore = 0;				//勝利カウント
	int nCntRankNum[4] = { 0,0,0,0 };	//順位ごとに何人いるか
	CharaSet nRepCharaSet = {};			//情報入れ替え

	float fPosX = 30;	//表彰台初期位置
	float fNext = 42;	//表彰台の間の幅

	InitPointer();
	SetPolygon();
	SetModel();
	SetAudience();
#if 0
	m_ResultChara[0].nPoint = 0;
	m_ResultChara[1].nPoint = 1;
	m_ResultChara[2].nPoint = 2;
	m_ResultChara[3].nPoint = 2;

	m_ResultChara[0].type = CPlayer::TYPE_BARANCE;
	m_ResultChara[1].type = CPlayer::TYPE_POWER;
	m_ResultChara[2].type = CPlayer::TYPE_SPEED;
	m_ResultChara[3].type = CPlayer::TYPE_REACH;
#endif
#if 1
	/* ソート */
	for (int nRank = 0; nRank < MAX_PLAYER; nRank++)
	{
		for (int nRankCnt = nRank + 1; nRankCnt < 4; nRankCnt++)
		{
			if (m_ResultChara[nRank].nPoint < m_ResultChara[nRankCnt].nPoint)
			{
				nRepCharaSet = m_ResultChara[nRank];
				m_ResultChara[nRank] = m_ResultChara[nRankCnt];
				m_ResultChara[nRankCnt] = nRepCharaSet;
			}
		}
	}
	//順位決め
	//ソート処理 大きい順
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
		{
			if (nCnt != nCntPlayer && m_ResultChara[nCntPlayer].nPoint >= m_ResultChara[nCnt].nPoint)
			{//他と比べて自分が大きい時勝利カウントを増やす
				nCntWinScore++;
			}
		}
		//何回勝ったかで順位決め
		switch (nCntWinScore)
		{
		case 0:
			m_ResultChara[nCntPlayer].nNumRank = 4;
			nCntRankNum[3]++;
			break;
		case 1:
			m_ResultChara[nCntPlayer].nNumRank = 3;
			nCntRankNum[2]++;
			break;
		case 2:
			m_ResultChara[nCntPlayer].nNumRank = 2;
			nCntRankNum[1]++;
			break;
		case 3:
			m_ResultChara[nCntPlayer].nNumRank = 1;
			nCntRankNum[0]++;
			break;
		default:
			break;
		}
		//勝利数を初期化
		nCntWinScore = 0;
	}
#endif // 0
	//ナンバーの生成
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		for (int nCntTime = 0; nCntTime < MAX_POINT; nCntTime++)
		{// ナンバー初期設定
			m_apNumber[nCntPlayer][nCntTime] = new CNumber;
			if (m_apNumber[nCntPlayer][nCntTime] != NULL)
			{
				if (nCntTime < 2)
				{	// ３桁まで
					m_apNumber[nCntPlayer][nCntTime]->Init(D3DXVECTOR3((TIMER_SPACE * nCntTime), CHARAICON_POS.y, CHARAICON_POS.z), 0);
					m_apNumber[nCntPlayer][nCntTime]->SetSize(D3DXVECTOR2(30.0f, 30.0f),
						D3DXVECTOR2((TIMER_SPACE * nCntTime) + m_apScene2D[nCntPlayer + 1]->GetPosition().x + 40.0f, m_apScene2D[nCntPlayer + 1]->GetPosition().y));
					m_apNumber[nCntPlayer][nCntTime]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
			}
		}
	}
#if 1
	//メッシュフィールド生成
	m_pMeshField = NULL;
	if (m_pMeshField == NULL)
	{
		m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_pMeshField->BindTexture("RANKING_MESHFIELD");
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (m_pPlayer[nCntPlayer] == NULL)
		{
			m_pPlayer[nCntPlayer] = CPlayer::Create();
		}
	}

	//表彰台生成
	for (int nCnt = 0; nCnt < nCntRankNum[0]; nCnt++)
	{//順位の数だけ
		CSceneX::Create(D3DXVECTOR3(fPosX, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CLoad::MODEL_PODIUM1, 1);
		if(nCnt == 1)
		{	//1位(同率)の場所へ変える
			fPosX = 30;
			fNext *= -1;
		}
		//位置をずらす
		fPosX += fNext;
	}

	fPosX = 70;
	for (int nCnt = 0; nCnt < nCntRankNum[1]; nCnt++)
	{//順位の数だけ
		CSceneX::Create(D3DXVECTOR3(fPosX, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CLoad::MODEL_PODIUM2, 1);
		if (nCnt == 0)
		{	//2位(同率)の場所へ変える
			fPosX = 30;
			fNext *= -1;
		}
		//位置をずらす
		fPosX += fNext;
	}

	fPosX = -10;
	fNext = -42;
	for (int nCnt = 0; nCnt < nCntRankNum[2]; nCnt++)
	{//順位の数だけ
		CSceneX::Create(D3DXVECTOR3(fPosX, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CLoad::MODEL_PODIUM3, 1);
		//3位(同率)の位置をずらす
		fPosX += fNext;
	}

	D3DXVECTOR3 RankPos;
	int nCntRankPos[4] = { 0,0,0,0 };	//順位ごとに何人いるか

	fPosX = 20;
	fNext = 32;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{	//初期位置設定
		switch (m_ResultChara[nCntPlayer].nNumRank)
		{
		case 1:
			if (nCntRankPos[0] == 0)
			{
				fPosX = 30;
				Set2DUI(nCntPlayer, 1);
				SetNumCallout(nCntPlayer,1, m_ResultChara[nCntPlayer].Movetype);	//吹き出しの位置
				TexPoint(1, m_ResultChara[nCntPlayer].nPoint);						//数字座標設定
			}
			if (nCntRankPos[0] == 1)
			{
				fPosX = 70;
				Set2DUI(nCntPlayer, 0);
				SetNumCallout(nCntPlayer, 0, m_ResultChara[nCntPlayer].Movetype);	
				TexPoint(0, m_ResultChara[nCntPlayer].nPoint);						//数字座標設定
			}
			if (nCntRankPos[0] == 2)
			{
				fPosX = -12;
				Set2DUI(nCntPlayer, 2);
				SetNumCallout(nCntPlayer, 2, m_ResultChara[nCntPlayer].Movetype);	//吹き出しの位置
				TexPoint(2, m_ResultChara[nCntPlayer].nPoint);						//数字座標設定
			}
			if (nCntRankPos[0] == 3)
			{
				fPosX = -52;
				Set2DUI(nCntPlayer, 3);
				SetNumCallout(nCntPlayer, 3, m_ResultChara[nCntPlayer].Movetype);	//吹き出しの位置
				TexPoint(3, m_ResultChara[nCntPlayer].nPoint);						//数字座標設定
			}
			RankPos = D3DXVECTOR3(fPosX, 30.0f, 0.0f);
			nCntRankPos[0]++;
			break;
		case 2:
			if (nCntRankPos[1] == 0)
			{
				fPosX = 70;
				Set2DUI(nCntPlayer, 0);
				SetNumCallout(nCntPlayer, 0, m_ResultChara[nCntPlayer].Movetype);	//吹き出しの位置
				TexPoint(0, m_ResultChara[nCntPlayer].nPoint);						//数字座標設定
			}
			if (nCntRankPos[1] == 1)
			{
				fPosX = -12;
				Set2DUI(nCntPlayer, 2);
				SetNumCallout(nCntPlayer, 2, m_ResultChara[nCntPlayer].Movetype);	//吹き出しの位置
				TexPoint(2, m_ResultChara[nCntPlayer].nPoint);						//数字座標設定
			}
			if (nCntRankPos[1] == 2)
			{
				fPosX = -52;
				Set2DUI(nCntPlayer, 3);
				SetNumCallout(nCntPlayer, 3, m_ResultChara[nCntPlayer].Movetype);	//吹き出しの位置
				TexPoint(3, m_ResultChara[nCntPlayer].nPoint);						//数字座標設定
			}
			RankPos = D3DXVECTOR3(fPosX, 20.0f, 0.0f);
			nCntRankPos[1]++;
			break;
		case 3:
			if (nCntRankPos[2] == 0)
			{
				fPosX = -12;
				Set2DUI(nCntPlayer, 2);
				SetNumCallout(nCntPlayer, 2, m_ResultChara[nCntPlayer].Movetype);	//吹き出しの位置
				TexPoint(2, m_ResultChara[nCntPlayer].nPoint);						//数字座標設定
			}
			if (nCntRankPos[2] == 1)
			{
				fPosX = -52;
				Set2DUI(nCntPlayer, 3);
				SetNumCallout(nCntPlayer, 3, m_ResultChara[nCntPlayer].Movetype);	//吹き出しの位置
				TexPoint(3, m_ResultChara[nCntPlayer].nPoint);						//数字座標設定
			}
			RankPos = D3DXVECTOR3(fPosX, 20.0f, 0.0f);
			nCntRankPos[2]++;
			break;
		case 4:
			RankPos = POS_4TH;
			Set2DUI(nCntPlayer, 3);
			SetNumCallout(nCntPlayer, 3, m_ResultChara[nCntPlayer].Movetype);	//吹き出しの位置
			TexPoint(3, m_ResultChara[nCntPlayer].nPoint);							//数字座標設定
			break;
		}

		if (m_pPlayer[nCntPlayer] != NULL)
		{
			m_pPlayer[nCntPlayer]->Set(RankPos, CCharaBase::MOVETYPE_RANKING_CHARA, nCntPlayer, m_ResultChara[nCntPlayer].type);
			m_pPlayer[nCntPlayer]->SetMotion(CPlayer::MOTION_UPPER_NEUTRAL, CPlayer::UPPER_BODY);
			m_pPlayer[nCntPlayer]->SetMotion(CPlayer::MOTION_LOWER_NEUTRAL, CPlayer::LOWER_BODY);
		}

		/* 数字の生成 */
		RankTex(nCntPlayer, m_ResultChara[nCntPlayer].nNumRank - 1);
		PLNumTex(nCntPlayer, m_ResultChara[nCntPlayer].type, m_ResultChara[nCntPlayer].Movetype);
	}
#endif
	//カメラの設定
	CCameraManager *pCameraManager = CManager::GetCameraManager();
	pCameraManager->CreateCamera("RESULT_CAMERA",CCamera::TYPE_SPECTOR,D3DXVECTOR3(7.0f, 30.0f, 130.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 135.0f);
	pCameraManager->SetCameraViewPort("RESULT_CAMERA", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	CCamera *pCamera = pCameraManager->GetCamera("RESULT_CAMERA");
	if (pCamera != NULL)
	{
		pCamera->SetPosR(D3DXVECTOR3(7.0f, 50.0f, 0.0f));
	}

	//ライト設定
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		if (m_pSpotLight[nCnt] == NULL)
		{
			m_pSpotLight[nCnt] = CSpotLight::Create(nCnt,D3DXVECTOR3(m_pPlayer[nCnt]->GetPosition().x, m_pPlayer[nCnt]->GetPosition().y + 60.0f, m_pPlayer[nCnt]->GetPosition().z),
				SPOTLIGHT_DIRECTION, SPOTLIGHT_DEFFUSE, SPOTLIGHT_AMBIENT, SPOTLIGHT_SPECULAR, 0.0f, 0.0f, 0.0f, 800.0f, SPOTLIGHT_FALLOFF, D3DXToRadian(30.0f), D3DXToRadian(50.0f));
			if (m_ResultChara[nCnt].nNumRank != 1)
			{//一位以外だったらライトをつけてない状態にする
				m_pSpotLight[nCnt]->SetLightEnable(nCnt, FALSE);
			}
		}
	}
	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CResult::Uninit(void)
{
	//メニューの破棄
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

	//ナンバーの破棄
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
		if (m_apPlayerIcon[nCntPlayer] != NULL)
		{//プレイヤーアイコン
			m_apPlayerIcon[nCntPlayer]->Uninit();
			m_apPlayerIcon[nCntPlayer] = NULL;
		}
		if (m_apRanking[nCntPlayer] != NULL)
		{//順位
			m_apRanking[nCntPlayer]->Uninit();
			m_apRanking[nCntPlayer] = NULL;
		}
		if (m_apPlayerNum[nCntPlayer] != NULL)
		{//プレイヤー番号
			m_apPlayerNum[nCntPlayer]->Uninit();
			m_apPlayerNum[nCntPlayer] = NULL;
		}
		for (int nCntEff = 0; nCntEff < 2; nCntEff++)
		{
			if (m_apEffect[nCntPlayer][nCntEff] != NULL)
			{
				m_apEffect[nCntPlayer][nCntEff]->Uninit();
				m_apEffect[nCntPlayer][nCntEff] = NULL;
			}
		}
		if (m_pSpotLight[nCntPlayer] != NULL) 
		{ 
			m_pSpotLight[nCntPlayer]->SetLightEnable(nCntPlayer, false);//スポットライトを消す
			m_pSpotLight[nCntPlayer]->SpotLightDelete();				//スポットライト基準からディレクショナルライト基準へ切り替え
			m_pSpotLight[nCntPlayer]->Uninit();
			delete m_pSpotLight[nCntPlayer];
			m_pSpotLight[nCntPlayer] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < RESULTTYPE_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{//背景/演出系
			m_apScene2D[nCnt]->Uninit();
			m_apScene2D[nCnt] = NULL;
		}
	}
	for (int nCntM = 0; nCntM < MAX_MODEL; nCntM++)
	{//モデルの数
		if (m_apStadium[nCntM] != NULL)
		{
			m_apStadium[nCntM]->Uninit();
			m_apStadium[nCntM] = NULL;
		}
		for (int nCntS = 0; nCntS < MAX_STADIUMSTEP; nCntS++)
		{//スタジアムの段差の数
			for (int nCnt = 0; nCnt < MAX_AUDIENCE; nCnt++)
			{//観客の数
				if (m_apAudience[nCnt] != NULL)
				{
					m_apAudience[nCnt]->Uninit();
					m_apAudience[nCnt] = NULL;
				}
			}
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

	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		if (m_bEffectPro != true)
		{
			m_EffectState = EFFECTPRO_PATTURN1;
			m_bEffectPro = true;
		}
		//生成フラグを管理
		if (m_bMenuCreate == true)
		{
			if (m_bMenu == true)
			{
				m_pSeletMenu = CSelectMenu::Create(D3DXVECTOR3(530.0f, SCREEN_HEIGHT / 2, 0), 220, 320, CSelectMenu::MENU_TYPE::MENU_TYPE_RESULT);
				m_pSeletMenu->SetModeSelectBool(true);
				SetAlpha();
				m_bMenu = false;
			}
			// 以降の更新処理を飛ばす
			return;
		}

		//任意のキーENTER
		if (CCommand::GetCommand("DECISION"))
		{
			if (m_bMenuCreate == false)
			{
				if (m_bMenu == false)
				{
					m_bMenu = true;
					m_bMenuCreate = true;
				}
			}
		}
	}
	/* 演出処理関数呼び出し */
	EffectPro();

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
void CResult::SetRanking(int nNumPlayer, CPlayer::PLAYER_TYPE type, CCharaBase::CHARACTOR_MOVE_TYPE typeM, int nPoint)
{
	m_ResultChara[nNumPlayer].type = type;
	m_ResultChara[nNumPlayer].Movetype = typeM;
	m_ResultChara[nNumPlayer].nPoint = nPoint;
}

//=============================================================================
// テクスチャを設定
//=============================================================================
void CResult::TexPoint(int nPlayer, int nPoint)
{
	for (int nCntTime = 0; nCntTime < MAX_POINT; nCntTime++)
	{// テクスチャに反映
		if (m_apNumber[nPlayer][nCntTime] != NULL)
		{
			if (nCntTime > 1)
			{
				m_apNumber[nPlayer][nCntTime]->SetNumber(nPoint / 10);
			}
			else if (nCntTime == 1)
			{
				m_apNumber[nPlayer][nCntTime]->SetNumber(nPoint / 1);
			}
			if (nCntTime < 2)
			{	// ３桁まで
				m_apNumber[nPlayer][nCntTime]->SetSize(D3DXVECTOR2(30.0f, 30.0f),
					D3DXVECTOR2((TIMER_SPACE * nCntTime) + m_apScene2D[nPlayer + 1]->GetPosition().x + 40.0f, m_apScene2D[nPlayer + 1]->GetPosition().y));
				m_apNumber[nPlayer][nCntTime]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}
	}
}
//=============================================================================
// ポインタの初期化処理
//=============================================================================
void CResult::InitPointer(void)
{
	for (int nCnt = 0; nCnt < RESULTTYPE_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (m_apStadium[nCnt] != NULL)
		{
			m_apStadium[nCnt] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		for (int nCntP = 0; nCntP < MAX_POINT; nCntP++)
		{
			if (m_apNumber[nCnt][nCntP] != NULL)
			{
				m_apNumber[nCnt][nCntP] = NULL;
			}
		}
		if (m_apPlayerIcon[nCnt] != NULL)
		{
			m_apPlayerIcon[nCnt] = NULL;
		}
		if (m_apRanking[nCnt] != NULL)
		{
			m_apRanking[nCnt] = NULL;
		}
		if (m_apPlayerNum[nCnt] != NULL)
		{
			m_apPlayerNum[nCnt] = NULL;
		}
		for (int nCntEff = 0; nCntEff < 2; nCntEff++)
		{
			if (m_apEffect[nCnt][nCntEff] != NULL)
			{
				m_apEffect[nCnt][nCntEff] = NULL;
			}
		}
		if (m_pSpotLight[nCnt] != NULL) { m_pSpotLight[nCnt] = NULL; }
	}
	for (int nCntM = 0; nCntM < MAX_MODEL; nCntM++)
	{//モデルの数
		if (m_apStadium[nCntM] != NULL) { m_apStadium[nCntM] = NULL; }
		for (int nCntS = 0; nCntS < MAX_STADIUMSTEP; nCntS++)
		{//スタジアムの段差の数
			for (int nCnt = 0; nCnt < MAX_AUDIENCE; nCnt++)
			{
				if (m_apAudience[nCnt] != NULL) { m_apAudience[nCnt] = NULL; }
			}
		}
	}
}
//=============================================================================
// ポインタの初期化処理
//=============================================================================
void CResult::SetPolygon(void)
{
	m_apScene2D[RESULTTYPE_WINDOW] = CScene2D::Create(D3DXVECTOR3(SIZE_X, ((DEFAULT_SIZE*1.25f) / 2)+39.5f, 0.0f), "RANKING_WINDOW",1);
	m_apScene2D[RESULTTYPE_WINDOW]->SetWidthHeight(DEFAULT_SIZE*6.2f, DEFAULT_SIZE*1.2f);
#if 1
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		m_apPlayerIcon[nCnt] = CScene2D::Create(D3DXVECTOR3(CHARAICON_POS.x + (CHARAICON_INTERVAL*nCnt), CHARAICON_POS.y, CHARAICON_POS.z), "RANKCHARA_ICON", 2);
		m_apPlayerIcon[nCnt]->SetWidthHeight(DEFAULT_SIZE*0.55f, DEFAULT_SIZE*0.5f);
		m_apPlayerIcon[nCnt]->SetTex(D3DXVECTOR2(0.0f, 0.0f + ((1.0f / MAX_PLAYER)*nCnt)), D3DXVECTOR2(1.0f, (1.0f / MAX_PLAYER) + ((1.0f / MAX_PLAYER)*nCnt)));
		m_PlayerIconPos[nCnt] = m_apPlayerIcon[nCnt]->GetPosition();
		m_PlayerIconSize[nCnt].x = m_apPlayerIcon[nCnt]->GetSize(0);
		m_PlayerIconSize[nCnt].y = m_apPlayerIcon[nCnt]->GetSize(1);

		m_apPlayerNum[nCnt] = CScene2D::Create(D3DXVECTOR3(CHARAICON_POS.x + (CHARAICON_INTERVAL*nCnt), CHARAICON_POS.y, 0.0f), "RANK&PLNUM",5);
		m_apPlayerNum[nCnt]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*0.3f);
		m_apPlayerNum[nCnt]->SetTex(D3DXVECTOR2(0.5f, 0.0f + ((1.0f / MAX_PLAYER)* nCnt)), D3DXVECTOR2(1.0f, (1.0f / MAX_PLAYER) + ((1.0f / MAX_PLAYER)*nCnt)));
		m_PlayerNumPos[nCnt] = m_apPlayerNum[nCnt]->GetPosition();
		m_PlayerNumSize[nCnt].x = m_apPlayerNum[nCnt]->GetSize(0);
		m_PlayerNumSize[nCnt].y = m_apPlayerNum[nCnt]->GetSize(1);

		m_apRanking[nCnt] = CScene2D::Create(D3DXVECTOR3(CHARAICON_POS.x + (CHARAICON_INTERVAL*nCnt), CHARAICON_POS.y, 0.0f), "RANK&PLNUM",5);
		m_apRanking[nCnt]->SetWidthHeight(DEFAULT_SIZE*0.6f, DEFAULT_SIZE*0.3f);
		m_apRanking[nCnt]->SetTex(D3DXVECTOR2(0.0f, 0.0f + ((1.0f / MAX_PLAYER)*nCnt)), D3DXVECTOR2(0.5f, (1.0f / MAX_PLAYER) + ((1.0f / MAX_PLAYER)*nCnt)));
		m_RankPos[nCnt] = m_apRanking[nCnt]->GetPosition();
		m_RankIconSize[nCnt].x = m_apRanking[nCnt]->GetSize(0);
		m_RankIconSize[nCnt].y = m_apRanking[nCnt]->GetSize(1);
		for (int nCntEff = 0; nCntEff < 2; nCntEff++)
		{
			if (nCntEff == 0)
			{
				m_apEffect[nCnt][nCntEff] = CScene2D::Create(D3DXVECTOR3(m_apPlayerIcon[nCnt]->GetPosition().x - 60.0f,
					m_apPlayerIcon[nCnt]->GetPosition().y - 60.0f,
					m_apPlayerIcon[nCnt]->GetPosition().z), "RANKING_EFFECT", 4);
				m_apEffect[nCnt][nCntEff]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*0.5f);
			}
			else
			{
				m_apEffect[nCnt][nCntEff] = CScene2D::Create(D3DXVECTOR3(m_apPlayerIcon[nCnt]->GetPosition().x + 60.0f,
					m_apPlayerIcon[nCnt]->GetPosition().y + 60.0f,
					m_apPlayerIcon[nCnt]->GetPosition().z), "RANKING_EFFECT", 4);
				m_apEffect[nCnt][nCntEff]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*0.5f);
			}
			m_apEffect[nCnt][nCntEff]->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.5f, 0.0f));
			m_apEffect[nCnt][nCntEff]->SetAdd(true);
			m_RankEffect[nCnt][nCntEff] = m_apEffect[nCnt][nCntEff]->GetPosition();
		}
	}
	/* 数字の下のセリフ枠：左から並べる、並べ替えなし */
	m_apScene2D[RESULTTYPE_CALLOUT_1] = CScene2D::Create(D3DXVECTOR3(m_PlayerIconPos[0].x, m_PlayerIconPos[0].y, 0.0f), "RANKCHARA_CALLOUT", 2);
	m_apScene2D[RESULTTYPE_CALLOUT_1]->SetScene2DLeftCenter(D3DXVECTOR3(m_PlayerIconPos[0].x, m_PlayerIconPos[0].y, 0.0f), DEFAULT_SIZE*0.6f, DEFAULT_SIZE*0.3f);

	m_apScene2D[RESULTTYPE_CALLOUT_2] = CScene2D::Create(D3DXVECTOR3(m_PlayerIconPos[1].x, m_PlayerIconPos[1].y, 0.0f), "RANKCHARA_CALLOUT", 2);
	m_apScene2D[RESULTTYPE_CALLOUT_2]->SetScene2DLeftCenter(D3DXVECTOR3(m_PlayerIconPos[1].x, m_PlayerIconPos[1].y, 0.0f), DEFAULT_SIZE*0.6f, DEFAULT_SIZE*0.3f);

	m_apScene2D[RESULTTYPE_CALLOUT_3] = CScene2D::Create(D3DXVECTOR3(m_PlayerIconPos[2].x, m_PlayerIconPos[2].y, 0.0f), "RANKCHARA_CALLOUT", 2);
	m_apScene2D[RESULTTYPE_CALLOUT_3]->SetScene2DLeftCenter(D3DXVECTOR3(m_PlayerIconPos[2].x, m_PlayerIconPos[2].y, 0.0f), DEFAULT_SIZE*0.6f, DEFAULT_SIZE*0.3f);

	m_apScene2D[RESULTTYPE_CALLOUT_4] = CScene2D::Create(D3DXVECTOR3(m_PlayerIconPos[3].x, m_PlayerIconPos[3].y, 0.0f), "RANKCHARA_CALLOUT", 2);
	m_apScene2D[RESULTTYPE_CALLOUT_4]->SetScene2DLeftCenter(D3DXVECTOR3(m_PlayerIconPos[3].x, m_PlayerIconPos[3].y, 0.0f), DEFAULT_SIZE*0.6f, DEFAULT_SIZE*0.3f);

#endif
}
//=============================================================================
// モデルの設定処理
//=============================================================================
void CResult::SetModel(void)
{
	if (m_apStadium[0] == NULL)
	{//正面
		m_apStadium[0] = CSceneX::Create(DEFAULT_POS, DEFAULT_ROT, DEFAULT_SCALE, CLoad::MODEL_RANKINGSTADIUM, 0);
		m_apStadium[0]->SetScale(D3DXVECTOR3(1.2f, 1.5f, 1.0f));
		m_apStadium[0]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -120.0f));
		m_apStadium[0]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f));
	}
	if (m_apStadium[1] == NULL)
	{//右
		m_apStadium[1] = CSceneX::Create(DEFAULT_POS, DEFAULT_ROT, DEFAULT_SCALE, CLoad::MODEL_RANKINGSTADIUM, 0);
		m_apStadium[1]->SetScale(D3DXVECTOR3(1.2f, 1.5f, 1.0f));
		m_apStadium[1]->SetPosition(D3DXVECTOR3(-145.0f, 0.0f, -80.0f));
		m_apStadium[1]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI*-0.3f, 0.0f));
	}
	if (m_apStadium[2] == NULL)
	{//左
		m_apStadium[2] = CSceneX::Create(DEFAULT_POS, DEFAULT_ROT, DEFAULT_SCALE, CLoad::MODEL_RANKINGSTADIUM, 0);
		m_apStadium[2]->SetScale(D3DXVECTOR3(1.2f, 1.5f, 1.0f));
		m_apStadium[2]->SetPosition(D3DXVECTOR3(145.0f, 0.0f, -80.0f));
		m_apStadium[2]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI*-0.7f, 0.0f));
	}
	if (m_apStadium[3] == NULL)
	{//奥
		m_apStadium[3] = CSceneX::Create(DEFAULT_POS, DEFAULT_ROT, DEFAULT_SCALE, CLoad::MODEL_RANKINGSTADIUM, 0);
		m_apStadium[3]->SetScale(D3DXVECTOR3(6.0f, 5.0f, 1.0f));
		m_apStadium[3]->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -250.0f));
		m_apStadium[3]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI*-0.5f, 0.0f));
	}
}
//=============================================================================
// 観客の配置
//=============================================================================
void CResult::SetAudience(void)
{
	int nNum = 0;
	for (int nCnt = 0; nCnt < MAX_AUDIENCE; nCnt++)
	{
		if (nCnt < 5)
		{
			if (m_apAudience[nCnt] == NULL)
			{
				m_apAudience[nCnt] = CScene3D::Create(D3DXVECTOR3(m_apStadium[0]->GetPosition().x + (55.0f + (-AUDIENCE_INTERVAL*nCnt)),
					75.0f, m_apStadium[0]->GetPosition().z),
					"RANKING_AUDIENCE");
				m_apAudience[nCnt]->SetRot(D3DXVECTOR3(D3DX_PI*-0.5f, D3DX_PI, 0.0f));
			}
		}
		else if (nCnt >= 5 && nCnt < 10)
		{
			if (m_apAudience[nCnt] == NULL)
			{
				m_apAudience[nCnt] = CScene3D::Create(D3DXVECTOR3(m_apStadium[0]->GetPosition().x + (55.0f + (-AUDIENCE_INTERVAL*(nCnt - 5))),
					90.0f, m_apStadium[0]->GetPosition().z - 20.0f),
					"RANKING_AUDIENCE");
				m_apAudience[nCnt]->SetRot(D3DXVECTOR3(D3DX_PI*-0.5f, D3DX_PI, 0.0f));
			}
		}
		else if (nCnt >= 10 && nCnt < 15)
		{
			if (m_apAudience[nCnt] == NULL)
			{
				m_apAudience[nCnt] = CScene3D::Create(D3DXVECTOR3(m_apStadium[0]->GetPosition().x + (55.0f + (-AUDIENCE_INTERVAL*(nCnt - 10))),
					105.0f, m_apStadium[0]->GetPosition().z - 40.0f),
					"RANKING_AUDIENCE");
				m_apAudience[nCnt]->SetRot(D3DXVECTOR3(D3DX_PI*-0.5f, D3DX_PI, 0.0f));
			}
		}
		else if (nCnt >= 15 && nCnt < 18)
		{
			if (m_apAudience[nCnt] == NULL)
			{
				m_apAudience[nCnt] = CScene3D::Create(D3DXVECTOR3(m_apStadium[1]->GetPosition().x + (-3.0f+(22.0f*(nCnt - 15))),
					70.0f, m_apStadium[1]->GetPosition().z+(20.0f+(-20.0f*(nCnt - 15)))),
					"RANKING_AUDIENCE");
				m_apAudience[nCnt]->SetRot(D3DXVECTOR3(D3DX_PI*-0.5f, D3DX_PI*-0.8f, 0.0f));
			}
		}
		else if (nCnt >= 18 && nCnt < 21)
		{
			if (m_apAudience[nCnt] == NULL)
			{
				m_apAudience[nCnt] = CScene3D::Create(D3DXVECTOR3(m_apStadium[1]->GetPosition().x + (-18.0f + (22.0f*(nCnt - 18))),
					90.0f, (m_apStadium[1]->GetPosition().z-35.0f) +(20.0f + (-15.0f*(nCnt - 18)))),
					"RANKING_AUDIENCE");
				m_apAudience[nCnt]->SetRot(D3DXVECTOR3(D3DX_PI*-0.5f, D3DX_PI*-0.8f, 0.0f));
			}
		}
		else if (nCnt >= 21 && nCnt < 24)
		{
			if (m_apAudience[nCnt] == NULL)
			{
				m_apAudience[nCnt] = CScene3D::Create(D3DXVECTOR3(m_apStadium[2]->GetPosition().x + (20.0f+(-AUDIENCE_INTERVAL*(nCnt - 21))),
					70.0f, m_apStadium[2]->GetPosition().z + (10.0f + (-10.0f*(nCnt - 21)))),
					"RANKING_AUDIENCE");
				m_apAudience[nCnt]->SetRot(D3DXVECTOR3(D3DX_PI*-0.5f, D3DX_PI*0.8f, 0.0f));
			}
		}
		else if (nCnt >= 24 && nCnt < 27)
		{
			if (m_apAudience[nCnt] == NULL)
			{
				m_apAudience[nCnt] = CScene3D::Create(D3DXVECTOR3(m_apStadium[2]->GetPosition().x + (20.0f + (-AUDIENCE_INTERVAL*(nCnt - 24))),
					85.0f, (m_apStadium[2]->GetPosition().z - 25.0f) + (20.0f + (-5.0f*(nCnt - 24)))),
					"RANKING_AUDIENCE");
				m_apAudience[nCnt]->SetRot(D3DXVECTOR3(D3DX_PI*-0.5f, D3DX_PI*0.8f, 0.0f));
			}
		}
		if (m_apAudience[nCnt] != NULL)
		{
			nNum = rand() % 2 + 1;
			m_apAudience[nCnt]->SetSize(DEFAULT_SIZE*0.1f, DEFAULT_SIZE*0.1f);
			m_apAudience[nCnt]->SetAnimation(nNum, 0.5f, 1.0f);
			//αテストを適用する
			m_apAudience[nCnt]->SetAlphaTest(true);
		}
	}
}
//=============================================================================
// セレクトメニュー生成時の3Dポリゴンalpha値の設定
//=============================================================================
void CResult::SetAlpha(void)
{
	for (int nCnt = 0; nCnt < RESULTTYPE_MAX; nCnt++)
	{
		m_apScene2D[nCnt]->SetCol(D3DXCOLOR(m_apScene2D[nCnt]->GetCol().r, m_apScene2D[nCnt]->GetCol().g, m_apScene2D[nCnt]->GetCol().b, DEFAULT_COL_WHITE_ALPHA_HARF.a));
	}
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		m_apPlayerIcon[nCnt]->SetCol(DEFAULT_COL_WHITE_ALPHA_HARF);
		m_apPlayerNum[nCnt]->SetCol(DEFAULT_COL_WHITE_ALPHA_HARF);
		m_apRanking[nCnt]->SetCol(DEFAULT_COL_WHITE_ALPHA_HARF);
		for (int nCntTime = 0; nCntTime < MAX_POINT; nCntTime++)
		{
			m_apNumber[nCnt][nCntTime]->SetCol(DEFAULT_COL_WHITE_ALPHA_HARF);
		}
	}
}
//=============================================================================
// 2DUIの設定
//=============================================================================
void  CResult::Set2DUI(int nNum, int nPosNum)
{
	if (m_apRanking[nNum] != NULL)
	{/*ランクの位置と大きさ*/
		m_apRanking[nNum]->SetPos(D3DXVECTOR3(m_RankPos[nPosNum].x, m_RankPos[nPosNum].y - m_PlayerIconSize[nNum].y, m_RankPos[nPosNum].z),
			0.0f, 1.0f, DEFAULT_COL_WHITE);
	}
	if (m_apPlayerNum[nNum] != NULL)
	{/*PL番号の位置と大きさ*/
		m_apPlayerNum[nNum]->SetPos(D3DXVECTOR3(m_PlayerNumPos[nPosNum].x, m_PlayerNumPos[nPosNum].y + m_PlayerIconSize[nNum].y, m_PlayerNumPos[nPosNum].z),
			0.0f, 1.0f, DEFAULT_COL_WHITE);
	}
	if (m_apPlayerIcon[nNum] != NULL)
	{/*キャラアイコンの位置と大きさ*/
		m_apPlayerIcon[nNum]->SetPos(D3DXVECTOR3(m_PlayerIconPos[nPosNum].x, m_PlayerIconPos[nPosNum].y, m_PlayerIconPos[nPosNum].z),
			0.0f, 1.0f, DEFAULT_COL_WHITE);
	}
	for (int nCntEff = 0; nCntEff < 2; nCntEff++)
	{
		if (m_apEffect[nNum][nCntEff] != NULL)
		{/*エフェクト*/
			m_apEffect[nNum][nCntEff]->SetPosition(m_RankEffect[nPosNum][nCntEff]);
			m_apEffect[nNum][nCntEff]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*0.5f);
			m_apEffect[nNum][nCntEff]->SetbDraw(false);
		}
	}
	if (m_ResultChara[nNum].nNumRank == 1)
	{//1位の設定をするときのみ別処理をする
		if (m_apPlayerIcon[nNum] != NULL)
		{
			m_apPlayerIcon[nNum]->SetWidthHeight(DEFAULT_SIZE*0.75f, DEFAULT_SIZE*0.75f);
			m_PlayerIconSize[nPosNum].x = m_apPlayerIcon[nNum]->GetSize(0);
		}
		if (m_apRanking[nNum] != NULL)
		{
			m_apRanking[nNum]->SetPosition(D3DXVECTOR3(m_RankPos[nPosNum].x, m_RankPos[nPosNum].y - (m_apPlayerIcon[nNum]->GetSize(1) - 20.0f), m_RankPos[nPosNum].z));
			m_apRanking[nNum]->SetWidthHeight(DEFAULT_SIZE*0.7f, DEFAULT_SIZE*0.4f);
		}
		for (int nCntEff = 0; nCntEff < 2; nCntEff++)
		{
			if (m_apEffect[nNum][nCntEff] != NULL) { m_apEffect[nNum][nCntEff]->SetbDraw(true); }
		}
	}
}
//=============================================================================
// 順位のテクスチャ座標設定
//=============================================================================
void CResult::RankTex(int nNum, int nRank)
{
	if (m_apRanking[nNum] != NULL)
	{
		m_apRanking[nNum]->SetTex(D3DXVECTOR2(0.0f, 0.0f + ((1.0f / MAX_PLAYER)*nRank)),
			D3DXVECTOR2(0.5f, (1.0f / MAX_PLAYER) + ((1.0f / MAX_PLAYER)*nRank)));
	}
}
//=============================================================================
// キャラアイコンのテクスチャ管理
//=============================================================================
void CResult::PLNumTex(int nNum, int nChara,CCharaBase::CHARACTOR_MOVE_TYPE type)
{
	switch (type)
	{
	case CCharaBase::MOVETYPE_PLAYER_INPUT:
		if (m_apPlayerIcon[nNum] != NULL)
		{
			m_apPlayerIcon[nNum]->SetTex(D3DXVECTOR2(0.0f, 0.0f + ((1.0f / MAX_PLAYER)*nChara)),
				D3DXVECTOR2(1.0f, (1.0f / MAX_PLAYER) + ((1.0f / MAX_PLAYER)*nChara)));
		}
		if (m_apPlayerNum[nNum] != NULL)
		{
			m_apPlayerNum[nNum]->SetTex(D3DXVECTOR2(0.5f, 0.0f + ((1.0f / MAX_PLAYER)*nNum)),
				D3DXVECTOR2(1.0f, (1.0f / MAX_PLAYER) + ((1.0f / MAX_PLAYER)*nNum)));
		}
		break;
	case CCharaBase::MOVETYPE_NPC_AI:
		if (m_apPlayerIcon[nNum] != NULL)
		{
			m_apPlayerIcon[nNum]->SetTex(D3DXVECTOR2(0.0f, 0.0f + ((1.0f / MAX_PLAYER)*nChara)),
				D3DXVECTOR2(1.0f, (1.0f / MAX_PLAYER) + ((1.0f / MAX_PLAYER)*nChara)));
		}
		if (m_apPlayerNum[nNum] != NULL)
		{
			m_apPlayerNum[nNum]->BindTexture("RANKCHARA_PLNUM_COM");
			m_apPlayerNum[nNum]->SetTex(D3DXVECTOR2(0.0f, 0.0f + ((1.0f / 3)*nNum)),
				D3DXVECTOR2(1.0f, (1.0f / 3) + ((1.0f / 3)*nNum)));
		}
	}
}
//=============================================================================
// 数字出す吹き出しの設定
//=============================================================================
void CResult::SetNumCallout(int nNum,int nIconPos, CCharaBase::CHARACTOR_MOVE_TYPE type)
{
	switch (type)
	{
	case CCharaBase::MOVETYPE_PLAYER_INPUT:
		switch (nNum)
		{//数字の窓枠の色
		case 0:
			if (m_apScene2D[RESULTTYPE_CALLOUT_2] != NULL)
			{
				m_apScene2D[RESULTTYPE_CALLOUT_2]->SetCol(DEFAULT_COL_PL1);
				m_apScene2D[RESULTTYPE_CALLOUT_2]->SetScene2DLeftCenter(D3DXVECTOR3(m_PlayerIconPos[nIconPos].x+(m_PlayerIconSize[nIconPos].x/2) , m_PlayerIconPos[nIconPos].y, 0.0f), DEFAULT_SIZE*0.7f, DEFAULT_SIZE*0.2f);
			}
			break;
		case 1:
			if (m_apScene2D[RESULTTYPE_CALLOUT_1] != NULL)
			{
				m_apScene2D[RESULTTYPE_CALLOUT_1]->SetCol(DEFAULT_COL_PL2);
				m_apScene2D[RESULTTYPE_CALLOUT_1]->SetScene2DLeftCenter(D3DXVECTOR3(m_PlayerIconPos[nIconPos].x + (m_PlayerIconSize[nIconPos].x / 2), m_PlayerIconPos[nIconPos].y, 0.0f), DEFAULT_SIZE*0.7f, DEFAULT_SIZE*0.2f);
			}
			break;
		case 2:
			if (m_apScene2D[RESULTTYPE_CALLOUT_3] != NULL)
			{
				m_apScene2D[RESULTTYPE_CALLOUT_3]->SetCol(DEFAULT_COL_PL3);
				m_apScene2D[RESULTTYPE_CALLOUT_3]->SetScene2DLeftCenter(D3DXVECTOR3(m_PlayerIconPos[nIconPos].x + (m_PlayerIconSize[nIconPos].x / 2), m_PlayerIconPos[nIconPos].y, 0.0f), DEFAULT_SIZE*0.7f, DEFAULT_SIZE*0.2f);
			}
			break;
		case 3:
			if (m_apScene2D[RESULTTYPE_CALLOUT_4] != NULL)
			{
				m_apScene2D[RESULTTYPE_CALLOUT_4]->SetCol(DEFAULT_COL_PL4);
				m_apScene2D[RESULTTYPE_CALLOUT_4]->SetScene2DLeftCenter(D3DXVECTOR3(m_PlayerIconPos[nIconPos].x + (m_PlayerIconSize[nIconPos].x / 2), m_PlayerIconPos[nIconPos].y, 0.0f), DEFAULT_SIZE*0.7f, DEFAULT_SIZE*0.2f);
			}
			break;
		}
		break;
	case CCharaBase::MOVETYPE_NPC_AI:
		switch (nNum)
		{//数字の窓枠の色
		case 0:
			if (m_apScene2D[RESULTTYPE_CALLOUT_2] != NULL)
			{
				m_apScene2D[RESULTTYPE_CALLOUT_2]->SetCol(DEFAULT_COL_COM);
				m_apScene2D[RESULTTYPE_CALLOUT_2]->SetScene2DLeftCenter(D3DXVECTOR3(m_PlayerIconPos[nIconPos].x + (m_PlayerIconSize[nIconPos].x / 2), m_PlayerIconPos[nIconPos].y, 0.0f), DEFAULT_SIZE*0.7f, DEFAULT_SIZE*0.2f);
			}
			break;
		case 1:
			if (m_apScene2D[RESULTTYPE_CALLOUT_1] != NULL)
			{
				m_apScene2D[RESULTTYPE_CALLOUT_1]->SetCol(DEFAULT_COL_COM);
				m_apScene2D[RESULTTYPE_CALLOUT_1]->SetScene2DLeftCenter(D3DXVECTOR3(m_PlayerIconPos[nIconPos].x + (m_PlayerIconSize[nIconPos].x / 2), m_PlayerIconPos[nIconPos].y, 0.0f), DEFAULT_SIZE*0.7f, DEFAULT_SIZE*0.2f);
			}
			break;
		case 2:
			if (m_apScene2D[RESULTTYPE_CALLOUT_3] != NULL)
			{
				m_apScene2D[RESULTTYPE_CALLOUT_3]->SetCol(DEFAULT_COL_COM);
				m_apScene2D[RESULTTYPE_CALLOUT_3]->SetScene2DLeftCenter(D3DXVECTOR3(m_PlayerIconPos[nIconPos].x + (m_PlayerIconSize[nIconPos].x / 2), m_PlayerIconPos[nIconPos].y, 0.0f), DEFAULT_SIZE*0.7f, DEFAULT_SIZE*0.2f);
			}
			break;
		case 3:
			if (m_apScene2D[RESULTTYPE_CALLOUT_4] != NULL)
			{
				m_apScene2D[RESULTTYPE_CALLOUT_4]->SetCol(DEFAULT_COL_COM);
				m_apScene2D[RESULTTYPE_CALLOUT_4]->SetScene2DLeftCenter(D3DXVECTOR3(m_PlayerIconPos[nIconPos].x + (m_PlayerIconSize[nIconPos].x / 2), m_PlayerIconPos[nIconPos].y, 0.0f), DEFAULT_SIZE*0.7f, DEFAULT_SIZE*0.2f);
			}
			break;
		}
		break;
	}
}
//=============================================================================
// エフェクトの演出処理
//=============================================================================
void CResult::EffectPro(void)
{
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		if (m_apEffect[nCnt][0] != NULL&&m_apEffect[nCnt][1] != NULL)
		{
			if (m_apEffect[nCnt][0]->GetbDraw() == true && m_apEffect[nCnt][1]->GetbDraw() == true)
			{
				switch (m_EffectState)
				{
				case EFFECTPRO_NONE:
					break;
				case EFFECTPRO_PATTURN1:
					if (m_EffectAlpha.x <= -0.5f&&m_EffectAlpha.y >= 1.5f)
					{
						m_EffectAlpha.x = -0.5f;
						m_EffectAlpha.y = 1.5f;
						m_EffectState = EFFECTPRO_PATTURN2;
					}
					else
					{
						m_apEffect[nCnt][0]->SetCol(D3DXCOLOR(m_apEffect[nCnt][0]->GetCol().r, m_apEffect[nCnt][0]->GetCol().g, m_apEffect[nCnt][0]->GetCol().b, m_EffectAlpha.x));
						m_apEffect[nCnt][1]->SetCol(D3DXCOLOR(m_apEffect[nCnt][1]->GetCol().r, m_apEffect[nCnt][1]->GetCol().g, m_apEffect[nCnt][1]->GetCol().b, m_EffectAlpha.y));
					}
					break;
				case EFFECTPRO_PATTURN2:
					if (m_EffectAlpha.x >= 1.5f&&m_EffectAlpha.y <= -0.5f)
					{
						m_EffectAlpha.x = 1.5f;
						m_EffectAlpha.y = -0.5f;
						m_EffectState = EFFECTPRO_PATTURN1;
					}
					else
					{
						m_apEffect[nCnt][0]->SetCol(D3DXCOLOR(m_apEffect[nCnt][0]->GetCol().r, m_apEffect[nCnt][0]->GetCol().g, m_apEffect[nCnt][0]->GetCol().b, m_EffectAlpha.x));
						m_apEffect[nCnt][1]->SetCol(D3DXCOLOR(m_apEffect[nCnt][1]->GetCol().r, m_apEffect[nCnt][1]->GetCol().g, m_apEffect[nCnt][1]->GetCol().b, m_EffectAlpha.y));
					}

					break;
				}

			}
		}
	}
	switch (m_EffectState)
	{
	case EFFECTPRO_NONE:
		break;
	case EFFECTPRO_PATTURN1:
		m_EffectAlpha.x -= 0.05f;
		m_EffectAlpha.y += 0.05f;
		break;
	case EFFECTPRO_PATTURN2:
		m_EffectAlpha.x += 0.05f;
		m_EffectAlpha.y -= 0.05f;
		break;
	}
}