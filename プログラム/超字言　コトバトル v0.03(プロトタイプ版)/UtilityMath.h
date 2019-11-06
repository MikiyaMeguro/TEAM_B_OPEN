//=============================================================================
//
// �ėp���w�N���X [UtilityMath.h]
// Author : Kodama Yuto
//	�N���X�̊T�v:
//	�E�悭�g���v�Z���N���X�����Ă܂Ƃ߂���
//	�E��{�I�ɂ��ׂĂ̕ϐ����Q�Ƃœn��
//	�E�{���̓��C�u�����������ق��������炵�����A�ҏW���y�ɂ��邽�߂ɍ���͂��̂܂܎g��
//
//=============================================================================
#ifndef _UTILITY_MATH_H_
#define _UTILITY_MATH_H_

#include "main.h"

//=============================================================================
//	�N���X��`
//=============================================================================
class CUtilityMath
{
public:

	static void CalWorldMatrix(D3DXMATRIX* pOut,const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXMATRIX* parent = NULL, const D3DXVECTOR3& scale = D3DXVECTOR3(1.0f,1.0f,1.0f));
	static void RotateNormarizePI(float* value);
	static float Mapping(const float& value, const float& fromSource, const float& toSource, const float& fromTarget, const float& toTarget);
	static D3DXVECTOR3 MoveCoeffient(D3DXVECTOR3& value,const float& coeffient);
};
#endif // !_UTILITY_MATH_H_
