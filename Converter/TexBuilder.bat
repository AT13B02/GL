@echo off
rem テクスチャファイル変換処理
rem ビルド処理
for %%1 in (*.bmp) do TextureConverter %%1
for %%1 in (*.tga) do TextureConverter %%1

pause

exit
