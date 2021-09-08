#!/bin/sh

# trimmed down from the cado-nfs code

# We're /bin/sh, not bash.
#
# Our output must be a Dockerfile

. "$(dirname $0)/000-functions.sh"
. "$(dirname $0)/001-environment.sh"

if ! [ "$DOCKER_SCRIPT" ] ; then
    echo "Enter CI script for $CI_PROJECT_NAMESPACE/$CI_PROJECT_NAME, stage $CI_JOB_STAGE ; $CI_BUILD_NAME"
fi

enter_section preparation "System preparation (${RUNTIME_TYPE:-docker})"
# id -a
# use this to dump environment variables
# export
echo "en_US.UTF-8 UTF-8" > /etc/locale.gen
leave_section

enter_section install_packages "Installing required packages"

debian_packages="$debian_packages     bc"
debian_packages="$debian_packages     locales"
debian_packages="$debian_packages     make autoconf automake"
debian_packages="$debian_packages     libgmp-dev"
debian_packages="$debian_packages     autoconf automake"
# is full perl really needed ?
# debian_packages="$debian_packages     perl"

opensuse_packages="$opensuse_packages     bc"
opensuse_packages="$opensuse_packages     which"  # is type -p more portable?
opensuse_packages="$opensuse_packages     hostname"
opensuse_packages="$opensuse_packages     gmp-devel"
opensuse_packages="$opensuse_packages     gzip"

fedora_packages="$fedora_packages     bc"
fedora_packages="$fedora_packages     gmp-devel"
fedora_packages="$fedora_packages     hostname"
# is full perl really needed ? seems that perl-interpreter and the auto
# dependencies that we pull already pull what we need.
# fedora_packages="$fedora_packages     perl"

alpine_packages="$alpine_packages     bc"
alpine_packages="$alpine_packages     gmp-dev"
alpine_packages="$alpine_packages     make autoconf automake"
alpine_packages="$alpine_packages     bash"
alpine_packages="$alpine_packages     perl"

freebsd_packages="$freebsd_packages     gmp"
freebsd_packages="$freebsd_packages     gmake"
freebsd_packages="$freebsd_packages     bash"
freebsd_packages="$freebsd_packages     perl5"

while [ $# -gt 0 ] ; do
    case "$1" in
        coverage|clang|gcc|debug|icc) eval "$1=1";;
        *) echo "$1 -> ???" >&2 ; exit 1;;
    esac
    shift
done

# These variables are set in ci/001-environment.sh
if [ "$coverage" ] ; then
    # vim is needed because we have a bit of ex scripting...
    debian_packages="$debian_packages     lcov gcovr vim-nox"
    opensuse_packages="$opensuse_packages lcov gcovr vim"
    fedora_packages="$fedora_packages     lcov gcovr vim"
    alpine_packages="$alpine_packages     lcov gcovr vim"
    if is_freebsd ; then
        echo "coverage -> not on freebsd" >&2
        freebsd_packages="$freebsd_packages   lcov vim-console"
        # freebsd has no gcovr at the moment, so it's a no-go for now. not
        # sure we expect much benefit in running coverage tests on fbsd as
        # well anyway
        exit 1
    fi
fi

if [ "$gcc32" ] ; then
    if ! is_debian ; then
        echo "multlib -> only debian (fedora,opensuse:IDK ; alpine:no-go)" >&2
        # didn't even check freebsd
        exit 1
    fi
    # note that opensuse has gmp-devel-32bit
    debian_packages="$debian_packages     g++-multilib"
    debian_packages="$debian_packages     curl"
    debian_packages="$debian_packages     lzip"
    # fedora_packages="$fedora_packages     g++"
    # alpine_packages="$alpine_packages     g++"
fi

if [ "$gcc" ] ; then
    debian_packages="$debian_packages     g++"
    opensuse_packages="$opensuse_packages gcc gcc-c++"
    fedora_packages="$fedora_packages     g++"
    alpine_packages="$alpine_packages     g++"
    freebsd_packages="$freebsd_packages   gcc"  # this pulls g++ too
fi

if [ "$clang" ] ; then
    debian_packages="$debian_packages     clang"
    opensuse_packages="$opensuse_packages clang"
    fedora_packages="$fedora_packages     clang"
    alpine_packages="$alpine_packages     clang"
    freebsd_packages="$freebsd_packages   llvm"
fi

if [ "$coverity" ] ; then
    # nothing special at this point. Note that we've tested it on debian
    # only.
    debian_packages="$debian_packages     curl git"
    opensuse_packages="$opensuse_packages curl git"
    fedora_packages="$fedora_packages     curl git"
    alpine_packages="$alpine_packages     curl git"
    freebsd_packages="$freebsd_packages   curl git"
fi

if [ "$DOCKER_SCRIPT" ] ; then
    debian_packages="$debian_packages sudo git vim-nox gdb"
    opensuse_packages="$opensuse_packages sudo git vim gdb"
    fedora_packages="$fedora_packages sudo git vim gdb"
    alpine_packages="$alpine_packages sudo git vim gdb"
    freebsd_packages="$freebsd_packages sudo git vim-console gdb"
fi

if is_debian ; then
    DEBIAN_FRONTEND=noninteractive apt-get -y update
    DEBIAN_FRONTEND=noninteractive apt-get -y install $debian_packages
elif is_opensuse ; then
    zypper -n install $opensuse_packages
elif is_fedora ; then
    dnf -y install $fedora_packages
elif is_alpine ; then
    cat >> /etc/apk/repositories <<EOF
http://dl-cdn.alpinelinux.org/alpine/edge/testing
EOF
    # is the community repo useful ?
    #http://dl-cdn.alpinelinux.org/alpine/edge/community
    apk update
    apk add $alpine_packages
elif is_freebsd ; then
    env ASSUME_ALWAYS_YES=yes pkg install $freebsd_packages
fi

if [ "$gcc32" ] ; then
    NCPUS=`"$(dirname $0)/utilities/ncpus.sh"`
    cd /tmp/
    curl -O https://gmplib.org/download/gmp/gmp-6.2.1.tar.lz
    tar xf gmp-6.2.1.tar.lz
    cd gmp-6.2.1
    # $GMP is set in ci/001-environment.sh
    ./configure --prefix=$GMP ABI=32
    make -j$NCPUS
    make install
fi

leave_section
