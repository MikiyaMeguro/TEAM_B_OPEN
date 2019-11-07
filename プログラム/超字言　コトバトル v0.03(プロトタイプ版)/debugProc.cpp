//=============================================================================
//
// デバック表示処理 [debugProc.cpp]
// Author : 目黒 未来也
//
//=============================================================================
#include "debugProc.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPD3DXFONT CDebugProc::m_pFont = NULL;
char CDebugProc::m_aStr[MAX_CHARDATA] = {};

//=============================================================================
// デバック表示クラスのコンストラクタ
//=============================================================================
CDebugProc::CDebugProc()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CDebugProc::~CDebugProc()
{
}

//=============================================================================
// デバック表示の初期化処理
//=============================================================================
void CDebugProc::Init(void)
{
#ifdef _DEBUG
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
#endif

}

//=============================================================================
// デバック表示の終了処理
//=============================================================================
void CDebugProc::Uninit(void)
{
#ifdef _DEBUG
	// デバッグ情報表示用フォントの破棄
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
#endif
}

//=============================================================================
// デバック表示の表示処理
//=============================================================================
void CDebugProc::Print(char *fmt, ...)
{
#ifdef _DEBUG

	int nNum = 0;
	double fNum = 0.0f;
	char cNum[1024];

	// 任意個の引数を１個の変数に変換
	va_list ap;

	// 可変長引数を１個の変数にまとめる
	va_start(ap, fmt);

	while (*fmt)
	{
		switch (*fmt)
		{
		case 'c':	// char型
			strcat(m_aStr, va_arg(ap, char*));	// リストの中のキャラ型を取り出して、m_aStrに入れる
			break;

		case 'n':	// int型
			nNum = va_arg(ap, int);		// リストの中のint型数字を引き出す

			sprintf(cNum, "%d", nNum);	// %dに入るint型をcNumのキャラ型に入れる

			strcat(m_aStr, cNum);		// 文字のデータにint型の数字を入れる

			break;

		case 'f':	// float型
			fNum = va_arg(ap, double);		// リストの中のfloat型数字を引き出す

			sprintf(cNum, "%.1f", fNum);	// %.1fに入るfloat型をcNumのキャラ型に入れる

			strcat(m_aStr, cNum);			// 文字のデータにfloat型の数字を入れる

			break;
		}

		fmt++;	// フォーマットの文字を１文字進める
	}


	strcat(m_aStr, "\n");

	va_end(ap);
#endif
}

//=============================================================================
// デバック表示の削除処理
//=============================================================================
void CDebugProc::ReleseStr(void)
{
#ifdef _DEBUG
	for (int nCntStr = 0; nCntStr < MAX_CHARDATA; nCntStr++)
	{
		if (m_aStr[nCntStr] != NULL)
		{
			m_aStr[nCntStr] = NULL;
		}
	}
#endif
}

//=============================================================================
// デバック表示の表示処理
//=============================================================================
void CDebugProc::Draw(void)
{
#ifdef _DEBUG
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//
	D3DXCOLOR col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	// テキスト描画
	m_pFont->DrawText(NULL, m_aStr, -1, &rect, DT_LEFT, col);
#endif

}