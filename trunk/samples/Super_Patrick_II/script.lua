--
-- Based on OSLib MOD port by Sakya (in english; pardon for translation errors)
--

-- Constants
gravity = 0.25
jumpSpeed = -6
groundLevel = 240
limitCameraX = 240

-- Globals
cameraX = 0
cameraY = 0

-- Manage the runner (called once per frame)
ManageRunner = function(runner)
    -- animate
    runner.frameNb = runner.frameNb + 1
    -- horizontal movement
    runner.x = runner.x + runner.vx
    -- vertical movement + manage gravity's effect on speed (VY)
    runner.y = runner.y + runner.vy
    runner.vy = runner.vy + gravity

    -- increase horizontal velocity (acceleration), but don't exceed 4
    runner.vx = math.min(runner.vx + 0.03, 4.0)

    -- manage collision with ground
    if runner.y + runner.height >= groundLevel then
        -- On the ground, the speed goes to zero (and we get a concussion, but not in a game :p)
        runner.vy = 0
        -- Reset to ground level
        runner.y = groundLevel - runner.height
        -- He's on the ground => he may skip
        runner.onGround = true
    end

    -- Cross: Jump
    if osl.controller.KeyPressed(osl.KEY_CROSS) and runner.onGround then
        runner.vy = jumpSpeed
        runner.onGround = false
    end
end

-- Draw the runner
DrawRunner = function(runner)
if runner.onGround then
        -- Draw the runner with another tile periodically (0-1-0-...)
        osl.image.SetImageFrame(imgRunner, (runner.frameNb / 16) % 2)
    else
        -- Otherwise he is in the air, use the jump tile (2)
        osl.image.SetImageFrame(imgRunner, 2)
    end
    -- Drawing, relative to the camera
    osl.image.DrawImageXY(imgRunner, math.floor(runner.x - cameraX), math.floor(runner.y - cameraY))
end

-- Return an initialized runner object
createRunner = function()
    return {
        frameNb = 0,
        -- Character size calculated via the image
        width = imgRunner.frameSizeX,
        height = imgRunner.frameSizeY,
        -- Initial position
        x = 0,
        y = groundLevel - 34,
        -- Initial velocities 0
        vx = 0,
        vy = 0,
        onGround = true,
        dead = false
    }
end

-- Return TRUE is there's a collision between the object and the runner specified
collision = function(object, runner)
    -- Overlay the two rectangles
    return runner.x + runner.width >= object.x and
        runner.x < object.x + object.width and
        runner.y + runner.height >= object.y and
        runner.y < object.y + object.height
end

-- Manage an object (regardless of its type) with a defined runner (including collisions)
ManageObject = function(object, runner)
    -- There is nothing special to do for the stones since they don't move
    if collision(object, runner) then
        -- If there's a collision with the runner, you lose!
        runner.dead = true
    end
end

-- Draw an object (regardless of type)
DrawObject = function(object)
    -- Drawing, relative to the camera
    osl.image.DrawImageXY(imgRock, object.x - cameraX, object.y - cameraY)
end

-- Create a new object of type rock, which we choose the initial X position
createRock = function(positionX) 
    return {
        -- Get info from the image
        width = imgRock.sizeX,
        height = imgRock.sizeY,
        -- The vertical position is always on the ground
        x = positionX,
        y = groundLevel - 16
    }
end

-- Generates an object type rock, placing it randomly just after the previous rock
-- And taking into account the difficulty for distance
createRandomRock = function(previousObject, difficulty)
    -- Distance with the previous rock
    distance = difficulty + math.random(difficulty)
    return createRock(previousObject.x + distance)
end

-- Number of objects
NB_OBJECTS = 20
-- Color used for transparency in the images
colorMask = osl.drawing.RGB(255, 0, 255)
-- The runner (main character)
runner = null
-- The objects (rocks, etc.)
objects = {}
-- various
difficulty = 0
time = 0
pause = false
skip = false
-- Scroll the ground texture
scrollX = 0

-- Initialization of OSLib
osl.SetQuitOnLoadFailure(false)

-- Load the images
imgBackground = osl.image.LoadImageFilePNG("fond.png", osl.IN_RAM, osl.PF_5650)
imgGround = osl.image.LoadImageFilePNG("sol.png", osl.IN_RAM, osl.PF_5650)

-- These images have a transparent color
osl.drawing.SetTransparentColor(colorMask)
imgRunner = osl.image.LoadImageFilePNG("coureur.png", osl.IN_RAM, osl.PF_5551)
imgRock = osl.image.LoadImageFilePNG("pierre.png", osl.IN_RAM, osl.PF_5551)
osl.drawing.DisableTransparentColor()

-- Load the resources
music = osl.audio.LoadSoundFileMP3("test.mp3", osl.FMT_STREAM)

-- Quick check that everything has loaded before continuing
if not music or not imgRunner or not imgBackground or not imgRunner or not imgRock then
    osl.message.FatalError("Missing files, please check your installation!")
end

-- The runner is divided into multiple tiles
osl.image.SetImageFrameSize(imgRunner, 20, 34)

osl.audio.SetSoundLoop(music, true)
osl.audio.PlaySound(music, 0)

while not osl.quit() do
    -- Initialize start of game
    time = 0
    cameraX = 0
    cameraY = 0
    difficulty = 192

    -- Initialize the runner
    runner = createRunner()

    -- Initialize the objects
    objects[1] = createRock(480)
    for i = 2, NB_OBJECTS do
        -- Others (each placed at a random distance from each other)
        objects[i] = createRandomRock(objects[i - 1], difficulty);
    end

    while not osl.quit() do
        -- Should we do the rendering?
        if not skip then
            osl.drawing.StartDrawing()

            -- Blue sky backgound
            osl.drawing.ClearScreen(osl.drawing.RGB(127, 182, 200))

            --[[
            Since the background is repeated every 256 pixels, it's pointless to
            scroll more than that;
            It's sufficient to show one more and shift the rest on the left.
            Also note the division: the bottom scrolls 4x slower than the rest.
            --]]
            scrollX = math.floor(cameraX / 4.0) % 256

            -- Draw the repeating background
            for i = 0, math.floor(480 / 256 + 1) do
                osl.image.DrawImageXY(imgBackground, i * 256 - scrollX, groundLevel - 240)
            end

            -- Draw the ground
            scrollX = math.floor(cameraX % 32)
            for i = 0, math.floor(480 / 32 + 1) do
                osl.image.DrawImageXY(imgGround, i * 32 - scrollX, groundLevel)
            end

            DrawRunner(runner)

            -- Draw the objects
            for i = 1, NB_OBJECTS do
                DrawObject(objects[i])
            end

            -- Display the time at the top of the screen
            osl.text.SetBkColor(osl.drawing.RGBA(0, 0, 0, 128))
            osl.text.SetTextColor(osl.drawing.RGB(255, 255, 255))
            osl.text.DrawString(0, 0, string.format("Time: %i sec", time))

            -- Display pause below that
            if pause then
                osl.text.DrawString(0, 8, "Pause")
            end

            osl.EndFrame()
            osl.drawing.EndDrawing()
        end
        
        -- Game over?
        if runner.dead then
            osl.message.Debug(string.format("You lost!\nYour time: %#1.2f seconds", time))
            break
        end
 
        -- For managing the keys
        osl.controller.ReadKeys()
 
        -- Toggle pause (yes / no)
        if osl.controller.KeyPressed(osl.KEY_START) then
            pause = not pause
        end
 
        -- In pause, the game is "frozen"
        if not pause then

            ManageRunner(runner)
 
            -- Manage the objects (make them move forward, collision, etc.)
            for i = 1, NB_OBJECTS do
                ManageObject(objects[i], runner)
            end

            -- If the first object is completely left of the screen, we regenerate another on
            if objects[1].x + objects[1].width < cameraX then
                --[[
                Shift all objects 1 (the 2nd becomes the 1st, etc..)
                to keep the items sorted according to their X position.
                ]]--
                for i = 2, NB_OBJECTS do
                    -- Generate a new object from the second to last
                    objects[i - 1] = objects[i]
                end
                objects[NB_OBJECTS] = createRandomRock(objects[NB_OBJECTS - 1], difficulty)
            end
 
            -- Camera management
            if runner.x - cameraX > limitCameraX then
                cameraX = runner.x - limitCameraX
            end
 
            -- The distance between the randomly generated rocks continuously decreases
            difficulty = difficulty * 0.9998
 
            -- The loop executes every 1/60 second
            time = time + 1.0 / 60.0
        end
 
        -- Synchronize to 60 fps
        skip = osl.SyncFrameEx(0, 6, 0)

    end

end
