--定义协程体
function f1()
	print('------------Step 1');
	coroutine.yield();
	print('------------Step 2');
	coroutine.yield();
	print('------------Step 3');
	coroutine.yield();
	print('------------Step 4');
	coroutine.yield();
	print('------------Step 5');
end

--运行协程
co = coroutine.create(f1);
coroutine.resume(co);

--恢复执行
function cc()
	coroutine.resume(co);
end

--查看状态
function ss()
	print(coroutine.status(co));
end