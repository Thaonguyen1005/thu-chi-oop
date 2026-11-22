# Thu chi cá nhân (Personal Income and Expense Management)

Đồ án môn **Lập trình hướng đối tượng** (PHY10609), Trường Đại học Khoa học Tự nhiên, ĐHQG-HCM. Nhóm 6.

Ứng dụng quản lý thu chi cá nhân viết bằng **C++ theo hướng đối tượng** (chạy trên console), kèm một **bản web minh họa** bằng HTML, CSS và JavaScript có cùng cấu trúc lớp.

## Chức năng

- **Quản lý người dùng:** đăng ký, đăng nhập, xem và sửa thông tin cá nhân, đổi mật khẩu.
- **Quản lý thu/chi:** thêm, xem, sửa, xóa giao dịch; phân loại theo danh mục, ngày, số tiền, ghi chú.
- **Ngân sách và cảnh báo:** đặt hạn mức chi tiêu theo tháng, cảnh báo khi chi từ 80% hạn mức và khi vượt hạn mức.
- **Thống kê:** theo ngày, theo tháng, theo danh mục (biểu đồ cột bằng ký tự `#`) và báo cáo tổng hợp.
- **Lưu trữ:** dữ liệu mỗi người dùng được lưu ra tệp văn bản và nạp lại khi chạy lần sau.

## Kiến thức OOP được áp dụng

| Nguyên lý | Cách áp dụng |
|---|---|
| Trừu tượng | `Transaction` là lớp trừu tượng với hàm thuần ảo `getType()` và `getCode()` |
| Kế thừa | `Income` và `Expense` kế thừa `Transaction` |
| Đa hình | `TransactionManager` lưu `unique_ptr<Transaction>`, `display()` gọi đúng `getType()` của từng loại giao dịch lúc chạy |
| Đóng gói | Thuộc tính `private` hoặc `protected`, truy cập qua getter và setter |

## Cấu trúc thư mục

```
.
├── main.cpp
├── App.h / App.cpp                           # giao diện menu, điều phối các module
├── User.h / User.cpp                         # User, UserManager
├── Transaction.h / Transaction.cpp           # Transaction (trừu tượng), Income, Expense
├── TransactionManager.h / .cpp               # quản lý giao dịch, lưu và đọc tệp
├── Budget.h                                  # hạn mức và cảnh báo
├── Statistics.h / Statistics.cpp             # thống kê, báo cáo
├── Date.h / Date.cpp                         # ngày tháng
├── Utils.h / Utils.cpp                       # hàm tiện ích nhập liệu, định dạng
├── web/index.html                            # bản web minh họa
└── docs/uml_class_diagram.mermaid            # sơ đồ lớp UML
```

## Cách biên dịch và chạy bản C++

Cần trình biên dịch `g++` hỗ trợ C++17 (ví dụ MinGW-w64 trên Windows). Biên dịch **tất cả** file `.cpp`:

```
g++ -std=c++17 main.cpp App.cpp Date.cpp Statistics.cpp Transaction.cpp TransactionManager.cpp User.cpp Utils.cpp -o thuchi
```

Chạy:

```
.\thuchi.exe      # Windows (PowerShell)
./thuchi          # Linux / macOS
```

Khi chạy, chương trình tạo `users.txt` và `<tên đăng nhập>_data.txt` trong thư mục hiện tại để lưu dữ liệu (các tệp này đã được loại khỏi Git bằng `.gitignore`).

## Bản web minh họa

Mở file `web/index.html` bằng trình duyệt là dùng được, không cần cài thêm gì. Dữ liệu lưu trong trình duyệt (localStorage) trên thiết bị đang dùng, không gửi lên máy chủ.

## Muốn học theo?

Tải code về máy để tự chạy và đọc:

```
git clone https://github.com/Thaonguyen1005/thu-chi-oop.git
```

Nếu có thắc mắc, bạn mở một **Issue** ở tab Issues của repo, nhóm sẽ trả lời khi có thể.

## Lưu ý

- Mật khẩu được lưu dạng văn bản thường, nên dự án chỉ phù hợp để **học tập và demo**, không dùng cho dữ liệu thật.
- Mã nguồn được chia sẻ cho mục đích học tập.

