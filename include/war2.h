/*
 * war2.h
 * libwar2
 *
 * Copyright (c) 2014 - 2015 Jean Guyomarc'h
 */

#ifndef _WAR2_H_
#define _WAR2_H_
#ifdef __cplusplus
extern "C" <%
#endif

#include "pud.h"

Pud_Bool war2_init(void);
void war2_shutdown(void);

typedef struct _War2_Data War2_Data;
typedef struct _War2_Tileset_Descriptor War2_Tileset_Descriptor;
typedef struct _War2_Units_Descriptor War2_Units_Descriptor;
typedef struct _War2_Color War2_Color;

struct _War2_Data
{
   unsigned char *mem_map;
   size_t         mem_map_size;
   unsigned char *ptr;

   uint32_t     magic;
   uint16_t     fid;

   uint16_t        entries_count;
   unsigned char **entries;

   unsigned int verbose;
};

struct _War2_Tileset_Descriptor
{
   Pud_Era       era;
   Pud_Color     palette[256];
   int           tiles;
};

struct _War2_Units_Descriptor
{
   Pud_Color    palette[256];
   Pud_Player   color;
   Pud_Side     race;
   int          units;
};

typedef void (*War2_Tileset_Decode_Func)(const Pud_Color *tile, int w, int h, const War2_Tileset_Descriptor *ts, int img_nb);
typedef void (*War2_Units_Decode_Func)(const Pud_Color *sprite, int w, int h, const War2_Units_Descriptor *ts, int img_nb);

War2_Data *war2_open(const char *file, int verbose);
void war2_close(War2_Data *w2);
void war2_verbosity_set(War2_Data *w2, int level);

unsigned char *war2_entry_extract(War2_Data *w2, unsigned int entry, size_t *size_ret);
unsigned char *war2_palette_extract(War2_Data *w2, unsigned int entry);

War2_Tileset_Descriptor *war2_tileset_decode(War2_Data *w2, Pud_Era era, War2_Tileset_Decode_Func func);
void war2_tileset_free(War2_Tileset_Descriptor *ts);

War2_Units_Descriptor *
war2_units_decode(War2_Data              *w2,
                  Pud_Player              player_color,
                  Pud_Side                race,
                  War2_Units_Decode_Func  func);

#ifdef __cplusplus
%>
#endif
#endif /* ! _WAR2_H_ */

