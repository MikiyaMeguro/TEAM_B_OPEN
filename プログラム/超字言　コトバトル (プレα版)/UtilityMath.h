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

#define _PI (3.141592f)
//=============================================================================
//	クラス定義(VECTOR_3D)	独自の３次元ベクトルクラス
//=============================================================================
class VECTOR_3D
{
public:
	float X;	//X軸の値
	float Y;	//Y軸の値
	float Z;	//Z軸の値

	//コンストラクタ(引数なし)
	VECTOR_3D()
	{
		this->X = 0.0f;
		this->Y = 0.0f;
		this->Z = 0.0f;
	}
	//コンストラクタ(引数あり)
	VECTOR_3D(const float& X, const float& Y, const float& Z)
	{
		this->X = X;
		this->Y = Y;
		this->Z = Z;
	}
	//デストラクタ(デフォルト)
	~VECTOR_3D() {};

	//独自関数
	VECTOR_3D RotateNormalize(void);

	/*オペレータ*/
	//代入
	void operator = (const VECTOR_3D& vec)
	{
		this->X = vec.X;
		this->Y = vec.Y;
		this->Z = vec.Z;
	}

	//足し算
	VECTOR_3D operator + (const VECTOR_3D& vec)
	{
		this->X = this->X + vec.X;
		this->Y = this->Y + vec.Y;
		this->Z = this->Z + vec.Z;

		return *this;
	}
	void operator += (const VECTOR_3D& vec)
	{
		this->X += vec.X;
		this->Y += vec.Y;
		this->Z += vec.Z;
	}

	//引き算
	VECTOR_3D operator - (const VECTOR_3D& vec)
	{
		this->X = this->X - vec.X;
		this->Y = this->Y - vec.Y;
		this->Z = this->Z - vec.Z;

		return *this;
	}
	void operator -= (const VECTOR_3D& vec)
	{
		this->X -= vec.X;
		this->Y -= vec.Y;
		this->Z -= vec.Z;
	}

	//掛け算
	VECTOR_3D operator * (const VECTOR_3D& vec)
	{
		this->X = this->X * vec.X;
		this->Y = this->Y * vec.Y;
		this->Z = this->Z * vec.Z;

		return *this;
	}
	void operator *= (const VECTOR_3D& vec)
	{
		this->X *= vec.X;
		this->Y *= vec.Y;
		this->Z *= vec.Z;
	}

	//割り算
	VECTOR_3D operator / (const VECTOR_3D& vec)
	{
		this->X = this->X / vec.X;
		this->Y = this->Y / vec.Y;
		this->Z = this->Z / vec.Z;

		return *this;
	}
	void operator /= (const VECTOR_3D& vec)
	{
		this->X /= vec.X;
		this->Y /= vec.Y;
		this->Z /= vec.Z;
	}

	//定数掛け算
	VECTOR_3D operator * (const float& fVal)
	{
		this->X = this->X * fVal;
		this->Y = this->Y * fVal;
		this->Z = this->Z * fVal;

		return *this;
	}

	//比較(可読性のために三項演算子を使う)
	bool operator == (const VECTOR_3D& vec)
	{// ==
		return (this->X == vec.X && this->Y == vec.Y && this->Z == vec.Z) ? true : false;
	}
	bool operator != (const VECTOR_3D& vec)
	{// !=
		return (this->X != vec.X && this->Y != vec.Y && this->Z != vec.Z) ? true : false;
	}
	bool operator > (const VECTOR_3D& vec)
	{// >
		return (this->X > vec.X && this->Y > vec.Y && this->Z > vec.Z) ? true : false;
	}
	bool operator >= (const VECTOR_3D& vec)
	{// >=
		return (this->X >= vec.X && this->Y >= vec.Y && this->Z >= vec.Z) ? true : false;
	}
	bool operator < (const VECTOR_3D& vec)
	{// <
		return (this->X < vec.X && this->Y < vec.Y && this->Z < vec.Z) ? true : false;
	}
	bool operator <= (const VECTOR_3D& vec)
	{// <=
		return (this->X <= vec.X && this->Y <= vec.Y && this->Z <= vec.Z) ? true : false;
	}
};

//=============================================================================
//	クラス定義(CUtilityMath)
//=============================================================================
class CUtilityMath
{
public:
	static void CalWorldMatrix(D3DXMATRIX* pOut,const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXMATRIX* parent = NULL, const D3DXVECTOR3& scale = D3DXVECTOR3(1.0f,1.0f,1.0f));
	static void RotateNormarizePI(float* value);
	static float Mapping(const float& value, const float& fromSource, const float& toSource, const float& fromTarget, const float& toTarget, bool bClamp = false);
	static D3DXVECTOR3 MoveCoeffient(D3DXVECTOR3& value,const float& coeffient);
	static float Round_n(float& fValue,const int nRound);
};
#endif // !_UTILITY_MATH_H_
