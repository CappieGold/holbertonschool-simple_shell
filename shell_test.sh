#!/bin/bash

# Function to run a command and compare output
run_test() {
    command=$1
    expected=$2
    output=$(echo -e "$command" | ./hsh)
    if [ "$output" == "$expected" ]; then
        echo "Test Passed: $command"
    else
        echo "Test FAILED: $command"
        echo "Expected: '$expected', but got: '$output'"
    fi
}

# Test simple command
run_test "echo Hello, world!" "Hello, world!"

# Test command not found
run_test "nonexistentcommand" "./hsh: 1: nonexistentcommand: not found"

# Test command with argument
run_test "echo test" "test"

# Test PATH usage
run_test "ls" "$(ls)"

# Test built-in command: exit
run_test "exit" ""

# Test built-in command: env (might need to adjust expected output)
env_output=$(env)
run_test "env" "$env_output"

# End of file (EOF) test
output=$(./hsh)
if [ -z "$output" ]; then
    echo "EOF Test Passed"
else
    echo "EOF Test FAILED"
fi

# Interactive mode test
output=$(echo "echo interactive test" | ./hsh)
if [ "$output" == "interactive test" ]; then
    echo "Interactive Mode Test Passed"
else
    echo "Interactive Mode Test FAILED"
fi

# Non-interactive mode test
output=$(echo "echo noninteractive test" | ./hsh)
if [ "$output" == "noninteractive test" ]; then
    echo "Non-Interactive Mode Test Passed"
else
    echo "Non-Interactive Mode Test FAILED"
fi
