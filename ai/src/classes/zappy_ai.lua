--- @class ZappyAI
--- @field public params ZappyParamsContainer
--- @field public server ZappyServer
--- @field public logger ZappyLogger
--- @field public inventory ZappyInventory
--- @field public commandsQueue ZappyCommandsQueue
--- @field public status number
--- @field public worldDimensions {x: number, y: number}
--- @field protected numTicks number
local ZappyAI <const> = {}

local Posix <const> = require("posix")
local Socket <const> = require("socket")
local Json <const> = require("ai/src/vendors/json")

local ZappyCommandsQueue <const> = require("ai/src/classes/zappy_commands_queue")
local ZappyAction <const> = require("ai/src/constants/network_zappy_action")
local ZappyParamsContainer <const> = require("ai/src/classes/zappy_params")
local ZappyInventory <const> = require("ai/src/classes/zappy_inventory")
local ZappyAIStatus <const> = require("ai/src/enums/zappy_ai_status")
local ZappyServer <const> = require("ai/src/classes/zappy_server")
local ZappyLogger <const> = require("ai/src/classes/zappy_logger")
local Utils <const> = require("ai/src/utils")
local LookParser <const> = require("ai/src/look_parser")

--- @param args string[]
--- @return ZappyAI
function ZappyAI.New(args)
    local self = setmetatable({}, { __index = ZappyAI })

    self.logger = ZappyLogger.New()
    self.params = ZappyParamsContainer.New(args)
    self.server = ZappyServer.New(self.params:Get("h"), self.params:Get("p"))
    self.inventory = ZappyInventory.New()
    self.commandsQueue = ZappyCommandsQueue.New(self)
    self.status = ZappyAIStatus.CONNECTING
    self.worldDimensions = {}
    self.numTicks = 0

    Posix.signal(Posix.SIGINT, function()
        self.logger:Warn("CTRL + C Pressed in the console, exiting...")
        self.status = ZappyAIStatus.ENDED
    end)
    return self
end

--[[
    Getters
--]]
--- @return boolean
function ZappyAI:GetIsPlaying()
    return self.status == ZappyAIStatus.PLAYING
end

--[[
    Setters
--]]
--- @param status number
function ZappyAI:SetStatus(status)
    self.status = status
end

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
    self.logger:Info(("Base inventory: %s"):format(self.inventory))
end

function ZappyAI:LookupEnvironment()
    local result <const> = self.server:SendSync(ZappyAction.LOOKUP_ENVIRONMENT)
    local parsedResult <const> = LookParser.Parse(result)

    for i, tile in ipairs(parsedResult) do
        self.logger:Info(("Tile %d: %s"):format(i, table.concat(tile, ", ")))
    end
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
    local response = self.server:SendSync(ZappyAction.SET_OBJECT .. " " .. object)
    self.logger:Info(("Set object response: %s"):format(response))
end

-- Start an incantation
function ZappyAI:StartIncantation()
    local response = self.server:SendSync(ZappyAction.INCANTATION)
    self.logger:Info(("Incantation response: %s"):format(response))
end

--- @param command string
--- @return void
function ZappyAI:HandleCommand(command)
    local cmd, param = command:match("^(%S+)%s*(.*)$")
    if cmd == "look" then
        self:LookupEnvironment()
    elseif cmd == "inventory" then
        self:SetupInventory()
    elseif cmd == "forward" then
        self:MoveForward()
    elseif cmd == "right" then
        self:TurnRight()
    elseif cmd == "left" then
        self:TurnLeft()
    elseif cmd == "broadcast" then
        self:Broadcast(param)
    elseif cmd == "connect_nbr" then
        self:ConnectNbr()
    elseif cmd == "fork" then
        self:ForkPlayer()
    elseif cmd == "eject" then
        self:Eject()
    elseif cmd == "take" then
        self:TakeObject(param)
    elseif cmd == "set" then
        self:SetObject(param)
    elseif cmd == "incantation" then
        self:StartIncantation()
    else
        self.logger:Warn(("Unknown command: %s"):format(command))
    end
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
    self:LookupEnvironment()
    
    local tcpListenRoutine <const> = coroutine.create(function() listen(self) end)
    while self:GetIsPlaying() do
        if coroutine.status(tcpListenRoutine) ~= "dead" then
            coroutine.resume(tcpListenRoutine)
        end
        if not self.commandsQueue:GetIsBusy() then
            self:IncreaseTickIndex()
            self:Decide()
        end
        self.commandsQueue:Dequeue()
        Socket.sleep(0.1)
    end
end

--[[
    Main decision maker
--]]
--- Main decision maker function
--- TODO: Implement
function ZappyAI:Decide()
end

-- Export
return ZappyAI
