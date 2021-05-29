# 说明
数字图像处理实验<br>
## 环境
opencv 4.5.0: [opencv](https://opencv.org/releases/) <br>
windosw 10家庭版<br>
VS2019社区版: [Visual Studio 2019](https://visualstudio.microsoft.com/zh-hans/vs/)<br>
C++ :[c++](https://en.cppreference.com/w/)<br>
第三方库链接方式: [静态链接](https://www.bilibili.com/video/BV1vp4y1W7ze?t=975)<br>

## 使用
使用:[视频演示](https://www.bilibili.com/video/BV1LB4y1u7UQ/)
1.打开vs2019<br>
2.在开始使用一栏中选择克隆存储库<br>
3.输入存储库位置<br>
https://github.com/hauqu/static_opencv450_lib.git<br>
本存储库的github地址<br>
任选一个路径保存（尽量不含中文）<br>
4.保持联网，克隆完成<br>
5.因为本项目采用静态链接，不需要额外配置opencv 可以直接运行<br>
6.按下F5 或本地Windos调试器（debug x64）不支持x86，需要的自己配<br>
	6.1若提示错误，找不到dll 将 dependencies/opencv/bin.zip 解压到
	static_opencv450_lib\x64\Debug(github不支持超过100mb的文件，所以压缩了一下)
	<br>
7.测试用例运行成功，图片显示<br>
8.在解决方案资源管理器选择显示全部文件，右键文件选择将任意文件包含或者排除项目中
使得每此只有一个cpp类型文件包含在项目中，分别进行实验1234.<br>
例如右键 test.cpp 选择排除文件(不是删除)，再右键将实验1.cpp包含到项目中，双击打开该文件<br>
按F5运行，显示实验1

## 时间 
2021-5-29
孙乐乐



