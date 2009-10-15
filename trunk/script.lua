local fontScale = 0.8

local pgfFont = osl.text.LoadFontFile("flash0:/font/ltn0.pgf")
pgfFont:SetStyle(fontScale, osl.drawing.RGB(255, 255, 255), osl.drawing.RGBA(0, 0, 0, 0), osl.INTRAFONT_NONE)
local fontHeight = pgfFont.charHeight * fontScale + 2
local fontAdj = pgfFont.charHeight - fontHeight
osl.text.SetFont(pgfFont)

local counter = 0
local index = 1
local skip = false

local samples = {
    { title = "Hello World", path = "samples", script = "helloWorld.lua" },
    { title = "Dialog Sample", path = "samples", script = "dialog.lua" },
    { title = "IntraFont Sample", path = "samples", script = "intraFont.lua" },
    { title = "Rect and Fonts Sample", path = "samples", script = "rectAndFonts.lua" },
    { title = "Super Patrick II Demo", path = "samples/Super_Patrick_II", script = "script.lua" }
}

while not osl.quit() do

    if not skip then

        local y = 50
        osl.drawing.StartDrawing()

        osl.text.DrawString(30, 10, "OSLua Samples")

        for i = 1, #samples do
            osl.text.DrawString(30, 30 + fontHeight * i, samples[i].title)
        end

        osl.text.DrawString(30, 260 - fontHeight, "Press START to Exit")

        osl.drawing.SetAlpha(osl.FX_ALPHA, 255 - 255 * (counter < 30 and counter / 30 or (60 - counter) / 30))
        osl.drawing.DrawFillRect(25, 25 + fontAdj + fontHeight * index, 300, 25 + fontAdj + fontHeight * (index + 1), osl.drawing.RGB(255, 255, 255))
        osl.drawing.SetAlpha(osl.FX_NONE)

        osl.drawing.EndDrawing()
    end

    osl.controller.ReadKeys()
    if osl.controller.KeyPressed(osl.KEY_START) then
        osl.quit(true)
    end
    if osl.controller.KeyPressed(osl.KEY_UP) then
        if index > 1 then
            index = index - 1
        else
            index = #samples
        end
        counter = 0
    end
    if osl.controller.KeyPressed(osl.KEY_DOWN) then
        if index < #samples then
            index = index + 1
        else
            index = 1
        end
        counter = 0
    end
    if osl.controller.KeyPressed(osl.KEY_CROSS) then
        osl.controller.FlushKey()
        osl.drawing.StartDrawing()
        osl.drawing.ClearScreen(osl.drawing.RGB(0, 0, 0));
        osl.drawing.EndDrawing()
        osl.text.SetFont(osl.sceFont)
        osl.EndFrame()
        osl.SyncFrame()
        local cwd = libfs.cwd()
        libfs.chdir(samples[index].path)
        local script, err = loadfile(samples[index].script)
        if script then xpcall(script, osl.message.Warning) else osl.message.Warning(err) end
        libfs.chdir(cwd)
        osl.controller.FlushKey()
        osl.drawing.StartDrawing()
        osl.drawing.ClearScreen(osl.drawing.RGB(0, 0, 0));
        osl.drawing.EndDrawing()
        osl.text.SetFont(pgfFont)
        osl.quit(false)
    end

    counter = (counter + 1) % 60

    osl.EndFrame()
    skip = osl.SyncFrame()
end
