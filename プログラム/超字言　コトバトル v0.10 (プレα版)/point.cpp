//=============================================================================
//
// タイマー処理 [time.cpp]
// Author : keisuke komatsu
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "point.h"
#include "number.h"
#include "game.h"
#include "fade.h"
#include "player.h"
#include "scene2D.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define CENTER_WIDTH		(SCREEN_WIDTH / 2)				// Xの中心座標
#define TIMER_SPACE			(30.0f)							// 数字と数字の間のサイズ(ゲーム時間)
#define TIMER_POSITION_Y	(70.0f)							// タイマーのY座標(ゲーム時間)
#define POWER_X				(10)
#define POINT_POS_1P_ONE	(D3DXVECTOR3(170.0f, 60.0f, 0.0f))	// 制限時間の位置(1Pだけの場合)
#define POINT_POS_2P_ONE	(D3DXVECTOR3(450.0f, 60.0f, 0.0f))	// 制限時間の位置(1Pだけの場合)
#define POINT_POS_3P_ONE	(D3DXVECTOR3(930.0f, 60.0f, 0.0f))	// 制限時間の位置(1Pだけの場合)
#define POINT_POS_4P_ONE	(D3DXVECTOR3(1210.0f, 60.0f, 0.0f))	// 制限時間の位置(1Pだけの場合)
#define POINT_POS_2P_TWO	(D3DXVECTOR3(170.0f, 430.0f, 0.0f))	// 制限時間の位置(2 ～ 4画面だけの場合)
#define POINT_POS_4P_TWO	(D3DXVECTOR3(1210.0f, 430.0f, 0.0f))// 制限時間の位置(2 ～ 4画面だけの場合)

#define WAIT_TIME_END		(180)							// 待ち時間
#define MAX_POINT			(99)							// 最大数
#define DEFAULT_SIZE		(D3DXVECTOR2(25.0f, 30.0f))		// デフォルトのサイズ (数字)
#define	MAX_SIZE			(D3DXVECTOR2(40.0f, 50.0f))		// 最大のサイズ (数字)
//=============================================================================
//	静的メンバ変数
//=============================================================================

//=============================================================================
// 生成処理
//=============================================================================
CPoint *CPoint::Create(int nID, int nNumPlayer, TYPE_CHARACTER type)
{
	CPoint *pPoint = NULL;

	//NULLチェック
	if (pPoint == NULL)
	{//動的確保
		pPoint = new CPoint;

		//NULLチェック
		if (pPoint != NULL)
		{
			pPoint->PointPostion(nNumPlayer, nID);	// ポイントの位置まとめ
			pPoint->m_type = type;		// 種類を代入
			pPoint->m_nNumPlayer = nNumPlayer;		// 人数を取得
			pPoint->m_nID = nID;
			//初期化処理
			pPoint->Init();
		}
	}

	return pPoint;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CPoint::CPoint(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	m_nPointNum = 1;
	m_bStart = false;
	m_pIcon = NULL;
	m_nID = 0;
	m_type = TYPE_NONE;
	m_bSizeChange = false;
	m_bChangeFlag = false;
	m_bColChange = false;
	m_bFlag = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPoint::~CPoint() {}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPoint::Init(void)
{
	int nTexData = 0;
	m_nTotalPoint = 0;
	m_nPointNum = PowerCalculation(m_nTotalPoint);

	PointBGCreate();		// ポイントの背景生成

	for (int nCntPoint = 0; nCntPoint < MAX_POINT_NUM; nCntPoint++)
	{	// ポイント初期設定
		m_apNumber[nCntPoint] = new CNumber;
		m_apNumber[nCntPoint]->Init(D3DXVECTOR3((m_pos.x - TIMER_SPACE * nCntPoint), m_pos.y, m_pos.z), 0);
		m_apNumber[nCntPoint]->SetSize(D3DXVECTOR2(25.0f, 30.0f), D3DXVECTOR2((m_pos.x - TIMER_SPACE * nCntPoint), m_pos.y));
		m_apNumber[nCntPoint]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	// 数字のテクスチャ設定
	TexPoint(nTexData);

	// UIの生成設定
	UIPosition();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPoint::Uninit(void)
{
	for (int nCntPoint = 0; nCntPoint < MAX_POINT_NUM; nCntPoint++)
	{	// タイマーの破棄
		if (m_apNumber[nCntPoint] != NULL)
		{
			m_apNumber[nCntPoint]->Uninit();
			m_apNumber[nCntPoint] = NULL;
		}
	}

	if (m_pIcon != NULL)
	{
		m_pIcon->Uninit();
		m_pIcon = NULL;
	}

	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPoint::Update(void)
{
	//現在のモードの取得
	CManager::MODE GameMode = CManager::GetMode();
	DebugKey();		// デバック用

	if ((GameMode == CManager::MODE_GAME) || (GameMode == CManager::MODE_TUTORIAL))
	{//制限時間
	 //ゲーム
		int nTexData = 0;
		// 数字のテクスチャ設定
		TexPoint(nTexData);
		
		// ポイント増減時の変化
		SizeChange();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CPoint::Draw(void)
{
	for (int nCntPoint = 0; nCntPoint < m_nPointNum; nCntPoint++)
	{
		if (m_apNumber[nCntPoint] != NULL)
		{
			m_apNumber[nCntPoint]->Draw();
		}
	}

	if (m_pIcon != NULL)
	{
		m_pIcon->Draw();
	}
}

//=============================================================================
// タイマーのTexture管理
//=============================================================================
void CPoint::TexPoint(int nTexData)
{
	nTexData = m_nTotalPoint;

	for (int nCntPoint = 0; nCntPoint < m_nPointNum; nCntPoint++)
	{// テクスチャに反映
		if (m_apNumber[nCntPoint] != NULL)
		{
			m_apNumber[nCntPoint]->SetNumber(nTexData);
			nTexData /= 10;
		}
	}
}
//=============================================================================
// タイム加算処理
//=============================================================================
void CPoint::AddPoint(int nPoint)
{
	if (m_nTotalPoint < MAX_POINT)
	{
		m_nTotalPoint += nPoint;
	}

	if (MAX_POINT < m_nTotalPoint) { m_nTotalPoint = MAX_POINT; }
	m_nPointNum = PowerCalculation(m_nTotalPoint);
	m_bSizeChange = true;
	m_bFlag = false;
	for (int nCntPoint = 0; nCntPoint < m_nPointNum; nCntPoint++)
	{// テクスチャに反映
		if (m_apNumber[nCntPoint] != NULL)
		{
			m_apNumber[nCntPoint]->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}
}
//=============================================================================
// タイム減算処理
//=============================================================================
void CPoint::SubtractionPoint(int nPoint)
{
	if (m_nTotalPoint < MAX_POINT)
	{
		m_nTotalPoint -= nPoint;
	}

	if (0 > m_nTotalPoint) { m_nTotalPoint = 0; }
	m_nPointNum = PowerCalculation(m_nTotalPoint);
	m_bSizeChange = true;
	m_bFlag = true;
	for (int nCntPoint = 0; nCntPoint < m_nPointNum; nCntPoint++)
	{// テクスチャに反映
		if (m_apNumber[nCntPoint] != NULL)
		{
			m_apNumber[nCntPoint]->SetCol(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
		}
	}
}

//=============================================================================
// べき乗の計算
//=============================================================================
int CPoint::PowerCalculation(int nData)
{
	int nNum = 1;
	int nPower = (int)std::pow(POWER_X, nNum);
	int nDataNum = nData;
	while ((nDataNum / nPower) != 0)
	{
		nNum++;
		nPower = (int)std::pow(POWER_X, nNum);		// べき乗する(二乗や三乗など)
		if (nNum >= MAX_POINT_NUM) { nNum = MAX_POINT_NUM; }
	}
	return nNum;
}

//=============================================================================
// 時間の管理
//=============================================================================
void CPoint::TimeManagement(void)
{
	
}
//=============================================================================
// デバック用
//=============================================================================
void CPoint::DebugKey(void)
{
	
}

//=============================================================================
// ポイントの背景生成
//=============================================================================
void CPoint::PointBGCreate(void)
{
	CScene2D *pBg = NULL;

	BGPosition(pBg);
}

//=============================================================================
// 背景の位置設定
//=============================================================================
void CPoint::BGPosition(CScene2D *pBg)
{
	// 人数が指定数内 かつ プレイヤーIDが指定した番号の場合
	if (m_nNumPlayer != 2 && m_nID == 0)
	{	// 画面左上 (1, 3, 4画面 1P)の位置
		pBg = CScene2D::Create(D3DXVECTOR3(120.0f, 40.0f, 0.0f), "BG_FREAME", 5);
	}
	else if (m_nNumPlayer == 1 && m_nID == 3 || m_nNumPlayer > 2 && m_nNumPlayer <= MAX_PLAYER && m_nID == 1)
	{	// 画面右上 (1画面 4P , 3～4画面 2P)の位置
		pBg = CScene2D::Create(D3DXVECTOR3(1160.0f, 40.0f, 0.0f), "BG_FREAME", 5);
	}
	else if (m_nID == 1&& m_nNumPlayer == 1)
	{	// 画面左上 (1画面 2P)の位置
		pBg = CScene2D::Create(D3DXVECTOR3(400.0f, 40.0f, 0.0f), "BG_FREAME", 5);
	}
	else if (m_nID == 2 && m_nNumPlayer == 1)
	{	// 画面右上 (1画面 3P)の位置
		pBg = CScene2D::Create(D3DXVECTOR3(880.0f, 40.0f, 0.0f), "BG_FREAME", 5);
	}
	else if (m_nNumPlayer > 2 && m_nNumPlayer <= MAX_PLAYER && m_nID == 2)
	{	// 画面左 ( 3画面、4画面 3P)の位置
		pBg = CScene2D::Create(D3DXVECTOR3(120.0f, 408.0f, 0.0f), "BG_FREAME", 5);
	}
	else if (m_nNumPlayer > 2 && m_nNumPlayer <= MAX_PLAYER && m_nID == 3)
	{	// 画面右 (3画面 ～ 4画面 4P)の位置
		pBg = CScene2D::Create(D3DXVECTOR3(1160.0f, 408.0f, 0.0f), "BG_FREAME", 5);
	}
	else if (m_nNumPlayer == 2 && m_nID == 0)
	{	// 2画面 1P
		pBg = CScene2D::Create(D3DXVECTOR3(250.0f, 40.0f, 0.0f), "BG_FREAME", 5);
	}
	else if (m_nID == 1 && m_nNumPlayer == 2)
	{	// 2画面 2P
		pBg = CScene2D::Create(D3DXVECTOR3(250.0f, 408.0f, 0.0f), "BG_FREAME", 5);
	}
	else if (m_nID == 2 && m_nNumPlayer == 2)
	{	// 2画面 3P
		pBg = CScene2D::Create(D3DXVECTOR3(1020.0f, 40.0f, 0.0f), "BG_FREAME", 5);
	}
	
	else if (m_nID == 3 && m_nNumPlayer == 2)
	{	// 2画面 4P
		pBg = CScene2D::Create(D3DXVECTOR3(1020.0f, 408.0f, 0.0f), "BG_FREAME", 5);
	}
	

	if (pBg != NULL)
	{	// サイズと色の設定
		pBg->SetWidthHeight(100.0f, 60.0f);
		pBg->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

}

//=============================================================================
// UIの位置設定
//=============================================================================
void CPoint::UIPosition(void)
{
	char *cName[MAX_PLAYER] = { "キャラ(スピード)", "キャラ(バランス)", "キャラ(パワー)", "キャラ(リーチ)" };
	D3DXVECTOR3 posIcon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 posNumber = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 posLogo = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CScene2D *pNumber = NULL;

	// 人数が指定数内 かつ プレイヤーIDが指定した番号の場合
	if (m_nNumPlayer != 2 && m_nID == 0)
	{	// 1, 3, 4画面 1Pの位置
		posIcon = D3DXVECTOR3(85.0f, 55.0f, 0.0f);
		posNumber = D3DXVECTOR3(125.0f, 18.0f, 0.0f);
		posLogo = D3DXVECTOR3(165.0f, 12.0f, 0.0f);
	}
	else if (m_nID == 1 && m_nNumPlayer == 1)
	{	// 1画面 2Pの場合
		posIcon = D3DXVECTOR3(365.0f, 55.0f, 0.0f);
		posNumber = D3DXVECTOR3(405.0f, 18.0f, 0.0f);
		posLogo = D3DXVECTOR3(445.0f, 12.0f, 0.0f);
	}
	else if (m_nID == 2 && m_nNumPlayer == 1)
	{	// 1画面 3Pの場合
		posIcon = D3DXVECTOR3(845.0f, 55.0f, 0.0f);
		posNumber = D3DXVECTOR3(885.0f, 18.0f, 0.0f);
		posLogo = D3DXVECTOR3(925.0f, 12.0f, 0.0f);
	}
	else if (m_nID == 3 && m_nNumPlayer == 1 || m_nID == 1 && m_nNumPlayer == 3 || m_nID == 1 && m_nNumPlayer == 4)
	{	// 1画面 4P, 3画面 2P, 4画面 2Pの位置
		posIcon = D3DXVECTOR3(1125.0f, 55.0f, 0.0f);
		posNumber = D3DXVECTOR3(1165.0f, 18.0f, 0.0f);
		posLogo = D3DXVECTOR3(1205.0f, 12.0f, 0.0f);
	}
	else if (m_nID == 2 && m_nNumPlayer == 3 || m_nID == 2 && m_nNumPlayer == 4)
	{ // 3画面 3P, 4画面 3Pの位置
		posIcon = D3DXVECTOR3(85.0f, 425.0f, 0.0f);
		posNumber = D3DXVECTOR3(125.0f, 386.0f, 0.0f);
		posLogo = D3DXVECTOR3(165.0f, 380.0f, 0.0f);
	}
	else if  (m_nID == 3 && m_nNumPlayer == 3 || m_nID == 3 && m_nNumPlayer == 4)
	{	//  3画面 4P, 4画面 4Pの位置
		posIcon = D3DXVECTOR3(1125.0f, 425.0f, 0.0f);
		posNumber = D3DXVECTOR3(1165.0f, 386.0f, 0.0f);
		posLogo = D3DXVECTOR3(1205.0f, 380.0f, 0.0f);
	}

	else if (m_nNumPlayer == 2 && m_nID == 0)
	{	// 2画面 1P
		posIcon = D3DXVECTOR3(215.0f, 55.0f, 0.0f);
		posNumber = D3DXVECTOR3(255.0f, 18.0f, 0.0f);
		posLogo = D3DXVECTOR3(295.0f, 12.0f, 0.0f);
	}
	else if (m_nID == 1 && m_nNumPlayer == 2)
	{	// 2画面 2P
		posIcon = D3DXVECTOR3(215.0f, 425.0f, 0.0f);
		posNumber = D3DXVECTOR3(255.0f, 386.0f, 0.0f);
		posLogo = D3DXVECTOR3(295.0f, 380.0f, 0.0f);
	}
	else if (m_nID == 2 && m_nNumPlayer == 2)
	{	// 2画面 3P
		posIcon = D3DXVECTOR3(985.0f, 55.0f, 0.0f);
		posNumber = D3DXVECTOR3(1025.0f, 18.0f, 0.0f);
		posLogo = D3DXVECTOR3(1165.0f, 12.0f, 0.0f);
	}
	
	else if (m_nID == 3 && m_nNumPlayer == 2)
	{	// 2画面 4P
		posIcon = D3DXVECTOR3(985.0f, 425.0f, 0.0f);
		posNumber = D3DXVECTOR3(1025.0f, 386.0f, 0.0f);
		posLogo = D3DXVECTOR3(1165.0f, 380.0f, 0.0f);
	}
	

	// キャラクターアイコンのロゴ
	if (m_pIcon == NULL)
	{
		m_pIcon = CScene2D::Create(posIcon, cName[3], 6);
		m_pIcon->SetWidthHeight(40.0f, 30.0f);
		m_pIcon->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (m_type == CPoint::TYPE_CPU)
	{	// CPUの場合
		m_nID = 4;					// 自分の番号を5番に指定
	}

	// キャラクター番号の設
	pNumber = CScene2D::Create(posNumber, "プレイ人数", 6);
	pNumber->SetWidthHeight(60.0f, 20.0f);
	pNumber->SetTex(D3DXVECTOR2(0.0f, m_nID * 0.2f), D3DXVECTOR2(1.0f, (m_nID * 0.2f) + 0.2f));
	pNumber->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//=============================================================================
// ポイントの位置設定
//=============================================================================
void CPoint::PointPostion(int nNumPlayer, int nID)
{
	// 人数が指定数内 かつ プレイヤーIDが指定した番号の場合
	if (nNumPlayer != 2 && nID == 0)
	{	// 1, 3, 4画面 1Pの位置
		m_pos = POINT_POS_1P_ONE;
	}
	else if (nID == 1 && nNumPlayer == 1)
	{	// 1画面 2Pの場合
		m_pos = POINT_POS_2P_ONE;
	}
	else if (nID == 2 && nNumPlayer == 1)
	{	// 1画面 3Pの場合
		m_pos = POINT_POS_3P_ONE;
	}
	else if (nID == 3 && nNumPlayer == 1 || nID == 1 && nNumPlayer == 3 || nID == 1 && nNumPlayer == 4)
	{	// 1画面 4P, 3画面 2P, 4画面 2Pの位置
		m_pos = POINT_POS_4P_ONE;
	}
	else if ( nID == 2 && nNumPlayer == 3 || nID == 2 && nNumPlayer == 4)
	{ // 3画面 3P, 4画面 3Pの位置
		m_pos = POINT_POS_2P_TWO;
	}
	else if (nID == 3 && nNumPlayer == 3 || nID == 3 && nNumPlayer == 4)
	{	// 3画面 4P, 4画面 4Pの位置
		m_pos = POINT_POS_4P_TWO;
	}

	else if (nNumPlayer == 2 && nID == 0)
	{	// 2画面 1P
		m_pos = D3DXVECTOR3(POINT_POS_1P_ONE.x + 130.0f, POINT_POS_1P_ONE.y, POINT_POS_1P_ONE.z);
	}
	else if (nID == 1 && nNumPlayer == 2)
	{	// 2画面 2P
		m_pos = D3DXVECTOR3(POINT_POS_2P_TWO.x + 130.0f, POINT_POS_2P_TWO.y, POINT_POS_2P_TWO.z);
	}
	else if (nID == 2 && nNumPlayer == 2)
	{	// 2画面 3P
		m_pos = D3DXVECTOR3(POINT_POS_4P_ONE.x - 140.0f, POINT_POS_4P_ONE.y, POINT_POS_4P_ONE.z);
	}
	else if (nID == 3 && nNumPlayer == 2)
	{	// 2画面 4P
		m_pos = D3DXVECTOR3(POINT_POS_4P_TWO.x - 140.0f, POINT_POS_4P_TWO.y, POINT_POS_4P_TWO.z);
	}
}

//=============================================================================
// ポイント増減時のサイズ変化
//=============================================================================
void CPoint::SizeChange(void)
{
	if (m_bSizeChange == false) { return; }

	for (int nCntPoint = 0; nCntPoint < m_nPointNum; nCntPoint++)
	{
		if (m_apNumber[nCntPoint] != NULL)
		{
			if (m_bSizeChange == true) 
			{
				D3DXVECTOR2 size = m_apNumber[nCntPoint]->GetSize();
				D3DXCOLOR col = m_apNumber[nCntPoint]->GetCol();
				float fSizeChangeX = 1.5f;
				float fSizeChangeY = 1.0f;
				float fCol = 0.1f;

				if (m_bChangeFlag == false)
				{
					size.x += fSizeChangeX;
					size.y += fSizeChangeY;
				}
				else if (m_bChangeFlag == true)
				{
					size.x -= fSizeChangeX;
					size.y -= fSizeChangeY;
				}

				if (m_bColChange == false)
				{
					if (m_bFlag == false)
					{
						col.r -= fCol;
						if (col.r < 0.4) { col.r = 0.4f; m_bColChange = true; }
					}
					else if (m_bFlag == true)
					{
						col.b -= fCol;
						if (col.b < 0.4) { col.b = 0.4f; m_bColChange = true; }
					}
				}
				else if (m_bColChange == true)
				{
					if (m_bFlag == false)
					{
						col.r += fCol;
						if (col.r > 1.0) { col.r = 1.0f; m_bColChange = false; }
					}
					else if (m_bFlag == true)
					{
						col.b += fCol;
						if (col.b > 1.0) { col.b = 1.0f; m_bColChange = false; }
					}
				}

				if (size.x > MAX_SIZE.x && size.y > MAX_SIZE.y) { m_bChangeFlag = true; }
				else if (size.x < DEFAULT_SIZE.x && size.y < DEFAULT_SIZE.y) { m_bChangeFlag = false; m_bSizeChange = false; }

				m_apNumber[nCntPoint]->SetSize(size, m_apNumber[nCntPoint]->GetPos());
				m_apNumber[nCntPoint]->SetCol(col);
			}
		}
	}

	for (int nCntPoint = 0; nCntPoint < m_nPointNum; nCntPoint++)
	{
		if (m_apNumber[nCntPoint] != NULL)
		{
			if (m_bSizeChange == false) { m_apNumber[nCntPoint]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); }
		}
	}
}