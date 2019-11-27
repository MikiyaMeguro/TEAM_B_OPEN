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

#define _PI (3.141592f)
//=============================================================================
//	�N���X��`(VECTOR_3D)	�Ǝ��̂R�����x�N�g���N���X
//=============================================================================
class VECTOR_3D
{
public:
	float X;	//X���̒l
	float Y;	//Y���̒l
	float Z;	//Z���̒l

	//�R���X�g���N�^(�����Ȃ�)
	VECTOR_3D()
	{
		this->X = 0.0f;
		this->Y = 0.0f;
		this->Z = 0.0f;
	}
	//�R���X�g���N�^(��������)
	VECTOR_3D(const float& X, const float& Y, const float& Z)
	{
		this->X = X;
		this->Y = Y;
		this->Z = Z;
	}
	//�f�X�g���N�^(�f�t�H���g)
	~VECTOR_3D() {};

	//�Ǝ��֐�
	VECTOR_3D RotateNormalize(void);

	/*�I�y���[�^*/
	//���
	void operator = (const VECTOR_3D& vec)
	{
		this->X = vec.X;
		this->Y = vec.Y;
		this->Z = vec.Z;
	}

	//�����Z
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

	//�����Z
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

	//�|���Z
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

	//����Z
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

	//�萔�|���Z
	VECTOR_3D operator * (const float& fVal)
	{
		this->X = this->X * fVal;
		this->Y = this->Y * fVal;
		this->Z = this->Z * fVal;

		return *this;
	}

	//��r(�ǐ��̂��߂ɎO�����Z�q���g��)
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
//	�N���X��`(CUtilityMath)
//=============================================================================
class CUtilityMath
{
public:
	//���[���h�}�g���b�N�X�v�Z�N���X
	static void CalWorldMatrix(D3DXMATRIX* pOut,const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXMATRIX* parent = NULL, const D3DXVECTOR3& scale = D3DXVECTOR3(1.0f,1.0f,1.0f),D3DXMATRIX* pViewMtx = NULL);

	static void RotateNormarizePI(float* value);
	static void RotateNormarizePI(D3DXVECTOR3* RotateValue);

	static float Mapping(const float& value, const float& fromSource, const float& toSource, const float& fromTarget, const float& toTarget, bool bClamp = false);
	static D3DXVECTOR3 MoveCoeffient(D3DXVECTOR3& value,const float& coeffient);
	static float Round_n(float& fValue,const int nRound);
	//������
	static D3DXVECTOR3 EulerToQuaternion(const D3DXQUATERNION& quat);

private:
	CUtilityMath();
};
#endif // !_UTILITY_MATH_H_
