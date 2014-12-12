@echo off
rem xファイル変換処理
rem ビルド処理
for /R %%1 in (*.x) do ..\..\tools\x_file_converter\XFileConverter %%1

pause

exit
