# 简单的基于 SDL 游戏引擎
- 引入 SDL 库

- C++ 模板
1. 变长参数模板  
    通过形如 `template <typename... Ts> class Magic{};` 的形式来声明一个变长参数模板。这个模板可以支持 0 ~ N 个变长参数。
    如果希望支持至少一个参数，可以使用 `template <typename T, typename... Ts> class Magic{};` 的写法。
2. 同样的，可以在函数中使用上述的变长参数模板。  
   例如，对于 `printf` 函数可以写出一个类型安全版  
   ```C++
   template <typename... Ts>
   void prinft(std::string& Str, Ts.. Args);
   ```
3. 如何解包  
   可以使用 `sizeof...(Args)` 来计算可变参数的长度  
   ```C++
   template <typename... Ts>
   void Magic(Ts... Args) {
       std::cout << sizeof...(Args) << std::endl;
   }
   ```


- CMakeLists 笔记
1. `include_directories(${PATH_NAME})` 用来指定目录下头文件路径
2. `add_library(${PROJECT_NAME} ${ALL_SOURCES} ${ALL_INCLUDES})` 用于生成动态库
3. `target_include_directories(${PROJECT_NAME} INTERFACE ${PATH_NAME})` 外部引用动态库时，可以通过此方法指定动态库的头文件路径，需要在 `add_library` 之后
4. `target_link_libraries(${PROJECT_NAME} ${LIB_NAME})` 用来指定链接库，输入名字，需要在 `add_executable` 之后 
5. `warning C4819: 该文件包含不能在当前代码页(936)中表示的字符` 可以在 CMAKE 中加入 
    ```C++
        if (MSVC)
            # 设置 msvc 输入代码编码格式为 utf-8
            set(CMAKE_C_FLAGS /source-charset:utf-8)
        endif()
    ```
6. .gitgnore 文件更新
   ```git
   git rm -r --cached .
   git add .
   git commit -m 'update .gitignore'
   git push -u origin master
   ```
7. `std::enable_shared_from_this` 如果父子类都需要这个特性，那么只需要在父类中继承这个类就可以了。在子类中可以通过 `std::static_ptr_cast<>` 方法来转换到子类的 `shared_ptr`
   ```C++
   class A : public std::enable_shared_from_this<A>
    {
    };

    class B : public A
    {
    public:
        void Test(const std::shared_ptr<B> &Parent)
        {
            if (Parent == std::static_pointer_cast<B>(shared_from_this()))
            {
                printf("Parent == This\n");
                return;
            }
            printf("Parent != This\n");
        }
    };

    int main(int argc, char **args)
    {
        auto b = std::make_shared<B>();
        auto testB = std::make_shared<B>();
        b->Test(b);     // Output : Parent == This
        b->Test(testB); // Output : Parent != This

        return 0;
    }
   ```
8. 
