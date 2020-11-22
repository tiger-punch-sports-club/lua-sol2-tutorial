#include <lua/lua.hpp>
#include <sol/sol.hpp>
#include <stdio.h>

void RandomStuff()
{
    printf("RandomStuff()\n");
}

int GetRandomNumber(int value)
{
    return value;
}

struct MyStruct
{
    float x, y;

    MyStruct() : x(0), y(0)
    {
    }

    MyStruct(float x, float y) : x(x), y(y)
    {
    }

    void Print() const
    {
        printf("%f, %f\n", x, y);
    }

    float GetX() const
    {
        return x;
    }

    float GetY() const
    {
        return y;
    }

    void SetX(const float& x)
    {
        this->x = x;
    }

    void SetY(const float& y)
    {
        this->y = y;
    }
};

void DoStuffToStruct(MyStruct& myStruct)
{
    myStruct.x = 200;
    myStruct.y = 200;
}

void main() 
{
    sol::state lua{};
    lua.open_libraries(sol::lib::base);

    // 1. Run Lua scripts
    lua.script("print('Hello World from Lua!')");
    
    // 3. Bind and call C++ functions to Lua
    lua.set_function("RandomStuff", &RandomStuff);
    lua.set_function("GetRandomNumber", &GetRandomNumber);
    lua.set_function("DoStuffToStruct", &DoStuffToStruct);

    
    // 4. Bind and use C++ data to Lua
    lua.new_usertype<MyStruct>("MyStruct",
        sol::constructors<void(), void(float, float)>(),
        "x", &MyStruct::x,
        "y", &MyStruct::y,
        "Print", &MyStruct::Print,
        "GetX", &MyStruct::GetX,
        "GetY", &MyStruct::GetY,
        "SetX", &MyStruct::SetX,
        "SetY", &MyStruct::SetY
    );
        
    // 2. Load Lua scripts from disk
    lua.script_file("script.lua");
    
    // 5. Call Lua functions from C++ (With return types)
    const std::function<void()>& luaFunction = lua["LuaFunction"];
    luaFunction();

    const std::function<int(int)>& luaFunction2 = lua["LuaFunction2"];
    auto value = luaFunction2(123);
    printf("value = %d \n", value);

    MyStruct myStruct;
    const std::function<void(MyStruct&)>& luaFunction3 = lua["LuaFunction3"];
    luaFunction3(myStruct);
    myStruct.Print();
}
