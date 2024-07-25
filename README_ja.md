[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver QMC5883L

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/qmc5883l/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

QMC5883L は、マルチチップ 3 軸磁気センサーです。この表面実装型の小型チップには、信号調整 ASIC を備えた磁気センサーが統合されており、ドローン、ロボット、モバイル、個人用ハンドヘルド デバイスでのコンパス、ナビゲーション、ゲームなどの高精度アプリケーションを対象としています。QMC5883L は、Honeywell AMR テクノロジーからライセンスを受けた最先端の高解像度磁気抵抗技術に基づいています。カスタム設計された 16 ビット ADC ASIC とともに、低ノイズ、高精度、低消費電力、オフセット キャンセル、温度補正などの利点があります。QMC5883L は、1° ～ 2° のコンパス方位精度を実現します。I²C シリアル バスにより、簡単にインターフェイスできます。

LibDriver QMC5883L は、LibDriver がリリースした QMC5883L のフル機能ドライバです。磁場読み取りなどの機能を提供します。LibDriver は MISRA に準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver QMC5883Lのソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver QMC5883L用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver QMC5883Lドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver QMC5883Lプログラミング例が含まれています。

/ docディレクトリには、LibDriver QMC5883Lオフラインドキュメントが含まれています。

/ datasheetディレクトリには、QMC5883Lデータシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/qmc5883l/index.html](https://www.libdriver.com/docs/qmc5883l/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。