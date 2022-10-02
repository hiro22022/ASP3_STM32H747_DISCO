# TOPPERS/ASP3 on STM32H747 Discovery

## 概要

TOPPERS/ASP3 を STM32H747 Discovery にポーティングする。
ポーティングは、以下の方針で行った。

 1. STM32F401RE のターゲット依存部、arch をベースに移植する
 2. 以下のものは、STM32CubeMX 生成コードを用いる
   * CPU クロックの初期化
   * タイマー
   * シリアル

幸いほとんどのアセンブラコードは、そのまま使用できる。Cortex-M4 と M7 では、命令セットが同じである。
なので、上記の3つを用意すればよい。

## Nucleo F401RE簡易パッケージ 

STM32F401RE に TOPPERS/ASP3 ポーティングしたものを使用した。
[TOPPERS/ASP3カーネル簡易パッケージのダウンロード](https://www.toppers.jp/asp3-e-download.html) にある
Nucleo F401RE簡易パッケージ [asp3_nucleo_f401re_gcc-20211228.zip](https://www.toppers.jp/download.cgi/asp3_nucleo_f401re_gcc-20211228.zip) をダウンロードして、ベースとした。

## STM32CubeMX 生成コード

CPUクロックの初期化、タイマー、シリアルのコードは STM32CubeMX の生成コードをベースにした。

ついでに LED も点灯できるように準備した。
LED が点灯できると、どこまでコード実行したか確認しやすいので、実際には、これを最初に用意した。
これも STM32CubeMX で生成できたようですが、私が生成したコードに含まれていなかったので、
自力で作ってみた。

## 現在のポーティング状態

とりあえず Cortex-M7 コアで TOPPERS/ASP3 が動作する。
Cortex-M4 コアでは、まだ STM32CubeMX で生成したコードを走らせておいた。

### Cortex-M7 用ビルド
 % cd obj_h747
 % make

asp.elf ができあがったら STM32CubeProgrammer を使用して書き込む。
書き込みアドレスを設定しなおす必要がないので、.bin より .elf を書き込んだ方が楽だし、安全である。

### Cortex-M4 用ビルド
 % cd target/stm32h747_discovery_m7/stm32hcube/CM4/Debug/
 % make STM32H747_CM4.elf

STM32H747_CM4.elf ができあがったら、STM32CubeProgrammer を使用して書き込む。

## 文鎮化 (bricked)

移植の途中、文鎮化は、2度経験している。

### ST-LINK error (DEV_TARGET_NOT_HALTED) で書き込めない

一回目の文鎮化は、クロック設定が動作範囲外だったようで、STM32CubeProgrammer の Download ボタンを押すと、
ST-LINK error (DEV_TARGET_NOT_HALTED) となってしまった。

これは Download ボタンを放すと同時に Reset ボタンを放すことで Download に成功し、脱出できた。
これは、一回では成功していなくて、何回かタイミングずらしながら試してうまくいった状況である。

### Error: No STM32 target found! で Connect に失敗する

二回目は、STM32CubeProgrammer の Connect ボタンを押すと Error: No STM32 target found! が発生して、Download の手前でエラーとなってしまった。
エラーが発生するものの電圧情報が表示されていたり、STM32H747 Discovery 内のストレージが　USB ドライブとして見えたり、tera term で USB Serial (COM3) の設定ができたりするので、電気的に死んでいるわけではなさそう。

この状態からの脱出は、STM32CubeProgrammer の Erasing & Programming で
 Full Chip Erase と Download File を automatic で実施して治ったもよう。

ここで注意する点として Full Chip Erase と Download File では、片方のコア用のプログラムしか書き込まれていないことだ。STM32H747 の場合、忘れずに、もう一つのコアのプログラムも書き込む必要がある。

 「もよう」と書いたのは何度か繰り返しているうちにうまくいったからだ。
途中で reset かけてみたり、USB コネクタの抜き差しを行ったりしているので、最終的にどうやったのがよかったかは、実はよくわかっていない。
何日も(期間としては3週間くらい) 復活できなかったので、もうあきらめようとしたらうまくいった。
（あきらめかけると、うまくいく、なんて経験は、よくありますね。一回目のときもそうだった）


この問題は、400MHz で動作させるように電圧を上げて、うまく動作させることができるようになって、
しばらくしたところで発生した。
先ほどの Erasing & Programming は、最初は 400MHz 動作のものを書き込みなおしていて問題が
解決していなかった。試しに、ずっと安定動作していた 320MHz のものに替えて書き込んだところ
正常にもどった。


一回目は、周波数を範囲外に設定したことで発生し、二回目は、電圧を範囲外に設定したことで問題が起きたようだ。

## HSEM (Hardware Semaphore) の TECS コンポーネント

コア間割込みをかける手段として、HSEM を TECS コンポーネントとして作成した。
tHSEM.cdl を参照。
このような資源は TECS コンポーネント化すると、きれいにいく。

sample1 のコマンドに p と P を追加してある。p は Cortex-M4 に HSEM1 をロックさせ、P はリリースさせる。リリースしたときに Cortex-M7 に割込みが入るようにしてある。それに合わせたメッセージが表示される。

## この先

まずは Cortex-M4 コアへ TOPPERS/ASP3 を移植する。

その後、TOPPERS/FMP3, TOPPERS/HRMP3 の移植を進めるつもりだ。

### キャッシュへの対応

Cortex-M7 コアでは、まだキャッシュ設定していない。
キャッシュを効かせる必要があるが、今後の課題になっている。
これも早めに対応しておきたい課題になる。

この CPU では、キャッシュやメモリのコヒーレンシ―を維持する機構がないようである。このため共有メモリはキャッシュなしにせざるを得ない。ただ、キャッシュから吐き出す機構があるので、うまく使えば効率を上げることは可能なようだ。

というようなこともあり、このプロセッサは、マルチコア構成だが、本来は TOPPERS/FMP3 などを動作させることを
意図されていないようだ。
性能を犠牲にせず TOPPERS/FMP3 を移植するのも課題になる。
