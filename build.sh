mkdir _build > /dev/null
pushd _build > /dev/null
# 使用 QT5_DIR 变量指定 Qt5 的安装路径
# 或使用 Qt6_DIR 变量指定 Qt6 的安装路径
cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build .
popd > /dev/null
