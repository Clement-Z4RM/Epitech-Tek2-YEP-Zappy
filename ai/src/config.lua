local Config <const> = {
    MaxQueuedCommands = 10,
    MaxLevel = 8,
    Debug = true,
    
    ElevationRequirements = {
        -- 1 > 2
        {
            items = {
                ["linemate"] = 1
            },
            playersCount = 1
        },
        -- 2 > 3
        {
            items = {
                ["linemate"] = 1,
                ["deraumere"] = 1,
                ["sibur"] = 1
            },
            playersCount = 2
        },
        -- 3 > 4 
        {
            items = {
                ["linemate"] = 2,
                ["phiras"] = 2,
                ["sibur"] = 1
            },
            playersCount = 2,
        },
        -- 4 > 5
        {
            items = {
                ["linemate"] = 1,
                ["deraumere"] = 1,
                ["sibur"] = 2,
                ["phiras"] = 1,
            },
            playersCount = 4
        },
        -- 5 > 6
        {
            items = {
                ["linemate"] = 1,
                ["deraumere"] = 2,
                ["sibur"] = 1,
                ["mendiane"] = 3,
            },
            playersCount = 4
        },
        -- 6 > 7
        {
            items = {
                ["linemate"] = 1,
                ["deraumere"] = 2,
                ["sibur"] = 3,
                ["phiras"] = 1
            },
            playersCount = 6
        },
        -- 7 > 8
        {
            items = {
                ["linemate"] = 2,
                ["deraumere"] = 2,
                ["sibur"] = 2,
                ["mendiane"] = 2,
                ["phiras"] = 2,
                ["thystame"] = 1
            },
            playersCount = 6
        }
    },
}

return Config