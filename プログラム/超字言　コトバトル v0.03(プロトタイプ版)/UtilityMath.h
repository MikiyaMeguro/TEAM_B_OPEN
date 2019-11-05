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
	typedef struct
	{
		D3DXVECTOR3 POS;		//位置
		D3DXVECTOR3 ROT;		//角度
		D3DXVECTOR3 SCALE;		//大きさ
		D3DXMATRIX  Matrix;		//マトリックス
		void operator()(void)
		{//初期化用オペレータ(引数なし)
			D3DXMATRIX mtxRot, mtxTrans, mtxScale;

			//初期化(中央に通常の大きさで描画できるようにする)
			POS = D3DXVECTOR3(0.0f,0.0f,0.0f);
			ROT = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			SCALE = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			D3DXMatrixIdentity(&Matrix);
			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, ROT.y, ROT.x, ROT.z);
			D3DXMatrixMultiply(&Matrix, &Matrix, &mtxRot);

			//拡大縮小の反映
			D3DXMatrixScaling(&mtxScale, SCALE.x, SCALE.y, SCALE.z);
			D3DXMatrixMultiply(&Matrix, &Matrix, &mtxScale);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTrans, POS.x, POS.y, POS.z);
			D3DXMatrixMultiply(&Matrix, &Matrix, &mtxTrans);
		}
		void operator()(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 scale = D3DXVECTOR3(1.0f,1.0f,1.0f))
		{//初期化用オペレータ(引数あり)
			D3DXMATRIX mtxRot, mtxTrans, mtxScale;

			//値を入れる
			POS = pos;
			ROT = rot;
			SCALE = scale;

			//マトリックスの初期化
			D3DXMatrixIdentity(&Matrix);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, ROT.y, ROT.x, ROT.z);
			D3DXMatrixMultiply(&Matrix, &Matrix, &mtxRot);

			//拡大縮小の反映
			D3DXMatrixScaling(&mtxScale, SCALE.x, SCALE.y, SCALE.z);
			D3DXMatrixMultiply(&Matrix, &Matrix, &mtxScale);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTrans, POS.x, POS.y, POS.z);
			D3DXMatrixMultiply(&Matrix, &Matrix, &mtxTrans);
		}
	}MODEL_DRAW_STATE;

	static float RotateNormarizePI(float& value);
	static float Mapping(const float& value, const float& fromSource, const float& toSource, const float& fromTarget, const float& toTarget);
	static D3DXVECTOR3 MoveCoeffient(D3DXVECTOR3& value,const float& coeffient);
};
#endif // !_UTILITY_MATH_H_
