//=============================================================================
//
// メイン処理 [main.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS //警告解除

#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <crtdbg.h>
#include <stdlib.h>
#include <time.h>

//C++ライブラリ
#include <vector>
#include <list>
#include <algorithm>


#include "d3dx9.h"

#define DIRECTINPUT_VERSION (0x0800)	// 警告対処用
#include "dinput.h"
#include "xaudio2.h"	//サウンドの処理に必要


//前方宣言
class CRenderer;
class CScene;

//*****************************************************************************
// ライブラリファイル
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dinput8.lib")

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(1280)	// ウインドウの幅
#define SCREEN_HEIGHT	(720)	// ウインドウの高さ
#define MAX_SCENE       (10000)
//2Dポリゴン頂点フォーマット( 頂点座標[2D] / 頂点カラー / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//3Dポリゴン頂点フォーマット( 頂点座標[3D] / 法線ベクトル / 頂点カラー / テクスチャ座標 )
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
//*****************************************************************************
// 構造体定義
//*****************************************************************************
// ２Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// 座標変換用係数(1.0fで固定)
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_2D;

// 3Dポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	D3DXVECTOR3 nor;	// 法線ベクトル
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ
} VERTEX_3D;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
#endif