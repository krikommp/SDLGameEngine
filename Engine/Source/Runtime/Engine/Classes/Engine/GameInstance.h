#ifndef _GAMEINSTANCE_H_
#define _GAMEINSTANCE_H_

#include <memory>
/**
 * @brief 保存当前的 WorldContext 和其他游戏信息
 * 类似与管理器
 * 在整个游戏中只有一个
 * 切换关卡等操作不会影响其中数据
 * 所以一些跟关卡无关的数据可以放在这里
 * 
 */
class UGameInstance : public std::enable_shared_from_this<UGameInstance>
{
public:
    ~UGameInstance();
public:
    void InitializeStandalone();

    void StartGameInstance();

    void Init();
protected:
    std::shared_ptr<struct FWorldContext> WorldContext;
};

#endif //  _GAMEINSTANCE_H_