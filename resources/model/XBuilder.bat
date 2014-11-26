@echo off
rem xファイル変換処理
rem ビルド処理
rem /Rはサブフォルダも探すよって命令

for /R %%1 in (*.x) do (
..\..\tool\x_file_converter\XFileConverter %%1
)

for /R %%1 in (*.xo) do (
move %%1 ..\..\framework\resources\model\game
)

pause

exit
