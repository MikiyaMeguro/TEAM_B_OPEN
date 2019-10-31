//=============================================================================
//
// �ėp���w�N���X [UtilityMath.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "UtilityMath.h"

//=============================================================================
//	�p�x�␳�֐�
//=============================================================================
float CUtilityMath::RotateRivisionPI(float& value)
{
	if (value > D3DX_PI)
	{
		value -= D3DX_PI * 2.0f;
	}
	else if (value < -D3DX_PI)
	{
		value += D3DX_PI * 2.0f;
	}
	return value;
}

//=============================================================================
//	���l�̐��`�ʑ��֐�
//=============================================================================
float CUtilityMath::Mapping(const float& value, const float& fromSource, const float& toSource, const float& fromTarget, const float& toTarget)
{
	return (value - fromSource) / (toSource - fromSource) * (toTarget - fromTarget) + fromTarget;
}
//=============================================================================
//	�ړ��͂ɌW�����|����֐�
//=============================================================================
D3DXVECTOR3 CUtilityMath::MoveCoeffient(D3DXVECTOR3& value, const float& coeffient)
{
	value.x += (0.0f - value.x) * coeffient;
	value.y += (0.0f - value.y) * coeffient;
	value.z += (0.0f - value.z) * coeffient;

	return value;
}