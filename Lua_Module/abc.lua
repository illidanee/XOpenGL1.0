-- 定义一个名为 abc 的模块
abc = {}

-- 定义一个常量
abc.constant = "this is a constant"

-- 定义一个函数
function abc.func1()
    io.write("this is a public function!\n")
end

local function func2()
    print("this is a private function!")
end

function abc.func3()
    func2()
end

return abc