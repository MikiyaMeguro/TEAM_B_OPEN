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

std::string CDebugProc::m_strDebug;		//宣言時にすでに初期化されているのでここで何かする必要はない

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
	//文字列の削除(初期化)
	m_strDebug.clear();
	m_strDebug.shrink_to_fit();

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

	// 任意個の引数を１個の変数に変換
	va_list ap;

	// 可変長引数を１個の変数にまとめる
	va_start(ap, fmt);

	while (*fmt)
	{
		switch (*fmt)
		{
		case 'c':	// char型
			m_strDebug += va_arg(ap, char*);		// リストの中のキャラ型を取り出して、m_strDebugに入れる
			break;

		case 'n':	// int型
			m_strDebug += std::to_string(va_arg(ap, int));//引き出した数字をstring型に変換して入れる
			m_strDebug += " ";	//数値の間は1マス開ける
			break;

		case 'f':	// float型
			m_strDebug += std::_Floating_to_string("%.1f", va_arg(ap, double));//引き出した数字をstring型に変換して入れる
			m_strDebug += " ";	//数値の間は1マス開ける
			break;
		}

		fmt++;	// フォーマットの文字を１文字進める
	}

	m_strDebug += "\n";	//改行

	va_end(ap);	//終了処理
#endif
}

//=============================================================================
// デバック表示の削除処理
//=============================================================================
void CDebugProc::ReleseStr(void)
{
#ifdef _DEBUG
	//文字列の削除(初期化)
	m_strDebug.clear();
	m_strDebug.shrink_to_fit();

#endif
}

//=============================================================================
// デバック表示の表示処理
//=============================================================================
void CDebugProc::Draw(void)
{
#ifdef _DEBUG
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//色指定
	D3DXCOLOR col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	// テキスト描画
	m_pFont->DrawText(NULL, m_strDebug.c_str(), -1, &rect, DT_LEFT, col);

#endif

}