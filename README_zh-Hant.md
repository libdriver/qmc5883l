[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver QMC5883L

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/qmc5883l/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

QMC5883L是一款多晶片三軸磁感測器。 這種表面貼裝的小型晶片集成了帶有訊號調理ASIC的磁感測器，適用於無人機、機器人、移動和個人手持設備中的指南針、導航和遊戲等高精度應用。 QMC5883L基於霍尼韋爾AMR科技授權的最先進的高解析度磁阻科技。 與定制設計的16比特ADC ASIC一起，它具有低雜訊、高精度、低功耗、偏移消除和溫度補償的優點。 QMC5883L可實現1°至2°的羅盤航向精度。 I²C串列匯流排便於介面。

LibDriver QMC5883L是LibDriver推出的QMC5883L的全功能驅動，該驅動提供磁場讀取等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver QMC5883L的源文件。

/interface目錄包含了LibDriver QMC5883L與平台無關的IIC總線模板。

/test目錄包含了LibDriver QMC5883L驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver QMC5883L編程範例。

/doc目錄包含了LibDriver QMC5883L離線文檔。

/datasheet目錄包含了QMC5883L數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的IIC總線模板，完成指定平台的IIC總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/qmc5883l/index.html](https://www.libdriver.com/docs/qmc5883l/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。