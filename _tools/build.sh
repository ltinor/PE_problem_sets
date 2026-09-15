#!/bin/bash

SRC_DIR="source/_posts"
TEMPLATE_DIR="_template"

# 遍历所有 .md 文件
for file in "$SRC_DIR"/*.md; do
    # 提取文件名（去路径）
    filename=$(basename "$file")

    # 提取数字部分（去掉 .md）
    num=${filename%.md}

    # 判断是否是纯数字
    if ! [[ "$num" =~ ^[0-9]+$ ]]; then
        continue
    fi

    # 补齐三位数
    num_padded=$(printf "%03d" "$num")

    # 跳过 001~004
    if [[ "$num_padded" == "001" || "$num_padded" == "002" || "$num_padded" == "003" || "$num_padded" == "004" ]]; then
        echo "Skip existing folder $num_padded"
        continue
    fi

    # 目标目录
    target_dir="$num_padded"

    # 如果文件夹已存在，跳过
    if [ -d "$target_dir" ]; then
        echo "Folder $target_dir already exists, skip"
        continue
    fi

    echo "Creating $target_dir"

    # 创建目录
    mkdir -p "$target_dir"

    # 拷贝 md 文件（不覆盖）
    cp -n "$file" "$target_dir/"

    # 拷贝模板（递归，不覆盖）
    cp -Rn "$TEMPLATE_DIR"/. "$target_dir/"

done

echo "Done!"