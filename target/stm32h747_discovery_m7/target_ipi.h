/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 *
 *  Copyright (C) 2009-2020 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 *
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 *
 *  $Id: target_ipi.h 289 2021-08-05 14:44:10Z ertl-komori $
 */

/*
 * プロセッサ間割込みに関する定義（RP2040用）
 */

#ifndef TOPPERS_TARGET_IPI_H
#define TOPPERS_TARGET_IPI_H

#include "com_var.h"
#include "gen/tIPIUsingHSEM_cif.h"

#define IPINO_DISPATCH    0x0001 /* ディスパッチ要求 */
#define IPINO_EXT_KER     0x0002 /* カーネル終了要求 */
#define IPINO_SET_HRT_EVT 0x0004 /* 高分解能タイマ設定要求 */

#if 0
/*
 *  ディスパッチ要求プロセッサ間割込みの割込み番号
 */
#define INTNO_IPI_PRC1 (RP2040_SIO_PROC0_IRQn + 16)
#define INTNO_IPI_PRC2 (RP2040_SIO_PROC1_IRQn + 16)

#define INHNO_IPI_PRC1 ((1 << 16) | INTNO_IPI_PRC1)
#define INHNO_IPI_PRC2 ((2 << 16) | INTNO_IPI_PRC2)

/*
 *  プロセッサ間割込みの割込み優先度
 */
#define INTPRI_IPI (TMAX_INTPRI - 1)
#endif /* 0 */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  ディスパッチ要求プロセッサ間割込みの発行
 */
Inline void request_dispatch_prc(uint_t prcid)
{
    if(is_M7Core()){
        __disable_irq();
       COM_IPI_7to4 |= IPINO_DISPATCH;;
       rProcessor1Migratable_IPI7_eIPISend_sendIPI( HSEM_InterCoreInt_CM7_to_CM4 );
       __enable_irq();
    }
    else{
        __disable_irq();
       COM_IPI_4to7 |= IPINO_DISPATCH;;
       rProcessor1Migratable_IPI7_eIPISend_sendIPI( HSEM_InterCoreInt_CM4_to_CM7 );
       __enable_irq();
    }
}

/*
 *  カーネル終了要求プロセッサ間割込みの発行
 */
Inline void request_ext_ker(uint_t prcid)
{
    if(is_M7Core()){
        __disable_irq();
       COM_IPI_7to4 |= IPINO_EXT_KER;;
       rProcessor1Migratable_IPI7_eIPISend_sendIPI( HSEM_InterCoreInt_CM7_to_CM4 );
       __enable_irq();
    }
    else{
        __disable_irq();
       COM_IPI_4to7 |= IPINO_EXT_KER;;
       rProcessor1Migratable_IPI7_eIPISend_sendIPI( HSEM_InterCoreInt_CM4_to_CM7 );
       __enable_irq();
    }
}

/*
 *  高分解能タイマ設定要求プロセッサ間割込みの発行
 */
Inline void request_set_hrt_event(uint_t prcid)
{
    if(is_M7Core()){
        __disable_irq();
       COM_IPI_7to4 |= IPINO_SET_HRT_EVT;;
       rProcessor1Migratable_IPI7_eIPISend_sendIPI( HSEM_InterCoreInt_CM7_to_CM4 );
       __enable_irq();
    }
    else{
        __disable_irq();
       COM_IPI_4to7 |= IPINO_SET_HRT_EVT;;
       rProcessor1Migratable_IPI7_eIPISend_sendIPI( HSEM_InterCoreInt_CM4_to_CM7 );
       __enable_irq();
    }
}

extern void chip_ipi_initialize(intptr_t exinf);
extern void _kernel_ipi_irq_handler(void);

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_TARGET_IPI_H */
