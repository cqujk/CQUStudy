#### MiniOB 的关键数据结构
```c
parse_def.h:
	struct Selects; //查询相关
	struct CreateTable; //建表相关
	struct DropTable; //删表相关
	enum SqlCommandFlag; //SQL 语句对应的 command 枚举
	union Queries; //各类 DML 和 DDL 操作的联合
table.h
	class Table;
db.h
	class Db;

```
#### MiniOB 的关键接口
```c
RC parse(const char *st, Query *sqln); //sql parse 入口
ExecuteStage::handle_request
ExecuteStage::do_select
DefaultStorageStage::handle_event
DefaultHandler::create_index
DefaultHandler::insert_record
DefaultHandler::delete_record
DefaultHandler::update_record
Db::create_table
Db::find_table
Table::create
Table::scan_record
Table::insert_record
Table::update_record
Table::delete_record
Table::scan_record
Table::create_index

```