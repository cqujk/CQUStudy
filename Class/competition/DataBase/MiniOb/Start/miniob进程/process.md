*process就是进程*，即miniob所在的进程
# process_param配置
这个`process_param`是一个全局变量，定义为`common`中的命名
```java
namespace common {
//! Global process config
ProcessParam *&the_process_param()
{
  static ProcessParam *process_cfg = new ProcessParam();
  return process_cfg;
}
}
```
每次要对`process_param`进行修改时，都会调用`the_process_param`方法，返回一个指向`ProcessParam*`（即指向`ProcessParam`类型指针的指针）的引用
	这种设计通常是为了确保函数返回的是一个指向全局唯一对象的指针，并且这个指针本身也是通过引用返回的，从而避免了通过函数返回指针时可能发生的拷贝，同时也允许调用者能够修改这个指针 ^b84c22

`static ProcessParam *process_cfg = new ProcessParam();`
在函数内部，定义了一个静态的`ProcessParam`类型的指针`process_cfg`，并使用`new`操作符动态分配了一个`ProcessParam`对象给它。==由于`process_cfg`是静态的，它只会在函数第一次被调用时初始化一次，之后的调用都会直接返回这个已经初始化的指针，它会在整个程序的生命周期内持续存在，直到程序结束==。这保证了`ProcessParam`对象的全局唯一性和单例性



# 进程`init()`方法
先检查进程是否是否已初始化，这个也是个全局变量，通过`static`实现
`  if (get_init()) {  return 0;}`
```java
bool *&_get_init()
{
  static bool  util_init   = false;
  static bool *util_init_p = &util_init;
  return util_init_p;
}
```
如果没有就设置其为1
然后将其以守护进程模式运行，（通过`is_demon()`方法检查），则尝试调用`daemonize_service()`函数来实现。如果守护进程化失败（即`daemonize_service()`返回非零值），则打印错误信息并返回错误码
	这个函数相当于干了两件事，一件事是将当前进程设置为守护进程，第二件事就是构建了进程的输出与错误打印文件

然后调用`writePidFile()`函数，将当前进程的PID写入到由`ProcessParam`对象指定的文件名中，用于在守护进程模式下跟踪进程ID。

接着就是加载配置文件以及初始化日志
```JAVA
  // Read Configuration files
  rc = get_properties()->load(process_param->get_conf());
  if (rc) {
    cerr << "Failed to load configuration files" << endl;
    return rc;
  }
    // Init tracer
  rc = init_log(process_param, *get_properties());
  if (rc) {
    cerr << "Failed to init Log" << endl;
    return rc;
  }
```
接着很重要的一步是构建了一个全局对象
`  rc = init_global_objects(process_param, *get_properties());`
`if (rc != 0) {    LOG_ERROR("failed to init global objects");return rc;  }`
```java
int init_global_objects(ProcessParam *process_param, Ini &properties)
{
  GCTX.handler_ = new DefaultHandler();
  int ret = 0;
  RC rc = GCTX.handler_->init("miniob", 
                              process_param->trx_kit_name().c_str(),
                              process_param->durability_mode().c_str());
  if (OB_FAIL(rc)) {
    LOG_ERROR("failed to init handler. rc=%s", strrc(rc));
    return -1;
  }
  return ret;
}
```
在这个函数中，通过 `DefalutHandler` 的 `init` 方法，构建了全局的系统数据库 miniob
# process.cpp
里面主要是进程初始化的函数实现
`daemonize_service`里调用`sys_log_redirect`
### daemonize_service
定义在`common`命名空间中，最主要的函数是 `daemonize_service`，有俩重载，
- **目的**：将当前进程守护进程化，即脱离终端，并在后台运行。
- **第一个重载(bool close_std_streams)**：不接受任何文件路径，仅关闭标准输入输出流（如果 `close_std_streams` 为 `true`）
	- 这个参数用于指示在守护进程化过程中是否应该关闭标准输入、输出和错误流（stdin, stdout, stderr）
	- **变量初始化**：
		- `int nochdir = 1;`：设置`nochdir`为1，这表示在守护进程化过程中不改变工作目录到根目录（`/`）。如果设置为0，则会改变工作目录到根目录。
		- `int noclose = close_std_streams ? 0 : 1;`：根据`close_std_streams`的值设置`noclose`。
			- 如果`close_std_streams`为`true`，则`noclose`为0，表示关闭标准输入、输出和错误流；如果为`false`，则`noclose`为1，表示不关闭
	- **调用`daemon`函数**
		- `int rc = daemon(nochdir, noclose);`：==调用`daemon`函数尝试将当前进程转换为守护进程。==
			- `daemon`函数根据`nochdir`和`noclose`参数的行为来执行必要的步骤（如创建子进程、关闭标准文件描述符、会话分离等）
	- 通过宏对特定平台处理
		- 对于Mac OS X（由`__MACH__`宏标识），使用GCC的诊断指令来忽略`-Wdeprecated-declarations`警告。这是因为`daemon`函数在Mac OS X上可能被标记为已弃用，但这些警告在编译守护进程化代码时可能会干扰开发者。使用`#pragma GCC diagnostic push`和`#pragma GCC diagnostic pop`可以临时忽略这些警告，而不会影响其他部分的代码
		- 这是通过如下代码实现的，即 `# ifdef __MACH_`
```java
#ifdef __MACH__

#include <libgen.h>

#endif
```
- **第二个重载(const char *std_out_file, const char *std_err_file) ** ：接受标准输出和标准错误输出的文件路径，并将它们重定向到这些文件。

### `sys_log_redirect` 函数

**目的**：将标准输出（stdout）和标准错误输出（stderr）重定向到指定的文件
**参数**：`const char *std_out_file` 和 `const char *std_err_file`，分别指向标准输出和标准错误输出文件的路径
- **实现**：首先，将标准输入（stdin）重定向到 `/dev/null`。然后，计算当前时间戳（尽管这个值在后续代码中并未直接使用）。接着，尝试打开指定的标准输出和标准错误输出文件，如果文件已存在且大小超过预设的限制（尽管这部分代码被注释掉了），则截断文件。最后，使用 `dup2` 将文件描述符重定向到 `STDOUT_FILENO` 和 `STDERR_FILENO`，并关闭原始的文件描述符。此外，还禁用了标准输出和标准错误输出的缓冲。

```c
  // Redirect stdin to /dev/null
  int nullfd = open("/dev/null", O_RDONLY);
  if (nullfd >= 0) {
    dup2(nullfd, STDIN_FILENO);
    close(nullfd);
  }
```
尝试以只读模式（`O_RDONLY`）打开`/dev/null`设备文件，并将返回的文件描述符赋值给`nullfd`变量
	在Unix和类Unix系统中，`/dev/null`是一个特殊的设备文件，通常被称为“空设备”或“黑洞”。向`/dev/null`写入的数据会被系统丢弃，读取`/dev/null`则会立即返回文件结束（EOF）
如果`/dev/null`成功打开，将使用`dup2`函数将`STDIN_FILENO`（标准输入的文件描述符，通常为0）重定向到`nullfd`
	`dup2`函数会复制`nullfd`到`STDIN_FILENO`，如果`STDIN_FILENO`之前已经打开了一个文件，那么这个文件会被关闭（除非它是`nullfd`本身）
[[linux之dup和dup2函数解析#^02cfdf]]


#### 创建文件

还是利用`open()`函数，将传入的文件地址，传入标志位以及权限标志
对于权限标志
`#define RWRR (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)`
是USR具有读写权力，而其他都只有R，即读权限

对于传入的标志位
`  std_err_flag = std_out_flag = O_CREAT | O_APPEND | O_WRONLY;`
`  std_err_flag |= O_TRUNC;  // Remove old content if any.`

```JAVA
  int errfd = open(err_file.c_str(), std_err_flag, RWRR);
  if (errfd >= 0) {
    dup2(errfd, STDERR_FILENO);
    close(errfd);
  }
  setvbuf(stderr, NULL, _IONBF, 0);  // Make sure stderr is not buffering
  cerr << "Process " << getpid() << " built error output at " << tv.tv_sec << endl;
```
`dup2(errfd, STDERR_FILENO);`将`errfd`（新打开的文件描述符）复制到`STDERR_FILENO`（标准错误的文件描述符，通常是2）。这意味着之后所有写入`stderr`的输出都会写入到`err_file`指定的文件中
**禁用`stderr`的缓冲**
`setvbuf(stderr, NULL, _IONBF, 0);  // Make sure stderr is not buffering
这行代码通过`setvbuf`函数禁用`stderr`的缓冲。`_IONBF`表示不缓冲，`NULL`和`0`作为其他参数，表示不使用用户提供的缓冲区，并且不设置缓冲区大小（因为不缓冲）
`

对于输出文件也一样
```java
  std_out_flag |= O_TRUNC;  // Remove old content if any.

  int outfd = open(outFile.c_str(), std_out_flag, RWRR);

  if (outfd >= 0) {

    dup2(outfd, STDOUT_FILENO);

    close(outfd);

  }

  setvbuf(stdout, NULL, _IONBF, 0);  // Make sure stdout not buffering

  cout << "Process " << getpid() << " built standard output at " << tv.tv_sec << endl;
```