### Importer::ReadFile预处理内参种类

`ReadFile(path, ${some_option_for_post_processing})`

第二个参数可以选填：

- `aiProcess_Triangulate`: 若模型不是全由三角形构成，需事先将所有图元转变为三角形
- `aiProcess_FlipUVs`: 翻转纹理y坐标
- `aiProcess_GenNormals`：如果模型不包含法向量的话，就为每个顶点创建法线。
- `aiProcess_SplitLargeMeshes`：将比较大的网格分割成更小的子网格，如果你的渲染有最大顶点数限制，只能渲染较小的网格，那么它会非常有用。
- `aiProcess_OptimizeMeshes`：和上个选项相反，它会将多个小网格拼接为一个大的网格，减少绘制调用从而进行优化。

在[此处](http://assimp.sourceforge.net/lib_html/postprocess_8h.html)找到所有的后处理选项。

