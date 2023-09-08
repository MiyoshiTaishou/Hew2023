#pragma once
#include <GamePad.h>

/**
 * @brief コントローラーのスティック方向を表す列挙型
 */
enum BUTTON
{
    LUP,     ///< 左スティック上
    LDOWN,   ///< 左スティック下
    LLEFT,   ///< 左スティック左
    LRIGHT,  ///< 左スティック右
    RUP,     ///< 右スティック上
    RDOWN,   ///< 右スティック下
    RLEFT,   ///< 右スティック左
    RRIGHT   ///< 右スティック右
};

/**
 * @brief コントローラーのボタンの状態を表す列挙型
 */
enum STATE
{
    UP = 0,         ///< ボタンが離されている状態
    HELD = 1,       ///< ボタンが押されている状態
    RELEASED = 2,   ///< ボタンが離された状態
    PRESSED = 3     ///< ボタンが押された状態
};

/**
 * @brief 入力処理を管理するクラス
 */
class Input
{
private:
    static BYTE m_OldKeyState[256];
    static BYTE m_KeyState[256];

    // パッドの判定
    static DirectX::GamePad m_GamePad;
    static DirectX::GamePad::State m_State;
    static DirectX::GamePad::ButtonStateTracker m_StateTracker;

public:
   
    static void Init();
    static void Update();

    /**
     * @brief キーボードのキーが押されているかを取得する
     * @param[in] KeyCode キーコード
     * @return キーが押されている場合はtrue、それ以外はfalse
     */
    static bool GetKeyPress(BYTE KeyCode);

    /**
     * @brief キーボードのキーが押された瞬間かを取得する
     * @param[in] KeyCode キーコード
     * @return キーが押された瞬間の場合はtrue、それ以外はfalse
     */
    static bool GetKeyTrigger(BYTE KeyCode);

    /**
     * @brief ゲームパッドのボタンの状態を取得する
     * @param[in] button ボタンの列挙型
     * @param[in] _buttonState ボタンの状態（UP/HELD/RELEASED/PRESSED）
     * @return ボタンの状態が指定されたものと一致する場合はtrue、それ以外はfalse
     */
    static bool GetGamePad(BUTTON button, STATE _buttonState);
};
