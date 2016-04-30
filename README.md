## 目的

学习OpenGL的笔记，主要来自于 [learnopengl网站](http://learnopengl.com/)

我是Mac， 使用Xcode，而learnopengl上则使用vs，二者还是有很多差异的

## CMakeLists.txt

为了方便构建项目，我使用cmake来创建xcode。这样就不需要每次都手动添加很多库了。写得比较简单，不过够我在Mac上用了。

记得每次更改一下 `project(YourProjectName)` 中的YourProjectName

## Xcode 使用笔记

#### 切换到Release模式

Product --> Scheme --> Edit scheme... 切换到release

然后cmd+b就会在`Build Products Path`(一般就是当前项目)下生成一个Release目录。里面就是可执行文件
