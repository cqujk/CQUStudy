```
pub fn factorial(num: u64) -> u64 {
    match num{
        0=>1,
        _ if num>1 => num*factorial(num-1),
        _ =>num,
    }
}
```

`(1..=num).fold(1, |acc, x| acc*x)`
`let status_shared = Arc::clone(&status);` 通过引用的类型, 就是堆上是唯一的东西,但是栈上是不同的指针
```
let qc = Arc::new(q);
let qc1 = Arc::clone(&qc);
let qc2 = Arc::clone(&qc);
```
使用 `Arc` 来共享 `Queue` 的所有权，并克隆 `Arc` 以在两个线程中使用

`Cow` 类型，这是 "Copy-On-Write" 的缩写。
`Cow` 是一个智能指针，它允许以不可变的方式访问借用的数据，并在需要时延迟克隆数据进行修改或获取所有权
- **Cow::Borrowed(_)**：表示 `Cow` 仍然借用原始数据。
- **Cow::Owned(_)**：表示 `Cow` 拥有数据的副本

`Rc<T>` 是一个引用计数的智能指针，允许多个所有者拥有相同的数据
1. **引用计数**：`Rc<T>` 使用引用计数来跟踪有多少个所有者正在使用数据。每次创建一个新的 `Rc<T>` 引用时，引用计数会增加。当一个 `Rc<T>` 被丢弃时，引用计数会减少。
2. **不可变共享**：`Rc<T>` 允许多个所有者以不可变的方式共享数据

在 Rust 中宏分为两大类：**声明式宏( _declarative macros_ )** `macro_rules!` 和三种**过程宏( _procedural macros_ )**:
- `#[derive]`，在之前多次见到的派生宏，可以为目标结构体或枚举派生指定的代码，例如 `Debug` 特征
- 类属性宏(Attribute-like macro)，用于为目标添加自定义的属性
- 类函数宏(Function-like macro)，看上去就像是函数调用

宏是通过一种代码来生成另一种代码
由于宏会被展开成其它代码，且这个展开过程是发生在编译器对代码进行解释之前。因此，宏可以为指定的类型实现某个特征：先将宏展开成实现特征的代码后，再被编译
而函数就做不到这一点，因为它直到运行时才能被调用，而特征需要在编译期被实现
```
macro_rules! my_macro {
    () => {
        println!("Check out my macro!");
    };
}
```
- `macro_rules!`：这是定义宏的关键字。
- `my_macro`：这是宏的名称。
- `{}`：宏的规则块，它定义了宏的行为。
定义了一个没有参数的宏（`()` 表示宏不接受任何输入）。当这个宏被调用时，它将展开为一个 `println!` 宏调用

宏 `my_macro` 被定义在 `macros` 模块中，但在 `main` 函数中尝试不通过模块前缀直接调用它。由于宏没有被标记为 `pub`，它在模块外部是不可见的
### 特征 `From`
`From` 特征用于值到值的转换，并且在转换过程中会消耗输入值。它与`Into` 特征是相反的操作。如果为一个类型正确实现了 `From` 特征，那么标准库会自动提供相对应的 `Into` 实现。