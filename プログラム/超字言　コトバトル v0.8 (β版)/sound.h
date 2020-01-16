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

		SOUND_LABEL_SE_SWITCHON,		// スイッチ押した音ON
		SOUND_LABEL_SE_SWITCHOFF,		// スイッチ押した音OFF

		SOUND_LABEL_SE_POINTUP,			// ポイントアップ
		SOUND_LABEL_SE_POINTDOWN,		// ポイントダウン

		SOUND_LABEL_SE_SELECT00,		// 決定音
		SOUND_LABEL_SE_SELECT01,		// キャンセルお”ぉ”ん
		SOUND_LABEL_SE_SELECT02,		// 選択恩
		SOUND_LABEL_SE_SELECT03,		// キャラクター選択音
		SOUND_LABEL_SE_SELECT04,		// ゲームスタート

		SOUND_LABEL_SE_VOICE00,		//タイトルコール
		SOUND_LABEL_SE_VOICE01,		//タイトルコール2
		SOUND_LABEL_SE_VOICE02,		//キャラ選択音　犬
		SOUND_LABEL_SE_VOICE03,		//キャラ選択音　熊
		SOUND_LABEL_SE_VOICE04,		//キャラ選択音　猫
		SOUND_LABEL_SE_VOICE05,		//キャラ選択音　兎
		SOUND_LABEL_SE_VOICE06,		//犬　攻撃ボイス
		SOUND_LABEL_SE_VOICE07,		//犬　攻撃ボイス
		SOUND_LABEL_SE_VOICE08,		//犬　被弾ボイス
		SOUND_LABEL_SE_VOICE09,		//熊　攻撃ボイス
		SOUND_LABEL_SE_VOICE10,		//熊　攻撃ボイス
		SOUND_LABEL_SE_VOICE11,		//熊　被弾ボイス
		SOUND_LABEL_SE_VOICE12,		//猫　攻撃ボイス
		SOUND_LABEL_SE_VOICE13,		//猫　攻撃ボイス
		SOUND_LABEL_SE_VOICE14,		//猫　被弾ボイス
		SOUND_LABEL_SE_VOICE15,		//兎　攻撃ボイス
		SOUND_LABEL_SE_VOICE16,		//兎　攻撃ボイス
		SOUND_LABEL_SE_VOICE17,		//兎　被弾ボイス
		SOUND_LABEL_SE_VOICE18,		//犬　優勝コメント
		SOUND_LABEL_SE_VOICE19,		//熊　優勝コメント
		SOUND_LABEL_SE_VOICE20,		//猫　優勝コメント
		SOUND_LABEL_SE_VOICE21,		//兎　優勝コメント

		SOUND_LABEL_SE_TITLE,		// タイトル


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

		{ "data/SE/switchon.wav", 0 },		// スイッチ押した音ON
		{ "data/SE/switchoff.wav", 0 },		// スイッチ押した音OFF

		{ "data/SE/pointup.wav", 0 },		// ポイントアップ
		{ "data/SE/pointupdown.wav", 0 },	// ポイントダウン

		{ "data/SE/Select1.wav", 0 },	// 決定音
		{ "data/SE/Select2.wav", 0 },	// キャンセル恩
		{ "data/SE/Select3.wav", 0 },	// 選択音
		{ "data/SE/Select4.wav", 0 },	// キャラクター選択音
		{ "data/SE/Select5.wav", 0 },	// ゲームスタート

		{ "data/VOICE/TitleCall.wav", 0 },			//タイトルコール
		{ "data/VOICE/TitleCall2.wav", 0 },			//タイトルコール2
		{ "data/VOICE/DogSelectVoice.wav", 0 },		//キャラ選択音　犬
		{ "data/VOICE/BearSelectVoice.wav", 0 },	//キャラ選択音　熊
		{ "data/VOICE/CatSelectVoice.wav", 0 },		//キャラ選択音　猫
		{ "data/VOICE/RabbitSelectVoice.wav", 0 },	//キャラ選択音　兎
		{ "data/VOICE/DogAttack.wav", 0 },			//犬　攻撃ボイス
		{ "data/VOICE/DogAttack2.wav", 0 },			//犬　攻撃ボイス
		{ "data/VOICE/DogDamage.wav", 0 },			//犬　被弾ボイス
		{ "data/VOICE/BearAttack.wav", 0 },			//熊　攻撃ボイス
		{ "data/VOICE/BearAttack2.wav", 0 },		//熊　攻撃ボイス
		{ "data/VOICE/BearDamage.wav", 0 },			//熊　被弾ボイス
		{ "data/VOICE/CatAttack.wav", 0 },			//猫　攻撃ボイス
		{ "data/VOICE/CatAttack2.wav", 0 },			//猫　攻撃ボイス
		{ "data/VOICE/CatDamage.wav", 0 },			//猫　被弾ボイス
		{ "data/VOICE/RabbitAttack.wav", 0 },		//兎　攻撃ボイス
		{ "data/VOICE/RabbitAttack2.wav", 0 },		//兎　攻撃ボイス
		{ "data/VOICE/RabbitDamage.wav", 0 },		//兎　被弾ボイス
		{ "data/VOICE/DogWin.wav", 0 },				//犬　優勝コメント
		{ "data/VOICE/BearWin.wav", 0 },			//熊　優勝コメント
		{ "data/VOICE/CatWin.wav", 0 },				//猫　優勝コメント
		{ "data/VOICE/RabbitWin.wav", 0 },			//兎　優勝コメント

		{ "data/SE/Title.wav", 0 },	// タイトル

	};
};
#endif
