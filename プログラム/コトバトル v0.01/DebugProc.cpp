//=============================================================================
//
// デバック情報表示処理 [DebugProc.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "DebugProc.h"
#include "Manager.h"

//==================================================================
//	静的メンバ(staticメンバ)変数宣言
//==================================================================
LPD3DXFONT CDebugProc::m_pFont = NULL;
char CDebugProc::m_aStr[MAX_CHARDATA] = {};

//==================================================================
//	コンストラクタ&デストラクタ
//==================================================================
CDebugProc::CDebugProc()
{

}
CDebugProc::~CDebugProc()
{

}

//==================================================================
//	初期化処理
//==================================================================
void CDebugProc::Init(void)
{
	//変数宣言
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//フォントの作成
	D3DXCreateFont(pDevice, 20, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

}

//==================================================================
//	終了処理
//==================================================================
void CDebugProc::Uninit(void)
{
	// デバッグ情報表示用フォントの破棄
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
}
//==================================================================
//	入力処理(printfとほぼ同様の処理)
//==================================================================
void CDebugProc::Print(char* fmt, ...)
{/*可変長引数を編集したいときは必ずva_startとva_endの間でやること*/

	//変数宣言
	va_list args;				//可変長引数のリスト	[va = variable(可変)]
	char cPrint[256];			//編集できるようにするためにいったん格納しておく変数

	va_start(args, fmt);			//可変長引数の編集開始

	vsprintf_s(cPrint,fmt, args);	//変数にfmtとargsを合成したものを入れる

	va_end(args);					//可変長引数の編集終了

	/*文字列を編集したいときはここでやる*/

	strcat_s(m_aStr, cPrint);		//描画用の変数に文字列を格納する
}

//==================================================================
//	描画(出力)処理
//==================================================================
void CDebugProc::Draw(void)
{
#ifdef _DEBUG
	//変数宣言
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };	//描画範囲の指定

	// テキスト描画
	m_pFont->DrawText(NULL,
		m_aStr,
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
#endif
	//文字列初期化
	ZeroMemory(m_aStr,sizeof(char) * MAX_CHARDATA);
}
