#pragma once
#include    <windows.h>
#include    <GamePad.h>

/**
 * @brief ボタンの列挙型
 */
enum BUTTON
{
    LUP,    /**< 左上ボタン */
    LDOWN,  /**< 左下ボタン */
    LLEFT,  /**< 左左ボタン */
    LRIGHT, /**< 左右ボタン */
    RUP,    /**< 右上ボタン */
    RDOWN,  /**< 右下ボタン */
    RLEFT,  /**< 右左ボタン */
    RRIGHT, /**< 右右ボタン */
};

/**
 * @brief ボタンの状態を表す列挙型
 */
enum STATE
{
    UP = 0,         /**< ボタンが離されている */
    HELD = 1,       /**< ボタンが押し続けられている */
    RELEASED = 2,   /**< ボタンがリリースされた */
    PRESSED = 3,    /**< ボタンが押された */
};

/**
 * @brief 入力管理クラス
 */
class Input
{
private:
    static BYTE m_OldKeyState[256];                 /**< 前回のキーボードの状態 */
    static BYTE m_KeyState[256];                    /**< 現在のキーボードの状態 */

    // ゲームパッドの判定
    static DirectX::GamePad m_GamePad;              /**< ゲームパッドのオブジェクト */
    static DirectX::GamePad::State m_State;        /**< ゲームパッドの状態 */
    static DirectX::GamePad::ButtonStateTracker m_StateTracker; /**< ゲームパッドのボタンの状態を追跡するトラッカー */

public:
    /**
     * @brief 入力管理クラスの初期化
     */
    static void Init();

    /**
     * @brief 入力管理クラスの終了処理
     */
    static void Uninit();

    /**
     * @brief 入力情報の更新
     */
    static void Update();

    /**
     * @brief 指定したキーコードのキーが押されているかを取得します。
     * @param KeyCode キーコード
     * @return キーが押されている場合はtrue、それ以外はfalse
     */
    static bool GetKeyPress(BYTE KeyCode);

    /**
     * @brief 指定したキーコードのキーがトリガーされたかを取得します。
     * @param KeyCode キーコード
     * @return キーがトリガーされた場合はtrue、それ以外はfalse
     */
    static bool GetKeyTrigger(BYTE KeyCode);

    /**
     * @brief 指定したゲームパッドのボタンの状態を取得します。
     * @param button ボタン
     * @param _buttonState ボタンの状態
     * @return ボタンの状態が指定した状態である場合はtrue、それ以外はfalse
     */
    static bool GetGamePad(BUTTON button, STATE _buttonState);

    static void Vibration(int player, float leftMotor, float rightMotor, float leftTrigger, float rightTrigger);
};
