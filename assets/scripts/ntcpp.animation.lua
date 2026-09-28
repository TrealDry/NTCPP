local function load()
    animation.add("bullet_1", {"sprBullet1_0","sprBullet1_1"}, {14, 8}, 1 / 14, false)
    animation.add("mutant_1_idle", {"sprMutant1Idle_0", "sprMutant1Idle_1", "sprMutant1Idle_2", "sprMutant1Idle_3"}, {0, 0}, 1 / 14, true)
    animation.add("mutant_1_walk", {"sprMutant1Walk_0", "sprMutant1Walk_1", "sprMutant1Walk_2", "sprMutant1Walk_3", "sprMutant1Walk_4", "sprMutant1Walk_5"}, {0, 0}, 1 / 14, true)
end

local function unload()
    -- f
end

return {
    load = load,
    unload = unload
}