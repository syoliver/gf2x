. "`dirname $0`"/common.sh
autoreconf -i
./configure $configure_extra
"$MAKE"
"$MAKE" tune-lowlevel
"$MAKE" tune-toom
