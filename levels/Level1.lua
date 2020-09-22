Level1 = {
    map = {
        textureID = "jungle",
        file = "levels/Level1.map",
        tileSize = 32,
        size = {
            width = 25,
            heigth = 20
        }
    },

    entities = {
        [0] = {
            entityType = 0,

            components = {
                transform = {
                    position = {
                        x = 0.0,
                        y = 0.0
                    },
                    size = {
                        width = 16,
                        height = 16
                    },
                    velocity = 50
                },
                sprite = {
                    textureID = "chopper-spritesheet",
                    isAnimated = true,
                    spriteOffset = {
                        x = 2,
                        y = 4
                    }
                }
            }
        },
        [1] = {
            entityType = 1,

            components = {
                transform = {
                    position = {
                        x = 50.0,
                        y = 30.0
                    },
                    size = {
                        width = 16,
                        height = 16
                    },
                    velocity = 10
                },
                sprite = {
                    textureID = "tank-big-down"
                }
            }
        }
    }
}
