#include <Wire.h>
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h> 
#include "esp_camera.h" 
#include <Base64.h> 
#include <HTTPClient.h> 
#include <ArduinoJson.h> 

//WiFi Credentials 
const char* ssid = "Airtel_madh_4268";
const char* password = "air95767"; 

//API Key 
const String apiKey = "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";


String Question = "Write a short poem about the image";


#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); 


#define PWDN_GPIO_NUM    32
#define RESET_GPIO_NUM   -1
#define XCLK_GPIO_NUM     0
#define SIOD_GPIO_NUM    26
#define SIOC_GPIO_NUM    27
#define Y9_GPIO_NUM      35
#define Y8_GPIO_NUM      34
#define Y7_GPIO_NUM      39
#define Y6_GPIO_NUM      36
#define Y5_GPIO_NUM      21
#define Y4_GPIO_NUM      19
#define Y3_GPIO_NUM      18
#define Y2_GPIO_NUM       5
#define VSYNC_GPIO_NUM   25
#define HREF_GPIO_NUM    23
#define PCLK_GPIO_NUM    22

void displa

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  Wire.begin(14,15); //SDA, SCL 
  if(!display.begin(SSD1306_PAGEADDR, 0x3C)){
    Serial.println(F("SSD1306 allocation failed"));
    while (1); 
    for (;;);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE); 

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_RGB565;


  config.frame_size = FRAMESIZE_QQVGA;  // 160x120
  config.jpeg_quality = 10;
  config.fb_count = 1;

  esp_err_t err = esp_camera_init(&config); 
  if(err!= ESP_OK){
    Serial.printf("Camera init failed with error 0x%x",err); 
    return; 
  }


  captureAndPrintBase64Img();
}

void captureAndPrintBase64Img(){
  camera_fb_t* fb = esp_camera_fb_get();
  if(!fb){
    Serial.println("Camera Capture Failed");
    return;
  } 

  //Encoding image buffer to Base64
  String base64Image = base64::encode((const uint8_t*)fb->buf, fb->len);

  //Print the Base64 string to the serial monitor 
  Serial.println("\n[Base64 Encoded Image]:");
  Serial.println(base64Image);

  esp_camera_fb_return(fb); //Return the frame buffer

}

void loop() {
  // put your main code here, to run repeatedly:

}
