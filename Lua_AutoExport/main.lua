
local function main()

    a = XHero(199, 'Hello Lua');
    a:SetName("Hello illidan");
    a:SetAge(18);
	
	print("Name: "..a:GetName());
	print("Age: "..a:GetAge());
	
	print("MemberVar:"..a.id);
end

print("GlobalVar:"..id);
print("GlobalTest:"..GlobalTest(11));

print("---------------------------------------------------------Start");

main()

print("---------------------------------------------------------End");