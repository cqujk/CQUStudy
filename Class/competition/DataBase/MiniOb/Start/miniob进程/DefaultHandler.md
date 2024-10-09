`  RC   init(const char *base_dir, const char *trx_kit_name, const char *log_handler_name);`
初始化存储引擎
   * @param base_dir 存储引擎的根目录。所有的数据库相关数据文件都放在这个目录下
   * @param trx_kit_name 使用哪种类型的事务模型
   * @param log_handler_name 使用哪种类型的日志处理器

### 函数流程

1. **目录检查与创建**：
    - 使用`filesystem::path`对象`db_dir`来构建基础目录下的`"db"`子目录的路径。
    - 检查`db_dir`是否存在，如果不存在，则尝试创建它。这里使用了`filesystem::is_directory`和`filesystem::create_directories`函数，并传入了一个`error_code`对象`ec`来捕获可能发生的错误
    - 如果目录不存在且无法创建，记录错误日志并返回`RC::INTERNAL`错误码。
2. **成员变量赋值**：
    - 将传入的`base_dir`、`trx_kit_name`、`log_handler_name`分别赋值给类的成员变量`base_dir_`、`trx_kit_name_`、`log_handler_name_`。
3. **创建并打开系统数据库**：
    - 定义一个常量字符串`sys_db`，表示系统数据库的名称（这里是`"sys"`）。
    - 调用`create_db(sys_db)`尝试创建系统数据库。如果返回的不是`RC::SUCCESS`也不是`RC::SCHEMA_DB_EXIST`（表示数据库已存在且结构兼容），则记录错误日志并返回相应的错误码。
    - 调用`open_db(sys_db)`尝试打开系统数据库。如果返回的不是`RC::SUCCESS`，则记录错误日志并返回相应的错误码。
4. **设置默认会话的当前数据库**：
    - 通过`Session::default_session()`获取默认会话对象。
    - 调用`set_current_db(sys_db)`将默认会话的当前数据库设置为系统数据库
5. **记录成功日志**：
    - 使用`LOG_INFO`记录一条信息日志，表示默认处理器初始化成功，并附带了基础目录的路径。
6. **返回成功**：
    - 函数返回`RC::SUCCESS`，表示初始化成功完成。