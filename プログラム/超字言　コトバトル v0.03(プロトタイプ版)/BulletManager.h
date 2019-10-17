//=============================================================================
//
// 弾生成クラス処理 [BulletManager.h]
// Author : Kodama Yuto
//
//	クラスの概要
//
//=============================================================================
#ifndef _BULLET_MANAGER_H_
#define _BULLET_MANAGER_H_

#include "main.h"
class CBulletBase;


class CBulletManager
{
public:
	typedef enum
	{
		BULLET_MODEL,
		BULLET_WORD,
	}BULLET_TYPE;
	CBulletManager();
	~CBulletManager();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	bool BulletCreate(BULLET_TYPE type,D3DXVECTOR3 pos,D3DXVECTOR3 rot);
private:
	std::list<CBulletBase*> m_listBullet;
	static int m_nCntID;
};

#endif // !_BULLET_MANAGER_H_
