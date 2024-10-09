使用`wait()`和`notify()`方法
# ???
# wait
***wait()方法会释放目标对象的锁,而Thread.sleep()方法不会释放任何资源.***

通过 `synchronized (object)` 语句块获取 `object` 的锁
	使用`synchronized (object)`就是获取类中的同步资源，防止其被其它线程修改
调用 `object.wait();`。`wait()` 方法会使当前线程（即 `Thread1`）等待，并释放 `object` 锁。这意味着其他线程（如 `Thread2`）可以获取 `object` 锁并执行其同步代码块

# notify
当某个线程完成了某个条件（或一系列条件）的准备工作，并希望另一个线程能够继续执行时，它会调用 `notify()` 方法来唤醒一个等待该条件的线程
`notify()` 方法会唤醒正在 `object` 上等待的单个线程（如果有的话）。注意，这里不保证唤醒的是 `Thread1`，但在本例中，由于没有其他线程在 `object` 上等待，且 `Thread1` 已经在等待，所以通常是 `Thread1` 被唤醒。

`Object notify()` 方法用于唤醒一个在此对象监视器上等待的线程

# 示例
`RunoobTest`里有一个用于测试的公共资源`List synchedList`,且定义了两个修改它的方法`String removeElement()`与`addElement(String element)`
	这两个修改方法都会去获得类的公共资源`List synchedList`
`String removeElement()`中，尝试删除元素，并打印出删除的元素
```Java
	// 列表为空就等待 
	while (synchedList.isEmpty()) { 
		System.out.println("List is empty...");
		 synchedList.wait();
		  System.out.println("Waiting..."); 
	   }
	   String element = (String) synchedList.remove(0);
```
`addElement(String element)`中，去添加元素
```java
// 添加元素到列表 
public void addElement(String element) {
	System.out.println("Opening...");
	 synchronized (synchedList) { 
	 // 添加一个元素，并通知元素已存在 
		 synchedList.add(element);
		 System.out.println("New Element:'" + element + "'"); 
		 synchedList.notifyAll(); 
		 System.out.println("notifyAll called!"); 
	 } 
	 System.out.println("Closing..."); 
}
```


```java
   try {  
        Thread threadA1 = new Thread(runA, "Google");  
        threadA1.start();  
  
        Thread.sleep(500);  
  
        Thread threadA2 = new Thread(runA, "Runoob");  
        threadA2.start();  
  
        Thread.sleep(500);  
  
        Thread threadB = new Thread(runB, "Taobao");  
        threadB.start();  
  
        Thread.sleep(1000);  
  
        threadA1.interrupt();  
        threadA2.interrupt();  
    } catch (InterruptedException x) {  
    }  
}
```
执行结果为
```
List is empty...
List is empty...
Opening...
New Element:'Hello!'
notifyAll called!
Closing...
Waiting...
Waiting...
List is empty...
Hello!
Interrupted Exception!
```

这里，remove相当于消费者，add相当于生产者