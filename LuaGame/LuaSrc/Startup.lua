print("Hello form Lua")
print(Table1.Value)

abc = ABC.new()
print(abc:get_value())
abc = ABC.new(42)
print(abc:get_value())
abc:overload()
abc:overload(12)