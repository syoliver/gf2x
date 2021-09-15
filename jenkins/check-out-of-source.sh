. "`dirname $0`"/common.sh
autoreconf -i
src="$PWD"
TMP=`mktemp -d /tmp/${BUILD_TAG}-XXXXXXX`
cleanup() { rm -rf "$TMP" ; }
trap cleanup EXIT
cd "$TMP"
if ! ($src/configure $configure_extra && "$MAKE" && "$MAKE" check) ; then
   echo "FAILED"
   cd "$src"
   exit 1
fi
cd "$src"
