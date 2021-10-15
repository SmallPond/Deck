# 简介
![](https://www.dingmos.com/usr/uploads/2021/10/3628734278.png)

基于 [稚晖君的Peak](https://github.com/peng-zhihui/Peak)，其使用了 FASTSHIFT 的码表 [X-TRACK](https://github.com/FASTSHIFT/X-TRACK)的丝滑 UI （IOS ViewController）并移植到了 ESP32 （修改部分库实现了 60 fps 纵享丝滑）上。

故忍不住自己来跑一跑学习一下 LVGL（久闻盛名），并且之后将基于此构建自己的小玩具。

修改：
- 更新了启动界面和显示图片


# 硬件

- esp32doit-devkit-v1 开发板
- 中景园1.3寸 IPS 屏（240*240）
- 硬件连线：
|ESP32|屏幕|
|:-:|:-:|
|GPIO_23(MOSI)|SDA|
|GPIO_18(SCLK)|SCL|
|GPIO_2(DC)|DC|
|GPIO_4(RST)|RES|
|GPIO_12(BLK)|BLK|

以下仅为个人的学习记录。
# LVGL
## 图片

基于已有框架增添自己的图片：

- 图片生成C代码网站：[Online Image Converter BMP, JPG or PNG to C array or binary](https://lvgl.io/tools/imageconverter),选择 True color with alpha
- 将生成的C文件保存到`src\App\Resources\Image\`目录下
- 在 `src\App\Resources\ResourcePool.cpp` 增加一行声明

## 动画

动画的[官方文档](https://docs.lvgl.io/master/overview/animation.html?highlight=lv_anim#create-an-animation)解释了基本用法。
动画的实现主要需要指定 4 个参数，其他可选参数可看文档：
- 执行对象：lv_anim_set_var(&a, obj);
- 动画执行持续的时间: lv_anim_set_time(&a, duration);
- 动画执行的方式：lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_obj_set_x); 设置回调函数
- 动画执行的起点和终点：lv_anim_set_values(&a, start, end);


X-TRACE 的 UI 库对其进行了封装，下面简单分析一下。

UI库定义了一个类 lv_anim_timeline_wrapper_t 用来保存一个动画涉及到的基本参数，并且定义了一个宏`ANIM_DEF(start_time, obj, attr, start, end)`来实例化这个类。因此可以采用以下的代码方便地定义多个动画。

```
#define ANIM_DEF(start_time, obj, attr, start, end) \
     {start_time, obj, LV_ANIM_EXEC(attr), start, end, 500, lv_anim_path_ease_out, true}

    lv_anim_timeline_wrapper_t wrapper[] =
        {
            ANIM_DEF(0, ui.cont, width, 0, lv_obj_get_style_width(ui.cont, 0)),
            //ANIM_DEF(500, ui.labelLogo, y, lv_obj_get_style_height(ui.cont, 0), lv_obj_get_y(ui.labelLogo)), // 从下往上
           ANIM_DEF(500, ui.labelLogo, x, lv_obj_get_x(ui.labelLogo)+80, lv_obj_get_x(ui.labelLogo)),, //从右往左
            
            LV_ANIM_TIMELINE_WRAPPER_END
        };

    lv_anim_timeline_add_wrapper(ui.anim_timeline, wrapper);
```