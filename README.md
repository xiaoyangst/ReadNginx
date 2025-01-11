## 如何调试 Nginx

创建nginx运行时必要的目录和文件

Clion 调试过程中的产物都位于cmake-build-debug目录下，因此需要在这个目录下创建相关文件

```shell
cd /opt/third-party/nginx-1.22.1
mkdir -p cmake-build-debug/logs
/bin/cp -fr conf cmake-build-debug/
/bin/cp -fr html cmake-build-debug/
```

修改 Nginx 配置文件

```shell
cd /opt/third-party/nginx-1.22.1
vim cmake-build-debug/conf/nginx.conf
```

在文件开头新增如下两行内容，表示nginx处于前台运行并且是单进程模式工作

```shell
daemon off;
master_process off;
```



# 参考资料

[Nginx 源码分析（25篇）](https://blog.csdn.net/yangyin007/article/details/82777086)

[Clion 调试 Nginx](https://blog.csdn.net/nangonghen/article/details/133975239)