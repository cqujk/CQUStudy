Statement SQL语句解析后通过Resolver转换成Stmt

# Statement的类型

```java
#define DEFINE_ENUM()            \

  DEFINE_ENUM_ITEM(CALC)         \

  DEFINE_ENUM_ITEM(SELECT)       \

  DEFINE_ENUM_ITEM(INSERT)       \

  DEFINE_ENUM_ITEM(UPDATE)       \

  DEFINE_ENUM_ITEM(DELETE)       \

  DEFINE_ENUM_ITEM(CREATE_TABLE) \

  DEFINE_ENUM_ITEM(DROP_TABLE)   \

  DEFINE_ENUM_ITEM(CREATE_INDEX) \

  DEFINE_ENUM_ITEM(DROP_INDEX)   \

  DEFINE_ENUM_ITEM(SYNC)         \

  DEFINE_ENUM_ITEM(SHOW_TABLES)  \

  DEFINE_ENUM_ITEM(DESC_TABLE)   \

  DEFINE_ENUM_ITEM(BEGIN)        \

  DEFINE_ENUM_ITEM(COMMIT)       \

  DEFINE_ENUM_ITEM(ROLLBACK)     \

  DEFINE_ENUM_ITEM(LOAD_DATA)    \

  DEFINE_ENUM_ITEM(HELP)         \

  DEFINE_ENUM_ITEM(EXIT)         \

  DEFINE_ENUM_ITEM(EXPLAIN)      \

  DEFINE_ENUM_ITEM(PREDICATE)    \

  DEFINE_ENUM_ITEM(SET_VARIABLE)
```


```java
enum class StmtType{
#define DEFINE_ENUM_ITEM(name) name,
  DEFINE_ENUM()
#undef DEFINE_ENUM_ITEM
};
```
# 定义与实现
## Stmt类型
```c
class Stmt
{
public:
  Stmt()          = default;
  virtual ~Stmt() = default;
  virtual StmtType type() const = 0;
public:
  static RC create_stmt(Db *db, ParsedSqlNode &sql_node, Stmt *&stmt);
private:
};
```

SQL解析后的语句，再进一步解析成Stmt，使用内部的数据结构来表示。

 * 比如table_name，解析成具体的 Table对象，attr/field name解析成Field对象

参数中，*db指明是哪个数据库，sql_node是解析后的结点，stmt是最后的返回类型*
依据sql_node中的flag来判别到底应该创建出什么样的stmt，再调用相关stmt的Creat方法
```c
RC Stmt::create_stmt(Db *db, ParsedSqlNode &sql_node, Stmt *&stmt)
{
  stmt = nullptr;
  switch (sql_node.flag) {

    case SCF_INSERT: {

      return InsertStmt::create(db, sql_node.insertion, stmt);

    }

    case SCF_DELETE: {

      return DeleteStmt::create(db, sql_node.deletion, stmt);

    }

    case SCF_SELECT: {

      return SelectStmt::create(db, sql_node.selection, stmt);

    }

  

    case SCF_EXPLAIN: {

      return ExplainStmt::create(db, sql_node.explain, stmt);

    }

  

    case SCF_CREATE_INDEX: {

      return CreateIndexStmt::create(db, sql_node.create_index, stmt);

    }

  

    case SCF_CREATE_TABLE: {

      return CreateTableStmt::create(db, sql_node.create_table, stmt);

    }

  

    case SCF_DESC_TABLE: {

      return DescTableStmt::create(db, sql_node.desc_table, stmt);

    }

  

    case SCF_HELP: {

      return HelpStmt::create(stmt);

    }

  

    case SCF_SHOW_TABLES: {

      return ShowTablesStmt::create(db, stmt);

    }

  

    case SCF_BEGIN: {

      return TrxBeginStmt::create(stmt);

    }

  

    case SCF_COMMIT:

    case SCF_ROLLBACK: {

      return TrxEndStmt::create(sql_node.flag, stmt);

    }

  

    case SCF_EXIT: {

      return ExitStmt::create(stmt);

    }

  

    case SCF_SET_VARIABLE: {

      return SetVariableStmt::create(sql_node.set_variable, stmt);

    }

  

    case SCF_LOAD_DATA: {

      return LoadDataStmt::create(db, sql_node.load_data, stmt);

    }

  

    case SCF_CALC: {

      return CalcStmt::create(sql_node.calc, stmt);

    }

  

    default: {

      LOG_INFO("Command::type %d doesn't need to create statement.", sql_node.flag);

    } break;

  }
  return RC::UNIMPLENMENT;
}
```

## stmt_type_ddl
```c
bool stmt_type_ddl(StmtType type);
```

```c
bool stmt_type_ddl(StmtType type)
{

  switch (type) {

    case StmtType::CREATE_TABLE:

    case StmtType::DROP_TABLE:

    case StmtType::DROP_INDEX:

    case StmtType::CREATE_INDEX: {

      return true;

    }

    default: {

      return false;

    }

  }

}
```
