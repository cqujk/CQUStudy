# Main
通过终端输入的 `argv` 向 `observer` 的 `main` 函数传递指令，
## 解析输入指令，得到进程参数
[[process_param#^b84c22]]
`parse_parameter(argc, argv);` 函数对其进行解析，结果保存在全局变量的 `process_param` 中
## 由进程参数构建出相应的数据库进程
通过`(the_process_param()`获取（全局）进程参数配置（是和上面共用的），并对其进行全局的`init()`方法进行进程的初始化操作
	这个`init()`是`os`文件夹下的，直接与操作系统关联，对进程进行操作
	经过 `init()` 可以创建出进程的输出、错误日志文件，以及全局的数据库对象——miniob

## 初始化服务器端
`  g_server = init_server();`
## 使服务器进入运行状态
经过 `  g_server->serve();` 后，进程可以对命令行中输入的 SQL 指令进行相应的解析与运行操作
```c
int main(int argc, char **argv)
{
  int rc = STATUS_SUCCESS;
  cout << startup_tips;
  set_signal_handler(quit_signal_handle);
  parse_parameter(argc, argv);
  rc = init(the_process_param());
  if (rc != STATUS_SUCCESS) {
    cerr << "Shutdown due to failed to init!" << endl;
    cleanup();
    return rc;
  }
  g_server = init_server();
  g_server->serve();
  LOG_INFO("Server stopped");
  cleanup();
  delete g_server;
  return 0;
}
```
# void parse_parameter(int argc, char **argv)

```c
void parse_parameter(int argc, char **argv)
{
  string process_name = get_process_name(argv[0]);
  ProcessParam *process_param = the_process_param();
  process_param->init_default(process_name);
  // Process args
  int          opt;
  extern char *optarg;
  while ((opt = getopt(argc, argv, "dp:P:s:t:T:f:o:e:hn:")) > 0) {
    switch (opt) {
      case 's': process_param->set_unix_socket_path(optarg); break;
      case 'p': process_param->set_server_port(atoi(optarg)); break;
      case 'P': process_param->set_protocol(optarg); break;
      case 'f': process_param->set_conf(optarg); break;
      case 'o': process_param->set_std_out(optarg); break;
      case 'e': process_param->set_std_err(optarg); break;
      case 't': process_param->set_trx_kit_name(optarg); break;
      case 'T': process_param->set_thread_handling_name(optarg); break;
      case 'n': process_param->set_buffer_pool_memory_size(atoi(optarg)); break;
      case 'd': process_param->set_durability_mode("disk"); break;
      case 'h':
        usage();
        exit(0);
        return;
      default: cout << "Unknown option: " << static_cast<char>(opt) << ", ignored" << endl; break;
    }
  }
}
```

argv是输入的第二项，，

```java
while ((opt = getopt(argc, argv, "dp:P:s:t:T:f:o:e:hn:")) > 0)
```
1. 调用 `getopt` 函数，传入命令行参数的数量 `argc`、指向参数字符串数组的指针 `argv`，以及一个短选项字符串 `"dp:P:s:t:T:f:o:e:hn:"`。
2. 短选项字符串中的每个字符代表一个有效的选项字符。如果选项字符后面跟着一个冒号（`:`），则表示该选项需要一个附加的参数。在你的例子中，`p`、`P`、`s`、`t`、`T`、`f`、`o`、`e` 和 `n` 都需要附加的参数 ^4ddfa0
3. `getopt` 函数会逐个解析 `argv` 中的参数，并返回找到的选项字符。如果所有选项都处理完毕，或者遇到了一个非法的选项字符，`getopt` 会返回 `-1`
4. `while` 循环会持续执行，直到 `getopt` 返回 `-1`，表示没有更多的选项需要处理。
5. 在每次循环中，`opt` 变量会被赋值为 `getopt` 返回的选项字符。然后，你可以根据 `opt` 的值来执行不同的操作,使用 `switch` 语句来检查是哪个选项被找到，并相应地处理它的附加参数

### 对于-p
`case 'p': process_param->set_server_port(atoi(optarg)); break;`
### getopt
```java
extern int getopt (int ___argc, char *const *___argv, const char *__shortopts)
       __THROW __nonnull ((2, 3));
__END_DECLS
```

函数接受三个参数：

- **`int ___argc`：命令行参数的数量。**
- `char *const *___argv`：指向命令行参数字符串数组的指针。
- `const char *__shortopts`：一个字符串，指定了有效的短选项字符及其可能的后续参数。
1. **`__nonnull` 属性**:  
    这是GCC的一个函数属性，用于指定函数的哪些参数不能为空（NULL）。在这个例子中，`__nonnull ((2, 3))`表明函数的第二个和第三个参数（即`___argv`和`__shortopts`）必须是非空的。如果传递给这些参数的指针是NULL，编译器会发出警告或错误。

