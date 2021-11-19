# Hello, OpenGL!

## 简介

由于疫情，[2021-2022-1] 的**计算机图形学**课程（课程代号：*B0301312C* ）采取了线上教学模式。

鉴于这门课程的内容有一定难度，我已将课程回放保存并上传 **bilibili 弹幕网**（[BV1ib4y1Y74J](https://b23.tv/sBmpt8E)）。此外，根据上课内容，我上传了课程的代码内容（[toulzx/NJUPT-CG-OpenGL](https://github.com/toulzx/NJUPT-CG-OpenGL)）供大家参考。


## 如何食用

### 项目结构

- 文件夹 `Source`
  - 文件夹 `HelloCG`: 此项目文件夹  
  - 一些文件 `.PDFs`: 功能库配置教程
- 一些文件 `.ZIPs`: 功能库

 
### 查阅历次代码及差异

我按照课程教学顺序，将历次课程代码提交到此仓库下。

`test_4` 分支的[最新一次 commit 内容](https://github.com/toulzx/NJUPT-CG-OpenGL/commit/65f6459491966bc9d3d7b68b8fe9ffbe4d46ba11)是本课程的最后一次作业（第 4 次作业），它是基于课程的代码内容，由于此分支包含了所有课程的代码内容的 commits，因此我将此分支设置为默认分支。

此外，此前另外 3 次作业的代码不在课程教学内容中，因此我创建了 `test_3` 、`test_2` 、`test_1` 分支，他们是从默认分支的某次课程内容延伸出去的。

你可以点击仓库主页的 [`commits`](https://github.com/toulzx/NJUPT-CG-OpenGL/commits/test_4)，这可以阅览历次 commit 的信息， 当你点击 [某次 commit 的标题](https://github.com/toulzx/NJUPT-CG-OpenGL/commit/ebd13441c8ac2de793d20d961ef16babb355a12a) 时，你可查看和上一次commit 内容的差异，我认为这可能会方便大家查看历次课程代码的差异。

⚠注意：这样的做法是我的首次尝试，有些 commits 的差异由于失误并不能正确预览，我会在出现这种情况的 `commit 差异` 页面提供批注。当然，你完全可以不参考 commit 差异，你仍然可以下载运行可使用的的历次课程代码（见下）。



## 历次课程代码

- [**Week2-1** 初始环境配置和 Demo 测试](https://github.com/toulzx/NJUPT-CG-OpenGL/tree/20743bb4fec727e91931253ce48461f96af195f7)

- [**Week2-1** 梳理、重写 Demo](https://github.com/toulzx/NJUPT-CG-OpenGL/tree/dc70d77b6df79eb13c22d53ca1cc291f37653c03)

- [**Week2-2** & **Week3-1** 使用着色器绘制一个三角形](https://github.com/toulzx/NJUPT-CG-OpenGL/tree/cf9c8fa6320f602795f934063711457f4182518b)

- [**Week3-2** 优化代码结构，将着色器部分代码独立存放](https://github.com/toulzx/NJUPT-CG-OpenGL/tree/83873486f750f92217054f8fa3e94f2f2bc60d19)

- [**Week4-1** 为三角形各个顶点设置不同的颜色](https://github.com/toulzx/NJUPT-CG-OpenGL/tree/e804677964a41f685bb35473bc51e9c2b435ba55)

- [**Week4-1** 使用两个三角形拼成正方型](https://github.com/toulzx/NJUPT-CG-OpenGL/tree/781216ef3c6c7f803eaadc9b6bafa9e62a3ee342)

- [**Week4-1** **Exercise1** 实现矩形颜色交替变换](https://github.com/toulzx/NJUPT-CG-OpenGL/tree/473bd6032d7f0cf8abcfe6ecb5b58d93202d88c3)

- [**Week5-1** 改用点和连接信息绘制正方形](https://github.com/toulzx/NJUPT-CG-OpenGL/tree/75e411d6e863007e5a90a2cb76410e4045b97491)

- [**Week5-1** 清理代码，准备学习纹理部分](https://github.com/toulzx/NJUPT-CG-OpenGL/tree/6ec1a01707344ef61b6bd6de9fe1f65c45a2b8b1)

- [**Week5-1** 配置SOIL2](https://github.com/toulzx/NJUPT-CG-OpenGL/tree/d84729346f00a6871e77d82a9ef770998fdef687)

- [**Week5-2** 尝试纹理贴图](https://github.com/toulzx/NJUPT-CG-OpenGL/tree/da3f7eb056b194211ea83619d49c0c9062bf30aa)

- [**Week5-2** **Exercise2** 使纹理单方向渐变移动](https://github.com/toulzx/NJUPT-CG-OpenGL/tree/4294601f92242a5cd2ed4f625f0827219d60f455)

- [**Week6-1** 配置 GLM 库；清理代码，去除纹理部分，back to Week4-1](https://github.com/toulzx/NJUPT-CG-OpenGL/tree/453b96c88eb3ec4112154cb1507f195ed21b4abf)

- [**Week7-1** 正方体的缩放、旋转、平移](https://github.com/toulzx/NJUPT-CG-OpenGL/tree/dbba0ac799630798118515fbed18781e78eaab4a)

- [**Week7-2**通过透视投影生成真正的正方体](https://github.com/toulzx/NJUPT-CG-OpenGL/tree/f09f6f81aa9948fef253d12f108026a46ce56602)

- [**Week7-2** **Exercise3** 地月模型旋转（近似圆轨道 + 23.5°）](https://github.com/toulzx/NJUPT-CG-OpenGL/tree/337b9d6d357fb4ffbe7f7ccdc20f767348d84bcf)

- [**Week8-1** 实现摄像机（即观察者）视角的移动（w/a/s/d）](https://github.com/toulzx/NJUPT-CG-OpenGL/tree/8c280566820e7289abf5d4a7a9b1089bac89033d)

- [**Week8-1** 实现摄像机视角移动的鼠标和滚轮事件](https://github.com/toulzx/NJUPT-CG-OpenGL/tree/1f0d24d7eb2a9c212b81fb968083a1463ba9cf46)

- [**Week8-2** & **Week8-3** 实现旋转光源照射物体的效果](https://github.com/toulzx/NJUPT-CG-OpenGL/tree/ebd13441c8ac2de793d20d961ef16babb355a12a)

- [**Week8-3** **Exercise4** & **fix** 实现控制物体的（↑/↓/←/→）移动 && 修复 x 轴光照位置的错误](https://github.com/toulzx/NJUPT-CG-OpenGL/tree/65f6459491966bc9d3d7b68b8fe9ffbe4d46ba11)


### 下载

你可以通过 `Git` 直接将项目 clone 到本地，然后借助编辑器内置的 Git 管理工具即可轻松切换历次版本。

如果你看不懂上面这一行我在说什么，你可以拷贝链接到 [DownGit](https://minhaskamal.github.io/DownGit/#/home) 下载。

## 友情链接

### 关于教程

我推荐你学习这篇教程：[**LearnOpenGL**](https://learnopengl-cn.github.io)，你会发现此课程（特指 2021-2022 学年第 1 学期的线上课程）的授课思路参考了这份教程。


### 课程笔记 & 代码

- [【CSDN】OpenGL初学者入门——学习指南](https://blog.csdn.net/Wang_Dou_Dou_/article/details/121240714)
- [【CSDN】南邮计算机图形学实验报告](https://blog.csdn.net/qq_45668594/category_11435461.html)
- [【GitHub】 GodWuzZ/Graphics](https://github.com/GodWuzZ/Graphics)
- [【yuque】tou/NJUPT-CG-OpenGL](https://www.yuque.com/toulzx/website-sync/njupt-cg-opengl#bt58x)


## 一点建议

**不要未经思考直接 copy 代码。**

首先，这对你学习这门课程没有好处；其次，老师检查作业的时候，会查看你的代码并询问细节。


## 更多

我已经将本课程的个人笔记上传到了语雀和个人博客，你可以在[**这里**](https://toulzx.github.io/)找到最新的文档。