find . -not \( -path "./lib/*" -o -path "./cmake-build-debug/*" -o -path "./build/*" \) \( -iname "*.h" -o -iname "*.cpp" \) -print0 | \
  xargs clang-format -dry-run -i --Werror

cpplint --exclude=lib/ --exclude=cmake-build-debug/ --exclude=build/ --filter=-legal/copyright,-build/include_subdir --recursive .
cppcheck --std=c++20 -i cmake-build-debug -i lib -i build .
