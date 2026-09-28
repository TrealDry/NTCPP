local function load()
    local ok, err = pcall(function()
        animation.add("bullet_1", {"sprBullet1_0","sprBullet1_1"}, 1/14, false)
    end)
    print(ok, err)

    --animation.add("bullet_1", {"sprBullet1_0", "sprBullet1_1"}, 1 / 14, false)
    animation.add("mutant_1_idle", {"sprMutant1Idle_0", "sprMutant1Idle_1", "sprMutant1Idle_2", "sprMutant1Idle_3"}, 1 / 14, true)
    animation.add("mutant_1_walk", {"sprMutant1Walk_0", "sprMutant1Walk_1", "sprMutant1Walk_2", "sprMutant1Walk_3", "sprMutant1Walk_4", "sprMutant1Walk_5"}, 1 / 14, true)
end

local function unload()
    -- f
end

return {
    load = load,
    unload = unload
}