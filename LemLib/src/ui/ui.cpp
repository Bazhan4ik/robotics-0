#include "liblvgl/core/lv_disp.h"
#include "liblvgl/core/lv_obj.h"
#include "liblvgl/extra/widgets/tileview/lv_tileview.h"
#include "ui/ui.hpp"
#include "ui/buttons.hpp"





lv_obj_t *mainscreen = lv_tileview_create(NULL);
lv_style_t style;


void ui_init() {
  lv_style_init(&style);
  lv_style_set_border_width(&style, 0);
  lv_style_set_radius(&style, 0);
  lv_style_set_text_color(&style, lv_color_hex(0xcfffe9));
  lv_style_set_bg_color(&style, lv_color_hex(0x000000));

  lv_scr_load(mainscreen);
  lv_obj_add_style(mainscreen, &style, LV_PART_MAIN);
  lv_obj_set_scrollbar_mode(mainscreen, LV_SCROLLBAR_MODE_OFF);

  init_buttons();
}