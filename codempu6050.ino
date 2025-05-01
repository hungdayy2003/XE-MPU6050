#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
RF24 radio(9, 10); // CE, CSN
const uint64_t pipe = 0xE8E8F0F0E1LL;

int msg[1]; // Mảng chứa dữ liệu gửi đi

void setup() {
    Serial.begin(9600);
    Wire.begin();

    // Khởi động MPU6050
    mpu.initialize();
    if (!mpu.testConnection()) {
        Serial.println("MPU6050 không kết nối! Kiểm tra dây.");
        while (1); // Dừng nếu không tìm thấy MPU6050
    } else {
        Serial.println("MPU6050 kết nối thành công!");
    }

    // Khởi động NRF24L01
    if (!radio.begin()) {
        Serial.println("NRF24L01 không kết nối! Kiểm tra dây.");
        while (1); // Dừng nếu NRF24L01 không hoạt động
    } else {
        Serial.println("NRF24L01 kết nối thành công!");
    }

    radio.openWritingPipe(pipe);
    radio.setPALevel(RF24_PA_MIN);
    radio.setChannel(80);
    radio.setDataRate(RF24_250KBPS);
    radio.stopListening(); // Chế độ phát

    radio.printDetails(); // Hiển thị thông tin cấu hình NRF24L01
}

void loop() {
    int16_t ax, ay, az, gx, gy, gz;
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    float angleX = ax / 16384.0 * 90; // Chuyển đổi thô (xấp xỉ)
    float angleY = ay / 16384.0 * 90;

    // Xử lý góc nghiêng để gửi lệnh điều khiển
    if (angleY > 20) {
        msg[0] = 1; // Tiến
    } else if (angleY < -20) {
        msg[0] = 2; // Lùi
    } else if (angleX > 20) {
        msg[0] = 3; // Rẽ trái
    } else if (angleX < -20) {
        msg[0] = 4; // Rẽ phải
    } else {
        msg[0] = 5; // Dừng
    }

    // Gửi dữ liệu và kiểm tra trạng thái gửi
    bool success = radio.write(msg, sizeof(msg));
    if (success) {
        Serial.print("Đã gửi: ");
    } else {
        Serial.print("Gửi thất bại! ");
    }
    Serial.println(msg[0]);

    delay(500);
}
