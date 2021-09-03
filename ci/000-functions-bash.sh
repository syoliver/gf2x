section_stack=()

# Usage: enter_section [internal name] [message]
#
# The message is optional and defaults to the internal name
enter_section() {
    internal_name="$1"
    message="$2"
    : ${message:="$1"}
    section_stack+=("$1")
    echo -e "section_start:`date +%s`:$internal_name\r${CSI_KILLLINE}${CSI_BLUE}$message${CSI_RESET}"
}

# Usage: leave_section [internal name] [message]
#
# Both arguments are optional. The message defaults to nothing. The
# internal name defaults to the last pushed section. If an inconsistency
# is detected, error out.
leave_section() {
    if ! [ "${#section_stack[@]}" -gt 0 ] ; then
        echo "script error, no section stack !" >&2
        exit 1
    fi
    last_index=$((${#section_stack[@]}-1))
    last_section="${section_stack[$last_index]}"
    section_stack="${section_stack[@]::$last_index}"

    if [ "$internal_name" ] && [ "$last_section" != "$internal_name" ] ; then
        echo "script error, last pushed section is $last_section, not $internal_name !" >&2
        exit 1
    fi
    internal_name="$last_section"
    message="$2"
    echo -e "section_end:`date +%s`:$internal_name\r${CSI_KILLLINE}${CSI_BLUE}$message${CSI_RESET}"
}
