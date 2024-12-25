#define BLYNK_TEMPLATE_ID "TMPL63R4fif9o"
#define BLYNK_TEMPLATE_NAME "Robot Arm"
#define BLYNK_AUTH_TOKEN "qp9pQUhha4RN02D7a4KShBBrO0UtOD1Y"
#define DEFAULT_ANGLE 90

#include <ESP32Servo.h>
#include <WiFi.h>               // Thư viện WiFi cho ESP32
#include <BlynkSimpleEsp32.h>   // Thư viện Blynk cho ESP32

// Khai báo servo
Servo servo_A;    // Servo điều khiển Root_goc
Servo servo_B;    // Servo điều khiển Trai
Servo servo_Z;    // Servo điều khiển Phai
Servo servo_kep;  // Servo điều khiển Gripper_kep

// Định nghĩa chân servo
#define servoA  13
#define servoB  12
#define servoZ  14
#define servokep  27

// Thông tin WiFi và Blynk
char ssid[] = "viettel 345";             // Tên mạng WiFi
char pass[] = "12345679";         // Mật khẩu WiFi
double currentAngles[4] = {DEFAULT_ANGLE, DEFAULT_ANGLE, DEFAULT_ANGLE, DEFAULT_ANGLE};

void setup() {
  // Khởi tạo kết nối WiFi và Blynk
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Kiểm tra kết nối WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Đang kết nối WiFi...");
  }
  Serial.println("Kết nối WiFi thành công.");

  // Gắn các chân servo
  servo_A.attach(servoA);
  servo_B.attach(servoB);
  servo_Z.attach(servoZ);
  servo_kep.attach(servokep);

  // Đặt góc mặc định cho các servo
  servo_A.write(DEFAULT_ANGLE);
  servo_B.write(DEFAULT_ANGLE);
  servo_Z.write(DEFAULT_ANGLE);
  servo_kep.write(DEFAULT_ANGLE);

  // Gửi giá trị mặc định đến các sliders trên Blynk
  if (Blynk.connected()) {
    Blynk.virtualWrite(V1, DEFAULT_ANGLE);
    Blynk.virtualWrite(V2, DEFAULT_ANGLE);
    Blynk.virtualWrite(V3, DEFAULT_ANGLE);
    Blynk.virtualWrite(V4, DEFAULT_ANGLE);
    Serial.println("Góc mặc định được gửi đến Blynk.");
  }

  // Đồng bộ hóa giá trị từ dashboard
  Blynk.syncVirtual(V1);
  Blynk.syncVirtual(V2);
  Blynk.syncVirtual(V3);
  Blynk.syncVirtual(V4);

  Serial.println("Cánh tay robot sẵn sàng điều khiển qua Blynk.");
}

// Điều khiển Gripper_kep qua V1
BLYNK_WRITE(V1) {
  double angle = param.asDouble();
  servo_kep.write(angle);
  Serial.println("Gripper_kep góc: ");
  //hien thi gia tri goc voi 2 chu so thap phan
  Serial.println(angle, 2); 
}

// Điều khiển Root_goc qua V2
BLYNK_WRITE(V2) {
  double angle = param.asDouble();
  servo_A.write(angle);
  Serial.println(angle, 2); 
}

// Điều khiển Trai qua V3
BLYNK_WRITE(V3) {
  double angle = param.asDouble();
  servo_B.write(angle);
  Serial.println(angle, 2); 
}

// Điều khiển Phai qua V4
BLYNK_WRITE(V4) {
  double angle = param.asDouble();
  servo_Z.write(angle);
  Serial.println(angle, 2); 
}

void loop() {
  Blynk.run(); // Duy trì kết nối Blynk
}
