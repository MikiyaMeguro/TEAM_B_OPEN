//=============================================================================
//
// 汎用数学クラス [UtilityMath.cpp](CUtilityMath)
// Author : Kodama Yuto
//
//=============================================================================
#include "UtilityMath.h"


//=============================================================================
//	ワールドマトリックス計算関数
//=============================================================================
D3DXMATRIX* CUtilityMath::CalWorldMatrix(D3DXMATRIX* pOut, const D3DXVECTOR3& pos, const D3DXVECTOR3& rot,
	const D3DXMATRIX* parent,const D3DXVECTOR3& scale, D3DXMATRIX* pViewMtx)
{
	D3DXMATRIX mtxRot, mtxTrans, mtxScale,mtxInv, mtxParent;				// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(pOut);

	// 回転を反映
	if (pViewMtx != NULL)	//pViewMtxがNULLかどうかでビルボードかを判別する
	{//	ビルボードなら
		D3DXMatrixIdentity(&mtxInv);
		//逆行列を設定
		mtxInv._11 = pViewMtx->_11;
		mtxInv._12 = pViewMtx->_21;
		mtxInv._13 = pViewMtx->_31;
		mtxInv._21 = pViewMtx->_12;
		mtxInv._22 = pViewMtx->_22;
		mtxInv._23 = pViewMtx->_32;
		mtxInv._31 = pViewMtx->_13;
		mtxInv._32 = pViewMtx->_23;
		mtxInv._33 = pViewMtx->_33;

		//出来た行列に回転を反映してワールドマトリックスに入れる
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(pOut, &mtxInv, &mtxRot);
	}
	else
	{//ビルボードでないなら
		//普通に回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(pOut, pOut, &mtxRot);
	}

	//拡大縮小の反映
	D3DXMatrixScaling(&mtxScale, scale.x, scale.y, scale.z);
	D3DXMatrixMultiply(pOut, pOut, &mtxScale);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(pOut, pOut, &mtxTrans);


	if (parent != NULL)
	{
		//親のマトリックスを掛け合わせる
		D3DXMatrixMultiply(pOut,pOut,parent);
	}

	return pOut;
}

//=============================================================================
//	角度補正関数
//=============================================================================
float CUtilityMath::RotateNormarizePI(float* value)
{//float
	if (*value > D3DX_PI)
	{
		*value -= D3DX_PI * 2.0f;
	}
	else if (*value < -D3DX_PI)
	{
		*value += D3DX_PI * 2.0f;
	}

	return *value;
}
D3DXVECTOR3 CUtilityMath::RotateNormarizePI(D3DXVECTOR3* RotateValue)
{//D3DXVECTOR3(float３回)

	RotateNormarizePI(&RotateValue->x);
	RotateNormarizePI(&RotateValue->y);
	RotateNormarizePI(&RotateValue->z);

	return *RotateValue;
}

//=============================================================================
//	float型の線形補完関数
//=============================================================================
float CUtilityMath::FloatLeap(const float& fromValue, const float& toValue, const float fTime)
{
	return (1.0f - fTime) * fromValue + fTime * toValue;
}

//=============================================================================
//	数値の線形写像関数
//=============================================================================
float CUtilityMath::Mapping(const float& value, const float& fromSource, const float& toSource, const float& fromTarget, const float& toTarget,bool bClamp)
{
	float fResult = (value - fromSource) / (toSource - fromSource) * (toTarget - fromTarget) + fromTarget;

	if (bClamp == true)
	{//クランプ
		if (fResult > toTarget) { fResult = toTarget; }
		else if (fResult < fromTarget) { fResult = fromTarget; }
	}
	return fResult;
}

//=============================================================================
//	移動力に係数を掛ける関数
//=============================================================================
D3DXVECTOR3 CUtilityMath::MoveCoeffient(D3DXVECTOR3& value, const float& coeffient)
{//D3DXVECTOR3
	value.x += (0.0f - value.x) * coeffient;
	value.y += (0.0f - value.y) * coeffient;
	value.z += (0.0f - value.z) * coeffient;

	return value;
}

//=============================================================================
//	任意の桁数でfloatを四捨五入する関数
//=============================================================================
float CUtilityMath::RoundF_n(float& fValue, const int nRound)
{
	fValue *= powf(10.0f,(float)(nRound - 1));	//四捨五入したい値を10の(n-1)乗倍する。
	fValue = round(fValue);						//小数点以下を四捨五入する。
	fValue /= pow(10.0f, (float)(nRound - 1));  //10の(n-1)乗で割る。

	return fValue;
}

//=============================================================================
//
// イージングクラス [UtilityMath.cpp](CEasingFunc)
// Author : Kodama Yuto
//
//=============================================================================
//=============================================================================
//	イージング関数
//=============================================================================
float CEasingFunc::Easing(CEasingFunc::EASE_TYPE type, float& fTime)
{
	float fResult = 0.0f;

	if (fTime > 1.0f)
	{
		fTime = 1.0f;
	}
	else if (fTime < 0.0f)
	{
		fTime = 0.0f;
	}

	float Time = fTime;
	//タイプごとに処理を分ける
	switch (type)
	{
	case EASE_LINIAR:
		fResult = Time;
		break;
	case EASE_IN_QUAD:
		fResult = Time * Time;
		break;
	case EASE_OUT_QUAD:
		fResult = -1.0f*Time*(Time - 2.0f);
		break;
	case EASE_INOUT_QUAD:
		Time /= 0.5f;
		if (Time < 1.0f)
		{
			fResult = Time * Time * 0.5f;
		}
		else
		{
			Time = Time - 1.0f;
			fResult = -0.5f * (Time*(Time - 2) - 1);
		}
		break;
	case EASE_IN_CUBIC:
		fResult = Time * Time * Time;
		break;
	case EASE_OUT_CUBIC:
		Time = Time - 1.0f;
		fResult = (Time*Time*Time + 1);
		break;
	case EASE_INOUT_CUBIC:
		Time /= 0.5f;
		if (Time < 1.0f)
		{
			fResult = 0.5f*Time*Time*Time;
		}
		else
		{
			Time = Time - 2;
			fResult = 0.5f * (Time*Time*Time + 2);
		}

		break;
	}

	return fResult;
}

//=============================================================================
//
// ３次元ベクトルクラス [UtilityMath.cpp](VECTOR_3D)
// Author : Kodama Yuto
//
//=============================================================================
//=============================================================================
//	角度を法線として使えるように線形写像する関数
//=============================================================================
VECTOR_3D VECTOR_3D::RotateNormalize(void)
{
	//角度を正規化
	//X
	if (this->X > _PI)
	{
		this->X -= _PI * 2.0f;
	}
	else if (this->X < -_PI)
	{
		this->X += _PI * 2.0f;
	}
	//Y
	if (this->Y > _PI)
	{
		this->Y -= _PI * 2.0f;
	}
	else if (this->Y < -_PI)
	{
		this->Y += _PI * 2.0f;
	}
	//Z
	if (this->Z > _PI)
	{
		this->Z -= _PI * 2.0f;
	}
	else if (this->Z < -_PI)
	{
		this->Z += _PI * 2.0f;
	}

	//-1.0fから1.0fまでの数値に直す
	this->X = CUtilityMath::Mapping(this->X, -_PI, _PI, -1.0f, 1.0f, true);
	this->Y = CUtilityMath::Mapping(this->Y, -_PI, _PI, -1.0f, 1.0f, true);
	this->Z = CUtilityMath::Mapping(this->Z, -_PI, _PI, -1.0f, 1.0f, true);

	return *this;
}