#pragma once
#include "scene.h"

/**
 * @brief リザルトシーン Result クラス
 */
class Result : public Scene
{
private:
    class Transition* m_Transition{}; /**< 画面遷移を管理するオブジェクト */
    class FadeUI* m_Fade{}; /**< フェードUIを管理するオブジェクト */

    bool m_Goal = false; /**< シーン遷移フラグ */

public:
  
    void Init() override;
    void Update() override;
};
