Level1 = {
    name = "Level 1",
    mapImage = "images/Level1.png",
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
            entityType = 4,

            components = {
                transform = {
                    position = {
                        x = -575.0,
                        y = 545.0
                    },
                    size = {
                        width = 16,
                        height = 16
                    },
                    velocity = 50,
                    angle = 0.0
                },
                sprite = {
                    textureID = "start",
                    isAnimated = false
                }
            }
        },
        [1] = {
            entityType = 5,

            components = {
                transform = {
                    position = {
                        x = 600.0,
                        y = -125.0
                    },
                    size = {
                        width = 16,
                        height = 16
                    },
                    velocity = 50,
                    angle = 0.0
                },
                sprite = {
                    textureID = "heliport",
                    isAnimated = false
                }
            }
        },
        [2] = {
            entityType = 0,

            components = {
                transform = {
                    position = {
                        x = -575.0,
                        y = 545.0
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
        [3] = {
            entityType = 1,

            components = {
                transform = {
                    position = {
                        x = -350.0,
                        y = 250.0
                    },
                    size = {
                        width = 16,
                        height = 16
                    },
                    velocity = 10.0,
                    angle = 180.0
                },
                sprite = {
                    textureID = "tank-big-down"
                },
                projectileEmitter = {
                    textureID = "bullet-enemy",
                    speed = 150,
                    range = 300,
                    angle = 270 + 180,
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
        },
        [4] = {
            entityType = 1,

            components = {
                transform = {
                    position = {
                        x = -710.0,
                        y = -320.0
                    },
                    size = {
                        width = 16,
                        height = 16
                    },
                    velocity = 10.0,
                    angle = 180.0
                },
                sprite = {
                    textureID = "tank-big-down"
                },
                projectileEmitter = {
                    textureID = "bullet-enemy",
                    speed = 150,
                    range = 300,
                    angle = 270 + 180,
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
        },
        [5] = {
            entityType = 1,

            components = {
                transform = {
                    position = {
                        x = -600.0,
                        y = -320.0
                    },
                    size = {
                        width = 16,
                        height = 16
                    },
                    velocity = 10.0,
                    angle = 135.0
                },
                sprite = {
                    textureID = "tank-big-down"
                },
                projectileEmitter = {
                    textureID = "bullet-enemy",
                    speed = 150,
                    range = 300,
                    angle = 270 + 135,
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
        },
        [6] = {
            entityType = 1,

            components = {
                transform = {
                    position = {
                        x = -600.0,
                        y = -450.0
                    },
                    size = {
                        width = 16,
                        height = 16
                    },
                    velocity = 10.0,
                    angle = 90.0
                },
                sprite = {
                    textureID = "tank-big-down"
                },
                projectileEmitter = {
                    textureID = "bullet-enemy",
                    speed = 150,
                    range = 300,
                    angle = 270 + 90,
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
        },
        [7] = {
            entityType = 1,

            components = {
                transform = {
                    position = {
                        x = -600.0,
                        y = 160.0
                    },
                    size = {
                        width = 16,
                        height = 16
                    },
                    velocity = 10.0,
                    angle = 0.0
                },
                sprite = {
                    textureID = "truck-right"
                }
            }
        },
        [8] = {
            entityType = 1,

            components = {
                transform = {
                    position = {
                        x = -250.0,
                        y = 140.0
                    },
                    size = {
                        width = 16,
                        height = 16
                    },
                    velocity = 10.0,
                    angle = 0.0
                },
                sprite = {
                    textureID = "army-group-3"
                }
            }
        },
        [9] = {
            entityType = 1,

            components = {
                transform = {
                    position = {
                        x = -250.0,
                        y = 100.0
                    },
                    size = {
                        width = 16,
                        height = 16
                    },
                    velocity = 10.0,
                    angle = 0.0
                },
                sprite = {
                    textureID = "truck-right"
                }
            }
        },
        [10] = {
            entityType = 1,

            components = {
                transform = {
                    position = {
                        x = -250.0,
                        y = 60.0
                    },
                    size = {
                        width = 16,
                        height = 16
                    },
                    velocity = 10.0,
                    angle = 0.0
                },
                sprite = {
                    textureID = "army-group-3"
                }
            }
        },
        [11] = {
            entityType = 1,

            components = {
                transform = {
                    position = {
                        x = -150.0,
                        y = 100.0
                    },
                    size = {
                        width = 16,
                        height = 16
                    },
                    velocity = 10.0,
                    angle = 90.0
                },
                sprite = {
                    textureID = "tank-big-down"
                },
                projectileEmitter = {
                    textureID = "bullet-enemy",
                    speed = 150,
                    range = 300,
                    angle = 270 + 90,
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
        },
        [12] = {
            entityType = 1,

            components = {
                transform = {
                    position = {
                        x = -50.0,
                        y = 250.0
                    },
                    size = {
                        width = 16,
                        height = 16
                    },
                    velocity = 10.0,
                    angle = 180.0
                },
                sprite = {
                    textureID = "tank-big-down"
                },
                projectileEmitter = {
                    textureID = "bullet-enemy",
                    speed = 150,
                    range = 300,
                    angle = 270 + 180,
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
        },
        [13] = {
            entityType = 1,

            components = {
                transform = {
                    position = {
                        x = -20.0,
                        y = -100.0
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
        },
        [14] = {
            entityType = 1,

            components = {
                transform = {
                    position = {
                        x = 450.0,
                        y = -130.0
                    },
                    size = {
                        width = 16,
                        height = 16
                    },
                    velocity = 10.0,
                    angle = 270.0
                },
                sprite = {
                    textureID = "tank-big-down"
                },
                projectileEmitter = {
                    textureID = "bullet-enemy",
                    speed = 150,
                    range = 300,
                    angle = 270 + 270,
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
        },
        [15] = {
            entityType = 1,

            components = {
                transform = {
                    position = {
                        x = 300.0,
                        y = 120.0
                    },
                    size = {
                        width = 16,
                        height = 16
                    },
                    velocity = 10.0,
                    angle = 0.0
                },
                sprite = {
                    textureID = "truck-right"
                }
            }
        },
        [16] = {
            entityType = 1,

            components = {
                transform = {
                    position = {
                        x = 500.0,
                        y = 450.0
                    },
                    size = {
                        width = 16,
                        height = 16
                    },
                    velocity = 10.0,
                    angle = 180.0
                },
                sprite = {
                    textureID = "tank-big-down"
                },
                projectileEmitter = {
                    textureID = "bullet-enemy",
                    speed = 150,
                    range = 300,
                    angle = 270 + 180,
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
        },
        [17] = {
            entityType = 1,

            components = {
                transform = {
                    position = {
                        x = 580.0,
                        y = 160.0
                    },
                    size = {
                        width = 16,
                        height = 16
                    },
                    velocity = 10.0,
                    angle = 180.0
                },
                sprite = {
                    textureID = "tank-big-down"
                },
                projectileEmitter = {
                    textureID = "bullet-enemy",
                    speed = 150,
                    range = 300,
                    angle = 270 + 180,
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
        },
        [18] = {
            entityType = 1,

            components = {
                transform = {
                    position = {
                        x = 600.0,
                        y = -60.0
                    },
                    size = {
                        width = 16,
                        height = 16
                    },
                    velocity = 10.0,
                    angle = 0.0
                },
                sprite = {
                    textureID = "truck-left"
                }
            }
        },
        [19] = {
            entityType = 1,

            components = {
                transform = {
                    position = {
                        x = 600.0,
                        y = -190.0
                    },
                    size = {
                        width = 16,
                        height = 16
                    },
                    velocity = 10.0,
                    angle = 0.0
                },
                sprite = {
                    textureID = "truck-left"
                }
            }
        }
    }
}
