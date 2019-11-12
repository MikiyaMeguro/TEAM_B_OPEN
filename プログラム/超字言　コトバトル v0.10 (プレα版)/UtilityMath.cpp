//=============================================================================
//
// �ėp���w�N���X [UtilityMath.cpp](CUtilityMath)
// Author : Kodama Yuto
//
//=============================================================================
#include "UtilityMath.h"


//=============================================================================
//	���[���h�}�g���b�N�X�v�Z�֐�
//=============================================================================
void CUtilityMath::CalWorldMatrix(D3DXMATRIX* pOut, const D3DXVECTOR3& pos, const D3DXVECTOR3& rot,
	const D3DXMATRIX* parent,const D3DXVECTOR3& scale)
{
	D3DXMATRIX mtxRot, mtxTrans, mtxScale, mtxParent;				// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(pOut);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(pOut, pOut, &mtxRot);

	//�g��k���̔��f
	D3DXMatrixScaling(&mtxScale, scale.x, scale.y, scale.z);
	D3DXMatrixMultiply(pOut, pOut, &mtxScale);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(pOut, pOut, &mtxTrans);

	if (parent != NULL)
	{
		//�e�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(pOut,pOut,parent);
	}

}

//=============================================================================
//	�p�x�␳�֐�
//=============================================================================
void CUtilityMath::RotateNormarizePI(float* value)
{//float
	if (*value > D3DX_PI)
	{
		*value -= D3DX_PI * 2.0f;
	}
	else if (*value < -D3DX_PI)
	{
		*value += D3DX_PI * 2.0f;
	}
}
void CUtilityMath::RotateNormarizePI(D3DXVECTOR3* RotateValue)
{//D3DXVECTOR3(float�R��)

	RotateNormarizePI(&RotateValue->x);
	RotateNormarizePI(&RotateValue->y);
	RotateNormarizePI(&RotateValue->z);
}

//=============================================================================
//	���l�̐��`�ʑ��֐�
//=============================================================================
float CUtilityMath::Mapping(const float& value, const float& fromSource, const float& toSource, const float& fromTarget, const float& toTarget,bool bClamp)
{
	float fResult = (value - fromSource) / (toSource - fromSource) * (toTarget - fromTarget) + fromTarget;

	if (bClamp == true)
	{
		if (fResult > toTarget) { fResult = toTarget; }
		else if (fResult < fromTarget) { fResult = fromTarget; }
	}
	return fResult;
}

//=============================================================================
//	�ړ��͂ɌW�����|����֐�
//=============================================================================
D3DXVECTOR3 CUtilityMath::MoveCoeffient(D3DXVECTOR3& value, const float& coeffient)
{//D3DXVECTOR3
	value.x += (0.0f - value.x) * coeffient;
	value.y += (0.0f - value.y) * coeffient;
	value.z += (0.0f - value.z) * coeffient;

	return value;
}

//=============================================================================
//	�C�ӂ̌�����float���l�̌ܓ�����֐�
//=============================================================================
float CUtilityMath::Round_n(float& fValue, const int nRound)
{
	fValue *= powf(10.0f,(float)(nRound - 1));	//�l�̌ܓ��������l��10��(n-1)��{����B
	fValue = round(fValue);						//�����_�ȉ����l�̌ܓ�����B
	fValue /= pow(10.0f, (float)(nRound - 1));  //10��(n-1)��Ŋ���B

	return fValue;
}
//=============================================================================
//	�N�H�[�^�j�I�����I�C���[�p(�R�����x�N�g��)�ɕϊ�����֐�(�쐬�r��)
//=============================================================================
D3DXVECTOR3 CUtilityMath::EulerToQuaternion(const D3DXQUATERNION& quat)
{
	D3DXMATRIX mtxRot;
	D3DXMatrixRotationQuaternion(&mtxRot,&quat);

	return D3DXVECTOR3(0.0f,0.0f,0.0f);
}

//=============================================================================
//
// �R�����x�N�g���N���X [UtilityMath.cpp](VECTOR_3D)
// Author : Kodama Yuto
//
//=============================================================================
//=============================================================================
//	�p�x��@���Ƃ��Ďg����悤�ɐ��`�ʑ�����֐�
//=============================================================================
VECTOR_3D VECTOR_3D::RotateNormalize(void)
{
	//�p�x�𐳋K��
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

	//-1.0f����1.0f�܂ł̐��l�ɒ���
	this->X = CUtilityMath::Mapping(this->X, -_PI, _PI, -1.0f, 1.0f, true);
	this->Y = CUtilityMath::Mapping(this->Y, -_PI, _PI, -1.0f, 1.0f, true);
	this->Z = CUtilityMath::Mapping(this->Z, -_PI, _PI, -1.0f, 1.0f, true);

	return *this;
}