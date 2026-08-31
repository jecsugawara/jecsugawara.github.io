//
// UltrasonicSensor.h
//
// Copyright (c) 2025 Embedded Technology Software Design Robot Contest
//

#ifndef SPIKE_CPP_API_ULTRASONIC_SENSOR_H_ 
#define SPIKE_CPP_API_ULTRASONIC_SENSOR_H_

#include <cstdint>
extern "C" {
#include <spike/pup/ultrasonicsensor.h>
}

#include <libcpp/spike/Port.h>

namespace spikeapi {
/**
 * @brief SPIKE 超音波センサークラス
 * @details 50mmから2000mmの距離を測定可能。誤差±20mm（実測では50-1800mmまでで±20mmの誤差、1850mm以上は測定不能)<br>
 * 対象物との入射角は±35度(実測は±20度程度でそれ以上は誤差が大きくなる)<br>
 * 音速を340m/sとすると、500mm先の対象物を測定するには音は往復1000mm進む。この時間は1000/340/1000=0.0294秒(2.94ミリ秒)
 * 2000mm先の対象物だと11.76ミリ秒かかる。
 * getDistance()はブロッキングしない。呼び出すと即座に値を返すが、この値はカーネルが保持している最新のキャッシュ値である。
 * センサーのサンプリングレートは100Hzであるから10ミリ秒に１回測定している。しかし、実際にはセンサーとハブ間の通信時間(10ms)、
 * RTOSのI/O更新周期(センサーとのシリアル通信)10ms～20msが掛かるため、合計30ms～40msのサンプリング遅延が発生する。
 * つまり、APIで取得した距離は30msから40msまえの値で、最短10msごとに更新される。
 */
class UltrasonicSensor
{
public:

  /**
   * @brief コンストラクタ 
   * @param port PUPポートID 
   */ 
  UltrasonicSensor(EPort port) { 
    mDevice = pup_ultrasonic_sensor_get_device(static_cast<pbio_port_id_t>(port));
  }
    
  /** 
   * @brief 超音波センサーで距離を測定する 
   * @details このAPIはブロッキングされない。実行すると即座にカーネルが保持する最新の値を返す。これは30ms～40ms前の値である。
   * センサーのサンプリングレートは100Hzなので10msごとに距離の値が更新される。
   * @return 距離（単位：mm） 
   */ 
  int32_t getDistance() const { 
    return pup_ultrasonic_sensor_distance(mDevice); 
  } 
    
  /** 
   * @brief 超音波信号を検出する 
   * @return true 超音波を検出した 
   * @return false 超音波を検出しなかった 
   */ 
  bool isPresence() const { 
    return pup_ultrasonic_sensor_presence(mDevice); 
  } 
    
  /** 
   * @brief 超音波センサーのライトの輝度を設定する 
   * @param bv1 輝度1 
   * @param bv2 輝度2 
   * @param bv3 輝度3 
   * @param bv4 輝度4 
   * @return - 
   */ 
  void setLight(int32_t bv1, int32_t bv2, int32_t bv3, int32_t bv4) const { 
    pup_ultrasonic_sensor_light_set(mDevice, bv1, bv2, bv3, bv4); 
  } 
    
  /** 
   * @brief 超音波センサーのライトを点灯する 
   * @return - 
   */ 
  void lightOn() const { 
    pup_ultrasonic_sensor_light_on(mDevice); 
  } 
    
  /** 
   * @brief 超音波センサーのライトを消灯する 
   * @return - 
   */ 
  void lightOff() const { 
    pup_ultrasonic_sensor_light_off(mDevice); 
  }

  /**
   * @brief インスタンス生成が正常にできたかどうかを確認するための共通メソッド
   * @details mDeviceがNULLの場合にtrueとなる
   */
  bool hasError() { return mDevice == 0; }
  
  
private: 
  pup_device_t *mDevice;
}; // class UltrasonicSensor
}  // namespace spikeapi

#endif // !SPIKE_CPP_API_ULTRASONIC_SENSOR_H_
