@echo off
rem �e�N�X�`���t�@�C���ϊ�����
rem �r���h����
for /R %%1 in (*.bmp) do ..\..\tools\texture_converter\TextureConverter %%1
for /R %%1 in (*.tga) do ..\..\tools\texture_converter\TextureConverter %%1

pause

exit
