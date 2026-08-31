//
// ColorSensor.h
//
// Copyright (c) 2025 Embedded Technology Software Design Robot Contest
//

#ifndef SPIKE_CPP_API_COLOR_SENSOR_H_ 
#define SPIKE_CPP_API_COLOR_SENSOR_H_

#include <cstdint>
extern "C" {
#include <spike/pup/colorsensor.h>
}

#include <libcpp/spike/Port.h>

namespace spikeapi {
/**
 * @brief SPIKE カラーセンサークラス
 * @details サンプリングレートは100Hz。最適な読み取り距離は16mm(10mm～300mm)<br>
 * getDistance()はブロッキングしない。呼び出すと即座に値を返すが、この値はカーネルが保持している最新のキャッシュ値である。
 * センサーのサンプリングレートは100Hzであるから10ミリ秒に１回測定している。しかし、実際にはセンサー内での計算時間(10ms)、
 * RTOSのI/O更新周期(センサーとのシリアル通信)10msが掛かるため、合計20msサンプリング遅延(レイテンシ)が発生する。
 * つまり、APIで取得した距離は20ms前の値で、最短10msごとに更新される。
 */
class ColorSensor
{
public:
  /**
   * @brief RGB構造体
   * @details Red(赤)、Green(緑)、Blue(青) の各色の強さを保持する
   */
  struct RGB {
    uint16_t r;
    uint16_t g;
    uint16_t b;
  };

  /**
   * @brief HSV構造体
   * @details Hue(色相)、Saturation(彩度)、Value(明度)を保持する
   、色を「色相（Hue）」「彩度（Saturation）」「明度（Value / Brightness）」の3つの要素で表現するカラーモデルです。
   */
  struct HSV {
    uint16_t h;
    uint8_t  s;
    uint8_t  v;
  };
  
  /** 
   * @brief コンストラクタ 
   * @param port PUPポートID 
   */ 
  ColorSensor(EPort port) { 
    mDevice = pup_color_sensor_get_device(static_cast<pbio_port_id_t>(port));
  }
  
  /** 
   * @brief カラーセンサーのRGB値を取得する 
   * @details このAPIはブロッキングしない。サンプリングレートは100Hz。レイテンシは20ms。
   * @param  値を設定するRGB構造体、各色8ビット
   * @return -
   */ 
  void getRGB(RGB& rgb) const { 
    pup_color_rgb_t pup_rgb = pup_color_sensor_rgb(mDevice);
    rgb.r = pup_rgb.r;
    rgb.g = pup_rgb.g;
    rgb.b = pup_rgb.b;    
  } 
    
  /** 
   * @brief カラーセンサーで色を測定する 
   * @details このAPIはブロッキングしない。サンプリングレートは100Hz。レイテンシは20ms。
   * @param surface trueならば表面の色から、falseならば他の光源の色を検出する 
   * @return 色（hsvによる表現） 
   */ 
  void getColor(HSV& hsv, bool surface = true) const { 
    pup_color_hsv_t pup_hsv = pup_color_sensor_color(mDevice, surface);
    hsv.h = pup_hsv.h;
    hsv.s = pup_hsv.s;
    hsv.v = pup_hsv.v;
  } 
    
  /** 
   * @brief カラーセンサーで色を測定する（近似なし） 
   * @details このAPIはブロッキングしない。サンプリングレートは100Hz。レイテンシは20ms。
   * @param surface trueならば表面の色から、falseならば他の光源の色を検出する 
   * @return 色（hsvによる表現） 
   */ 
  void getHSV(HSV& hsv, bool surface = true ) const { 
    pup_color_hsv_t pup_hsv = pup_color_sensor_hsv(mDevice, surface);
    hsv.h = pup_hsv.h;
    hsv.s = pup_hsv.s;
    hsv.v = pup_hsv.v;
  } 
    
  /** 
   * @brief センサーの発する光を表面がどの程度反射するかを測定する 
   * @details このAPIはブロッキングしない。サンプリングレートは100Hz。レイテンシは20ms。
   * @return どの程度反射しているか（％） 
   */ 
  int32_t getReflection() const { 
    return pup_color_sensor_reflection(mDevice); 
  } 
    
  /** 
   * @brief 周囲の光の強度を測定する 
   * @details このAPIはブロッキングしない。サンプリングレートは100Hz。レイテンシは20ms。
   * @return 周囲の光の強度（％） 
   */ 
  int32_t getAmbient() const { 
    return pup_color_sensor_ambient(mDevice); 
  } 
    
  /** 
   * @brief カラーセンサーのライトを設定する 
   * @param bv1 輝度1 
   * @param bv2 輝度2 
   * @param bv3 輝度3 
   * @return - 
   */ 
  void setLight(int32_t bv1, int32_t bv2, int32_t bv3) const { 
    pup_color_sensor_light_set(mDevice, bv1, bv2, bv3); 
  } 
    
  /** 
   * @brief カラーセンサーのライトを点灯する 
   * @param -
   * @return - 
   */ 
  void lightOn() const { 
    pup_color_sensor_light_on(mDevice); 
  } 
    
  /** 
   * @brief カラーセンサーのライトを消灯する 
   * @param -
   * @return - 
   */ 
  void lightOff() const { 
    pup_color_sensor_light_off(mDevice); 
  } 
    
  /** 
   * @brief カラーセンサーが検知する色を設定する 
   * @param size カラーの配列のサイズ 
   * @param colors カラーの配列 
   * @return - 
   */ 
  void setDetectableColors(int32_t size, pup_color_hsv_t *colors) const { 
    pup_color_sensor_detectable_colors(size, colors);
  }

  /**
   * @brief インスタンス生成が正常にできたかどうかを確認するための共通メソッド
   * @details mDeviceがNULLの場合にtrueとなる
   */
  bool hasError() { return mDevice == 0; }

  
private: 
  pup_device_t *mDevice;
}; // class ColorSensor
}  // namespace spikeapi

#endif // !SPIKE_CPP_API_COLOR_SENSOR_H_
