#!/bin/bash

# Get the current date and time
current_date=$(date +"%Y-%m-%d")
current_time=$(date +"%H:%M:%S")

# Construct the log file name
log_file="log_${current_date}_${current_time}-${BUILD_TYPE}-${LIB_TYPE}.log"

# Get the directory where this script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

# Navigate to the project directory
cd "$SCRIPT_DIR" || { echo -e "\033[31mFailed to navigate to the script directory.\033[0m"; exit 1; }

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
