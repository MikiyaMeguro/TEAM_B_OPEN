//=============================================================================
//
// �|�[�Y���� [pause.h]
// Author : Kodama Yuto
//
//	�N���X�̊T�v
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "scene.h"
#include "scene2D.h"

//=============================================================================
// �N���X��`
//=============================================================================
class CPause : public CScene
{
public:
	CPause();
	CPause(int nPriority = 7);
	~CPause();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CScene2D* m_pSelectMenu[4];//�|�[�Y���j���[�̌����p�ӂ���
};

#endif // !_PAUSE_H_
