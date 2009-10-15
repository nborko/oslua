f = io.open("ll.lua", "w+")
f:write(string.dump(loadfile("test.lua")))
