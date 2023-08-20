def add_comment_after_empty_line(input_file, output_file):
    with open(input_file, 'r') as infile, open(output_file, 'w') as outfile:
        previous_line_empty = False

        for line in infile:
            # 空行を判定する（改行文字のみの行も空行として扱う）
            is_empty_line = len(line.strip()) == 0

            if previous_line_empty:
                # 空行の次の行の最初に '#' を追加
                line = '#' + line

            # 出力ファイルに書き込み
            outfile.write(line)

            # previous_line_emptyを更新
            previous_line_empty = is_empty_line

if __name__ == "__main__":
    input_filename = "railmap.txt"  # 入力ファイル名を適宜変更してください
    output_filename = "railmap2.txt"  # 出力ファイル名を適宜変更してください
    add_comment_after_empty_line(input_filename, output_filename)
