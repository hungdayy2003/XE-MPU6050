
# 🚗 Dự án: Xe Điều Khiển Từ Xa Bằng Cảm Biến Tay Nghiêng

## 🔍 Giới thiệu

Đây là dự án thiết kế và triển khai một hệ thống điều khiển xe từ xa sử dụng cảm biến nghiêng tay MPU6050. Khi người dùng nghiêng tay theo các hướng khác nhau, tín hiệu được xử lý và truyền không dây thông qua module NRF24L01 đến xe mô hình, từ đó điều khiển động cơ để xe di chuyển theo các hướng tương ứng.

## ⚙️ Hệ thống bao gồm 2 phần:

### 1. Bộ điều khiển (Transmitter)
- Arduino Nano
- MPU6050: Cảm biến đo gia tốc và con quay hồi chuyển để phát hiện độ nghiêng tay.
- NRF24L01: Gửi tín hiệu không dây đến xe.

### 2. Xe mô hình (Receiver)
- Arduino Nano
- NRF24L01: Nhận tín hiệu từ bộ điều khiển.
- Driver L298N: Điều khiển động cơ DC.
- Động cơ DC x4
- Nguồn pin Li-ion 7.4V

## 🔧 Nguyên lý hoạt động

1. Người dùng nghiêng tay (trên 20°) → MPU6050 thu dữ liệu gia tốc.
2. Arduino xử lý và mã hóa tín hiệu điều khiển.
3. NRF24L01 truyền lệnh đến xe mô hình.
4. Xe nhận lệnh và thực hiện: tiến, lùi, rẽ trái, rẽ phải, hoặc dừng lại.

## 🔋 Hệ thống nguồn

- Pin Li-ion 7.4V → LM2596 chuyển xuống 5V cho Arduino và L298N.
- LM1117-3.3 hạ áp từ 5V xuống 3.3V cho NRF24L01.

## 📦 Linh kiện chính

| Thiết bị         | Điện áp hoạt động | Dòng tiêu thụ |
|------------------|-------------------|----------------|
| Arduino Nano     | 5V                | ~50mA          |
| MPU6050          | 3.3V / 5V         | ~3.5mA         |
| NRF24L01         | 3.3V              | ~11–13mA       |
| L298N            | 5V logic / 6-9V motor | ~600mA    |
| Động cơ DC x4    | 6–9V              | ~140mA mỗi cái |

## 🛠️ Chức năng

- Điều khiển hướng: tiến, lùi, trái, phải.
- Tự dừng khi mất kết nối.
- Tiết kiệm năng lượng.
- Phản hồi nhanh và ổn định.

