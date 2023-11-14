def extract_text_between_single_quotes(input_file, output_file):
    with open(input_file, 'r', encoding='utf-8') as file:
        content = file.read()

    extracted_text = []
    inside_quotes = False
    current_text = ''

    for char in content:
        if char == "'":
            inside_quotes = not inside_quotes
            if not inside_quotes:
                extracted_text.append(current_text)
                current_text = ''
        elif inside_quotes:
            current_text += char

    # 将提取的文本写入新文件，不加换行
    with open(output_file, 'w', encoding='utf-8') as new_file:
        new_file.write(''.join(extracted_text))

    print(f"Extracted text between single quotes and saved to: {output_file}")



if __name__ == "__main__":
    # 替换为你的输入和输出文件路径
    input_file_path = "./ID.txt"
    output_file_path = "./ID_OUT.txt"

    extract_text_between_single_quotes(input_file_path, output_file_path)
