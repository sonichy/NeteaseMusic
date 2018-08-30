s="[Desktop Entry]\nName=网易云音乐\nComment=Media player\nExec=`pwd`/NeteaseMusic\nIcon=`pwd`/icon.jpg\nPath=`pwd`\nTerminal=false\nType=Application\nCategories=AudioVideo;"
echo -e $s > NeteaseMusic.desktop
cp `pwd`/NeteaseMusic.desktop ~/.local/share/applications/NeteaseMusic.desktop