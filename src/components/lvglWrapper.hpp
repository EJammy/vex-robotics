#include "../basics/basics.hpp"
/**
 * Mixing two colors is possible with mixed_color = lv_color_mix(color1, color2, ratio). 
 * Ration can be 0..255. 0 results fully color2, 255 result fully color1.
 */
/* brain screen area available for user code is probably 480 x 240 pixels */
const int screenX = 480;
const int screenY = 240;

class lvObj
{
	protected:
		lv_obj_t *obj;
		lv_style_t style;
	public:
		lvObj(int x, int y, lv_obj_t * parent, lv_obj_t * (*create)(lv_obj_t *, const lv_obj_t *))
		{
			lv_style_copy(&style, &lv_style_plain_color);
			// style.text.font = &arial_40;

			obj = create(parent, NULL);
			lv_obj_set_style(obj, &style);
			lv_obj_set_pos(obj, x, y);
		}
		void hide(){
			lv_obj_set_hidden(obj, true);
		}
		~lvObj(){
			delete obj;
		}
};

class lvButton : lvObj{
	private:
		lv_style_t style_pr;
		lv_style_t style_rel;
	public:
		/**
		 * contructor:
		 * enter x position, y position, width, hieght, label
		 */
		lvButton(int x, int y, int w, int h, int id, lv_color_t color, lv_obj_t *parent, std::string txt = "") :
			lvObj(x, y, parent, lv_btn_create)
		{
			lv_obj_set_size(obj, w, h);
			lv_obj_set_free_num(obj, id);
			lv_obj_t * label = lv_label_create(obj, NULL);
			lv_label_set_text(label, txt.c_str());
			lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);

			lv_style_copy(&style_rel, &lv_style_plain);
			style_rel.body.main_color = color;
			style_rel.body.grad_color = color;
			lv_btn_set_style(obj, LV_BTN_STYLE_REL, &style_rel);
			lv_style_copy(&style_pr, &style_rel);
			color = lv_color_mix(color, LV_COLOR_BLACK, 100);
			style_pr.body.main_color = color;
			style_pr.body.grad_color = color;
			lv_btn_set_style(obj, LV_BTN_STYLE_PR, &style_pr);
		}
		void setEvent(lv_action_t callback){
			lv_btn_set_action(obj, LV_BTN_ACTION_CLICK, callback);
		}
		void hide(){
			lv_obj_set_hidden(obj, true);
		}
};


class lvText : lvObj
{
	private:
		lv_style_t style;
	public:
		/**
		 * contructor:
		 * enter x position, y position, width, hieght, label
		 */
		lvText(int x, int y, lv_obj_t *parent, std::string txt = "Button") : lvObj(x, y, parent, lv_label_create) {
			lv_style_copy(&style, &lv_style_plain_color);
			// style.text.font = &arial_40;

			lv_label_set_style(obj, &style);
			lv_label_set_text(obj, txt.c_str());
			lv_obj_set_pos(obj, x, y);
		}
		void setText(std::string txt){
			lv_label_set_text(obj, txt.c_str());
		}
};