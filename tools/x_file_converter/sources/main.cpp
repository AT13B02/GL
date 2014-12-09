
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>

#include "XfileParser.h"

int main(int argc, char* argv[])
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	char aFileName[256] = {};

	if(argc < 2)
	{
		// ファイルを指定していない
		printf("ファイルが指定されていません\n");
		exit(1);
	}

	// ファイル名コピー
	strncpy_s(aFileName, sizeof(aFileName)-1, argv[1], sizeof(aFileName)-1);

	// Xファイルパース
	XFileParser parser;
	parser.ParseFile(aFileName);

	// データ書き出し
	parser.WriteBinDataGL();

	return 0;
}