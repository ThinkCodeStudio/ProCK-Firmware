# ProCK-Firmware
这是可编程客制化键盘的固件, 是基于RT-Thread嵌入式实时系统开发的, 代码包括固件代码和bootloader

## 文件夹说明
| 文件夹 | 说明 |
| :----: | :---- |
| device | 设备驱动 |
| doc | 文档 |
| port | 芯片接口 |
| tools | 工具 |

***芯片接口:由于官方的驱动可能无法满足要求, 所以部分接口自己实现***

## 编译使用
### bootloader
在 `appconfig.h` 使能编译:
```C
/**     app         **/
#define BOOTLOADER
```

### app
在 `appconfig.h` 失能 **bootloader** 编译:
```C
/**     app         **/
// #define BOOTLOADER
```

修改连接脚本中的 ROM 地址, 地址偏移是 **APP_ADDR** 的位置

file: linkscripts/AT32F435ZM/link.lds
ROM(rx): 0x08000000 -> 0x08080000

施工中...

## 片上接口
[1] QSPI [flash]

## 软件库
[1] [agile_upgrade](https://github.com/loogg/agile_upgrade)
[2] [pikascript](http://pikascript.com/)

## 技术参考&使用
[1] [loogg/AT32F437_Boot](https://github.com/loogg/AT32F437_Boot)