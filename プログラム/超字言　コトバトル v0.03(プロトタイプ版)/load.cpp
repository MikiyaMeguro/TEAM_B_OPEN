//=============================================================================
//
// テクスチャ処理 [texture.cpp]
// Author : 目黒 未来也
//
//=============================================================================
#include "load.h"
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "debugProc.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_FILE_NAME				("data\\TEXT\\SetModel.txt")

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPD3DXMESH *CLoad::m_pMesh = NULL;			// メッシュ情報（頂点情報）へのポインタ
LPD3DXBUFFER *CLoad::m_pBuffMat = NULL;	// マテリアル情報へのポインタ
DWORD *CLoad::m_nNumMat = 0;				// マテリアル情報の数
int	CLoad::m_nMaxModel = 0;
int	CLoad::m_nCntModel = 0;
char CLoad::m_apModelName[MODEL_MAX][256] = {NULL};
LPDIRECT3DTEXTURE9 *CLoad::m_pTexture[MODEL_MAX] = { NULL };
//const char *CLoad::m_apModelFilename[] =
//{// モデル
//	"data\\MODEL\\car000.x",				//0
//	"data\\MODEL\\car001.x",				//1
//	"data\\MODEL\\box000.x",				//2
//};

//const char *CLoad::m_apModelFilename[] =
//{// モデル
//	"data\\MODEL\\car000.x",				//0
//	"data\\MODEL\\car001.x",				//1
//	"data\\MODEL\\Desk.x",				//2 (机)
//	"data\\MODEL\\Pulin.x",				// プリン
//	"data\\MODEL\\Knife.x",				// ナイフ
//	"data\\MODEL\\apple.x",				// リンゴ
//	"data\\MODEL\\box000.x",				//3
//	"data\\MODEL\\SampleModel_Player.x",	//3
//};


//=============================================================================
// コンストラクタ
//=============================================================================
CLoad::CLoad()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CLoad::~CLoad()
{
}

//=============================================================================
// テクスチャ読み込み処理
//=============================================================================
HRESULT CLoad::LoadModel(void)
{
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	if (m_pMesh != NULL)
	{
		// メモリを解放する
		delete[] m_pMesh;
		m_pMesh = NULL;
	}

	if (m_pBuffMat != NULL)
	{
		// メモリを解放する
		delete[] m_pBuffMat;
		m_pBuffMat = NULL;
	}

	if (m_nNumMat != NULL)
	{
		// メモリを解放する
		delete[] m_nNumMat;
		m_nNumMat = NULL;
	}

	//ファイル読み込み
	LoadFile();

	int nModelData = (sizeof m_apModelName);
	int nModelSize = (sizeof m_apModelName[0]);
	int nNumModel = nModelData / nModelSize;
	nNumModel = m_nMaxModel;
	// 動的に確保
	m_pMesh = new LPD3DXMESH[nNumModel];
	m_pBuffMat = new LPD3DXBUFFER[nNumModel];
	m_nNumMat = new DWORD[nNumModel];

	//モデルを生成
	for (int nCntModel = 0; nCntModel < MODEL_MAX; nCntModel++)
	{
		D3DXLoadMeshFromX(&m_apModelName[nCntModel][0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat[nCntModel],
			NULL,
			&m_nNumMat[nCntModel],
			&m_pMesh[nCntModel]);
	}


	for (int nCntModel = 0; nCntModel < MODEL_MAX; nCntModel++)
	{
		//テクスチャ初期化
		TextureSetting(nCntModel);
	}

	return S_OK;
}

//=============================================================================
// テクスチャ解放処理
//=============================================================================
void CLoad::UnloadModel(void)
{
	//ポインタのNULLチェック
	if (m_pTexture != NULL)
	{
		for (int nCntModel = 0; nCntModel < MODEL_MAX; nCntModel++)
		{
			for (int nCnt = 0; nCnt < (int)m_nNumMat[nCntModel]; nCnt++)
			{
				//ポインタ内のポインタのNULLチェック
				if (m_pTexture[nCntModel][nCnt] != NULL)
				{
					//テクスチャ破棄
					m_pTexture[nCntModel][nCnt]->Release();
					m_pTexture[nCntModel][nCnt] = NULL;
				}
			}
			//メモリを開放
			delete[] m_pTexture[nCntModel];
		}
	}
	//NULLを入れる
	*m_pTexture = NULL;



	if (m_pBuffMat != NULL)
	{
		// メモリを解放する
		delete[] m_pBuffMat;
		m_pBuffMat = NULL;
	}

	if (m_nNumMat != NULL)
	{
		// メモリを解放する
		delete[] m_nNumMat;
		m_nNumMat = NULL;
	}

	if (m_pMesh != NULL)
	{
		// メモリを解放する
		delete[] m_pMesh;
		m_pMesh = NULL;
	}
}

//=============================================================================
// メッシュ取得
//=============================================================================
LPD3DXMESH CLoad::GetMesh(int nIdx)
{
	return m_pMesh[nIdx];
}

//=============================================================================
// マテリアル情報取得
//=============================================================================
LPD3DXBUFFER CLoad::GetBuffMat(int nIdx)
{
	return m_pBuffMat[nIdx];
}

//=============================================================================
// マテリアル情報の数取得
//=============================================================================
DWORD CLoad::GetNumMat(int nIdx)
{
	return m_nNumMat[nIdx];
}

//=============================================================================
// テクスチャの設定
//=============================================================================
void CLoad::TextureSetting(int nModel)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//マテリアルデータへのポインタ
	D3DXMATERIAL *pMat;
	//マテリアル情報からテクスチャの取得
	pMat = (D3DXMATERIAL*)m_pBuffMat[nModel]->GetBufferPointer();
	//テクスチャをマテリアルの数分動的確保
	m_pTexture[nModel] = new LPDIRECT3DTEXTURE9[m_nNumMat[nModel]];
	//マテリアルの数回す
	for (int nCntMatTex = 0; nCntMatTex < (int)m_nNumMat[nModel]; nCntMatTex++)
	{
		//NULLを入れる 中身を空に
		m_pTexture[nModel][nCntMatTex] = NULL;

		if (pMat[nCntMatTex].pTextureFilename != NULL)
		{
			// テクスチャの設定
			D3DXCreateTextureFromFile(pDevice,			// デバイスへのポインタ
				pMat[nCntMatTex].pTextureFilename,			// ファイルの名前
				&m_pTexture[nModel][nCntMatTex]);		// テクスチャへのポインタ
		}
	}
}

//=============================================================================
// テクスチャの取得処理
//=============================================================================
LPDIRECT3DTEXTURE9 *CLoad::GetTexture(MODEL Model)
{
	return m_pTexture[Model];
}



//=============================================================================
// オブジェクトの配置情報を読み込み
//=============================================================================
void CLoad::LoadFile(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//ファイル読み込み用変数
	FILE *pFile;			//ファイルポインタ
	char *pStrcur;			//現在の先頭の文字列
	char aLine[256];		//文字列
	char aStr[256];			//一時保存文字列
	int nIndex = 0;			//現在のインデックス
	int nWord = 0;			//ポップで返された値を保持
	int nNumModel = 0;		//モデルの数
	int nCntModel = 0;
	int nType = 0;			//モデルの種類
	D3DXVECTOR3 ModelPos;	//モデルの位置
	D3DXVECTOR3 ModelRot;
	//ファイルを開く 読み込み
	pFile = fopen(MODEL_FILE_NAME, "r");
	//NULLチェック
	if (pFile != NULL)
	{

		while (1)
		{
			//文字列の先頭を設定
			pStrcur = ReadLine(pFile, &aLine[0]);
			//文字列を取り出す
			strcpy(aStr, pStrcur);

			//スクリプトの終わり
			if (memcmp(pStrcur, "END_SCRIPT	", strlen("END_SCRIPT")) == 0)
			{
				break;
			}

			//文字列のデータ 比較する文字列 比較する文字数
			if (memcmp(pStrcur, "NUM_MODEL = ", strlen("NUM_MODEL = ")) == 0)
			{
				//頭出し
				pStrcur += strlen("NUM_MODEL = ");
				//文字列の先頭を設定
				strcpy(aStr, pStrcur);
				//文字列抜き出し
				nNumModel = atoi(pStrcur);
				m_nMaxModel = nNumModel;

				// 動的に確保
				//m_apModelName[0] = "test";
				//m_apModelName = new LPSTR[10];
				//m_apModelName[0] = "TEST0";
				//m_apModelName2 = new char[10];
				//m_apModelName2[0] = new char[10][50];

			}

			if (memcmp(pStrcur, "MODEL_FILENAME = ", strlen("MODEL_FILENAME = ")) == 0)
			{
				//頭出し
				pStrcur += strlen("MODEL_FILENAME = ");

				//文字列を設定
				strcpy(aStr, pStrcur);

				//必要な文字列の最後の文字までの文字数を数える
				int nNullNum = PopString(pStrcur, &aStr[0]);

				//文字列を取り戻す
				strcpy(aStr, pStrcur);

				//最後の文字にNULL文字を入れる
				aStr[nNullNum - 2] = '\0';

				//対象の文字列から抜き出し
				strcpy(&m_apModelName[m_nCntModel][0], aStr);

				//文字列を格納
				//strcpy(&m_apModelName2[m_nCntModel], aStr);
				//	"data\\MODEL\\car000.x",				//0
				//	"data\\MODEL\\car001.x",				//1
				//	"data\\MODEL\\box000.x",				//2

				m_nCntModel += 1;
			}
		}
	}

	//ファイルを閉じる
	fclose(pFile);
}


//=============================================================================
//　ファイル読み込み無効文を排除
//=============================================================================
char *CLoad::ReadLine(FILE *pFile, char *pDst)
{
	while (1)
	{
		//１行分読み込み
		fgets(&pDst[0], 256, pFile);

		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pDst, "#", strlen("#")) == 0)
		{
			pDst += strlen("\n");
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, "\t", strlen("\t")) == 0)
		{
			pDst += strlen("\t");
			while (1)
			{
				if (memcmp(pDst, "\t", strlen("\t")) == 0)
				{
					pDst += strlen("\t");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, " ", strlen(" ")) == 0)
		{
			pDst += strlen(" ");
			while (1)
			{
				if (memcmp(pDst, " ", strlen(" ")) == 0)
				{
					pDst += strlen(" ");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, "\n", strlen("\n")) == 0)
		{
			pDst += strlen("\n");
		}
		else
		{
			break;
		}
	}
	return pDst;
}

//=============================================================================
//　ファイル読み込み先頭を排除
//=============================================================================
char * CLoad::GetLineTop(char * pStr)
{
	while (1)
	{
		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{
			pStr += strlen(" ");
			while (1)
			{
				if (memcmp(pStr, " ", strlen(" ")) == 0)
				{
					pStr += strlen(" ");
				}
				else
				{
					break;
				}
				break;
			}
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{
			pStr += strlen("\t");
			while (1)
			{
				if (memcmp(pStr, "\t", strlen("\t")) == 0)
				{
					pStr += strlen("\t");
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	return pStr;
}

//=============================================================================
//　文字数を返す
//=============================================================================
int CLoad::PopString(char * pStr, char * pDest)
{
	int nWord = 0;

	while (1)
	{	//頭出し
		pStr += 1;
		nWord += 1;
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{	//頭出し
			pStr = "\0";
			nWord += 1;
			break;
		}
		if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{	//頭出し
			pStr = "\0";
			nWord += strlen("\t");
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pStr, "\n", strlen("\n")) == 0)
		{
			//頭出し
			nWord += strlen("\n");
			break;
		}
	}
	strcpy(pDest, pStr);
	//文字列の数を返す
	return nWord;
}
