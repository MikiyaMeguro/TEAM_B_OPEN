//---------------------------------------------------------------------
//	オブジェクト配置処理(SetObject.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "SetObject.h"
#include "game.h"
#include "fade.h"
#include "sceneX.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_SPEED     (5.0f)
#define MODEL_DEPTH     (50.0f)

#define PLAYER_DEPTH	(15)		// プレイヤーの幅調整用
#define PLAYER_HEIGHT	(50.0f)		// プレイヤーの背の高さ

#define FILE_NAME0				("data\\TEXT\\SetModel.txt")

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------

//--------------------------------------------
//オブジェクトクラス コンストラクタ
//--------------------------------------------
CSetObject::CSetObject() : CScene(3, CScene::OBJTYPE_SCENEX)
{
}

//--------------------------------------------
//オブジェクトクラス デストラクタ
//--------------------------------------------
CSetObject::~CSetObject()
{
}

//--------------------------------------------
//オブジェクトの生成
//--------------------------------------------
CSetObject *CSetObject::Create()
{
	//オブジェクトポインタ
	CSetObject *pObjectBG;
	pObjectBG = new CSetObject;
	//オブジェクトの初期化
	pObjectBG->Init();
	//オブジェクトの情報を返す
	return pObjectBG;
}

//=============================================================================
// オブジェクトの初期化処理
//=============================================================================
HRESULT CSetObject::Init()
{
	//オブジェクト種類の設定
	CScene::SetObjType(CScene::OBJTYPE_SCENEX);

	return S_OK;
}

//=============================================================================
// オブジェクトの終了処理
//=============================================================================
void CSetObject::Uninit(void)
{
	//自分を消す(オブジェクトを破棄)
	Release();
}

//=============================================================================
// オブジェクトの更新処理
//=============================================================================
void CSetObject::Update(void)
{
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

	if (pInput->GetTrigger(DIK_RCONTROL) == true)
	{	//ファイルロード
		LoadFile();
	}
}

//=============================================================================
// オブジェクトの描画処理
//=============================================================================
void CSetObject::Draw(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DXMATRIX mtxParent;

}


//=============================================================================
// オブジェクトの配置情報を読み込み
//=============================================================================
void CSetObject::LoadFile(void)
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
	int nType = 0;			//モデルの種類
	D3DXVECTOR3 ModelPos;	//モデルの位置
	D3DXVECTOR3 ModelRot;
	D3DXVECTOR3 ModelScale;
	int			nCollisionType;

	//ファイルを開く 読み込み
	pFile = fopen(FILE_NAME0, "r");
	//NULLチェック
	if (pFile != NULL)
	{
		while (1)
		{
			//文字列の先頭を設定
			pStrcur = ReadLine(pFile, &aLine[0]);
			//文字列を取り出す
			strcpy(aStr, pStrcur);

			//オブジェクト読み込み
			if (memcmp(pStrcur, "MODELSET", strlen("MODELSET")) == 0)
			{
				//頭出し
				pStrcur += strlen("MODELSET");
				//文字列の先頭を設定
				pStrcur = ReadLine(pFile, &aLine[0]);
				//種類
				if (memcmp(pStrcur, "TYPE = ", strlen("TYPE = ")) == 0)
				{
					//頭出し
					pStrcur += strlen("TYPE = ");
					//文字列の先頭を設定
					strcpy(aStr, pStrcur);
					//文字列抜き出し
					nType = atoi(pStrcur);
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
				}
				//位置
				if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
				{
					//頭出し
					pStrcur += strlen("POS = ");
					//文字列の先頭を設定
					strcpy(aStr, pStrcur);

					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//POS.X代入
					ModelPos.x = (float)atof(pStrcur);
					//文字数分進める
					pStrcur += nWord;

					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//POS.Y代入
					ModelPos.y = (float)atof(pStrcur);
					//文字数分進める
					pStrcur += nWord;

					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//POS.Z代入
					ModelPos.z = (float)atof(pStrcur);
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
				}
				//ROTを読み込み
				if (memcmp(pStrcur, "ROT = ", strlen("ROT = ")) == 0)
				{
					//頭出し
					pStrcur += strlen("ROT = ");
					//文字列の先頭を設定
					strcpy(aStr, pStrcur);

					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//文字列変換
					ModelRot.x = (float)atof(pStrcur);

					//文字数分進める
					pStrcur += nWord;
					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//文字列変換
					ModelRot.y = (float)atof(pStrcur);

					//文字数分進める
					pStrcur += nWord;
					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//文字列変換
					ModelRot.z = (float)atof(pStrcur);
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
				}
				//SCALEを読み込み
				if (memcmp(pStrcur, "SCALE = ", strlen("SCALE = ")) == 0)
				{
					//頭出し
					pStrcur += strlen("SCALE = ");
					//文字列の先頭を設定
					strcpy(aStr, pStrcur);

					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//文字列変換
					ModelScale.x = (float)atof(pStrcur);

					//文字数分進める
					pStrcur += nWord;
					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//文字列変換
					ModelScale.y = (float)atof(pStrcur);

					//文字数分進める
					pStrcur += nWord;
					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//文字列変換
					ModelScale.z = (float)atof(pStrcur);
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
				}
				//COLLISIONを読み込み
				if (memcmp(pStrcur, "COLLISION = ", strlen("COLLISION = ")) == 0)
				{
					//頭出し
					pStrcur += strlen("COLLISION = ");
					//文字列の先頭を設定
					strcpy(aStr, pStrcur);

					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//文字列変換
					nCollisionType = (int)atoi(pStrcur);
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
				}
			}
			//モデルを生成
			if (memcmp(pStrcur, "END_MODELSET", strlen("END_MODELSET")) == 0)
			{
				//CObjectBG::Create(ModelPos, ModelRot, D3DXVECTOR3(0.0f, 0.0f, 0.0f)
				//	, (CObjectBG::MODELTYPE)nType, CObjectBG::MOVETYPE_NONE, 1);
				CSceneX::Create(ModelPos, ModelRot, ModelScale, (CLoad::MODEL)nType, nCollisionType);
			}
			//スクリプトの終わり
			if (memcmp(pStrcur, "END_SCRIPT	", strlen("END_SCRIPT")) == 0)
			{
				break;
			}
		}
	}

	//ファイルを閉じる
	fclose(pFile);
}


//=============================================================================
//　ファイル読み込み無効文を排除
//=============================================================================
char *CSetObject::ReadLine(FILE *pFile, char *pDst)
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
char * CSetObject::GetLineTop(char * pStr)
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
int CSetObject::PopString(char * pStr, char * pDest)
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
