--- @module Utils
local Utils = {}

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

return Utils