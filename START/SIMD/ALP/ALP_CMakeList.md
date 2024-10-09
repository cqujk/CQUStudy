使用 `define_property` 命令定义了一个全局属性 `ALP_ALL_BENCHMARK_TARGETS`，用于存储基准测试目标的列表。
```
define_property(GLOBAL PROPERTY ALP_ALL_BENCHMARK_TARGETS
BRIEF_DOCS "Global list of elements"
FULL_DOCS "Global list of elements")
```
- 使用 `set_property` 命令初始化这个全局属性，初始值为空字符串。

- 定义了一个宏 `add_alp_benchmark`，它使用 `set_property` 命令将新的变量追加到全局属性 `ALP_ALL_BENCHMARK_TARGETS`。
1. **条件编译**：
    
    - 根据系统名称和处理器类型，决定添加哪些子目录：
        - 如果是 Emscripten，设置可执行文件后缀为 `.html` 并添加 `wasm` 子目录。
            
        - 如果处理器是 arm64 或 aarch64，添加 `arm64v8` 子目录并定义 `ALP_ARM64V8`。
            
        - 如果处理器是 x86 或 amd64，添加 `x86_64` 子目录并定义 `ALP_X86_64`。

使用 `add_library` 命令添加了一个共享库 `alp_generated`，它包含了一些生成的对象文件和 `alp_generated.cpp`

# CMake_Study
[cmake使用详细教程（日常使用这一篇就足够了）_cmake教程-CSDN博客](https://blog.csdn.net/iuu77/article/details/129229361)
- **PROJECT_BINARY_DIR**是cmake系统变量，意思是执行cmake命令的目录，我们计划在**build**目录下执行**cmake**命令，所以这个变量也就等同于build目录


## 生成库函数
  *add_library(lib_name STATIC/SHARED src)*    
2. # 函数作用：生成库。
    
3. # 参数lib_name：是要生成的库名称，
    
4. # 参数STATIC/SHARED：指定生成静态库或动态库，
    
5. # 参数src：指明库的生成所需要的源文件
![[Pasted image 20240928165150.png]]
**set_target_properties**重新定义了库的输出名称，如果不使用set_target_properties也可以，那么库的名称就是add_library里定义的名称
![[Pasted image 20240928165327.png]]
Set 就是指定一些参数, 进行设置生成
	如果是**LIBRARY_OUTPUT_PATH**, 就是去设置生成的库函数所处的路径 是cmake系统变量，项目生成的库文件都放在这个目录下。这里我指定库生成到lib目录

***add_library 就是生成库函数,add_executable 就是去生成一个可执行文件***
##  main函数来使用库文件 
**目录结构如下：**
- **lib**目录下存放静态库和动态库
- **main_src**目录下存放main函数相关的源文件
- **bin**目录存放项目生成的可执行文件

Cmake 里面写的就是, 把源文件包含进 MAIN_SRC
引入头文件路径,
然后查找库文件, 在 lib 里面
	/../就是往上反了一级
Set 就是指定一些参数,进行设置生成
	如果是**EXECUTABLE_OUTPUT_PATH**,就是存放可执行文件的路径,是cmake系统变量，意思是生成的可执行文件的的目录，我这里把他改为bin目录，因此生成的可执行性文件会出现在bin目录中

![[Pasted image 20240928165600.png|525]]
使用 aux_source 来整合所有的代码,源文件
使用 include来引入所有的头文件
使用 find_library 来引入所有的库文件
	这一步只是相当于把库引了进来
使用 target_link 把库, 连接到生成的可执行文件中
	这一步才是真正把库运行在项目当中
## add_subdirectory
[Cmake命令之add_subdirectory_cmake add subdirectory-CSDN博客](https://blog.csdn.net/sinat_31608641/article/details/122660652)
该命令是**添加一个子目录并构建该子目录**
add_subdirectory (source_dir [binary_dir] [EXCLUDE_FROM_ALL])


├── [CMakeLists](https://so.csdn.net/so/search?q=CMakeLists&spm=1001.2101.3001.7020).txt   父目录的CMakeList .txt  
├── main.cpp    源文件，包含main函数  
├── sub    子目录  
 └── CMakeLists.txt    子目录的CMakeLists.txt  
 └── test.h    子目录头文件  
 └── test.cpp    子目录源文件

**场景1**：父目录 `CMakeLists.txt` 的 `add_subdirectory` 只指定了 `source_dir`
1.   
    add_subdirectory(sub)
在父目录下调用 `cmake .` 构建之后，在 `sub` 目录下会出现 `libsub.a` 库，说明当不指定 `binary_dir`，输出目标文件就会放到 `source_dir` 目录下

测试 simd 函数，和编译器的指令的快慢
	1.
ALP 论文，优化方式
毕业论文——思想

超哥——serf项目框架中 ALP 实现方式？