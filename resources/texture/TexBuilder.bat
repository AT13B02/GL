@echo off
rem テクスチャファイル変換処理
rem ビルド処理
for /R %%1 in (*.bmp) do ..\..\tools\texture_converter\TextureConverter %%1
for /R %%1 in (*.tga) do ..\..\tools\texture_converter\TextureConverter %%1

pause

exit
