#!/bin/bash

prev_char="."
while IFS= read -r -n1 char; do
    if [[ "$prev_char" =~ [.!?] && "$char" =~ [a-zA-Z] ]]; then
        printf "%s" "$(tr '[:lower:]' '[:upper:]' <<< "$char")"
    else
        printf "%s" "$char"
    fi
    if [[ ! "$char" =~ [[:space:]] ]]; then
        prev_char="$char"
    fi
done < input.txt
