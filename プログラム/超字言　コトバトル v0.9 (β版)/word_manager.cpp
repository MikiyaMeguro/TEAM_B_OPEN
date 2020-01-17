//=============================================================================
//
// 文字の管理処理 [word_manager.cpp]
// Author : 横道 駿
//
//=============================================================================
#include "word_manager.h"
#include "input.h"
#include "InputKeyboard.h"
#include "manager.h"
#include "sceneX.h"
#include "debugProc.h"
#include "game.h"
#include "SetWord.h"
#include "point.h"
#include "word.h"
#include "PlayerNumSelect.h"

#include "bullet.h"
#include "CameraManager.h"
#include "tutorial.h"

#include "sound.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define COL_1P	(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))		// 1Pカラー (赤)
#define COL_2P	(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f))		// 2Pカラー (青)
#define COL_3P	(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f))		// 3Pカラー	(緑)
#define COL_4P	(D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f))		// 4Pカラー	(オレンジ)
#define COL_CPU	(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f))		// CPUカラー(クレー)

//=============================================================================
// 静的メンバ変数
//=============================================================================
D3DXVECTOR3 *CWordManager::m_AnswerNum = &D3DXVECTOR3(NOT_NUM, NOT_NUM, NOT_NUM);
int CWordManager::m_nAnswerDataNum = 0;
D3DXVECTOR3 *CWordManager::m_Scale = &D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 *CWordManager::m_rot = &D3DXVECTOR3(0.0f, 0.0f, 0.0f);
int *CWordManager::m_type = 0;
int *CWordManager::m_nAnswerTypeModel = 0;
int *CWordManager::m_nPoint = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
CWordManager::CWordManager()
{
	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{	// 管理の中身を初期化
		m_aWord[nCntWord].nNum = EMPTINESS_NUM;
		m_aWord[nCntWord].cWord = "NULL";
		m_aWord[nCntWord].bClearFlag = false;

		m_nStock[nCntWord] = EMPTINESS_NUM;

	}
	m_nCntNum = 0;			// 回数のカウント
	m_nCreateType = NOT_NUM;// 生成するタイプ
	m_nCntaAnswer = 0;		// 正解との比較して合っている数
	m_nPlayerID = 0;		// プレイヤーが何番かの保存
	m_bPress = false;		// 指定した文字以上をいれないフラグ
	m_bSearch = false;		// サーチを開始する時のフラグ
	m_bFlag = false;
	m_bAnswerCheck = false;

	m_fAnswerData = NULL;
	m_Scale = NULL;
	m_type = NULL;
	m_nAnswerTypeModel = NULL;
	m_rot = NULL;
	m_nPoint = NULL;

	m_nCntStock = 0;
	m_bGatherFlag = false;
}
//=============================================================================
// デストラクタ
//=============================================================================
CWordManager::~CWordManager() {}

//=============================================================================
// 初期化処理
//=============================================================================
void CWordManager::Init()
{

}

//=============================================================================
// 終了処理
//=============================================================================
void CWordManager::Uninit(void)
{
	if (m_AnswerNum != NULL)
	{
		delete[] m_AnswerNum;
		m_AnswerNum = NULL;
	}

	if (m_fAnswerData != NULL && m_bSearch == true)
	{
		delete[] m_fAnswerData;
		m_fAnswerData = NULL;
	}

	if (m_Scale != NULL)
	{
		delete[] m_Scale;
		m_Scale = NULL;
	}

	if (m_rot != NULL)
	{
		delete[] m_rot;
		m_rot = NULL;
	}

	if (m_type != NULL)
	{
		delete[] m_type;
		m_type = NULL;
	}

	if (m_nAnswerTypeModel != NULL)
	{
		delete[] m_nAnswerTypeModel;
		m_nAnswerTypeModel = NULL;
	}

	if (m_nPoint != NULL)
	{
		delete[] m_nPoint;
		m_nPoint = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CWordManager::Update(void)
{
	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	CreateOblDebug();		// 数字で文字の管理(デバック用)

	if (CManager::GetWordCreate()->GetCreateFlag() == true)
	{
		m_bSearch = false;
		SearchWord();
		CManager::GetWordCreate()->SetCreateFlagr(false);
	}

	if (m_nCntNum != 2 && m_bSearch == true)
	{ // 持っている文字が2文字以外ならサーチのフラグを変更
		m_bSearch = false;
		UninitAssist();
		if (m_fAnswerData != NULL)
		{
			delete[] m_fAnswerData;
			m_fAnswerData = NULL;
		}
		//*m_fAnswerData = 99.0f;		// 空の番号をいれる
	}

	if (m_nCntNum == MAX_WORD)
	{	// 最大ならこれ以上数字をいれない
		m_bPress = true;
		m_bAnswerCheck = false;
	}

	if (m_bAnswerCheck == true && m_bPress == false)
	{
		//m_bAnswerCheck = false;
	}

	if (m_bPress == true && m_bAnswerCheck == false)
	{
		if (m_nCntaAnswer == 0)
		{
			for (int nCntAnswer = 0; nCntAnswer < m_nAnswerDataNum; nCntAnswer++)
			{	// 答えの数だけ回す
				for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
				{	// 答との比較
					if (m_AnswerNum[nCntAnswer].x == m_aWord[nCntWord].nNum && m_bAnswer[0] == false) { m_bAnswer[0] = true; }
					else if (m_AnswerNum[nCntAnswer].y == m_aWord[nCntWord].nNum && m_bAnswer[1] == false) { m_bAnswer[1] = true; }
					else if (m_AnswerNum[nCntAnswer].z == m_aWord[nCntWord].nNum && m_bAnswer[2] == false) { m_bAnswer[2] = true; }
				}

				if (m_bAnswer[0] == true && m_bAnswer[1] == true && m_bAnswer[2] == true) { m_nCntaAnswer = MAX_WORD; m_bFlag = false; }
				else if (m_nCntaAnswer < MAX_WORD)
				{
					for (int nCount = 0; nCount < MAX_WORD; nCount++)
					{
						m_bAnswer[nCount] = false;
						m_bFlag = true;
					}
				}

				if (m_nCntaAnswer == MAX_WORD)
				{
					m_nCntNum = 0;
					m_nCreateType = nCntAnswer;
					m_nStock[m_nCntStock] = nCntAnswer;
					if (CManager::GetTube(m_nPlayerID) != NULL)
					{
						CManager::GetTube(m_nPlayerID)->SetAnswer(nCntAnswer, m_nCntStock);
						CManager::GetTube(m_nPlayerID)->SetPoint(m_nPoint[m_nCreateType], m_nPlayerID, false);
						CManager::GetTube(m_nPlayerID)->SetStockNum(m_nCntStock);
					}

					m_nCntaAnswer = 0;
					m_nCntStock++;
					if (m_nCntStock >= MAX_WORD) { m_nCntStock = MAX_WORD;  m_bGatherFlag = true; }

					m_bAnswerCheck = true;
					return;
				}
				else { m_nCntaAnswer = 0; }
			}

			//if (m_nCreateType > m_nAnswerDataNum )
			//{
			//	if (CGame::GetTube(m_nPlayerID) != NULL)
			//	{
			//		CGame::GetTube(m_nPlayerID)->SetAnswer(NOT_NUM);
			//		//CGame::GetTube(m_nPlayerID)->SetPoint(-3, m_nPlayerID);
			//	}
			//}
		}

		//テスト
		//if (pInputKeyboard->GetTrigger(DIK_LSHIFT))
		//{	// 弾の生成
		//	BulletCreate(0);
		//}

		m_bAnswerCheck = true;
	}

	// ストックがある場合 弾を打てるフラグを立てる
	if (m_nCntStock > 0) { m_bPress = true; }

	if (m_bFlag == true)
	{
		if (CManager::GetTube(m_nPlayerID) != NULL)
		{
			CManager::GetTube(m_nPlayerID)->SetAnswer(NOT_NUM, m_nCntStock);
			CManager::GetTube(m_nPlayerID)->SetPoint(1, m_nPlayerID, true);
			CManager::GetTube(m_nPlayerID)->SetStockNum(m_nCntStock);
		}
		m_nStock[m_nCntStock] = NOT_NUM;
		m_nCntNum = 0;
		m_nCntaAnswer = 0;
		m_bFlag = false;

		m_nCntStock++;
		if (m_nCntStock >= MAX_WORD)
		{
			m_nCntStock = MAX_WORD;
			m_bGatherFlag = true;
		}
	}



#ifdef _DEBUG
	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		CDebugProc::Print("cc", "m_aWord = ", m_aWord[nCntWord].cWord);
	}
#endif
}

//=============================================================================
// 設定処理
//=============================================================================
void CWordManager::SetWord(int nType)
{
	CSound *pSound = CManager::GetSound();		//	音の取得
	if (m_nCntNum < MAX_WORD)
	{
		if (m_nCntNum == 0)
		{
			for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
			{
				m_aWord[nCntWord].nNum = EMPTINESS_NUM;
			}
			pSound->SetVolume(CSound::SOUND_LABEL_SE_GETTEXT000, 0.5f);
			pSound->PlaySound(CSound::SOUND_LABEL_SE_GETTEXT000);
		}
		else if (m_nCntNum == 1)
		{
			pSound->SetVolume(CSound::SOUND_LABEL_SE_GETTEXT001, 0.5f);
			pSound->PlaySound(CSound::SOUND_LABEL_SE_GETTEXT001);
		}
		else if (m_nCntNum == 2)
		{
			pSound->SetVolume(CSound::SOUND_LABEL_SE_GETTEXT002, 0.5f);
			pSound->PlaySound(CSound::SOUND_LABEL_SE_GETTEXT002);
		}
		m_aWord[m_nCntNum].nNum = nType;
		WordDebug(m_nCntNum);
		if (CManager::GetTube(m_nPlayerID) != NULL)
		{	// NULLチェック
			CManager::GetTube(m_nPlayerID)->SetWordNum(nType, m_nCntNum, m_nCntStock);
		}
		m_nCntNum++;
	}
}

//=============================================================================
// リセット関数
//=============================================================================
void CWordManager::Reset(void)
{
	if (m_nStock > 0)
	{
		for (int nCntWord = m_nCntNum; nCntWord < MAX_WORD; nCntWord++)
		{
			m_aWord[nCntWord].nNum = EMPTINESS_NUM;
			m_aWord[nCntWord].cWord = "NULL";
		}
	}

	for (int nCount = 0; nCount < MAX_WORD; nCount++)
	{
		m_bAnswer[nCount] = false;
	}

	m_nStock[0] = EMPTINESS_NUM;
	for (int nCntStcok = 0; nCntStcok < MAX_WORD - 1; nCntStcok++)
	{
		int nAnswerStock = m_nStock[nCntStcok];
		m_nStock[nCntStcok] = m_nStock[nCntStcok + 1];
		m_nStock[nCntStcok + 1] = nAnswerStock;
	}

	m_bGatherFlag = false;
	m_nCntStock--;
	if (m_nCntStock < 0) { m_nCntStock = 0; }
	if (CManager::GetTube(m_nPlayerID) != NULL)
	{
		CManager::GetTube(m_nPlayerID)->SetStockNum(m_nCntStock);
		CManager::GetTube(m_nPlayerID)->AllDelete(m_nCntNum);
		CManager::GetTube(m_nPlayerID)->UninitChack(false);
	}

	m_nCntaAnswer = 0;

	if (m_nStock[0] < m_nAnswerDataNum || m_nStock[0] == NOT_NUM)
	{
		m_bPress = true;
	}
	else { m_bPress = false;}
}

//=============================================================================
// 文字リセット関数
//=============================================================================
void CWordManager::WordReset(void)
{
	m_nCntNum = 0;

	if (m_nStock > 0)
	{
		for (int nCntWord = m_nCntNum; nCntWord < MAX_WORD; nCntWord++)
		{
			m_aWord[nCntWord].nNum = EMPTINESS_NUM;
			m_aWord[nCntWord].cWord = "NULL";
		}
	}

	for (int nCount = 0; nCount < MAX_WORD; nCount++)
	{
		m_bAnswer[nCount] = false;
	}

	m_bGatherFlag = false;

	m_nCntaAnswer = 0;
}

//=============================================================================
// 弾の生成  Editor : Kodama Yuto
//=============================================================================
void CWordManager::BulletCreate(int nID, D3DXVECTOR3 BulletMuzzle, D3DXVECTOR3 BulletRot, CPlayer::PLAYER_TYPE type, C3DCharactor* pChara)
{
	CSound *pSound = CManager::GetSound();		//	音の取得

	CCameraManager *pCameraManager = CManager::GetCameraManager();

	if (type == CPlayer::TYPE_RANDOM)
	{//ランダムが選ばれるのは不正なので処理を打ち切る
		return;
	}

	/*モードによって処理を変える*/
	if (CManager::GetPlayer(nID) != NULL)
	{//指定したプレイヤーが存在していれば
		if (m_nCntStock > 0)
		{
			if (m_nStock[0] < m_nAnswerDataNum)
			{	// 指定した文字なら弾を生成する
				int nType = 0;
				CModelBullet* pModel = NULL;
				D3DXVECTOR3 Sector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				nType = m_nStock[0];
				m_nCreateType = m_nAnswerTypeModel[nType] + (int)CLoad::MODEL_CAR0;	//弾になるモデルの位置までタイプをずらす

				switch (type)
				{
				case CPlayer::TYPE_SPEED://猫はミサイル型
					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{
						pModel->Set(BulletMuzzle, BulletRot + D3DXVECTOR3(0.0f, 0.0f, 0.0f),
							(CLoad::MODEL)m_nCreateType,
							CModelBullet::TYPE_MISSILE_CENTER,
							nID, m_rot[nType]);
						pModel->SetModelScale(m_Scale[nType]);	//大きさの設定
						pModel->SetHomingChara(pChara);
					}

					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{//0.75f
						pModel->Set(BulletMuzzle, BulletRot + D3DXVECTOR3(0.0f, 0.85f, 0.0f),
							(CLoad::MODEL)m_nCreateType,
							CModelBullet::TYPE_MISSILE_SIDE,
							nID, m_rot[nType]);
						pModel->SetModelScale(m_Scale[nType]);	//大きさの設定
						pModel->SetHomingChara(pChara);
					}

					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{
						pModel->Set(BulletMuzzle, BulletRot + D3DXVECTOR3(0.0f, -0.85f, 0.0f),
							(CLoad::MODEL)m_nCreateType,
							CModelBullet::TYPE_MISSILE_SIDE,
							nID, m_rot[nType]);
						pModel->SetModelScale(m_Scale[nType]);	//大きさの設定
						pModel->SetHomingChara(pChara);
					}

					m_nCreateType = EMPTINESS_NUM;
					break;
				case CPlayer::TYPE_REACH://うさぎはマシンガン型
					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{
						pModel->Set(BulletMuzzle, BulletRot,
							(CLoad::MODEL)m_nCreateType,
							CModelBullet::TYPE_MACHINEGUN,
							nID, m_rot[nType]);
						pModel->SetModelScale(m_Scale[nType]);	//大きさの設定
					}

					m_nCreateType = EMPTINESS_NUM;
					break;
				case CPlayer::TYPE_BARANCE://犬はショットガン型
					//弾生成
					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{
						Sector.y = 0.4f;
						pModel->Set(BulletMuzzle, BulletRot + Sector,
							(CLoad::MODEL)m_nCreateType,
							CModelBullet::TYPE_SHOTGUN_SLOW,
							nID, m_rot[nType]);
						pModel->SetModelScale(m_Scale[nType]);	//大きさの設定
					}
					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{
						Sector.y = -0.4f;
						pModel->Set(BulletMuzzle, BulletRot + Sector,
							(CLoad::MODEL)m_nCreateType,
							CModelBullet::TYPE_SHOTGUN_SLOW,
							nID, m_rot[nType]);
						pModel->SetModelScale(m_Scale[nType]);	//大きさの設定
					}

					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{
						Sector.y = 0.2f;
						pModel->Set(BulletMuzzle, BulletRot + Sector,
							(CLoad::MODEL)m_nCreateType,
							CModelBullet::TYPE_SHOTGUN_MEDIUM,
							nID, m_rot[nType]);
						pModel->SetModelScale(m_Scale[nType]);	//大きさの設定
					}

					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{
						Sector.y = -0.2f;
						pModel->Set(BulletMuzzle, BulletRot + Sector,
							(CLoad::MODEL)m_nCreateType,
							CModelBullet::TYPE_SHOTGUN_MEDIUM,
							nID, m_rot[nType]);
						pModel->SetModelScale(m_Scale[nType]);	//大きさの設定
					}
					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{
						Sector.y = 0.1f;
						pModel->Set(BulletMuzzle, BulletRot + Sector,
							(CLoad::MODEL)m_nCreateType,
							CModelBullet::TYPE_SHOTGUN,
							nID, m_rot[nType]);
						pModel->SetModelScale(m_Scale[nType]);	//大きさの設定
					}

					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{
						Sector.y = -0.1f;
						pModel->Set(BulletMuzzle, BulletRot + Sector,
							(CLoad::MODEL)m_nCreateType,
							CModelBullet::TYPE_SHOTGUN,
							nID, m_rot[nType]);
						pModel->SetModelScale(m_Scale[nType]);	//大きさの設定
					}
					m_nCreateType = EMPTINESS_NUM;
					break;
				case CPlayer::TYPE_POWER://熊は爆弾型
					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{
						pModel->Set(BulletMuzzle, BulletRot + D3DXVECTOR3(0.0f, 0.1f, 0.0f),
							(CLoad::MODEL)m_nCreateType,
							CModelBullet::TYPE_BOMB,
							nID, m_rot[nType]);
						pModel->SetModelScale(m_Scale[nType]);	//大きさの設定
						pModel->SetHomingChara(pChara);
					}

					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{
						pModel->Set(BulletMuzzle, BulletRot + D3DXVECTOR3(0.0f, -0.1f, 0.0f),
							(CLoad::MODEL)m_nCreateType,
							CModelBullet::TYPE_BOMB,
							nID, m_rot[nType]);
						pModel->SetModelScale(m_Scale[nType]);	//大きさの設定
						pModel->SetHomingChara(pChara);
					}

					break;
				default:
					pModel = CModelBullet::Create();
					if (pModel != NULL)
					{
						//pModel->Set(BulletMuzzle, BulletRot, (CLoad::MODEL)m_nCreateType, (CModelBullet::BULLET_PROPERTY)m_type[nType], nID, m_rot[nType]);
						pModel->Set(BulletMuzzle, BulletRot, (CLoad::MODEL)m_nCreateType, CModelBullet::TYPE_BOMB, nID, m_rot[nType]);

						pModel->SetModelScale(m_Scale[nType]);	//大きさの設定
						if (m_type[nType] == CModelBullet::TYPE_MISSILE_CENTER)
						{
							pModel->SetHomingChara(pChara);
						}
						m_nCreateType = EMPTINESS_NUM;

						if ((CModelBullet::BULLET_PROPERTY)m_type[nType] == (CModelBullet::BULLET_PROPERTY)m_type[0])
						{
							pSound->SetVolume(CSound::SOUND_LABEL_SE_BULLET000, 3.0f);
							pSound->PlaySound(CSound::SOUND_LABEL_SE_BULLET000);
						}
						else if ((CModelBullet::BULLET_PROPERTY)m_type[nType] == (CModelBullet::BULLET_PROPERTY)m_type[1])
						{
							pSound->SetVolume(CSound::SOUND_LABEL_SE_BULLET001, 3.0f);
							pSound->PlaySound(CSound::SOUND_LABEL_SE_BULLET001);
						}
						else if ((CModelBullet::BULLET_PROPERTY)m_type[nType] == (CModelBullet::BULLET_PROPERTY)m_type[2])
						{
							pSound->SetVolume(CSound::SOUND_LABEL_SE_BULLET002, 3.0f);
							pSound->PlaySound(CSound::SOUND_LABEL_SE_BULLET002);
						}
						else if ((CModelBullet::BULLET_PROPERTY)m_type[nType] == (CModelBullet::BULLET_PROPERTY)m_type[3])
						{
							pSound->SetVolume(CSound::SOUND_LABEL_SE_BULLET003, 3.0f);
							pSound->PlaySound(CSound::SOUND_LABEL_SE_BULLET003);
						}
					}
					break;
				}

			}
			else if (m_nStock[0] == NOT_NUM)
			{	// ゴミモデルを出す
				CModelBullet* pModel = CModelBullet::Create();
				if (pModel != NULL)
				{
					pModel->Set(BulletMuzzle, BulletRot, CLoad::MODE_DUST, CModelBullet::TYPE_NORMAL, nID);
					pModel->SetModelScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));//大きさの設定
				}
			}

			if (CManager::GetMode() == CManager::MODE_GAME)
			{
				//ブレンド無しで弾打ちモーションに移行
				CGame::GetPlayer(nID)->SetMotion(CPlayer::MOTION_UPPER_SHOT, CPlayer::UPPER_BODY, CPlayer::STATE_NORMAL);
				CGame::GetPlayer(nID)->SetMotion(CPlayer::MOTION_LOWER_SHOT, CPlayer::LOWER_BODY, CPlayer::STATE_NORMAL);

				if (type != CPlayer::TYPE_REACH)
				{
					Reset();		// 設定を戻す
				}
			}
			else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
			{
				//ブレンド無しで弾打ちモーションに移行
				CTutorial::GetPlayer(nID)->SetMotion(CPlayer::MOTION_UPPER_SHOT, CPlayer::UPPER_BODY, CPlayer::STATE_NORMAL);
				CTutorial::GetPlayer(nID)->SetMotion(CPlayer::MOTION_LOWER_SHOT, CPlayer::LOWER_BODY, CPlayer::STATE_NORMAL);
				if (type != CPlayer::TYPE_REACH)
				{
					Reset();		// 設定を戻す
				}
			}

		}
	}
}

//=============================================================================
// Textから読み込み 答えの割り当て
//=============================================================================
void CWordManager::SetWordLoad(int nNumModel, D3DXVECTOR3 AnswerNum, D3DXVECTOR3 scale, D3DXVECTOR3 rot, int type, int Model, int nPoint)
{
	m_AnswerNum[nNumModel] = AnswerNum;
	m_Scale[nNumModel] = scale;
	m_type[nNumModel] = type;
	m_nAnswerTypeModel[nNumModel] = Model;
	m_rot[nNumModel] = rot;
	m_nPoint[nNumModel] = nPoint;
}

//=============================================================================
// Textから最大数読み込み 動的確保
//=============================================================================
void CWordManager::SetWordAnswerNum(int nAnswerNum)
{
	m_nAnswerDataNum = nAnswerNum;
	m_AnswerNum = new D3DXVECTOR3[m_nAnswerDataNum];
	m_Scale = new D3DXVECTOR3[m_nAnswerDataNum];
	m_rot = new D3DXVECTOR3[m_nAnswerDataNum];
	m_type = new int[m_nAnswerDataNum];
	m_nAnswerTypeModel = new int[m_nAnswerDataNum];
	m_nPoint = new int[nAnswerNum];
}

//=============================================================================
// 文字の組み合わせが合っているかどうかを取得
//=============================================================================
int CWordManager::SearchWord(void)
{
	if (m_nCntNum == 2 && m_bSearch == false)
	{	// 拾った文字が２文字の場合
		int nData = 0;
		if (m_fAnswerData == NULL)
		{
			m_fAnswerData = new float[m_nAnswerDataNum];
		}

		for (int nCntAnswer = 0; nCntAnswer < m_nAnswerDataNum; nCntAnswer++)
		{	// 答えの数だけ回す
			int nAnswer = 0;
			for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
			{	// 答との比較
				if (m_AnswerNum[nCntAnswer].x == m_aWord[nCntWord].nNum && m_bAnswer[0] == false) { m_bAnswer[0] = true; nAnswer++; }
				else if (m_AnswerNum[nCntAnswer].y == m_aWord[nCntWord].nNum && m_bAnswer[1] == false) { m_bAnswer[1] = true; nAnswer++; }
				else if (m_AnswerNum[nCntAnswer].z == m_aWord[nCntWord].nNum && m_bAnswer[2] == false) { m_bAnswer[2] = true; nAnswer++; }

				if (nAnswer == 2)
				{	// 合っている所が2箇所の場合
					for (int nCntData = 0; nCntData < MAX_WORD; nCntData++)
					{
						if (m_bAnswer[nCntData] == false)
						{	// falseの場所を探す 見つけた答えを代入
							if (nCntData == 0) { m_fAnswerData[nData] = m_AnswerNum[nCntAnswer].x; }
							else if (nCntData == 1) { m_fAnswerData[nData] = m_AnswerNum[nCntAnswer].y; }
							else if (nCntData == 2) { m_fAnswerData[nData] = m_AnswerNum[nCntAnswer].z; }
							nData++;		// 回数を増やす
						}
					}
					nAnswer = 0;	// 合っている回数をリセット
				}
			}

			for (int nCount = 0; nCount < MAX_WORD; nCount++)
			{	// 全てfalseに戻す
				m_bAnswer[nCount] = false;
			}
		}

		// 3文字目候補のアシスト
		SearchAssist(nData);

		m_bSearch = true;		// Flagをtureに
		return nData;			// 答えの出た回数
	}

	return 0;
}

//=============================================================================
// 文字探しアシストの処理
//=============================================================================
void CWordManager::SearchAssist(int nCntData)
{
	if (nCntData == 0) { return; }
	int nNum = 0;
	int nCount = 0;

	CScene *pScene = NULL;

	nNum = CManager::GetWordCreate()->GetPopNum();

	while (nCount < CWord::GetAllNum())
	{
		// 先頭のオブジェクトを取得
		pScene = CScene::GetTop(5);

		while (pScene != NULL)
		{// 優先順位が弾と同じオブジェクトを1つ1つ確かめる
		 // 処理の最中に消える可能性があるから先に記録しておく
			CScene *pSceneNext = pScene->GetNext();
			if (pScene->GetDeath() == false && pScene->GetObjType() == CScene::OBJTYPE_WORD)
			{// 死亡フラグが立っていないもの
				CWord *pWord = ((CWord*)pScene);		// CBulletBaseへキャスト(型の変更)
				for (int nCntWord = 0; nCntWord < nCntData; nCntWord++)
				{
					if (pWord->GetWordNum() == m_fAnswerData[nCntWord])
					{
						pWord->SetSearchCol(m_nPlayerID);
					}
				}
				nCount++;
			}
			pScene = pSceneNext;
		}
	}
}

//=============================================================================
// 3文字目候補のアシストカラーをデフォルトに変更
//=============================================================================
void CWordManager::UninitAssist(void)
{
	int nNum = 0;
	int nCount = 0;

	CScene *pScene = NULL;

	if (CManager::MODE_GAME == CManager::GetMode()) { nNum = CGame::GetWordCreate()->GetPopNum(); }
	if (CManager::MODE_TUTORIAL == CManager::GetMode()) { nNum = CTutorial::GetWordCreate()->GetPopNum(); }

	while (nCount < CWord::GetAllNum())
	{
		// 先頭のオブジェクトを取得
		pScene = CScene::GetTop(5);

		while (pScene != NULL)
		{// 優先順位が弾と同じオブジェクトを1つ1つ確かめる
		 // 処理の最中に消える可能性があるから先に記録しておく
			CScene *pSceneNext = pScene->GetNext();
			if (pScene->GetDeath() == false && pScene->GetObjType() == CScene::OBJTYPE_WORD)
			{// 死亡フラグが立っていないもの
				CWord *pWord = ((CWord*)pScene);		// CBulletBaseへキャスト(型の変更)
				pWord->UninitSearchCol(m_nPlayerID);
				nCount++;
			}
			pScene = pSceneNext;
		}
	}
}


//=============================================================================
// 文字で生成のデバック用(数字管理)
//=============================================================================
void CWordManager::CreateOblDebug(void)
{
	CInputKeyboard *pKey = CManager::GetInputKeyboard();

	if (m_bPress == false)
	{
		if (pKey->GetPress(DIK_1))
		{	// あ行
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// あ
				m_aWord[m_nCntNum].nNum = 0;
				m_aWord[m_nCntNum].cWord = "あ";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// い
				m_aWord[m_nCntNum].nNum = 1;
				m_aWord[m_nCntNum].cWord = "い";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// う
				m_aWord[m_nCntNum].nNum = 2;
				m_aWord[m_nCntNum].cWord = "う";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// え
				m_aWord[m_nCntNum].nNum = 3;
				m_aWord[m_nCntNum].cWord = "え";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// え
				m_aWord[m_nCntNum].nNum = 4;
				m_aWord[m_nCntNum].cWord = "お";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_2))
		{	// か行
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// か
				m_aWord[m_nCntNum].nNum = 5;
				m_aWord[m_nCntNum].cWord = "か";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// き
				m_aWord[m_nCntNum].nNum = 6;
				m_aWord[m_nCntNum].cWord = "き";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// く
				m_aWord[m_nCntNum].nNum = 7;
				m_aWord[m_nCntNum].cWord = "く";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// け
				m_aWord[m_nCntNum].nNum = 8;
				m_aWord[m_nCntNum].cWord = "け";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// こ
				m_aWord[m_nCntNum].nNum = 9;
				m_aWord[m_nCntNum].cWord = "こ";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_3))
		{	// さ行
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// さ
				m_aWord[m_nCntNum].nNum = 10;
				m_aWord[m_nCntNum].cWord = "さ";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// し
				m_aWord[m_nCntNum].nNum = 11;
				m_aWord[m_nCntNum].cWord = "し";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// す
				m_aWord[m_nCntNum].nNum = 12;
				m_aWord[m_nCntNum].cWord = "す";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// せ
				m_aWord[m_nCntNum].nNum = 13;
				m_aWord[m_nCntNum].cWord = "せ";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// そ
				m_aWord[m_nCntNum].nNum = 14;
				m_aWord[m_nCntNum].cWord = "そ";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_4))
		{	// た行
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// た
				m_aWord[m_nCntNum].nNum = 15;
				m_aWord[m_nCntNum].cWord = "た";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ち
				m_aWord[m_nCntNum].nNum = 16;
				m_aWord[m_nCntNum].cWord = "ち";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// つ
				m_aWord[m_nCntNum].nNum = 17;
				m_aWord[m_nCntNum].cWord = "つ";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// て
				m_aWord[m_nCntNum].nNum = 18;
				m_aWord[m_nCntNum].cWord = "て";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// と
				m_aWord[m_nCntNum].nNum = 19;
				m_aWord[m_nCntNum].cWord = "と";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_5))
		{	// な行
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// な
				m_aWord[m_nCntNum].nNum = 20;
				m_aWord[m_nCntNum].cWord = "な";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// に
				m_aWord[m_nCntNum].nNum = 21;
				m_aWord[m_nCntNum].cWord = "に";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ぬ
				m_aWord[m_nCntNum].nNum = 22;
				m_aWord[m_nCntNum].cWord = "ぬ";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// ね
				m_aWord[m_nCntNum].nNum = 23;
				m_aWord[m_nCntNum].cWord = "ね";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// の
				m_aWord[m_nCntNum].nNum = 24;
				m_aWord[m_nCntNum].cWord = "の";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_6))
		{	// は行
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// は
				m_aWord[m_nCntNum].nNum = 25;
				m_aWord[m_nCntNum].cWord = "は";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ひ
				m_aWord[m_nCntNum].nNum = 26;
				m_aWord[m_nCntNum].cWord = "ひ";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ふ
				m_aWord[m_nCntNum].nNum = 27;
				m_aWord[m_nCntNum].cWord = "ふ";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// へ
				m_aWord[m_nCntNum].nNum = 28;
				m_aWord[m_nCntNum].cWord = "へ";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// ほ
				m_aWord[m_nCntNum].nNum = 29;
				m_aWord[m_nCntNum].cWord = "ほ";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_7))
		{	// ま行
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// ま
				m_aWord[m_nCntNum].nNum = 30;
				m_aWord[m_nCntNum].cWord = "ま";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// み
				m_aWord[m_nCntNum].nNum = 31;
				m_aWord[m_nCntNum].cWord = "み";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// む
				m_aWord[m_nCntNum].nNum = 32;
				m_aWord[m_nCntNum].cWord = "む";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// め
				m_aWord[m_nCntNum].nNum = 33;
				m_aWord[m_nCntNum].cWord = "め";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// も
				m_aWord[m_nCntNum].nNum = 34;
				m_aWord[m_nCntNum].cWord = "も";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_8))
		{	// や行
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// や
				m_aWord[m_nCntNum].nNum = 35;
				m_aWord[m_nCntNum].cWord = "や";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ゆ
				m_aWord[m_nCntNum].nNum = 36;
				m_aWord[m_nCntNum].cWord = "ゆ";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// よ
				m_aWord[m_nCntNum].nNum = 37;
				m_aWord[m_nCntNum].cWord = "よ";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_9))
		{	// ら行
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// ら
				m_aWord[m_nCntNum].nNum = 38;
				m_aWord[m_nCntNum].cWord = "ら";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// り
				m_aWord[m_nCntNum].nNum = 39;
				m_aWord[m_nCntNum].cWord = "り";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// る
				m_aWord[m_nCntNum].nNum = 40;
				m_aWord[m_nCntNum].cWord = "る";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// れ
				m_aWord[m_nCntNum].nNum = 41;
				m_aWord[m_nCntNum].cWord = "れ";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// ろ
				m_aWord[m_nCntNum].nNum = 42;
				m_aWord[m_nCntNum].cWord = "ろ";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_0))
		{	// わ行
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// わ
				m_aWord[m_nCntNum].nNum = 43;
				m_aWord[m_nCntNum].cWord = "わ";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// を
				m_aWord[m_nCntNum].nNum = 44;
				m_aWord[m_nCntNum].cWord = "を";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ん
				m_aWord[m_nCntNum].nNum = 45;
				m_aWord[m_nCntNum].cWord = "ん";
				m_nCntNum++;
			}
		}
	}

	if (m_nCntNum == MAX_WORD)
	{	// 最大ならこれ以上数字をいれない
		m_bPress = true;
	}
}

//=============================================================================
// 文字のデバック用
//=============================================================================
void CWordManager::WordDebug(int nCntNum)
{
	if (m_aWord[nCntNum].nNum == 0)
	{	// あ
		m_aWord[nCntNum].cWord = "あ";
	}
	else if (m_aWord[nCntNum].nNum == 1)
	{	// い
		m_aWord[nCntNum].cWord = "い";
	}
	else if (m_aWord[nCntNum].nNum == 2)
	{	// う
		m_aWord[nCntNum].cWord = "う";
	}
	else if (m_aWord[nCntNum].nNum == 3)
	{	// え
		m_aWord[nCntNum].cWord = "え";
	}
	else if (m_aWord[nCntNum].nNum == 4)
	{	// え
		m_aWord[nCntNum].cWord = "お";
	}
	else if (m_aWord[nCntNum].nNum == 5)
	{	// か
		m_aWord[nCntNum].cWord = "か";
	}
	else if (m_aWord[nCntNum].nNum == 6)
	{	// き
		m_aWord[nCntNum].cWord = "き";
	}
	else if (m_aWord[nCntNum].nNum == 7)
	{	// く
		m_aWord[nCntNum].cWord = "く";
	}
	else if (m_aWord[nCntNum].nNum == 8)
	{	// け
		m_aWord[nCntNum].cWord = "け";
	}
	else if (m_aWord[nCntNum].nNum == 9)
	{	// こ
		m_aWord[nCntNum].cWord = "こ";
	}
	else if (m_aWord[nCntNum].nNum == 10)
	{	// さ
		m_aWord[nCntNum].cWord = "さ";
	}
	else if (m_aWord[nCntNum].nNum == 11)
	{	// し
		m_aWord[nCntNum].cWord = "し";
	}
	else if (m_aWord[nCntNum].nNum == 12)
	{	// す
		m_aWord[nCntNum].cWord = "す";
	}
	else if (m_aWord[nCntNum].nNum == 13)
	{	// せ
		m_aWord[nCntNum].cWord = "せ";
	}
	else if (m_aWord[nCntNum].nNum == 14)
	{	// そ
		m_aWord[nCntNum].cWord = "そ";
	}
	else if (m_aWord[nCntNum].nNum == 15)
	{	// た
		m_aWord[nCntNum].cWord = "た";
	}
	else if (m_aWord[nCntNum].nNum == 16)
	{	// ち
		m_aWord[nCntNum].cWord = "ち";
	}
	else if (m_aWord[nCntNum].nNum == 17)
	{	// つ
		m_aWord[nCntNum].cWord = "つ";
	}
	else if (m_aWord[nCntNum].nNum == 18)
	{	// て
		m_aWord[nCntNum].cWord = "て";
	}
	else if (m_aWord[nCntNum].nNum == 19)
	{	// と
		m_aWord[nCntNum].cWord = "と";
	}
	else if (m_aWord[nCntNum].nNum == 20)
	{	// な
		m_aWord[nCntNum].cWord = "な";
	}
	else if (m_aWord[nCntNum].nNum == 21)
	{	// に
		m_aWord[nCntNum].cWord = "に";
	}
	else if (m_aWord[nCntNum].nNum == 22)
	{	// ぬ
		m_aWord[nCntNum].cWord = "ぬ";
	}
	else if (m_aWord[nCntNum].nNum == 23)
	{	// ね
		m_aWord[nCntNum].cWord = "ね";
	}
	else if (m_aWord[nCntNum].nNum == 24)
	{	// の
		m_aWord[nCntNum].cWord = "の";
	}
	else if (m_aWord[nCntNum].nNum == 25)
	{	// は
		m_aWord[nCntNum].cWord = "は";
	}
	else if (m_aWord[nCntNum].nNum == 26)
	{	// ひ
		m_aWord[nCntNum].cWord = "ひ";
	}
	else if (m_aWord[nCntNum].nNum == 27)
	{	// ふ
		m_aWord[nCntNum].cWord = "ふ";
	}
	else if (m_aWord[nCntNum].nNum == 28)
	{	// へ
		m_aWord[nCntNum].cWord = "へ";
	}
	else if (m_aWord[nCntNum].nNum == 29)
	{	// ほ
		m_aWord[nCntNum].cWord = "ほ";
	}
	else if (m_aWord[nCntNum].nNum == 30)
	{	// ま
		m_aWord[nCntNum].cWord = "ま";
	}
	else if (m_aWord[nCntNum].nNum == 31)
	{	// み
		m_aWord[nCntNum].cWord = "み";
	}
	else if (m_aWord[nCntNum].nNum == 32)
	{	// む
		m_aWord[nCntNum].cWord = "む";
	}
	else if (m_aWord[nCntNum].nNum == 33)
	{	// め
		m_aWord[nCntNum].cWord = "め";
	}
	else if (m_aWord[nCntNum].nNum == 34)
	{	// も
		m_aWord[nCntNum].cWord = "も";
	}
	else if (m_aWord[nCntNum].nNum == 35)
	{	// や
		m_aWord[nCntNum].cWord = "や";
	}
	else if (m_aWord[nCntNum].nNum == 36)
	{	// ゆ
		m_aWord[nCntNum].cWord = "ゆ";
	}
	else if (m_aWord[nCntNum].nNum == 37)
	{	// よ
		m_aWord[nCntNum].cWord = "よ";
	}
	else if (m_aWord[nCntNum].nNum == 38)
	{	// ら
		m_aWord[nCntNum].cWord = "ら";
	}
	else if (m_aWord[nCntNum].nNum == 39)
	{	// り
		m_aWord[nCntNum].cWord = "り";
	}
	else if (m_aWord[nCntNum].nNum == 40)
	{	// る
		m_aWord[nCntNum].cWord = "る";
	}
	else if (m_aWord[nCntNum].nNum == 41)
	{	// れ
		m_aWord[nCntNum].cWord = "れ";
	}
	else if (m_aWord[nCntNum].nNum == 42)
	{	// ろ
		m_aWord[nCntNum].cWord = "ろ";
	}
	else if (m_aWord[nCntNum].nNum == 43)
	{	// わ
		m_aWord[nCntNum].cWord = "わ";
	}
	else if (m_aWord[nCntNum].nNum == 44)
	{	// を
		m_aWord[nCntNum].cWord = "を";
	}
	else if (m_aWord[nCntNum].nNum == 45)
	{	// ん
		m_aWord[nCntNum].cWord = "ん";
	}
	else if (m_aWord[nCntNum].nNum == NOT_NUM)
	{	// 空の状態
		m_aWord[nCntNum].cWord = "NULL";
	}
}


