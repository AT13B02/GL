@echo off
rem xファイル変換処理
rem ビルド処理
for %%1 in (*.x) do XFileConverter %%1

pause

exit
