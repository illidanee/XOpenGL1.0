--定义协程体
function f1(a, b, c)
	print('------------Step 0', a, b, c);
	
	a = a + 1;
	b = b + 1;
	c = c + 1;
	print('------------Step 1', a, b, c);
	coroutine.yield(a, b, c);
	
	
	a = a + 1;
	b = b + 1;
	c = c + 1;
	print('------------Step 2', a, b, c);
	coroutine.yield(a, b, c);

	
	a = a + 1;
	b = b + 1;
	c = c + 1;
	print('------------Step 3', a, b, c);
	coroutine.yield(a, b, c);

	
	a = a + 1;
	b = b + 1;
	c = c + 1;
	print('------------Step 4', a, b, c);
	coroutine.yield(a, b, c);
	
	a = a + 1;
	b = b + 1;
	c = c + 1;
	print('------------Step 5', a, b, c);
end

--运行协程
co = coroutine.create(f1);
coroutine.resume(co, 0, 100, 1000);

--恢复执行
function cc()
	print(coroutine.resume(co, a, b, c));
end

--查看状态
function ss()
	print(coroutine.status(co));
end