//已验证，esp32_FFT，快速傅里叶变换实现音乐频谱

//移植小改 from https://github.com/xiaocainiao11111/esp32_FFT_music?tab=readme-ov-file

#include <Arduino.h>
#include <ArduinoFFT.h>
#include <Adafruit_SSD1306.h>


#define samples 1024 //采样点数，2的N次幂（FFT用）
#define halfsamples samples/2 //32

#define SAMPLING_FREQUENCY 10000  //采样频率10khz

#define NumofCopy halfsamples*sizeof(double) //位宽
#define Interval 128/(halfsamples) //4
Adafruit_SSD1306 display(100);

float vReal[samples];
float vImag[samples];
float  vTemp[halfsamples];

ArduinoFFT<float> myFFT(vReal, vImag, samples,SAMPLING_FREQUENCY); 

void setup() {
  // setP32();  //设置32分频,加快AD采样
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop() {
//  Serial.println("start:"+String(micros()));
  for(int i=0;i<samples;i++)
  {
    vReal[i]=analogRead(14)-512;                 //analogRead ( ADC采样输入引脚 )
    vImag[i] = 0.0;
  }
//  Serial.println("end:"+String(micros()));
  display.clearDisplay();
  
  myFFT.windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);//加窗，汉宁窗
  myFFT.compute(vReal, vImag, samples, FFT_FORWARD);  //计算fft
  myFFT.complexToMagnitude(vReal, vImag, samples);  //计算幅度
  
  for(int i=0;i<halfsamples-2;i++)
  {
    display.drawPixel(i*Interval,vTemp[halfsamples-i-1]*0.007+1, WHITE); //点
    display.drawLine(i*Interval, 0, i*Interval,vReal[halfsamples-i-1]*0.007, WHITE); //线
  
}

  display.display(); //推送
 
  memcpy(vTemp, vReal, NumofCopy);
  delay(2);  //改为128点时可以注释掉，防止刷新太慢
}
 