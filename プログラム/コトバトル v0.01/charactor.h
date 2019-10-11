//=============================================================================
//
// キャラクター処理 [charactor.h]
// Author : Kodama Yuto
//
//	クラスの概要
//	・PositionやRotationなど、姿勢制御に使う変数を持ったクラス群
//	・クラス内で姿勢制御を行い、Get関数でそれらを取得する
//
//	C2DCharactor
//	・2Dのキャラクター用のクラス
//	・マトリックスを持たず、PositionとRotationで制御する
//
//	C3DCharactor
//	・3Dのキャラクター用のクラス
//	・PositionとRotationに加えて,マトリックスを使って姿勢制御を行う
//
//=============================================================================
#ifndef _CHARACTOR_H_
#define _CHARACTOR_H_

#include "scene.h"
class CCharaBase : public CScene
{
public:
	typedef enum
	{
		MOVETYPE_PLAYER_INPUT,		//プレイヤーの操作
		MOVETYPE_AI,
		MOVETYPE_MAX
	}CHARACTOR_MOVE_TYPE;

private:
};

class C2DCharactor : public CCharaBase
{

};

class C3DCharactor : public CCharaBase
{

};

#endif // !_CHARACTOR_H_
