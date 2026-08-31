//
// IMU.h
//
// Copyright (c) 2025 Embedded Technology Software Design Robot Contest
//

#ifndef SPIKE_CPP_API_IMU_H_
#define SPIKE_CPP_API_IMU_H_

extern "C" {
#include <spike/hub/imu.h>
}

namespace spikeapi {
/**
 * @brief SPIKE ハブ内蔵IMUクラス
 * @details このクラスはSPIKEハブの内蔵IMUセンサーを操作するためのインターフェースを提供します。IMU(Inertial Measurement Unit)
 * クラスとは慣性計測ユニットのことでジャイロセンサーや加速度センサーのことです。また、角度は右ねじの方向が正です。
 * サンプリングレートは833Hz(1.2ms周期)。レイテンシは1mscから数ms程度。
 *
 * @image html SPIKE-hub-xyz.jpg "SPIKEハブのジャイロセンサーの座標系" width=600px
 * <br>
 * @image html SPIKE-hub-accel.jpg "SPIKEハブの加速度センサーの座標系" width=600px
 */
class IMU
{
public:

  /** @brief 加速度 mm/s^2 */
  struct Acceleration {
    float x;
    float y;
    float z;
  };

  /** @brief 角速度 degree/s */
  struct AngularVelocity {
    float x;
    float y;
    float z;
  };
    

  /**
   * @brief コンストラクタ 
   *
   * IMUモジュールの初期化を行う. 内部で実行される hub_imu_init() は2回目以降エラーとなるが、値を取る上では問題ないためそのままとする
   */
  IMU(void) {
    // このinitは2回目以降エラーとなるが、値を取る上では問題ないためそのままとする
    hub_imu_init();
  }
    
  /** 
   * @brief IMUから加速度を取得する
   *
   * @param accel [out] x/y/z軸の加速度を格納するためのAcceleration構造体[mm/s^2] 
   */ 
  void getAcceleration(Acceleration &accel);
    
  /** 
   * @brief IMUから角速度を取得する
   * @details 角速度は1秒あたりに変化する角度です。IMUのサンプリングレートは833Hzです(1秒間に833回計測する)。角速度は右ねじの方向が正であることに注意すること
   * @param ang [out] x/y/z軸の角速度を格納するためのAngularVelocity構造体[°/s] 
   */ 
  void getAngularVelocity(AngularVelocity &ang);
    
  /** 
   * @brief IMUから温度を取得する
   * @return 温度[℃] 
   */
  float getTemperature() const { 
    return hub_imu_get_temperature(); 
  }

  /**
   * @brief IMUjモジュールが使用可能かチェックする
   * @return true: 準備が整っている, false: まだ準備が整っていない
   */
  bool isReady() const {
    return hub_imu_is_ready();
  }

  /**
   * @brief IMUモジュールが静止状態かチェックする
   * @return true: 静止している, false: 動いている
   */
  bool isStationary() const {
    return hub_imu_is_stationary();
  }

  /**
   * @brief IMUモジュールの傾斜角度をセットする
   * @details 傾斜角度は、IMUのY軸を基準にした回転角度です。右ねじの方向が正です。
   * @param angle [in] モジュールの（Y軸に対する）傾斜角度（度）
   */
  void setTilt(float angle) {
    hub_imu_set_tilt(angle);
  }

  /**
   * @brief IMUの方位角を取得する
   * @details 方位角は、IMUのZ軸を基準にした回転角度です。右ねじの方向が正です。
   * @return 方位角 [°]
   */
  float getHeading() const {
    return hub_imu_get_heading();
  }

  /**
   * @brief IMUの方位角をリセットする
   * @details 方位角を0°にリセットする
   * @return -
   */
  void resetHeading() {
    hub_imu_reset_heading();
  }

  /**
   * @brief インスタンス生成が正常にできたかどうかを確認するための共通メソッド
   * @details IMUでは複数生成が問題ないので、常にfalseを返す
   * @return false
   */
  bool hasError() { return false; }
  
  
}; // class IMU
}  // namespace spikeapi

#endif // !SPIKE_CPP_API_IMU_H_
