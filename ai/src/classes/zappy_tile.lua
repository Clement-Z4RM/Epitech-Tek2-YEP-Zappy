--- @field protected position number
--- @field protected items string[]
--- @class ZappyTile
local ZappyTile = {}

--- @param position number
--- @param items string[]
--- @return ZappyTile
function ZappyTile.New(position, items)
    local self = setmetatable({}, {__index = ZappyTile})
   
    self.position = position
    self.items = items
    return self
end

--- @return number
function ZappyTile:GetPosition()
    return (self.position - 1)
end

--- @param itemName string
--- @return boolean
function ZappyTile:Has(itemName)
    if #self.items == 0 then
        return false
    end
    for _, tileItemName in ipairs(self.items) do
        if tileItemName == itemName then
            return true
        end
    end
    return false
end

--- @param itemName string
--- @return number
function ZappyTile:CountItems(itemName)
    local count = 0

    for _, tileItemName in ipairs(self.items) do
        if tileItemName == itemName then
            count = count + 1
        end
    end
    return count
end

return ZappyTile