#!/bin/bash

# Function to run a command and compare output
run_test() {
    command=$1
    expected=$2
    output=$(echo -e "$command" | ./hsh 2>&1)  # Capture both stdout and stderr
    if [[ "$output" == *"$expected"* ]]; then  # Use pattern matching for env
        echo "Test Passed: $command"
    else
        echo "Test FAILED: $command"
        echo "Expected: '$expected', but got: '$output'"
    fi
}

# Adjusted tests
run_test "echo Hello, world!" "Hello, world!"
run_test "nonexistentcommand" "not found"  # Looking for "not found" in output
run_test "echo test" "test"
run_test "ls" "$(ls)"
run_test "exit" ""
run_test "env" "PATH="  # Testing for presence of PATH in env output

# Other tests remain the same...
