@echo off
rem �e�N�X�`���t�@�C���ϊ�����
rem �r���h����
for %%1 in (*.bmp) do TextureConverter %%1
for %%1 in (*.tga) do TextureConverter %%1

pause

exit
