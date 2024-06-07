local Socket <const> = require("socket")
local ZappyAI <const> = require("ai/src/classes/zappy_ai")

--- @module App
local App = {}

--- @return void
function App.ShowHelp()
    print("USAGE:\t./zappy_ai -p port -n name -h machine")
end

--- @param args string[]
--- @return void
function App.Main(args)
    if #args > 0 and args[1] == "-help" then
        return App.ShowHelp()
    end
    local ai <const> = ZappyAI.New(args)
    if not ai.params:ContainsAll({"h", "p", "n"}) then
        return ai:Error("Too few arguments, see -help to see usage.")
    end
    if not ai.server:Connect() then
        return ai:Error("Could not connect to the Zappy server.")
    end
end

return App