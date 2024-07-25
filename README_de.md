[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver QMC5883L
[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/qmc5883l/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der QMC5883L ist ein dreiachsiger Magnetsensor mit mehreren Chips. Dieser oberflächenmontierbare, kleine Chip verfügt über integrierte Magnetsensoren mit Signalzustands-ASIC und ist für hochpräzise Anwendungen wie Kompass, Navigation und Gaming in Drohnen, Robotern, mobilen und persönlichen Handgeräten gedacht. Der QMC5883L basiert auf unserer hochmodernen, hochauflösenden, magnetoresistiven Technologie, die von Honeywell AMR Technology lizenziert wurde. Zusammen mit dem kundenspezifischen 16-Bit-ADC-ASIC bietet er die Vorteile von geringem Rauschen, hoher Genauigkeit, geringem Stromverbrauch, Offset-Auslöschung und Temperaturkompensation. QMC5883L ermöglicht eine Kompassrichtungsgenauigkeit von 1° bis 2°. Der serielle I²C-Bus ermöglicht eine einfache Schnittstelle.

LibDriver QMC5883L ist der voll funktionsfähige Treiber von QMC5883L, der von LibDriver eingeführt wurde. Er bietet Magnetfeldlesung und andere Funktionen. LibDriver ist MISRA-kompatibel.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver QMC5883L-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver QMC5883L IIC.

/test enthält den Testcode des LibDriver QMC5883L-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver QMC5883L-Beispielcode.

/doc enthält das LibDriver QMC5883L-Offlinedokument.

/Datenblatt enthält QMC5883L-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/qmc5883l/index.html](https://www.libdriver.com/docs/qmc5883l/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.