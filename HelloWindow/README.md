## 重点

#### GLEW include Header

GLEW的功能就是根据不同的平台进行适配，所以必须在GLFW之前incldue GLEW，这样GLFW才能包含到正确的gl.h等头文件

而且，如果使用GLEW的static lib，如linux的libglew.a文件，需要在include前面加

`#define GLEW_STATIC`

如果是引用动态库，则不需要。

#### 初始化和配置glfw

使用
[glfwWindowHint](http://www.glfw.org/docs/latest/group__window.html#ga4fd9e504bb937e79588a0ffdca9f620b)
配置各种参数。尤其需要注意Mac平台：[来源](http://www.glfw.org/docs/latest/compat.html#compat_osx)

> Support for OpenGL 3.2 and above was introduced with OS X 10.7 and even then only forward-compatible, core profile contexts are supported. Support for OpenGL 4.1 was introduced with OS X 10.9, also limited to forward-compatible, core profile contexts. There is also still no mechanism for requesting debug contexts. Versions of Mac OS X earlier than 10.7 support at most OpenGL version 2.1.

> Because of this, on OS X 10.7 and later, the GLFW_CONTEXT_VERSION_MAJOR and GLFW_CONTEXT_VERSION_MINOR hints will cause glfwCreateWindow to fail if given version 3.0 or 3.1, the GLFW_OPENGL_FORWARD_COMPAT hint must be set to GL_TRUE and theGLFW_OPENGL_PROFILE hint must be set to GLFW_OPENGL_CORE_PROFILE when creating OpenGL 3.2 and later contexts and theGLFW_OPENGL_DEBUG_CONTEXT hint is ignored.

也就是说，在Mac上必须指定这2个设置：

`
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
`

还有，必须按照你显卡支持的OpenGL版本设置`GLFW_CONTEXT_VERSION_MAJOR`和`GLFW_CONTEXT_VERSION_MINOR`，比如我的版本是4.1，那么前者就应该设置为4，后者为1。


#### Error callback

原文中没有提到如何检测错误，我在stackoverflow上找到一个简单方法：

```
  void glfwErrorCallback(int error, const char *description) {
      fprintf(stderr, "GLFW error [%d] : %s\n",
                  error ,
                  description
              );
  }

  glfwSetErrorCallback(glfwErrorCallback);
```
