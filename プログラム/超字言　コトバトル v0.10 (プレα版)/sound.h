//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 目黒 未来也
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*********************************************************************
//サウンドクラスの定義
//*********************************************************************
//基本クラス
class CSound
{
public:
	// サウンドファイル
	typedef enum //ラベルと数と並びを揃える
	{
		SOUND_LABEL_BGM_TITLE = 0,		// タイトル
		SOUND_LABEL_BGM_SELECT,			// セレクト
		SOUND_LABEL_BGM_TUTORIAL,		// チュートリアル
		SOUND_LABEL_BGM_CHARACTERSELECT,// キャラクターセレクト
		SOUND_LABEL_BGM_STAGESELECT,	// ステージセレクト
		SOUND_LABEL_BGM_GAME000,		// ゲーム[機械ステージ]
		SOUND_LABEL_BGM_GAME001,		// ゲーム[天候ステージ]
		SOUND_LABEL_BGM_GAME002,		// ゲーム[地形ステージ]
		SOUND_LABEL_BGM_RANKING,		// ランキング
		SOUND_LABEL_MAX,
	} SOUND_LABEL;
	// パラメータ構造体定義
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント(-1でループ再生)
	} SOUNDPARAM;

	CSound();
	~CSound();
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

protected:
	IXAudio2				*m_pXAudio2 = NULL;								// XAudio2オブジェクトへのポインタ
	IXAudio2MasteringVoice	*m_pMasteringVoice = NULL;						// マスターボイスへのポインタ
	IXAudio2SourceVoice		*m_apSourceVoice[SOUND_LABEL_MAX] = {};			// ソースボイスへのポインタ
	BYTE					*m_apDataAudio[SOUND_LABEL_MAX] = {};			// オーディオデータへのポインタ
	DWORD					m_aSizeAudio[SOUND_LABEL_MAX] = {};				// オーディオデータサイズ
    // 各音素材のパラメータ ラベルと数と並びを揃える
	SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
	{
		{ "data/BGM/TITLE.wav", -1 },			// タイトル
		{ "data/BGM/SELECT.wav", -1 },			// セレクト
		{ "data/BGM/TUTORIAL.wav", -1 },		// チュートリアル
		{ "data/BGM/CHARACTERSELECT.wav", -1 },	// キャラクターセレクト
		{ "data/BGM/STAGESELECT.wav", -1 },		// ステージセレクト
		{ "data/BGM/GAME000.wav", -1 },			// ゲーム[機械ステージ]
		{ "data/BGM/GAME000.wav", -1 },			// ゲーム[天候ステージ]
		{ "data/BGM/GAME000.wav", -1 },			// ゲーム[地形ステージ]
		{ "data/BGM/RANKING.wav", -1 },			// ランキング

	};
};
#endif
