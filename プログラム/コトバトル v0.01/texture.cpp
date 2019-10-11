//=============================================================================
//
// テクスチャクラス [texture.cpp] {CTexture}
// Author : Kodama Yuto
//
//
//	勝手に編集しないこと！！(コメントはOK)
//
//=============================================================================
#include "texture.h"
#include "manager.h"

//==================================================================
// 静的メンバ変数
//==================================================================
std::vector<CTexture::TexData> CTexture::m_TexData;

//==================================================================
// マクロ定義
//==================================================================
#define TEXDATA ("data/TEXT/TexLoad.txt")		//テキストのアドレス

//==================================================================
// テクスチャ読み込み
//==================================================================
HRESULT CTexture::Load(void) {
	//テクスチャのデータ読み込み
	//変数宣言
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	FILE* pFile = NULL;		// ファイルポインタ
	char ReadText[256];		// 読み込んだ文字列を入れておく
	char HeadText[256];		// 比較用
	char DustBox[256];		// 使用しないものを入れておく
	int nCntTexData = 0;	// 読み込み数カウンタ

	TexData OneTexData;			//texにデータを入れるための変数
	m_TexData.clear();


	//ファイルオープン
	pFile = fopen(TEXDATA, "r");

	if (pFile != NULL)
	{//ファイルが開かれていれば
		while (strcmp(HeadText, "START_LOAD") != 0)
		{// "START_LOAD" が読み込まれるまで繰り返し文字列を読み取る
			fgets(ReadText, sizeof(ReadText), pFile);
			sscanf(ReadText, "%s", &HeadText);
		}
		if (strcmp(HeadText, "START_LOAD") == 0)
		{// "START_LOAD" が読み取れた場合、処理開始
			while (strcmp(HeadText, "END_LOAD") != 0)
			{// "END_LOAD" が読み込まれるまで繰り返し文字列を読み取る
				fgets(ReadText, sizeof(ReadText), pFile);
				sscanf(ReadText, "%s", &HeadText);

				if (strcmp(HeadText, "\n") == 0)
				{// 文字列の先頭が [\n](改行) の場合処理しない

				}
				else if (strcmp(HeadText, "DATA") == 0)
				{// "DATA" が読み取れた場合

					//DATAより後ろのデータをスペース区切りで読み込む
					sscanf(ReadText, "%s %c %d %s %s",
						&DustBox, &DustBox,
						&OneTexData.nID,
						&OneTexData.TexAddress,
						&OneTexData.TexNameTag);

					//読み取ったテクスチャをvector配列の中に入れる
					m_TexData.emplace_back(OneTexData);
				}
			}
		}

		//ファイルクローズ
		if (pFile != NULL)
		{
			fclose(pFile);
			pFile = NULL;
		}

		if (m_TexData.size() > 0)
		{
			//テクスチャデータの初期化
			for (auto itr = m_TexData.begin(); itr != m_TexData.end(); itr++)	//auto itr = vector配列内の位置を指し示すポインタのようなもの(イテレータ)
			{
				itr->pTexture = NULL;
			}
		}

	}
	else
	{//ここに入ったらエラー(そのファイルがないor開けない)
		MessageBox(NULL, "テクスチャ情報ファイルが開けませんでした。", NULL, MB_OK);
		return S_FALSE;
	}

	return S_OK;
}

//==================================================================
// テクスチャ解放
//==================================================================
void CTexture::Unload(void)
{
	if (m_TexData.size() > 0)
	{
		for (auto itr = m_TexData.begin(); itr != m_TexData.end(); itr++)
		{
			//テクスチャの解放
			if (itr->pTexture != NULL)
			{
				itr->pTexture->Release();
				itr->pTexture = NULL;
			}
			itr->nID = 0;
		}
	}
}
//==================================================================
// テクスチャ取得
//==================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(const int nID) {			//ID
	if (m_TexData.size() > 0)
	{
		auto result = std::find(m_TexData.begin(), m_TexData.end(), nID);

		if (result != m_TexData.end())
		{//IDが一致したら
			if (result->pTexture == NULL)
			{//まだテクスチャが作られていなければ作る
				Create(result->TexAddress, result->pTexture);
			}
			return result->pTexture;
		}
	}
	return NULL;
}
LPDIRECT3DTEXTURE9 CTexture::GetTexture(const LPCSTR Tag) {		//タグ
	if (m_TexData.size() > 0)
	{
		auto result = std::find(m_TexData.begin(), m_TexData.end(), Tag);
		if (result != m_TexData.end())
		{//タグが一致したら
			if (result->pTexture == NULL)
			{//まだテクスチャが作られていなければ作る
				Create(result->TexAddress, result->pTexture);
			}
			return result->pTexture;
		}
	}
	return NULL;
}

//==================================================================
// 使わなくなったテクスチャの解放
//==================================================================
void CTexture::Release(const int nID)//ID
{
	if (m_TexData.size() > 0)
	{
		auto result = std::find(m_TexData.begin(), m_TexData.end(), nID);

		if (result != m_TexData.end())
		{//IDが一致したら
			if (result->pTexture != NULL)
			{//テクスチャが作られているなら
				result->pTexture->Release();
				result->pTexture = NULL;
			}
		}
	}
}
void CTexture::Release(const LPCSTR Tag)//タグ
{
	if (m_TexData.size() > 0)
	{
		auto result = std::find(m_TexData.begin(), m_TexData.end(), Tag);
		if (result != m_TexData.end())
		{//タグが一致したら
			if (result->pTexture != NULL)
			{//テクスチャが作られているなら
				result->pTexture->Release();
				result->pTexture = NULL;
			}
		}
	}
}

//==================================================================
// テクスチャ生成
//==================================================================
void CTexture::Create(LPCSTR address, LPDIRECT3DTEXTURE9& pTexture)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	if (pTexture == NULL)
	{//テクスチャの生成
		D3DXCreateTextureFromFile(pDevice,
			address,
			&pTexture);
	}
}

//==================================================================
// テクスチャ数カウント
//==================================================================
int CTexture::GetTexNum(bool bCreate)
{
	int nTexNum = m_TexData.size();	//テクスチャの数(ファイルから読み込んだテクスチャの数で初期化)

	if (bCreate == true)
	{//テクスチャポインタがあるものだけカウントするなら
		nTexNum = 0;		//いったん0で初期化

		if (m_TexData.size() > 0)
		{//読み込んだテクスチャ数が0以上なら

			for (auto itr = m_TexData.begin(); itr != m_TexData.end(); itr++)
			{//Textureが作られていれば++
				if (itr->pTexture != NULL)
				{
					nTexNum++;
				}
			}
		}
	}
	return nTexNum;
}
