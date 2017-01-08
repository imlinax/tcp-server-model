# tcp-server-model
chenshuo在《Linux多线程服务端编程 使用muduo C++网络库》中，总结了12种并发网络服务程序设计方案。该项目会分别以这12种方案实现echo客户端。
![网络服务器并发模型](http://img.blog.csdn.net/20170107230947044?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvQXNoaW5lZQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

方案0: basic模型，只有一个进程，一个线程，main函数中初始化socket之后，便一直accept下去，每次仅能服务一个客户端。当前的客户端不断开，后一个客户端就都不到服务。对应代码,solution0.c  
方案1: fork模型，即简单的多进程模型，主进程不处理业务，只accept客户端，然后将得到的client socke fd交由子进程处理。对应代码，solution1.c  
方案2: thread模型，与fork模型基本一致，只不过将多进程模型换成了多线程模型,在效率上有一定的提高。  
