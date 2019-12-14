#include <stdbool.h>
#include "color.h"
#include "reloc.h"
#include "z64.h"

// Uncomment to apply theme for testing
// #define USE_THEME

struct hud_color_config {
    uint32_t version;

    // Version 0
    z64_color_rgb8_t button_a;
    z64_color_rgb8_t button_b;
    z64_color_rgb8_t button_c;
    z64_color_rgb8_t button_start;
    z64_color_rgb8_t clock_emblem;
    z64_color_rgb8_t clock_emblem_inverted_1;
    z64_color_rgb8_t clock_emblem_inverted_2;
    z64_color_rgb8_t clock_emblem_sun;
    z64_color_rgb8_t clock_moon;
    z64_color_rgb8_t clock_sun;
    z64_color_rgb8_t heart;
    z64_color_rgb8_t heart_dd;
    z64_color_rgb8_t magic;
    z64_color_rgb8_t magic_inf;
    z64_color_rgba8_t map;
    z64_color_rgb8_t map_entrance_cursor;
    z64_color_rgb8_t map_player_cursor;
    z64_color_rgb8_t rupee[3];
};

struct hud_color_config HUD_COLOR_CONFIG = {
    .version = 0,

    // Version 0
    .button_a                = { 0x64, 0xC8, 0xFF },
    .button_b                = { 0x64, 0xFF, 0x78 },
    .button_c                = { 0xFF, 0xF0, 0x00 },
    .button_start            = { 0xFF, 0x82, 0x3C },
    .clock_emblem            = { 0x00, 0xAA, 0x64 },
    .clock_emblem_inverted_1 = { 0x64, 0xCD, 0xFF },
    .clock_emblem_inverted_2 = { 0x00, 0x9B, 0xFF },
    .clock_emblem_sun        = { 0xFF, 0xFF, 0x6E },
    .clock_moon              = { 0xFF, 0xFF, 0x37 },
    .clock_sun               = { 0xFF, 0x64, 0x6E },
    .heart                   = { 0xFF, 0x46, 0x32 },
    .heart_dd                = { 0xC8, 0x00, 0x00 },
    .magic                   = { 0x00, 0xC8, 0x00 },
    .magic_inf               = { 0x00, 0x00, 0xC8 },
    .map                     = { 0x00, 0xFF, 0xFF, 0xA0 },
    .map_entrance_cursor     = { 0xC8, 0x00, 0x00 },
    .map_player_cursor       = { 0xC8, 0xFF, 0x00 },
    .rupee                   = {
                               { 0xC8, 0xFF, 0x64 },
                               { 0xAA, 0xAA, 0xFF },
                               { 0xFF, 0x69, 0x69 },
    },
};

static uint32_t color_rgb8_to_int(z64_color_rgb8_t color, uint8_t alpha) {
    return (color.r << 24) | (color.g << 16) | (color.b << 8) | alpha;
}

static uint32_t color_rgba8_to_int(z64_color_rgba8_t color) {
    return (color.r << 24) | (color.g << 16) | (color.b << 8) | color.a;
}

uint32_t get_magic_meter_color(bool inf) {
    uint8_t alpha = z64_game.sub_169E8.rupees_alpha & 0xFF;
    if (inf) {
        return color_rgb8_to_int(HUD_COLOR_CONFIG.magic_inf, alpha);
    } else {
        return color_rgb8_to_int(HUD_COLOR_CONFIG.magic, alpha);
    }
}

uint32_t get_map_color() {
    return color_rgba8_to_int(HUD_COLOR_CONFIG.map);
}

uint32_t get_map_player_cursor_color() {
    uint8_t alpha = z64_game.sub_169E8.minimap_alpha & 0xFF;
    return color_rgb8_to_int(HUD_COLOR_CONFIG.map_player_cursor, alpha);
}

uint32_t get_map_entrance_cursor_color() {
    uint8_t alpha = z64_game.sub_169E8.minimap_alpha & 0xFF;
    return color_rgb8_to_int(HUD_COLOR_CONFIG.map_entrance_cursor, alpha);
}

uint32_t get_clock_emblem_color() {
    uint8_t alpha = (uint8_t)(*(uint16_t *)(0x801BFB2C));
    return color_rgb8_to_int(HUD_COLOR_CONFIG.clock_emblem, alpha);
}

uint16_t get_clock_emblem_inverted_color(uint8_t idx) {
    z64_color_rgb8_t colors;
    int16_t mode = *(int16_t *)0x801BFBE8;

    if (idx > 2) {
        return 0;
    }

    // Mode should be either 0 (first color) or 1 (second color)
    if (!mode) {
        colors = HUD_COLOR_CONFIG.clock_emblem_inverted_1;
    } else {
        colors = HUD_COLOR_CONFIG.clock_emblem_inverted_2;
    }

    return colors.bytes[idx];
}

uint32_t get_clock_emblem_sun_color(uint16_t alpha) {
    return color_rgb8_to_int(HUD_COLOR_CONFIG.clock_emblem_sun, alpha & 0xFF);
}

uint32_t get_clock_sun_color() {
    uint8_t alpha = (*(uint16_t *)0x801BFB2C) & 0xFF;
    return color_rgb8_to_int(HUD_COLOR_CONFIG.clock_sun, alpha);
}

uint32_t get_clock_moon_color() {
    uint8_t alpha = (*(uint16_t *)0x801BFB2C) & 0xFF;
    return color_rgb8_to_int(HUD_COLOR_CONFIG.clock_moon, alpha);
}

uint32_t get_a_button_color() {
    uint8_t alpha = z64_game.sub_169E8.a_button_alpha & 0xFF;
    return color_rgb8_to_int(HUD_COLOR_CONFIG.button_a, alpha);
}

uint32_t get_b_button_color() {
    // Alpha won't be used but set it anyway
    uint8_t alpha = z64_game.sub_169E8.b_button_alpha & 0xFF;
    return color_rgb8_to_int(HUD_COLOR_CONFIG.button_b, alpha);
}

uint32_t get_c_button_color(uint16_t alpha) {
    return color_rgb8_to_int(HUD_COLOR_CONFIG.button_c, alpha & 0xFF);
}

uint32_t get_start_button_color(uint16_t alpha) {
    return color_rgb8_to_int(HUD_COLOR_CONFIG.button_start, alpha & 0xFF);
}

void update_heart_colors(z64_game_t *game) {
    // Normal heart colors
    z64_color_rgb16_2_t *heart = &(z64_game.sub_169E8.heart_inner_rgb);
    z64_color_rgb16_t *heart_beating = &(z64_game.sub_169E8.heartbeat_inner_rgb);

    // Double defense heart colors
    z64_color_rgb16_t *heart_dd = &(z64_file.heart_dd_rgb);
    z64_color_rgb16_t *heart_dd_beating = &(z64_file.heart_dd_beating_rgb);

    // This function writes constant values to where the heart colors are stored.
    // It might also do other things.
    z64_WriteHeartColors(game);

    // Update heart colors (normal)
    heart->r1 = HUD_COLOR_CONFIG.heart.r;
    heart->g1 = HUD_COLOR_CONFIG.heart.g;
    heart->b1 = HUD_COLOR_CONFIG.heart.b;
    heart_beating->r = HUD_COLOR_CONFIG.heart.r;
    heart_beating->g = HUD_COLOR_CONFIG.heart.g;
    heart_beating->b = HUD_COLOR_CONFIG.heart.b;

    // Update heart colors (double defense)
    heart_dd->r = HUD_COLOR_CONFIG.heart_dd.r;
    heart_dd->g = HUD_COLOR_CONFIG.heart_dd.g;
    heart_dd->b = HUD_COLOR_CONFIG.heart_dd.b;
    heart_dd_beating->r = HUD_COLOR_CONFIG.heart_dd.r;
    heart_dd_beating->g = HUD_COLOR_CONFIG.heart_dd.g;
    heart_dd_beating->b = HUD_COLOR_CONFIG.heart_dd.b;
}

static void update_rupee_colors(uint16_t *rupee_colors) {
    for (int i = 0; i < 3; i++) {
        int idx = i * 3;
        rupee_colors[idx] = HUD_COLOR_CONFIG.rupee[i].r;
        rupee_colors[idx + 1] = HUD_COLOR_CONFIG.rupee[i].g;
        rupee_colors[idx + 2] = HUD_COLOR_CONFIG.rupee[i].b;
    }
}

static void apply_objectively_best_theme() {
#define APPLY(FIELD, R, G, B)     \
    HUD_COLOR_CONFIG.FIELD.r = R; \
    HUD_COLOR_CONFIG.FIELD.g = G; \
    HUD_COLOR_CONFIG.FIELD.b = B;

    APPLY(button_a,                0xFF, 0x60, 0xA0);
    APPLY(button_b,                0x58, 0xA4, 0xED);
    APPLY(button_c,                0xF0, 0xF0, 0xF0);
    APPLY(clock_emblem,            0xF0, 0xF0, 0xF0);
    APPLY(clock_emblem_inverted_1, 0xFF, 0xA0, 0xC0);
    APPLY(clock_emblem_inverted_2, 0xFF, 0xC0, 0xE0);
    APPLY(heart,                   0x58, 0xA4, 0xED);
    APPLY(heart_dd,                0x14, 0x87, 0xCD);
    APPLY(magic,                   0xFF, 0x60, 0xA0);
    APPLY(magic_inf,               0xFF, 0x80, 0xC0);
    APPLY(map,                     0xF0, 0xF0, 0xF0);
    APPLY(map_entrance_cursor,     0x38, 0x94, 0xDD);
    APPLY(map_player_cursor,       0xFF, 0x60, 0xA0);
    APPLY(rupee[0],                0xF0, 0xF0, 0xF0);
    APPLY(rupee[1],                0xFF, 0x60, 0xA0);
    APPLY(rupee[2],                0x58, 0xA4, 0xED);

#undef APPLY
}

void hud_colors_init() {
    uint16_t *rupee_colors = (uint16_t *)0x801BFD2C;

#ifdef USE_THEME
    // Apply theme
    apply_objectively_best_theme();
#endif // USE_THEME

    // The rupee colors never seem to get modified, so just update them once
    update_rupee_colors(rupee_colors);
}

void hud_colors_main_menu_init() {
    // Update rupee colors
    update_rupee_colors(z64_file_select_ctxt.rupee_colors);

    // Update hearts colors
    z64_file_select_ctxt.heart_rgb[0].r = HUD_COLOR_CONFIG.heart.r;
    z64_file_select_ctxt.heart_rgb[0].g = HUD_COLOR_CONFIG.heart.g;
    z64_file_select_ctxt.heart_rgb[0].b = HUD_COLOR_CONFIG.heart.b;
    z64_file_select_ctxt.heart_rgb[1].r = HUD_COLOR_CONFIG.heart_dd.r;
    z64_file_select_ctxt.heart_rgb[1].g = HUD_COLOR_CONFIG.heart_dd.g;
    z64_file_select_ctxt.heart_rgb[1].b = HUD_COLOR_CONFIG.heart_dd.b;
}
