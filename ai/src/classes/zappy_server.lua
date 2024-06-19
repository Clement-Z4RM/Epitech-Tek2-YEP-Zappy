--- @field protected host string
--- @field protected port number
--- @field protected tcp table
--- @field protected status number
--- @class ZappyServer
local ZappyServer = {}

local NetworkZappyAnswer <const> = require("ai/src/constants/network_zappy_answer")
local NetworkTCPStatus <const> = require("ai/src/enums/network_tcp_status")
local Socket <const> = require("socket")

--- @param host string
--- @param port number
--- @return ZappyServer
function ZappyServer.New(host, port)
    local self = setmetatable({}, {__index = ZappyServer})
    
    self.host = host
    self.port = port
    self.tcp = Socket.tcp()
    self.status = NetworkTCPStatus.IDLE
    return self
end

--- @return number
function ZappyServer:GetStatus()
    return self.status
end

--- @param content string
function ZappyServer:Send(content)
    self.tcp:send(("%s\n"):format(content))
end

--- @param content string
--- @param numResults number
--- @return string | string[]
function ZappyServer:SendSync(content, numResults)
    self:Send(content)
    if not numResults then
        return self:GetLastAnswer()
    end
    local results <const> = {}
    for i = 1, numResults do
        local tcpAnswer <const> = self:GetLastAnswer()
        if tcpAnswer == "ko" then
            break
        end
        results[#results + 1] = tcpAnswer
    end
    return results
end

--- @return boolean
function ZappyServer:Connect()
    self.tcp:connect(self.host, self.port)
    local answer <const> = self.tcp:receive()
    if not answer or answer ~= NetworkZappyAnswer.CONNECTED then
        return false
    end
    return true
end

--- @return string
function ZappyServer:GetLastAnswer()
    local answer <const> = self.tcp:receive()
    return answer
end

--- @return boolean true if successfully disconnected
function ZappyServer:Disconnect()
    if self.status ~= NetworkTCPStatus.CONNECTED then
        return false
    end
    self.tcp:close()
    self.status = NetworkTCPStatus.INTERRUPTED
    return true
end

return ZappyServer