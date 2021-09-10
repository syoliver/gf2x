#!/usr/bin/env bash

. "$(dirname $0)/000-functions.sh"
. "$(dirname $0)/001-environment.sh"

enter_section configuration Configuring
autoreconf -i

if [ "$out_of_source" ] ; then
    if ! [ "$build_tree" ] ; then
        build_tree="${TMPDIR:-/tmp}/$CI_BUILD_NAME"
        # spaces in dir names don't work, mostly because of libtool
        # (look at gf2x/fft/libgf2x-fft.la)
        # This substitution is bash-only, but this should be fine to 
        # have in a conditional that non-bash skips over
        build_tree="${build_tree// /_}"
    fi
    if ! [ -d "$build_tree" ] ; then
        mkdir "$build_tree"
    fi
    configure_call="$source_tree/configure"
else
    build_tree=$PWD
    configure_call="./configure"
fi

export build_tree
export source_tree
export configure_call

if [ "$remove_gpl_sources" ] ; then
    ln -sf "toom-gpl-placeholder.c" "$source_tree"/toom-gpl.c
    $ECHO_E "${CSI_BLUE}Removing toom-gpl.c (trying an LGPL test)${CSI_RESET}"
fi

(cd "$build_tree" ; "$configure_call")

if [ "$do_make_dist" ] ; then
    eval $(cd "$build_tree" > /dev/null ; grep '^\(PACKAGE_\(TARNAME\|VERSION\)\)' Makefile | tr -d \  )
    cd "${TMPDIR:-/tmp}"
    tar xf "$build_tree/${PACKAGE_TARNAME}-${PACKAGE_VERSION}.tar.gz"
    # hack, and change source tree and build tree.
    source_tree="$PWD/${PACKAGE_TARNAME}-${PACKAGE_VERSION}"
    if [ "$out_of_source" ] ; then
        rm -rf "$build_tree"
        build_tree="${TMPDIR:-/tmp}/$CI_BUILD_NAME"
        build_tree="${build_tree// /_}"
        mkdir "$build_tree"
        configure_call="$source_tree/configure"
    else
        $ECHO_E "${CSI_BLUE}Changing source directory to $source_tree${CSI_RESET}"
        cd $source_tree
        build_tree=$PWD
    fi
    export build_tree
    export source_tree
    (cd "$build_tree" ; "$configure_call")
fi

leave_section

