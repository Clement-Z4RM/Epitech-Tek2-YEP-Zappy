-- look_parser.lua

local LookParser = {}

--- Parse the response of the look command
--- @param response string
--- @return table
function LookParser.Parse(response)
    local tiles = {}
    -- Remove the surrounding brackets
    response = response:sub(2, -2)
    -- Split the response by commas
    for tile in response:gmatch("[^,]+") do
        local objects = {}
        -- Split each tile's content by spaces
        for obj in tile:gmatch("%S+") do
            table.insert(objects, obj)
        end
        table.insert(tiles, objects)
    end
    return tiles
end

return LookParser
