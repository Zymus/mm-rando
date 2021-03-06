#ifndef MISC_H
#define MISC_H

#include <stdbool.h>
#include "z2.h"

union hash {
    union {
        u8 primary[0x04];
        u32 value;
    };
    u8 full[0x10];
};

enum crit_wiggle_state {
    CRIT_WIGGLE_DEFAULT,
    CRIT_WIGGLE_ALWAYS_ON,
    CRIT_WIGGLE_ALWAYS_OFF,
};

enum quest_consume_state {
    QUEST_CONSUME_DEFAULT,
    QUEST_CONSUME_ALWAYS,
    QUEST_CONSUME_NEVER,
};

// Magic number for misc_config: "MISC"
#define MISC_CONFIG_MAGIC 0x4D495343

struct misc_config {
    u32 magic;              /* 0x0000 */
    u32 version;            /* 0x0004 */
    union hash hash;        /* 0x0008 */
    union {
        struct {
            // Version 0 flags
            u32 crit_wiggle        : 2;
            u32 draw_hash          : 1;
            u32 fast_push          : 1;
            u32 ocarina_underwater : 1;
            u32 quest_item_storage : 1;

            // Version 1 flags
            u32 close_cows         : 1;
            u32 freestanding       : 1;
            u32 quest_consume      : 2;
            u32 arrow_cycle        : 1;
            u32 arrow_magic_show   : 1;
            u32                    : 20;
        };
        u32 flags;          /* 0x0018 */
    };
    union {
        struct {
            // Version 1 flags
            u32 vanilla_layout     : 1;
            u32                    : 31;
        };
        u32 internal;
    };                      /* 0x001C */
};                          /* 0x0020 */

extern struct misc_config MISC_CONFIG;

bool misc_can_use_ocarina_underwater();
struct misc_config* misc_get_config();
f32 misc_get_push_block_speed(z2_actor_t *actor, z2_game_t *game);
void misc_init(void);

#endif // MISC_H
