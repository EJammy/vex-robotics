#include "../basics/basics.hpp"
/**
 * Mixing two colors is possible with mixed_color = lv_color_mix(color1, color2, ratio). 
 * Ration can be 0..255. 0 results fully color2, 255 result fully color1.
 */
/* brain screen area available for user code is probably 480 x 240 pixels */


class lvButton{
	private:
		lv_obj_t *btn;
		lv_style_t style_pr;
		lv_style_t style_rel;
	public:
		/**
		 * contructor:
		 * enter x position, y position, width, hieght, label
		 */
		lvButton(int x, int y, int w, int h, int id, lv_color_t color, lv_obj_t *parent, std::string txt = "Button"){
			btn = lv_btn_create(parent, NULL);
			lv_obj_set_pos(btn, x, y);
			lv_obj_set_size(btn, w, h);
			lv_obj_set_free_num(btn, id);
			lv_obj_t * label = lv_label_create(btn, NULL);
			lv_label_set_text(label, txt.c_str());
			lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);


			lv_style_copy(&style_rel, &lv_style_plain);
			style_rel.body.main_color = color;
			style_rel.body.grad_color = color;
			lv_btn_set_style(btn, LV_BTN_STYLE_REL, &style_rel);
			lv_style_copy(&style_pr, &style_rel);
			color = lv_color_mix(color, LV_COLOR_BLACK, 100);
			style_pr.body.main_color = color;
			style_pr.body.grad_color = color;
			lv_btn_set_style(btn, LV_BTN_STYLE_PR, &style_pr);
		}
		void setEvent(lv_action_t callback){
			lv_btn_set_action(btn, LV_BTN_ACTION_CLICK, callback);
		}
		void hide(){
			lv_obj_set_hidden(btn, true);
		}
		~lvButton(){
			delete btn;
		}
};

class lvText{
	private:
		lv_obj_t *label;
		lv_style_t style;
	public:
		/**
		 * contructor:
		 * enter x position, y position, width, hieght, label
		 */
		lvText(int x, int y, lv_obj_t *parent, std::string txt = "Button"){
			lv_style_copy(&style, &lv_style_plain_color);
			// style.text.font = &arial_40;

			label = lv_label_create(parent, NULL);
			lv_label_set_style(label, &style);
			lv_label_set_text(label, txt.c_str());
			lv_obj_set_pos(label, x, y);
		}
		void setText(std::string txt){
			lv_label_set_text(label, txt.c_str());
		}
		void hide(){
			lv_obj_set_hidden(label, true);
		}
};

class lvPage{
	private:
		lv_obj_t *page;
	public:
		/**
		 * contructor
		 */
		lvPage(lv_obj_t *parent, lv_color_t color, std::string title = "TITLE"){
			page = lv_obj_create(parent, NULL);
			lv_obj_set_size(page, 480, 240);

			static lv_style_t style;
			lv_style_copy(&style, &lv_style_plain);
			style.body.grad_color = color;
			style.body.main_color = color;
			lv_obj_set_style(page, &style);	
			// lv_label_set_text(page, txt.c_str());
		}
		void hide(){
			lv_obj_set_hidden(page, true);
		}
		void show(){
			lv_obj_set_hidden(page, false);
		}
		lv_obj_t* operator()(){
			return page;
		}
};
