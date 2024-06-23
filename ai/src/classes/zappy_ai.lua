--- @class ZappyAI
--- @field public params ZappyParamsContainer
--- @field public server ZappyServer
--- @field public logger ZappyLogger
--- @field public inventory ZappyInventory
--- @field public commandsQueue ZappyCommandsQueue
--- @field public status number
--- @field public worldDimensions {x: number, y: number}
--- @field protected numTicks number
--- @field protected isBusy boolean
local ZappyAI <const> = {}

local Posix <const> = require("posix")
local Socket <const> = require("socket")
local Json <const> = require("ai/src/vendors/json")
local Config <const> = require("ai/src/config")

local ZappyCommandsQueue <const> = require("ai/src/classes/zappy_commands_queue")
local ZappyAction <const> = require("ai/src/constants/network_zappy_action")
local ZappyParamsContainer <const> = require("ai/src/classes/zappy_params")
local ZappyAnswer <const> = require("ai/src/constants/network_zappy_answer")
local ZappyInventory <const> = require("ai/src/classes/zappy_inventory")
local TerminalColor <const> = require("ai/src/constants/terminal_color")
local ZappyAIStatus <const> = require("ai/src/enums/zappy_ai_status")
local ZappyServer <const> = require("ai/src/classes/zappy_server")
local ZappyLogger <const> = require("ai/src/classes/zappy_logger")
local ZappyEnvironment <const> = require("ai/src/classes/zappy_environment")
local ZappyTask <const> = require("ai/src/enums/zappy_ai_task")
local Utils <const> = require("ai/src/utils")
local LookParser <const> = require("ai/src/look_parser")

--- @param args string[]
--- @return ZappyAI
function ZappyAI.New(args)
    local self = setmetatable({}, { __index = ZappyAI })

    self.logger = ZappyLogger.New()
    self.params = ZappyParamsContainer.New(args)
    self.server = ZappyServer.New(self.params:Get("h"), self.params:Get("p"))
    self.inventory = ZappyInventory.New(self)
    self.commandsQueue = ZappyCommandsQueue.New(self)
    self.status = ZappyAIStatus.CONNECTING
    self.worldDimensions = {}
    self.isBusy = false
    self.numTicks = 0
    self.level = 1

    Posix.signal(Posix.SIGINT, function()
        self.logger:Warn("CTRL + C Pressed in the console, exiting...")
        self.status = ZappyAIStatus.ENDED
    end)
    return self
end

--[[
    Getters
--]]
--- Return true if the ai is playing 
--- @return boolean
function ZappyAI:GetIsPlaying()
    return self.status == ZappyAIStatus.PLAYING
end

--- Get the current level of the AI
--- @return number
function ZappyAI:GetLevel()
    return self.level
end

--- Return true if the AI is busy (doing an action)
--- @return boolean
function ZappyAI:GetIsBusy()
    return self.isBusy
end

--- @param targetTask number
--- @return boolean
function ZappyAI:HasTo(targetTask)
    return self.task == targetTask
end

--[[
    Setters
--]]
--- @param status number
function ZappyAI:SetStatus(status)
    self.status = status
end

--- @param isBusy boolean
--- @return void
function ZappyAI:SetBusy(isBusy)
    self.isBusy = isBusy
    self.logger:Debug(("[%sS%s] State updated to: %s%s"):format(TerminalColor.RED, TerminalColor.RESET, isBusy and ("%sbusy"):format(TerminalColor.RED) or ("%savailable"):format(TerminalColor.GREEN), TerminalColor.RESET))
end

--- @param task number
--- @return void
function ZappyAI:SetTask(task)
    if self.task == task then
        return
    end
    self.task = task
    self.logger:Debug(("[%sT%s] New task: %s%s%s"):format(TerminalColor.YELLOW, TerminalColor.RESET, TerminalColor.YELLOW, task, TerminalColor.RESET))
end

--[[
    Errors
-]]
--- @param message string
--- @return void
function ZappyAI:Error(message)
    self.logger:Error(message)
    os.exit(84)
end

--[[
    Actions
--]]
--- Send the team's name to the server and receive game's data
--- @return boolean
function ZappyAI:SetupBaseInfos()
    local teamName <const> = self.params:Get("n")
    local data <const> = self.server:SendSync(teamName, 2)

    if not data[1] or not data[2] then
        return false
    end
    self.logger:Info("Team is allowed to connect.")
    local dimensions <const> = Utils.SplitString(data[2], " ")
    for _, dimension in ipairs(dimensions) do
        dimension = tonumber(dimension)
        if not dimension then
            return false
        end
    end
    self.worldDimensions = {dimensions[1], dimensions[2]}
    self.logger:Info(("World dimension is X: %s | Y: %s"):format(dimensions[1], dimensions[2]))
    return true
end

--- Ask the server for the base inventory
--- @return void
function ZappyAI:SetupInventory()
    local input = self.server:SendSync(ZappyAction.GET_INVENTORY)
    input = input:match("%[(.*)%]")
    input = input:gsub("^%s+", ""):gsub("%s+$", "")

    local items = {}
    local function split(str, sep)
        local result = {}
        for part in str:gmatch("([^" .. sep .. "]+)") do
            table.insert(result, part)
        end
        return result
    end

    local elements = split(input, ",")
    for _, element in ipairs(elements) do
        element = element:gsub("^%s+", ""):gsub("%s+$", "")
        local item, quantity = element:match("(%a+)%s+(%d+)")
        if item and quantity then
            items[item] = tonumber(quantity)
        end
    end

    for item, quantity in pairs(items) do
        self.inventory:Add(item, quantity)
    end
end

--- @param callback fun(environment: ZappyEnvironment) | nil
function ZappyAI:LookupEnvironment(callback)
    self.commandsQueue:Enqueue(ZappyAction.LOOKUP_ENVIRONMENT, function(answer)
        if not callback then
            return
        end
        local parsedResult <const> = LookParser.Parse(answer)
        callback(ZappyEnvironment.New(parsedResult))
    end)
end

-- Move forward one tile
function ZappyAI:MoveForward()
    self.commandsQueue:Enqueue(ZappyAction.MOVE_FORWARD, function(answer)
        if answer ~= "ok" then
            -- Fail
            return
        end
        -- Success
    end)
end

-- Turn 90 degrees to the right
function ZappyAI:TurnRight()
    self.commandsQueue:Enqueue(ZappyAction.MOVE_RIGHT, function(answer)
        if answer ~= "ok" then
            -- Fail
            return
        end
        -- Success
    end)
end

-- Turn 90 degrees to the left
function ZappyAI:TurnLeft()
    self.commandsQueue:Enqueue(ZappyAction.MOVE_LEFT, function(answer)
        if answer ~= "ok" then
            -- Fail
            return
        end
        -- Success
    end)
end

-- Broadcast a message
--- @param message string
function ZappyAI:Broadcast(message)
    self.commandsQueue:Enqueue(ZappyAction.BROADCAST, function(answer)
        if answer ~= "ok" then
            -- Fail
            return
        end
        -- Success
    end, {message})
end

-- Get number of unused slots in the team
function ZappyAI:ConnectNbr()
    self.commandsQueue:Enqueue(ZappyAction.CONNECT_NBR, function(answer)
            self.logger:Info(("Connect number response: %s"):format(answer))
    end)
end

-- Fork a player
function ZappyAI:ForkPlayer()
    self.commandsQueue:Enqueue(ZappyAction.FORK, function(answer)
        if answer ~= "ok" then
            -- Fail
            return
        end
        -- Success
    end)
end

-- Eject players from this tile
function ZappyAI:Eject()
    self.commandsQueue:Enqueue(ZappyAction.EJECT, function(answer)
        if answer ~= "ok" then
            -- Fail
            return
        end
        -- Success
    end)
end

-- Take an object
--- @param object string
function ZappyAI:TakeObject(object)
    self.commandsQueue:Enqueue(ZappyAction.TAKE_OBJECT, function(answer)
        if answer ~= "ok" then
            -- Fail
            return
        end
        -- Success
    end, {object})
end

-- Set an object
--- @param object string
function ZappyAI:SetObject(object)
    self.commandsQueue:Enqueue(ZappyAction.SET_OBJECT, function(answer)
        if answer ~= "ok" then
            -- Fail
            return
        end
        -- Success
    end, {object})
end

-- Start an incantation
function ZappyAI:StartIncantation()
    self.commandsQueue:Enqueue(ZappyAction.INCANTATION, function(answer)
        if answer:find("ko") then
            -- Fail
            return
        end
        -- Success
    end)
end

--[[
    AI Core
--]]
--- @return void
function ZappyAI:IncreaseTickIndex()
    self.numTicks = self.numTicks + 1
end

---@param zappyAI ZappyAI
local function listen(zappyAI)
    local sock <const> =  zappyAI.server:GetTcpClient()
    while true do
        sock:settimeout(0)
        while true do
            local data, err = sock:receive("*l")
            if data and not err then
                zappyAI:HandleIncomingPacket(data)
            end
            coroutine.yield()
        end
    end
end

--- @param dataStr string
--- @return void
function ZappyAI:HandleIncomingPacket(dataStr)
    if Utils.StartsWith(dataStr, "message") then
        return self.logger:Debug(("New broadcast packet received: [%s]"):format(dataStr))
    end
    if dataStr == "dead" then
        self.status = ZappyAIStatus.ENDED
        self.logger:Warn("AI Bot is dead...")
        return
    end
    self.commandsQueue:HandleCommandCallback(dataStr)
end

--- Setup TCP listen thread and main AI thread
--- @return void
function ZappyAI:SetupThreads()
    self:SetupInventory()
    
    local tcpListenRoutine <const> = coroutine.create(function() listen(self) end)
    while self:GetIsPlaying() do
        if coroutine.status(tcpListenRoutine) ~= "dead" then
            coroutine.resume(tcpListenRoutine)
        end
        if not self:GetIsBusy() then
            self:UpdateTask()
            self:ExecuteTask()
        end
        self.commandsQueue:Dequeue()
        self:IncreaseTickIndex()
        Socket.sleep(0.1)
    end
end

--[[
    Main decision maker
--]]

-- Define priorities based on the current state
function ZappyAI:UpdateTask()
    if self.inventory:Count("food") < 13 then
        self:SetTask(ZappyTask.FIND_FOOD)
        return
    end
    if self:CanElevate() then
        self:SetTask(ZappyTask.ELEVATE)
        return
    end
    self:SetTask(ZappyTask.FIND_MATERIALS)
end

-- Execute task
function ZappyAI:ExecuteTask()
    -- Food task
    if self:HasTo(ZappyTask.FIND_FOOD) then
        self:SetBusy(true)
        self.logger:Debug(("[%sT%s] I need some food !"):format(TerminalColor.YELLOW, TerminalColor.RESET))
        self:MoveRandom()
        
        self:LookupEnvironment(function(environment)
            local tileWithFood <const> = environment:GetTileWith("food")
            if not tileWithFood then
                self:SetBusy(false)
                return
            end
            if tileWithFood:GetPosition() == 0 then
                self:Take("food", function()
                    self:SetBusy(false)
                end)
                return
            end
            self:WalkToTile(tileWithFood:GetPosition(), function()
                self:Take("food", function()
                    self:SetBusy(false)
                end)
                return
            end)
        end)
        return
    end

    -- Elevation task
    if self:HasTo(ZappyTask.ELEVATE) then
        self.logger:Debug(("[%sT%s] I to elevate !"):format(TerminalColor.YELLOW, TerminalColor.RESET))
        return
    end

    -- Finding materials task
    if self:HasTo(ZappyTask.FIND_MATERIALS) then
        self.logger:Debug(("[%sT%s] I need to find some materials to elevate !"):format(TerminalColor.YELLOW, TerminalColor.RESET))
        return
    end
end

--- Return true if the AI has enough items to elevate to the next level
--- @return boolean
function ZappyAI:CanElevate()
    local currentLevel <const> = self:GetLevel()

    if currentLevel == Config.MaxLevel then
        return false
    end
    local nextElevationCfg <const> = Config.ElevationRequirements[currentLevel]
    if not nextElevationCfg then
        return false
    end
    for itemName, requiredQuantity in pairs(nextElevationCfg.items) do
        if not self.inventory:Has(itemName, requiredQuantity) then
            return false
        end
    end
    return true
end

--[[
    AI Actions
--]]
--- @param tileIndex number
--- @param callback fun()
function ZappyAI:WalkToTile(tileIndex, callback)
    local actions <const> = Utils.GetActionsToTile(tileIndex)

    if not actions then
        return error("Tile index is invalid")
    end
    for actionIndex, action in ipairs(actions) do
        if actionIndex == #actions then
            self.commandsQueue:Enqueue(action, callback)
        else
            self.commandsQueue:Enqueue(action)
        end
    end
end

--- @param itemName string
--- @param callback fun(isSuccess: boolean)
function ZappyAI:Take(itemName, callback)
    self.commandsQueue:Enqueue(ZappyAction.TAKE_OBJECT, function(answer)
        if answer ~= ZappyAnswer.EXECUTED then
            return callback(false)
        end
        self.inventory:Add(itemName)
        return callback(true)
    end, {itemName})
end

function ZappyAI:MoveRandom()
    local possibilities <const> = {ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_RIGHT, ZappyAction.MOVE_LEFT}
    local action <const> = possibilities[math.random(#possibilities)]
    self.commandsQueue:Enqueue(action, function(answer)
        if answer ~= ZappyAnswer.EXECUTED then
            self.logger:Warn(("Action %sMoveRandom%s failed !"):format(TerminalColor.YELLOW, TerminalColor.RESET))
        end
    end)
end

-- Export
return ZappyAI
