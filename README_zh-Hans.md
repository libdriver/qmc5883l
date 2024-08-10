[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver QMC5883L

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/qmc5883l/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

QMC5883L是一款多芯片三轴磁传感器。这种表面贴装的小型芯片集成了带有信号调理ASIC的磁传感器，适用于无人机、机器人、移动和个人手持设备中的指南针、导航和游戏等高精度应用。QMC5883L基于霍尼韦尔AMR技术授权的最先进的高分辨率磁阻技术。与定制设计的16位ADC ASIC一起，它具有低噪声、高精度、低功耗、偏移消除和温度补偿的优点。QMC5883L可实现1°至2°的罗盘航向精度。

LibDriver QMC5883L是LibDriver推出的QMC5883L的全功能驱动，该驱动提供磁场读取等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver QMC5883L的源文件。

/interface目录包含了LibDriver QMC5883L与平台无关的IIC总线模板。

/test目录包含了LibDriver QMC5883L驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver QMC5883L编程范例。

/doc目录包含了LibDriver QMC5883L离线文档。

/datasheet目录包含了QMC5883L数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的IIC总线模板，完成指定平台的IIC总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

#### example basic

```C
#include "driver_qmc5883l_basic.h"

uint8_t res;
uint8_t i;
float m_gauss[3];

res = qmc5883l_basic_init();
if (res != 0)
{
    return 1;
}

...


for (i = 0; i < 3; i++)
{
    qmc5883l_interface_delay_ms(1000);
    res = qmc5883l_basic_read((float *)m_gauss);
    if (res != 0)
    {
        (void)qmc5883l_basic_deinit();

        return 1;
    }
    qmc5883l_interface_debug_print("qmc5883l: x is %0.3f.\n", m_gauss[0]);
    qmc5883l_interface_debug_print("qmc5883l: y is %0.3f.\n", m_gauss[1]);
    qmc5883l_interface_debug_print("qmc5883l: z is %0.3f.\n", m_gauss[2]);
    
    ...
    
}

...

(void)qmc5883l_basic_deinit();

return 0;
```

### 文档

在线文档: [https://www.libdriver.com/docs/qmc5883l/index.html](https://www.libdriver.com/docs/qmc5883l/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。