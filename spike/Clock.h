//
// Clock.h
//
// Copyright (c) 2025 Embedded Technology Software Design Robot Contest
//

#ifndef SPIKE_CPP_API_CLOCK_H_
#define SPIKE_CPP_API_CLOCK_H_

//#include <cstdint>

extern "C" {
#include <kernel.h>
}

namespace spikeapi {
/**
 * @brief SPIKE クロッククラス
 */
class Clock
{
public:
  /**
   * @brief コンストラクタ
   * @details 開始時間をシステム時刻で初期化する
   * @param -
   * @return -
   */
  Clock(void);

  /**
   * @brief リセット
   * @details 開始時間を現在のシステム時刻でリセットする
   * @param -
   * @return -
   */
  void reset(void);

  /**
   * @brief 経過時間取得
   * @details 開始時間からの経過時間を取得する
   * @param -
   * @return 経過時間[usec]
   */
  uint64_t now(void) const;
  
  /**
   * @brief 自タスク遅延
   * @details 指定された時間だけタスクを遅延させる
   * @param duration 遅延時間[usec]
   * @return -
   */
  void wait(uint64_t duration)
  {
    dly_tsk(duration);
  }
  
  /**
   * @brief 自タスクスリープ
   * @details 指定された時間だけタスクをスリープさせる
   * @param duration スリープ時間[usec]
   * @return -
   */
  void sleep(uint64_t duration)
  {
    tslp_tsk(duration);
  }

  /**
   * @brief インスタンス生成が正常にできたかどうかを確認するための共通メソッド
   * @details Clockでは複数生成が問題ないので、常にfalseを返す
   */
  bool hasError() { return false; }
  


protected:
  /**
   * @brief システム時刻取得
   * @param -
   * @return 現在のシステム時刻[usec]
   */
  static uint64_t getTim();

private:
    uint64_t mStartClock;
}; // class Clock
}  // namespace spikeapi

#endif // !SPIKE_CPP_API_CLOCK_H_
