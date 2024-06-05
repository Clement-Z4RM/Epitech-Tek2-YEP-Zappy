local Config = require("ai/src/config")

--- @module App
local App = {}

function App.ShowHelp()
    print("USAGE:\t./zappy_gui -p port -h machine")
end

--- @param args string[]
--- @return void
function App.Main(args)
    if args[1] == "-help" then
        return App.ShowHelp()
    end
end

--- @param code number
--- @return void
function App.Exit(code)
    os.exit(code)
end

return App