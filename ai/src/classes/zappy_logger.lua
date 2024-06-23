--- @class ZappyLogger
local ZappyLogger = {}

local Config <const> = require("ai/src/config")

--- @return ZappyLogger
function ZappyLogger.New()
    local self = setmetatable({}, {__index = ZappyLogger})
    return self
end

--- @param message string
--- @return void
function ZappyLogger:Debug(message)
    if not Config.Debug then
        return
    end
    print(("\27[35m[Debug] \27[97m%s"):format(message))
end

--- @param message string
--- @return void
function ZappyLogger:Success(message)
    print(("\27[32m[Success] \27[97m%s"):format(message))
end

--- @param message string
--- @return void
function ZappyLogger:Info(message)
    print(("\27[34m[Info] \27[97m%s"):format(message))
end

--- @param message string
--- @return void
function ZappyLogger:Warn(message)
    print(("\27[33m[Warning] \27[97m%s"):format(message))
end

--- @param message string
--- @return void
function ZappyLogger:Error(message)
    print(("\27[91m[Error] \27[97m%s"):format(message))
end

return ZappyLogger