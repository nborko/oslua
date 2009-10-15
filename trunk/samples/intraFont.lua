local colors = {
    RED =   osl.drawing.RGB(0xff, 0, 0),
    GREEN = osl.drawing.RGB(0, 0xff, 0),
    BLUE =  osl.drawing.RGB(0, 0, 0xff),
    WHITE = osl.drawing.RGB(0xff, 0xff, 0xff),
    LITEGRAY = osl.drawing.RGB(0xbf, 0xbf, 0xbf),
    GRAY =  osl.drawing.RGB(0x7f, 0x7f, 0x7f),
    DARKGRAY = osl.drawing.RGB(0x3f, 0x3f, 0x3f),
    BLACK = osl.drawing.RGB(0, 0, 0)
}

osl.SetQuitOnLoadFailure(true)
osl.controller.SetKeyAutorepeatInit(40)
osl.controller.SetKeyAutorepeatInterval(10)

local skip = false

-- Load background
local bkg = osl.image.LoadImageFilePNG("bkg.png", osl.IN_RAM + osl.SWIZZLED, osl.PF_8888)

-- Load fonts
local ltn = {}
for i = 1, 16 do
    ltn[i] = osl.text.LoadFontFile(string.format("flash0:/font/ltn%d.pgf", i - 1))
    osl.text.IntraFontSetStyle(ltn[i], 1.0, colors.WHITE, colors.BLACK, osl.INTRAFONT_ALIGN_LEFT)
end

local jpn0 = osl.text.LoadIntraFontFile("flash0:/font/jpn0.pgf", osl.INTRAFONT_CACHE_ALL + osl.INTRAFONT_STRING_SJIS); --japanese font with SJIS support
osl.text.IntraFontSetStyle(jpn0, 1.0, colors.WHITE, colors.BLACK, osl.INTRAFONT_ALIGN_LEFT)

local kr0 = osl.text.LoadIntraFontFile("flash0:/font/kr0.pgf", osl.INTRAFONT_STRING_UTF8);  --Korean font (not available on all systems) with UTF-8 encoding
osl.text.IntraFontSetStyle(kr0, 0.8, colors.WHITE, colors.DARKGRAY, osl.INTRAFONT_NONE);                                  --scale to 80%

chn = osl.text.LoadIntraFontFile("flash0:/font/gb3s1518.bwfon", osl.INTRAFONT_NONE);               --chinese font
osl.text.IntraFontSetStyle(chn, 0.8, colors.WHITE, colors.DARKGRAY, osl.INTRAFONT_NONE);                                  --scale to 80%

local clock = 0

while not osl.quit() do
    clock = (clock + 1) % 60
    if not skip then
        osl.drawing.StartDrawing()
        osl.image.DrawImageXY(bkg, 0, 0)

        -- Draw various text
        local y = 15
        osl.text.IntraFontSetStyle(ltn[5], 1.0, colors.BLACK, colors.WHITE, osl.INTRAFONT_ALIGN_CENTER)
        osl.text.SetFont(ltn[5])
        osl.text.DrawString(240, y, string.format("OSLib v.%s with intraFont by Sakya", osl.VERSION))
        osl.text.IntraFontSetStyle(ltn[5], 1.0, colors.WHITE, colors.BLACK, osl.INTRAFONT_ALIGN_LEFT)

        y = y + 30
        osl.text.SetFont(ltn[9])
        osl.text.DrawString(10, y, "Latin Sans-Serif: ")
        osl.text.SetFont(ltn[1])
        osl.text.DrawString(180, y, "regular, ")
        osl.text.SetFont(ltn[3])
        osl.text.DrawString(270, y, "italic, ")
        osl.text.SetFont(ltn[5])
        osl.text.DrawString(330, y, "bold, ")
        osl.text.SetFont(ltn[7])
        osl.text.DrawString(390, y, "both")

        y = y + 20
        osl.text.SetFont(ltn[9])
        osl.text.DrawString(10, y, "Latin Sans-Serif small: ")
        osl.text.DrawString(180, y, "regular, ")
        osl.text.SetFont(ltn[11])
        osl.text.DrawString(270, y, "italic, ")
        osl.text.SetFont(ltn[13])
        osl.text.DrawString(330, y, "bold, ")
        osl.text.SetFont(ltn[15])
        osl.text.DrawString(390, y, "both")

        y = y + 20
        osl.text.SetFont(ltn[9])
        osl.text.DrawString(10, y, "Latin with Serif: ")
        osl.text.SetFont(ltn[2])
        osl.text.DrawString(180, y, "regular, ")
        osl.text.SetFont(ltn[4])
        osl.text.DrawString(270, y, "italic, ")
        osl.text.SetFont(ltn[6])
        osl.text.DrawString(330, y, "bold, ")
        osl.text.SetFont(ltn[8])
        osl.text.DrawString(390, y, "both")

        y = y + 20
        osl.text.SetFont(ltn[9])
        osl.text.DrawString(10, y, "Latin with Serif small: ")
        osl.text.SetFont(ltn[10])
        osl.text.DrawString(180, y, "regular, ")
        osl.text.SetFont(ltn[12])
        osl.text.DrawString(270, y, "italic, ")
        osl.text.SetFont(ltn[14])
        osl.text.DrawString(330, y, "bold, ")
        osl.text.SetFont(ltn[16])
        osl.text.DrawString(390, y, "both")
        y = y + 20
        osl.text.SetFont(ltn[9])
        osl.text.DrawString(10, y, "JPN (S-JIS): ")
        osl.text.SetFont(jpn0)
        osl.text.DrawString(180, y, "CtHg")

        y = y + 25
        osl.text.SetFont(ltn[9])
        osl.text.DrawString(10, y, "Colors: ")
        osl.text.IntraFontSetStyle(ltn[9], 1.0,colors.RED,colors.BLUE,osl.INTRAFONT_NONE)
        osl.text.DrawString(80, y, "colorful, ")
        osl.text.IntraFontSetStyle(ltn[9], 1.0,colors.WHITE,osl.drawing.RGBA(0,0,0,0),osl.INTRAFONT_NONE)
        osl.text.DrawString(140, y, "no shadow, ")
        osl.text.IntraFontSetStyle(ltn[9], 1.0,osl.drawing.RGBA(0,0,0,0),colors.BLACK,osl.INTRAFONT_NONE)
        osl.text.DrawString(220, y, "no text, ")
        osl.text.IntraFontSetStyle(ltn[9], 1.0,osl.drawing.RGBA(0xff,0xff,0xff,0x7f),colors.BLACK,osl.INTRAFONT_NONE)
        osl.text.DrawString(275, y, "transparent, ")
        osl.text.IntraFontSetStyle(ltn[9], 1.0,colors.GRAY,colors.WHITE,osl.INTRAFONT_NONE)
        osl.text.DrawString(363, y, "glowing, ")
        local t = (clock % 60.0) / 60.0
        local val = (t < 0.5) and math.floor(t*511) or math.floor((1.0-t)*511)
        osl.text.IntraFontSetStyle(ltn[9], 1.0,colors.LITEGRAY,osl.drawing.RGB(val, val, val), osl.INTRAFONT_NONE)
        osl.text.DrawString(425, y, "flashing")
        osl.text.IntraFontSetStyle(ltn[9], 1.0,colors.WHITE,colors.BLACK,osl.INTRAFONT_NONE)

        y = y + 20
        osl.text.DrawString(10, y, "Spacing: ")
        osl.text.IntraFontSetStyle(ltn[9], 1.0,colors.WHITE,colors.BLACK,osl.INTRAFONT_WIDTH_FIX)
        osl.text.DrawString(80, y, "fixed (default), ")
        osl.text.IntraFontSetStyle(ltn[9], 1.0,colors.WHITE,colors.BLACK,osl.INTRAFONT_WIDTH_FIX + 12)
        osl.text.DrawString(220, y, "fixed (12), ")
        osl.text.IntraFontSetStyle(ltn[9], 1.0,colors.WHITE,colors.BLACK,osl.INTRAFONT_NONE)
        osl.text.DrawString(360, y, "variable width")

        y = y + 30
        osl.text.DrawString(10, y, "Scaling: ")
        osl.text.IntraFontSetStyle(ltn[1], 0.5,colors.WHITE,colors.BLACK,osl.INTRAFONT_NONE)
        osl.text.SetFont(ltn[1])
        osl.text.DrawString(80, y, "tiny, ")
        osl.text.IntraFontSetStyle(ltn[1], 0.75,colors.WHITE,colors.BLACK,osl.INTRAFONT_NONE)
        osl.text.DrawString(110, y, "small, ")
        osl.text.IntraFontSetStyle(ltn[1], 1.0,colors.WHITE,colors.BLACK,osl.INTRAFONT_NONE)
        osl.text.DrawString(160, y, "regular, ")
        osl.text.IntraFontSetStyle(ltn[1], 1.25,colors.WHITE,colors.BLACK,osl.INTRAFONT_NONE)
        osl.text.DrawString(250, y, "large, ")
        osl.text.IntraFontSetStyle(ltn[1], 1.5,colors.WHITE,colors.BLACK,osl.INTRAFONT_NONE)
        osl.text.DrawString(330, y, "huge")
        osl.text.IntraFontSetStyle(ltn[1], 1.0,colors.WHITE,colors.BLACK,osl.INTRAFONT_NONE)

        y = y + 20
        osl.text.SetFont(ltn[9])
        osl.text.DrawString(10, y, "Align: ")
        osl.text.IntraFontSetStyle(ltn[9], 1.0,colors.WHITE,colors.BLACK,osl.INTRAFONT_ALIGN_LEFT)
        osl.text.DrawString(80, y, "left")
        osl.text.IntraFontSetStyle(ltn[9], 1.0,colors.WHITE,colors.BLACK,osl.INTRAFONT_ALIGN_CENTER)
        osl.text.DrawString((80+470)/2, y, "center")
        osl.text.IntraFontSetStyle(ltn[9], 1.0,colors.WHITE,colors.BLACK,osl.INTRAFONT_ALIGN_RIGHT)
        osl.text.DrawString(470, y, "right")
        osl.text.IntraFontSetStyle(ltn[9], 1.0,colors.WHITE,colors.BLACK,osl.INTRAFONT_NONE)

        y = y + 25
        osl.text.IntraFontSetStyle(ltn[5], 1.0,colors.BLACK,colors.WHITE,osl.INTRAFONT_ALIGN_CENTER)
        osl.text.SetFont(ltn[5])
        osl.text.DrawString(240, y, "Press X to quit")

        osl.drawing.EndDrawing()
    end

    osl.controller.ReadKeys()
    if osl.controller.KeyPressed(osl.KEY_CROSS) then
        osl.quit(true)
    end

    osl.EndFrame()
    skip = osl.SyncFrame()
end

--for i = 1, 16 do
--    osl.text.DeleteFont(ltn[i])
--end
--osl.image.DeleteImage(bkg)
