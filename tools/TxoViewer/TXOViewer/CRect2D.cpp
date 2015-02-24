//=============================================================================
//
// �����ɕ`����2D�|���S���N���X [CRect2D.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/4
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CRect2D.h"
#include "CStaticVBO.h"

//=============================================================================
// 2D�`��
//=============================================================================
void CRect2D::DrawPrimitive(GLenum drawType, void* pBuffer, unsigned nNumVertex)
{
	CStaticVBO *pVtxBuff = NULL;
	CStaticVBO *pColorBuff = NULL;
	CStaticVBO *pTexCoordBuff = NULL;
	
	// VBO�쐬
	// ���_
	CStaticVBO::CreateBuffer(sizeof(Vector3) * nNumVertex, 3, GL_VERTEX_ARRAY, &pVtxBuff);
	// �F
	CStaticVBO::CreateBuffer(sizeof(Vector4) * nNumVertex, 4, GL_COLOR_ARRAY, &pColorBuff);
	// �e�N�X�`�����W
	CStaticVBO::CreateBuffer(sizeof(Vector2) * nNumVertex, 2, GL_TEXTURE_COORD_ARRAY, &pTexCoordBuff);

	VERTEX_2D *pVtx = (VERTEX_2D*)pBuffer;
	Vector3* pVtxPos;
	Vector4* pColor;
	Vector2* pTexCoord;
	pVtxBuff->GetBufferPointer((void**)&pVtxPos);
	pColorBuff->GetBufferPointer((void**)&pColor);
	pTexCoordBuff->GetBufferPointer((void**)&pTexCoord);

	for(int i = 0; i < (int)nNumVertex; i++)
	{
		pVtxPos[i] = pVtx[i].pos;
		pColor[i] = pVtx[i].color;
		pTexCoord[i] = pVtx[i].tex;
	}
	
	pVtxBuff->GenBuffer();
	pColorBuff->GenBuffer();
	pTexCoordBuff->GenBuffer();
	
	// �[�x�e�X�g������
	glDisable(GL_DEPTH_TEST);
	
	// ���_�z��L����
	pVtxBuff->ValidateArrayValue();
	// �J���[�z��L����
	pColorBuff->ValidateArrayValue();
	// �e�N�X�`���z��L����
	pTexCoordBuff->ValidateArrayValue();
	// �`��
	glDrawArrays(drawType, 0, nNumVertex);
	// �z�񖳌���
	pVtxBuff->InvalidateArrayValue();
	pColorBuff->InvalidateArrayValue();
	pTexCoordBuff->InvalidateArrayValue();
	
	// �[�x�e�X�g�L����
	glEnable(GL_DEPTH_TEST);

	pVtxBuff->Release();
	pColorBuff->Release();
	pTexCoordBuff->Release();
}

// EOF