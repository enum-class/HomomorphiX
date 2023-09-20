#! /bin/bash

run-clang-tidy -fix -extra-arg=-std=c++17 -extra-arg=-Wno-unknown-warning-option `git diff --name-only origin/master`
