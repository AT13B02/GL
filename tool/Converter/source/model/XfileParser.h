// X�t�@�C�����p�[�X����

#pragma once
#ifndef __KBR_XFILE_PARSER_H__
#define __KBR_XFILE_PARSER_H__

#include <Windows.h>
#include "kbMath.h"
#include "CGrowableArray.h"
#include <fstream>
#include "kbArray.h"
#include "kbString.h"

//*****************************************************************************
// ���_�ۑ��p�L���b�V��
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/23
//*****************************************************************************
struct CacheEntry
{
	UINT uIndex;		// �L���b�V���C���f�b�N�X
	CacheEntry *pNext;	// ���̃L���b�V���ւ̃|�C���^
};

class XFileParser
{
public:

	// �t�@�C���p�[�X
	void ParseFile(char* pFileName);

	// OBJ�`���ŏo��
	void WriteOBJData();
	// �Ǝ��t�H�[�}�b�g�ŏo��
	void WriteBinDataDX();
	// �Ǝ��t�H�[�}�b�g�ŏo��
	void WriteBinDataGL();

private:

	// �ʒ��_�E�ʖ@���E�ʃ}�e���A���C���f�b�N�X
	struct VtxFacePosNorMatIndex
	{
		kb::CArray<int> idxPos;
		kb::CArray<int> idxNor;
		int idxMat;
	};

	// �}�e���A�����
	struct Material
	{
		Vector4 Diffuse;
		Vector4 Ambient;
		Vector4 Specular;
		Vector4 Emissive;
		float SpecPower;
	};

	// �e�N�X�`���t�}�e���A�����
	struct TexMaterial
	{
		Material mat;
		char TexFileName[MAX_PATH];
	};

	// 3���_�\����
	struct Vtx3Face
	{
		int postex[3];	// ���_�E�e�N�X�`�����W�C���f�b�N�X
		int nor[3];	// �@���C���f�b�N�X
		int mat;	// �}�e���A���C���f�b�N�X
	};

	// ���_���
	struct Vertex
	{
		Vector3 pos;
		Vector3 nor;
		Vector2 tex;
	};

	// ���b�V���A�g���r���[�g
	struct MeshAttribute
	{
		unsigned idxStart;	// �J�n�C���f�b�N�X
		unsigned idxNum;	// �C���f�b�N�X��
		unsigned vtxStart;	// �J�n���_�ԍ�
		unsigned vtxNum;	// ���_��
		unsigned faceNum;	// �v���~�e�B�u��
	};

	// �f�[�^�w�b�_
	struct DataHeader
	{
		unsigned uVtx;
		unsigned uIdx;
		unsigned uMat;
		unsigned uAtt;
	};

private:

	// ���_�ǂݍ���
	void ParsePosition(std::ifstream &ifs);
	// �@���ǂݍ���
	void ParseNormal(std::ifstream &ifs);
	// �e�N�X�`�����W�ǂݍ���
	void ParseTexCoord(std::ifstream &ifs);
	// �}�e���A���ǂݍ���
	void ParseMaterial(std::ifstream &ifs);

	// �ʕ�������
	// �w�肵���ԍ��̃C���f�b�N�X���番������
	Vtx3Face DivideFace(int nIndex, VtxFacePosNorMatIndex& idx);

	// ���_�E�C���f�b�N�X����
	void CreateVertexAndIndex();

	// ���_�E�C���f�b�N�X�ǉ�
	void AddVertexAndIndex(Vtx3Face& faceInfo, const int faceIndex, Vertex* pVtx);

	// �d�����_�������ꍇ�A�n�b�V���e�[�u���ɒǉ�
	DWORD AddVertex(UINT uHash, Vertex *pVtx);

private:

	// �t�@�C����
	kb::CString strFileName;

	// ���W
	kb::CArray<Vector3> position;
	// �@��
	kb::CArray<Vector3> normal;
	// �e�N�X�`�����W
	kb::CArray<Vector2> texcoord;

	// �}�e���A��
	kb::CArray<TexMaterial> material;

	// �ʒ��_�E�ʖ@���C���f�b�N�X
	kb::CArray<VtxFacePosNorMatIndex> PosNorIndex;

	// 3���_�\���ʃf�[�^
	kb::CArray<Vtx3Face> Vtx3FaceIndex;

	// �d���������_�̂��߂̃n�b�V���e�[�u��
	CGrowableArray <CacheEntry*>	VertexCache;

	// ���W�o�̓o�b�t�@
	CGrowableArray<Vector3> outPosition;
	// �@���o�̓o�b�t�@
	CGrowableArray<Vector3> outNormal;
	// �e�N�X�`�����W�o�̓o�b�t�@
	CGrowableArray<Vector2> outTexcoord;

	// ���b�V���A�g���r���[�g
	CGrowableArray<MeshAttribute> outAttribute;

	// ���_
	//CGrowableArray<Vertex> vertex;
	// �C���f�b�N�X
	CGrowableArray<unsigned> index;
};

#endif	// __KBR_XFILE_PARSER_H__

// EOF