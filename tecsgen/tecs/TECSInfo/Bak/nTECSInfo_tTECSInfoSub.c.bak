/*
 *   Copyright (C) 2008-2017 by TOPPERS Project
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
 *  @(#) $Id: nTECSInfo_tTECSInfoSub.c 2663 2017-07-08 23:09:53Z okuma-top $
 */

/* #[<PREAMBLE>]#
 * #[<...>]# から #[</...>]# で囲まれたコメントは編集しないでください
 * tecsmerge によるマージに使用されます
 *
 * 呼び口関数 #_TCPF_#
 * call port: cNamespaceInfo signature: nTECSInfo_sNamespaceInfo context:task
 *   ER             cNamespaceInfo_getName( char_t* name, int_t max_len );
 *   uint16_t       cNamespaceInfo_getNameLength( );
 *   uint32_t       cNamespaceInfo_getNNamespace( );
 *   ER             cNamespaceInfo_getNamespaceInfo( uint32_t ith, Descriptor( nTECSInfo_sNamespaceInfo )* des );
 *   uint32_t       cNamespaceInfo_getNSignature( );
 *   ER             cNamespaceInfo_getSignatureInfo( uint32_t ith, Descriptor( nTECSInfo_sSignatureInfo )* des );
 *   uint32_t       cNamespaceInfo_getNCelltype( );
 *   ER             cNamespaceInfo_getCelltypeInfo( uint32_t ith, Descriptor( nTECSInfo_sCelltypeInfo )* des );
 *   [ref_desc]
 *      Descriptor( nTECSInfo_sNamespaceInfo ) cNamespaceInfo_refer_to_descriptor();
 *      Descriptor( nTECSInfo_sNamespaceInfo ) cNamespaceInfo_ref_desc()      (same as above; abbreviated version);
 * call port: cNamespaceInfoTemp signature: nTECSInfo_sNamespaceInfo context:task optional:true
 *   bool_t     is_cNamespaceInfoTemp_joined()                     check if joined
 *   ER             cNamespaceInfoTemp_getName( char_t* name, int_t max_len );
 *   uint16_t       cNamespaceInfoTemp_getNameLength( );
 *   uint32_t       cNamespaceInfoTemp_getNNamespace( );
 *   ER             cNamespaceInfoTemp_getNamespaceInfo( uint32_t ith, Descriptor( nTECSInfo_sNamespaceInfo )* des );
 *   uint32_t       cNamespaceInfoTemp_getNSignature( );
 *   ER             cNamespaceInfoTemp_getSignatureInfo( uint32_t ith, Descriptor( nTECSInfo_sSignatureInfo )* des );
 *   uint32_t       cNamespaceInfoTemp_getNCelltype( );
 *   ER             cNamespaceInfoTemp_getCelltypeInfo( uint32_t ith, Descriptor( nTECSInfo_sCelltypeInfo )* des );
 *   [dynamic, optional]
 *      void           cNamespaceInfoTemp_set_descriptor( Descriptor( nTECSInfo_sNamespaceInfo ) desc );
 *      void           cNamespaceInfoTemp_unjoin(  );
 * call port: cRegionInfo signature: nTECSInfo_sRegionInfo context:task
 *   ER             cRegionInfo_getName( char_t* name, int_t max_len );
 *   uint16_t       cRegionInfo_getNameLength( );
 *   uint32_t       cRegionInfo_getNCell( );
 *   ER             cRegionInfo_getCellInfo( uint32_t ith, Descriptor( nTECSInfo_sCellInfo )* des );
 *   uint32_t       cRegionInfo_getNRegion( );
 *   ER             cRegionInfo_getRegionInfo( uint32_t ith, Descriptor( nTECSInfo_sRegionInfo )* des );
 *   [ref_desc]
 *      Descriptor( nTECSInfo_sRegionInfo ) cRegionInfo_refer_to_descriptor();
 *      Descriptor( nTECSInfo_sRegionInfo ) cRegionInfo_ref_desc()      (same as above; abbreviated version);
 * call port: cRegionInfoTemp signature: nTECSInfo_sRegionInfo context:task optional:true
 *   bool_t     is_cRegionInfoTemp_joined()                     check if joined
 *   ER             cRegionInfoTemp_getName( char_t* name, int_t max_len );
 *   uint16_t       cRegionInfoTemp_getNameLength( );
 *   uint32_t       cRegionInfoTemp_getNCell( );
 *   ER             cRegionInfoTemp_getCellInfo( uint32_t ith, Descriptor( nTECSInfo_sCellInfo )* des );
 *   uint32_t       cRegionInfoTemp_getNRegion( );
 *   ER             cRegionInfoTemp_getRegionInfo( uint32_t ith, Descriptor( nTECSInfo_sRegionInfo )* des );
 *   [dynamic, optional]
 *      void           cRegionInfoTemp_set_descriptor( Descriptor( nTECSInfo_sRegionInfo ) desc );
 *      void           cRegionInfoTemp_unjoin(  );
 *
 * #[</PREAMBLE>]# */

/* Put prototype declaration and/or variale definition here #_PAC_# */
#include "nTECSInfo_tTECSInfoSub_tecsgen.h"

#ifndef E_OK
#define	E_OK	0		/* success */
#define	E_ID	(-18)	/* illegal ID */
#endif

/* entry port function #_TEPF_# */
/* #[<ENTRY_PORT>]# eTECSInfo
 * entry port: eTECSInfo
 * signature:  nTECSInfo_sTECSInfo
 * context:    task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eTECSInfo_findNamespace
 * name:         eTECSInfo_findNamespace
 * global_name:  nTECSInfo_tTECSInfoSub_eTECSInfo_findNamespace
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
ER
eTECSInfo_findNamespace(const char_t* namespace_path, Descriptor( nTECSInfo_sNamespaceInfo )* NSdesc)
{
#define NAME_LEN  256
    const char_t  *p = namespace_path;
    char_t  name[ NAME_LEN + 1 ];
    char_t  name2[ NAME_LEN + 1 ];
    char_t  *p2;
    Descriptor( nTECSInfo_sNamespaceInfo ) desc;
    int     i;
    int     n;

    if( p[ 0 ] == ':' && p[ 1 ] == ':' ){
        p += 2;
    }
    desc = cNamespaceInfo_refer_to_descriptor(); // root name space
    cNamespaceInfoTemp_set_descriptor( desc );
    while( *p != '\0' ){
        p2 = name;
        for( i = 0; i < NAME_LEN; i++ ){
            if( *p == '\0' ||  *p == ':' ){
                *p2 = '\0';
                break;
            }
            *p2++ = *p++;
        }
        if( i == NAME_LEN )
            return E_NORES;

        n = cNamespaceInfoTemp_getNNamespace( );
        for( i = 0; i < n; i++ ){
            cNamespaceInfoTemp_getNamespaceInfo( i, &desc );
            cNamespaceInfoTemp_set_descriptor( desc );
            cNamespaceInfoTemp_getName( name2, NAME_LEN + 1 );
            if( strcmp( name, name2 ) == 0 )
                break;
        }
        if( i == n )
            return E_NOID;

        if( p[ 0 ] == ':' ){
            if( p[ 1 ] == ':' )
                p += 2;
            else
                return E_OBJ;
        }
    }
    *NSdesc = desc;
    return E_OK;
}

/* #[<ENTRY_FUNC>]# eTECSInfo_findRegion
 * name:         eTECSInfo_findRegion
 * global_name:  nTECSInfo_tTECSInfoSub_eTECSInfo_findRegion
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
ER
eTECSInfo_findRegion(const char_t* namespace_path, Descriptor( nTECSInfo_sRegionInfo )* RGNdesc)
{
    const char_t  *p = namespace_path;
    char_t  name[ NAME_LEN + 1 ];
    char_t  name2[ NAME_LEN + 1 ];
    char_t  *p2;
    Descriptor( nTECSInfo_sRegionInfo ) desc;
    int     i;
    int     n;

    if( p[ 0 ] == ':' && p[ 1 ] == ':' ){
        p += 2;
    }
    desc = cRegionInfo_refer_to_descriptor();
    cRegionInfoTemp_set_descriptor( desc );
    while( *p != '\0' ){
        p2 = name;
        for( i = 0; i < NAME_LEN; i++ ){
            if( *p == '\0' ||  *p == ':' ){
                *p2 = '\0';
                break;
            }
            *p2++ = *p++;
        }
        if( i == NAME_LEN )
            return E_NORES;

        n = cRegionInfoTemp_getNRegion( );
        for( i = 0; i < n; i++ ){
            cRegionInfoTemp_getRegionInfo( i, &desc );
            cRegionInfoTemp_set_descriptor( desc );
            cRegionInfoTemp_getName( name2, NAME_LEN + 1 );
            if( strcmp( name, name2 ) == 0 )
                break;
        }
        if( i == n )
            return E_NOID;

        if( p[ 0 ] == ':' ){
            if( p[ 1 ] == ':' )
                p += 2;
            else
                return E_OBJ;
        }
    }
    *RGNdesc = desc;
    return E_OK;
}

/* #[<ENTRY_FUNC>]# eTECSInfo_findSignature
 * name:         eTECSInfo_findSignature
 * global_name:  nTECSInfo_tTECSInfoSub_eTECSInfo_findSignature
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
ER
eTECSInfo_findSignature(const char_t* namespace_path, Descriptor( nTECSInfo_sSignatureInfo )* SIGdesc)
{
  return E_NOSPT;
}

/* #[<ENTRY_FUNC>]# eTECSInfo_findCelltype
 * name:         eTECSInfo_findCelltype
 * global_name:  nTECSInfo_tTECSInfoSub_eTECSInfo_findCelltype
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
ER
eTECSInfo_findCelltype(const char_t* namespace_path, Descriptor( nTECSInfo_sCelltypeInfo )* CTdesc)
{
  return E_NOSPT;
}

/* #[<ENTRY_FUNC>]# eTECSInfo_findCell
 * name:         eTECSInfo_findCell
 * global_name:  nTECSInfo_tTECSInfoSub_eTECSInfo_findCell
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
ER
eTECSInfo_findCell(const char_t* namespace_path, Descriptor( nTECSInfo_sCellInfo )* CELLdesc)
{
  return E_NOSPT;
}

/* #[<POSTAMBLE>]#
 *   これより下に非受け口関数を書きます
 * #[</POSTAMBLE>]#*/
