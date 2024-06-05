local ZappyAI = require("ai/src/classes/zappy_ai")
local Config = require("ai/src/config")

--- @module App
local App = {}

function App.ShowHelp()
    print("USAGE:\t./zappy_ai -p port -n name -h machine")
end

--- @param args string[]
--- @return void
function App.Main(args)
    if #args > 0 and args[1] == "-help" then
        return App.ShowHelp()
    end
    local zappyAI <const> = ZappyAI.New(args)
    
end

--- @param code number
--- @return void
function App.Exit(code)
    os.exit(code)
end

return App