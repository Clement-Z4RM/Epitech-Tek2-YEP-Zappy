--- @class ZappyAI
--- @field public params ZappyParamsContainer
--- @field public server ZappyServer
--- @field public logger ZappyLogger
--- @field public inventory ZappyInventory
--- @field public status number
--- @field public worldDimensions {x: number, y: number}
--- @field protected numTicks
local ZappyAI <const> = {}

local Posix <const> = require("posix")
local Socket <const> = require("socket")
local ZappyAction <const> = require("ai/src/constants/network_zappy_action")
local ZappyParamsContainer <const> = require("ai/src/classes/zappy_params")
local ZappyInventory <const> = require("ai/src/classes/zappy_inventory")
local ZappyAIStatus <const> = require("ai/src/enums/zappy_ai_status")
local ZappyServer <const> = require("ai/src/classes/zappy_server")
local ZappyLogger <const> = require("ai/src/classes/zappy_logger")
local Utils <const> = require("ai/src/utils")

--- @param args string[]
--- @return ZappyAI
function ZappyAI.New(args)
    local self = setmetatable({}, { __index = ZappyAI })
    
    self.params = ZappyParamsContainer.New(args)
    self.server = ZappyServer.New(self.params:Get("h"), self.params:Get("p"))
    self.logger = ZappyLogger.New()
    self.inventory = ZappyInventory.New()
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

--- @TODO: Implement
function ZappyAI:LookupEnvironment()
    local result <const> = self.server:SendSync(ZappyAction.LOOKUP_ENVIRONMENT)
end

--[[
    AI Core
--]]
--- @return void
function ZappyAI:IncreaseTickIndex()
    self.numTicks = self.numTicks + 1
end

--- @return void
function ZappyAI:Tick()
    if self.numTicks == 0 then
        self:SetupInventory()
    end
    self:LookupEnvironment()
    self:IncreaseTickIndex()
end

-- Export
return ZappyAI