//=============================================================================
//
// �v���C���[�̑̃p�[�c���� [CharaParts.h]
// Author : Kodama Yuto
//
//	�N���X�̊T�v
//
//=============================================================================
#ifndef _CHARA_PARTS_H_
#define _CHARA_PARTS_H_

#include "main.h"
#include "sceneX.h"
//=============================================================================
//	�N���X��`
//=============================================================================
class CCharaParts : public CSceneX
{
public:
	CCharaParts();
	~CCharaParts();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
};
#endif // !_CHARA_PARTS_H_
