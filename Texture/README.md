## MipMap的意义

当图像距离观察者较远时，如果还给物体渲染精度很高的纹理，是性能上的极大浪费，同时还会导致失真。为此GL提出了MipMap的概念。它只在变小的物体上有效（即GL_TEXTURE_MIN_FILTER)。MipMap就是把原纹理图像进行了2分采样形成的很多层金字塔。在精度较低的物体上，会使用金字塔较高层的纹理。

不同选项的含义如下：

- GL_NEAREST_MIPMAP_NEAREST: takes the nearest mipmap to match the pixel size and uses nearest neighbor interpolation for texture sampling. 选出mipmap上最近的层，在该层上进行nearest采样。
- GL_LINEAR_MIPMAP_NEAREST: takes the nearest mipmap level and samples using linear interpolation. 选出mipmap上最近的层，在该层上进行线性采样。
- GL_NEAREST_MIPMAP_LINEAR: linearly interpolates between the two mipmaps that most closely match the size of a pixel and samples via nearest neighbor interpolation. 将相邻mipmap的2层进行线性融合，获得新层；在该层上进行最近采样。
- GL_LINEAR_MIPMAP_LINEAR: linearly interpolates between the two closest mipmaps and samples the texture via linear interpolation.  将相邻mipmap的2层进行线性融合，获得新层；在该层上进行线性采样。

## 纹理坐标计算

因为加载进的纹理图像中，是以左上角为原点。而OpenGL则是把屏幕的左下角作为原点，所以渲染后的图像中，纹理可能是上下颠倒的。可以在给vbo赋值前，就把vertices的纹理坐标进行处理：`y = 1 - y0`，或者在fragment shader中如下处理：
```
texture(ourTexture, vec2(TexCoord.x, 1-TexCoord.y))
```


## glActiveTexture的使用

在使用texture unit时，需要先通过glActiveTexture指定在哪个Unit上生效，后续包括glBindTexture的操作都会在改Unit上起作用。
