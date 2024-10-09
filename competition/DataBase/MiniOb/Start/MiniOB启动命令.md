先`bash build.sh`进行编译
编译完成后输入`cd build_debug`进入build_debug文件夹
后`./bin/observer -f ../etc/observer.ini -P cli`

# Part1
 [[Bash,sh]]
`bash build.sh` 是一个在命令行（终端）中执行的命令，它的作用是用 Bash（Bourne Again SHell）这个 shell 解释器来执行名为 `build.sh` 的脚本文件
	**build.sh**：这是一个文本文件，通常包含了一系列的命令，这些命令在 bash 或其他兼容的 shell 环境中执行时，会完成一些特定的任务，比如编译软件、构建项目、执行测试等。文件名的 `.sh` 后缀是一个约定俗成的命名习惯，用来表示这是一个 shell 脚本文件
	**bash build.sh**：当你在命令行中输入这个命令时，你实际上是在告诉 bash 解释器去读取并执行 `build.sh` 文件中的命令。这相当于你手动在命令行中一行一行地输入那些命令，但自动化了这一过程

# Part2
命令 `./bin/observer -f ../etc/observer.ini -P cli` 是在Linux或类Unix操作系统中执行的一个命令行指令，它通常用于启动一个名为`observer`的程序或守护进程，并带有特定的配置和参数
	`./bin/observer`：这部分指定了要执行的程序或脚本的路径。`.` 代表当前目录，`/bin/observer` 表示在当前目录下的 `bin` 文件夹中有一个名为 `observer` 的可执行文件或脚本
	`-f ../etc/observer.ini`：这是传递给 `observer` 程序的第一个参数
		`-f` 通常用于指定配置文件的路径
		在这个例子中，它指定了 `observer` 应该使用位于上一级目录（`..`）中的 `etc` 文件夹下的 `observer.ini` 文件作为配置文件。这个配置文件可能包含了程序运行所需的各种设置和参数
	`P cli`：这是第二个参数，它可能用于指定程序应该以某种特定的模式运行
		**`-P cli` 可能意味着 `observer` 程序应该以命令行界面（CLI）模式运行**
这个命令的作用是从当前目录的 `bin` 子目录中启动 `observer` 程序，使用位于上一级目录的 `etc` 文件夹中的 `observer.ini` 文件作为配置文件，并以命令行界面模式运行。这样的命令通常用于启动需要持续运行并监控某些资源或执行周期性任务的后台服务或守护进程

对于`./bin/observer -f ../etc/observer.ini -P cli`的解析，在[[observer]]的  `parse_parameter(argc, argv)`函数
[[observer#^4ddfa0]]
-P就是修改了其protocol



