//
// Button.h
//
// Copyright (c) 2025 Embedded Technology Software Design Robot Contest
//

#ifndef SPIKE_CPP_API_BUTTON_H_
#define SPIKE_CPP_API_BUTTON_H_

namespace spikeapi {
/**
 * @brief SPIKE ボタンクラス
 */
class Button
{
public:
  /**
   * @brief コンストラクタ
   * @param -
   * @return -
   */
  Button(void) = default;
  
  /**
   * @brief LEFTボタンが押されているかを確認する
   * @param -
   * @return -
   */
  bool isLeftPressed();
  
  /**
   * @brief CENTERボタンが押されているかを確認する
   * @param -
   * @return -
   */
  bool isCenterPressed();

  /**
   * @brief RIGHTボタンが押されているかを確認する
   * @param -
   * @return -
   */
  bool isRightPressed();

  /**
   * @brief BRUETOOTHボタンが押されているかを確認する
   * @param -
   * @return -
   */
  bool isBluetoothPressed();

  /**
   * @brief インスタンス生成が正常にできたかどうかを確認するための共通メソッド
   * @details Buttonでは複数生成が問題ないので、常にfalseを返す
   */
  bool hasError() { return false; }
  
}; // class Button
}  // namespace spikeapi

#endif // !SPIKE_CPP_API_BUTTON_H_
