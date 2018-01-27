--打印路径
print("----------------------------------------Path");
print("path : " .. package.path);

print("----------------------------------------CPath");
print("cpath : " .. package.cpath);

--加载Lua模块
abc = require("abc");
print("----------------------------------------Lua Module");

print(abc.constant);
abc.func1();
abc.func3();

print("----------------------------------------End");

--加载C程序模块
xyz = require("LuaCLib");
print("----------------------------------------C Module");

total1 = xyz.Sum(11, 22, 33);
print("Total1 = " .. total1);

total2 = XYZ.Sum(22, 33, 44);
print("Total2 = " .. total2);

print("----------------------------------------End");