--- @class ZappyCommandsQueue
--- @field public lastCommandSendId number
--- @field public lastCommandReceivedId number
--- @field public commandsHandler {status: number, commandStr: string, cb: fun(answer: string)}[]
--- @field protected parent ZappyAI
local ZappyCommandsQueue = {}

local Config <const> = require("ai/src/config")

local TerminalColor <const> = require("ai/src/constants/terminal_color")
local ZappyAICommandStatus <const> = require("ai/src/enums/zappy_ai_command_status")

--- @param actionStr string
--- @param args string[]
local function buildCommandStr(actionStr, args)
    if not args or #args <= 0 then
        return actionStr
    end
    for _, argStr in ipairs(args) do
        actionStr = actionStr .. (" %s"):format(argStr) 
    end
    return actionStr
end

--- @param parent ZappyAI
--- @return ZappyCommandsQueue
function ZappyCommandsQueue.New(parent)
    local self = setmetatable({}, {__index = ZappyCommandsQueue})

    self.lastCommandReceivedId = 0
    self.lastCommandSendId = 0
    self.commandsHandler = {}
    self.parent = parent
    return self
end

--- @return boolean
function ZappyCommandsQueue:GetIsBusy()
    return self:CountCurrentBeingProcessedCommands() >= 10
end

--- @return number
function ZappyCommandsQueue:CountCurrentBeingProcessedCommands()
    local count = 0

    for _, command in pairs(self.commandsHandler) do
        if command.status == ZappyAICommandStatus.EXECUTED then
            count = count + 1
        end
    end
    return count
end

--- @param dataStr string
function ZappyCommandsQueue:HandleCommandCallback(dataStr)
    self.lastCommandReceivedId = self.lastCommandReceivedId + 1
    
    local commandId <const> = self.lastCommandReceivedId
    local command <const> = self.commandsHandler[commandId]
    if not command then
        self.parent.logger:Warn(("[%s!%s] Received an unknown command id %s#%s%s"):format(TerminalColor.RED, TerminalColor.RESET, TerminalColor.PINK, commandId, TerminalColor.RESET))
        return
    end
    self.parent.logger:Debug(("[%s≪%s] Callback %s%s %scommand (%s#%s%s)"):format(TerminalColor.GREEN, TerminalColor.RESET, TerminalColor.PINK, command.commandStr, TerminalColor.RESET, TerminalColor.PINK, commandId, TerminalColor.RESET))
    self.commandsHandler[commandId].status = ZappyAICommandStatus.RECEIVED
    if not command.cb then
        return
    end
    command.cb(dataStr)
end

--- @param actionStr string
--- @param args string[]
--- @param cb fun(answer: string)
--- @return void
--- @vararg string
function ZappyCommandsQueue:Enqueue(actionStr, cb, args)
    local commandStr <const> = buildCommandStr(actionStr, args)
    
    self.lastCommandSendId = (self.lastCommandSendId + 1)
    self.commandsHandler[self.lastCommandSendId] = {
        status = ZappyAICommandStatus.ENQUEUED,
        commandStr = commandStr,
        cb = cb
    }
    self.parent.logger:Debug(("[%s+%s] Enqued %s%s %scommand (%s#%s%s)"):format(TerminalColor.GREEN, TerminalColor.RESET, TerminalColor.PINK, actionStr, TerminalColor.RESET, TerminalColor.PINK, self.lastCommandSendId, TerminalColor.RESET))
end

--- @return void
function ZappyCommandsQueue:Dequeue()
    local currentBeingProcessedCommandsCount <const> = self:CountCurrentBeingProcessedCommands()
    
    --- @type {index: string, commandStr: string}[]
    local commandsToSend <const> = {}

    if currentBeingProcessedCommandsCount >= Config.MaxQueuedCommands then
        return
    end
    for commandId, command in pairs(self.commandsHandler) do
        if #commandsToSend >= Config.MaxQueuedCommands then
            break
        end
        if command.status ~= ZappyAICommandStatus.ENQUEUED then
            goto continue
        end
        commandsToSend[#commandsToSend + 1] = {
            index = commandId,
            commandStr = command.commandStr
        }
        :: continue ::
    end
    if currentBeingProcessedCommandsCount > 0 then
        while (#commandsToSend + currentBeingProcessedCommandsCount) > Config.MaxQueuedCommands do
            table.remove(commandsToSend, #commandsToSend)
        end
    end
    for _, commandToSendCfg in ipairs(commandsToSend) do
        self.parent.server:Send(commandToSendCfg.commandStr)
        self.parent.logger:Debug(("[%s≫%s] Sent %s%s %scommand (%s#%s%s)"):format(TerminalColor.GREEN, TerminalColor.RESET, TerminalColor.PINK, commandToSendCfg.commandStr, TerminalColor.RESET, TerminalColor.PINK, commandToSendCfg.index, TerminalColor.RESET))
        self.commandsHandler[commandToSendCfg.index].status = ZappyAICommandStatus.EXECUTED
    end
end

return ZappyCommandsQueue