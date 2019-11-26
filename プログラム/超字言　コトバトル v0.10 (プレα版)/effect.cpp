//=============================================================================
//
// エフェクト(パーティクル)処理 [effect.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene3D.h"		// シーン3D
#include "manager.h"		// マネージャー
#include "renderer.h"		// レンダラー
#include "input.h"			// 入力
#include "effect.h"			// エフェクト
#include "scene.h"			// シーン

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
int g_nCounteraaa = 0;

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
LPDIRECT3DTEXTURE9   CEffect::m_pTexture[MAX_EFFECTTYPE] = {};
char				 CEffect::m_cTextName[128] = {};
char				 CEffect::m_cTextureName[MAX_EFFECTTYPE][128] = {};
int					 CEffect::m_nTexttureType = NULL;
CEffect::EFFECT_STATE CEffect::m_EffectState = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CEffect::CEffect() : CScene(3, CScene::OBJTYPE_EFFECT)
{
	for (int nCount = 0; nCount < MAX_EFFECT; nCount++)
	{
		m_apScene3D[nCount] = NULL;
		m_NumMove[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//	動きの割り当て
		m_nNumLife[nCount] = 0;												//	寿命
	}
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//	位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//	回転
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);								//	色
	m_TexUV = D3DXVECTOR2(0.0f, 0.0f);										//	UV
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);									//	大きさ
	m_posRange = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								//	位置の幅
	m_nSetPoriMAX = 0;														//	ポリゴンの数
	m_nEffectType = 0;														//	エフェクトの種類
	m_nLife = 0;															//	寿命
	m_fGravity = 0;															//	重力
}

//=============================================================================
// デストラクタ
//=============================================================================
CEffect::~CEffect()
{
}
//=============================================================================
//	エフェクトの生成
//=============================================================================
CEffect *CEffect::Create(D3DXVECTOR3 pos, int textype, int txsttype)
{
	CEffect *pEffect = NULL;
	if (pEffect == NULL)
	{//	アイテムの生成
		pEffect = new CEffect;
		if (pEffect != NULL)
		{//アイテムの初期化
			pEffect->m_pos = pos;							//	位置の設定
			pEffect->m_nEffectType = textype;				//	エフェクトの画像の種類
			pEffect->m_nBindText = txsttype;				//	エフェクトの演出割り当て
			pEffect->Init();
		}
	}
	return pEffect;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEffect::Init(void)
{
	for (int nCount = 0; nCount < m_EffectState.nSetPoriMAX[m_nBindText]; nCount++)
	{//	確保した分
	 //	変数の初期化
		m_apScene3D[nCount] = NULL;
		if (m_apScene3D[nCount] == NULL)
		{//	変数に何も入っていなかった場合
		 //	メモリの確保
			m_apScene3D[nCount] = new CScene3D(3, CScene::OBJTYPE_EFFECT);
			if (m_apScene3D[nCount] != NULL)
			{//	3Dポリゴンのメモリが確保出来たら
			 //	動きの初期設定
				m_NumMove[nCount] = D3DXVECTOR3(
					(sinf((rand() % 628) / 100.0f) * ((rand() % (int)1) + m_EffectState.move[m_nBindText].x)),
					(cosf((rand() % 314 / 2) / 100.0f) * ((rand() % (int)1) + m_EffectState.move[m_nBindText].y)),
					(cosf((rand() % 628) / 100.0f) * ((rand() % (int)1) + m_EffectState.move[m_nBindText].z)));
				//	位置の初期設定
				m_pos += D3DXVECTOR3((sinf((rand() % 628) / 100.0f) * ((rand() % (int)1) + m_EffectState.posRange[m_nBindText].x)),
					(cosf((rand() % 628) / 100.0f) * ((rand() % (int)1) + m_EffectState.posRange[m_nBindText].y)),
					(cosf((rand() % 628) / 100.0f) * ((rand() % (int)1) + m_EffectState.posRange[m_nBindText].z)));
				//	寿命の設定
				m_nNumLife[nCount] = m_EffectState.nLife[m_nBindText];
				m_fGravity = m_EffectState.fGravity[m_nBindText];
				//	テクスチャの割り当て
				m_apScene3D[nCount]->BindTexture(m_pTexture[m_nEffectType]);

				if (m_EffectState.nBillType[m_nBindText] == 0)
				{//	加算合成なし
					m_apScene3D[nCount]->SetInitAll(m_pos, m_EffectState.rot[m_nBindText], m_EffectState.size[m_nBindText], m_EffectState.col[m_nBindText], m_EffectState.TexUV[m_nBindText], CScene3D::SCENE3DTYPE_BILLBOARD);
				}
				else if (m_EffectState.nBillType[m_nBindText] == 1)
				{//	加算合成あり
					m_apScene3D[nCount]->SetInitAll(m_pos, m_EffectState.rot[m_nBindText], m_EffectState.size[m_nBindText], m_EffectState.col[m_nBindText], m_EffectState.TexUV[m_nBindText], CScene3D::SCENE3DTYPE_BILLEFFECT);
				}
				m_apScene3D[nCount]->Init();
			}
		}
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEffect::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_EFFECT; nCount++)
	{//	最大数分回す
		if (m_apScene3D[nCount] != NULL)
		{//	使用されていなかったら
			m_apScene3D[nCount]->Uninit();
			m_apScene3D[nCount] = NULL;
		}
	}
	// シーン開放
	CScene::Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEffect::Update(void)
{
	D3DXVECTOR3 pos[MAX_EFFECT];							//	位置の取得
	D3DXVECTOR3 rot[MAX_EFFECT];							//	向きの設定
	D3DXVECTOR3 size[MAX_EFFECT];							//	大きさの取得
	D3DXCOLOR   col[MAX_EFFECT];							//	色の設定

	CInputKeyboard *pInputKeybaod = CManager::GetInputKeyboard();

	for (int nCount = 0; nCount < m_EffectState.nSetPoriMAX[m_nBindText]; nCount++)
	{//	ポリゴンの数文回す
		if (m_apScene3D[nCount] != NULL)
		{//	空じゃないか調べる
			pos[nCount] = m_apScene3D[nCount]->GetPos();	//	位置の取得
			rot[nCount] = m_apScene3D[nCount]->GetRot();	//	向きの設定
			size[nCount].y = m_apScene3D[nCount]->GetSizeY();	//	大きさの取得Y
			size[nCount].x = m_apScene3D[nCount]->GetSizeX();	//	大きさの取得X
			col[nCount] = m_apScene3D[nCount]->Getcol();	//	色の設定


			//	重力の設定
			m_NumMove[nCount].y -= m_fGravity;
			//	位置に動きを代入する
			pos[nCount] += m_NumMove[nCount];

			m_apScene3D[nCount]->SetPos(pos[nCount]);		//	位置の設定
			m_apScene3D[nCount]->SetSizeY(size[nCount].y, size[nCount].x);	//	大きさの設定
			m_apScene3D[nCount]->SetColor(col[nCount]);		//	色の設定
			m_apScene3D[nCount]->SetRot(rot[nCount]);		//	向きの設定
															//	体力の減少
			m_nNumLife[nCount]--;
			if (m_nNumLife[nCount] < 0)
			{//	ライフが0以下になった場合消す
				Uninit();
			}
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void CEffect::Draw(void)
{

}
//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CEffect::Load(void)
{
	LoadTexNameEffect();
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	for (int nCount = 0; nCount < m_nTexttureType; nCount++)
	{//	テクスチャの数文回す
		D3DXCreateTextureFromFile(pDevice, &m_cTextureName[nCount][0], &m_pTexture[nCount]);
	}

	return S_OK;
}
//=============================================================================
// アンロード処理
//=============================================================================
void CEffect::Unload(void)
{
	for (int nCount = 0; nCount < MAX_EFFECT; nCount++)
	{//	エフェクトのデータの初期化
		m_EffectState.posRange[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	位置の範囲
		m_EffectState.rot[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	向き
		m_EffectState.move[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	動き
		m_EffectState.size[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	位置
		m_EffectState.col[nCount] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//	色
		m_EffectState.TexUV[nCount] = D3DXVECTOR2(0.0f, 0.0f);			//	UV
		m_EffectState.nSetPoriMAX[nCount] = 0;							//	ポリゴンの数
		m_EffectState.fGravity[nCount] = 0;								//	重力
		m_EffectState.nLife[nCount] = 0;								//	寿命
		m_EffectState.nBillType[nCount] = false;						//	加算合成ありかなしか
	}
	m_EffectState.nCounter = false;										//	加算合成ありかなしか
																		////	使っていないメモリの開放
																		//for (int nCount = 0; nCount < MAX_EFFECTTYPE; nCount++)
																		//{//	テクスチャの数文回す
																		//	if (m_pTexture[nCount] != NULL)
																		//	{//	テクスチャの破棄
																		//		m_pTexture[nCount]->Release();
																		//		m_pTexture[nCount] = NULL;
																		//	}
																		//}
}

//=============================================================================
// エフェクトの情報読み込み(データ読み込み)
//=============================================================================
void CEffect::LoadDataEffect(void)
{
	FILE *pFile = NULL;
	//	テキストの文字列読み込み
	char read[128];
	//	テキストの読み込み
	pFile = fopen(&m_cTextName[0], "r");

	if (pFile != NULL)
	{//	ファイルの読み込みが設定出来たら
	 //	テキストのデータ読み込み
		fscanf(pFile, "%s", &read[0]);

		while (read[0] != NULL &&strcmp(&read[0], "EFFECTSET_STATE") == 0)
		{//	文字列が読み込まれていた場合
			do
			{//	エフェクトの読み込み
				fscanf(pFile, "%s", &read[0]);
				if (strcmp(&read[0], "POSRANGE") == 0)
				{//	回転の設定
					fscanf(pFile, "%s%f%f%f", &read[0], &m_EffectState.posRange[m_EffectState.nCounter].x, &m_EffectState.posRange[m_EffectState.nCounter].y, &m_EffectState.posRange[m_EffectState.nCounter].z);
				}
				else if (strcmp(&read[0], "ROT") == 0)
				{//	回転の設定
					fscanf(pFile, "%s%f%f%f", &read[0], &m_EffectState.rot[m_EffectState.nCounter].x, &m_EffectState.rot[m_EffectState.nCounter].y, &m_EffectState.rot[m_EffectState.nCounter].z);
				}
				else if (strcmp(&read[0], "MOVE") == 0)
				{//	大きさの設定
					fscanf(pFile, "%s%f%f%f", &read[0], &m_EffectState.move[m_EffectState.nCounter].x, &m_EffectState.move[m_EffectState.nCounter].y, &m_EffectState.move[m_EffectState.nCounter].z);
				}
				else if (strcmp(&read[0], "SIZE") == 0)
				{//	大きさの設定
					fscanf(pFile, "%s%f%f%f", &read[0], &m_EffectState.size[m_EffectState.nCounter].x, &m_EffectState.size[m_EffectState.nCounter].y, &m_EffectState.size[m_EffectState.nCounter].z);
				}
				else if (strcmp(&read[0], "COL") == 0)
				{//	色の設定
					fscanf(pFile, "%s%f%f%f%f", &read[0], &m_EffectState.col[m_EffectState.nCounter].r, &m_EffectState.col[m_EffectState.nCounter].g, &m_EffectState.col[m_EffectState.nCounter].b, &m_EffectState.col[m_EffectState.nCounter].a);
				}
				else if (strcmp(&read[0], "TEXUV") == 0)
				{//	UVの設定
					fscanf(pFile, "%s%f%f", &read[0], &m_EffectState.TexUV[m_EffectState.nCounter].x, &m_EffectState.TexUV[m_EffectState.nCounter].y);
				}
				else if (strcmp(&read[0], "PRIGONMAX") == 0)
				{//	ポリゴンの数の設定
					fscanf(pFile, "%s%d", &read[0], &m_EffectState.nSetPoriMAX[m_EffectState.nCounter]);
				}
				else if (strcmp(&read[0], "GRAVITY") == 0)
				{//	エフェクトが消える時間の設定
					fscanf(pFile, "%s%f", &read[0], &m_EffectState.fGravity[m_EffectState.nCounter]);
				}
				else if (strcmp(&read[0], "LIFE") == 0)
				{//	エフェクトが消える時間の設定
					fscanf(pFile, "%s%d", &read[0], &m_EffectState.nLife[m_EffectState.nCounter]);
				}
				else if (strcmp(&read[0], "BILLTYPE") == 0)
				{//	エフェクト加算合成の設定
					fscanf(pFile, "%s%d", &read[0], &m_EffectState.nBillType[m_EffectState.nCounter]);
				}
			} while (strcmp(&read[0], "EFFECT_END") != 0);
			//	次の文字列読み込む
			fscanf(pFile, "%s", &read[0]);
			m_EffectState.nCounter++;					//	カウント
		}
		fclose(pFile);
	}
}


//=============================================================================
// エフェクトの情報読み込み(テキストの名前読み込み)
//=============================================================================
void CEffect::LoadNameEffect(void)
{
	FILE *pFile = NULL;
	int nNumTxst = 0;	//	読み込むテキストの数
	int nCount = 0;		//
	char *pStrCur;		//	文字列の先頭へのポインタ
	char aLine[256];	//	文字列の読み込み用[1行分]
	char aStr[256];		//	文字列の抜き出し用
	char *pCheck;
	char *pStrLen;

	pFile = fopen("data/TEXT/EFFECT/EFFECT_SET_TEXT.txt", "r");

	if (pFile != NULL)
	{//	ファイルの読み込みが設定出来たら
		while (fgets(aLine, 256, pFile) != NULL)
		{//	1行分分読み込む
			pStrCur = aLine;			//	先頭アドレスを読み込む
			strcpy(aStr, pStrCur);		//	先頭アドレスを抜き出す
			pStrLen = "NUM_TEXT = ";
			if (memcmp(pStrCur, "NUM_TEXT = ", strlen(pStrLen)) == 0)
			{//	モデルの番号
				pStrCur += strlen(pStrLen);			//	文字列のところまでアドレスをずらす
				strcpy(aStr, pStrCur);				//	ずらしたところまでの文字列を代入する
				nNumTxst = atoi(aStr);				//	文字列をint型に変換する
				break;
			}
		}
		nCount = 0;
		while (fgets(aLine, 256, pFile) != NULL)
		{//	1行分分読み込む
		 //	改行文字があるかないか
			pCheck = strchr(aLine, '\n');
			if (pCheck != NULL)
			{//	改行文字があった場合
				*pCheck = '\0';
			}//	改行文字を終端文字に入れ替える
			pStrCur = aLine;			//	先頭アドレスを読み込む
			strcpy(aStr, pStrCur);		//	先頭アドレスを抜き出す
			pStrLen = "TEXT_NAME = ";
			if (memcmp(pStrCur, "TEXT_NAME = ", strlen(pStrLen)) == 0)
			{//	モデルの名前
				pStrCur += strlen(pStrLen);
				strcpy(&m_cTextName[0], pStrCur);
				if (nCount > nNumTxst)
				{
					break;
				}
			}
			nCount += 1;
		}
		fclose(pFile);
	}
}

//=============================================================================
// エフェクトの情報読み込み(エフェクトの画像の名前読み込み)
//=============================================================================
void CEffect::LoadTexNameEffect(void)
{
	FILE *pFile = NULL;
	int nNumTex = 0;	//	読み込むテクスチャの数
	int nCount = 0;
	char *pStrCur;		//	文字列の先頭へのポインタ
	char aLine[256];	//	文字列の読み込み用[1行分]
	char aStr[256];		//	文字列の抜き出し用
	char *pCheck;		//	文字列の中のゴミcheck
	char *pStrLen;		//	文字列の長さ

	pFile = fopen("data/TEXT/EFFECT/EFFECT_SET_TEXTURE.txt", "r");

	if (pFile != NULL)
	{//	ファイルの読み込みが設定出来たら
		while (fgets(aLine, 256, pFile) != NULL)
		{//	1行分分読み込む
			pStrCur = aLine;			//	先頭アドレスを読み込む
			strcpy(aStr, pStrCur);		//	先頭アドレスを抜き出す
			pStrLen = "MAX_TEXTURE = ";
			if (memcmp(pStrCur, "MAX_TEXTURE = ", strlen(pStrLen)) == 0)
			{//	モデルの番号
				pStrCur += strlen(pStrLen);			//	文字列のところまでアドレスをずらす
				strcpy(aStr, pStrCur);				//	ずらしたところまでの文字列を代入する
				nNumTex = atoi(aStr);				//	文字列をint型に変換する
				break;
			}
		}
		m_nTexttureType = nNumTex;
		nCount = 0;
		while (fgets(aLine, 256, pFile) != NULL)
		{//	1行分分読み込む
		 //	改行文字があるかないか
			pCheck = strchr(aLine, '\n');
			if (pCheck != NULL)
			{//	改行文字があった場合
				*pCheck = '\0';
			}//	改行文字を終端文字に入れ替える
			pStrCur = aLine;			//	先頭アドレスを読み込む
			strcpy(aStr, pStrCur);		//	先頭アドレスを抜き出す
			pStrLen = "TEXTURE_NAME = ";
			if (memcmp(pStrCur, "TEXTURE_NAME = ", strlen(pStrLen)) == 0)
			{//	モデルの名前
				pStrCur += strlen(pStrLen);
				strcpy(&m_cTextureName[nCount][0], pStrCur);
				if (nCount > nNumTex)
				{
					break;
				}
			}
			nCount += 1;
		}
		fclose(pFile);
	}

}