--- @class ZappyAI
--- @field protected params table<string, any>
local ZappyAI = {}

--- @param args string[]
--- @return ZappyAI
function ZappyAI.New(args)
    local self = setmetatable({}, { __index = ZappyAI })
    
    self.params = self:ParseParams(args)
    return self
end

--- @param args string[]
--- @return table<string, any>
function ZappyAI:ParseParams(args)
    local params = {}
    local currentParamIdentifier
    
    for _, paramValue in ipairs(args) do
        if currentParamIdentifier then
            params[currentParamIdentifier] = paramValue
            currentParamIdentifier = nil
        end
        
        if paramValue:sub(1, 1) == "-" then
            local identifier <const> = paramValue:sub(2)
            currentParamIdentifier = identifier
        end
    end
    return params
end

return ZappyAI