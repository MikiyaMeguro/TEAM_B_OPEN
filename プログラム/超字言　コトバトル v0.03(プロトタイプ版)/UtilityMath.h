//=============================================================================
//
// 汎用数学クラス [UtilityMath.h]
// Author : Kodama Yuto
//	クラスの概要:
//	・よく使う計算をクラス化してまとめた物
//	・基本的にすべての変数を参照で渡す
//	・本来はライブラリ化したほうがいいらしいが、編集を楽にするために今回はこのまま使う
//
//=============================================================================
#ifndef _UTILITY_MATH_H_
#define _UTILITY_MATH_H_

#include "main.h"

//=============================================================================
//	クラス定義
//=============================================================================
class CUtilityMath
{
public:

	static void CalWorldMatrix(D3DXMATRIX* pOut,const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXMATRIX* parent = NULL, const D3DXVECTOR3& scale = D3DXVECTOR3(1.0f,1.0f,1.0f));
	static void RotateNormarizePI(float* value);
	static float Mapping(const float& value, const float& fromSource, const float& toSource, const float& fromTarget, const float& toTarget);
	static D3DXVECTOR3 MoveCoeffient(D3DXVECTOR3& value,const float& coeffient);
	static float Round_n(float& fValue,const int nRound);
};
#endif // !_UTILITY_MATH_H_
