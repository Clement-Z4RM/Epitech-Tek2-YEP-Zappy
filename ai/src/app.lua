local Socket <const> = require("socket")
local ZappyAI <const> = require("ai/src/classes/zappy_ai")
local ZappyAIStatus <const> = require("ai/src/enums/zappy_ai_status")

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
    ai.logger:Success("Successfully connected to the Zappy server.")
    if not ai:SetupBaseInfos(commandToSendCfg) then
        return ai:Error("Server denied data, is the team name correct ?")
    end
    ai:SetStatus(ZappyAIStatus.PLAYING)
    ai:SetupThreads()
end

return App