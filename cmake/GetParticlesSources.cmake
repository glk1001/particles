function(Particles_get_modules Particles_root_dir module_files)
    set(Particles_modules
        ${Particles_root_dir}include/particles/effects/effect.cppm
        ${Particles_root_dir}include/particles/effects/attractor_effect.cppm
        ${Particles_root_dir}include/particles/effects/fountain_effect.cppm
        ${Particles_root_dir}include/particles/effects/tunnel_effect.cppm
        ${Particles_root_dir}include/particles/particle_generators.cppm
        ${Particles_root_dir}include/particles/particle_updaters.cppm
        ${Particles_root_dir}include/particles/particles.cppm
    )

    SET(${module_files} ${Particles_modules} PARENT_SCOPE)
endfunction()

function(Particles_get_source_files Particles_root_dir source_files)
    set(Particles_source_files
        ${Particles_root_dir}src/particles/effects/attractor_effect.cpp
        ${Particles_root_dir}src/particles/effects/fountain_effect.cpp
        ${Particles_root_dir}src/particles/effects/tunnel_effect.cpp
        ${Particles_root_dir}src/particles/particle_generators.cpp
        ${Particles_root_dir}src/particles/particle_updaters.cpp
        ${Particles_root_dir}src/particles/particles.cpp
    )

    SET(${source_files} ${Particles_source_files} PARENT_SCOPE)
endfunction()
