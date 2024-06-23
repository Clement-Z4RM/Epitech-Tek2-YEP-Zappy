--- @class ZappyInventory
--- @field public items table<string, number>
local ZappyInventory = {}

local Json <const> = require("ai/src/vendors/json")

--- @param inventory ZappyInventory
local function classToString(inventory)
    return Json.encode(inventory.items)
end

--- @return ZappyInventory
function ZappyInventory.New()
    local self = setmetatable({}, {__index = ZappyInventory, __tostring = classToString})

    self.items = {}
    return self
end

--- @param itemName string
--- @param quantity string
--- @return boolean true if the item has been removed
function ZappyInventory:Remove(itemName, quantity)
    quantity = quantity or 1
    
    local currentCount <const> = self:Count(itemName)
    if currentCount == 0 or currentCount < quantity then
        return false
    end
    local newCount = currentCount - quantity
    if newCount <= 0 then
        newCount = 0
    end
    self.items[itemName] = newCount
    return true
end

--- @param itemName string
--- @param quantity number | nil
function ZappyInventory:Add(itemName, quantity)
    if quantity == 0 then
        return
    end
    quantity = quantity or 1
    local currentCount <const> = self:Count(itemName)
    if currentCount == 0 then
        self.items[itemName] = quantity
        return
    end
    self.items[itemName] = self.items[itemName] + quantity
end

--- @param itemName string
--- @return boolean
function ZappyInventory:Contains(itemName)
    return self.items[itemName] ~= nil
end

--- @param itemName string
--- @param quantity number | nil
--- @return boolean
function ZappyInventory:Has(itemName, quantity)
    quantity = quantity or 1
    
    local currentCount <const> = self:Count(itemName)
    if currentCount == 0 then
        return false
    end
    return currentCount >= quantity
end

--- @param itemName string
--- @return number
function ZappyInventory:Count(itemName)
    local count <const> = self.items[itemName]
    if not count then
        return 0
    end
    return count
end

return ZappyInventory