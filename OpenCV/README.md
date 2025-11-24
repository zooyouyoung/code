# This is my OpenCV
## BASIC of BASIC
### 窗口和图片
+ `namedWindows("name" WINDOW_NORMAL/WINDOW_AUTOSIZE)`
+ `imshow("image name")`
+ `resizeWindow("name" ,width,height)`
+ `waitKey(0)`
+ `destroyAllWindows()`
+ `imread(path, flag)`: `flag`默认`IMAGE_COLOR`: 加载图片
+ `imwrite(filename, name , img)`: 保存图片
+ `clone()/copyTO()`
### 视频
+ `VideoCapture()`
+ `read()`
+ `release()`
+ `VideoWriter(filename, int fourcc, double fps, Size frameSize, bool isColor = true)`: 输出文件/多媒体文件格式/帧率/分辨率
+ `write()`
### 鼠标
+ `setMouseCallback(windowname, callback, userdata)`
+ `callback(event, x, y, flags, userdata)`: 鼠标操作/鼠标坐标x,y/鼠标键及组合键/
### TrackBar
+ `createTrackbar(Trackbar_name , windows_name, value, maxnum, callback, uerdata)`
+ `getTrackbarPos()`
## 色彩空间及基础操作(RGB/HSV/YUV)
### 色彩
+ RGB: 
+ HSV: Hue(色相/色彩)/Saturation(饱和度)/Value(明度)
<img src="./image/HSV.png" width="25%" height="25%">

+ HSL: Hue/Saturation/Ligthness
<img src="./image/HSV-HSL.png" width="40%" height="40%">

+ YUV: 用于视频
### 色彩空间转换
+ `zeros()`
+ `cvtColor(input_img, output_ret, flag)`: `COLOR_BGR2GRAY`/`COLOR_GRAY2BGR`/`COLOR_BGR2HSV`/`COLOR_HSV2BGR`;
+ `channels()`: 通道数
## 基本图形绘制
## 图像的运算
## 图形的进阶操作
## 滤波
## 形态学操作
## 轮廓
## 特征检测
### 


