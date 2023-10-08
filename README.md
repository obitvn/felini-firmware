## Minh Họa

![](https://cdn.hackaday.io/images/681491695708719074.jpg)

> Dự án này là một thiết bị multi tool nhỏ gọn tích hợp khung hình ảnh LVGL, khung MVC, khung tin nhắn, và hỗ trợ nhiều loại giao tiếp phổ biến như  UART, SPI, IIC....
>
> Dự án đang trong giai đoạn sơ khai, trong tương lai nó sẽ được sử dụng như một bộ điều khiển thông minh, hoặc như một công cụ đa năng để giải quyết nhiều vấn đề trong thế giới điện tử và lập trình nhúng

Felini - là một thiết bị nhỏ gọn dành cho các chuyên gia cũng như những người đam mê điện tử. Giống như một con dao quân đội Thụy Sĩ, Felini được thiết kế để thay thế hiệu quả nhiều công cụ phổ biến trong lĩnh vực điện tử.
Giao diện trực quan để chuyển đổi giữa các công cụ tương tự như các ứng dụng trên điện thoại thông minh, không có công tắc bật tắt, không có menu sử dụng các nút phức tạp và khó hiểu. Felini là sự khởi đầu của một cuộc cách mạng về dụng cụ đa năng và máy đo đa năng.

## 1. Xây dựng dự án

Dự án được xây dựng dựa trên esp-idf 5.1 và khung lvgl 8.x và vscode. Để tiến hành build, sử dụng file cấu hình vscode "felini_vscode" để tải đầy đủ các phụ thuộc, ngoài ra, MinGW cũng được yêu cầu.

## 2. Phần mềm

Các tính năng trên felini hoạt động độc lập dưới dạng các ứng dụng riêng biệt, được phân tách bởi mô hình MVC và tách biệt phần cứng qua lớp phần cứng trừ tượng HAL.
Thông tin chi tiết về dự án có trên [Hackaday](https://hackaday.io/project/192130-felini-revolutionary-pocket-sized-electronic-lab)

## 3. Sự nhìn nhận

> Cảm ơn @[FASTSHIFT](https://github.com/FASTSHIFT/X-TRACK/commits?author=FASTSHIFT) về khung quản lý trang LVGL.

> Cảm ơn [@ReclaimerLabs ](https://github.com/ReclaimerLabs) về khung giao tiếp USB PD trên FUSB302.

> Cảm ơn [@fbiego](https://github.com/fbiego) về ý tưởng triển khai giao diện Lumia trên ESP32.\
>
> Cảm ơn [@lovyan03](https://github.com/lovyan03) về trình điều khiển màn hình.
>
> 
