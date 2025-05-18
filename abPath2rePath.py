# 将原来笔记中的 绝对路径图片复制到笔记根目录 assets 下，并修改为相对路径
import os
import re
import shutil
import chardet
from pathlib import Path

# def convert_encoding(filepath):
#     """ 检测并转换文件编码为UTF-8 """
#     try:
#         with open(filepath, 'rb') as f:
#             raw = f.read()
#             encoding = chardet.detect(raw)['encoding']
            
#         if not encoding or encoding.lower() == 'utf-8':
#             print(f"  → 文件已是UTF-8编码: {filepath}")
#             return False
        
#         content = raw.decode(encoding, errors='replace')
#         with open(filepath, 'w', encoding='utf-8') as f:
#             f.write(content)
#         print(f"  → 文件编码转换为UTF-8: {filepath}")
#         return True
#     except Exception as e:
#         print(f"编码转换失败: {filepath} - {str(e)}")
#         return False


def migrate_images(md_root, asset_root='assets'):
    """ 核心迁移逻辑 """
    md_root = Path(md_root).resolve()
    asset_root = md_root / asset_root
    
    # 遍历所有Markdown文件
    for md_file in md_root.glob('**/*.md'):
        print(f"\n处理文件中: {md_file.relative_to(md_root)}")
        
        # 编码转换
        # convert_encoding(md_file)
            
        with open(md_file, 'r', encoding='utf-8') as f:
            content = f.read()
            
        # 匹配所有图片引用
        img_pattern = re.compile(
            r'!\[(?P<alt>.*?)\]\((?P<path>.*?)\)'  # Markdown语法
            r'|<img.*?src="(?P<img_path>.*?)".*?>',  # HTML语法
            re.IGNORECASE  # 模式忽略大小写
        )
        
        # 路径替换
        new_content = content
        for match in img_pattern.finditer(content):
            img_path = match.group('path') or match.group('img_path')
            original_path = Path(img_path.strip())
            
            # 处理绝对路径
            if original_path.is_absolute():
                print(f"  发现绝对路径: {original_path}")
                
                # 构建新的存储路径
                if md_root in original_path.parents:
                    # 项目内图片：保留相对目录结构
                    rel_path = original_path.relative_to(md_root)
                    new_path = asset_root / rel_path
                else:
                    # 外部图片：统一存储在assets/external
                    rel_path = Path('external') / original_path.drive.replace(':', '_drive') / original_path.relative_to(original_path.anchor)
                    new_path = asset_root / rel_path
                
                # 创建目录并复制图片
                new_path.parent.mkdir(parents=True, exist_ok=True)
                if not new_path.exists():
                    try:
                        shutil.copy(original_path, new_path)
                        print(f"    已复制图片到: {new_path.relative_to(md_root)}")
                    except Exception as e:
                        print(f"    ! 图片复制失败: {original_path} → {e}")
                        continue
                
                # 计算相对路径
                relative_to_md = os.path.relpath(new_path, md_file.parent).replace('\\', '/')
                
                # 替换路径
                if match.group('path'):
                    replacement = f'![{match.group("alt")}]({relative_to_md})'
                else:
                    replacement = f'<img src="{relative_to_md}" alt="{match.group("alt")}">'
                
                new_content = new_content.replace(match.group(), replacement)
        
        # 写回文件
        if new_content != content:
            with open(md_file, 'w', encoding='utf-8') as f:
                f.write(new_content)
            print(f"  → 已更新{content.count('![')}处图片路径")

if __name__ == '__main__':
    # 配置参数（根据实际情况修改）
    NOTES_ROOT = r"G:\MyUniversity\CS-Note"  # 修改为你的实际路径
    ASSET_DIR = "assets"  # 统一资源目录名
    
    migrate_images(NOTES_ROOT, ASSET_DIR)
    print("\n迁移完成！所有资源已集中存储在:", Path(NOTES_ROOT) / ASSET_DIR)
                