//=============================================================================
//
// カメラ処理 [camera.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

class C3DCharactor;

#define ANGLE_MOVE  (0.03f) //カメラ角度の移動量
#define CAMERA_POSR_COEFFICIENT (0.50f) 	//カメラ注視点の係数
#define CAMERA_POSV_COEFFICIENT (0.18f)	    //カメラ視点の係数
#define CAMERA_ROT_COEFFICIENT (0.20f)		//カメラ角度の係数

#define CAMERA_POS_INTERVAL (20.0f)			//カメラの注視点の位置


//===================================================================
// クラスの定義
//===================================================================
class CCamera
{
public:
	typedef enum
	{
		TYPE_FPS,		//一人称(PosV追従、PosR回転)
		TYPE_TPS,		//三人称(PosR追従、PosV回転)
		TYPE_SPECTOR,	//自由(固定無し,PosVとRotでPosRが決まる)
	}CAMERA_TYPE;

	CCamera();
	~CCamera();

	void Set(CAMERA_TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fLength);

	void Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);

	/*Get*/
	D3DXVECTOR3 GetPosV(void) { return m_posV; };
	D3DXVECTOR3 GetPosR(void) { return m_posR; };
	D3DXVECTOR3 GetRotation(void) { return m_rot; };
	float GetLength(void) { return m_fLength; };
	D3DVIEWPORT9 GetViewPort(void) { return m_ViewPort; };
	CAMERA_TYPE GetType(void) { return m_Type; };
	/*Set*/
	//SPECTOR用
	void SetPosV(D3DXVECTOR3 posV) { m_posV = posV; };
	void SetPosR(D3DXVECTOR3 posR) { m_posR = posR; };
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; };

	//FPS,TPS用
	void SetPosVDest(D3DXVECTOR3 posVDest) { m_posVdest = posVDest; };
	void SetPosRDest(D3DXVECTOR3 posRDest) { m_posRdest = posRDest; };
	void SetRotationDest(D3DXVECTOR3 rotDest) { m_rotDest = rotDest; };

	//共通
	void SetLength(float fLength) { m_fLength = fLength; };

	void SetViewPort(D3DVIEWPORT9 ViewPort) { m_ViewPort = ViewPort; };
	void SetViewPort(int X, int Y, int Width, int Height, float MinZ = 0.0f, float MaxZ = 1.0f)
	{
		m_ViewPort.X = X;
		m_ViewPort.Y = Y;
		m_ViewPort.Width = Width;
		m_ViewPort.Height = Height;
		m_ViewPort.MinZ = MinZ;
		m_ViewPort.MaxZ = MaxZ;
	};

	void SetLockOnChara(C3DCharactor* pChara) { m_pLockOnChara = pChara; };
	void SetHomingChara(C3DCharactor* pChara) { m_pHomingChara = pChara; };
	void SetCameraAngle(float fAngle) { m_fCameraAngle = fAngle; };

private:
	D3DXVECTOR3 m_posV;		//視点
	D3DXVECTOR3 m_posVdest;	//目標の視点
	D3DXVECTOR3 m_posR;		//注視点
	D3DXVECTOR3 m_posRdest; //目標の注視点
	D3DXVECTOR3 m_vecU;		//上方向ベクトル
	D3DXVECTOR3 m_rot;		//角度
	D3DXVECTOR3 m_rotDest;	//目標の角度

	float m_fLength;	//PosVからPosRまでの距離

	D3DXMATRIX m_mtxProjection; //プロジェクションマトリックス
	D3DXMATRIX m_mtxView;		//ビューマトリックス

	D3DVIEWPORT9 m_ViewPort;	//ビューポート
	float m_fCameraAngle;		//カメラ角

	CAMERA_TYPE m_Type;			//カメラのタイプ
	C3DCharactor* m_pLockOnChara;	//posRでロックオンしているキャラのポインタ(NULLならロックオンしてない状態)
	C3DCharactor* m_pHomingChara;	//posVで追従するキャラのポインタ(NULLなら追従なし)

	D3DXVECTOR3 m_ORGposV;		//視点
	D3DXVECTOR3 m_ORGposR;		//注視点
	D3DXVECTOR3 m_ORGvecU;		//上方向ベクトル
	D3DXVECTOR3 m_ORGrotDest;	//目標の角度

};
#endif // !_CAMERA_H_
