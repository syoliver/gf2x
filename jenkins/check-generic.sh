. "`dirname $0`"/common.sh
autoreconf -i
./configure $configure_extra
"$MAKE"
"$MAKE" check
if [ -f "`dirname $0`"/extra-"`basename $0`" ] ; then
    . "`dirname $0`"/extra-"`basename $0`"
fi

# do that on all architectures.
"$MAKE" distclean
./configure $configure_extra --disable-hardware-specific-code
"$MAKE"
"$MAKE" check
"$MAKE" tune-lowlevel
"$MAKE" tune-toom TOOM_TUNING_LIMIT=64
if [ -f "`dirname $0`"/extra-"`basename $0`" ] ; then
    . "`dirname $0`"/extra-"`basename $0`"
fi

