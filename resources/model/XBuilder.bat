@echo off
rem x�t�@�C���ϊ�����
rem �r���h����
rem /R�̓T�u�t�H���_���T������Ė���

for /R %%1 in (*.x) do (
..\..\tool\x_file_converter\XFileConverter %%1
)

for /R %%1 in (*.xo) do (
move %%1 ..\..\framework\resources\model\game
)

pause

exit
