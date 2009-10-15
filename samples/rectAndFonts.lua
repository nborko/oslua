osl.SetQuitOnLoadFailure(true)
osl.controller.SetKeyAutorepeatInit(40)
osl.controller.SetKeyAutorepeatInterval(10)

local skip = false

local bkg = osl.image.LoadImageFilePNG("bkg.png", osl.IN_RAM + osl.SWIZZLED, osl.PF_8888)
local rect_01 = osl.image.LoadImageFilePNG("rect_01.png", osl.IN_RAM + osl.SWIZZLED, osl.PF_8888)

local pgfFont = osl.text.LoadFontFile("flash0:/font/ltn0.pgf")
osl.text.IntraFontSetStyle(pgfFont, 0.5, osl.drawing.RGBA(255,255,255,255), osl.drawing.RGBA(0,0,0,0), osl.INTRAFONT_ALIGN_LEFT)

oftFont = osl.text.LoadFontFile("font.oft")
osl.text.SetTextColor(osl.drawing.RGBA(255,255,255,255))
osl.text.SetBkColor(osl.drawing.RGBA(0,0,0,0))

while not osl.quit() do
    if not skip then
        osl.drawing.StartDrawing()
        osl.image.DrawImageXY(bkg, 0, 0)

        osl.image.DrawImageXY(rect_01, 50, 50)
        osl.text.SetFont(pgfFont)
        osl.text.DrawString(35, 155, "pgf on rect")
        osl.text.SetFont(oftFont)
        osl.text.DrawString(35, 170, "oft on rect")

        osl.drawing.DrawFillRect(30, 150, 200, 250, osl.drawing.RGB(150, 150, 150))
        osl.text.SetFont(pgfFont)
        osl.text.DrawString(35, 155, "pgf on rect")
        osl.text.SetFont(oftFont)
        osl.text.DrawString(35, 170, "oft on rect")

        osl.drawing.DrawFillRect(300, 150, 400, 250, osl.drawing.RGB(100, 100, 100))
        osl.text.SetFont(pgfFont)
        osl.text.DrawString(305, 155, "pgf on rect")
        osl.text.SetFont(oftFont)
        osl.text.DrawString(305, 170, "oft on rect")

        osl.drawing.DrawGradientRect(300, 20, 430, 120, osl.drawing.RGBA(100, 100, 100, 100),osl.drawing.RGBA(100, 100, 100, 100), osl.drawing.RGBA(200, 200, 200, 100), osl.drawing.RGBA(200, 200, 200, 100))
        osl.text.SetFont(pgfFont)
        osl.text.DrawString(305, 25, "pgf on gradient rect")
        osl.text.SetFont(oftFont)
        osl.text.DrawString(305, 40, "oft on gradient rect")

        osl.drawing.EndDrawing()
    end
    
    osl.controller.ReadKeys()
    if osl.controller.KeyPressed(osl.KEY_TRIANGLE, osl.KEY_CIRCLE, osl.KEY_CROSS, osl.KEY_SQUARE, osl.KEY_START) then
        osl.quit(true)
    end

    osl.EndFrame()
    skip = osl.SyncFrame()
end
