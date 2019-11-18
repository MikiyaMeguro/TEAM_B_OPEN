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

		SOUND_LABEL_SE_BULLET000,		// 弾との衝突音[ノックバック大]
		SOUND_LABEL_SE_BULLET001,		// 弾との衝突音[スピード]
		SOUND_LABEL_SE_BULLET002,		// 弾との衝突音[跳ね返る]
		SOUND_LABEL_SE_BULLET003,		// 弾との衝突音[貫通]

		SOUND_LABEL_SE_GETTEXT000,		// 文字取得音[1文字目取得]
		SOUND_LABEL_SE_GETTEXT001,		// 文字取得音[2文字目取得]
		SOUND_LABEL_SE_GETTEXT002,		// 文字取得音[3文字目取得]

		SOUND_LABEL_SE_STEP,			// ステップ
		SOUND_LABEL_SE_PAUSEOPEN,		// ポーズ音押した際の音
		SOUND_LABEL_SE_PAUSECLOSE,		// ポーズ終えた際の音

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

	float GetVolume(SOUND_LABEL label);						// 音量の取得
	void SetVolume(SOUND_LABEL label, float fVolume);		// 音量の設定

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

		{ "data/SE/bullet000.wav", 0 },			// 弾との衝突音[ノックバック大]
		{ "data/SE/bullet001.wav", 0 },			// 弾との衝突音[スピード]
		{ "data/SE/bullet002.wav", 0 },			// 弾との衝突音[跳ね返る]
		{ "data/SE/bullet003.wav", 0 },			// 弾との衝突音[貫通]

		{ "data/SE/gettext000.wav", 0 },		// 文字取得音[1文字目取得]
		{ "data/SE/gettext001.wav", 0 },		// 文字取得音[2文字目取得]
		{ "data/SE/gettext002.wav", 0 },		// 文字取得音[3文字目取得]

		{ "data/SE/step.wav", 0 },				// ステップ
		{ "data/SE/pause_open.wav", 0 },		// ポーズ音押した際の音
		{ "data/SE/pause_close.wav", 0 },		// ポーズ終えた際の音


	};
};
#endif
