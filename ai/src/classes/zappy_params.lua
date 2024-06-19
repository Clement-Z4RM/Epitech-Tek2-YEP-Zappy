--- @field protected params table<string, any>
--- @class ZappyParamsContainer
local ZappyParamsContainer = {}

--- @param args string[]
--- @return table<string, any>
local function parseParams(args)
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

--- @param args string[]
--- @return ZappyParamsContainer
function ZappyParamsContainer.New(args)
    local self = setmetatable({}, {__index = ZappyParamsContainer})

    self.params = parseParams(args)
    return self
end

--- @param expectedArg string
--- @return boolean
function ZappyParamsContainer:Contains(expectedArg)
    return self.params[expectedArg] ~= nil
end

--- @param expectedArgs string[]
--- @return boolean
function ZappyParamsContainer:ContainsAll(expectedArgs)
    for _, argIdentifier in ipairs(expectedArgs) do
        if not self:Contains(argIdentifier) then
            return false
        end
    end
    return true
end

--- @param paramIdentifier string
--- @return string | number
function ZappyParamsContainer:Get(paramIdentifier)
    local arg <const> = self.params[paramIdentifier]

    if not arg then
        return
    end
    local numericalArg <const> = tonumber(arg)
    return (numericalArg ~= nil and numericalArg or arg)
end

return ZappyParamsContainer