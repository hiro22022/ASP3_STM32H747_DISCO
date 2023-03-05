/*
 *  mruby => TECS brige
 *  
 *   Copyright (C) 2008-2012 by TOPPERS Project
 *--
 *   上記著作権者は，以下の(1)(4)の条件を満たす場合に限り，本ソフトウェ
 *   ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *   変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *   (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *       権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *       スコード中に含まれていること．
 *   (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *       用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *       者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *       の無保証規定を掲載すること．
 *   (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *       用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *       と．
 *     (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *         作権表示，この利用条件および下記の無保証規定を掲載すること．
 *     (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *         報告すること．
 *   (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *       害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *       また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *       由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *       免責すること．
 *  
 *   本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *   よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *   に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *   アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *   の責任を負わない．
 *  
 *   $Id: TECSPointer.c 1855 2012-07-29 02:44:07Z okuma-top $ 
 */
#include "mruby.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "mruby/string.h"
#include "TECSPointer.h"
#include "string.h"       // strnlen


// array element get & set function
GET_SET_BOOL( Bool,  bool_t )
GET_SET_INT( Int8,  int8_t )
GET_SET_INT( Int16, int16_t )
GET_SET_INT( Int32, int32_t )
GET_SET_INT( Int64, int64_t )
GET_SET_INT( Char,  char_t )
GET_SET_FLOAT( Double64, double64_t )
GET_SET_FLOAT( Float32, float32_t )
GET_SET_INT( Int,   int )
GET_SET_INT( Short, short )
GET_SET_INT( Long,  long )

//  define ruby class
POINTER_CLASS( Bool,  bool_t )
POINTER_CLASS( Int8,  int8_t )
POINTER_CLASS( Int16, int16_t )
POINTER_CLASS( Int32, int32_t )
POINTER_CLASS( Int64, int64_t )
POINTER_CLASS( Char,  char_t )
POINTER_CLASS( Double64, double64_t )
POINTER_CLASS( Float32, float32_t )
POINTER_CLASS( Int,   int )
POINTER_CLASS( Short, short )
POINTER_CLASS( Long,  long )

void
init_TECSPointer( mrb_state *mrb, struct RClass *TECS )
{
	struct RClass *c;

	(void)tecs_init_BoolPointer( mrb, TECS );
	(void)tecs_init_Int8Pointer( mrb, TECS );
	(void)tecs_init_Int16Pointer( mrb, TECS );
	(void)tecs_init_Int32Pointer( mrb, TECS );
	(void)tecs_init_Int64Pointer( mrb, TECS );
	c  =  tecs_init_CharPointer( mrb, TECS );
	(void)tecs_init_Double64Pointer( mrb, TECS );
	(void)tecs_init_Float32Pointer( mrb, TECS );
	(void)tecs_init_IntPointer( mrb, TECS );
	(void)tecs_init_ShortPointer( mrb, TECS );
	(void)tecs_init_LongPointer( mrb, TECS );

	mrb_define_method(mrb, c, "to_s", CharPointer_to_s, ARGS_NONE());
	mrb_define_method(mrb, c, "from_s", CharPointer_from_s, ARGS_REQ(1));
}
