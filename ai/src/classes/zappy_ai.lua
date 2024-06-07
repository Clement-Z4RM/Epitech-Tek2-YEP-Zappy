--- @class ZappyAI
--- @field public params ZappyParamsContainer
--- @field public server ZappyServer
local ZappyAI <const> = {}

local ZappyParamsContainer <const> = require("ai/src/classes/zappy_params")
local ZappyServer <const> = require("ai/src/classes/zappy_server")

--- @param args string[]
--- @return ZappyAI
function ZappyAI.New(args)
    local self = setmetatable({}, { __index = ZappyAI })
    
    self.params = ZappyParamsContainer.New(args)
    self.server = ZappyServer.New(self, self.params:Get("h"), self.params:Get("p"))
    return self
end

--- @param message string
--- @return void
function ZappyAI:Error(message)
    print(("Error: %s"):format(message))
    os.exit(84)
end


-- Export
return ZappyAI