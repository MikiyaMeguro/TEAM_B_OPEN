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
	typedef struct
	{
		D3DXVECTOR3 POS;		//�ʒu
		D3DXVECTOR3 ROT;		//�p�x
		D3DXVECTOR3 SCALE;		//�傫��
		D3DXMATRIX  Matrix;		//�}�g���b�N�X
		void operator()(void)
		{//�������p�I�y���[�^(�����Ȃ�)
			D3DXMATRIX mtxRot, mtxTrans, mtxScale;

			//������(�����ɒʏ�̑傫���ŕ`��ł���悤�ɂ���)
			POS = D3DXVECTOR3(0.0f,0.0f,0.0f);
			ROT = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			SCALE = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			D3DXMatrixIdentity(&Matrix);
			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, ROT.y, ROT.x, ROT.z);
			D3DXMatrixMultiply(&Matrix, &Matrix, &mtxRot);

			//�g��k���̔��f
			D3DXMatrixScaling(&mtxScale, SCALE.x, SCALE.y, SCALE.z);
			D3DXMatrixMultiply(&Matrix, &Matrix, &mtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTrans, POS.x, POS.y, POS.z);
			D3DXMatrixMultiply(&Matrix, &Matrix, &mtxTrans);
		}
		void operator()(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 scale = D3DXVECTOR3(1.0f,1.0f,1.0f))
		{//�������p�I�y���[�^(��������)
			D3DXMATRIX mtxRot, mtxTrans, mtxScale;

			//�l������
			POS = pos;
			ROT = rot;
			SCALE = scale;

			//�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&Matrix);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, ROT.y, ROT.x, ROT.z);
			D3DXMatrixMultiply(&Matrix, &Matrix, &mtxRot);

			//�g��k���̔��f
			D3DXMatrixScaling(&mtxScale, SCALE.x, SCALE.y, SCALE.z);
			D3DXMatrixMultiply(&Matrix, &Matrix, &mtxScale);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTrans, POS.x, POS.y, POS.z);
			D3DXMatrixMultiply(&Matrix, &Matrix, &mtxTrans);
		}
	}MODEL_DRAW_STATE;

	static float RotateNormarizePI(float& value);
	static float Mapping(const float& value, const float& fromSource, const float& toSource, const float& fromTarget, const float& toTarget);
	static D3DXVECTOR3 MoveCoeffient(D3DXVECTOR3& value,const float& coeffient);
};
#endif // !_UTILITY_MATH_H_
