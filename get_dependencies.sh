#/bin/sh

wget -O stbimage.zip https://codeload.github.com/nothings/stb/zip/master
unzip stbimage.zip
/bin/rm -rf lib
/bin/rm -rf stbimage.zip
mv stb-master lib

