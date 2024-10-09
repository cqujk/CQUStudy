# 1
从按下主机上的 power 键后，第一个运行的软件是 BIOS。于是产生了三个问题。
（1）它是由谁加载的。 
（2）它被加载到哪里。 
（3）它的 cs：ip 是谁来更改的。
# 2
## 2 .1
Intel 8086 有 20 条地址线，故其可以访问 1 MB 的内存空间，即 2 的 20 次方=1048576=1 MB, 地址范围若按十六进制来表示，是 0 x 00000 到 0 xFFFF
地址总线宽度决定了可以访问的内存空间大小，如 16 位机的地址总线为 20 位，其地址范围是 1 MB，32 位地址总线宽度是 32 位，其地址范围是 4 GB

即使内存条大小没有超过地址总线的范围，也不会全都能被访问到，毕竟要预留一些地址用来访问其他外设，所以最终还得看地址总线把地址指向哪块内存了
	这就是安装了 4 GB 内存，电脑中只显示 3.8 GB 左右的原因
CPU 能够访问一个地址，这是地址总线给做的映射，相当于给该地址分配了一个存储单元，而该存储单元要么落在某个 rom 中，要么落到了某个外设的内存中，要么落到了物理内存条上
## 2 .2
因为 BIOS 是计算机上第一个运行的软件，所以它不可能自己加载自己，由此可以知道，*它是由硬件加载的*
只读存储器中的内容是不可擦除的，也就是它不像动态随机访问存储器 DRAM 那样，掉电后，里面的数据就会丢失
BIOS 代码所做的工作也是一成不变的，而且在正常情况下，其本身是不需要修改的
ROM 也是块内存，内存就需要被访问。此 ROM 被映射在低端 1 MB 内存的顶部，即地址 0 xF 0000～0 xFFFFF 处
	只要访问此处的地址便是访问了 BIOS，这个映射是由硬件完成的
BIOS 本身是个程序，程序要执行，就要有个入口地址才行，此入口地址便是 0 xFFFF 0
在开机的一瞬间，也就是接电的一瞬间，CPU 的 cs：ip 寄存器被强制初始化为 0 xF 000：0 xFFF 0。由于开机的时候处于实模式，在实模式下的段基址要乘以 16，也就是左移 4 位，于是 0 xF 000： 0 xFFF 0 的等效地址将是 0 xFFFF 0
 BIOS 便马不停蹄地检测内存、显卡等外设信息，当检测通过，并初始化好硬件后，开始在内存中 0 x 000～0 x 3 FF 处建立数据结构，中断向量表 IVT 并填写中断例程
## 2 .3
主引导记 mbr 是段程序，无论位于软盘、硬盘或者其他介质，总该有个地方保存它