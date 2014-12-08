// Xファイルをパースする

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
// 頂点保存用キャッシュ
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/23
//*****************************************************************************
struct CacheEntry
{
	UINT uIndex;		// キャッシュインデックス
	CacheEntry *pNext;	// 次のキャッシュへのポインタ
};

class XFileParser
{
public:

	// ファイルパース
	void ParseFile(char* pFileName);

	// OBJ形式で出力
	void WriteOBJData();
	// 独自フォーマットで出力
	void WriteBinDataDX();
	// 独自フォーマットで出力
	void WriteBinDataGL();

private:

	// 面頂点・面法線・面マテリアルインデックス
	struct VtxFacePosNorMatIndex
	{
		kb::CArray<int> idxPos;
		kb::CArray<int> idxNor;
		int idxMat;
	};

	// マテリアル情報
	struct Material
	{
		Vector4 Diffuse;
		Vector4 Ambient;
		Vector4 Specular;
		Vector4 Emissive;
		float SpecPower;
	};

	// テクスチャ付マテリアル情報
	struct TexMaterial
	{
		Material mat;
		char TexFileName[MAX_PATH];
	};

	// 3頂点構成面
	struct Vtx3Face
	{
		int postex[3];	// 頂点・テクスチャ座標インデックス
		int nor[3];	// 法線インデックス
		int mat;	// マテリアルインデックス
	};

	// 頂点情報
	struct Vertex
	{
		Vector3 pos;
		Vector3 nor;
		Vector2 tex;
	};

	// メッシュアトリビュート
	struct MeshAttribute
	{
		unsigned idxStart;	// 開始インデックス
		unsigned idxNum;	// インデックス数
		unsigned vtxStart;	// 開始頂点番号
		unsigned vtxNum;	// 頂点数
		unsigned faceNum;	// プリミティブ数
	};

	// データヘッダ
	struct DataHeader
	{
		unsigned uVtx;
		unsigned uIdx;
		unsigned uMat;
		unsigned uAtt;
	};

private:

	// 頂点読み込み
	void ParsePosition(std::ifstream &ifs);
	// 法線読み込み
	void ParseNormal(std::ifstream &ifs);
	// テクスチャ座標読み込み
	void ParseTexCoord(std::ifstream &ifs);
	// マテリアル読み込み
	void ParseMaterial(std::ifstream &ifs);

	// 面分割処理
	// 指定した番号のインデックスから分割処理
	Vtx3Face DivideFace(int nIndex, VtxFacePosNorMatIndex& idx);

	// 頂点・インデックス生成
	void CreateVertexAndIndex();

	// 頂点・インデックス追加
	void AddVertexAndIndex(Vtx3Face& faceInfo, const int faceIndex, Vertex* pVtx);

	// 重複頂点だった場合、ハッシュテーブルに追加
	DWORD AddVertex(UINT uHash, Vertex *pVtx);

private:

	// ファイル名
	kb::CString strFileName;

	// 座標
	kb::CArray<Vector3> position;
	// 法線
	kb::CArray<Vector3> normal;
	// テクスチャ座標
	kb::CArray<Vector2> texcoord;

	// マテリアル
	kb::CArray<TexMaterial> material;

	// 面頂点・面法線インデックス
	kb::CArray<VtxFacePosNorMatIndex> PosNorIndex;

	// 3頂点構成面データ
	kb::CArray<Vtx3Face> Vtx3FaceIndex;

	// 重複した頂点のためのハッシュテーブル
	CGrowableArray <CacheEntry*>	VertexCache;

	// 座標出力バッファ
	CGrowableArray<Vector3> outPosition;
	// 法線出力バッファ
	CGrowableArray<Vector3> outNormal;
	// テクスチャ座標出力バッファ
	CGrowableArray<Vector2> outTexcoord;

	// メッシュアトリビュート
	CGrowableArray<MeshAttribute> outAttribute;

	// 頂点
	//CGrowableArray<Vertex> vertex;
	// インデックス
	CGrowableArray<unsigned> index;
};

#endif	// __KBR_XFILE_PARSER_H__

// EOF