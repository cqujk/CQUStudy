直接映射配置窗口（DMW）。它可以提供虚拟地址`[31:29]`部分到物理地址`[31:29]`的映射配置,在地址映射窗口中设置允许访问该窗口的特权级以及Cache属性。
# 配置DMW
在计算机上电启动时，软件运行在物理地址空间中，真实硬件上通常会在上电启动时从第一级Bootloader开始执行完成系统的初始化，再逐级载入更高级的Bootloader以至于最后启动操作系统

而具体从哪一级开始使用虚拟地址取决于各架构以及系统软件
- 对于我们本次实验使用的LoongArch32架构而言,在[[CQUStudy/Class/Junior/Autumn 2024/OS/CQU/Note/Summary/KnowledgePoints/QEMU]]上运行时是在uCore操作系统启动时，由操作系统配置DMW窗口并修改CSR.CRMD寄存器开始开启虚拟地址映射的
- 而如果是使用Chiplab软核，它的第一级Bootloader是PMON，在PMON中就会设置DMW并开启虚拟地址映射