# 声明

**源码：**[xiaocainiao11111/esp32_FFT_music: 在esp32上用FFT库实现快速傅里叶变换显示声音频谱](https://github.com/xiaocainiao11111/esp32_FFT_music)

**源码：**[xiaocainiao11111/esp32_FFT_music: 在esp32上用FFT库实现快速傅里叶变换显示声音频谱](https://github.com/xiaocainiao11111/esp32_FFT_music)

**源码：**[xiaocainiao11111/esp32_FFT_music: 在esp32上用FFT库实现快速傅里叶变换显示声音频谱](https://github.com/xiaocainiao11111/esp32_FFT_music)

不清楚是 **软件版本不同** 还是用的 **板子不同**，源码并不能正常运行

硬件：**ESP-WROOM-32 / SSD1306 / MAX9814**

萌新第一次用git上传代码，写markdown，还在学习如何操作git

所以没有在作者的项目中添加branch，如有违反开源社区相关规定，**请务必联系删仓库**

# 修改

1、引入头文件 `` #include  <ArduinoFFT.h>``

2、创建FFT对象 ``ArduinoFFT<float> myFFT(vReal, vImag, samples,SAMPLING_FREQUENCY);``

3、adafruit创建的显示对象似乎默认使用硬件 **I2C**，接口请用 **SDA = 21，SCL = 22**

4、用大模型为每句代码加上注释``//FFT......``

# 演示

![示例图片](https://github.com/Kokoroumi/ESP32_FFT_To_SSD1306/tree/main/images/ShowSpectrum.jpg)

## Contact me

ygarry3909@gmail.com
