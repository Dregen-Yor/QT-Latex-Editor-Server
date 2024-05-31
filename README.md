# 本项目为QT-Latex-Editor的后端

## 实现效果

从前端接受 .tex 文件数据,通过 latexmk 编译为pdf文件并保存到 Mariadb 数据库中,查询数据库中保存过的文件列表,获取某个文件的具体内容.

## 使用技术

- CMake
- Glog
- [facebook-proxygen](https://github.com/facebook/proxygen/)
- [mariadb 数据库](https://mariadb.org/)