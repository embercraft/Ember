#!/bin/bash

# Define the ember function
ember() {
    # Check if no arguments are passed
    if [ $# -eq 0 ]; then
        echo "No arguments provided. Use 'ember --help' for more information."
        return 1
    fi

    # Handle the --help option
    if [ "$1" = "--help" ]; then
        cat << EOF
Usage: ember [COMMAND] [SCENE]...

Commands:
  --help                      Display this help message
  --version, --v              Show version information
  launch                      Start Ember
  flush                       Flush the server
  load [SCENE]                Load a scene to the server
  fload [SCENE]               Flush then load a scene to the server
  log [message]               Send a message to the server to be logged

Examples:
  ember --help                # Display this help message
  ember --version             # Show version
  ember load scene.ember      # Load scene.ember
  ember flush                 # Flush the scene
  ember fload scene.ember     # Flush then load scene.ember
  ember log "Hello, world!"   # Log "Hello, world!"
EOF
        return 0
    fi

    # Handle specific ember subcommands
    case "$1" in
        --version | --v)
            echo "ember v0.1.0 (CLI feature branch)"
            ;;
        launch)
            SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" &> /dev/null && pwd)"
            echo "Launching Ember..."
            cd "$SCRIPT_DIR/Foundry" || { echo "Error: Unable to change directory"; return 1; }
            ../build/Debug-Static/Foundry/Foundry
            ;;
        load | fload)
            if [ -z "$2" ]; then
                echo "Error: No scene file specified."
                return 1
            fi

            # Convert the provided path to an absolute path
            ABS_PATH="$(realpath "$2")"

            if [ ! -f "$ABS_PATH" ]; then
                echo "Error: Scene file '$ABS_PATH' not found."
                return 1
            fi

            if [ "$1" = "fload" ]; then
                echo "flush" | nc localhost 8080
            fi

            echo "load $ABS_PATH" | nc localhost 8080
            ;;
        *)
            # Send everything else as-is
            echo "$*" | nc localhost 8080
            ;;
    esac
}

# Export the ember function so it can be used in the current shell
export -f ember

# Define the autocomplete function for ember
_ember_autocomplete() {
    local cur prev opts
    COMPREPLY=()
    cur="${COMP_WORDS[COMP_CWORD]}"
    prev="${COMP_WORDS[COMP_CWORD-1]}"
    opts="--help --version --v launch log flush load fload"

    # If the previous word is "load" or "fload", suggest scene files or directories
    if [[ "${prev}" == "load" || "${prev}" == "fload" ]]; then
        # Use compgen to generate possible completions
        local IFS=$'\n'
        local files=($(compgen -f -- "${cur}"))

        for f in "${files[@]}"; do
            if [ -d "$f" ]; then
                # Append "/" to directories
                COMPREPLY+=("$f/")
            else
                # Convert to absolute path before adding to completion
                COMPREPLY+=("$(realpath "$f")")
            fi
        done

        # Remove the last space if it's added by completion
        if [[ "${#COMPREPLY[@]}" -gt 0 ]]; then
            compopt -o nospace
        fi

        return 0
    fi

    # Suggest commands
    COMPREPLY=($(compgen -W "${opts}" -- ${cur}))
    return 0
}

# Register the autocomplete function for the ember command
complete -F _ember_autocomplete ember
