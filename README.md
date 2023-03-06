# MyShader

### 写在前面

之前写的那个render的重制版

使用vs写代码很重要的一点就是这里的相对路径的起始位置



## shader

对shader的一个封装

只需要读取两个shader的路径就可以得到一个可使用的shader

这里的vertex buffer可以在绑定之后解除绑定

但是EBO不行 	

## Texture

使用stb_image头文件来读取

封装在Texture类中



## window

对glfw window的一个抽象



## Camera

同样是一个封装，把变换封装在这个类中

考虑到之后输入的交互，同时在这里加入一个交互的系统

我们设置一个工具类，全部使用静态函数，其中包含给出目标位置和相机位置得到方向的函数

*注意，此时的model采用的还是单位矩阵，同时透视矩阵还是指定的一个矩阵*



## 模型

使用assimp导入































