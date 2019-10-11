//=============================================================================
//
// サウンド処理 [sound.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

class CSound
{
public:
	//*************************************
	// サウンドファイル
	//*************************************
	typedef enum
	{
		SOUND_LABEL_BGM_000,		// BGM 0(ゲームBGM1)
		SOUND_LABEL_MAX
	} SOUND_LABEL;

	//*****************************************************************************
	// パラメータ構造体定義
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント(-1でループ再生)
	} SOUNDPARAM;

	CSound();
	~CSound();

	static CSound* Create(HWND hWnd);
	HRESULT Init(HWND hWnd);
	void Uninit(void);

	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void StopAll(void);

private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);// チャンクのチェック
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);// チャンクデータの読み込み

	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2オブジェクトへのポインタ
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// マスターボイスへのポインタ
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイスへのポインタ
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータへのポインタ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ

																// 各音素材のパラメータ
	SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
	{// -1 ループ再生　,　0 通常再生
		{ "data/BGM/CaravanMode0.wav",-1 },
	};

};
#endif
