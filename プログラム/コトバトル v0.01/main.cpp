//=============================================================================
//
// メイン処理 [main.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "main.h"
#include "Manager.h"
#include "DebugProc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"AppClass"				// ウインドウのクラス名
#define WINDOW_NAME		"超字言　コトバトル"	// ウインドウのキャプション名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//=============================================================================
// メイン関数
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//インスタンス生成
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	HWND hWnd;
	MSG msg;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	int nCountFPS = 0;
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// 指定したクライアント領域を確保するために必要なウィンドウ座標を計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
						WINDOW_NAME,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						(rect.right - rect.left),
						(rect.bottom - rect.top),
						NULL,
						NULL,
						hInstance,
						NULL);

	//マネージャの生成
	CManager *pManager = NULL;
	pManager = new CManager;

	if (pManager != NULL)
	{
		pManager->Init(hInstance,hWnd);
	}

	// 分解能を設定
	timeBeginPeriod(1);

	// フレームカウント初期化
	dwCurrentTime =
	dwFrameCount = 0;
	dwExecLastTime =
	dwFPSLastTime = timeGetTime();

	// ウインドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// メッセージループ
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();	// 現在の時間を取得
			if((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5秒ごとに実行
#ifdef _DEBUG
				// FPSを算出
				nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
				dwFPSLastTime = dwCurrentTime;	// 現在の時間を保存
				dwFrameCount = 0;
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 1/60秒経過
				dwExecLastTime = dwCurrentTime;	// 現在の時間を保存

				if (pManager != NULL)
				{
#ifdef _DEBUG
					CDebugProc::Print("FPS:%d\n", nCountFPS);//FPSセット
#endif
					pManager->Update();
					pManager->Draw();
				}

				dwFrameCount++;
			}
		}
	}

	//マネージャの解放
	if (pManager != NULL)
	{
		pManager->Uninit();

		delete pManager;
		pManager = NULL;

	}

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 分解能を戻す
	timeEndPeriod(1);

	return (int)msg.wParam;
}

//=============================================================================
// ウインドウプロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:				// [ESC]キーが押された
			DestroyWindow(hWnd);	// ウィンドウを破棄するよう指示する
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

