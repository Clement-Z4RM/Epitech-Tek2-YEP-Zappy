--- @class ZappyEnvironment
--- @field public tiles ZappyTile[]
local ZappyEnvironment = {}

local ZappyTile <const> = require("ai/src/classes/zappy_tile")

--- @param tiles ZappyTile[]
--- @return ZappyEnvironment
function ZappyEnvironment.New(tiles)
    local self = setmetatable({}, {__index = ZappyEnvironment})

    self.tiles = {}
    for tileIndex, tileInventory in ipairs(tiles) do
        self.tiles[#self.tiles + 1] = ZappyTile.New(tileIndex, tileInventory)
    end
    return self
end

--- @param itemName string
--- @return ZappyTile
function ZappyEnvironment:GetTileWith(itemName)
    for _, tile in ipairs(self.tiles) do
        if tile:Has(itemName) then
            return tile
        end
    end
end

return ZappyEnvironment