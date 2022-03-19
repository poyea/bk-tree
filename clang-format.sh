#!/bin/sh

set -e

find . -regex '.*\.\(cpp\|hpp\|cc\|cxx\|c\|cc\|h\)' -not -path './build/*' -exec clang-format -style=file -i {} \;