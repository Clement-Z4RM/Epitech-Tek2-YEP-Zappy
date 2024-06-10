--- @class ZappyLogger
local ZappyLogger = {}

--- @return ZappyLogger
function ZappyLogger.New()
    local self = setmetatable({}, {__index = ZappyLogger})
    return self
end

--- @param message string
--- @return void
function ZappyLogger:Info(message)
    print(("\27[34m[Info] \27[97m%s"):format(message))
end

--- @param message string
--- @return void
function ZappyLogger:Error(message)
    print(("\27[91m[Error] \27[97m%s"):format(message))
end

return ZappyLogger