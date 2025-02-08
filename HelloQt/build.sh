mkdir _build > /dev/null
pushd _build > /dev/null
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build . --config Release
popd > /dev/null
