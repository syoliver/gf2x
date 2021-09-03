#!/usr/bin/env bash

. "$(dirname $0)/000-functions.sh"
. "$(dirname $0)/001-environment.sh"

enter_section configuration Configuring
autoreconf -i
if [ "$out_of_source" ] ; then
    (cd "$build_tree" ; "$source_tree"/configure)
else
    ./configure
fi
leave_section

