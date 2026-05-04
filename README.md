*This project has been created as part of the 42 curriculum by Minipl0p, rcompain.*

<div align="center">

```
███╗   ███╗██╗███╗   ██╗██╗██████╗ ████████╗
████╗ ████║██║████╗  ██║██║██╔══██╗╚══██╔══╝
██╔████╔██║██║██╔██╗ ██║██║██████╔╝   ██║   
██║╚██╔╝██║██║██║╚██╗██║██║██╔══██╗   ██║   
██║ ╚═╝ ██║██║██║ ╚████║██║██║  ██║   ██║   
╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝   ╚═╝   
```

*A ray tracer written in C — from scratch, pixel by pixel.*

[![Language](https://img.shields.io/badge/language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Platform](https://img.shields.io/badge/platform-Linux-lightgrey.svg)](https://www.linux.org/)
[![Library](https://img.shields.io/badge/graphics-MacroLibX-orange.svg)](https://github.com/Tabrizian/MacroLibX)

</div>

---

## Table of Contents

    - [Description](#description)
    - [Features](#features)
    - [Mandatory](#mandatory)
    - [Bonus](#bonus)
    - [Solar Mode (.solar)](#solar-mode-solar)
    - [How Ray Tracing Works](#how-ray-tracing-works)
    - [The Ray](#the-ray)
    - [Intersections](#intersections)
    - [Lighting Model (Phong)](#lighting-model-phong)
    - [Shadows](#shadows)
    - [Textures & UV Mapping](#textures--uv-mapping)
    - [Bump Mapping](#bump-mapping)
    - [Gamma Correction](#gamma-correction)
    - [Physics Simulation (Verlet)](#physics-simulation-verlet)
    - [Instructions](#instructions)
    - [Dependencies](#dependencies)
    - [Compilation](#compilation)
    - [Execution](#execution)
    - [Controls](#controls)
    - [Scene File Formats](#scene-file-formats)
    - [Mandatory .rt Format](#mandatory-rt-format)
    - [Bonus .rt Format](#bonus-rt-format)
    - [Solar .solar Format](#solar-solar-format)
    - [Screenshots](#screenshots)
- [Resources](#resources)

    ---

## Description

    **MiniRT** is a ray tracer built entirely from scratch in C as part of the 42 school curriculum. It renders 3D scenes described in plain-text files (`.rt` or `.solar`) by simulating the physical behavior of light rays.

    The project comes in three versions of increasing complexity:

    | Mode | Command | Description |
    |------|---------|-------------|
    | Mandatory | `make` | Basic ray tracer: spheres, planes, cylinders, ambient + diffuse lighting |
    | Bonus | `make bonus` | Full Phong lighting, hard shadows, textures (image map + bump map + chessboard), interactive camera |
    | Solar | `make bonus` + `.solar` file | N-body gravitational simulation using Verlet integration, rendered in real-time with texture-mapped planets |

    The graphics window is provided by **MacroLibX**, a custom lightweight graphics library written in C++ using Vulkan, developed specifically for 42 projects on Linux.

    ---

## Features

### Mandatory

    - **3 geometric primitives**: sphere, plane, infinite cylinder (with caps)
    - **Camera**: configurable position, orientation, and horizontal field of view (FOV)
    - **Ambient light**: uniform background illumination
    - **Point light**: one positional light source with intensity and color
    - **Diffuse (Lambertian) shading**: light intensity proportional to the angle of incidence
    - **Scene parsing**: custom `.rt` file format with strict validation and descriptive error messages
    - **Interactive camera**: real-time navigation with keyboard

### Bonus

    Everything in Mandatory, plus:

    - **Specular highlights** (Phong reflection model): shiny reflections on surfaces
                                                        - **Hard shadows**: shadow rays detect occlusion between the hit point and the light source
                                                        - **Image textures**: PNG texture mapping on spheres, planes, and cylinders using UV coordinates
                                                        - **Bump mapping**: normal perturbation using a grayscale height map for surface detail illusion
                                                        - **Chessboard texture**: procedural alternating two-color pattern on any primitive
                                                        - **Gamma correction**: perceptual color correction applied to the final pixel color
                                                        - **Physics simulation**: N-body gravitational simulation (see Solar Mode)

### Solar Mode (.solar)

                                                        A special extension of the bonus mode activated when a `.solar` file is provided. Each sphere can optionally be given a **mass** (in solar masses) and an **initial velocity vector**.

                                                        At runtime, the gravitational attraction between all physics-enabled bodies is computed at every frame and their positions are updated via **Verlet integration** (60 sub-steps per frame). This allows simulating planetary systems such as our Solar System with physically plausible orbits.

                                                        Units used internally:
                                                        | Quantity | Unit |
                                                        |----------|------|
                                                        | Distance | 1 AU (Astronomical Unit = 1.496×10¹¹ m) |
                                                        | Mass | 1 Solar mass (1.989×10³⁰ kg) |
                                                        | Time | 1 day (86400 s) |

                                                        Pre-built maps are provided:
                                                        - `solar_system.solar` — All 8 planets with NASA-grade textures
                                                        - `Double_sun.solar` — Binary star system
                                                        - `with_mune.solar` — Solar system with major moons

                                                        ---

## How Ray Tracing Works

                                                        Ray tracing is a rendering technique that simulates light by casting rays from the camera into the scene and computing what each ray hits — the inverse of how light physically works (from light sources to the eye).

### The Ray

                                                        For each pixel `(x, y)` on the screen, a ray is constructed:

                                                        ```
    ray.origin = camera.origin
ray.direction = normalize(viewport_corner + x * horizontal_vec + y * vertical_vec - camera.origin)
    ```

    The viewport is built from the camera's FOV and the aspect ratio of the window:

    ```
focal = 1 / tan(fov / 2)
    horizontal_vec = right_vector * aspect_ratio
    vertical_vec   = up_vector
    corner         = forward * focal - horizontal_vec/2 - vertical_vec/2
    ```

    All rays are normalized before use to guarantee consistent distance calculations.

### Intersections

    For each ray, every object in the scene is tested. The closest positive intersection (`t > 0.001`) is kept.

#### Sphere

    A sphere of center **C** and radius **r** is hit when:

    ```
    ||ray(t) - C||² = r²
    ```

    Expanding with `ray(t) = O + t*D` and `oc = O - C`:

    ```
    a = D·D
    b = oc·D
    c = oc·oc - r²
    discriminant = b² - a*c

t = (-b - sqrt(discriminant)) / a   (nearest root)
    ```

    If `discriminant < 0` → no intersection. If the nearest `t` is behind the camera (negative), the far root is tested.

#### Plane

    A plane defined by a point **P** and normal **N** intersects at:

    ```
t = ((P - O) · N) / (D · N)
    ```

    If `D · N ≈ 0` the ray is parallel to the plane (no intersection).

#### Cylinder

    The cylinder (axis **v**, center **C**, radius **r**, height **h**) requires separating the ray into components parallel and perpendicular to the axis:

    ```
    A_vec = D - (D·v)*v        // D projected onto plane perpendicular to axis
    B_vec = oc - (oc·v)*v      // oc projected similarly

    a = A_vec · A_vec
    b = A_vec · B_vec
    c = B_vec · B_vec - r²
    ```

    After solving the quadratic, the hit point is checked to be within `[-h/2, h/2]` along the axis. The two flat **caps** are tested independently as disk-plane intersections.

### Lighting Model (Phong)

    The Phong model decomposes light into three components:

    ```
    I = ambient + diffuse + specular
    ```

#### Ambient

    ```
    ambient[c] = (ambient_color[c] / 255) * ambient_ratio
    ```

    Always present regardless of geometry.

#### Diffuse (Lambertian)

    ```
coef_diffuse = dot(N, L)          // N = surface normal, L = direction to light
    diffuse[c]   = (light_color[c] / 255) * coef_diffuse * light_intensity
    ```

    Only applied if `coef_diffuse > 0` (surface faces the light) and no shadow occlusion.

#### Specular (Phong)

    ```
    R = 2 * (N·L) * N - L            // reflection vector
coef_specular = dot(R, V)         // V = direction to camera
    specular[c] = (light_color[c] / 255) * pow(coef_specular, SHININESS) * KS * intensity
    ```

    Constants used: `SHININESS = 32`, `KS = 0.5`.

    Only applied when `coef_specular > EPS`.

#### Final composition

    ```
    light[c] = clamp(ambient[c] + diffuse[c] + specular[c], 0.0, 1.0)
pixel_color[c] = 255 * pow(object_color[c] * light[c] / 255, GAMMA)
    ```

### Shadows

    After finding a hit point, a **shadow ray** is cast from the hit point toward the light source:

    ```
    shadow_ray.origin    = hit_point + 0.001 * normal    // small offset to avoid self-intersection
shadow_ray.direction = normalize(light_position - hit_point)
    ```

    The scene is tested for any intersection along this ray with `t < distance_to_light`. If found, the point is in shadow — diffuse and specular components are zeroed.

    The `0.001` epsilon offset is critical to prevent **shadow acne** (a surface incorrectly self-shadowing due to floating-point imprecision).

### Textures & UV Mapping

    In bonus mode, a texture image (PNG) can be mapped onto any primitive by computing **(u, v)** coordinates at the hit point — normalized coordinates in [0, 1] that indicate where in the image to sample.

#### Sphere UV

    ```
u = 0.5 + atan2(Pz, Px) / (2π)
    v = 0.5 + asin(Py) / π
    ```

    where `(Px, Py, Pz)` is the normalized hit point relative to the sphere center.

#### Plane UV

    Two orthogonal tangent vectors are computed from the plane normal:

    ```
    tangent   = cross(normal, up)    // (fallback to 'depth' if normal ≈ up)
    bitangent = cross(normal, tangent)
    u = dot(hit_point, tangent)
v = dot(hit_point, bitangent)
    ```

#### Cylinder UV

    The lateral surface uses the angle around the axis for `u` and the projection along the axis for `v`. Caps use the same tangent/bitangent method as the plane.

#### Chessboard

    Instead of sampling an image, the UV index is computed:

    ```
case_idx = floor(u / scale) + floor(v / scale)
    color = (case_idx % 2 == 0) ? color1 : color2
    ```

### Bump Mapping

    Bump mapping perturbs the surface **normal** at a hit point to simulate fine surface relief without modifying geometry. A grayscale height map image is used.

    For a hit point with UV coordinates `(u, v)`, the gradient is estimated by finite differences:

    ```
    h        = luminance(bump_map(u,     v))
    h_next_u = luminance(bump_map(u+du,  v))
h_next_v = luminance(bump_map(u,     v+dv))

    gradient_u = h_next_u - h
    gradient_v = h_next_v - h
    ```

    where `luminance = (r + g + b) / (3 * 255)`.

    The normal is then perturbed along the tangent and bitangent vectors:

    ```
new_normal = normalize(normal + gradient_u * tangent + gradient_v * bitangent)
    ```

    This creates the illusion of bumps and ridges on the surface.

### Gamma Correction

    Human vision perceives brightness non-linearly. Without correction, dark tones appear too dark on screen. A gamma of **0.8** is applied after lighting:

    ```
final_color[c] = 255 * pow(lit_color[c] / 255, GAMMA)    // GAMMA = 0.8
    ```

    ---

## Physics Simulation (Verlet)

    The solar mode uses **Verlet integration** to update the position of each physics-enabled body each frame. Unlike Euler integration, Verlet does not require storing velocity explicitly — it is implicitly encoded in the difference between the current and previous positions, making it **more numerically stable** over long simulations.

### Position Update

    ```
    new_pos = 2 * cur_pos - prev_pos + acc * dt²
    ```

    After the update, `prev_pos ← cur_pos` and `cur_pos ← new_pos`.

### Acceleration (Gravitational N-body)

    For each pair of bodies `(i, j)`:

    ```
dir  = normalize(pos_j - pos_i)
    dist = ||pos_j - pos_i||

    acc_i += G * m_j / dist² * dir
    acc_j -= G * m_i / dist² * dir
    ```

    Pairs with `dist < 0.001` are skipped to avoid singularities (collision/merger condition).

    The gravitational constant is scaled to the AU/solar_mass/day unit system:

    ```
    G = 2.959122e-4    (AU³ / (solar_mass * day²))
DT = 0.01          (days per step)
    ```

### Simulation Speed

    60 Verlet steps are executed per rendered frame, meaning each visual frame represents `60 * DT = 0.6` simulated days.

    ---

## Instructions

### Dependencies

    MiniRT uses **MacroLibX** (included as a submodule) which requires:

    ```bash
# Ubuntu / Debian
    sudo apt-get install build-essential cmake libvulkan-dev libx11-dev libxext-dev

# Arch Linux
    sudo pacman -S base-devel cmake vulkan-headers libx11 libxext
    ```

    > **Note:** A Vulkan-compatible GPU driver is required. On VMs, ensure Vulkan support is enabled.

### Compilation

    ```bash
# Clone the repository (with submodules)
    git clone --recurse-submodules https://github.com/Remi-cpn/MiniRT.git
    cd MiniRT

# Build MacroLibX first (done automatically by the Makefile)
# Compile mandatory version
    make

# Compile bonus version (textures, bump maps, physics)
    make bonus

# Clean objects
    make clean

# Full clean (objects + binary)
    make fclean

# Rebuild
    make re
    ```

    > The Makefile automatically selects the correct source directory (`Mandatory/` or `Bonus/`) based on the build target.

### Execution

    ```bash
# Mandatory
    ./minirt path/to/scene.rt

# Bonus (standard .rt file)
    ./minirt path/to/scene.rt

# Bonus (solar simulation)
    ./minirt path/to/scene.solar
    ```

    Example scenes are provided in `Mandatory/maps/` and `Bonus/maps/`.

    ```bash
# Quick test examples
    ./minirt Mandatory/maps/basic.rt
    ./minirt Bonus/maps/solar_system.solar
    ./minirt Bonus/maps/Double_sun.solar
    ./minirt Bonus/maps/with_mune.solar
    ```

    > The program detects the `.solar` extension automatically and activates the physics simulation accordingly.

### Controls

    | Key | Action |
    |-----|--------|
    | `ESC` | Quit the program |
    | `W` | Move camera forward |
    | `S` | Move camera backward |
    | `A` | Strafe left |
    | `D` | Strafe right |
    | `SPACE` | Move camera up |
    | `CTRL` | Move camera down |
    | `↑` | Rotate camera up (pitch) |
    | `↓` | Rotate camera down (pitch) |
    | `←` | Rotate camera left (yaw) |
    | `→` | Rotate camera right (yaw) |
    | `I` | Increase FOV |
    | `O` | Decrease FOV |
    | `R` | Reload scene from file |
    | ✕ (window close) | Quit the program |

    > **Note:** CTRL and SPACE are currently bound but partially unused in the update logic — camera vertical movement is active. R reloads and reparses the `.rt` file on the fly without restarting.

    ---

## Scene File Formats

    All scene files use **space-separated fields** on each line. Lines beginning with `#` are comments (bonus only). Each identifier must appear **exactly once** for `A`, `C`, and `L`. Objects (`sp`, `pl`, `cy`) can be repeated freely.

### Mandatory .rt Format

    | Identifier | Fields | Description |
    |------------|--------|-------------|
    | `A` | `ratio R,G,B` | Ambient light. `ratio` ∈ [0.0, 1.0] |
    | `C` | `x,y,z dx,dy,dz fov` | Camera. Direction must be normalized. `fov` ∈ ]0, 180[ |
    | `L` | `x,y,z intensity R,G,B` | Point light. `intensity` ∈ [0.0, 1.0] |
    | `sp` | `x,y,z diameter R,G,B` | Sphere |
    | `pl` | `x,y,z nx,ny,nz R,G,B` | Plane. Normal must be normalized |
    | `cy` | `x,y,z ax,ay,az diameter height R,G,B` |
