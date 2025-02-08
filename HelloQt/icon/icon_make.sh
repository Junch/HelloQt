#!/bin/bash
# [使用sip和iconutil自动创建electron macOS图标。在Electron的项目中使用iconutil 和 - 掘金](https://juejin.cn/post/7127308585360424967)
# [Hello Vector SVG Icon (2) - SVG Repo](https://www.svgrepo.com/svg/333110/hello)

input_filepath='1024x1024.png'
output_iconset_name='icon.iconset'
mkdir $output_iconset_name

sips -z 16 16     $input_filepath --out "${output_iconset_name}/icon_16x16.png"
sips -z 32 32     $input_filepath --out "${output_iconset_name}/icon_16x16@2x.png"
sips -z 32 32     $input_filepath --out "${output_iconset_name}/icon_32x32.png"
sips -z 64 64     $input_filepath --out "${output_iconset_name}/icon_32x32@2x.png"
sips -z 64 64     $input_filepath --out "${output_iconset_name}/icon_64x64.png"
sips -z 128 128   $input_filepath --out "${output_iconset_name}/icon_64x64@2x.png"
sips -z 256 256   $input_filepath --out "${output_iconset_name}/icon_128x128@2x.png"
sips - 256 256    $input_filepath --out "${output_iconset_name}/icon_256x256.png"
sips -z 512 512   $input_filepath --out "${output_iconset_name}/icon_256x256@2x.png"
sips -z 512 512   $input_filepath --out "${output_iconset_name}/icon_512x512.png"
sips -z 1024 1024 $input_filepath --out "${output_iconset_name}/icon_512x512@2x.png"

iconutil -c icns $output_iconset_name
rm -R $output_iconset_name
