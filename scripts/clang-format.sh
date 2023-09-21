#! /bin/bash

for run in {1..2}
do
  git clang-format-15 HEAD^ -- include/*.hpp include/*/*.hpp tests/*/*.cpp -f
done
