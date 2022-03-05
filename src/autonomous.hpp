#include "autonomous/autonZigZag.hpp"
#include "autonomous/autonTest.hpp"
#include "autonomous/skill2.hpp"
#include "autonomous/autonR.hpp"
#include "autonomous/autonPlat.hpp"

int autonSelection = -1;
lv_res_t autonChooseFunc(lv_obj_t *btn) {
    uint8_t id = lv_obj_get_free_num(btn);
    autonSelection = id;
    return LV_RES_OK;
}
lvButton selectR(240, 0, 240, 200, 0, LV_COLOR_ORANGE, lv_scr_act(), "R");
lvButton selectL(0, 0, 240, 200, 1, LV_COLOR_ORANGE, lv_scr_act(), "L");
lvButton selectWP(0, 400, 480, 80, 2, LV_COLOR_AQUA, lv_scr_act(), "WP");

void competition_initialize() {
    // 480 * 240
    selectL.setEvent(autonChooseFunc);
    selectR.setEvent(autonChooseFunc);
    selectWP.setEvent(autonChooseFunc);
    // while(autonSelection == -1) {
    //     delay (100);
    //     cout<< autonSelection << endl;
    // }
    while (!control.Y()) { delay(100); }
    // cout<< autonSelection << endl;
}

void autonomous() {
    selectL.hide();
    selectR.hide();
    selectWP.hide();
    /* (0,0) is bottom left corner
    * Robot pivot at center
    */
    runAutonSkill();
    // delay(1000);
    // return;

    // mxV1 = 165;
    // runZigZag();
    // mxV1 = 140;
    // mxV2 = 100;
    // autonPlat();
    // runAutonR();

    // autonTest();

    return;

    // if (autonSelection == 0){
    //     runAutonR();
    // }else if (autonSelection == 1) {
    //     runAutonL();
    // }else if (autonSelection == 2) {
    //     runAutonWP();
    // }else { // -1 
    //     runAutonR();
    //     // runAutonWP();
    //     // roller.moveVelocity(rollerVelocity);
    //     // delay(5000);
    //     // chassis->setState({0_in, 0_in});
    //     // moveTo(10, 0, 0);
    // }
    delay(1000);

}
