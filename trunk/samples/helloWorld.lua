osl.SetQuitOnLoadFailure(true)
osl.controller.SetKeyAutorepeatInit(40)
osl.controller.SetKeyAutorepeatInterval(10)

local bkg = osl.image.LoadImageFilePNG("bkg.png", osl.IN_RAM + osl.SWIZZLED, osl.PF_8888)

local pgfFont = osl.text.LoadFontFile("flash0:/font/ltn0.pgf")
osl.text.IntraFontSetStyle(pgfFont, 1.0, osl.drawing.RGBA(255,255,255,255), osl.drawing.RGBA(0,0,0,0), osl.INTRAFONT_ALIGN_LEFT)
osl.text.SetFont(pgfFont)

local skip = false

while not osl.quit() do
    if not skip then
        osl.drawing.StartDrawing()

        osl.image.DrawImageXY(bkg, 0, 0)
        osl.text.DrawString(180, 150, "Hello world")
        osl.text.DrawString(150, 250, "Press X to quit")

        osl.drawing.EndDrawing()
    end

    osl.controller.ReadKeys()
    if osl.controller.KeyPressed(osl.KEY_CROSS) then
        osl.quit(true)
    end

    osl.EndFrame()
    skip = osl.SyncFrame()
end
