import os
import re

def MdImgPathCovert(md_root, raw_str, target_str):
    # 递归访问目录内所有 markdown 文件
    for root, dirs, files in os.walk(md_root):
        for file in files:
            if file.endswith('.md'):
                print('正在处理文件：', file)
                # 读取文件内容
                try:
                    with open(os.path.join(root, file), 'r', encoding='utf-8') as f:
                        content = f.read()
                except UnicodeDecodeError as e:    # 编码不是 utf-8的文件直接跳过即可
                    print(f"无法读取文件 {file}，编码错误：{e}")
                    continue
                # 替换图片路径
                content, count_md = re.subn(r'!\[.*?\]\((.*?)\)', lambda m: m.group(0).replace(m.group(1), m.group(1).replace(raw_str, target_str)), content)
                content, count_html = re.subn(r'<img.*?src="(.*?)".*?>', lambda m: m.group(0).replace(m.group(1), m.group(1).replace(raw_str, target_str)), content)
                print(f'替换了 {count_md + count_html} 处图片路径')
                # 将新的内容保存到原文件中
                with open(os.path.join(root, file), 'w', encoding='utf-8') as f:
                    f.write(content)
    
    print('图片路径替换完成！')
    
if __name__ == '__main__':
    MdImgPathCovert('G:\MyUniversity\CS-Note', r'G:/software3%20tools', r'G:/softwares')