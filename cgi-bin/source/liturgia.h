/***************************************************************/
/*                                                             */
/* liturgia.h                                                  */
/* (c)1999-2013 | Juraj Vid�ky | videky@breviar.sk             */
/*                                                             */
/* description | obsahuje zakladne vecicky pre liturgiu hodin  */
/* document history                                            */
/*   01/11/1999A.D. | created                                  */
/*   01/02/2000A.D. | modified                                 */
/*   18/02/2000A.D. | trosku prekopane | stringove kontanty su */
/*                    tu iba deklarovane; definovane v hodin.h */
/*   06/09/2001A.D. | tento popis                              */
/*   2003-07-02a.D. | pridana LINK_DEN_MESIAC_ROK_PRESTUP      */
/*                    kvoli prestupnym rokom (iny _global_link)*/
/*   2003-07-15a.D. | rozne definicie pre modlitbu cez den     */
/*   2003-07-15a.D. | odstraneny #include "mybase.h"           */
/*   2003-08-06a.D. | rozne definicie pre posvatne citanie     */
/*   2003-08-07a.D. | pridana void _init_dm co nastavi dummy   */
/*   2003-08-11a.D. | -Wall upozornila na / * within comments  */
/*   2003-08-11a.D. | void _init_dm zapoznamkovana             */
/*   2003-08-13a.D. | pridane logy pre modlitbu cez den        */
/*                  - pridane MODL_CEZ_DEN_VSETKY              */
/*   2003-08-21a.D. | definicie pre posvatne citania           */
/*   2003-11-20a.D. | definicie pre posvatne citania zmenene   */
/*   2004-04-28a.D. | MAX_STR_AF_FILE zmenene na 16            */
/*   2004-08-14a.D. | char zmeneny na unsigned (_nedelne_p...) */
/*   2005-03-27a.D. | CHAR_MODL_* z funkcie pismenko_modlitby  */
/*   2005-07-27a.D. | pridan� nazov_slavenia_lokal[]           */
/*   2005-08-05a.D. | pridan� zvazok_OBD[]                     */
/*   2005-11-11a.D. | Doplnen� parametre pre Te Deum           */
/*   2006-02-07a.D. | ZALTAR_... pre funkciu zaltar_zvazok();  */
/*   2006-07-11a.D. | prv� kroky k jazykov�m mut�ci�m          */
/*   2006-08-01a.D. | zmenen� defin�cie kon�t�nt (jaz.mut�cie) */
/*   2006-08-07a.D. | pridan� sv. mu�ov/�ien, �o �ili v man�.  */
/*   2006-08-18a.D. | zmena int na short int (sta�� 32tis.)    */
/*   2006-08-19a.D. | pridanie liturgickej farby               */
/*   2006-10-11a.D. | pre invitat�rium a komplet�rium          */
/*   2006-10-13a.D. | jazykovo z�visl� je aj nazov_Modlitby    */
/*   2006-12-12a.D. | doplnenie latin�iny (la)                 */
/*   2007-06-01a.D. | niektor� definy presunut� do mydefs.h    */
/*   2007-06-28a.D. | doplnen�: PARAM_TEDEUM_BEGIN aj _END     */
/*   2007-10-02a.D. | doplnen�: PARAM_SKRY_ANTIFONU_BEGIN/END  */
/*                  - tie� PARAM_ANTIFONA1x a PARAM_ANTIFONA3x */
/*   2008-01-03a.D. | doplnen� text_DRUHA_NEDELA_PO_NAR_PANA[] */
/*   2008-01-05a.D. | doplnen� text_PO_POPOLCOVEJ_STREDE[]     */
/*                  - a tie� text_V_OKTAVE_NARODENIA[]         */
/*   2008-01-23a.D. | opraven� pole kon�t�nt zvazok_breviara[] */
/*   2008-06-24a.D. | doplnen� LOKAL_SLAV_SPIS_BA_PATRON       */
/*   2008-08-15a.D. | pridan� �al�� "jazyk" (cz-op)            */
/*   2009-01-29a.D. | pridan� �al�� jazyk - ma�ar�ina (hu)     */
/*   2009-04-08a.D. | zakon�enie modlitby trojak� (kr�tke/dlh�)*/
/*   2009-05-15a.D. | pridan� text_PRO_OP[]                    */
/*   2009-12-14a.D. | zakon�enie modlitby s mal�m p�smenkom na za�iatku */
/*   2010-03-16a.D. | doplnen� LOKAL_SLAV_BRATISLAVA           */
/*   2010-05-17a.D. | pridan� niektor� ma�arsk� sl�venia       */
/*   2010-05-21a.D. | doplnen�: PARAM_SPOMIENKA_PRIVILEG_BEGIN/END */
/*   2010-08-03a.D. | do �trukt�ry "dm" pridan� premenn� pre   */
/*                    �pecifik�ciu, o ak� kalend�r ide:        */
/*                    v�eobecn� danej cirkevnej provincie      */
/*                    alebo nejak� reho�n� a pod.              */
/*   2010-10-11a.D. | pridan� nazov_kalendara_long[]           */
/*   2011-01-25a.D. | premenovan� niektor� HTML s�bory         */
/*   2011-04-13a.D. | re�azcov� funkcie equals() presunut�     */
/*   2011-05-11a.D. | vytvoren�: _vytvor_string_z_datumu()     */
/*   2011-10-07a.D. | vymenen� kon�tanty RCH <-> posv.��t.     */
/*   2013-01-29a.D. | option 5 pre alternat�vy v textoch       */
/*                                                             */
/*                                                             */
/***************************************************************/

#include "vstudio.h"

#ifndef __LITURGIA_H_
#define __LITURGIA_H_

#include "mysystem.h"
#include "mysysdef.h"
#include "mydefs.h"
#include "mylog.h"
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#define MENO_SVIATKU 250

// 2006-07-11: Pridan� kv�li jazykov�m mut�ci�m 
// 2006-12-12: Pridan� latin�ina, k�dy s� pod�a ISO 639-1 (a� na �e�tinu)
// 2008-08-15: Pridan� "dominik�nska �e�tina"; presunut� sem bezprostredne za defin�ciu POCET_JAZYKOV
// 2009-01-29: pridan� ma�ar�ina
#define JAZYK_SK	0
#define JAZYK_CZ	1
#define JAZYK_EN	2
#define JAZYK_LA    3
#define JAZYK_UNDEF 4
#define JAZYK_CZ_OP 5
#define JAZYK_HU    6

// 2011-05-12: form�ty vypisovania d�tumu, kv�li ma�ar�ine, angli�tine...
#define FORMAT_DATUMU_DEN_MESIAC_ROK 0 // DD. MM RRRR
#define FORMAT_DATUMU_MESIAC_DEN_ROK 1 // MM DD RRRR
#define FORMAT_DATUMU_ROK_MESIAC_DEN 2 // RRRR. MM DD

extern const short int format_datumu[POCET_JAZYKOV + 1];

// 2008-08-15: Pridan� POCET_CSS, aby mohol by� "doln�k" (CSS_UNDEF) hodnota 0
#define POCET_CSS	11
// 2006-08-08: Pridan� kv�li r�znym css-k�m 
// 2009-04-02: pridan� historick� css-k�
// 2010-02-25: pridan� css pre webstr�nky http://www.jm-krize.cz/
// 2011-05-24: pridan� "inverzn�" �t�l pre mobiln� zariadenia (�ierne pozadie, biely text)
// 2011-07-26: pridan� vzh�ad ako http://www.kbs.sk
#define CSS_UNDEF				0
#define CSS_breviar_sk			1
#define CSS_breviar_sk_invert	2
#define CSS_kbd_sk				3
#define CSS_ebreviar_cz			4
#define CSS_breviar_cz_op		5
#define CSS_breviar_hist_2003	6
#define CSS_breviar_hist_2005	7
#define CSS_breviar_hist_2007	8
#define CSS_breviar_hist_2008	9
#define CSS_jm_krize_cz			10
#define CSS_kbs_sk				11

#define	POCET_FONTOV	9

// 2011-05-06: jednotliv� fonty na v�ber v drop-down liste
#define FONT_UNDEF		0
#define FONT_CSS		1
#define FONT_CHECKBOX	2
#define FONT_CAMBRIA    3
#define FONT_CANDARA	4
#define FONT_GEORGIA	5
#define FONT_TAHOMA		6
#define FONT_HELVETICA	7
#define FONT_SERIF		8
#define FONT_SANS_SERIF	9

#define	POCET_FONT_SIZE	8

// 2011-05-13: jednotliv� fonty na v�ber v drop-down liste
#define FONT_SIZE_UNDEF		0
#define FONT_SIZE_CSS		1 // inherit
#define FONT_SIZE_XX_SMALL	2
#define FONT_SIZE_X_SMALL 	3
#define FONT_SIZE_SMALL   	4
#define FONT_SIZE_MEDIUM  	5
#define FONT_SIZE_LARGE   	6
#define FONT_SIZE_X_LARGE 	7
#define FONT_SIZE_XX_LARGE	8

// 2013-01-29: alternat�vy pre niektor� �asti modlitby
#define BIT_ALT_HYMNUS                  1
#define BIT_ALT_ANTCHVAL                2
#define BIT_ALT_LEN_DOPLNKOVA_PSALMODIA 4
#define BIT_ALT_DOPLNK_PSALM_122_129    8
#define BIT_ALT_DOPLNK_PSALM_127_131   16
#define BIT_ALT_DOPLNK_PSALM_126_129   32
#define BIT_ALT_HYMNUS_VN              64

// nasledovne 2 definovane 2003-08-13; zmenene 2004-04-28 (12->16)
#define MAX_STR_AF_FILE   16
#define MAX_STR_AF_ANCHOR 23
struct _anchor_and_file{
	char file[MAX_STR_AF_FILE];
	char anchor[MAX_STR_AF_ANCHOR];
};
typedef struct _anchor_and_file _struct_anchor_and_file;

// definicie pre ranne chvaly a vespery
#define rchvalospev  zalm2
#define vchvalospev  zalm3
#define magnifikat   benediktus

// definicie pre posvatne citania upravene 2003-08-21 a opatovne 2003-11-20

// vers po psalmodii pred citaniami - je kresponz

// prve  citanie aj s responzoriom za nim
// #define	citanie1	kcitanie

// druhe citanie aj s responzoriom za nim
// #define	citanie2	benediktus

// prosby ostavaju pre posvatne citania nedefinovane

struct tmodlitba1{
	short int alternativy; // bitov� komponenty hovoria, ktor� �asti m��u ma� alternat�vy
	_struct_anchor_and_file popis     ;
	_struct_anchor_and_file hymnus    ;
	_struct_anchor_and_file antifona1 ;
	_struct_anchor_and_file zalm1     ;
	_struct_anchor_and_file antifona2 ;
	_struct_anchor_and_file zalm2     ;
	_struct_anchor_and_file antifona3 ;
	_struct_anchor_and_file zalm3     ;
	_struct_anchor_and_file kcitanie  ;
	_struct_anchor_and_file kresponz  ; 
	_struct_anchor_and_file benediktus; // antifona na benediktus/magnifikat
	_struct_anchor_and_file prosby    ; // pre posvatne citanie nedefinovane; 2011-03-16: "zneu�it�" (pou�it�) pre hagiografick� ��tanie (�ubovo�nej) spomienky sv�tca v p�ste
	_struct_anchor_and_file modlitba  ;
	_struct_anchor_and_file ant_spomprivileg; // 2010-05-21: pridan� kv�li spomienkam a �ubovo�n�m spomienkam v p�stnom obdob� (zobrazenie po modlitbe d�a p�stnej f�rie) // 2012-02-09: zov�eobecnen� v zmysle VSLH �. 238 (Spomienky pripadaj�ce na privilegovan� dni)
	_struct_anchor_and_file modlitba_spomprivileg; // 2010-05-21: pridan� kv�li spomienkam a �ubovo�n�m spomienkam v p�stnom obdob� (zobrazenie po modlitbe d�a p�stnej f�rie) // 2012-02-09: zov�eobecnen� v zmysle VSLH �. 238 (Spomienky pripadaj�ce na privilegovan� dni)
};
typedef struct tmodlitba1 _type_ranne_chvaly;
typedef struct tmodlitba1 _type_vespery;
typedef struct tmodlitba1 _type_1vespery;
// typedef struct tmodlitba1 _type_posv_citanie;

struct tmodlitba2{
	short int alternativy; // bitov� komponenty hovoria, ktor� �asti m��u ma� alternat�vy
	_struct_anchor_and_file popis     ;
	_struct_anchor_and_file hymnus    ;
	_struct_anchor_and_file antifona1 ;
	_struct_anchor_and_file zalm1     ;
	_struct_anchor_and_file antifona2 ;
	_struct_anchor_and_file zalm2     ;
	_struct_anchor_and_file antifona3 ;
	_struct_anchor_and_file zalm3     ;
	_struct_anchor_and_file kcitanie  ;
	_struct_anchor_and_file kresponz  ;
	_struct_anchor_and_file modlitba  ;
};
typedef struct tmodlitba2 _type_cez_den_9;
typedef struct tmodlitba2 _type_cez_den_12;
typedef struct tmodlitba2 _type_cez_den_3;
// pre jednoduchsiu orientaciu pridane 2003-07-15
typedef struct tmodlitba2 _type_cez_den_pred;
typedef struct tmodlitba2 _type_cez_den_na;
typedef struct tmodlitba2 _type_cez_den_po;

struct tmodlitba3{
	short int alternativy; // bitov� komponenty hovoria, ktor� �asti m��u ma� alternat�vy
	short int pocet_zalmov            ; // pridan� 2006-10-18; niekedy s� a� 2 �almy
	_struct_anchor_and_file popis     ; // pridan� 2006-10-11; zru�en� antifona2, zalm2 a modlitba
	_struct_anchor_and_file hymnus    ;
	_struct_anchor_and_file antifona1 ;
	_struct_anchor_and_file zalm1     ;
	_struct_anchor_and_file antifona2 ; // pridan� 2006-10-17; niekedy s� a� 2 �almy
	_struct_anchor_and_file zalm2     ;
	_struct_anchor_and_file kcitanie  ;
	_struct_anchor_and_file kresponz  ;
	_struct_anchor_and_file nunc_dimittis; // antif�na na nunc dimittis; pridan� 2013-04-03 (kv�li OPRAEM, 08dec)
	_struct_anchor_and_file modlitba  ;
};
typedef struct tmodlitba3 _type_kompletorium;
typedef struct tmodlitba3 _type_1kompletorium;

struct tmodlitba4{
	_struct_anchor_and_file popis     ;
	_struct_anchor_and_file antifona1 ;
	_struct_anchor_and_file zalm1     ;
};
typedef struct tmodlitba4 _type_invitatorium;

// 2011-03-25: pre posv�tn� ��tanie kv�li sl�veniu vig�li� nov� typ
struct tmodlitba5{
	short int alternativy; // bitov� komponenty hovoria, ktor� �asti m��u ma� alternat�vy
	_struct_anchor_and_file popis     ;
	_struct_anchor_and_file hymnus    ;
	_struct_anchor_and_file antifona1 ;
	_struct_anchor_and_file zalm1     ;
	_struct_anchor_and_file antifona2 ;
	_struct_anchor_and_file zalm2     ;
	_struct_anchor_and_file antifona3 ;
	_struct_anchor_and_file zalm3     ;
	_struct_anchor_and_file kresponz  ; 
	_struct_anchor_and_file citanie1  ; // 1. citanie pre posvatne citanie
	_struct_anchor_and_file citanie2  ; // 2. citanie pre posvatne citanie
	_struct_anchor_and_file citanie_spomprivileg ; // 2011-03-16: "zneu�it�" (pou�it�) pre hagiografick� ��tanie (�ubovo�nej) spomienky sv�tca v p�ste; 2011-03-25: nov� typ -> nov� meno
	_struct_anchor_and_file ant_chval ; // vig�lia: antif�na pre chv�lospevy
	_struct_anchor_and_file chval1    ; // vig�lia: chv�lospev I
	_struct_anchor_and_file chval2    ; // vig�lia: chv�lospev II
	_struct_anchor_and_file chval3    ; // vig�lia: chv�lospev III
	_struct_anchor_and_file evanjelium; // vig�lia: evanjelium
	_struct_anchor_and_file modlitba  ;
};
typedef struct tmodlitba5 _type_posv_citanie;

struct den_mesiac{ // takto povodne vyzerala struct dm
	short int den;        // cislo dna mesiaca (1--31)
	short int mesiac;     // cislo mesiaca (1--12) - in�� ako je potrebn� pre v��inu pol�, kde je mesiac 0--11
};
typedef struct den_mesiac _struct_den_mesiac;

#define POCET_MODLITIEB         14 // 2006-08-02: nepou��valo sa; upraven� na 13 (z p�vodn�ch 8); 2011-10-03: upraven� na 14 kv�li MODL_VSETKY
// modlitby; 2011-10-05: vymenen� rann� chv�ly a posv�tn� ��tanie, re�pektujeme usporiadanie tla�enej LH; 2011-10-07: vymenen� kon�tanty RCH<->posv.��t.
#define MODL_INVITATORIUM       0
#define MODL_POSV_CITANIE       1
#define MODL_RANNE_CHVALY       2
#define MODL_CEZ_DEN_9          3
#define MODL_CEZ_DEN_12         4
#define MODL_CEZ_DEN_3          5
#define MODL_VESPERY            6
#define MODL_KOMPLETORIUM       7
#define MODL_NEURCENA           8
// dalsie, iba docasne modlitby
#define MODL_PRVE_VESPERY       9
#define MODL_PRVE_KOMPLETORIUM  10
#define MODL_DRUHE_VESPERY      11
#define MODL_DRUHE_KOMPLETORIUM 12
// formular s detailami ohladom generovania modlitby -- 2011-10-03: odstaven�
#define MODL_DETAILY            13
// 2011-10-03: pridan� pokusne
#define MODL_VSETKY             14
// pre jednoduchsiu orientaciu pridane 2003-07-15
#define MODL_PREDPOLUDNIM       3
#define MODL_NAPOLUDNIE         4
#define MODL_POPOLUDNI          5
// pre modlitbu cez den kvoli zaltaru (psalmodii) rovnake, pridane 2003-08-13
#define MODL_CEZ_DEN_VSETKY     20

// 2007-12-05: doplnen� kv�li modlitbe komplet�ria, funkcia _set_kompletorium_nedela()
#define MODL_KOMPLETORIUM_NEDELNA	0
#define MODL_KOMPLETORIUM_SLAVNOSTI	1
#define MODL_KOMPLETORIUM_TROJDNIE	2

// ... a stringy pre ne
#ifdef LONG_PARAM_NAMES
	#define		STR_MODL_INVITATORIUM	"MODL_INVITATORIUM"
	#define		STR_MODL_POSV_CITANIE	"MODL_POSV_CITANIE"
	#define		STR_MODL_RANNE_CHVALY	"MODL_RANNE_CHVALY"
	#define		STR_MODL_VESPERY		"MODL_VESPERY"
	#define		STR_MODL_PREDPOLUDNIM	"MODL_PREDPOLUDNIM"
	#define		STR_MODL_NAPOLUDNIE		"MODL_NAPOLUDNIE"
	#define		STR_MODL_POPOLUDNI		"MODL_POPOLUDNI"
	#define		STR_MODL_DETAILY		"MODL_DETAILY"
	#define		STR_MODL_KOMPLETORIUM	"MODL_KOMPLETORIUM"
	#define		STR_MODL_PRVE_VESPERY	"MODL_PRVE_VESPERY"
	#define		STR_MODL_PRVE_KOMPLETORIUM	"MODL_PRVE_KOMPLETORIUM"
	#define		STR_MODL_VSETKY            "MODL_VSETKY"
#else
	#define		STR_MODL_INVITATORIUM      "mi"
	#define		STR_MODL_POSV_CITANIE	   "mpc"
	#define		STR_MODL_RANNE_CHVALY      "mrch"
	#define		STR_MODL_VESPERY           "mv"
	#define		STR_MODL_PREDPOLUDNIM      "mpred"
	#define		STR_MODL_NAPOLUDNIE        "mna"
	#define		STR_MODL_POPOLUDNI         "mpo"
	#define		STR_MODL_DETAILY           "mdet"
	#define		STR_MODL_KOMPLETORIUM      "mk"
	#define		STR_MODL_PRVE_VESPERY      "mpv"
	#define		STR_MODL_PRVE_KOMPLETORIUM "mpk"
	#define		STR_MODL_VSETKY            "*"
#endif

// 2005-03-27: Vlozene do definicnej casti z funkcie dbzaltar.cpp::pismenko_modlitby()
#define CHAR_MODL_INVITATORIUM       'i'
#define CHAR_MODL_POSV_CITANIE       'c'
#define CHAR_MODL_RANNE_CHVALY       'r'
#define CHAR_MODL_CEZ_DEN_9          '9'
#define CHAR_MODL_CEZ_DEN_12         '2'
#define CHAR_MODL_CEZ_DEN_3          '3'
#define CHAR_MODL_VESPERY            'v'
#define CHAR_MODL_KOMPLETORIUM       'k'
#define CHAR_MODL_NEURCENA           '_' // toto by sa nemalo
#define CHAR_MODL_PRVE_VESPERY       '1'
#define CHAR_MODL_PRVE_KOMPLETORIUM  'p'
#define CHAR_MODL_DRUHE_VESPERY      'w' // toto by sa nemalo
#define CHAR_MODL_DRUHE_KOMPLETORIUM 'm' // toto by sa nemalo
// #define CHAR_MODL_CEZ_DEN_VSETKY     'd' // 2005-03-27: pridan�
#define CHAR_MODL_VSETKY             '*' // 2011-10-03: pridan� pokusne

// 2008-04-09: doplnen� pre batch generovanie modlitieb
extern const char char_modlitby[POCET_MODLITIEB + 1];
extern const char *str_modlitby[POCET_MODLITIEB + 1];

//extern const char *nazov_modlitby[];
extern const char *nazov_modlitby_jazyk[POCET_MODLITIEB + 1][POCET_JAZYKOV + 1];
#define		nazov_modlitby(a)	nazov_modlitby_jazyk[a][_global_jazyk]

//extern const char *nazov_Modlitby[];
extern const char *nazov_Modlitby_jazyk[POCET_MODLITIEB + 1][POCET_JAZYKOV + 1];
#define		nazov_Modlitby(a)	nazov_Modlitby_jazyk[a][_global_jazyk]

//extern const char *nazov_MODLITBY[];
extern const char *nazov_MODLITBY_jazyk[POCET_MODLITIEB + 1][POCET_JAZYKOV + 1];
#define		nazov_MODLITBY(a)	nazov_MODLITBY_jazyk[a][_global_jazyk]

// ... a file templates (suborove vzory) pre modlitby | 2011-01-25: premenovan� (aby mali spolo�n� prefix)
#define TEMPLAT_INVITATORIUM     "m_invitat.htm"
#define TEMPLAT_POSV_CITANIE     "m_posvcit.htm"
#define TEMPLAT_RANNE_CHVALY     "m_rchvaly.htm"
#define TEMPLAT_CEZ_DEN_9        "m_predpol.htm"
#define TEMPLAT_CEZ_DEN_12       "m_napol.htm"
#define TEMPLAT_CEZ_DEN_3        "m_popol.htm"
#define TEMPLAT_VESPERY          "m_vespery.htm"
#define TEMPLAT_KOMPLETORIUM     "m_komplet.htm"
#define TEMPLAT_NEURCENY         "" // 2011-10-03: doplnen� kv�li MODL_VSETKY

// pridan� 2006-10-24 pre komplet�rium
#define nazov_obd_KOMPLETORIUM   "cezrok_k.htm"

extern const char *TEMPLAT[POCET_MODLITIEB + 1];

// znaky, ktore znacia (pre interpretovanie templatu) zaciatok a koniec klucoveho slova
#define CHAR_KEYWORD_BEGIN   '{'
#define CHAR_KEYWORD_END     '}'
#define CHAR_KEYWORD_DIVIDER ':'
/*
#define CHAR_KEYWORD2_BEGIN  '<'
#define CHAR_KEYWORD2_END    '>'
*/

// znak '_' pou��vame ako z�stupn� pre nezlomite�n� medzeru (exportuje sa ako HTML_NONBREAKING_SPACE == "&nbsp;" definovan� v mydefs.h) 
// 2011-05-02: pridan�; nevad�, �e je duplicita s UNDERSCORE resp. CHAR_MODL_NEURCENA 
#define CHAR_NONBREAKING_SPACE '_'

// include parameters (parametre v inkludovanych suboroch)
#define INCLUDE_BEGIN   "BEGIN" // zaciatok
#define INCLUDE_END     "END"   // koniec

// parameter identifiers
#define PARAM_POPIS         "POPIS"
#define PARAM_HYMNUS        "HYMNUS"
#define PARAM_ANTIFONA1     "ANTIFONA1"
#define PARAM_ANTIFONA2     "ANTIFONA2"
#define PARAM_ANTIFONA3     "ANTIFONA3"
#define PARAM_ZALM1         "ZALM1"
#define PARAM_ZALM2         "ZALM2"
#define PARAM_ZALM3         "ZALM3"
#define PARAM_ANTRCHVAL     "ANTRCHVAL" // vlastne ANTIFONA2
#define PARAM_ANTVCHVAL     "ANTVCHVAL" // vlastne ANTIFONA3
#define PARAM_RCHVALOSPEV   "RCHVALOSPEV" // vlastne ZALM2
#define PARAM_VCHVALOSPEV   "VCHVALOSPEV" // vlastne ZALM3
#define PARAM_KCITANIE      "KCITANIE"
#define PARAM_KRESPONZ      "KRESPONZ"
#define PARAM_MAGNIFIKAT    "MAGNIFIKAT" // antif�na na Magnifikat
#define PARAM_BENEDIKTUS    "BENEDIKTUS" // antif�na na Benediktus
#define PARAM_NUNC_DIMITTIS "NUNCDIMITTIS" // antif�na na Nunc dimittis
#define PARAM_PROSBY        "PROSBY"
#define PARAM_MODLITBA      "MODLITBA"
// pridane 2003-08-06, upravene 2003-08-21
#define PARAM_CITANIE1      "CITANIE1" // vlastne KCITANIE
#define PARAM_CITANIE2      "CITANIE2" // vlastne BENEDIKTUS
// 2007-10-02: pridan� kv�li rovnak�m antif�nam pre modlitbu cez de�
#define PARAM_ANTIFONA1x    "ANTIFONA1_DRUHA"
#define PARAM_ANTIFONA3x    "ANTIFONA3_PRVA"
// 2008-04-03: pridan� kv�li komplet�riu vo ve�kono�nom obdob�, �i pri druhej antif�ne zobrazi� dvojku alebo nie
#define PARAM_ANTIFONA1k    "ANTIFONA1_KOMPLET"
#define PARAM_ANTIFONA2k    "ANTIFONA2_KOMPLET"
// 2010-05-21: pridan� kv�li spomienkam a �ubovo�n�m spomienkam v p�stnom obdob� (zobrazenie po modlitbe d�a p�stnej f�rie)
// 2012-02-09: zov�eobecnen� v zmysle VSLH �. 238 (Spomienky pripadaj�ce na privilegovan� dni)
#define PARAM_ANT_SPOMPRIVILEG  "ANT_SPOMPRIVILEG"
#define PARAM_MODL_SPOMPRIVILEG "MODL_SPOMPRIVILEG"
// 2011-03-16: pridan� kv�li spomienkam a �ubovo�n�m spomienkam v p�stnom obdob� (zobrazenie po 2. ��tan� v posv. ��tan�)
// 2012-02-09: zov�eobecnen� v zmysle VSLH �. 238 (Spomienky pripadaj�ce na privilegovan� dni)
#define PARAM_CITANIE2_SPOMPRIVILEG "CITANIE2_SPOMPRIVILEG"
// 2011-07-03: pridan� kv�li navig�cii v modlitbe
#define PARAM_NAVIGACIA     "NAVIGACIA"
// 2011-10-04: pridan� nadpis v modlitbe
#define PARAM_NADPIS        "NADPIS"
// 2012-04-03: pridan� podnadpis v modlitbe (napr. pre MCD: doplnkov� psalm�dia)
#define PARAM_PODNADPIS     "PODNADPIS"
// 2012-08-16: pridan� �al�� podnadpis v modlitbe (rubrika pre spolo�n� �as�)
#define PARAM_SPOL_CAST     "SPOL_CAST"
// 2012-05-24: doplnen� -- pred�en� sl�venie vig�li� v r�mci posv�tn�ch ��tan�
#define PARAM_ANTIFONA_VIG  "ANTIFONA_VIG"
#define PARAM_CHVALOSPEV1   "CHVALOSPEV1"
#define PARAM_CHVALOSPEV2   "CHVALOSPEV2"
#define PARAM_CHVALOSPEV3   "CHVALOSPEV3"
#define PARAM_EVANJELIUM    "EVANJELIUM"
// 2012-09-05: mo�nos� zobrazi� pre doplnkov� psalm�diu priamy URL odkaz (na prepnutie)
#define PARAM_DOPLNKOVA_PSALMODIA      "DOPLNKOVA-PSALMODIA" // 2012-10-01: _ sa menilo na &nbsp; preto som zmenil na -
// 2013-08-22: mo�nos� zobrazi� priamy URL odkaz (na prepnutie) pre �almy z troch t��d�ov �alt�ra
#define PARAM_PSALMODIA_TRI_TYZDNE     "PSALMODIA-TRI-TYZDNE"
// 2012-09-27: mo�nos� zobrazi� chv�lospev, hymnus Te Deum, Ot�en� (na prepnutie), opakovan� zvolania v prosb�ach, Sl�va Otcu, pln� znenie responz�ri� pre posv�tn� ��tania...
#define PARAM_CHVALOSPEV               "CHVALOSPEV"
#define PARAM_TEDEUM		           "TEDEUM"
#define PARAM_OTCENAS                  "OTCENAS"
#define PARAM_ZVOLANIA                 "ZVOLANIA"
#define PARAM_SLAVAOTCU	               "SLAVAOTCU"
#define PARAM_RESPONZ                  "RESPONZ" // PARAM_PLNE_RESP je u� obsaden�...
#define PARAM_KRATSIE_PROSBY           "KRATSIE-PROSBY" // 2012-11-15: _ sa menilo na &nbsp; preto som zmenil na -
#define PARAM_ZALM95                   "ZALM95" // 2012-11-23: kv�li <a name...>
#define PARAM_VIGILIA                  "VIGILIA"
#define PARAM_SPOL_CAST_SPOM           "SPOL-CAST-SPOM"
#define PARAM_ALT_HYMNUS               "ALT-HYMNUS"
#define PARAM_ZALM122                  "ZALM122"
#define PARAM_ZALM126                  "ZALM126"
#define PARAM_ZALM127                  "ZALM127"
#define PARAM_ZALM129                  "ZALM129"
#define PARAM_ZALM131                  "ZALM131"

// dalsie parametre: specificke pre obdobie
// Od nedele P�novho zm�tvychvstania a� do Druhej ve�kono�nej nedele vr�tane, ako aj na druh� ve�pery sl�vnosti Zoslania Ducha Sv�t�ho
#define PARAM_ALELUJA_ALELUJA_BEGIN         "ALELUJA_ALELUJA_BEGIN"
#define PARAM_ALELUJA_ALELUJA_END           "ALELUJA_ALELUJA_END"
#define PARAM_ALELUJA_NIE_V_POSTE           "ALELUJA_NIE_V_POSTE" // pou��va sa v inkludovan�ch s�boroch, napr. v r�mci antif�n
#define PARAM_ALELUJA_NIE_V_POSTE_BEGIN     "ALELUJA_NIE_V_POSTE_BEGIN"
#define PARAM_ALELUJA_NIE_V_POSTE_END       "ALELUJA_NIE_V_POSTE_END"
#define PARAM_ALELUJA_VO_VELKONOCNOM        "V_O_ALELUJA" // pou��va sa v inkludovan�ch s�boroch, napr. v r�mci antif�n
#define PARAM_ALELUJA_VO_VELKONOCNOM_BEGIN  "V_O_ALELUJA_BEGIN" // pou��vaj� sa v templ�tach
#define PARAM_ALELUJA_VO_VELKONOCNOM_END    "V_O_ALELUJA_END"
// 2005-08-15: Doplnen� parametre pre vo�n�, in� hymny v 34. t��dni OCR
#define PARAM_HYMNUS_34_OCR_INY_BEGIN       "HYMNUS_34_OCR_INY_BEGIN"
#define PARAM_HYMNUS_34_OCR_INY_END         "HYMNUS_34_OCR_INY_END"
// nasleduju casti, ktore sa mozu pri generovani modlitby vynechat alebo doplnit podla lubovole
#define PARAM_OTCENAS_BEGIN                 "OTCENAS_BEGIN"
#define PARAM_OTCENAS_END                   "OTCENAS_END"
#define PARAM_CHVALOSPEV_BEGIN              "CHVALOSPEV_BEGIN"
#define PARAM_CHVALOSPEV_END                "CHVALOSPEV_END"
#define PARAM_ZAKONCENIE_BEGIN              "ZAKONCENIE_BEGIN"
#define PARAM_ZAKONCENIE_END                "ZAKONCENIE_END"
#define PARAM_KOMPLETORIUM_DVA_ZALMY_BEGIN	"KOMPLETORIUM_DVA_ZALMY_BEGIN"
#define PARAM_KOMPLETORIUM_DVA_ZALMY_END	"KOMPLETORIUM_DVA_ZALMY_END"
#define PARAM_SLAVAOTCU_BEGIN               "SLAVAOTCU_BEGIN"
#define PARAM_SLAVAOTCU_END                 "SLAVAOTCU_END"
// 2011-04-29: doplnen� Sl�va Otcu "�peci�lne" pre ��ely chv�lospevu Dan 3, 57-88. 56, kde nie je "Sl�va Otcu" (p�vodne to bolo dan� porad�m, ale templ�ty pre r�zne jazyky maj� rozli�n� poradie tohto "Sl�va Otcu")
#define PARAM_SLAVAOTCU_SPEC_BEGIN          "SLAVAOTCU_SPEC_BEGIN"
#define PARAM_SLAVAOTCU_SPEC_END            "SLAVAOTCU_SPEC_END"
// 2007-06-28: doplnen� Te Deum; nem��e sa riadi� rovnak�mi pravidlami ako chv�lospevy 
// 2011-04-11: pridan� �al�� p�r parametrov
//             JE_TEDEUM_BEGIN a END hovoria, �i v danej modlitbe m� v�bec by� zobrazen� �o i len zmienka o Te Deum (riaden� podmienkou je_tedeum);
//             TEDEUM_BEGIN a END hovoria, �e ak m� by� Te Deum (je_tedeum), tak ak chce pou��vate� zobrazi� pln� text, ohrani�uj� ho
#define PARAM_TEDEUM_BEGIN                  "TEDEUM_BEGIN"
#define PARAM_TEDEUM_END                    "TEDEUM_END"
#define PARAM_JE_TEDEUM_BEGIN               "JE_TEDEUM_BEGIN"
#define PARAM_JE_TEDEUM_END                 "JE_TEDEUM_END"
// 2007-10-02: doplnen� skrytie rovnak�ch antif�n pre mcd
#define PARAM_SKRY_ANTIFONU_BEGIN           "SKRY_ANTIFONU_BEGIN"
#define PARAM_SKRY_ANTIFONU_END             "SKRY_ANTIFONU_END"
// 2013-10-21: doplnen�: inverzia pre skrytie rovnak�ch antif�n pre mcd
#define PARAM_ZOBRAZ_ANTIFONU_BEGIN         "ZOBRAZ_ANTIFONU_BEGIN"
#define PARAM_ZOBRAZ_ANTIFONU_END           "ZOBRAZ_ANTIFONU_END"
// 2012-05-24: doplnen� -- pred�en� sl�venie vig�li� v r�mci posv�tn�ch ��tan�
#define PARAM_JE_VIGILIA_BEGIN              "JE_VIGILIA_BEGIN"
#define PARAM_JE_VIGILIA_END                "JE_VIGILIA_END"

// 2010-05-21: doplnen� zobrazenie antif�ny a modlitby pre spomienku sv�tca v p�stnom obdob�
// 2012-02-09: zov�eobecnen� v zmysle VSLH �. 238 (Spomienky pripadaj�ce na privilegovan� dni)
#define PARAM_SPOMIENKA_PRIVILEG_BEGIN      "SPOMIENKA_PRIVILEG_BEGIN"
#define PARAM_SPOMIENKA_PRIVILEG_END        "SPOMIENKA_PRIVILEG_END"
// 2011-01-12: doplnen� zobrazenie/skrytie my�lienky k �almu -- pre cezro�n� obdobie alternat�vnej antif�ny �almu/chv�lospevu ("my�lienka k �almu" pod�a bodu 111 a 114 VSLH)
#define PARAM_PSALMODIA_MYSLIENKA           "PSALMODIA_MYSLIENKA" // 2011-08-31: zmenen�; p�vodne bolo: PARAM_MYSLIENKA_K_ZALMU "MYSLIENKA_K_ZALMU"
// 2011-08-31: doplnen� zobrazenie/skrytie nadpisu k �almu/chv�lospevu ("nadpis k �almu" pod�a bodu 111 VSLH)
#define PARAM_PSALMODIA_NADPIS              "PSALMODIA_NADPIS"

#define PARAM_RUBRIKA_BEGIN                 "RUBRIKA_BEGIN"
#define PARAM_RUBRIKA_END                   "RUBRIKA_END"

// 2011-05-03: doplnen� kv�li posv�tn�mu ��taniu na ve�kono�n� nede�u
#define PARAM_VN_VYNECHAJ_BEGIN             "VELK_NEDELA_VYNECHAJ_BEGIN"
#define PARAM_VN_VYNECHAJ_END               "VELK_NEDELA_VYNECHAJ_END"

// 2011-07-07: doplnen� kv�li zobrazovaniu/skr�vaniu dlh��ch z�verov responz�ri� v posv�tnom ��tan�
#define PARAM_PLNE_RESP                     "PLNE_RESP"
#define PARAM_PLNE_RESP_BODKA               "PLNE_RESP_BODKA"

// 2011-10-05: doplnen� kv�li zobrazovaniu/skr�vaniu opakovan�ho zvolania v prosb�ch (rann� chv�ly, ve�pery)
#define PARAM_ZVOLANIE                      "ZVOLANIE"

// 2011-10-26: doplnen� rubriky priamo v includovan�ch HTML s�boroch
#define PARAM_RUBRIKA                       "RUBRIKA"

// 2011-04-04: doplnen� zobrazenie/skrytie ��slovania ver�ov v �almoch, chv�lospevoch a biblick�ch ��taniach
#define PARAM_CISLO_VERSA_BEGIN				"v"
#define PARAM_CISLO_VERSA_END				"/v"

// 2011-04-05: doplnenie referencie pod�a biblick�ho odkazu na str�nky dkc.kbs.sk (Biblia -- Mat�� Brilla)
#define PARAM_REFERENCIA_BEGIN				"r"
#define PARAM_REFERENCIA_END				"/r"

// 2011-09-01: odkaz na katech�zy (p�vodne v HTML zdroj�koch bola subscript hviezdi�ka za nadpisom)
#define PARAM_KATECHEZA_BEGIN				"k"
#define PARAM_KATECHEZA_END					"/k"

// 2011-09-06: odkaz na �alm 95 (p�vodne v HTML zdroj�koch pre �almy 24, 67, 100 bol natvrdo <a href> odkaz)
#define PARAM_LINK_ZALM95_BEGIN				"z95"
#define PARAM_LINK_ZALM95_END				"/z95"

// 2011-07-08: zobrazovanie/nezobrazenie kr�ika (antif�na toto�n� s ver�om �almu/chv�lospevu)
#define PARAM_KRIZIK                        "KRIZIK"

// 2011-07-14: zobrazovanie/nezobrazenie zalomen�ch textov tak, ako je v tla�enom vydan� LH (dlh� riadky-ver�e �almov/chv�lospevov a pod.)
#define PARAM_ZALOMENIE                     "ZALOMENIE"

// 2011-10-07: zakon�enie modlitieb (skrze, lebo on, lebo ty...) in�� (jednoduch�ie, bez begin-end)
#define PARAM_ZAKONCENIE                    "ZAKONCENIE"

// 2013-02-26: doplnkov� psalm�dia, alternat�vne �almy
#define PARAM_DOPLNK_PSALM_122_129          "DPSALM-122-129"
#define PARAM_DOPLNK_PSALM_126_129          "DPSALM-126-129"
#define PARAM_DOPLNK_PSALM_127_131          "DPSALM-127-131"

// 2009-04-08: zakon�enie modlitby trojak�, kr�tke resp. dlh�
#define PARAM_ZAKONCENIE_SKRZE              "SKRZE"
#define PARAM_ZAKONCENIE_LEBO_TY            "LEBO_TY"
#define PARAM_ZAKONCENIE_LEBO_ON            "LEBO_ON"
// 2009-12-14: zakon�enie modlitby trojak�, kr�tke resp. dlh� s mal�m p�smenkom na za�iatku
#define PARAM_ZAKONCENIE_SKRZE_MALE         "SKRZE_MALE"
#define PARAM_ZAKONCENIE_LEBO_TY_MALE       "LEBO_TY_MALE"
#define PARAM_ZAKONCENIE_LEBO_ON_MALE       "LEBO_ON_MALE"
// 2010-06-07: e�te jedno zakon�enie modlitby pre sloven�inu, kr�tke resp. dlh� (POST1_MODLITBA5NE)
#define PARAM_ZAKONCENIE_ON_JE              "ON_JE"
// 2010-01-14: e�te jedno zakon�enie modlitby pre sloven�inu, kr�tke resp. dlh�
#define PARAM_ZAKONCENIE_KTORY_JE           "KTORY_JE"
// 2012-03-16: predslovy k zakon�eniam, ktor� sa pre f�rie nemaj� zobrazi�, ak sa sl�vi spomienka v privilegovan�ch d�och
#define PARAM_ZAKONCENIE_O_TO_TA_PROSIME    "O_TO_TA_PROSIME"

// 2011-08-15: force pre jednotliv� �asti modlitby, funkcie _set_spolocna_cast()...
#define FORCE_BRAT_ANTIFONY      1
#define FORCE_BRAT_ZALMY         2
#define FORCE_BRAT_KCIT_1CIT     4 // kr�tke ��tanie pre rch+v; 1. ��tanie pre posv�tn� ��tanie
#define FORCE_BRAT_KRESP_PROSBY  8
#define FORCE_BRAT_2CITANIE     16
#define FORCE_BRAT_ANTIFONY_MCD 32

// stringy parametrov vstupu pre MODL_OPT..., ktore generovanie modlitby ovplyvnuju
// option 1
//#define STR_ANO "�no"
extern const char *str_ano[POCET_JAZYKOV + 1];
#ifndef		STR_ANO
#define		STR_ANO		str_ano[_global_jazyk]
#endif
//#define STR_NIE "nie"
extern const char *str_nie[POCET_JAZYKOV + 1];
#ifndef		STR_NIE
#define		STR_NIE		str_nie[_global_jazyk]
#endif

/* option 2 - presunut� do mydefs.h 
#define MODL_ZALMY_ZO_DNA 0
#define MODL_ZALMY_ZO_SV  1
*/

//#define STR_MODL_ZALMY_ZO_DNA "d�a"
extern const char *str_modl_zalmy_zo_dna[POCET_JAZYKOV + 1];
#ifndef		STR_MODL_ZALMY_ZO_DNA
#define		STR_MODL_ZALMY_ZO_DNA 	str_modl_zalmy_zo_dna[_global_jazyk]
#endif
//#define STR_MODL_ZALMY_ZO_SV  "sviatku"
extern const char *str_modl_zalmy_zo_sv[POCET_JAZYKOV + 1];
#ifndef		STR_MODL_ZALMY_ZO_SV
#define		STR_MODL_ZALMY_ZO_SV 	str_modl_zalmy_zo_sv[_global_jazyk]
#endif

// option 3 -- tieto nasledujuce definicie definuju to, co je sucastou _struct_dm::spolcast
#define MAX_MODL_SPOL_CAST  28
// najviac MAX_MODL_SPOL_CAST "spolocnych casti", t.j. identifikatorov MODL_SPOL_CAST_...; musi byt o jedno vacsia ako poslena, t.j. MODL_SPOL_CAST_NEBRAT

#define MODL_SPOL_CAST_NULL              -1
#define MODL_SPOL_CAST_NEURCENA           0
#define MODL_SPOL_CAST_DUCH_PAST_KNAZ     1
#define MODL_SPOL_CAST_DUCH_PAST_BISKUP   2
#define MODL_SPOL_CAST_DUCH_PAST_PAPEZ    3
#define MODL_SPOL_CAST_UCITEL_CIRKVI      4
#define MODL_SPOL_CAST_APOSTOL            5
#define MODL_SPOL_CAST_MUCENIK            6 // muz
#define MODL_SPOL_CAST_VIAC_MUCENIKOV     7
#define MODL_SPOL_CAST_PANNA_MARIA        8
#define MODL_SPOL_CAST_SV_MUZ_REHOLNIK    9
#define MODL_SPOL_CAST_SV_MUZ            10 // jeden
#define MODL_SPOL_CAST_PANNA             11 // jedna
#define MODL_SPOL_CAST_SV_ZENA_REHOLNIK  12
#define MODL_SPOL_CAST_SV_ZENA           13 // jedna
#define MODL_SPOL_CAST_DUCH_PAST_VIACERI 14
#define MODL_SPOL_CAST_MUCENICA          15 // zena
#define MODL_SPOL_CAST_SV_ZENA_VYCH      16
#define MODL_SPOL_CAST_SV_MUZ_VYCH       17
#define MODL_SPOL_CAST_SV_ZENA_SKUTKYMIL 18
#define MODL_SPOL_CAST_SV_MUZ_SKUTKYMIL  19
#define MODL_SPOL_CAST_SV_ZENA_VIACERE   20
#define MODL_SPOL_CAST_SV_MUZ_VIACERI    21 // viaceri
#define MODL_SPOL_CAST_PANNY_VIACERE     22 // viacere
#define MODL_SPOL_CAST_POSVIACKA_CHRAMU  23
#define MODL_SPOL_CAST_ZA_ZOSNULYCH      24
// MODL_SPOL_CAST_NEBRAT musi byt posledna, napr. kvoli "while" v dnes.cpp::showPrayer(); ale predsa mensia ako MAX_MODL_SPOL_CAST
#define MODL_SPOL_CAST_SV_ZENA_MANZ      25 // pre t�ch, �o �ili v man�elstve
#define MODL_SPOL_CAST_SV_MUZ_MANZ       26 // pre t�ch, �o �ili v man�elstve
#define MODL_SPOL_CAST_NEBRAT            27 // nechce zo spol. casti
#define POCET_SPOL_CASTI	MAX_MODL_SPOL_CAST - 1

extern const char *str_doplnkova_psalmodia[POCET_JAZYKOV + 1];
//#define STR_MODL_CEZ_DEN_ZALMY_ZO_DNA        "be�nej"
extern const char *str_modl_cez_den_zalmy_zo_dna[POCET_JAZYKOV + 1];
#ifndef		STR_MODL_CEZ_DEN_ZALMY_ZO_DNA
#define		STR_MODL_CEZ_DEN_ZALMY_ZO_DNA	str_modl_cez_den_zalmy_zo_dna[_global_jazyk]
#endif
//#define STR_MODL_CEZ_DEN_DOPLNKOVA_PSALMODIA "doplnkovej"
extern const char *str_modl_cez_den_doplnkova_psalmodia[POCET_JAZYKOV + 1];
#ifndef		STR_MODL_CEZ_DEN_DOPLNKOVA_PSALMODIA
#define		STR_MODL_CEZ_DEN_DOPLNKOVA_PSALMODIA	str_modl_cez_den_doplnkova_psalmodia[_global_jazyk]
#endif

// a pre tieto - vyssie uvedene - konstanty aj retazce... -- malo by ich byt do MAX_MODL_SPOL_CAST
//extern const char *nazov_spolc[MODL_SPOL_CAST_NEBRAT + 1];
extern const char *nazov_spolc_jazyk[POCET_SPOL_CASTI + 1][POCET_JAZYKOV + 1];
#ifndef		nazov_spolc
#define		nazov_spolc(a)	nazov_spolc_jazyk[a][_global_jazyk]
#endif

// a pre tieto konstanty aj retazce -- nazvy suborov -- malo by ich byt do MAX_MODL_SPOL_CAST
// sc_rh == spolocna cast pre reholnikov / reholnice;
// sc_skm == spolocna cast pre tych, co konali skutky milosrdenstva ;
// sc_vv == spolocna cast pre vychovavatelov;
// zosnuli == oficium za zosnulych;
extern const char *nazov_spolc_htm[MODL_SPOL_CAST_NEBRAT + 1];
// a pre tieto konstanty aj retazce -- nazvy kotiev -- malo by ich byt do MAX_MODL_SPOL_CAST
extern const char *nazov_spolc_ANCHOR[MODL_SPOL_CAST_NEBRAT + 1];

#define ANCHOR_SPOL_CAST_DUCH_PAST "SCDP"
// vacsinu veci maju duchovni pastieri spolocnych; odlisnosti: su v nazov_spolc_ANCHOR[]
#define ANCHOR_SPOL_CAST_JEDEN_MUCENIK "SCJM"
// na sviatok jedneho mucenika sa rozhoduje, ci ide o muza alebo zenu | v niektorych pripadoch; odlisnosti: su v nazov_spolc_ANCHOR[]
#define ANCHOR_SPOL_CAST_PANNA_MUCENICA "SCAM"
//  na sviatok vychovavatelov: nevieme (a je jedno), ci ide o muza alebo zenu -- ked berieme z fajlu sc_vv.htm
/*
#define ANCHOR_SPOL_CAST_VYCHOVAVATEL "SCVV"
#define FILE_SPOL_CAST_VYCHOVAVATEL "sc_vv.htm"
*/
// na sviatok tych, co konali skutky milosrdenstva: nevieme (a je jedno), ci ide o muza alebo zenu -- ked berieme z fajlu sc_skm.htm
/*
#define ANCHOR_SPOL_CAST_SKUTKYMIL "SCSKM"
#define FILE_SPOL_CAST_SKUTKYMIL "sc_skm.htm"
*/ // je to v poli... v hodin.h

struct sc{
	short int a1;
	short int a2;
	short int a3;
};
typedef struct sc _struct_sc;

// 2005-07-27: zaveden� nov� premenn� v �trukt�re: typslav_lokal ur�en� nies� �peci�lnu inform�ciu o tom, �i dan� sl�venie je lok�lne.
// �tandardne 0 = bez �peci�lnej lokaliz�cie.
// 2006-08-19: pridan� premenn� pre liturgick� farbu
// 2010-08-03: pridan� premenn� pre �pecifik�ciu, o ak� kalend�r ide (kalendar): v�eobecn� danej cirkevnej provincie alebo nejak� reho�n� a pod.
struct dm{
	short int den;        // cislo dna mesiaca (1--31)
	short int mesiac;     // cislo mesiaca (1--12)
	short int rok;        // rok
	short int denvt;      // cislo dna v tyzdni (0--6) DEN_...
	short int denvr;      // cislo dna v roku (1--365/366) -- de� v roku
	// toto boli "obcianske" zalezitosti
	char litrok;          // liturgicky rok ('A'--'C')
	short int tyzden;     // tyzden v danom liturgickom obdobi
	short int tyzzal;     // tyzden v zaltari (vacsinou ((tyzden - 1) % 4) + 1)
	short int litobd;     // liturgicke obdobie, OBD_...
	short int typslav;    // typ slavenia (1--5): SLAV_...
	short int typslav_lokal; // lok�lny typ slavenia : LOKAL_SLAV_...
	short int smer;       // poradove cislo z c.59 Vseobecnych smernic o liturgii hodin a kalendari
	short int prik;		  // ci je to prikazany sviatok alebo nie: PRIKAZANY_SVIATOK resp. NIE_JE_PRIKAZANY_SVIATOK
	int spolcast;		  // spolocna cast -- zakodovane data pre svatych o tom, z akej spolocnej casti sa ma modlit;
						  // obsahuje max. 3 spolocne casti vo formate spolcast == a1 + a2 * MAX + a3 * MAX * MAX,
						  // kde -- MAX je MAX_MODL_SPOL_CAST,
						  //     -- a1, a2, a3 su konstanty MODL_SPOL_CAST_... (v poradi a1, ak druhe tak a2, ak tretie tak aj a3)
						  // _encode_..., _decode_spol_cast();
	char meno[MENO_SVIATKU]; // nazov prip. sviatku
	short int farba;      // liturgick� farba pre sl�venie
	short int kalendar;   // �pecifik�cia, o ak� kalend�r ide: v�eobecn� danej cirkevnej provincie alebo nejak� reho�n� a pod.
};
typedef struct dm _struct_dm;

// dni
#define DEN_NEDELA      0
#define DEN_PONDELOK    1
#define DEN_UTOROK      2
#define DEN_STREDA      3
#define DEN_STVRTOK     4
#define DEN_PIATOK      5
#define DEN_SOBOTA      6
// neznamy den
#define DEN_UNKNOWN     7
#define POCET_DNI		7

// mesiace
#define MES_JAN 0
#define MES_FEB 1
#define MES_MAR 2
#define MES_APR 3
#define MES_MAY 4
#define MES_MAJ 4
#define MES_JUN 5
#define MES_JUL 6
#define MES_AUG 7
#define MES_SEP 8
#define MES_OCT 9
#define MES_OKT 9
#define MES_NOV 10
#define MES_DEC 11
// neznamy mesiac
#define UNKNOWN_MESIAC	12
#define POCET_MESIACOV	12
// vsetky mesiace
#define VSETKY_MESIACE	13
#define STR_VSETKY_MESIACE  "*"
// vsetky dni
#define VSETKY_DNI   32
#define STR_VSETKY_DNI  "*"

// liturgick� obdobia 
// 2011-01-26: ��sla kon�tant�m pridelen� tak, aby re�pektovali plynulos� liturgick�ho roka od zv�zku I brevi�ra
//OBD_ADVENTNE
#define OBD_ADVENTNE_I             0 // do 16. decembra
#define OBD_ADVENTNE_II            1 // po 16. decembri
//OBD_VIANOCNE
#define OBD_OKTAVA_NARODENIA       2 // narodenie Pana -- 1. jan.
#define OBD_VIANOCNE_I             3 // do slavnosti zjavenia pana
#define OBD_VIANOCNE_II            4 // po slavnosti zjavenia pana
//OBD_CEZ_ROK
#define OBD_CEZ_ROK                5
//OBD_POSTNE
#define OBD_POSTNE_I               6 // do soboty v piatom tyzdni
#define OBD_POSTNE_II_VELKY_TYZDEN 7 // velky tyzden
//OBD_VELKONOCNE_TROJDNIE
#define OBD_VELKONOCNE_TROJDNIE    8 // umucenia a zmrtvychvstania Pana
//OBD_VELKONOCNE
#define OBD_VELKONOCNA_OKTAVA      9 // velkonocna nedela -- 2. velk. ne
#define OBD_VELKONOCNE_I          10 // do nanebovstupenia pana
#define OBD_VELKONOCNE_II         11 // po nanebovstupeni pana

#define	POCET_OBDOBI	11

// zv�zok brevi�ra - zv�zok, v ktorom sa nach�dza dan� liturgick� obdobie; doplnen� 2007-12-20; opraven� 2008-01-23
const short int zvazok_breviara[POCET_OBDOBI + 1] = 
{1, 1, 1, 1, 1, 3, 2, 2, 2, 2, 2, 2}; // nepotrebujeme rozl�i� 3. a 4. zv�zok, ktor� obidva obsahuj� OBD_CEZ_ROK

// po�et t��d�ov pre dan� liturgick� obdobie; doplnen� 2011-01-25
const short int lit_obd_pocet_tyzdnov[POCET_OBDOBI + 1] = 
{4, 1, 1, 2, 1, 34, 6, 1, 1, 1, 7, 2};

// nazov_obdobia: string pre nazov liturgickeho obdobia
//extern const char *nazov_obdobia[];
extern const char *nazov_obdobia_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1];
#define		nazov_obdobia(a)	nazov_obdobia_jazyk[a][_global_jazyk]

extern const char *nazov_obdobia_[POCET_OBDOBI + 1];

// lokal == 6. pad, v kom/com
//extern const char *nazov_obdobia_v[];
extern const char *nazov_obdobia_v_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1];
#define		nazov_obdobia_v(a)	nazov_obdobia_v_jazyk[a][_global_jazyk]

//extern const char *nazov_OBDOBIA_V[];
extern const char *nazov_OBDOBIA_V_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1];
#define		nazov_OBDOBIA_V(a)	nazov_OBDOBIA_V_jazyk[a][_global_jazyk]

extern const char *nazov_OBDOBIA_AKA_jazyk[POCET_OBDOBI + 1][POCET_JAZYKOV + 1];
#define		nazov_OBDOBIA_AKA(a)	nazov_OBDOBIA_AKA_jazyk[a][_global_jazyk]

// gen[itiv] == 2. pad, koho/coho
// extern const char *nazov_obdobia_gen[];
// extern const char *nazov_Obdobia[];

// nazov_obdobia: string pre nazov suboru .htm liturgickeho obdobia
extern const char *nazov_obd_htm[POCET_OBDOBI + 1];
// nazov_obdobia: string pre nazov kotvy v .htm liturgickeho obdobia
extern const char *nazov_OBD[POCET_OBDOBI + 1];
// nazov_obdobia pc: string pre nazov suboru .htm liturgickeho obdobia pre posvatne citania
extern const char *nazov_obd_htm_pc[POCET_OBDOBI + 1];
// 2005-08-05: Pridan�. zv�zok brevi�ra (LH) pre spolo�n� �asti sv�t�ch v kotv�ch
extern const char *zvazok_OBD[POCET_OBDOBI + 1];

// typy slavenia
#define SLAV_NEURCENE            0
#define SLAV_SLAVNOST            1
#define SLAV_SVIATOK             2
#define SLAV_SPOMIENKA           3
#define SLAV_LUB_SPOMIENKA       4
#define SLAV_VLASTNE             5

#define	POCET_SLAVENI            5

// nazov_slavenia: string pre nazov typu slavenia
//extern const char *nazov_slavenia[];
extern const char *nazov_slavenia_jazyk[POCET_SLAVENI + 1][POCET_JAZYKOV + 1];
#define		nazov_slavenia(a)	nazov_slavenia_jazyk[a][_global_jazyk]

// the name of celebration -- for memoria (in privileged days)
extern const char *nazov_slavenia_na_spomienku_jazyk[POCET_JAZYKOV + 1];

// extern const char *nazov_Slavenia[];

extern const char *nazov_slavenia_lokal[];

#define LOKAL_SLAV_NEURCENE					0
#define LOKAL_SLAV_ROZNAVA_KATEDRALA		1
#define LOKAL_SLAV_TRNAVA_PATRON			2
#define LOKAL_SLAV_TT_BB_KE_NR_RO			3
#define LOKAL_SLAV_NITRA_PATRON				4
#define LOKAL_SLAV_KOSICE					5
#define LOKAL_SLAV_NITRA					6
#define LOKAL_SLAV_BYSTRICA					7
#define LOKAL_SLAV_SPIS						8
#define LOKAL_SLAV_ROZNAVA					9
#define LOKAL_SLAV_TRNAVA					10 // p�vodne bolo LOKAL_SLAV_TRNAVA, upraven� 2007-08-31 na LOKAL_SLAV_BA_TT; nasp� na LOKAL_SLAV_TRNAVA 2008-06-23
#define LOKAL_SLAV_DOM_SV_MARTINA			11
#define LOKAL_SLAV_SPIS_PATRON				12
#define LOKAL_SLAV_BYSTRICA_PATRON			13
#define LOKAL_SLAV_TT_BB_NR_RO				14
#define LOKAL_SLAV_KOSICE_PATRON			15
#define LOKAL_SLAV_14_FEB_CYRIL_METOD		16
#define LOKAL_SLAV_ROZNAVA_PATRON			17
#define LOKAL_SLAV_KONSEKR_KOSTOLY			18
#define LOKAL_SLAV_DRUHA_VELK_NEDELA		19
#define LOKAL_SLAV_KONIEC_OKTAVY_NAR		20
#define LOKAL_SLAV_KONIEC_OKTAVY_NAR_CZ		21
#define LOKAL_SLAV_PRAHA_PATRON				22
#define LOKAL_SLAV_PRAHA					23
#define LOKAL_SLAV_BRNO						24
#define LOKAL_SLAV_MORAVA_SPOMIENKA			25
#define LOKAL_SLAV_DRUHA_VELK_NEDELA_CZ		26
#define LOKAL_SLAV_PRAHA_KATEDRALA			27
#define LOKAL_SLAV_CESKE_BUDEJOVICE			28
#define LOKAL_SLAV_OLOMOUC					29
#define LOKAL_SLAV_CECHY_SPOMIENKA			30
#define LOKAL_SLAV_PLZEN_PATRON				31
#define LOKAL_SLAV_OSTRAVA_OPAVA			32
#define LOKAL_SLAV_LITOMERICE				33
#define LOKAL_SLAV_HRADEC_KRALOVE			34
#define LOKAL_SLAV_KONSEKR_KOSTOLY_CZ 		35
#define LOKAL_SLAV_PLZEN 					36
#define LOKAL_SLAV_OSTRAVA_OPAVA_SLAVNOST	37
#define LOKAL_SLAV_CESKE_BUDEJOVICE_PAMATKA	38
#define LOKAL_SLAV_SPIS_BA_PATRON			39 // pre 11. novembra, patr�na BA-arcidiec�zy; 2008-06-24; nahr�dza LOKAL_SLAV_SPIS_PATRON
#define LOKAL_SLAV_BRATISLAVA				40 // doplnen� 2010-03-16
#define LOKAL_SLAV_KONIEC_OKTAVY_NAR_HU		41 // doplnen� 2010-05-17
#define LOKAL_SLAV_KONGREGACIA_SSK			42 // doplnen� 2011-01-27
#define LOKAL_SLAV_SPOMIENKA_OFMCAP			43 // nasledovn� doplnen� 2011-03-16
#define LOKAL_SLAV_SVIATOK_OFM				44
#define LOKAL_SLAV_SPOMIENKA_OFM			45
#define LOKAL_SLAV_SVIATOK_OFMCAP			46 // nasledovn� doplnen� 2011-03-17
#define LOKAL_SLAV_SPOMIENKA_FMA			47
#define LOKAL_SLAV_SLAVNOST_FMA				48
#define LOKAL_SLAV_SLAVNOST_SDB				49
#define LOKAL_SLAV_SVIATOK_VDB				50
#define LOKAL_SLAV_SVIATOK_SCSC				51
#define LOKAL_SLAV_DRUHA_VELK_NEDELA_HU		52
#define LOKAL_SLAV_SZOMBATHELYI_EGYH        53
#define LOKAL_SLAV_POZS_NAGYSZ_PATRON       54
#define LOKAL_SLAV_SZEGED_CSAN_PATRON       55
#define LOKAL_SLAV_PECSI_EGYH               56
#define LOKAL_SLAV_PECSI_EGYH_PATRON        57
#define LOKAL_SLAV_SZEGED_CSAN_EGYH         58
#define LOKAL_SLAV_VESZPREMI_EGYH_PATRON    59
#define LOKAL_SLAV_GYORI_SZEKESFEH_EGYH     60
#define LOKAL_SLAV_KAPORSVAR_FELSZ          61
#define LOKAL_SLAV_VACI_FELSZ               62
#define LOKAL_SLAV_KAL_KECS_FOEGYH          63
#define LOKAL_SLAV_ESZTERGOM_BUDA_FOEGYH    64
#define LOKAL_SLAV_KAL_KECS_FELSZ           65
#define LOKAL_SLAV_GYORI_SZEKESEGYH_FELSZ   66
#define LOKAL_SLAV_VACI_PATRON              67
#define LOKAL_SLAV_SZEGED_CSAN_PATRON2      68
#define LOKAL_SLAV_VESZPREM_FOEGYH          69
#define LOKAL_SLAV_KONSEKR_KOSTOLY_HU		70
#define LOKAL_SLAV_SZEGED_CSAN_EGYH2        71
#define LOKAL_SLAV_PECS_PATRON              72
#define LOKAL_SLAV_SZOMBATHELYI_PATRON      73
#define LOKAL_SLAV_SZEKESFEHERVAR_EGYH      74
#define LOKAL_SLAV_EGER_FOEGYH              75
#define LOKAL_SLAV_ESZTERGOM_EML            76
#define LOKAL_SLAV_GYOR_EGYH                77
#define LOKAL_SLAV_ESZTERGOM_FOEGYH         78
#define LOKAL_SLAV_EGER_FOEGYH2             79
#define LOKAL_SLAV_VESZPREM_FOEGYH_T        80
#define LOKAL_SLAV_SZATMAR                  81
#define LOKAL_SLAV_CESKO_BRNO               82
#define LOKAL_SLAV_SVIATOK_OP_ZENY          83
#define LOKAL_SLAV_ZILINA                   84
#define LOKAL_SLAV_OPRAEM_SVIATOK_STRAHOV   85
#define LOKAL_SLAV_OPRAEM_SLAVNOST_TEPLA    86
#define LOKAL_SLAV_OPRAEM_NOVA_RISE         87
#define LOKAL_SLAV_OPRAEM_STRAHOV_NOVA_RISE 88
#define LOKAL_SLAV_OPRAEM_ZELIV             89
#define LOKAL_SLAV_OPRAEM_STRAHOV           90
#define LOKAL_SLAV_SZ_LASZLO                91
#define LOKAL_SLAV_SLAVNOST_OSC             92
#define LOKAL_SLAV_SVIATOK_OFMCONV          93
#define LOKAL_SLAV_SVIATOK_OFS              94
#define LOKAL_SLAV_SPOMIENKA_OFMCONV_OFMCAP 95
#define LOKAL_SLAV_SPOMIENKA_OSC            96
#define LOKAL_SLAV_NEDOVOLENE               97
#define LOKAL_SLAV_KATONAI_ORDINARIAT       98
#define LOKAL_SLAV_DEBR_NYIREGY             99

// 2010-08-03: pridan� kalend�r
#define KALENDAR_NEURCENY                   0
#define KALENDAR_VSEOBECNY                  1
#define KALENDAR_VSEOBECNY_SK               2
#define KALENDAR_VSEOBECNY_CZ               3
#define KALENDAR_CZ_OP                      4
#define KALENDAR_SK_CSSR                    5
#define KALENDAR_VSEOBECNY_HU               6
#define KALENDAR_SK_SVD                     7
#define KALENDAR_SK_SJ                      8
#define KALENDAR_SK_SDB                     9
#define KALENDAR_SK_OFM                    10
#define KALENDAR_SK_OP                     11
#define KALENDAR_SK_CM                     12
#define KALENDAR_CZ_OPRAEM                 13

#define POCET_KALENDAROV                   13

// filenames for special calendars / n�zov s�bora pre kalend�re
extern const char *nazov_htm_kalendar[POCET_KALENDAROV + 1];

extern const char *nazov_kalendara_long[POCET_KALENDAROV + 1];

// prikazany / neprikazany sviatok / �ubovo�n� spomienka bez z�v�znosti (blahoslaven� napr. pre SK_OP)
#define PRIKAZANY_SVIATOK           0
#define NIE_JE_PRIKAZANY_SVIATOK    1
#define VOLNA_LUBOVOLNA_SPOMIENKA   2 // pre SK OP; v kalend�ri zna�en� kurz�vou (bez popisu "�ubovo�n� spomienka"); 2012-04-01

// div, mod: delenie pre short int
#define DIV	/
#define MOD	%

// 2006-02-07: dodefinovan� r�zne spr�vanie funkcie zaltar_zvazok();
#define	ZALTAR_VSETKO                0
#define ZALTAR_IBA_ZALMY             1
#define ZALTAR_IBA_ZALMY_HYMNUS_MCD  2

// 2006-08-19: pridan� liturgick� farby
#define LIT_FARBA_NEURCENA			0
#define LIT_FARBA_CERVENA			1
#define LIT_FARBA_BIELA				2
#define LIT_FARBA_ZELENA			3
#define LIT_FARBA_FIALOVA			4
#define LIT_FARBA_RUZOVA			5
#define LIT_FARBA_CIERNA			6
#define LIT_FARBA_FIALOVA_CIERNA	7 // LIT_FARBA_FIALOVA a LIT_FARBA_CIERNA
#define LIT_FARBA_FIALOVA_BIELA		8 // LIT_FARBA_FIALOVA a LIT_FARBA_BIELA
#define LIT_FARBA_RUZOVA_FIALOVA	9 // LIT_FARBA_RUZOVA a LIT_FARBA_FIALOVA

#define POCET_FARIEB				9
#define POCET_FARIEB_REALNYCH		6

// nazov_farby: string pre n�zov liturgickej farby
extern const char *nazov_farby_jazyk[POCET_FARIEB_REALNYCH + 1][POCET_JAZYKOV + 1];
#define		nazov_farby(a)	nazov_farby_jazyk[a][_global_jazyk]

extern const char *html_farba_pozadie[POCET_FARIEB_REALNYCH + 1];
extern const char *html_farba_popredie[POCET_FARIEB_REALNYCH + 1];

// juliansky datum, funkcia juliansky_datum, dane synonymum JD
#define	JD	juliansky_datum

#define ZVAZKY_LH 4
// tyzden zaltara (1, 2, 3, 4) podla tyzdna t; 06/03/2000A.D.: namiesto "-1" prerobene na "+3"
#define  tyzden_zaltara(t)  ((((t) + 3) % 4) + 1)
extern const char *rimskymi_tyzden_zaltara[ZVAZKY_LH + 1];

extern const short int prvy_den[12];

extern short int pocet_dni[12];

extern const char char_nedelne_pismeno[POCET_DNI];

#define POCET_NEDELNY_CYKLUS 3
extern const char char_nedelny_cyklus[POCET_NEDELNY_CYKLUS];

#define	ROK_1968		1968
#define	JUL_DATE_0_JAN_1968	2439856L // juliansky datum pre 0. januar 1968

#define	POCET_DNI_V_ROKU	365

#define	POCET_NEDIEL_CEZ_ROK	34
#define	KRISTA_KRALA	34 // 34. nedela v obdobi cez rok je sviatok K.K.

// poradie prva adventna nedela, neprestupny rok!
#define	PRVA_ADVENTNA_NEDELA_b	331

#define	OD_VELKEJ_NOCI_PO_POPOLCOVU_STR		-46
#define OD_VELKEJ_NOCI_PO_NANEBOSTUPENIE	39
#define OD_VELKEJ_NOCI_PO_NANEBOSTUPENIE_NE	42
#define	OD_VELKEJ_NOCI_PO_ZOSLANIE_DUCHA	49

// sposob pisania slov
#define CASE_case 0 // vsetky male
#define CASE_Case 1 // Prve Pismeno Velke
#define CASE_CASE 2 // VSETKO VELKE

// nazov_dna: string pre nazov dna; suhlasi s struct tm.tm_wday; Weekday (0--6; Sunday/nedela = 0)

//extern const char *nazov_dna[];
extern const char *nazov_dna_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1];
#define		nazov_dna(a)	nazov_dna_jazyk[a][_global_jazyk]

//extern const char *nazov_dna_asci[];
extern const char *nazov_dna_asci_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1];
#define		nazov_dna_asci(a)	nazov_dna_asci_jazyk[a][_global_jazyk]

//extern const char *nazov_Dna[];
extern const char *nazov_Dna_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1];
#define		nazov_Dna(a)	nazov_Dna_jazyk[a][_global_jazyk]

//extern const char *nazov_DNA[];
extern const char *nazov_DNA_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1];
#define		nazov_DNA(a)	nazov_DNA_jazyk[a][_global_jazyk]

//extern const char *nazov_Dn[];
extern const char *nazov_Dn_jazyk[POCET_DNI + 1][POCET_JAZYKOV + 1];
#define		nazov_Dn(a)	nazov_Dn_jazyk[a][_global_jazyk]

extern const char *nazov_DN_asci[POCET_DNI + 1];
extern const char *nazov_dn_asci[POCET_DNI + 1];

// nazov_mesiaca: string pre nazov dna; suhlasi s struct tm.tm_mon; Month (0--11)

//extern const char *nazov_mesiaca[];
extern const char *nazov_mesiaca_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1];
#define		nazov_mesiaca(a)	nazov_mesiaca_jazyk[a][_global_jazyk]

//extern const char *nazov_mesiaca_asci[];
extern const char *nazov_mesiaca_asci_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1];
#define		nazov_mesiaca_asci(a)	nazov_mesiaca_asci_jazyk[a][_global_jazyk]

//extern const char *nazov_Mesiaca[];
extern const char *nazov_Mesiaca_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1];
#define		nazov_Mesiaca(a)	nazov_Mesiaca_jazyk[a][_global_jazyk]

//extern const char *nazov_MESIACA[];
extern const char *nazov_MESIACA_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1];
#define		nazov_MESIACA(a)	nazov_MESIACA_jazyk[a][_global_jazyk]

// 2007-03-20: pridan� genit�v n�zvu mesiaca kv�li latin�ine
extern const char *nazov_mesiaca_gen_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1];
#define		nazov_mesiaca_gen(a)	nazov_mesiaca_gen_jazyk[a][_global_jazyk]

extern const char *nazov_Mesiaca_gen_jazyk[POCET_MESIACOV + 1][POCET_JAZYKOV + 1];
#define		nazov_Mesiaca_gen(a)	nazov_Mesiaca_gen_jazyk[a][_global_jazyk]

extern const char *nazov_MES[POCET_MESIACOV + 1];
extern const char *nazov_mes[POCET_MESIACOV + 1];

#define		POCET_TYZDNOV 34

extern const char *poradie_Slovom_jazyk[POCET_TYZDNOV + 1][POCET_JAZYKOV + 1];
#define		poradie_Slovom(a)	poradie_Slovom_jazyk[a][_global_jazyk]

extern const char *poradie_SLOVOM_jazyk[POCET_TYZDNOV + 1][POCET_JAZYKOV + 1];
#define		poradie_SLOVOM(a)	poradie_SLOVOM_jazyk[a][_global_jazyk]

#define POCET_ALIASOV          7
// sucast struktury lrok, indexy
#define idx_KRST_KRISTA_PANA       0
#define idx_POPOLCOVA_STREDA       1
#define idx_VELKONOCNA_NEDELA      2
#define idx_NANEBOVSTUPENIE_PANA   3
#define idx_ZOSLANIE_DUCHA_SV      4
#define idx_PRVA_ADVENTNA_NEDELA   5
#define idx_SVATEJ_RODINY          6

// sucast struktury lrok, aliasy
#define _KRST_KRISTA_PANA         _den[idx_KRST_KRISTA_PANA]
#define _POPOLCOVA_STREDA         _den[idx_POPOLCOVA_STREDA]
#define _VELKONOCNA_NEDELA        _den[idx_VELKONOCNA_NEDELA]
#define _NANEBOVSTUPENIE_PANA     _den[idx_NANEBOVSTUPENIE_PANA]
#define _PRVA_ADVENTNA_NEDELA     _den[idx_PRVA_ADVENTNA_NEDELA]
#define _ZOSLANIE_DUCHA_SV        _den[idx_ZOSLANIE_DUCHA_SV]
#define _SVATEJ_RODINY            _den[idx_SVATEJ_RODINY]

#define YES 1
#define NO  0

#define NIJAKE_NEDELNE_PISMENO 'x'
struct lrok{
	short int prestupny;  // ci je rok prestupny (YES, NO)
	char p1, p2;          // nedelne pismeno/pismena; ak ma rok iba jedno, druhe p2 == NIJAKE_NEDELNE_PISMENO
	char litrok;          // pismeno liturgickeho roka, ktory zacina prvou adventnou nedelou v roku
	short int tyzden_ocr_po_vn; // cislo tyzdna obdobia "cez rok", ktory nasleduje po nedeli zoslania ducha svateho, teda po velkonocnom obdobi
	short int tyzden_ocr_pred_po; // cislo tyzdna obdobia cez rok, v ktorom zacina post
	struct dm _den[POCET_ALIASOV];
};
typedef struct lrok _struct_lrok;

#define LINK_DEN_MESIAC_NIE 0 // 2008-01-22: pridan�, Vlado Ki� upozornil, �e je to zbyto�n�
#define LINK_DEN_MESIAC_ROK 1
#define LINK_DEN_MESIAC 3
#define LINK_DEN 2
#define LINK_DEN_MESIAC_ROK_PRESTUP 4 // pridana kvoli prestupnym rokom, 2003-07-02
#define LINK_ISO_8601 5 // pridana kvoli SIMPLE exportu, 2005-03-21
#define LINK_DEN_MESIAC_PREDOSLY 6 // 2007-08-15 pridan� kv�li nov�mu kalend�ru
#define LINK_DEN_MESIAC_NASLEDOVNY 7 // 2007-08-15 pridan� kv�li nov�mu kalend�ru
#define LINK_DEN_MESIAC_GEN 8 // 2011-12-19: to ist� ako LINK_DEN_MESIAC, len mesiac je v genit�ve

//---------------------------------------------------------------------
// globalne premenne -- su definovane v dnes.cpp (18/02/2000A.D.)

// globalna premenna, do ktorej sa ukladaju info o analyzovanom dni
extern _struct_dm *_global_den_ptr;
#define _global_den (*_global_den_ptr)

// globalna premenna, ktora obsahuje data o spomienke panny marie v sobotu

extern _struct_dm *_global_pm_sobota_ptr;
#define _global_pm_sobota (*_global_pm_sobota_ptr)

// globalne premenne, do ktorych sa ukladaju info o analyzovanom dni o sviatkoch svatych
extern _struct_dm *(_global_svaty_ptr[MAX_POCET_SVATY]); // an array of '_struct_dm' pointers
#define _global_svaty(i) (*(_global_svaty_ptr[i - 1]))
#define _global_svaty1 (*_global_svaty_ptr[0])
#define _global_svaty2 (*_global_svaty_ptr[1])
#define _global_svaty3 (*_global_svaty_ptr[2])
#define _global_svaty4 (*_global_svaty_ptr[3])
#define _global_svaty5 (*_global_svaty_ptr[4])

// globalne premenne obsahujuce data modlitbach

extern _type_1vespery     *_global_modl_prve_vespery_ptr;
// extern _type_1vespery      _global_modl_prve_vespery;
#define _global_modl_prve_vespery (*_global_modl_prve_vespery_ptr)

extern _type_1kompletorium *_global_modl_1kompletorium_ptr;
// extern _type_1kompletorium _global_modl_prve_kompletorium;
#define _global_modl_prve_kompletorium (*_global_modl_1kompletorium_ptr)

extern _type_invitatorium *_global_modl_invitatorium_ptr;
// extern _type_invitatorium  _global_modl_invitatorium;
#define _global_modl_invitatorium (*_global_modl_invitatorium_ptr)

extern _type_posv_citanie *_global_modl_posv_citanie_ptr;
#define _global_modl_posv_citanie (*_global_modl_posv_citanie_ptr)

extern _type_ranne_chvaly *_global_modl_ranne_chvaly_ptr;
// extern _type_ranne_chvaly  _global_modl_ranne_chvaly;
#define _global_modl_ranne_chvaly (*_global_modl_ranne_chvaly_ptr)

extern _type_cez_den_9     *_global_modl_cez_den_9_ptr;
// extern _type_cez_den_9     _global_modl_cez_den_9;
#define _global_modl_cez_den_9 (*_global_modl_cez_den_9_ptr)
extern _type_cez_den_12     *_global_modl_cez_den_12_ptr;
// extern _type_cez_den_12     _global_modl_cez_den_12;
#define _global_modl_cez_den_12 (*_global_modl_cez_den_12_ptr)
extern _type_cez_den_3     *_global_modl_cez_den_3_ptr;
// extern _type_cez_den_3     _global_modl_cez_den_3;
#define _global_modl_cez_den_3 (*_global_modl_cez_den_3_ptr)

// pridane 2003-08-13 pre lahsie pouzitie
#define _global_modl_predpol  _global_modl_cez_den_9
#define _global_modl_napol    _global_modl_cez_den_12
#define _global_modl_popol    _global_modl_cez_den_3

extern _type_vespery      *_global_modl_vespery_ptr;
// extern _type_vespery       _global_modl_vespery;
#define _global_modl_vespery (*_global_modl_vespery_ptr)

extern _type_kompletorium *_global_modl_kompletorium_ptr;
// extern _type_kompletorium _global_modl_kompletorium;
#define _global_modl_kompletorium (*_global_modl_kompletorium_ptr)

// globalna premenna, ktora obsahuje MODL_...
extern short int _global_modlitba;

// globalna premenna, do ktorej ukladaju funkcie vytvor_query_string_... linku tvaru PATH_CGI(SCRIPT_NAME) ++ "?param1=val&param2=val&..."
extern char *_global_link_ptr;
// extern char _global_link[MAX_STR];
#define _global_link _global_link_ptr

extern char *_global_pom_str; // pomocny string pre velke pismena
// extern char _global_pom_str[MAX_STR];

// globalna premenna, do ktorej sa ukladaju info o jednotlivych vyznacnych liturgickych dni, pouzivaju void _dm_...() funkcie a void analyzuj_rok() funkcia
extern _struct_dm *_global_result_ptr;
// extern _struct_dm _global_result;
#define _global_result (*_global_result_ptr)

// globalna premenna, do ktorej sa uklada info o liturgickom roku pouziva void analyzuj_rok() funkcia
extern _struct_lrok *_global_r_ptr;
// extern _struct_lrok _global_r;
#define _global_r (*_global_r_ptr)

// globalna premenna, do ktorej sviatky_svatych() uklada pocet sviatkov (de facto lubovolnych spomienok), ktore pripadaju na dany den
// -- v podstate neuklada do nej, ale v _rozbor_dna() sa do nej priradi vysledok (navratova hodnota) z sviatky_svatych()
extern short int _global_pocet_svatych;

#define OPT_0_SPECIALNE            0
#define OPT_1_CASTI_MODLITBY       1
#define OPT_2_HTML_EXPORT          2
#define OPT_3_SPOLOCNA_CAST        3
#define OPT_4_OFFLINE_EXPORT       4
#define OPT_5_ALTERNATIVES         5

// glob�lna premenn� -- pole -- obsahuj�ca options; p�vodne to boli glob�lne premenn� _global_opt 1..9 at�., obsahuj� pom_MODL_OPT...
extern short int _global_opt[POCET_GLOBAL_OPT];
// glob�lna premenn� -- pole -- obsahuj�ca force options; p�vodne to boli glob�lne premenn� _global_optf 1..9 at�., obsahuj� pom_MODL_OPTF...
extern short int _global_optf[POCET_GLOBAL_OPT];

#define POCET_OPT_0_SPECIALNE               6 // jednotliv� komponenty option 0 -- bity pre force option 0
extern short int _global_opt_specialne[POCET_OPT_0_SPECIALNE];
// 2011-04-08: �prava v�znamu (a interpret�cie) option 0 ==  OPT_0_SPECIALNE (zobrazi�/nezobrazi� "pridan� hodnotu" oproti papierovej LH)
#define BIT_OPT_0_VERSE                     1
#define BIT_OPT_0_REFERENCIE                2
#define BIT_OPT_0_CITANIA                   4
#define BIT_OPT_0_ZJAVENIE_PANA_NEDELA      8 // �i sa Zjavenie P�na sl�vi v nede�u (1) alebo nie (teda 6. janu�ra; hodnota 0 == default)
#define BIT_OPT_0_NANEBOVSTUPNENIE_NEDELA  16 // �i sa Nanebovst�penie P�na sl�vi v nede�u (1) alebo nie (teda vo �tvrtok, na 40.-ty de� po Ve�kono�nej nedeli; hodnota 0 == default)
#define BIT_OPT_0_TELAKRVI_NEDELA          32 // �i sa Najsv. Kristovho tela a krvi sl�vi v nede�u (1) alebo nie (teda vo �tvrtok, 11.-ty de� po Zoslan� Ducha Sv.; hodnota 0 == default)

#define POCET_OPT_1_CASTI_MODLITBY         15 // jednotliv� komponenty option 1 -- bity pre force option 1
extern short int _global_opt_casti_modlitby[POCET_OPT_1_CASTI_MODLITBY];
// 2011-04-11: �prava v�znamu (a interpret�cie) option 1 == OPT_1_CASTI_MODLITBY (zobrazi�/nezobrazi� najm� pevn�/nemenn� s��asti modlitieb, ale aj in�, �o s�/nie s� v LH)
// 2011-10-10: �prava niektor�ch bitov, posunutie popisu na koniec
#define BIT_OPT_1_TEDEUM                    1
#define BIT_OPT_1_RUBRIKY                   2
#define BIT_OPT_1_CHVALOSPEVY               4
#define BIT_OPT_1_SLAVA_OTCU                8
#define BIT_OPT_1_OTCENAS                  16
#define BIT_OPT_1_MCD_DOPLNKOVA            32 // pou��va sa pre modlitbu cez de� -- 1 = alternat�vna, doplnkov� psalm�dia
#define BIT_OPT_1_PC_VIGILIA               64
#define BIT_OPT_1_SPOMIENKA_SPOL_CAST     128 // pri sl�ven� spomienky mo�no pod�a v�eobecn�ch smern�c, �. 235 b), vzia� niektor� �asti alebo zo spolo�nej �asti (1), alebo zo d�a (0)
#define BIT_OPT_1_PLNE_RESP               256
#define BIT_OPT_1_ZALM95                  512 // pou��va sa pre rann� chv�ly a ve�pery -- 1 = vzia� namiesto �almov 24, 67, 100 �alm 95 (0 = bra� pr�slu�n� �alm 24, 67 resp. 100)
#define BIT_OPT_1_PROSBY_ZVOLANIE        1024 // zvolanie v prosb�ch zobrazi� (opakova�) po ka�dej prosbe
#define BIT_OPT_1_SKRY_POPIS             2048
#define BIT_OPT_1_ZOBRAZ_SPOL_CAST       4096
#define BIT_OPT_1_VESP_KRATSIE_PROSBY    8192 // pou�i� (pre ktor�ko�vek de� v roku) krat�ie prosby k ve�per�m z dodatku (0 = default, zo d�a)
#define BIT_OPT_1_MCD_ZALTAR_TRI        16384 // pou��va sa pre modlitbu cez de� -- 1 = psalm�dia sa pou��va z troch t��d�ov �alt�ra (aktu�lny, predch�dzaj�ci, nasleduj�ci)

#define POCET_OPT_2_HTML_EXPORT            15 // jednotliv� komponenty option 2 -- bity pre force option 2
extern short int _global_opt_html_export[POCET_OPT_2_HTML_EXPORT];
// 2011-04-12: �prava v�znamu (a interpret�cie) option 2 (rozli�n� prep�na�e pre [online aj offline] export, napr. tla�idl�, zobrazenie d�tumov a podobne)
// 2012-10-01: doplnen� �al�ie komponenty najm� pre vzh�ad �vodnej obrazovky
#define BIT_OPT_2_ISO_DATUM                 1 // zobrazova� d�tum v ISO form�te YYYY-MM-DD (0 = iba ��slo d�a)
#define BIT_OPT_2_BUTTON_PRVE_VESPERY       2 // zobrazova� prv� ve�pery (a komplet�rium po nich) pre ten de�, pre ktor� patria (teda pre nede�u/sl�vnos�)
#define BIT_OPT_2_FONT_FAMILY               4 // 0 = Serif, 1 = Sans Serif
#define BIT_OPT_2_FONT_NAME_CHOOSER         8 // zobrazi� drop-down list s mo�nos�ou vo�by font (family) name
#define BIT_OPT_2_FONT_SIZE_CHOOSER        16 // zobrazi� drop-down list s mo�nos�ou vo�by ve�kosti fontu
#define BIT_OPT_2_NAVIGATION               32 // zobrazi� navig�ciu v modlitbe (predo�l�, nasledovn� modlitba a pod.)
#define BIT_OPT_2_TEXT_WRAP                64 // zobrazi� zalomenie v textoch modlitby pod�a tla�enej LH
#define BIT_OPT_2_BUTTONY_USPORNE         128 // zobrazi� buttony pre modlitby v �spornej podobe (tabu�ka) kv�li mobiln�m zariadeniam
#define BIT_OPT_2_NOCNY_REZIM             256 // zobrazi� invertovane farby (biele na ciernom)
#define BIT_OPT_2_ROZNE_MOZNOSTI          512 // zobrazi� rozli�n� "hypertextov� odkazy" v modlitbe (napr. pre modlitbu cez de� mo�nos� doplnkovej psalm�die)
#define BIT_OPT_2_HIDE_NAVIG_BUTTONS     1024 // mo�nos� zobrazi�/skry� navig�ciu (tla�idl�) v modlitbe a pre "dnes", ak je zvolen� 6. bit (BIT_OPT_2_NAVIGATION)
#define BIT_OPT_2_HIDE_KALENDAR          2048 // skry� kalend�rik pre "dnes" (0 = zobrazi�)
#define BIT_OPT_2_HIDE_OPTIONS1          4096 // skry� html_text_dalsie_moznosti_1[] pre "dnes" (0 = zobrazi�)
#define BIT_OPT_2_HIDE_OPTIONS2          8192 // skry� html_text_dalsie_moznosti_2[] pre "dnes" (0 = zobrazi�)
#define BIT_OPT_2_ALTERNATIVES          16384 // uk�za� iba jednu alternat�vu (0 = ako doteraz; bu� syst�m vyberie, alebo uk�e v�etky mo�nosti)

#define POCET_OPT_4_OFFLINE_EXPORT          2 // jednotliv� komponenty option 4 -- bity pre force option 4
extern short int _global_opt_offline_export[POCET_OPT_4_OFFLINE_EXPORT];
// 2011-04-08: �prava v�znamu (a interpret�cie) option 4 (rozli�n� prep�na�e pre offline export, napr. aj batch m�d)
#define BIT_OPT_4_MESIAC_RIADOK             1
#define BIT_OPT_4_FNAME_MODL_ID             2 // �i pre n�zov s�boru pou�i� (��seln�) ID modlitby alebo p�smenko modlitby (default)

#define POCET_OPT_5_ALTERNATIVES           11 // jednotliv� komponenty option 5 -- bity pre force option 5
extern short int _global_opt_alternatives[POCET_OPT_5_ALTERNATIVES];
#define BIT_OPT_5_HYMNUS_KOMPL              1 // hymnus na komplet�rium (Cezro�n� obdobie, A/B)
#define BIT_OPT_5_HYMNUS_PC                 2 // hymnus pre posv�tn� ��tanie (Cezro�n� obdobie, I./II.)
#define BIT_OPT_5_HYMNUS_MCD_PREDPOL        4 // hymnus pre modlitbu cez de�, predpoludn�m (Cezro�n� obdobie)
#define BIT_OPT_5_HYMNUS_MCD_NAPOL          8 // hymnus pre modlitbu cez de�, napoludnie (Cezro�n� obdobie)
#define BIT_OPT_5_HYMNUS_MCD_POPOL         16 // hymnus pre modlitbu cez de�, popoludn� (Cezro�n� obdobie)
#define BIT_OPT_5_DOPLNK_PSALM_122_129     32 // pre modlitbu cez de� v doplnkovej psalm�dii namiesto �almu 122 mo�no bra� �alm 129
#define BIT_OPT_5_DOPLNK_PSALM_127_131     64 // pre modlitbu cez de� v doplnkovej psalm�dii namiesto �almu 127 mo�no bra� �alm 131
#define BIT_OPT_5_DOPLNK_PSALM_126_129    128 // pre modlitbu cez de� v doplnkovej psalm�dii namiesto �almu 126 mo�no bra� �alm 129
#define BIT_OPT_5_HYMNUS_VN_PC            256 // hymnus pre posv�tn� ��tanie (Ve�kono�n� obdobie I. po Okt�ve: nede�n� alebo z f�rie)
#define BIT_OPT_5_HYMNUS_VN_RCH           512 // hymnus pre rann� chv�ly (Ve�kono�n� obdobie I. po Okt�ve: nede�n� alebo z f�rie)
#define BIT_OPT_5_HYMNUS_VN_VESP         1024 // hymnus pre ve�pery (Ve�kono�n� obdobie I. po Okt�ve: nede�n� alebo z f�rie)

#define MAX_POCET_OPT                      16 // malo by to by� aspo� maximum z POCET_OPT_0_... a� POCET_OPT_5_...

const short int pocet_opt[POCET_GLOBAL_OPT] = {POCET_OPT_0_SPECIALNE, POCET_OPT_1_CASTI_MODLITBY, POCET_OPT_2_HTML_EXPORT, 0 /* option 3 nem� bitov� komponenty */, POCET_OPT_4_OFFLINE_EXPORT, POCET_OPT_5_ALTERNATIVES};

// globalna premenna, co obsahuje string vypisany na obsazovku
extern char *_global_string;
extern char *_global_string2; // obsahuje I, II, III, IV, V alebo pismeno roka
extern char *_global_string_farba; // 2006-08-19: doplnen�
// 2011-10-04: pridan�, pre titulok modlitby (u� sa nepriliepa do _global_string)
// extern char _global_string_modlitba[SMALL];

extern char *_global_buf; // 2006-08-01: t�to premenn� tie� alokujeme
extern char *_global_buf2; // 2006-08-01: t�to premenn� tie� alokujeme

extern short int _global_linky;

// 2006-07-11: Pridan� kv�li jazykov�m mut�ci�m (breviar.cpp) 
// 2010-08-04: zmenen� _global_language na _global_jazyk (doteraz bolo len pomocou #define)
extern short int _global_jazyk;
// 2010-08-04: pridan� kv�li kalend�rom (napr. reho�n�), s�vis� s jazykov�mi mut�ciami
extern short int _global_kalendar;

extern short int _global_css; // 2008-08-08: Pridan� kv�li r�znym css

extern short int _global_font; // 2011-05-06: Pridan� kv�li r�znym fontom
extern short int _global_font_size; // 2011-05-13: Pridan� kv�li r�znym ve�kostiam fontov

// 2006-10-17: Pridan� kv�li komplet�riu: niekedy obsahuje a� dva �almy
extern short int _global_pocet_zalmov_kompletorium;

extern const char *nazov_jazyka[POCET_JAZYKOV + 1];
extern const char *skratka_jazyka[POCET_JAZYKOV + 1];
extern const char *postfix_jazyka[POCET_JAZYKOV + 1];

extern const char *nazov_kalendara_short[POCET_KALENDAROV + 1];
extern const char *skratka_kalendara[POCET_KALENDAROV + 1];

extern const char *nazov_css[POCET_CSS + 1];
extern const char *skratka_css[POCET_CSS + 1];
extern const char *nazov_css_invert_colors;

extern const char *charset_jazyka[POCET_JAZYKOV + 1];

extern const char *nazov_fontu[POCET_FONTOV + 1];
extern const char *nazov_fontu_CHECKBOX[POCET_JAZYKOV + 1];
extern const char *nazov_fontu_CSS[POCET_FONTOV + 1];

extern const char *nazov_font_size_jazyk[POCET_FONT_SIZE + 1][POCET_JAZYKOV + 1];
extern const char *nazov_font_size_css[POCET_FONT_SIZE + 1];

//---------------------------------------------------------------------

//---------------------------------------------------------------------
// tu nasleduju funkcie(), ibaze by som inkludoval "liturgia.cpp"

short int _allocate_global_var(void);
short int _deallocate_global_var(void);

short int cislo_mesiaca(char *mesiac);
char *caps_BIG(const char *input);
char *remove_diacritics(const char *input);
char *convert_nonbreaking_spaces(const char *input);

char *_vytvor_string_z_datumu(short int den, short int mesiac, short int rok, short int _case, short int typ, short int align);
// pod�a toho, ako sa funkcia vol�, ur��m case (pou�itie ve�k�ch/mal�ch p�smen)
#define vytvor_global_link(den, mesiac, rok, typ, align)	_vytvor_global_link(den, mesiac, rok, CASE_case, typ, align)
#define vytvor_global_link_class(den, mesiac, rok, typ, align, html_class)	_vytvor_global_link(den, mesiac, rok, CASE_case, typ, align, html_class)
#define Vytvor_global_link(den, mesiac, rok, typ, align)	_vytvor_global_link(den, mesiac, rok, CASE_Case, typ, align)
#define VYTVOR_global_link(den, mesiac, rok, typ, align)	_vytvor_global_link(den, mesiac, rok, CASE_CASE, typ, align)
// 2011-05-11: doplnen� nov� parameter align -- �i zarovna� jednocifern� d�tumy (��slovka d�a) medzerou z�ava
void _vytvor_global_link(short int den, short int mesiac, short int rok, short int _case, short int typ, short int align);
void _vytvor_global_link(short int den, short int mesiac, short int rok, short int _case, short int typ, short int align, const char * html_class);

#define PRILEP_REQUEST_OPTIONS_DEFAULT   0
#define PRILEP_REQUEST_OPTIONS_AJ_FORCE  1
#define PRILEP_REQUEST_OPTIONS_LEN_FORCE 2
void prilep_request_options(char pom2 [MAX_STR], char pom3 [MAX_STR], short int force_opt = PRILEP_REQUEST_OPTIONS_DEFAULT); // 2013-03-07: pokus; pravdepodobne PRILEP_REQUEST_OPTIONS_LEN_FORCE je neu�ito�n� a PRILEP_REQUEST_OPTIONS_AJ_FORCE mo�no trocha riskantn�...

short int prestupny(short int);
short int pocet_dni_v_roku(short int);
short int poradie(short int den, short int mesiac, short int rok);
short int poradie(_struct_den_mesiac den_a_mesiac, short int rok);
short int zjavenie_pana(short int rok);
long juliansky_datum(short int por, short int rok);
long juliansky_datum(short int den, short int mesiac, short int rok);
_struct_den_mesiac velkonocna_nedela(short int R);
short int _velkonocna_nedela(short int rok);
short int den_v_tyzdni(short int por, short int rok);
short int den_v_tyzdni(short int den, short int mesiac, short int rok);
short int den_v_tyzdni(_struct_den_mesiac den_a_mesiac, short int rok);
unsigned char _nedelne_pismeno(short int rok);
char nedelne_pismeno(short int rok);
unsigned char _nedelne_pismeno(short int por, short int rok);
char nedelne_pismeno(short int por, short int rok);
char nedelne_pismeno(short int den, short int mesiac, short int rok);
unsigned char _nedelne_pismeno(short int den, short int mesiac, short int rok);
unsigned char _nedelne_pismeno(_struct_den_mesiac den_a_mesiac, short int rok);
char nedelne_pismeno(_struct_den_mesiac den_a_mesiac, short int rok);
_struct_den_mesiac por_den_mesiac(short int poradie, short int rok);
#ifdef FUNKCIE_PRE_SPECIALNE_DNI
short int _svatej_rodiny(short int rok);
short int _krst_krista_pana(short int rok);
short int _popolcova_streda(short int rok);
short int _nanebovstupenie(short int rok);
#endif
short int _zoslanie_ducha(short int rok);
short int _prva_adventna_nedela(short int rok);
_struct_den_mesiac prva_adventna_nedela(short int rok);
short int nedelny_cyklus(short int por, short int rok);
short int nedelny_cyklus(short int den, short int mesiac, short int rok);
short int nedelny_cyklus(_struct_den_mesiac den_a_mesiac, short int rok);
short int ferialny_cyklus(short int por, short int rok);
short int ferialny_cyklus(short int den, short int mesiac, short int rok);
_struct_dm por_den_mesiac_dm(short int poradie, short int rok);
short int tyzden_cez_rok_po_vn(short int rok);
short int cislo_nedele_cez_rok_po_vn(short int rok);
void init_global_pm_sobota(void);
void _dm_popolcova_streda(short int rok, short int _vn);
void _dm_nanebovstupenie(short int rok, short int _vn);
void _dm_zoslanie_ducha(short int rok, short int _vn);
void _dm_prva_adventna_nedela(short int rok, short int p2);
void _dm_svatej_rodiny(short int rok);
void _dm_krst_krista_pana(short int rok);
void _dm_velkonocna_nedela(short int rok, short int _vn);

void analyzuj_rok(short int year);

#define UNKNOWN_PORADIE_SVATEHO 0
// 28/03/2000A.D.: naschval < 0, aby nebol problem s porovnanim s _global_pocet_svatych v _rozbor_dna() 
// 2009-03-19: presunut� z breviar.cpp
// 2009-03-27: po z�fal�ch pokusoch dnes - napokon som zistil, �e u� je �plne jedno, ak� hodnotu bude t�to kon�tanta ma�, preto som ju dal op� na 0

// definovany 2003-08-11 na zaklade funkcie _init_dm() 
// upraven� 2007-08-16, preto�e sa pou��va aj v _main_dnes()
#define _INIT_DM(a) {\
	a.den = 1;    \
	a.mesiac = 1; \
	a.rok = 1900; \
	a.denvt = 0;  \
	a.denvr = 1;  \
	a.litrok = 'A'; \
	a.tyzden = 1;   \
	a.tyzzal = 1;   \
	a.litobd = OBD_CEZ_ROK; \
	a.typslav = SLAV_NEURCENE; \
	a.typslav_lokal = LOKAL_SLAV_NEURCENE; \
	a.smer = 99; \
	a.prik = NIE_JE_PRIKAZANY_SVIATOK; \
	a.spolcast = _encode_spol_cast(MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA, MODL_SPOL_CAST_NEURCENA); \
	mystrcpy(a.meno, STR_UNDEF, MENO_SVIATKU); \
	a.farba = LIT_FARBA_NEURCENA;\
	a.kalendar = KALENDAR_NEURCENY;\
}

// inicializacne definy pridane 2003-08-13
#define _INIT_ANCHOR_AND_FILE(a) {\
	mystrcpy(a.file, STR_UNDEF, MAX_STR_AF_FILE); \
	mystrcpy(a.anchor, STR_UNDEF, MAX_STR_AF_ANCHOR); \
}

// 2010-05-21: roz��ren� kv�li spomienkam a �ubovo�n�m spomienkam v p�stnom obdob� (zobrazenie po modlitbe d�a p�stnej f�rie)
#define _INIT_TMODLITBA1(a) {\
	a.alternativy = 0; \
	_INIT_ANCHOR_AND_FILE(a.popis); \
	_INIT_ANCHOR_AND_FILE(a.hymnus); \
	_INIT_ANCHOR_AND_FILE(a.antifona1); \
	_INIT_ANCHOR_AND_FILE(a.zalm1); \
	_INIT_ANCHOR_AND_FILE(a.antifona2); \
	_INIT_ANCHOR_AND_FILE(a.zalm2); \
	_INIT_ANCHOR_AND_FILE(a.antifona3); \
	_INIT_ANCHOR_AND_FILE(a.zalm3); \
	_INIT_ANCHOR_AND_FILE(a.kcitanie); \
	_INIT_ANCHOR_AND_FILE(a.kresponz); \
	_INIT_ANCHOR_AND_FILE(a.benediktus); \
	_INIT_ANCHOR_AND_FILE(a.prosby); \
	_INIT_ANCHOR_AND_FILE(a.modlitba); \
	_INIT_ANCHOR_AND_FILE(a.ant_spomprivileg); \
	_INIT_ANCHOR_AND_FILE(a.modlitba_spomprivileg); \
};

#define _INIT_TMODLITBA2(a) {\
	a.alternativy = 0; \
	_INIT_ANCHOR_AND_FILE(a.popis); \
	_INIT_ANCHOR_AND_FILE(a.hymnus); \
	_INIT_ANCHOR_AND_FILE(a.antifona1); \
	_INIT_ANCHOR_AND_FILE(a.zalm1); \
	_INIT_ANCHOR_AND_FILE(a.antifona2); \
	_INIT_ANCHOR_AND_FILE(a.zalm2); \
	_INIT_ANCHOR_AND_FILE(a.antifona3); \
	_INIT_ANCHOR_AND_FILE(a.zalm3); \
	_INIT_ANCHOR_AND_FILE(a.kcitanie); \
	_INIT_ANCHOR_AND_FILE(a.kresponz); \
	_INIT_ANCHOR_AND_FILE(a.modlitba); \
};

// 2006-10-11 doplnen�
#define _INIT_TMODLITBA3(a) {\
	a.alternativy = 0; \
	a.pocet_zalmov = 1;\
	_INIT_ANCHOR_AND_FILE(a.popis); \
	_INIT_ANCHOR_AND_FILE(a.hymnus); \
	_INIT_ANCHOR_AND_FILE(a.antifona1); \
	_INIT_ANCHOR_AND_FILE(a.zalm1); \
	_INIT_ANCHOR_AND_FILE(a.antifona2); \
	_INIT_ANCHOR_AND_FILE(a.zalm2); \
	_INIT_ANCHOR_AND_FILE(a.kcitanie); \
	_INIT_ANCHOR_AND_FILE(a.kresponz); \
	_INIT_ANCHOR_AND_FILE(a.nunc_dimittis); \
	_INIT_ANCHOR_AND_FILE(a.modlitba); \
};

// 2006-10-11 doplnen�
#define _INIT_TMODLITBA4(a) {\
	_INIT_ANCHOR_AND_FILE(a.popis); \
	_INIT_ANCHOR_AND_FILE(a.antifona1); \
	_INIT_ANCHOR_AND_FILE(a.zalm1); \
};

// 2011-03-25: doplnen� pre posv�tn� ��tanie
#define _INIT_TMODLITBA5(a) {\
	a.alternativy = 0; \
	_INIT_ANCHOR_AND_FILE(a.popis); \
	_INIT_ANCHOR_AND_FILE(a.hymnus); \
	_INIT_ANCHOR_AND_FILE(a.antifona1); \
	_INIT_ANCHOR_AND_FILE(a.zalm1); \
	_INIT_ANCHOR_AND_FILE(a.antifona2); \
	_INIT_ANCHOR_AND_FILE(a.zalm2); \
	_INIT_ANCHOR_AND_FILE(a.antifona3); \
	_INIT_ANCHOR_AND_FILE(a.zalm3); \
	_INIT_ANCHOR_AND_FILE(a.kresponz); \
	_INIT_ANCHOR_AND_FILE(a.citanie1); \
	_INIT_ANCHOR_AND_FILE(a.citanie2); \
	_INIT_ANCHOR_AND_FILE(a.citanie_spomprivileg); \
	_INIT_ANCHOR_AND_FILE(a.ant_chval); \
	_INIT_ANCHOR_AND_FILE(a.chval1); \
	_INIT_ANCHOR_AND_FILE(a.chval2); \
	_INIT_ANCHOR_AND_FILE(a.chval3); \
	_INIT_ANCHOR_AND_FILE(a.evanjelium); \
	_INIT_ANCHOR_AND_FILE(a.modlitba); \
};

#define Log_struktura_dm Log("  <dm>"); Log
void Log(_struct_dm g);
#define Log_struktura_rok Log("  <rok>"); Log
void Log(_struct_lrok r);
#define Log_struktura_tm1 Log("  <tm1>"); Log
void Log(struct tmodlitba1);
#define Log_struktura_tm2 Log("  <tm2>"); Log
void Log(struct tmodlitba2);
#define Log_struktura_tm3 Log("  <tm3>"); Log
void Log(struct tmodlitba3);
#define Log_struktura_tm4 Log("  <tm4>"); Log
void Log(struct tmodlitba4);
#define Log_struktura_tm5 Log("  <tm5>"); Log
void Log(struct tmodlitba5);

int _encode_spol_cast(short int, short int, short int);
int _encode_spol_cast(short int, short int);
int _encode_spol_cast(short int);
_struct_sc _decode_spol_cast(int);

extern const char *text_JAN_KRST[POCET_JAZYKOV + 1];
extern const char *text_POPOLCOVA_STREDA[POCET_JAZYKOV + 1];
extern const char *text_NANEBOVSTUPENIE_PANA[POCET_JAZYKOV + 1];
extern const char *text_VELKONOCNA_NEDELA[POCET_JAZYKOV + 1];
extern const char *text_NEDELA_PANOVHO_ZMRTVYCHVSTANIA[POCET_JAZYKOV + 1];
extern const char *text_NEDELA_VO_VELKONOCNEJ_OKTAVE[POCET_JAZYKOV + 1];
extern const char *text_DEN_VO_VELKONOCNEJ_OKTAVE[POCET_JAZYKOV + 1];
extern const char *text_NAJSVATEJSEJ_TROJICE[POCET_JAZYKOV + 1];
extern const char *text_KRISTA_KRALA[POCET_JAZYKOV + 1];
extern const char *text_NAJSV_KRISTOVHO_TELA_A_KRVI[POCET_JAZYKOV + 1];
extern const char *text_NAJSV_SRDCA_JEZISOVHO[POCET_JAZYKOV + 1];
extern const char *text_NEPOSKVRNENEHO_SRDCA_PM[POCET_JAZYKOV + 1];
extern const char *text_NARODENIE_PANA[POCET_JAZYKOV + 1];
extern const char *text_ZOSLANIE_DUCHA_SVATEHO[POCET_JAZYKOV + 1];
extern const char *text_PRVA_ADVENTNA_NEDELA[POCET_JAZYKOV + 1];
extern const char *text_NEDELA_SV_RODINY[POCET_JAZYKOV + 1];
extern const char *text_SPOMIENKA_PM_V_SOBOTU[POCET_JAZYKOV + 1];
extern const char *text_ZELENY_STVRTOK[POCET_JAZYKOV + 1];
extern const char *text_VELKY_PIATOK[POCET_JAZYKOV + 1];
extern const char *text_BIELA_SOBOTA[POCET_JAZYKOV + 1];
extern const char *text_KVETNA_NEDELA[POCET_JAZYKOV + 1];
extern const char *text_DRUHA_NEDELA_PO_NAR_PANA[POCET_JAZYKOV + 1];
extern const char *text_PO_POPOLCOVEJ_STREDE[POCET_JAZYKOV + 1];
extern const char *text_V_OKTAVE_NARODENIA[POCET_JAZYKOV + 1];

extern const char *text_DEC_08[POCET_JAZYKOV + 1];
extern const char *text_AUG_15[POCET_JAZYKOV + 1];
extern const char *text_NOV_01[POCET_JAZYKOV + 1];

extern const char *text_ZAKONCENIE_SKRZE_dlhe[POCET_JAZYKOV + 1];
extern const char *text_ZAKONCENIE_SKRZE_kratke[POCET_JAZYKOV + 1];
extern const char *text_ZAKONCENIE_LEBO_ON_dlhe[POCET_JAZYKOV + 1];
extern const char *text_ZAKONCENIE_LEBO_ON_kratke[POCET_JAZYKOV + 1];
extern const char *text_ZAKONCENIE_LEBO_TY_dlhe[POCET_JAZYKOV + 1];
extern const char *text_ZAKONCENIE_LEBO_TY_kratke[POCET_JAZYKOV + 1];
extern const char *text_ZAKONCENIE_ON_JE_dlhe; // len SK
extern const char *text_ZAKONCENIE_ON_JE_kratke; // len SK
extern const char *text_ZAKONCENIE_KTORY_JE_dlhe; // len SK
extern const char *text_ZAKONCENIE_KTORY_JE_kratke; // len SK
extern const char *text_ZAKONCENIE_O_TO_TA_PROSIME[POCET_JAZYKOV + 1];

extern const char *text_PRO_OP[POCET_JAZYKOV + 1];

extern const char *html_text_batch_Back[POCET_JAZYKOV + 1];
extern const char *html_text_batch_Prev[POCET_JAZYKOV + 1];
extern const char *html_text_batch_Next[POCET_JAZYKOV + 1];

#endif // __LITURGIA_H_

