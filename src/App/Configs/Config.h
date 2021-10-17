#ifndef __CONFIG_H
#define __CONFIG_H

/*=========================
   Application configuration
 *=========================*/

#define CONFIG_SYSTEM_SAVE_FILE_PATH          "S:/SystemSave.json"
#define CONFIG_SYSTEM_LANGUAGE_DEFAULT        {'e','n','-','G','B'}
#define CONFIG_SYSTEM_GMT_OFFSET_DEFAULT      8 // GMT+ 8

#define CONFIG_WEIGHT_DEFAULT                 65 // kg

#define CONFIG_GPS_REFR_PERIOD                1000 // ms
#define CONFIG_GPS_LNG_DEFAULT                116.391332
#define CONFIG_GPS_LAT_DEFAULT                39.907415

#define CONFIG_TRACK_FILTER_OFFSET_THRESHOLD  2 // pixel
#define CONFIG_TRACK_RECORD_FILE_DIR_NAME     "Track"

#define CONFIG_MAP_USE_WGS84_DEFAULT          false

#define CONFIG_MAP_DIR_PATH                   {'/','M','A','P'}//"/MAP"

#define CONFIG_ARROW_THEME_DEFAULT            "default"

#define CONFIG_LIVE_MAP_LEVEL_DEFAULT         16
#define CONFIG_LIVE_MAP_VIEW_WIDTH            LV_HOR_RES
#define CONFIG_LIVE_MAP_VIEW_HEIGHT           LV_VER_RES

/* Simulator */
#define CONFIG_TRACK_VIRTUAL_GPX_FILE_PATH    "S:/TRK_20210801_203324.gpx"

/*=========================
   Hardware Configuration
 *=========================*/

#define NULL_PIN                    PD0

/* Screen */
// #define TFT_MISO 19
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS    -1 // Not connected
#define TFT_DC    2
#define TFT_RST   4  // Connect reset to ensure display initialises
#define CONFIG_SCREEN_BLK_PIN       15

#define CONFIG_SCREEN_HOR_RES       240
#define CONFIG_SCREEN_VER_RES       240
#define CONFIG_SCREEN_BUFFER_SIZE   (CONFIG_SCREEN_HOR_RES * CONFIG_SCREEN_VER_RES /2)

/* Battery */
#define CONFIG_BAT_DET_PIN          37
#define CONFIG_BAT_CHG_DET_PIN      38

/* Buzzer */
#define CONFIG_BUZZ_PIN             27
#define CONFIG_BUZZ_CHANNEL         2
#define CONFIG_SOUND_ENABLE_DEFAULT false

/* IMU */
#define CONFIG_IMU_INT1_PIN         32
#define CONFIG_IMU_INT2_PIN         33

/* I2C */
#define CONFIG_MCU_SDA_PIN          -1
#define CONFIG_MCU_SCL_PIN          -1

/* Encoder */
#define CONFIG_ENCODER_B_PIN        33 //34  Prev 
#define CONFIG_ENCODER_A_PIN        25 //35  Next
#define CONFIG_ENCODER_PUSH_PIN     12 // 27

/* Power */
#define CONFIG_POWER_EN_PIN         21

/* Debug USART */
#define CONFIG_DEBUG_SERIAL         Serial

/* SD CARD */
#define CONFIG_SD_SPI               SPI_SD
#define CONFIG_SD_CD_PIN            -1
#define CONFIG_SD_MOSI_PIN          -1
#define CONFIG_SD_MISO_PIN          -1 // PB14
#define CONFIG_SD_SCK_PIN           -1 // PB13
#define CONFIG_SD_CS_PIN            -1
#define CONFIG_SD_DET_PIN           22

/* Stack Info */
#define CONFIG_USE_STACK_INFO       0

#endif
