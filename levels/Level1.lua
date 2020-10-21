Level1 = {
    map = {
        textureID = "jungle",
        file = "levels/Level1.map",
        tileSize = 32,
        size = {
            width = 25,
            height = 20
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
                    velocity = 50,
                    angle = 0.0
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
                    velocity = 10.0,
                    angle = 0.0
                },
                sprite = {
                    textureID = "tank-big-down"
                },
                projectileEmitter = {
                    textureID = "bullet-enemy",
                    speed = 150,
                    range = 300,
                    angle = 270 + 0,
                    size = {
                        width = 4,
                        height = 4
                    },
                    shouldLoop = true,
                    particle = {
                        colorBegin = { r = 254 / 255.0, g = 109 / 255.0, b = 41 / 255.0, a = 1.0 },
                        colorEnd = { r = 254 / 255.0, g = 212 / 255.0, b = 123 / 255.0, a = 1.0 },
                        sizeBegin = 0.5,
                        sizeVariation = 0.3,
                        sizeEnd = 0.0,
                        lifeTime = 1.0,
                        velocity = { x = 0.0, y = 0.0 },
                        velocityVariation = { x = 3.0, y = 1.0 },
                        position = { x = 0.0, y = 0.0 },
                    }
                }
            }
        }
    }
}
