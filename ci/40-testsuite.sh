#!/usr/bin/env bash

. "$(dirname $0)/000-functions.sh"
. "$(dirname $0)/001-environment.sh"
. "$(dirname $0)/003-trap-add.bash"
. "$(dirname $0)/004-disksize-watchdog.bash"

export TMPDIR=$(mktemp -d /tmp/XXXXXXXXXXXX)
trap_add "rm -rf $TMPDIR" EXIT

# Note that we now **SOURCE** all these scripts. This makes it possible
# to play tricks with what the source and build directories are.

. "$(dirname $0)"/01-conf.sh
. "$(dirname $0)"/02-build.sh
. "$(dirname $0)"/03-check.sh
