/*
 *		システムサービスのターゲット依存部（Mac OS X用）
 *
 *  システムサービスのターゲット依存部のヘッダファイル．システムサービ
 *  スのターゲット依存の設定は，できる限りコンポーネント記述ファイルで
 *  記述し，このファイルに記述するものは最小限とする．
 * 
 *  $Id: target_syssvc.h 1065 2018-11-20 11:09:50Z ertl-hiro $
 */

#ifndef TOPPERS_TARGET_SYSSVC_H
#define TOPPERS_TARGET_SYSSVC_H

/*
 *  ターゲットシステムのOS依存の定義
 */
#include "macosx.h"

#ifdef TOPPERS_OMIT_TECS

/*
 *  起動メッセージのターゲットシステム名
 */
#define TARGET_NAME	"Mac OS X"

/*
 *  システムログの低レベル出力のための文字出力
 *
 *  ターゲット依存の方法で，文字cを表示/出力/保存する．
 */
extern void	target_fput_log(char c);

/*
 *  シリアルポートの数
 */
#define TNUM_PORT		1		/* サポートするシリアルポートの数 */

/*
 *  システムログタスク関連の定数の定義
 */
#define LOGTASK_STACK_SIZE	SIGSTKSZ	/* スタック領域のサイズ */

#endif /* TOPPERS_OMIT_TECS */
#endif /* TOPPERS_TARGET_SYSSVC_H */
