## 投光物

- 定向光（平行光）
- 点光源
- 聚光

## 定向光(direct light)

当一个光源处于很远的地方时，来自光源的每条光线就会近似于互相平行。不论物体和/或者观察者的位置，看起来好像所有的光都来自于同一个方向。当我们使用一个假设光源处于**无限**远处的模型时，它就被称为定向光，因为它的所有光线都有着相同的方向，它与光源的位置是没有关系的。

![img](https://learnopengl-cn.github.io/img/02/05/light_casters_directional.png)

```c
struct Light {
	// vec3 position; // 使用定向光就不再需要了
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
```

> 我们一直将光的位置和位置向量定义为`vec3`，但一些人会喜欢将所有的向量都定义为`vec4`。当我们将位置向量定义为一个`vec4`时，很重要的一点是要将w分量设置为1.0，这样变换和投影才能正确应用。然而，当我们定义一个方向向量为`vec4`的时候，我们不想让位移有任何的效果（因为它仅仅代表的是方向），所以我们将w分量设置为0.0。
>
> 方向向量就会像这样来表示：`vec4(0.2f, 1.0f, 0.3f, 0.0f)`。这也可以作为一个快速检测光照类型的工具：你可以检测w分量是否等于1.0，来检测它是否是光的位置向量；w分量等于0.0，则它是光的方向向量，这样就能根据这个来调整光照计算了：
>
> ```
> if(lightVector.w == 0.0) // 注意浮点数据类型的误差
>   // 执行定向光照计算
> else if(lightVector.w == 1.0)
>   // 根据光源的位置做光照计算（与上一节一样）
> ```
>
> 你知道吗：这正是旧OpenGL（固定函数式）决定光源是定向光还是位置光源(Positional Light Source)的方法，并根据它来调整光照。

## 点光源

$$
\begin{equation} F_{att} = \frac{1.0}{K_c + K_l * d + K_q * d^2} \end{equation}
$$

在这里dd代表了片段距光源的距离。接下来为了计算衰减值，我们定义3个（可配置的）项：常数项KcKc、一次项KlKl和二次项KqKq。

- 常数项通常保持为1.0，它的主要作用是保证分母永远不会比1小，否则的话在某些距离上它反而会增加强度，这肯定不是我们想要的效果。
- 一次项会与距离值相乘，以线性的方式减少强度。
- 二次项会与距离的平方相乘，让光源以二次递减的方式减少强度。二次项在距离比较小的时候影响会比一次项小很多，但当距离值比较大的时候它就会比一次项更大了。

![img](https://learnopengl-cn.github.io/img/02/05/attenuation.png)

## 聚光

![img](https://learnopengl-cn.github.io/img/02/05/light_casters_spotlight_angles.png)

- `LightDir`：从片段指向光源的向量。
- `SpotDir`：聚光所指向的方向。
- `Phi`ϕ：指定了聚光半径的切光角。落在这个角度之外的物体都不会被这个聚光所照亮。
- `Theta`θ：LightDir向量和SpotDir向量之间的夹角。在聚光内部的话θ值应该比ϕ值小。

### 边缘模糊

$$
\begin{equation} I = \frac{\theta - \gamma}{\epsilon} \end{equation}
$$

这里ϵ(Epsilon)是内（ϕ）和外圆锥（γ）之间的余弦值差（ϵ=ϕ−γ）。最终的II值就是在当前片段聚光的强度。

