from collections import Counter

def count_and_encode_characters(file_path):
    # 读取文本文件内容
    with open(file_path, 'r', encoding='utf-8') as file:
        content = file.read()

    # 使用 Counter 统计字符出现次数
    char_counts = Counter(content)

    # 排序字符并分配编号
    sorted_chars = sorted(char_counts.keys())

    # 为数字和英文字母分配编号
    alnum_chars = [char for char in sorted_chars if char.isalnum()]
    alnum_to_id = {char: idx+1 for idx, char in enumerate(alnum_chars)}

    # 为汉字分配编号
    # 为汉字分配编号
    chinese_chars = [char for char in sorted_chars if '\u4e00' <= char <= '\u9fff']
    chinese_to_id = {char: idx + len(alnum_to_id) + 1 for idx, char in enumerate(chinese_chars)}

    # 打印每个字符和对应的ID
    print("Character IDs:")
    for char in sorted_chars:
        if char.isalnum():
            char_id = alnum_to_id[char]
        elif char == '\n':
            char_id = None  # 将换行符的ID设置为None
        else:
            char_id = chinese_to_id[char]
        print(f"Character '{char}' (ASCII: {ord(char)}, ID: {char_id})")

    # 创建新的文本内容
    new_content = ''
    for char in content:
        if char.isalnum():
            char_id = alnum_to_id[char]
        elif char == '\n':
            char_id = None  # 保留原始换行符
        else:
            char_id = chinese_to_id[char]
        if char_id is not None:
            new_content += f"\\x{char_id:02X}"
        else:
            new_content += char

    # 在每一行的末尾添加"\xFF"
    new_content = new_content.replace('\n', '\n')

    # 将新的文本内容写入新的文件
    new_file_path = "./a.txt"
    with open(new_file_path, 'w', encoding='utf-8') as new_file:
        new_file.write(new_content)

    print(f"New file with IDs and '\\xFF' at the end of each line generated: {new_file_path}")

if __name__ == "__main__":
    # 替换为你的文本文件路径
    file_path = "./name.txt"

    count_and_encode_characters(file_path)