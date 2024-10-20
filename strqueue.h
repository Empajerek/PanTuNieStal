#ifndef STRQUEUE_H_
#define STRQUEUE_H_

#ifdef __cplusplus
    #include <cstddef>
#else
    #include <stddef.h>
#endif

#ifdef __cplusplus
namespace cxx {
extern "C" {
#endif

unsigned long strqueue_new();
void strqueue_delete(unsigned long id);
size_t strqueue_size(unsigned long id);
void strqueue_insert_at(unsigned long id, size_t position, const char* str);
void strqueue_remove_at(unsigned long id, size_t position);
const char* strqueue_get_at(unsigned long id, size_t position);
void strqueue_clear(unsigned long id);
int strqueue_comp(unsigned long id1, unsigned long id2);

#ifdef __cplusplus
}
} // namespace cxx
#endif

#endif // STRQUEUE_H_

/*
                              ....
                           ,;;'''';;,                    ,;;;;,
                 ,        ;;'      `;;,               .,;;;'   ;
              ,;;;       ;;          `;;,';;;,.     ,%;;'     '
            ,;;,;;       ;;         ,;`;;;, `;::.  %%;'
           ;;;,;;;       `'       ,;;; ;;,;;, `::,%%;'
           ;;;,;;;,          .,%%%%%'% ;;;;,;;   %;;;
 ,%,.      `;;;,;;;,    .,%%%%%%%%%'%; ;;;;;,;;  %;;;
;,`%%%%%%%%%%`;;,;;'%%%%%%%%%%%%%'%%'  `;;;;;,;, %;;;
;;;,`%%%%%%%%%%%,; ..`%%%%%%%%;'%%%'    `;;;;,;; %%;;
 `;;;;;,`%%%%%,;;/, .. `"""'',%%%%%      `;;;;;; %%;;,
    `;;;;;;;,;;/////,.    ,;%%%%%%%        `;;;;,`%%;;
           ;;;/%%%%,%///;;;';%%%%%%,          `;;;%%;;,
          ;;;/%%%,%%%%%/;;;';;'%%%%%,             `%%;;
         .;;/%%,%%%%%//;;'  ;;;'%%%%%,             %%;;,
         ;;//%,%%%%//;;;'   `;;;;'%%%%             `%;;;
         ;;//%,%//;;;;'      `;;;;'%%%              %;;;,
         `;;//,/;;;'          `;;;'%%'              `%;;;
           `;;;;'               `;'%'                `;;;;
                                  '      .,,,.        `;;;;
                                      ,;;;;;;;;;;,     `;;;;
                                     ;;;'    ;;;,;;,    `;;;;
                                     ;;;      ;;;;,;;.   `;;;;
                                      `;;      ;;;;;,;;   ;;;;
                                        `'      `;;;;,;;  ;;;;
                                                   `;;,;, ;;;;
                                                      ;;, ;;;;
                                                        ';;;;;
                                                         ;;;;;
                                                        .;;;;'
                                                       .;;;;'
                                                      ;;;;;'
                                                     ,;;;;'
*/
