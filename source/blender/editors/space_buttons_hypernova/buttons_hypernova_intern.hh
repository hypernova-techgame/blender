/* SPDX-FileCopyrightText: 2008 Blender Authors
 *
 * SPDX-License-Identifier: GPL-2.0-or-later */

/** \file
 * \ingroup spbuttons_hypernova
 */

#pragma once

#include "BLI_bitmap.h"
#include "DNA_listBase.h"
#include "RNA_types.hh"

struct ARegionType;
struct ID; 
struct SpaceHypernova;
struct Tex;
struct bContext;
struct bContextDataResult;
struct bNode;
struct bNodeSocket;
struct bNodeTree;
struct wmOperatorType;

struct SpaceHypernova_Runtime {
  /** For filtering properties displayed in the space. */
  char search_string[UI_MAX_NAME_STR];
  /**
* 
   * Bit-field (in the same order as the tabs) for whether each tab has properties
   * that match the search filter. Only valid when #search_string is set.
   */
  BLI_bitmap *tab_search_results;
};

/* context data */

struct ButsContextPath {
  PointerRNA ptr[8];
  int len;
  int flag;
  int collection_ctx;
};

struct ButsTextureUser {
  ButsTextureUser *next, *prev;

  ID *id;

  PointerRNA ptr;
  PropertyRNA *prop;

  bNodeTree *ntree;
  bNode *node;
  bNodeSocket *socket;

  const char *category;
  int icon;
  const char *name;

  int index;
};

struct ButsContextTexture {
  ListBase users;

  struct Tex *texture;

  struct ButsTextureUser *user;
  int index;
};

/* internal exports only */

/* `buttons_hypernova_context.cc` */

void buttons_hypernova_context_compute(const bContext *C, SpaceHypernova *sbuts);
int buttons_hypernova_context(const bContext *C, const char *member, bContextDataResult *result);
void buttons_hypernova_context_register(ARegionType *art);
ID *buttons_hypernova_context_id_path(const bContext *C);

extern "C" const char *buttons_hypernova_context_dir[]; /* doc access */

/* `buttons_hypernova_texture.cc` */

void buttons_hypernova_texture_context_compute(const bContext *C, SpaceHypernova *sbuts);

/* `buttons_hypernova_ops.cc` */  

void BUTTONS_HYPERNOVA_OT_start_filter(wmOperatorType *ot);
void BUTTONS_HYPERNOVA_OT_clear_filter(wmOperatorType *ot);
void BUTTONS_HYPERNOVA_OT_toggle_pin(wmOperatorType *ot);
void BUTTONS_HYPERNOVA_OT_file_browse(wmOperatorType *ot);
/**
 * Second operator, only difference from #BUTTONS_HYPERNOVA_OT_file_browse is #WM_FILESEL_DIRECTORY.
 */
void BUTTONS_HYPERNOVA_OT_directory_browse(wmOperatorType *ot);
void BUTTONS_HYPERNOVA_OT_context_menu(wmOperatorType *ot);
