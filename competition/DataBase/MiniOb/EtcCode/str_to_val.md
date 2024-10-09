目的是将一个字符串（`std::string`）转换为一个给定类型 `T` 的值，并允许指定基数（进制）进行转换

- **模板参数**：`T` 是一个模板参数，表示目标值的类型。
- **函数参数**：
    - `const string &str`：要转换的源字符串。
    - `T &val`：对目标值的引用，转换后的值将被存储在这里。
    - `ios_base &(*radix)(ios_base &)`：一个指向 `ios_base` 成员函数的指针，这个函数用于设置输入流的基数（进制）。默认为 `std::dec`，即十进制。这个参数允许用户指定不同的基数（如十六进制 `std::hex`）进行转换。

```c
template <class T>
bool str_to_val(const string &str, T &val, ios_base &(*radix)(ios_base &)/* = std::dec */)
{
  bool          success = true;
  istringstream is(str);
  if (!(is >> radix >> val)) {
    val     = 0;
    success = false;
  }
  return success;
}
```


- 创建一个 `istringstream` 对象 `is`，用于从字符串 `str` 中读取数据。
	- 结果保存在 is当中
- 尝试使用 `radix` 指定的基数从 `is` 中读取数据到 `val`。