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

