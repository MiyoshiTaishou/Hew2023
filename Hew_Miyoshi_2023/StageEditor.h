#pragma once
#include "scene.h"

// 列挙型でクラスの種類を管理
enum CLASS
{
    BOX,   /**< ボックスクラス */
    ENEMY, /**< エネミークラス */
    NONE,  /**< なし */
};

/**
 * @brief オブジェクトの情報データ構造体
 */
struct InfoObjData
{
    CLASS ClassKind;                          /**< クラスの種類 */
    DirectX::SimpleMath::Vector3 pos;         /**< 位置 */
    DirectX::SimpleMath::Vector3 scale;       /**< スケール */
    DirectX::SimpleMath::Vector3 rot;         /**< 回転 */
};

/**
 * @brief ステージを作成するシーン StageEditor クラス
 */
class StageEditor : public Scene
{
public:
   
    void Init() override;
    void Update() override;   
    void Draw() override;

    /**
     * @brief オブジェクト情報をファイルに保存する関数
     * @param filename 保存先のファイル名
     */
    void SavepositionToFile(const std::string& filename);

    /**
     * @brief オブジェクト情報をファイルから読み込む関数
     * @param filename 読み込むファイル名
     */
    void LoadpositionToFile(const std::string& filename);

    /**
     * @brief オブジェクトを作成する関数
     */
    void CreateObject();

    /**
     * @brief 履歴にオブジェクト情報を追加する関数
     */
    void AddToHistory();

    /**
     * @brief アンドゥ（取り消し）する関数
     */
    void Undo();

    /**
     * @brief リドゥ（やり直し）する関数
     */
    void Redo();

private:
    // 履歴管理用のコンテナ
    std::array<std::list<InfoObjData>, 4> history;
    std::vector<InfoObjData> position;
    std::vector<GameObject*> objList;
    int historyIndex = 0;
};
