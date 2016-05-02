## GLSL的数据传递

数据在shader之间只能从上一个shader传到下一个shader。
上一个shader的`out type varname`，会传到下一个shader的`in type varname`中，其中`type`和`varname`只要匹配就行。

在vertex shader中，gl_Position是默认的输出数据。

此外，还有一种特别方便的从CPU向GPU传输参数的方法：即`uniform`类型。传输函数是一族函数：[glUniform](https://www.opengl.org/sdk/docs/man/html/glUniform.xhtml)

其中 **glUniform{1|2|3|4}{f|i|ui}** 是设置一个变量，如果是1，就是给uint、int、float这种类型赋值，后缀中的f、i、ui分别表示float、int和uint；如果是2，则是给vec2这种类型赋值，f、i、ui还是表示类型；3和4依次类推。**glUniform{1|2|3|4}{f|i|ui}v** 这一族跟以上类似，只是后面的`v`表示数组，所以这一族是给一个数组赋值，数组的类型由 *{1|2|3|4}{f|i|ui}* 指定。比如`1fv`就是给`float*`赋值，`2fv`则是给`vec2*`赋值，内部数值是float类型。


## 指定多个vertex attribute

当vertex属性变复杂后，可以重复调用glVertexAttribPointer和glEnableVertexAttribArray在不同的location设置多个属性。

因为vertices是通过一维数组传上去的，所以每次调用glVertexAttribPointer之前，都设置一下index，size和offset即可。

这样在vertex shader中就能通过指定location获取到不同的属性。


## fragment interpolation

在画多边形时，在fragment阶段，会给vertices之间的fragment像素的颜色进行插值处理。
