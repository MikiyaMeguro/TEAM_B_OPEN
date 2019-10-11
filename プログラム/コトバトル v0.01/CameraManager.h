//=============================================================================
//
// カメラ管理処理 [CameraManager.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _CAMERA_MANAGER_H_
#define _CAMERA_MANAGER_H_

#include "main.h"
#include "camera.h"
//===================================================================
// クラスの定義
//===================================================================
class CCameraManager
{
public:
	struct CAMERA_STATE
	{//カメラ情報の構造体
		CCamera* pCamera;	//カメラのポインタ
		LPCSTR CameraTag;	//カメラ識別用のタグ

		bool operator == (const LPCSTR Tag)
		{//タグ比較(同じならtrue)
			return (strcmp(CameraTag, Tag) == 0);
		}
	};

	CCameraManager();
	~CCameraManager();

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);

	//カメラのセット
	bool SetCamera(LPCSTR Tag);

	//カメラ生成
	bool CreateCamera(LPCSTR Tag, CCamera::CAMERA_TYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fLength);

	//カメラのビューポート設定
	bool SetCameraViewPort(LPCSTR Tag, int X, int Y, int Width, int Height, float MinZ = 0.0f, float MaxZ = 1.0f);

	////カメラ削除
	//bool DeleteCamera(LPCSTR Tag);

	int GetCameraNum(void) { return m_vecCameraState.size(); };
private:
	std::vector<CAMERA_STATE> m_vecCameraState;	//カメラ情報の動的配列

	LPCSTR m_SetCamera;		//現在セットしているカメラの名前
};
#endif // !_CAMERA_MANAGER_H_
