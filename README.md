# linux_kernel
some research and tries about linux-kernel

使用linux内核调试机制jprobe对 sys_execve函数入口点进行监视，获取函数参数，从而得到系统执行指令 以及 指令的参数值

## Useage：
1. 确保没有同名的内核模块已安装在内核
```sh
lsmod | grep xtw.ko
```

2. 如果发现同名模块，则先删除
```sh
rmmod xtw.ko
```

3. 安装本模块到内核
```sh
insmod xtw.ko
```

4. 敲入命令，该模块的输出是在内核环境下，因此需要通过输出内核输出信息来查看
```sh
dmesg 
```

![image](https://raw.githubusercontent.com/carterMgj/blog_img/master/git-readme/jprobe-1.png)

