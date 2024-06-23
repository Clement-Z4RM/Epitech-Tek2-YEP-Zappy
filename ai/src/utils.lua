--- @module Utils
local Utils = {}

local ZappyAction <const> = require("ai/src/constants/network_zappy_action")

--- @param inputStr string
--- @param sep string
--- @return string[]
function Utils.SplitString(inputStr, sep)
    if sep == nil then
        sep = "%s"
    end
    local tbl = {}
    for str in string.gmatch(inputStr, "([^" .. sep .. "]+)") do
        table.insert(tbl, str)
    end
    return tbl
end

--- @param str string
--- @param prefix string
--- @return boolean
function Utils.StartsWith(str, prefix)
    return string.sub(str, 1, string.len(prefix)) == prefix
end

--- @param tileIndex number
--- @return string[]
function Utils.GetActionsToTile(tileIndex)
    if tileIndex == 1 then
        return {ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_LEFT}
    end
    if tileIndex == 2 then
        return {ZappyAction.MOVE_FORWARD}
    end
    if tileIndex == 3 then
        return {ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_RIGHT}
    end
    if tileIndex == 4 then
        return {ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_LEFT, ZappyAction.MOVE_LEFT}
    end
    if tileIndex == 5 then
        return {ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_LEFT}
    end
    if tileIndex == 6 then
        return {ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_FORWARD}
    end
    if tileIndex == 7 then
        return {ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_RIGHT}
    end
    if tileIndex == 8 then
        return {ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_RIGHT, ZappyAction.MOVE_RIGHT}
    end
    if tileIndex == 9 then
        return {ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_LEFT, ZappyAction.MOVE_LEFT, ZappyAction.MOVE_LEFT}
    end
    if tileIndex == 10 then
        return {ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_LEFT, ZappyAction.MOVE_LEFT}
    end
    if tileIndex == 11 then
        return {ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_LEFT}
    end
    if tileIndex == 12 then
        return {ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_FORWARD}
    end
    if tileIndex == 13 then
        return {ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_RIGHT}
    end
    if tileIndex == 14 then
        return {ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_RIGHT, ZappyAction.MOVE_RIGHT}
    end
    if tileIndex == 15 then
        return {ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_FORWARD, ZappyAction.MOVE_RIGHT, ZappyAction.MOVE_RIGHT, ZappyAction.MOVE_RIGHT}
    end
end

return Utils