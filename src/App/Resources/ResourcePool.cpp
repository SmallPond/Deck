#include "ResourcePool.h"

/* Global resource manager */
ResourcePool Resource;

extern "C" {
#define IMPORT_FONT(name) \
do{\
    LV_FONT_DECLARE(font_##name)\
    Resource.Font_.AddResource(#name, (void*)&font_##name);\
}while(0)

#define IMPORT_IMG(name) \
do{\
    LV_IMG_DECLARE(img_src_##name)\
    Resource.Image_.AddResource(#name, (void*)&img_src_##name);\
}while (0)

    static void Resource_Init()
    {
        /* Import Fonts */
        IMPORT_FONT(bahnschrift_13);
        IMPORT_FONT(bahnschrift_17);
        IMPORT_FONT(bahnschrift_32);
        IMPORT_FONT(bahnschrift_65);
        IMPORT_FONT(agencyb_36);

        /* Import Images */
        IMPORT_IMG(alarm);
        IMPORT_IMG(battery);
        IMPORT_IMG(battery_info);
        IMPORT_IMG(bicycle);
        IMPORT_IMG(compass);
        IMPORT_IMG(gps_arrow_default);
        IMPORT_IMG(gps_arrow_dark);
        IMPORT_IMG(gps_arrow_light);
        IMPORT_IMG(gps_pin);
        IMPORT_IMG(gyroscope);
        IMPORT_IMG(locate);
        IMPORT_IMG(map_location);
        IMPORT_IMG(menu);
        IMPORT_IMG(origin_point);
        IMPORT_IMG(pause);
        IMPORT_IMG(satellite);
        IMPORT_IMG(sd_card);
        IMPORT_IMG(start);
        IMPORT_IMG(stop);
        IMPORT_IMG(storage);
        IMPORT_IMG(system_info);
        IMPORT_IMG(time_info);
        IMPORT_IMG(trip);

        // IMPORT_IMG(arm);
        IMPORT_IMG(bluetooth);
        IMPORT_IMG(pose6d);
        IMPORT_IMG(joints);
        IMPORT_IMG(xman);
    }

} /* extern "C" */

void ResourcePool::Init()
{
    lv_obj_remove_style_all(lv_scr_act());
    lv_disp_set_bg_color(lv_disp_get_default(), lv_color_black());

    Font_.SetDefault((void*)&lv_font_montserrat_14);

    Resource_Init();
}
