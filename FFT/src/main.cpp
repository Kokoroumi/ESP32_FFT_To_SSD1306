//已验证，esp32_FFT，快速傅里叶变换实现音乐频谱
//移植小改 from https://github.com/xiaocainiao11111/esp32_FFT_music?tab=readme-ov-file

#include <Arduino.h>         //引入 Arduino 核心库，提供对 Arduino 平台的基础支持。
#include <ArduinoFFT.h>      //引入 ArduinoFFT 库，用于执行快速傅里叶变换（FFT）。
#include <Adafruit_SSD1306.h>//引入 Adafruit SSD1306 库，用于控制 OLED 显示屏（SSD1306 模块）。


#define samples 1024 //采样点数，2的N次幂（FFT用）设置采样点数为 1024，这个值必须是 2 的幂，因为 FFT 要求输入数据点数为 2 的幂次方。
#define halfsamples samples/2 //计算采样点的一半，因为 FFT 只使用前半部分数据来计算频谱。

#define SAMPLING_FREQUENCY 10000  //采样频率10khz

#define NumofCopy halfsamples*sizeof(double) //位宽 定义复制数据的字节数，halfsamples 是采样点的一半。
#define Interval 128/(halfsamples) //4
Adafruit_SSD1306 display(100);//创建一个 SSD1306 OLED 显示器对象，100 是显示器的宽度（像素数）。

float vReal[samples];     //声明一个大小为 samples 的数组，用来存储 FFT 的实部数据。
float vImag[samples];     //声明一个大小为 samples 的数组，用来存储 FFT 的虚部数据。
float  vTemp[halfsamples];//临时数组，用来保存频谱数据，避免修改原始的 vReal 数组

ArduinoFFT<float> myFFT(vReal, vImag, samples,SAMPLING_FREQUENCY); 

void setup() {
  // setP32();  //设置32分频,加快AD采样
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);//初始化 OLED 显示器，0x3C 是显示器的 I2C 地址。 似乎默认硬件I2C，参考引脚接线
  display.clearDisplay();       //清除显示器上的内容。
  display.setTextSize(1);       //设置显示文本的大小为 1。
  display.setTextColor(WHITE);  //设置显示文本的颜色为白色。
}

void loop() {
//  Serial.println("start:"+String(micros()));
  for(int i=0;i<samples;i++)
  {
    vReal[i]=analogRead(14)-512;                 //analogRead ( ADC采样输入引脚 )
    vImag[i] = 0.0;
  }
//  Serial.println("end:"+String(micros()));
  display.clearDisplay();//清空 OLED 显示屏。
  
  myFFT.windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);//对实部数据 vReal 应用汉明窗，减少频谱泄露现象。

  myFFT.compute(vReal, vImag, samples, FFT_FORWARD);  //执行 FFT 计算，结果会存储在 vReal 和 vImag 中。

  myFFT.complexToMagnitude(vReal, vImag, samples);  //计算复数数据的幅度，并将结果存储在 vReal 数组中。
  
  for(int i=0;i<halfsamples-2;i++)  //遍历一半的采样点（频谱数据）
  {
    /*在屏幕上绘制频谱数据的点，Interval 控制频谱点的间距，0.007 是幅度的缩放因子，+1 是为了避免绘制到屏幕的底部。*/
    display.drawPixel(i*Interval,vTemp[halfsamples-i-1]*0.007+1, WHITE); 

    /*在屏幕上绘制频谱数据的线条*/
    display.drawLine(i*Interval, 0, i*Interval,vReal[halfsamples-i-1]*0.007, WHITE); 
  
}

  display.display(); //推送
 
  memcpy(vTemp, vReal, NumofCopy);//将当前的频谱数据（存储在 vReal 中）复制到 vTemp 数组，以便在下一次绘制时使用。
  delay(2);  //改为128点时可以注释掉，防止刷新太慢
}