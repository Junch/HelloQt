mkdir _build > /dev/null
pushd _build > /dev/null
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON  -DCMAKE_PREFIX_PATH=/Users/juchen3/Qt/5.15.2/clang_64
cmake --build .
popd > /dev/null
