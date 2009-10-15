osl.network.NetInit()
osl.SetQuitOnLoadFailure(true)
osl.controller.SetKeyAutorepeatInit(40)
osl.controller.SetKeyAutorepeatInterval(10)

local bkg = osl.image.LoadImageFilePNG("bkg.png", osl.IN_RAM + osl.SWIZZLED, osl.PF_8888)

local pgfFont = osl.text.LoadFontFile("flash0:/font/ltn0.pgf")
osl.text.SetFont(pgfFont)

local skip = false
local message = ""
local dialog = osl.DIALOG_NONE

while not osl.quit() do
    if not skip then
        osl.drawing.StartDrawing()
        osl.image.DrawImageXY(bkg, 0, 0)
        osl.text.DrawString(30, 50, "Press X to see a message dialog.")
        osl.text.DrawString(30, 70, "Press [] to see an error dialog.")
        osl.text.DrawString(30, 90, "Press O to see the net conf dialog.")
        osl.text.DrawString(30, 150, "Press /\\ to quit.")

        osl.text.DrawString(30, 200, message);

        dialog = osl.dialog.GetDialogType()
        if dialog ~= osl.DIALOG_NONE then
            osl.dialog.DrawDialog()
            if osl.dialog.GetDialogStatus() == osl.PSP_UTILITY_DIALOG_NONE then
                if osl.dialog.DialogGetResult() == osl.DIALOG_CANCEL then
                    message = "Cancel"
                elseif dialog == osl.DIALOG_MESSAGE then
                    button = osl.dialog.GetDialogButtonPressed()
                    if button == osl.PSP_UTILITY_MSGDIALOG_RESULT_YES then
                        message = "You pressed YES"
                    elseif button == osl.PSP_UTILITY_MSGDIALOG_RESULT_NO then
                        message = "You pressed NO"
                    end
                end
                osl.dialog.EndDialog()
            end
        end
        osl.drawing.EndDrawing()
    end

    if dialog == osl.DIALOG_NONE then
        osl.controller.ReadKeys()
        if osl.controller.KeyPressed(osl.KEY_TRIANGLE) then
            osl.quit(true)
        elseif osl.controller.KeyPressed(osl.KEY_CROSS) then
            osl.dialog.InitMessageDialog("Test message dialog", true)
            message = ""
        elseif osl.controller.KeyPressed(osl.KEY_SQUARE) then
            osl.dialog.InitErrorDialog(0x80020001);
            message = ""
        elseif osl.controller.KeyPressed(osl.KEY_CIRCLE) then
            osl.dialog.InitNetDialog()
            message = ""
        end
    end

    osl.EndFrame()
    skip = osl.SyncFrame()

end

osl.network.NetTerm()
