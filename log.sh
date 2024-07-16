#!/bin/bash

# Get the current date and time
current_date=$(date +"%Y-%m-%d")
current_time=$(date +"%H:%M:%S")

# Initialize default values
BUILD_TYPE="Debug"
LIB_TYPE="Static"

# Parse arguments to determine BUILD_TYPE and LIB_TYPE
for arg in "$@"; do
    case "${arg,,}" in
        ("r")
            BUILD_TYPE="Release"
            ;;
        ("s")
            LIB_TYPE="Shared"
            ;;
    esac
done

# Construct the log file name
log_file="log_${current_date}_${current_time}-${BUILD_TYPE}-${LIB_TYPE}.log"

# Pass arguments to run.sh and capture the output
script -q -c "./run.sh $*" "$log_file"

# Remove ANSI color codes
sed 's/\x1b\[[0-9;]*[a-zA-Z]//g' "$log_file" > cleaned_log.log
rm "$log_file"
mv cleaned_log.log "$log_file"

# Make a log directory if it doesn't exist
mkdir -p logs

# Move the log file to the logs directory
mv "$log_file" logs/

# Make the log file read-only
chmod 444 "logs/$log_file"

# Print the path to the log file
echo -e "\e[34mLog file saved to: $(pwd)/logs/$log_file\e[0m"
