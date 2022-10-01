# TOPPERS/ASP3 on STM32H747 Discovery

## 概要

TOPPERS/ASP3 を STM32H747 Discovery にポーティングする。
ポーティングは、以下の方針で行った。

 1. STM32F401RE のターゲット依存部、arch をベースに移植する
 2. 最低限必要なものは、以下のものである。
   1. CPU、タイマー、シリアルのクロックの初期化
   2. タイマー
   3. シリアル

## Nucleo F401RE簡易パッケージ 

STM32F401RE に TOPPERS/ASP3 ポーティングしたものを使用した。
[TOPPERS/ASP3カーネル簡易パッケージのダウンロード](https://www.toppers.jp/asp3-e-download.html#nucleo_note) にある
Nucleo F401RE簡易パッケージ [asp3_nucleo_f401re_gcc-20211228.zip](https://www.toppers.jp/download.cgi/asp3_nucleo_f401re_gcc-20211228.zip) をダウンロードして、ベースとした。

## STM32CubeMX 生成コード

クロック、タイマー、シリアルのコードは STM32CubeMX の生成コードをベースにした。

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

これは Download ボタンを放すと同時に Reset ボタンを押すことで Download に成功し、脱出できた。
これは、一回では成功していなくて、何回かタイミングずらしながら試してうまくいった状況である。

### Error: No STM32 target found! で Connect に失敗する

二回目は、STM32CubeProgrammer の Connect ボタンを押すと Error: No STM32 target found! が発生して、Download の手前でエラーとなってしまう。
エラーが発生するものの電圧情報が表示されていたり、STM32H747 Discovery 内のストレージが　USB ドライブとして見えたり、tera term で USB Serial (COM3) の設定ができたりするので、電気的に死んでいるわけではなさそう。

この状態からの脱出は、STM32CubeProgrammer の Erasing & Programming で
 Full Chip Erase と Download File を automatic で実施して治ったもよう。
これも何回か繰り返していて、途中で reset かけてみたり、USB コネクタの抜き差しを行ったりしている。

 「もよう」と書いたのは何度か繰り返しているうちにうまくいったからだ。
何日も(期間としては3週間くらい) 復活できなかったので、もうあきらめようとしたらうまくいった。
（あきらめかけると、うまくいく、なんて経験は、よくありますね。一回目のときもそうだった）

この問題は、400MHz で動作させるように電圧を上げて、うまく動作させることができるようになって、
しばらくしたところで発生した。
先ほどの Erasing & Programming は、最初は 400MHz 動作のものを書き込みなおしていて問題が
解決していなかった。試しに、ずっと安定動作していた 320MHz のものに替えて書き込んだところ
正常にもどった。

現象の現れ方が違っていたけど、根は一回目と同じだったかもしれない。
上記の方法で脱出したが、一回目と同様の方法でも脱出できていたかもしれない。

## HSEM (Hardware Semaphore) の TECS コンポーネント

コア間割込みをかける手段として、HSEM を TECS コンポーネントとして作成した。
tHSEM.cdl を参照。

このような資源は TECS コンポーネント化するときれいにいく。

## この先

まずは Cortex-M4 コアへ TOPPERS/ASP3 を移植する。

その後、TOPPERS/FMP3, TOPPERS/HRMP3 の移植を進めるつもりだ。

Cortex-M7 コアでは、まだキャッシュ設定していない。
キャッシュを効かせる必要があるが、今後の課題になっている。

このプロセッサは、マルチコア構成だが、本来は TOPPERS/FMP3 などを動作させることを
意図されていないようだ。
性能を犠牲にせず TOPPERS/FMP3 を移植するのも課題になる。


