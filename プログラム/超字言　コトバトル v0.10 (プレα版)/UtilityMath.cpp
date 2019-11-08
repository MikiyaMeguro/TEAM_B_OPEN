//=============================================================================
//
// 汎用数学クラス [UtilityMath.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "UtilityMath.h"


//=============================================================================
//	マトリックス計算関数
//=============================================================================
void CUtilityMath::CalWorldMatrix(D3DXMATRIX* pOut, const D3DXVECTOR3& pos, const D3DXVECTOR3& rot,
	const D3DXMATRIX* parent,const D3DXVECTOR3& scale)
{
	D3DXMATRIX mtxRot, mtxTrans, mtxScale, mtxParent;				// 計算用マトリックス
																	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(pOut);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(pOut, pOut, &mtxRot);

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
}

//=============================================================================
//	角度補正関数
//=============================================================================
void CUtilityMath::RotateNormarizePI(float* value)
{
	if (*value > D3DX_PI)
	{
		*value -= D3DX_PI * 2.0f;
	}
	else if (*value < -D3DX_PI)
	{
		*value += D3DX_PI * 2.0f;
	}
}

//=============================================================================
//	数値の線形写像関数
//=============================================================================
float CUtilityMath::Mapping(const float& value, const float& fromSource, const float& toSource, const float& fromTarget, const float& toTarget)
{
	return (value - fromSource) / (toSource - fromSource) * (toTarget - fromTarget) + fromTarget;
}

//=============================================================================
//	移動力に係数を掛ける関数
//=============================================================================
D3DXVECTOR3 CUtilityMath::MoveCoeffient(D3DXVECTOR3& value, const float& coeffient)
{
	value.x += (0.0f - value.x) * coeffient;
	value.y += (0.0f - value.y) * coeffient;
	value.z += (0.0f - value.z) * coeffient;

	return value;
}

//=============================================================================
//	任意の桁数でfloatを切り上げる関数
//=============================================================================
float CUtilityMath::Round_n(float& fValue, const int nRound)
{
	fValue *= powf(10.0f,(float)(nRound - 1));	//四捨五入したい値を10の(n-1)乗倍する。
	fValue = round(fValue);						//小数点以下を四捨五入する。
	fValue /= pow(10.0f, (float)(nRound - 1));  //10の(n-1)乗で割る。

	return fValue;
}