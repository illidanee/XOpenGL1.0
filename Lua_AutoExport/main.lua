
local function main()

    a = XHero(199, 'Hello Lua');
    a:SetName("Hello illidan");
    a:SetAge(18);
	
	print("Name: "..a:GetName());
	print("Age: "..a:GetAge());
end


print("---------------------------------------------------------Start");

main()

print("---------------------------------------------------------End");