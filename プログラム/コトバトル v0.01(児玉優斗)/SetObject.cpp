//---------------------------------------------------------------------
//	オブジェクト配置処理(SetObject.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "SetObject.h"
#include "game.h"
#include "fade.h"
#include "sceneX.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_SPEED     (5.0f)
#define MODEL_DEPTH     (50.0f)

#define PLAYER_DEPTH	(15)		// プレイヤーの幅調整用
#define PLAYER_HEIGHT	(50.0f)		// プレイヤーの背の高さ

#define FILE_NAME0				("data\\TEXT\\SetModel.txt")

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPD3DXMESH					CSetObject::m_pMesh[MODELTYPE_MAX] = {};
LPD3DXBUFFER				CSetObject::m_pBuffMat[MODELTYPE_MAX] = {};
LPDIRECT3DTEXTURE9			CSetObject::m_pTexture[MODELTYPE_MAX] = {};
DWORD						CSetObject::m_nNumMat[MODELTYPE_MAX] = {};
int							CSetObject::m_nMaxModel = 0;
char						CSetObject::m_aFileName[MODELTYPE_MAX][256] = { NULL };


//--------------------------------------------
//オブジェクトクラス コンストラクタ
//--------------------------------------------
CSetObject::CSetObject() : CScene(3, CScene::OBJTYPE_SCENEX)
{
	m_pos = D3DXVECTOR3(0, 0, 0);					//位置
	m_posold = D3DXVECTOR3(0, 0, 0);				//前回の位置
	m_move = D3DXVECTOR3(0, 0, 0);					//移動量
	m_ModelMove = D3DXVECTOR3(0, 0, 0);
	m_rot = D3DXVECTOR3(0, 0, 0);					//向き
	D3DXMatrixIdentity(&m_mtxWorld);				//ワールドマトリックス
	m_nCollision = 0;
	m_nCount = 0;
	m_Type = CSetObject::MODELTYPE_BOX000;
	m_nType = 0;
	m_bBillboard = false;
	m_nRange = 0;
	//m_nMaxModel = 0;
	m_pObject = NULL;
}

//--------------------------------------------
//オブジェクトクラス デストラクタ
//--------------------------------------------
CSetObject::~CSetObject()
{
}

//--------------------------------------------
//オブジェクトの生成
//--------------------------------------------
CSetObject *CSetObject::Create(D3DXVECTOR3 pos)
{
	//オブジェクトポインタ
	CSetObject *pObjectBG;
	pObjectBG = new CSetObject;
	//初期値が入った後 pos代入
	pObjectBG->m_pos = pos;
	//オブジェクトの初期化
	pObjectBG->Init();
	//オブジェクトの情報を返す
	return pObjectBG;
}

//=============================================================================
// オブジェクトの初期化処理
//=============================================================================
HRESULT CSetObject::Init()
{
	//オブジェクト種類の設定
	CScene::SetObjType(CScene::OBJTYPE_SCENEX);

	m_rot = D3DXVECTOR3(0, D3DX_PI * 0.0f, 0);
	m_move = D3DXVECTOR3(0, 0, 0);
	m_fDestAngle = D3DX_PI * 1.0f;
	m_fDiffAngle = 0;
	m_nRange = (int)MODEL_DEPTH;
	LPDIRECT3DVERTEXBUFFER9 VtxBuff = NULL;		// 頂点バッファへのポインタ

	////モデルを生成	オフセット設定
	//m_pObject = CSceneObject::Create(m_pos, m_rot);
	////モデルを割り当て
	//m_pObject->BindModel(m_nNumMat[m_Type], m_pMesh[m_Type], m_pBuffMat[m_Type]);
	////モデルの親を指定
	//m_pObject->SetParent(NULL);
	////位置設定
	//m_pObject->Setpos(m_pos);
	return S_OK;
}

//=============================================================================
// オブジェクトの終了処理
//=============================================================================
void CSetObject::Uninit(void)
{
	//自分を消す(オブジェクトを破棄)
	Release();
}

//=============================================================================
// オブジェクトの更新処理
//=============================================================================
void CSetObject::Update(void)
{
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

	if (pInput->GetTrigger(DIK_RSHIFT) == true)
	{	//ファイルセーブ
		SaveFile();
	}
	else if (pInput->GetTrigger(DIK_RCONTROL) == true)
	{	//ファイルロード
		LoadFile();
	}

#if 0

	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//カメラを取得
	CCamera *pCamera = CGame::GetCamera();
	//過去の位置を設定
	m_posold = m_pos;

	// 移動量の初期化
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//向きの代入
	D3DXVECTOR3 rot = m_pObject->GetRot();

	//任意のキーA
	if (pInput->GetPress(DIK_A) == true)
	{

		if (pInput->GetPress(DIK_W) == true)
		{//左上移動
		 //モデルの移動	モデルの移動する角度(カメラの向き + 角度) * 移動量
			m_pos.x -= sinf(pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.75f) * MODEL_SPEED;
			m_pos.z -= cosf(pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.75f) * MODEL_SPEED;
			m_fDestAngle = (pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.75f);
		}
		else if (pInput->GetPress(DIK_S) == true)
		{//左下移動
		 //モデルの移動	モデルの移動する角度(カメラの向き + 角度) * 移動量
			m_pos.x -= sinf(pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.25f) * MODEL_SPEED;
			m_pos.z -= cosf(pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.25f) * MODEL_SPEED;
			m_fDestAngle = (pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.25f);
		}
		else
		{	//モデルの移動	モデルの移動する角度(カメラの向き + 角度) * 移動量
			m_pos.x -= sinf(pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.5f) * MODEL_SPEED;
			m_pos.z -= cosf(pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.5f) * MODEL_SPEED;
			m_fDestAngle = (pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.5f);
		}
	}
	//任意のキーD
	else if (pInput->GetPress(DIK_D) == true)
	{
		if (pInput->GetPress(DIK_W) == true)
		{//右上移動
		 //モデルの移動	モデルの移動する角度(カメラの向き + 角度) * 移動量
			m_pos.x -= sinf(pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.75f) * MODEL_SPEED;
			m_pos.z -= cosf(pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.75f) * MODEL_SPEED;
			m_fDestAngle = (pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.75f);
		}
		else if (pInput->GetPress(DIK_S) == true)
		{//右下移動
		 //モデルの移動	モデルの移動する角度(カメラの向き + 角度) * 移動量
			m_pos.x -= sinf(pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.25f) * MODEL_SPEED;
			m_pos.z -= cosf(pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.25f) * MODEL_SPEED;
			m_fDestAngle = (pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.25f);
		}
		else
		{	//モデルの移動	モデルの移動する角度(カメラの向き + 角度) * 移動量
			m_pos.x -= sinf(pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.5f) * MODEL_SPEED;
			m_pos.z -= cosf(pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.5f) * MODEL_SPEED;
			m_fDestAngle = (pCamera->GetCamera().rotCamera.y - D3DX_PI * 0.5f);
		}
	}
	//任意のキーW
	else if (pInput->GetPress(DIK_W) == true)
	{	//モデルの移動	モデルの移動する角度(カメラの向き + 角度) * 移動量
		m_pos.x += sinf(pCamera->GetCamera().rotCamera.y) * MODEL_SPEED;
		m_pos.z += cosf(pCamera->GetCamera().rotCamera.y) * MODEL_SPEED;
		m_fDestAngle = (pCamera->GetCamera().rotCamera.y + D3DX_PI * 1.0f);

	}
	//任意のキーS
	else if (pInput->GetPress(DIK_S) == true)
	{
		//モデルの移動	モデルの移動する角度(カメラの向き + 角度) * 移動量
		m_pos.x -= sinf(pCamera->GetCamera().rotCamera.y) * MODEL_SPEED;
		m_pos.z -= cosf(pCamera->GetCamera().rotCamera.y) * MODEL_SPEED;
		m_fDestAngle = (pCamera->GetCamera().rotCamera.y + D3DX_PI * 0.0f);
	}

	if (pInput->GetTrigger(DIK_1) == true)
	{
		//モデルを切り替え
		m_nType -= 1;

		//3Dオブジェクトとビルボードの切り替え
		if (m_nType == m_nMaxModel)
		{
			m_bBillboard = false;
			m_pBBItem->GetpBillBoard()->bDrawSet(m_bBillboard);
		}
		//0以下なら最後のモデルへ
		if (m_nType < 0)
		{
			m_nType = m_nMaxModel;
			m_bBillboard = true;
			m_pBBItem->GetpBillBoard()->bDrawSet(m_bBillboard);
		}
		if (m_bBillboard == false)
		{	//ビルボードではないとき
			//モデルを割り当て
			m_pObject->BindModel(m_nNumMat[m_nType], m_pMesh[m_nType], m_pBuffMat[m_nType]);
		}
	}
	else if (pInput->GetTrigger(DIK_2) == true)
	{
		m_nType += 1;
		if (m_nType == m_nMaxModel)
		{
			m_bBillboard = true;
			m_pBBItem->GetpBillBoard()->bDrawSet(m_bBillboard);
		}

		//モデル最大数以上なら0番目のモデルへ
		if (m_nType > m_nMaxModel)
		{
			m_nType = 0;
			m_bBillboard = false;
			m_pBBItem->GetpBillBoard()->bDrawSet(m_bBillboard);
		}

		if (m_bBillboard == false)
		{	//ビルボードではないとき
			//モデルを割り当て
			m_pObject->BindModel(m_nNumMat[m_nType], m_pMesh[m_nType], m_pBuffMat[m_nType]);
		}
	}

	if (pInput->GetTrigger(DIK_RETURN) == true)
	{
		CObjectBG::Create(m_pos, m_rot, D3DXVECTOR3(0.0f, 0.0f, 0.0f)
			, (CObjectBG::MODELTYPE)m_nType, CObjectBG::MOVETYPE_NONE, 1);
	}

	if (pInput->GetTrigger(DIK_BACKSPACE) == true)
	{
		CScene *pScene;
		//プライオリティーチェック
		pScene = CScene::GetTop(3);

		//NULLチェック
		while (pScene != NULL)
		{
			//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
			CScene *pSceneNext = pScene->GetNext();
			if (pScene->GetDeath() == false)
			{
				//タイプがオブジェクトだったら
				if (pScene->GetObjType() == OBJTYPE_BGMODEL)
				{
					D3DXVECTOR3 ModelPos;
					ModelPos = ((CObjectBG*)pScene)->GetPos();

					if (m_pos.x + (float)m_nRange >= ModelPos.x && m_pos.x - (float)m_nRange <= ModelPos.x)
					{// Zの範囲内にいる
						if (m_pos.z + (float)m_nRange >= ModelPos.z && m_pos.z - (float)m_nRange <= ModelPos.z)
						{// Xの範囲内にいる
							((CObjectBG*)pScene)->Uninit();
						}
					}
				}
			}
			//Nextに次のSceneを入れる
			pScene = pSceneNext;
		}
	}

	if (pInput->GetTrigger(DIK_RSHIFT) == true)
	{	//ファイルセーブ
		SaveFile();
	}
	else if (pInput->GetTrigger(DIK_RCONTROL) == true)
	{	//ファイルロード
		LoadFile();
	}
	//削除範囲拡大縮小
	if (pInput->GetPress(DIK_0) == true)
	{
		m_nRange++;
	}
	else if (pInput->GetPress(DIK_9) == true)
	{
		if (m_nRange > 0)
		{
			m_nRange--;
		}
	}

	//オブジェクトの回転処理
	if (pInput->GetPress(DIK_F) == true)
	{
		m_rot.y += 0.01f;
	}
	else if (pInput->GetPress(DIK_G) == true)
	{
		m_rot.y -= 0.01f;
	}
	else if (pInput->GetTrigger(DIK_H) == true)
	{
		m_rot.y += D3DX_PI / 2;
	}
	else if (pInput->GetTrigger(DIK_J) == true)
	{
		m_rot.y -= D3DX_PI / 2;
	}
	else if (pInput->GetTrigger(DIK_K) == true)
	{
		m_rot.y = 0;
	}

	//位置と回転の更新
	m_pObject->Setpos(m_pos);
	m_pObject->Setrot(m_rot);
	//
	m_pBBItem->SetPosItem(m_pos);

#ifdef  _DEBUG
	CDebugProc::Print(1, " [操作方法]\n W,A,S,Dで移動 F,Gでモデル回転 H,Jで90度回転 Kで回転リセット  \n");
	CDebugProc::Print(1, " 1,2キーでモデル切り替え ENTERキーで配置 BACKSPACEキーで範囲削除\n");
	CDebugProc::Print(1, " 右Shiftで保存 右CONTROLで読み込み 0キーで範囲増加 9キーで範囲減少\n\n");
	CDebugProc::Print(1, " 削除範囲        : ( %d )\n", m_nRange);
	CDebugProc::Print(1, " モデルの位置    : ( %.1f ,%.1f ,%.1f )\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print(1, " モデルのタイプ  : ( No.%d )\n", m_nType + 1);

#endif

#endif // 0
}

//=============================================================================
// オブジェクトの描画処理
//=============================================================================
void CSetObject::Draw(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DXMATRIX mtxParent;

	////ビルボードではないとき
	//if (m_bBillboard == false)
	//{
	//	// ワールドマトリックスの初期化
	//	D3DXMatrixIdentity(&m_mtxWorld);
	//	// 回転を反映
	//	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	//	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	//	// 位置を反映
	//	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	//	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//	//影の描画処理
	//	D3DXMATRIX	mtxShadow;
	//	D3DXPLANE	planeField;
	//	D3DXVECTOR4 VecLight;
	//	D3DXVECTOR3 pos, normal;

	//	// ライトを無効にする
	//	pDevice->LightEnable(0, FALSE);
	//	pDevice->LightEnable(1, FALSE);
	//	pDevice->LightEnable(2, FALSE);
	//	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//	//減算合成
	//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//	//シャドウマトリックスの初期化
	//	D3DXMatrixIdentity(&mtxShadow);
	//	//ライトの設定
	//	VecLight = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.0f);
	//	//影の位置設定
	//	pos = D3DXVECTOR3(0.0f, 0.01f, 0.0f);
	//	//法線の設定
	//	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//	//平面を作成
	//	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
	//	//影マトリックスの設定
	//	D3DXMatrixShadow(&mtxShadow, &VecLight, &planeField);
	//	//ワールドマトリックスと掛け合わせる
	//	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);
	//	//ワールドマトリックスの設定
	//	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	//	//if (m_pObject != NULL)
	//	//{
	//	//	m_pObject->Draw();
	//	//}
	//	//レンダーステイトを元に戻す
	//	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//	// ライトを有効にする
	//	pDevice->LightEnable(0, TRUE);
	//	pDevice->LightEnable(1, TRUE);
	//	pDevice->LightEnable(2, TRUE);
	//	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//	// ワールドマトリックスの設定
	//	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);


	//	//if (m_pObject != NULL)
	//	//{
	//	//	m_pObject->Draw();
	//	//}
	//}
}

//=============================================================================
// オブジェクトの位置設定
//=============================================================================
void CSetObject::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// テクスチャの読み込み処理
//=============================================================================
HRESULT CSetObject::Load(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	//ファイル読み込み用変数
	FILE *pFile;			//ファイルポインタ
	char *pStrcur;			//現在の先頭の文字列
	char aLine[256];		//文字列
	char aStr[256];			//一時保存文字列
	int nIndex = 0;			//現在のインデックス
	int nWord = 0;			//ポップで返された値を保持
	int nNumModel = 0;		//モデルの数
	char aFileName[MODELTYPE_MAX][256];	//モデルのファイル名
	int nCntModel = 0;		//モデルカウント用

							//ファイルを開く 読み込み
	pFile = fopen(FILE_NAME0, "r");
	//NULLチェック
	if (pFile != NULL)
	{
		while (1)
		{
			//文字列の先頭を設定
			pStrcur = ReadLine(pFile, &aLine[0]);
			//文字列を取り出す
			strcpy(aStr, pStrcur);

			//文字列のデータ 比較する文字列 比較する文字数
			if (memcmp(pStrcur, "NUM_MODEL = ", strlen("NUM_MODEL = ")) == 0)
			{
				//頭出し
				pStrcur += strlen("NUM_MODEL = ");
				//文字列の先頭を設定
				strcpy(aStr, pStrcur);
				//文字列抜き出し
				nNumModel = atoi(pStrcur);
				m_nMaxModel = nNumModel;
			}

			if (memcmp(pStrcur, "MODEL_FILENAME = ", strlen("MODEL_FILENAME = ")) == 0)
			{
				//頭出し
				pStrcur += strlen("MODEL_FILENAME = ");

				//文字列を設定
				strcpy(aStr, pStrcur);

				//必要な文字列の最後の文字までの文字数を数える
				int nNullNum = PopString(pStrcur, &aStr[0]);

				//文字列を取り戻す
				strcpy(aStr, pStrcur);

				//最後の文字にNULL文字を入れる
				aStr[nNullNum - 1] = '\0';

				//対象の文字列から抜き出し
				strcpy(&aFileName[nCntModel][0], aStr);

				strcpy(&m_aFileName[nCntModel][0], &aFileName[nCntModel][0]);

				// Xファイルの読み込み
				D3DXLoadMeshFromX(&aFileName[nCntModel][0], D3DXMESH_SYSTEMMEM, pDevice, NULL,
					&m_pBuffMat[nCntModel], NULL, &m_nNumMat[nCntModel], &m_pMesh[nCntModel]);

				nCntModel++;
			}

			//スクリプトの終わり
			if (memcmp(pStrcur, "END_SCRIPT	", strlen("END_SCRIPT")) == 0)
			{
				break;
			}
		}
	}
	//ファイルを閉じる
	fclose(pFile);


	//テクスチャの読み込み
	for (int nCnt = 0; nCnt < m_nMaxModel; nCnt++)
	{
		//マテリアル情報からテクスチャの取得
		pMat = (D3DXMATERIAL*)m_pBuffMat[nCnt]->GetBufferPointer();

		//マテリアルの数回す
		for (int nCntMatTex = 0; nCntMatTex < (int)m_nNumMat[nCnt]; nCntMatTex++)
		{
			if (pMat[nCntMatTex].pTextureFilename != NULL)
			{
				// テクスチャの設定
				D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
					pMat[nCntMatTex].pTextureFilename,	// ファイルの名前
					&m_pTexture[nCnt]);					// テクスチャへのポインタ
				//色の変化
				pMat[nCntMatTex].MatD3D.Diffuse.a = 0.6f;
			}
		}
	}

	return S_OK;
}

//=============================================================================
// テクスチャの破棄処理
//=============================================================================
void CSetObject::UnLoad(void)
{
	for (int nCnt = 0; nCnt < m_nMaxModel; nCnt++)
	{
		// メッシュの開放
		if (m_pMesh[nCnt] != NULL)
		{
			m_pMesh[nCnt]->Release();
			m_pMesh[nCnt] = NULL;
		}
		// マテリアルの開放
		if (m_pBuffMat[nCnt] != NULL)
		{
			m_pBuffMat[nCnt]->Release();
			m_pBuffMat[nCnt] = NULL;
		}

		//テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
//=============================================================================
// オブジェクトの位置
//=============================================================================
D3DXVECTOR3 CSetObject::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// オブジェクトの配置情報を保存
//=============================================================================
void CSetObject::SaveFile(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//ファイル
//	FILE *pFile;
#if 0
	//書き込み
	pFile = fopen(FILE_NAME0, "w");
	//NULLチェック
	if (pFile != NULL)
	{	//ファイル書き込み
		fprintf(pFile, "#============================================================\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "# [モデル配置ツール]スクリプトファイル [%s]\n", FILE_NAME0);
		fprintf(pFile, "#  Author : MIKIYA MEGURO\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#============================================================\n");

		fprintf(pFile, "SCRIPT			# この行は絶対消さないこと！\n\n");

		fprintf(pFile, "#------------------------------------------------------------\n");
		fprintf(pFile, "#                      モデル数 \n");
		fprintf(pFile, "#------------------------------------------------------------\n");
		fprintf(pFile, "NUM_MODEL = %d\n\n", m_nMaxModel);




		fprintf(pFile, "#------------------------------------------------------------\n");
		fprintf(pFile, "#                      モデルファイル名\n");
		fprintf(pFile, "#------------------------------------------------------------\n");

		//テクスチャの読み込み
		for (int nCnt = 0; nCnt < m_nMaxModel; nCnt++)
		{
			fprintf(pFile, "MODEL_FILENAME = %s\n", &m_aFileName[nCnt]);
		}

		fprintf(pFile, "\n#------------------------------------------------------------\n");
		fprintf(pFile, "#                      モデル配置情報 \n");
		fprintf(pFile, "#------------------------------------------------------------\n\n");

		CScene *pScene;
		//プライオリティーチェック
		pScene = CScene::GetTop(3);

		//NULLチェック
		while (pScene != NULL)
		{
			//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
			CScene *pSceneNext = pScene->GetNext();
			if (pScene->GetDeath() == false)
			{
				//タイプがオブジェクトだったら
				if (pScene->GetObjType() == OBJTYPE_BGMODEL)
				{
					D3DXVECTOR3 Pos;
					D3DXVECTOR3 Rot;
					int nType = 0;
					Pos = ((CObjectBG*)pScene)->GetPos();
					Rot = ((CObjectBG*)pScene)->GetRot();
					nType = ((CObjectBG*)pScene)->GetModelType();

					fprintf(pFile, "MODELSET \n");
					fprintf(pFile, "\tTYPE = %d\n", nType);
					fprintf(pFile, "\tPOS = %.1f %.1f %.1f\n", Pos.x, Pos.y, Pos.z);
					fprintf(pFile, "\tROT = %.1f %.1f %.1f\n", Rot.x, Rot.y, Rot.z);
					fprintf(pFile, "END_MODELSET\n\n");

				}
			}
			//Nextに次のSceneを入れる
			pScene = pSceneNext;
		}
		fprintf(pFile, "END_SCRIPT		# この行は絶対消さないこと！");
	}
	else
	{	//ファイルが開けなかった
		//printf("ファイルが開けませんでした\n");
	}
	//ファイルを閉じる
	fclose(pFile);
#endif

#if 0
	////書き込み
	//pFile = fopen(FILE_NAME1, "wb");
	////NULLチェック
	//if (pFile != NULL)
	//{	//ファイル読み込み
	//	//fwrite(&g_aHeght[0][0], sizeof(float), m_nSplitX * m_nSplitZ, pFile);
	//}
	//else
	//{	//ファイルが開けなかった
	//	printf("ファイルが開けませんでした\n");
	//}
	////ファイルを閉じる
	//fclose(pFile);
#endif

}

//=============================================================================
// オブジェクトの配置情報を読み込み
//=============================================================================
void CSetObject::LoadFile(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//ファイル読み込み用変数
	FILE *pFile;			//ファイルポインタ
	char *pStrcur;			//現在の先頭の文字列
	char aLine[256];		//文字列
	char aStr[256];			//一時保存文字列
	int nIndex = 0;			//現在のインデックス
	int nWord = 0;			//ポップで返された値を保持
	int nNumModel = 0;		//モデルの数
	int nType = 0;			//モデルの種類
	D3DXVECTOR3 ModelPos;	//モデルの位置
	D3DXVECTOR3 ModelRot;
	//ファイルを開く 読み込み
	pFile = fopen(FILE_NAME0, "r");
	//NULLチェック
	if (pFile != NULL)
	{
		while (1)
		{
			//文字列の先頭を設定
			pStrcur = ReadLine(pFile, &aLine[0]);
			//文字列を取り出す
			strcpy(aStr, pStrcur);

			//オブジェクト読み込み
			if (memcmp(pStrcur, "MODELSET", strlen("MODELSET")) == 0)
			{
				//頭出し
				pStrcur += strlen("MODELSET");
				//文字列の先頭を設定
				pStrcur = ReadLine(pFile, &aLine[0]);
				//種類
				if (memcmp(pStrcur, "TYPE = ", strlen("TYPE = ")) == 0)
				{
					//頭出し
					pStrcur += strlen("TYPE = ");
					//文字列の先頭を設定
					strcpy(aStr, pStrcur);
					//文字列抜き出し
					nType = atoi(pStrcur);
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
				}
				//位置
				if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
				{
					//頭出し
					pStrcur += strlen("POS = ");
					//文字列の先頭を設定
					strcpy(aStr, pStrcur);

					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//POS.X代入
					ModelPos.x = (float)atof(pStrcur);
					//文字数分進める
					pStrcur += nWord;

					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//POS.Y代入
					ModelPos.y = (float)atof(pStrcur);
					//文字数分進める
					pStrcur += nWord;

					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//POS.Z代入
					ModelPos.z = (float)atof(pStrcur);
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
				}
				//ROTを読み込み
				if (memcmp(pStrcur, "ROT = ", strlen("ROT = ")) == 0)
				{
					//頭出し
					pStrcur += strlen("ROT = ");
					//文字列の先頭を設定
					strcpy(aStr, pStrcur);

					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//文字列変換
					ModelRot.x = (float)atof(pStrcur);

					//文字数分進める
					pStrcur += nWord;
					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//文字列変換
					ModelRot.y = (float)atof(pStrcur);

					//文字数分進める
					pStrcur += nWord;
					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//文字列変換
					ModelRot.z = (float)atof(pStrcur);
				}
			}
			//モデルを生成
			if (memcmp(pStrcur, "END_MODELSET", strlen("END_MODELSET")) == 0)
			{
				//CObjectBG::Create(ModelPos, ModelRot, D3DXVECTOR3(0.0f, 0.0f, 0.0f)
				//	, (CObjectBG::MODELTYPE)nType, CObjectBG::MOVETYPE_NONE, 1);
				CSceneX::Create(ModelPos, (CLoad::MODEL)nType);
			}
			//スクリプトの終わり
			if (memcmp(pStrcur, "END_SCRIPT	", strlen("END_SCRIPT")) == 0)
			{
				break;
			}
		}
	}

	//ファイルを閉じる
	fclose(pFile);
}


//=============================================================================
//　ファイル読み込み無効文を排除
//=============================================================================
char *CSetObject::ReadLine(FILE *pFile, char *pDst)
{
	while (1)
	{
		//１行分読み込み
		fgets(&pDst[0], 256, pFile);

		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pDst, "#", strlen("#")) == 0)
		{
			pDst += strlen("\n");
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, "\t", strlen("\t")) == 0)
		{
			pDst += strlen("\t");
			while (1)
			{
				if (memcmp(pDst, "\t", strlen("\t")) == 0)
				{
					pDst += strlen("\t");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, " ", strlen(" ")) == 0)
		{
			pDst += strlen(" ");
			while (1)
			{
				if (memcmp(pDst, " ", strlen(" ")) == 0)
				{
					pDst += strlen(" ");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, "\n", strlen("\n")) == 0)
		{
			pDst += strlen("\n");
		}
		else
		{
			break;
		}
	}
	return pDst;
}

//=============================================================================
//　ファイル読み込み先頭を排除
//=============================================================================
char * CSetObject::GetLineTop(char * pStr)
{
	while (1)
	{
		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{
			pStr += strlen(" ");
			while (1)
			{
				if (memcmp(pStr, " ", strlen(" ")) == 0)
				{
					pStr += strlen(" ");
				}
				else
				{
					break;
				}
				break;
			}
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{
			pStr += strlen("\t");
			while (1)
			{
				if (memcmp(pStr, "\t", strlen("\t")) == 0)
				{
					pStr += strlen("\t");
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	return pStr;
}

//=============================================================================
//　文字数を返す
//=============================================================================
int CSetObject::PopString(char * pStr, char * pDest)
{
	int nWord = 0;

	while (1)
	{	//頭出し
		pStr += 1;
		nWord += 1;
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{	//頭出し
			pStr = "\0";
			nWord += 1;
			break;
		}
		if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{	//頭出し
			pStr = "\0";
			nWord += strlen("\t");
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pStr, "\n", strlen("\n")) == 0)
		{
			//頭出し
			nWord += strlen("\n");
			break;
		}
	}
	strcpy(pDest, pStr);
	//文字列の数を返す
	return nWord;
}
