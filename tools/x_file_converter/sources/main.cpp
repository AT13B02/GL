
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
		// �t�@�C�����w�肵�Ă��Ȃ�
		printf("�t�@�C�����w�肳��Ă��܂���\n");
		exit(1);
	}

	// �t�@�C�����R�s�[
	strncpy_s(aFileName, sizeof(aFileName)-1, argv[1], sizeof(aFileName)-1);

	// X�t�@�C���p�[�X
	XFileParser parser;
	parser.ParseFile(aFileName);

	// �f�[�^�����o��
	parser.WriteBinDataGL();

	return 0;
}