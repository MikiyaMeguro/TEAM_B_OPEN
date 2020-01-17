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

		SOUND_LABEL_SE_CURTAIN,			// カーテンの音
		SOUND_LABEL_SE_SWITCHON,		// スイッチ押した音ON
		SOUND_LABEL_SE_SWITCHOFF,		// スイッチ押した音OFF

		SOUND_LABEL_SE_POINTUP,			// ポイントアップ
		SOUND_LABEL_SE_POINTDOWN,		// ポイントダウン

		SOUND_LABEL_SE_SELECT00,		// 決定音
		SOUND_LABEL_SE_SELECT01,		// キャンセルお”ぉ”ん
		SOUND_LABEL_SE_SELECT02,		// 選択恩
		SOUND_LABEL_SE_SELECT03,		// キャラクター選択音
		SOUND_LABEL_SE_SELECT04,		// ゲームスタート

		SOUND_LABEL_VOICE_TITLECALL00,		//タイトルコール
		SOUND_LABEL_VOICE_TITLECALL01,		//タイトルコール2
		SOUND_LABEL_VOICE_SELECT_DOG,		//キャラ選択音　犬
		SOUND_LABEL_VOICE_SELECT_BEAR,		//キャラ選択音　熊
		SOUND_LABEL_VOICE_SELECT_CAT,		//キャラ選択音　猫
		SOUND_LABEL_VOICE_SELECT_RABBIT,	//キャラ選択音　兎
		SOUND_LABEL_VOICE_DOG_ATTACK00,		//犬　攻撃ボイス
		SOUND_LABEL_VOICE_DOG_ATTACK01,		//犬　攻撃ボイス
		SOUND_LABEL_VOICE_DOG_DAMAGE00,		//犬　被弾ボイス
		SOUND_LABEL_VOICE_BEAR_ATTACK00,	//熊　攻撃ボイス
		SOUND_LABEL_VOICE_BEAR_ATTACK01,	//熊　攻撃ボイス
		SOUND_LABEL_VOICE_BEAR_DAMAGE00,	//熊　被弾ボイス
		SOUND_LABEL_VOICE_CAT_ATTACK00,		//猫　攻撃ボイス
		SOUND_LABEL_VOICE_CAT_ATTACK01,		//猫　攻撃ボイス
		SOUND_LABEL_VOICE_CAT_DAMAGE00,		//猫　被弾ボイス
		SOUND_LABEL_VOICE_RABBIT_ATTACK00,	//兎　攻撃ボイス
		SOUND_LABEL_VOICE_RABBIT_ATTACK01,	//兎　攻撃ボイス
		SOUND_LABEL_VOICE_RABBIT_DAMAGE00,	//兎　被弾ボイス
		SOUND_LABEL_VOICE_DOG_VICTORY,		//犬　優勝コメント
		SOUND_LABEL_VOICE_BEAR_VICTORY,		//熊　優勝コメント
		SOUND_LABEL_VOICE_CAT_VICTORY,		//猫　優勝コメント
		SOUND_LABEL_VOICE_RABBIT_VICTORY,	//兎　優勝コメント

		SOUND_LABEL_SE_GAMESTART00,	//コトバトル
		SOUND_LABEL_SE_GAMESTART01,	//スタート
		SOUND_LABEL_SE_GAMEEND,		//そこまで


		SOUND_LABEL_SE_TITLE,		// タイトル

		SOUND_LABEL_SE_EXPLOSION, //爆発

		// 文字モデルの名前
		SOUND_LABEL_WORDVOICE_KURUMA,		// くるま
		SOUND_LABEL_WORDVOICE_MAIKU,		// まいく
		SOUND_LABEL_WORDVOICE_TUKUE,		// つくえ
		SOUND_LABEL_WORDVOICE_PURIN,		// ぷりん
		SOUND_LABEL_WORDVOICE_NAIHU,		// ないふ
		SOUND_LABEL_WORDVOICE_RINGO,		// りんご
		SOUND_LABEL_WORDVOICE_ENOGU,		// えのぐ
		SOUND_LABEL_WORDVOICE_TAIYA,		// たいや
		SOUND_LABEL_WORDVOICE_TAIKO,		// たいこ
		SOUND_LABEL_WORDVOICE_KOIN,			// こいん

		SOUND_LABEL_WORDVOICE_SUIKA,		// すいか
		SOUND_LABEL_WORDVOICE_TARAI,		// たらい
		SOUND_LABEL_WORDVOICE_YAKAN,		// やかん
		SOUND_LABEL_WORDVOICE_IKARI,		// いかり
		SOUND_LABEL_WORDVOICE_IKADA,		// いかだ
		SOUND_LABEL_WORDVOICE_SAIHU,		// さいふ
		SOUND_LABEL_WORDVOICE_KARUTA,		// かるた
		SOUND_LABEL_WORDVOICE_KAMERA,		// かめら
		SOUND_LABEL_WORDVOICE_KOEDA,		// こえだ
		SOUND_LABEL_WORDVOICE_ITIGO,		// いちご

		SOUND_LABEL_WORDVOICE_TAMAGO,		// たまご
		SOUND_LABEL_WORDVOICE_RANNSU,		// らんす
		SOUND_LABEL_WORDVOICE_KADAN,		// かだん
		SOUND_LABEL_WORDVOICE_KATANA,		// かたな
		SOUND_LABEL_WORDVOICE_MARUTA,		// まるた
		SOUND_LABEL_WORDVOICE_TURARA,		// つらら
		SOUND_LABEL_WORDVOICE_DANGO,		// だんご
		SOUND_LABEL_WORDVOICE_MAKURA,		// まくら
		SOUND_LABEL_WORDVOICE_KUNAI,		// くない
		SOUND_LABEL_WORDVOICE_SAKANA,		// さかな

		SOUND_LABEL_WORDVOICE_KAZAN,		// かざん
		SOUND_LABEL_WORDVOICE_NASUKA,		// なすか
		SOUND_LABEL_WORDVOICE_TANKU,		// たんく
		SOUND_LABEL_WORDVOICE_YAGURA,		// やぐら
		SOUND_LABEL_WORDVOICE_ZAISU,		// ざいす
		SOUND_LABEL_WORDVOICE_KONGA,		// こんが
		SOUND_LABEL_WORDVOICE_DAISU,		// だいす
		SOUND_LABEL_WORDVOICE_TAKARA,		// たから
		SOUND_LABEL_WORDVOICE_GARASU,		// がらす
		SOUND_LABEL_WORDVOICE_RINGU,		// りんぐ

		SOUND_LABEL_WORDVOICE_KUSUMA,		// くさや
		SOUND_LABEL_WORDVOICE_SAZAE,		// ざざえ
		SOUND_LABEL_WORDVOICE_TAIRU,		// たいる
		SOUND_LABEL_WORDVOICE_RAISU,		// らいす
		SOUND_LABEL_WORDVOICE_MANGA,		// まんが
		SOUND_LABEL_WORDVOICE_HUIGO,		// ふいご
		SOUND_LABEL_WORDVOICE_NAMAKO,		// なまこ
		SOUND_LABEL_WORDVOICE_KONBU,		// こんぶ
		SOUND_LABEL_WORDVOICE_RAITI,		// らいち
		SOUND_LABEL_WORDVOICE_MASUKU,		// ますく

		SOUND_LABEL_WORDVOICE_MEKABU,		// めかぶ
		SOUND_LABEL_WORDVOICE_KUSURI,		// くすり
		SOUND_LABEL_WORDVOICE_KAIGA,		// かいが
		SOUND_LABEL_WORDVOICE_IKURA,		// いくら
		SOUND_LABEL_WORDVOICE_MENKO,		// めんこ
		SOUND_LABEL_WORDVOICE_MEISU,		// めいす
		SOUND_LABEL_WORDVOICE_SARAI,		// さらい
		SOUND_LABEL_WORDVOICE_INKU,			// いんく
		SOUND_LABEL_WORDVOICE_ZAIRU,		// ざいる
		SOUND_LABEL_WORDVOICE_INARI,		// いなり

		SOUND_LABEL_WORDVOICE_GAKUHU,		// がくふ
		SOUND_LABEL_WORDVOICE_TAITU,		// たいつ
		SOUND_LABEL_WORDVOICE_KAERU,		// かえる
		SOUND_LABEL_WORDVOICE_HURAGU,		// ふらぐ
		SOUND_LABEL_WORDVOICE_SAIN,			// さいん
		SOUND_LABEL_WORDVOICE_TAIMA,		// たいま
		SOUND_LABEL_WORDVOICE_SAKURA,		// さくら
		SOUND_LABEL_WORDVOICE_KAYAKU,		// かやく
		SOUND_LABEL_WORDVOICE_IRUI,			// いるい
		SOUND_LABEL_WORDVOICE_KOTATU,		// こたつ

		SOUND_LABEL_WORDVOICE_KUKUI,		// くくい
		SOUND_LABEL_WORDVOICE_TAKOSU,		// たこす
		SOUND_LABEL_WORDVOICE_SARADA,		// さらだ
		SOUND_LABEL_WORDVOICE_MENMA,		// めんま
		SOUND_LABEL_WORDVOICE_RATAKO,		// たらこ
		SOUND_LABEL_WORDVOICE_KAMEN,		// かめん
		SOUND_LABEL_WORDVOICE_IHUKU,		// いふく
		SOUND_LABEL_WORDVOICE_HUSUMA,		// ふすま
		SOUND_LABEL_WORDVOICE_TANSU,		// たんす
		SOUND_LABEL_WORDVOICE_NAMEKO,		// なめこ

		SOUND_LABEL_WORDVOICE_IRUKA,		// いるか
		SOUND_LABEL_WORDVOICE_ITII,			// いちい
		SOUND_LABEL_WORDVOICE_KANNA,		// かんな
		SOUND_LABEL_WORDVOICE_IEI,			// いえい
		SOUND_LABEL_WORDVOICE_MEDAMA,		// めだま
		SOUND_LABEL_WORDVOICE_SUDATI,		// すだち
		SOUND_LABEL_WORDVOICE_RINSU,		// りんす
		SOUND_LABEL_WORDVOICE_RANPU,		// らんぷ
		SOUND_LABEL_WORDVOICE_SANGO,		// さんご
		SOUND_LABEL_WORDVOICE_SUMAI,		// すまい

		SOUND_LABEL_WORDVOICE_KUKURI,		// くくり
		SOUND_LABEL_WORDVOICE_KORUKU,		// こるく
		SOUND_LABEL_WORDVOICE_NAHUDA,		// なふだ
		SOUND_LABEL_WORDVOICE_SURUME,		// するめ
		SOUND_LABEL_WORDVOICE_SUZUME,		// すずめ
		SOUND_LABEL_WORDVOICE_TITAN,		// ちたん
		SOUND_LABEL_WORDVOICE_YASAI,		// やさい
		SOUND_LABEL_WORDVOICE_HUMEN,		// ふめん
		SOUND_LABEL_WORDVOICE_MAGUMA,		// まぐま
		SOUND_LABEL_WORDVOICE_KANAGU,		// かなぐ

		SOUND_LABEL_WORDVOICE_SARAME,		// ざらめ
		SOUND_LABEL_WORDVOICE_KAMASU,		// かます
		SOUND_LABEL_WORDVOICE_TATARA,		// たたら
		SOUND_LABEL_WORDVOICE_SUKAN,		// ずかん
		SOUND_LABEL_WORDVOICE_すぶた,		// すぶた
		SOUND_LABEL_WORDVOICE_SUZURI,		// すすり
		SOUND_LABEL_WORDVOICE_KAIKO,		// かいこ
		SOUND_LABEL_WORDVOICE_MEDAKA,		// めだか

		SOUND_LABEL_MAX
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

		{ "data/SE/Curtain.wav", 0 },		// カーテン
		{ "data/SE/switchon.wav", 0 },		// スイッチ押した音ON
		{ "data/SE/switchoff.wav", 0 },		// スイッチ押した音OFF

		{ "data/SE/pointup.wav", 0 },		// ポイントアップ
		{ "data/SE/pointupdown.wav", 0 },	// ポイントダウン

		{ "data/SE/Select1.wav", 0 },	// 決定音
		{ "data/SE/Select2.wav", 0 },	// キャンセル恩
		{ "data/SE/Select3.wav", 0 },	// 選択音
		{ "data/SE/Select4.wav", 0 },	// キャラクター選択音
		{ "data/SE/Select5.wav", 0 },	// ゲームスタート

		{ "data/VOICE/titlecall000.wav", 0 },		//タイトルコール
		{ "data/VOICE/titlecall001.wav", 0 },		//タイトルコール2
		{ "data/VOICE/dog_select.wav", 0 },			//キャラ選択音　犬
		{ "data/VOICE/bea_select.wav", 0 },			//キャラ選択音　熊
		{ "data/VOICE/cat_select.wav", 0 },			//キャラ選択音　猫
		{ "data/VOICE/rabit_select.wav", 0 },		//キャラ選択音　兎
		{ "data/VOICE/dog_atk000.wav", 0 },			//犬　攻撃ボイス
		{ "data/VOICE/dog_atk001.wav", 0 },			//犬　攻撃ボイス
		{ "data/VOICE/dog_damege.wav", 0 },			//犬　被弾ボイス
		{ "data/VOICE/bea_atk000.wav", 0 },			//熊　攻撃ボイス
		{ "data/VOICE/bea_atk001.wav", 0 },			//熊　攻撃ボイス
		{ "data/VOICE/bea_damege.wav", 0 },			//熊　被弾ボイス
		{ "data/VOICE/cat_atk000.wav", 0 },			//猫　攻撃ボイス
		{ "data/VOICE/cat_atk001.wav", 0 },			//猫　攻撃ボイス
		{ "data/VOICE/cat_damege.wav", 0 },			//猫　被弾ボイス
		{ "data/VOICE/rabit_atk000.wav", 0 },		//兎　攻撃ボイス
		{ "data/VOICE/rabit_atk001.wav", 0 },		//兎　攻撃ボイス
		{ "data/VOICE/rabit_damege.wav", 0 },		//兎　被弾ボイス
		{ "data/VOICE/dog_victory.wav", 0 },		//犬　優勝
		{ "data/VOICE/bea_victory.wav", 0 },		//熊　優勝
		{ "data/VOICE/cat_victory.wav", 0 },		//猫　優勝
		{ "data/VOICE/rabit_victory.wav", 0 },		//兎　優勝

		{ "data/VOICE/gamestart000.wav", 0 },		//コトバトル
		{ "data/VOICE/gamestart001.wav", 0 },		//スタート
		{ "data/VOICE/gameend000.wav", 0 },			//そこまで


		{ "data/SE/Title.wav", 0 },	// タイトル
		{ "data/SE/Explosion001.wav", 0 },	// 爆発

		// 文字モデル名 SE
		{ "data/SE/WORDVOICE/00くるま.wav", 0 },			//	車
		{ "data/SE/WORDVOICE/00すいか.wav", 0 },			//	すいか
		{ "data/SE/WORDVOICE/01たまご.wav", 0 },			//	たまご
		{ "data/SE/WORDVOICE/02kかざん.wav", 0 },			//	かざん
		{ "data/SE/WORDVOICE/03くさや.wav", 0 },			//	くさや
		{ "data/SE/WORDVOICE/04めかぶ.wav", 0 },			//	めかぶ
		{ "data/SE/WORDVOICE/05がくふ.wav", 0 },			//	がくふ
		{ "data/SE/WORDVOICE/06くくり.wav", 0 },			//	くくり
		{ "data/SE/WORDVOICE/07いるか.wav", 0 },			//	いるか
		{ "data/SE/WORDVOICE/08くくり.wav", 0 },			//	くくり
		{ "data/SE/WORDVOICE/09ざらめ.wav", 0 },			//	ざらめ

		{ "data/SE/WORDVOICE/10まいく.wav", 0 },			//	まいく
		{ "data/SE/WORDVOICE/11たらい.wav", 0 },			//	たらい
		{ "data/SE/WORDVOICE/12らんす.wav", 0 },			//	らんす
		{ "data/SE/WORDVOICE/13なすか.wav", 0 },			//	なすか
		{ "data/SE/WORDVOICE/14ざざえ.wav", 0 },			//	さざえ
		{ "data/SE/WORDVOICE/15くすり.wav", 0 },			//	くすり
		{ "data/SE/WORDVOICE/16たいつ.wav", 0 },			//	たいつ
		{ "data/SE/WORDVOICE/17たこす.wav", 0 },			//	たこす
		{ "data/SE/WORDVOICE/18いちい.wav", 0 },			//	いちい
		{ "data/SE/WORDVOICE/19こるく.wav", 0 },			//	こるく
		{ "data/SE/WORDVOICE/20かます.wav", 0 },			//	かます

		{ "data/SE/WORDVOICE/21つくえ.wav", 0 },			//	つくえ
		{ "data/SE/WORDVOICE/22やかん.wav", 0 },			//	やかん
		{ "data/SE/WORDVOICE/23かだん.wav", 0 },			//	かだん
		{ "data/SE/WORDVOICE/24たんく.wav", 0 },			//	たんく
		{ "data/SE/WORDVOICE/25たいる.wav", 0 },			//	たいる
		{ "data/SE/WORDVOICE/26かいが.wav", 0 },			//	かいが
		{ "data/SE/WORDVOICE/27かえる.wav", 0 },			//	かえる
		{ "data/SE/WORDVOICE/28さらだ.wav", 0 },			//	さらだ
		{ "data/SE/WORDVOICE/29かんな.wav", 0 },			//	かんな
		{ "data/SE/WORDVOICE/30なふだ.wav", 0 },			//	なふだ
		{ "data/SE/WORDVOICE/31たたら.wav", 0 },			//	たたら

		{ "data/SE/WORDVOICE/32ぷりん.wav", 0 },			//	ぷりん
		{ "data/SE/WORDVOICE/33いかり.wav", 0 },			//	いかり
		{ "data/SE/WORDVOICE/34かたな.wav", 0 },			//	かたな
		{ "data/SE/WORDVOICE/35やぐら.wav", 0 },			//	やぐら
		{ "data/SE/WORDVOICE/36らいす.wav", 0 },			//	らいす
		{ "data/SE/WORDVOICE/37いくら.wav", 0 },			//	いくら
		{ "data/SE/WORDVOICE/38ぷらぐ.wav", 0 },			//	ぷらぐ
		{ "data/SE/WORDVOICE/39めんま.wav", 0 },			//	めんま
		{ "data/SE/WORDVOICE/40いえい.wav", 0 },			//	いえい
		{ "data/SE/WORDVOICE/41するめ.wav", 0 },			//	するめ
		{ "data/SE/WORDVOICE/42ずかん.wav", 0 },			//	ずかん

		{ "data/SE/WORDVOICE/43ないふ.wav", 0 },			//	ないふ
		{ "data/SE/WORDVOICE/44いかだ.wav", 0 },			//	いかだ
		{ "data/SE/WORDVOICE/45まるた.wav", 0 },			//	まるた
		{ "data/SE/WORDVOICE/46ざいす.wav", 0 },			//	ざいす
		{ "data/SE/WORDVOICE/47まんが.wav", 0 },			//	まんが
		{ "data/SE/WORDVOICE/48めんこ.wav", 0 },			//	めんこ
		{ "data/SE/WORDVOICE/49さいん.wav", 0 },			//	さいん
		{ "data/SE/WORDVOICE/50たらこ.wav", 0 },			//	たらこ
		{ "data/SE/WORDVOICE/51めだま.wav", 0 },			//	めだま
		{ "data/SE/WORDVOICE/52すずめ.wav", 0 },			//	すずめ
		{ "data/SE/WORDVOICE/53すぶた.wav", 0 },			//	すぶた

		{ "data/SE/WORDVOICE/54りんご.wav", 0 },			//	りんご
		{ "data/SE/WORDVOICE/55さいふ.wav", 0 },			//	さいふ
		{ "data/SE/WORDVOICE/56つらら.wav", 0 },			//	つらら
		{ "data/SE/WORDVOICE/57こんが.wav", 0 },			//	こんが
		{ "data/SE/WORDVOICE/58ふいご.wav", 0 },			//	ふいご
		{ "data/SE/WORDVOICE/59めいす.wav", 0 },			//	めいす
		{ "data/SE/WORDVOICE/60たいま.wav", 0 },			//	たいま
		{ "data/SE/WORDVOICE/61かめん.wav", 0 },			//	かめん
		{ "data/SE/WORDVOICE/62すだち.wav", 0 },			//	すだち
		{ "data/SE/WORDVOICE/63ちたん.wav", 0 },			//	ちたん
		{ "data/SE/WORDVOICE/64すすり.wav", 0 },			//	たいま

		{ "data/SE/WORDVOICE/65えのぐ.wav", 0 },			//	えのぐ
		{ "data/SE/WORDVOICE/66かるた.wav", 0 },			//	かるた
		{ "data/SE/WORDVOICE/67だんご.wav", 0 },			//	だんご
		{ "data/SE/WORDVOICE/68だいす.wav", 0 },			//	だいす
		{ "data/SE/WORDVOICE/69なまこ.wav", 0 },			//	なまこ
		{ "data/SE/WORDVOICE/70さらい.wav", 0 },			//	さらい
		{ "data/SE/WORDVOICE/71さくら.wav", 0 },			//	さくら
		{ "data/SE/WORDVOICE/72いふく.wav", 0 },			//	いふく
		{ "data/SE/WORDVOICE/73りんす.wav", 0 },			//	りんす
		{ "data/SE/WORDVOICE/74やさい.wav", 0 },			//	やさい
		{ "data/SE/WORDVOICE/75かいこ.wav", 0 },			//	かいこ

		{ "data/SE/WORDVOICE/76たいや.wav", 0 },			//	たいや
		{ "data/SE/WORDVOICE/77かめら.wav", 0 },			//	かめら
		{ "data/SE/WORDVOICE/78まくら.wav", 0 },			//	まくら
		{ "data/SE/WORDVOICE/79たから.wav", 0 },			//	たから
		{ "data/SE/WORDVOICE/80こんぶ.wav", 0 },			//	こんぶ
		{ "data/SE/WORDVOICE/81いんく.wav", 0 },			//	いんく
		{ "data/SE/WORDVOICE/82かやく.wav", 0 },			//	かやく
		{ "data/SE/WORDVOICE/83ふすま.wav", 0 },			//	ふすま
		{ "data/SE/WORDVOICE/84らんぷ.wav", 0 },			//	らんぷ
		{ "data/SE/WORDVOICE/85ふめん.wav", 0 },			//	ふめん
		{ "data/SE/WORDVOICE/86めだか.wav", 0 },			//	めだか

		{ "data/SE/WORDVOICE/87たいこ.wav", 0 },			//	たいこ
		{ "data/SE/WORDVOICE/88こえだ.wav", 0 },			//	こえだ
		{ "data/SE/WORDVOICE/89くない.wav", 0 },			//	くない
		{ "data/SE/WORDVOICE/90がらす.wav", 0 },			//	がらす
		{ "data/SE/WORDVOICE/91らいち.wav", 0 },			//	らいち
		{ "data/SE/WORDVOICE/92ざいる.wav", 0 },			//	ざいる
		{ "data/SE/WORDVOICE/93いるい.wav", 0 },			//	いるい
		{ "data/SE/WORDVOICE/94たんす.wav", 0 },			//	たんす
		{ "data/SE/WORDVOICE/95さんご.wav", 0 },			//	さんご
		{ "data/SE/WORDVOICE/96まぐま.wav", 0 },			//	まぐま

		{ "data/SE/WORDVOICE/97こいん.wav", 0 },			//	こいん
		{ "data/SE/WORDVOICE/98いちご.wav", 0 },			//	いちご
		{ "data/SE/WORDVOICE/99さかな.wav", 0 },			//	さかな
		{ "data/SE/WORDVOICE/100りんぐ.wav", 0 },			//	りんぐ
		{ "data/SE/WORDVOICE/101ますく.wav", 0 },			//	ますく
		{ "data/SE/WORDVOICE/102いなり.wav", 0 },			//	いなり
		{ "data/SE/WORDVOICE/103こたつ.wav", 0 },			//	こたつ
		{ "data/SE/WORDVOICE/104なめこ.wav", 0 },			//	なめこ
		{ "data/SE/WORDVOICE/105すまい.wav", 0 },			//	すまい
		{ "data/SE/WORDVOICE/106かなぐ.wav", 0 },			//	かなぐ
	};
};
#endif
