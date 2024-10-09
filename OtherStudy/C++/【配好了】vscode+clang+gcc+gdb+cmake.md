[[ vscode + clangd + gcc + gdb + cmake] 一文带你构造C/C++开发环境 #支持嵌入式开发 #超详细 #小白_vscode_ElderlyPeng-开放原子开发者工作坊 (csdn.net)](https://openatomworkshop.csdn.net/66470558b12a9d168eb6ef88.html?dp_token=eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpZCI6MTU4NzMxOSwiZXhwIjoxNzI3MjY2NTE3LCJpYXQiOjE3MjY2NjE3MTcsInVzZXJuYW1lIjoibTBfNzM1NTM0MTEifQ.UZjVDvc3gmLZiejC2102uvaeJDSNLGZ1AU66Czr96A0&spm=1001.2101.3001.6650.3&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7Eactivity-3-134235159-blog-115601111.235%5Ev43%5Epc_blog_bottom_relevance_base8&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromBaidu%7Eactivity-3-134235159-blog-115601111.235%5Ev43%5Epc_blog_bottom_relevance_base8&utm_relevant_index=6)
![[CQUStudy/OtherStudy/C++/image/Pasted image 20240918202700.png]] 

1. github上下载的源码只有一堆.c/.h文件，不是vs工程，如何在源码上进行构建开发？
2. 发布开源工程，要告诉别人怎么使用我的库好麻烦，如果编译等过程可以用命令行写成脚本，整个过程自动完成就好了
## GCC编译器
GCC 是 GNU 开发的C语言编译器，开发C语言必不可少的工具。而 windows 平台下的 GCC 叫 MinGW，因此我们需要安装这个叫 **MinGW** 的软件

`gcc -o main.exe main.c` ，这个命令的意思是调用 gcc 编译器，将 main.c 编译成可执行文件 main.exe
最终目的是在 main.c 所在目录生成一个 **.vscode 文件夹** 里面有 **launch.json** 文件。这个文件会告诉 c/c++ 插件，要去哪里找到 gdb 程序、要用 gdb 去调试哪个 .exe 文件
“name”, “type”, “request” 是必须有的, “type”: “cppdbg” 代表使用 c/c++ 插件进行调试  
**“program” 最重要**，表示需要调试程序的路径，即 main.exe 的路径，“cwd” 用于查找依赖项和其他文件的当前工作目录  
“MIMode”, “miDebuggerPath” 提供了gdb的路径 **（这个路径要根据你自己安装 MinGW 的路径填写）**

在命令行执行 `mingw32-make.exe` (linux执行 `make`)，这个 make 程序会在当前命令行路径下找到 Makefile 文件，执行Makefile里预设好的命令。这里运行了第2行的命令 “gcc -o main main.c
1. 执行`mingw32-make.exe clean`命令，自动执行 Makefile 里的 第5行 指令 “rm main.exe”


重点是第8行，表示使用 main.c 生成 main.exe
 `add_executable(main main.c)`


1. 在源码目录下执行 `mkdir .\build\`，在该目录下创建一个 build 文件夹
2. 执行 `cd .\build\` ，进入刚刚创建的 build 文件夹
3. 执行 `cmake .. -G "MinGW Makefiles"` ，这个命令是使用 CMake 插件来生成 Makefile
a **. .** 表示在 build 的上一层目录 _（即源码 main.c 所在目录）_ 寻找 CMakeLists.txt  
b **-G “MinGW Makefiles”** 是因为 CMake 默认使用微软的 MSVC 作为编译器，想使用 MinGW 编译器可以通过 -G 参数来进行指定，只有第一次构建项目时需要指定。  
c 步骤 5-7 称为使用 CMake 进行 **外部构建** ，执行完后在 build 文件夹中生成了Makefile 。你还可以发现一个 **compile_commands.json** 文件，这是神奇妙妙文件，作用之后再说。

1. 执行`mingw32-make.exe`，步骤7 生成了 Makefile ，接下来当然就是执行 make 编生成 main.exe 文件
2. 执行`./main.exe` 运行程序，程序正常执行输出 hello world!

window 平台下 使用 printf() 函数时，编译器 MinGW 会在它的库文件里找到函数实现并调用。同样，用户在 **Linux 平台下**调用函数时，**交叉编译工具链**也会去**内核源码**中找到函数实现并调用。但是 windows 平台下没法运行 Linux 的交叉编译工具，在看到 printf() 时不知道去哪找这个函数的实现。  
但是在编译程序时，代码里每个函数的具体实现在哪个 .c 文件是确定的，这是在 Makefile 里写好了的。跟踪 Makefile 的编译过程可以知道各个函数的调用关系。在 **4.2 步骤7** 中生成的 **compile_commands.json** 就是保存了各个函数调用关系的文件。Clangd 读取这个文件，从而提供代码补全、跳转定义等语法服务。

## IPV 6 地址
目的地址可以是以下三种类型
- 单播
	- 点对点通信