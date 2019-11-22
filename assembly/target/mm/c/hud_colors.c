#include <stdbool.h>
#include "z64.h"

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} z64_color_rgb8_t;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} z64_color_rgba8_t;

// Infinite magic meter color (blue).
z64_color_rgb8_t MAGIC_INF_COLOR_CONFIG = { 0x00, 0x00, 0xC8 };

// Magic meter color (green).
z64_color_rgb8_t MAGIC_COLOR_CONFIG = { 0x00, 0xC8, 0x00 };

// Map color.
z64_color_rgba8_t MAP_COLOR_CONFIG = { 0x00, 0xFF, 0xFF, 0xA0 };

// Map player cursor color.
z64_color_rgb8_t MAP_PLAYER_CURSOR_COLOR_CONFIG = { 0xC8, 0xFF, 0x00 };

// Map entrance cursor color.
z64_color_rgb8_t MAP_ENTRANCE_CURSOR_COLOR_CONFIG = { 0xC8, 0x00, 0x00 };

static uint32_t color_rgb8_to_int(z64_color_rgb8_t color, uint8_t alpha) {
    return (color.r << 24) | (color.g << 16) | (color.b << 8) | alpha;
}

static uint32_t color_rgba8_to_int(z64_color_rgba8_t color) {
    return (color.r << 24) | (color.g << 16) | (color.b << 8) | color.a;
}

uint32_t get_magic_meter_color(bool inf) {
    uint8_t alpha = z64_game.sub_169E8.rupees_alpha & 0xFF;
    if (inf) {
        return color_rgb8_to_int(MAGIC_INF_COLOR_CONFIG, alpha);
    } else {
        return color_rgb8_to_int(MAGIC_COLOR_CONFIG, alpha);
    }
}

uint32_t get_map_color() {
    return color_rgba8_to_int(MAP_COLOR_CONFIG);
}

uint32_t get_map_player_cursor_color() {
    uint8_t alpha = z64_game.sub_169E8.minimap_alpha & 0xFF;
    return color_rgb8_to_int(MAP_PLAYER_CURSOR_COLOR_CONFIG, alpha);
}

uint32_t get_map_entrance_cursor_color() {
    uint8_t alpha = z64_game.sub_169E8.minimap_alpha & 0xFF;
    return color_rgb8_to_int(MAP_ENTRANCE_CURSOR_COLOR_CONFIG, alpha);
}
