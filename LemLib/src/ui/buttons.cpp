#include "ui/buttons.hpp"
#include "liblvgl/core/lv_obj.h"
#include "liblvgl/core/lv_obj_style.h"
#include "ui/ui.hpp"






lv_obj_t *alliance_button_red;
lv_obj_t *alliance_button_blue;

lv_obj_t *side_button_positive;
lv_obj_t *side_button_negative;

lv_style_t button_red;
lv_style_t button_blue;
lv_style_t button_green;



void select_red(lv_event_t * e) {
  lv_obj_set_style_bg_color(alliance_button_red, lv_color_hex(0xba1111), 0);
  lv_obj_set_style_bg_color(alliance_button_blue, lv_color_hex(0x28344d), 0);
};
void select_blue(lv_event_t * e) {
  lv_obj_set_style_bg_color(alliance_button_red, lv_color_hex(0x4d2828), 0);
  lv_obj_set_style_bg_color(alliance_button_blue, lv_color_hex(0x1009e0), 0);
};
void select_positive(lv_event_t * e) {
  lv_obj_set_style_bg_color(side_button_negative, lv_color_hex(0x4d2828), 0);
  lv_obj_set_style_bg_color(side_button_positive, lv_color_hex(0x2eed0c), 0);
}
void select_negative(lv_event_t * e) {
  lv_obj_set_style_bg_color(side_button_negative, lv_color_hex(0xba1111), 0);
  lv_obj_set_style_bg_color(side_button_positive, lv_color_hex(0x2b5224), 0);
}



void button_styles() {
  lv_style_init(&button_red);
  lv_style_set_border_width(&button_red, 2);
  lv_style_set_radius(&button_red, 3);
  lv_style_set_border_color(&button_red, lv_color_hex(0xff0000));
  lv_style_set_text_color(&button_red, lv_color_hex(0xff0000));
  lv_style_set_bg_color(&button_red, lv_color_hex(0x5a5a5a));

  lv_style_init(&button_blue);
  lv_style_set_border_width(&button_blue, 2);
  lv_style_set_radius(&button_blue, 3);
  lv_style_set_border_color(&button_blue, lv_color_hex(0x1009e0));
  lv_style_set_text_color(&button_blue, lv_color_hex(0x1009e0));
  lv_style_set_bg_color(&button_blue, lv_color_hex(0x28344d));


  lv_style_init(&button_green);
  lv_style_set_border_width(&button_green, 2);
  lv_style_set_radius(&button_green, 3);
  lv_style_set_border_color(&button_green, lv_color_hex(0x29e009));
  lv_style_set_text_color(&button_green, lv_color_hex(0x1009e0));
  lv_style_set_bg_color(&button_green, lv_color_hex(0x5a5a5a));

}





void init_buttons() {
  alliance_button_red = lv_obj_create(mainscreen);
  alliance_button_blue = lv_obj_create(mainscreen);

  side_button_negative = lv_obj_create(mainscreen);
  side_button_positive = lv_obj_create(mainscreen);

  button_styles();

  lv_obj_set_height(alliance_button_red, 40);
  lv_obj_set_width(alliance_button_red, 240);
  lv_obj_add_style(alliance_button_red, &button_red, LV_PART_MAIN);
  lv_obj_set_pos(alliance_button_red, 5, 5);

  lv_obj_set_height(alliance_button_blue, 40);
  lv_obj_set_width(alliance_button_blue, 240);
  lv_obj_add_style(alliance_button_blue, &button_blue, LV_PART_MAIN);
  lv_obj_set_pos(alliance_button_blue, 255, 5);


  // side buttons
  lv_obj_set_height(side_button_positive, 40);
  lv_obj_set_width(side_button_positive, 240);
  lv_obj_add_style(side_button_positive, &button_green, LV_PART_MAIN);
  lv_obj_set_pos(side_button_positive, 5, 55);

  lv_obj_set_height(side_button_negative, 40);
  lv_obj_set_width(side_button_negative, 240);
  lv_obj_add_style(side_button_negative, &button_red, LV_PART_MAIN);
  lv_obj_set_pos(side_button_negative, 255, 55);



  lv_obj_add_event_cb(alliance_button_red, select_red, LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(alliance_button_blue, select_blue, LV_EVENT_CLICKED, NULL);


  lv_obj_add_event_cb(side_button_negative, select_negative, LV_EVENT_CLICKED, NULL);
  lv_obj_add_event_cb(side_button_positive, select_positive, LV_EVENT_CLICKED, NULL);


};

