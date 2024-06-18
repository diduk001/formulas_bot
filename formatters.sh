find . -not \( -path "./lib/*" -o -path "./cmake-build-debug/*" -o -path "./build/*" -o -path "./CMakeFiles/*" \) \( -iname "*.h" -o -iname "*.cpp" \) -print0 | \
  xargs clang-format -dry-run -i --Werror

cpplint --exclude=lib/ --exclude=cmake-build-debug/ --exclude=build/ --exclude=CMakeFiles --filter=-legal/copyright,-build/include_subdir,-build/c++11 --recursive .
cppcheck --std=c++20 -i cmake-build-debug -i lib -i build -i CMakeFiles .