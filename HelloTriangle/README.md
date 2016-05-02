## OpenGL pipeline

opengl pipeline总共有6个部分：

```
Vertex Data[] -->
    1)* Vertex Shader -->
    2)  Shape assemble -->
    3)* Geometry shader -->
    4)  Rasterization -->
    5)* Fragment Shader -->
    6)  Alpha test & blending
```

其中，Vertex Data定义了节点的所有属性，比如位置、颜色等；

Vertex shader的作用是把3d坐标转换为其他3d坐标(比如根据已有的vertex构造line或者triangle)，同时可以对vertex属性进行更多调整。

Shape assemble就是简单的形状组合

Geometry shader可以根据已有的形状构造出其他形状

Rasterizaiton把形状转换为像素，同时进行必要的裁剪，把超出范围的像素去掉。

> A fragment in OpenGL is all the data required for OpenGL to render a single pixel. fragment是一个像素的所有属性。


Fragment shader在像素上应用光照、阴影等高级效果。

Alpha test & blending 根据透明度、深度等信息确定最终要显示的像素。滤除那些不需要显示的数据。

实际情况中，我们只需要操作Vertex shader和fragment shader即可。Geometry shader也可以修改，但是一般使用默认。


## VBO

在cpu中创建出数据，输送到GPU。在OpenGL中，使用vbo作为传输对象。和OpenGL中的所有对象一样，它也必须有一个唯一引用id。这个id是我们创建的。

vbo中尽量包含所有数据，因为从cpu到gpu的传输是非常慢的。

VBO的类型是`GL_ARRAY_BUFFER`，OpenGL允许很多buffer type。一旦绑定了这个数组，那么后面所有对GL_ARRAY_BUFFER类型的操作，都是针对这个数组了。如果需要更换VBO，就需要重新绑定一个VBO。

## VAO

从VBO的使用特性上看，如果需要更换VBO，就需要重复指定各种配置，比较啰嗦。使用了VAO之后，这些配置就会保存在VAO相关的对象里，然后在game loop中，只需要重新绑定相关的VAO，就可以重绘图像了。不需要在重新配置一遍VBO。


## glVertexAttribPointer

函数签名如下：
```
void glVertexAttribPointer(
    GLuint index,
    GLint size,
    GLenum type,
    GLboolean normalized,
    GLsizei stride,
    const GLvoid * pointer);
```

它的作用是上传节点的属性信息，这些信息将存储在显卡中。在vertex shader中，我们通过指定location = index， 使OpenGL获得正确的属性信息，然后它才能对这些数据进行正确解读。

size是单个vertex的长度，默认为4，即`vec4`。

type则是数组中数据的类型，可以是 GL_BYTE, GL_UNSIGNED_BYTE, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, GL_UNSIGNED_INT,  GL_HALF_FLOAT, GL_FLOAT, GL_DOUBLE, GL_FIXED 等类型。

normalized则指定是否对数组进行归一化。也就是把-1和1**之外**的数据映射到这个范围内。一般选择false。

stride是单个vertex的字节长度。等于`size*sizeof(type)`，如果是紧凑型，即vertex中间不需要跳过某些数，可以直接指定为0 。此时OpenGL会自动计算stride。
