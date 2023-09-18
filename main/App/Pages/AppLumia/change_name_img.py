import os

lastname = "AppList"
replaceby = "AppLumia"

folder_path = "./"  # Đường dẫn đến thư mục chứa các tệp .c

for filename in os.listdir(folder_path):
    if filename.endswith(".cpp"):
        file_path = os.path.join(folder_path, filename)

        # Đọc nội dung tệp .cIICDiscovery
        with open(file_path, 'r',  encoding="utf8") as file:
            content = file.read()
            
        # Thay thế chuỗi "ui_font" thành "font" trong tên file
        new_filename = filename.replace(lastname, replaceby)

        # Thay thế "#include "../ui.h"" bằng "#ifdef LV_LVGL_H_INCLUDE_SIMPLE\n#include "lvgl.h"\n#else\n#include "lvgl.h"\n#endif"
        new_content = content.replace(lastname,
                                       replaceby)
        # new_content = content.replace('ui_img',
        #                                'img_src')

        # Ghi nội dung đã sửa vào tệp mới
        new_file_path = os.path.join(folder_path, new_filename)
        with open(new_file_path, 'w', encoding="utf8") as new_file:
            new_file.write(new_content)

    if filename.endswith(".h"):
        file_path = os.path.join(folder_path, filename)

        # Đọc nội dung tệp .c
        with open(file_path, 'r',  encoding="utf8") as file:
            content = file.read()

        # Thay thế chuỗi "ui_font" thành "font" trong tên file
        new_filename = filename.replace(lastname, replaceby)

        # Thay thế "#include "../ui.h"" bằng "#ifdef LV_LVGL_H_INCLUDE_SIMPLE\n#include "lvgl.h"\n#else\n#include "lvgl.h"\n#endif"
        new_content = content.replace(lastname,
                                       replaceby)
        # new_content = content.replace('ui_img',
        #                                'img_src')

        # Ghi nội dung đã sửa vào tệp mới
        new_file_path = os.path.join(folder_path, new_filename)
        with open(new_file_path, 'w', encoding="utf8") as new_file:
            new_file.write(new_content)
